"""
Cryptanalysis - Padding Oracle Attack

This module demonstrates padding oracle attacks, which exploit the fact that
some cryptographic systems reveal information about whether padding is valid
or not. This information can be used to decrypt ciphertext without knowing
the encryption key.

Key Concepts:
- Padding Oracle: A system that reveals whether padding is valid
- CBC Mode: Cipher Block Chaining mode of operation
- PKCS#7 Padding: Standard padding scheme for block ciphers
- Chosen Ciphertext Attack: Attacker can choose ciphertexts to decrypt
- Side-Channel Information: Information leaked through system behavior

Security Implications:
- Can completely break CBC mode encryption
- Exploits implementation flaws, not algorithm weaknesses
- Demonstrates importance of constant-time implementations
- Shows why authenticated encryption is necessary

Author: Cryptography Lecture
Date: 2024
"""

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import os
import time
from typing import Tuple, Optional


class PaddingOracle:
    """
    A simulated padding oracle that reveals whether padding is valid.
    
    This class simulates a vulnerable server that reveals padding information
    through different error messages or timing differences.
    """
    
    def __init__(self, key: bytes):
        """
        Initialize the padding oracle with a secret key.
        
        Args:
            key (bytes): The secret encryption key
        """
        self.key = key
    
    def decrypt_and_check_padding(self, ciphertext: bytes, iv: bytes) -> Tuple[bool, Optional[bytes]]:
        """
        Decrypt ciphertext and check if padding is valid.
        
        This simulates a vulnerable server that reveals padding information.
        In real attacks, this information might be revealed through:
        - Different error messages
        - Timing differences
        - Different response codes
        
        Args:
            ciphertext (bytes): The ciphertext to decrypt
            iv (bytes): The initialization vector
        
        Returns:
            Tuple[bool, Optional[bytes]]: (is_padding_valid, decrypted_plaintext)
        """
        try:
            # Decrypt the ciphertext
            cipher = AES.new(self.key, AES.MODE_CBC, iv)
            padded_plaintext = cipher.decrypt(ciphertext)
            
            # Try to remove padding
            plaintext = unpad(padded_plaintext, AES.block_size)
            
            return True, plaintext
            
        except ValueError:
            # Padding is invalid
            return False, None
    
    def vulnerable_oracle(self, ciphertext: bytes, iv: bytes) -> bool:
        """
        A vulnerable oracle that only reveals padding validity.
        
        This is the type of oracle that padding oracle attacks exploit.
        
        Args:
            ciphertext (bytes): The ciphertext to check
            iv (bytes): The initialization vector
        
        Returns:
            bool: True if padding is valid, False otherwise
        """
        is_valid, _ = self.decrypt_and_check_padding(ciphertext, iv)
        return is_valid


class PaddingOracleAttacker:
    """
    An attacker that exploits padding oracle vulnerabilities.
    
    This class implements the padding oracle attack algorithm that can
    decrypt ciphertext without knowing the encryption key.
    """
    
    def __init__(self, oracle: PaddingOracle):
        """
        Initialize the attacker with access to a padding oracle.
        
        Args:
            oracle (PaddingOracle): The padding oracle to exploit
        """
        self.oracle = oracle
    
    def attack_block(self, target_block: bytes, previous_block: bytes) -> bytes:
        """
        Attack a single block using padding oracle.
        
        The attack works by:
        1. Creating a modified previous block
        2. Testing different byte values to find valid padding
        3. Using the padding information to recover plaintext
        
        Args:
            target_block (bytes): The block to decrypt
            previous_block (bytes): The previous ciphertext block (or IV)
        
        Returns:
            bytes: The decrypted plaintext block
        """
        block_size = len(target_block)
        plaintext = bytearray(block_size)
        
        # Attack each byte from right to left
        for byte_pos in range(block_size - 1, -1, -1):
            # Create a modified previous block
            modified_previous = bytearray(previous_block)
            
            # Set up the padding for the current position
            padding_length = block_size - byte_pos
            
            # Set the bytes after current position to create valid padding
            for i in range(byte_pos + 1, block_size):
                modified_previous[i] = plaintext[i] ^ padding_length
            
            # Try different values for the current byte
            for byte_value in range(256):
                modified_previous[byte_pos] = byte_value
                
                # Test if this creates valid padding
                if self.oracle.vulnerable_oracle(bytes(modified_previous) + target_block, b'\x00' * 16):
                    # Found the correct byte value
                    plaintext[byte_pos] = byte_value ^ padding_length
                    break
            else:
                # This should not happen in a successful attack
                raise ValueError(f"Could not find valid byte at position {byte_pos}")
        
        return bytes(plaintext)
    
    def attack_ciphertext(self, ciphertext: bytes, iv: bytes) -> bytes:
        """
        Attack a complete ciphertext using padding oracle.
        
        Args:
            ciphertext (bytes): The complete ciphertext
            iv (bytes): The initialization vector
        
        Returns:
            bytes: The decrypted plaintext
        """
        block_size = AES.block_size
        plaintext_blocks = []
        
        # Split ciphertext into blocks
        blocks = [ciphertext[i:i+block_size] for i in range(0, len(ciphertext), block_size)]
        
        # Attack each block
        for i, block in enumerate(blocks):
            if i == 0:
                # First block uses IV
                previous_block = iv
            else:
                # Subsequent blocks use previous ciphertext block
                previous_block = blocks[i-1]
            
            # Attack this block
            plaintext_block = self.attack_block(block, previous_block)
            plaintext_blocks.append(plaintext_block)
        
        # Combine all plaintext blocks
        plaintext = b''.join(plaintext_blocks)
        
        return plaintext


def demonstrate_padding_oracle_attack():
    """
    Demonstrate a padding oracle attack on CBC mode encryption.
    """
    print("=" * 60)
    print("PADDING ORACLE ATTACK DEMONSTRATION")
    print("=" * 60)
    
    # Generate random key and IV
    key = get_random_bytes(16)  # 128-bit key
    iv = get_random_bytes(16)   # 128-bit IV
    
    print(f"Secret key: {key.hex()}")
    print(f"IV: {iv.hex()}")
    
    # Create padding oracle
    oracle = PaddingOracle(key)
    
    # Encrypt a message
    message = b"Secret message that will be attacked"
    print(f"Original message: {message.decode()}")
    
    # Encrypt the message
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_message = pad(message, AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    
    print(f"Ciphertext: {ciphertext.hex()}")
    print(f"Ciphertext length: {len(ciphertext)} bytes")
    
    print("\n" + "-" * 40)
    
    # Perform the attack
    print("Performing padding oracle attack...")
    
    attacker = PaddingOracleAttacker(oracle)
    
    start_time = time.time()
    recovered_plaintext = attacker.attack_ciphertext(ciphertext, iv)
    attack_time = time.time() - start_time
    
    print(f"Attack completed in {attack_time:.2f} seconds")
    print(f"Recovered plaintext: {recovered_plaintext.decode()}")
    print(f"Attack successful: {message == recovered_plaintext}")
    
    print("\n" + "-" * 40)
    
    # Show the attack process for the first block
    print("Attack process for first block:")
    
    first_block = ciphertext[:16]
    print(f"First block: {first_block.hex()}")
    
    # Attack the first block step by step
    block_size = AES.block_size
    plaintext_block = bytearray(block_size)
    
    for byte_pos in range(block_size - 1, -1, -1):
        padding_length = block_size - byte_pos
        print(f"Attacking byte {byte_pos} (padding length {padding_length})")
        
        # Create modified IV
        modified_iv = bytearray(iv)
        
        # Set up padding for bytes after current position
        for i in range(byte_pos + 1, block_size):
            modified_iv[i] = plaintext_block[i] ^ padding_length
        
        # Try different values for current byte
        for byte_value in range(256):
            modified_iv[byte_pos] = byte_value
            
            if oracle.vulnerable_oracle(bytes(modified_iv) + first_block, b'\x00' * 16):
                plaintext_block[byte_pos] = byte_value ^ padding_length
                print(f"  Found byte {byte_pos}: 0x{byte_value:02x} -> 0x{plaintext_block[byte_pos]:02x}")
                break
        else:
            print(f"  Failed to find byte {byte_pos}")
    
    print(f"Recovered first block: {bytes(plaintext_block).decode()}")


def demonstrate_padding_oracle_vulnerabilities():
    """
    Demonstrate different ways padding oracle vulnerabilities can manifest.
    """
    print("\n" + "=" * 60)
    print("PADDING ORACLE VULNERABILITIES")
    print("=" * 60)
    
    print("Common ways padding oracle vulnerabilities manifest:")
    print("-" * 40)
    
    print("1. Different Error Messages:")
    print("   • 'Invalid padding' vs 'Invalid key'")
    print("   • Different HTTP status codes")
    print("   • Different error descriptions")
    
    print("\n2. Timing Differences:")
    print("   • Different processing times for valid/invalid padding")
    print("   • Early termination on padding errors")
    print("   • Different code paths")
    
    print("\n3. Response Differences:")
    print("   • Different response lengths")
    print("   • Different response headers")
    print("   • Different response content")
    
    print("\n4. Side-Channel Information:")
    print("   • Power consumption differences")
    print("   • Electromagnetic emissions")
    print("   • Cache timing differences")
    
    print("\n" + "-" * 40)
    
    # Demonstrate timing differences
    print("Timing Attack Simulation:")
    
    key = get_random_bytes(16)
    oracle = PaddingOracle(key)
    
    # Test with valid padding
    message = b"Valid message"
    cipher = AES.new(key, AES.MODE_CBC, get_random_bytes(16))
    padded_message = pad(message, AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    
    # Time valid padding check
    start_time = time.time()
    for _ in range(1000):
        oracle.vulnerable_oracle(ciphertext, cipher.iv)
    valid_time = time.time() - start_time
    
    # Test with invalid padding
    invalid_ciphertext = get_random_bytes(16)
    
    # Time invalid padding check
    start_time = time.time()
    for _ in range(1000):
        oracle.vulnerable_oracle(invalid_ciphertext, get_random_bytes(16))
    invalid_time = time.time() - start_time
    
    print(f"Valid padding check time: {valid_time:.4f} seconds")
    print(f"Invalid padding check time: {invalid_time:.4f} seconds")
    print(f"Time difference: {abs(valid_time - invalid_time):.4f} seconds")
    
    if abs(valid_time - invalid_time) > 0.001:
        print("WARNING: Timing difference detected!")
    else:
        print("No significant timing difference detected.")


def demonstrate_padding_oracle_prevention():
    """
    Demonstrate how to prevent padding oracle attacks.
    """
    print("\n" + "=" * 60)
    print("PADDING ORACLE ATTACK PREVENTION")
    print("=" * 60)
    
    print("Prevention Strategies:")
    print("-" * 40)
    
    print("1. Use Authenticated Encryption:")
    print("   • GCM mode (AES-GCM)")
    print("   • CCM mode (AES-CCM)")
    print("   • ChaCha20-Poly1305")
    print("   • These modes provide both confidentiality and authenticity")
    
    print("\n2. Constant-Time Implementations:")
    print("   • Always perform the same operations regardless of padding validity")
    print("   • Use constant-time comparison functions")
    print("   • Avoid early termination on errors")
    
    print("\n3. Uniform Error Handling:")
    print("   • Return the same error message for all decryption failures")
    print("   • Use the same response format")
    print("   • Avoid revealing specific error types")
    
    print("\n4. Rate Limiting:")
    print("   • Limit the number of decryption attempts")
    print("   • Implement exponential backoff")
    print("   • Monitor for suspicious patterns")
    
    print("\n" + "-" * 40)
    
    # Demonstrate secure implementation
    print("Secure Implementation Example:")
    
    key = get_random_bytes(16)
    
    def secure_decrypt(ciphertext: bytes, iv: bytes) -> Tuple[bool, Optional[bytes]]:
        """
        Secure decryption that doesn't reveal padding information.
        """
        try:
            cipher = AES.new(key, AES.MODE_CBC, iv)
            padded_plaintext = cipher.decrypt(ciphertext)
            plaintext = unpad(padded_plaintext, AES.block_size)
            return True, plaintext
        except ValueError:
            # Return generic error without revealing specific failure type
            return False, None
    
    # Test secure implementation
    message = b"Secure message"
    cipher = AES.new(key, AES.MODE_CBC, get_random_bytes(16))
    padded_message = pad(message, AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    
    # Valid decryption
    is_valid, decrypted = secure_decrypt(ciphertext, cipher.iv)
    print(f"Valid decryption: {is_valid}")
    print(f"Decrypted message: {decrypted.decode() if decrypted else 'None'}")
    
    # Invalid decryption
    is_valid, decrypted = secure_decrypt(get_random_bytes(16), get_random_bytes(16))
    print(f"Invalid decryption: {is_valid}")
    print(f"Decrypted message: {decrypted.decode() if decrypted else 'None'}")
    
    print("\nNote: Both valid and invalid decryptions return the same error format!")


def demonstrate_authenticated_encryption():
    """
    Demonstrate how authenticated encryption prevents padding oracle attacks.
    """
    print("\n" + "=" * 60)
    print("AUTHENTICATED ENCRYPTION PREVENTION")
    print("=" * 60)
    
    print("Authenticated Encryption Modes:")
    print("-" * 40)
    
    # AES-GCM example
    print("AES-GCM (Galois/Counter Mode):")
    
    key = get_random_bytes(16)
    message = b"Message protected by authenticated encryption"
    
    # Encrypt with GCM
    cipher = AES.new(key, AES.MODE_GCM)
    ciphertext, tag = cipher.encrypt_and_digest(message)
    
    print(f"Message: {message.decode()}")
    print(f"Ciphertext: {ciphertext.hex()}")
    print(f"Authentication tag: {tag.hex()}")
    
    # Decrypt with GCM
    cipher_decrypt = AES.new(key, AES.MODE_GCM, nonce=cipher.nonce)
    try:
        decrypted = cipher_decrypt.decrypt_and_verify(ciphertext, tag)
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except ValueError:
        print("Authentication failed!")
    
    print("\n" + "-" * 40)
    
    # Test tampering
    print("Tampering Test:")
    
    # Tamper with ciphertext
    tampered_ciphertext = bytearray(ciphertext)
    tampered_ciphertext[0] ^= 1  # Flip one bit
    
    try:
        decrypted = cipher_decrypt.decrypt_and_verify(bytes(tampered_ciphertext), tag)
        print(f"Tampered decryption: {decrypted.decode()}")
    except ValueError:
        print("Tampering detected! Authentication failed!")
    
    print("\n" + "-" * 40)
    
    print("Why Authenticated Encryption Prevents Padding Oracle Attacks:")
    print("• Authentication tag verifies ciphertext integrity")
    print("• Invalid ciphertexts are rejected before decryption")
    print("• No padding information is revealed")
    print("• All decryption failures look the same")
    print("• Attacker cannot distinguish between different failure types")


def practical_padding_oracle_examples():
    """
    Show practical examples of padding oracle attacks.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL PADDING ORACLE EXAMPLES")
    print("=" * 60)
    
    print("Real-World Examples:")
    print("-" * 40)
    
    print("1. Web Application Vulnerabilities:")
    print("   • Different error messages for invalid padding vs invalid key")
    print("   • Different HTTP status codes")
    print("   • Different response times")
    
    print("\n2. TLS/SSL Vulnerabilities:")
    print("   • SSL 3.0 POODLE attack")
    print("   • Different error messages in TLS implementations")
    print("   • Timing differences in padding validation")
    
    print("\n3. Database Encryption:")
    print("   • Different error messages for decryption failures")
    print("   • Timing differences in key validation")
    print("   • Different response codes")
    
    print("\n4. File Encryption:")
    print("   • Different error messages for invalid files")
    print("   • Different processing times")
    print("   • Different error codes")
    
    print("\n" + "-" * 40)
    
    # Simulate a vulnerable web application
    print("Vulnerable Web Application Simulation:")
    
    key = get_random_bytes(16)
    oracle = PaddingOracle(key)
    
    def vulnerable_web_app(ciphertext: bytes, iv: bytes) -> str:
        """
        Simulate a vulnerable web application.
        """
        is_valid, plaintext = oracle.decrypt_and_check_padding(ciphertext, iv)
        
        if is_valid:
            return "200 OK - Decryption successful"
        else:
            return "400 Bad Request - Invalid padding"
    
    # Test with valid ciphertext
    message = b"User session data"
    cipher = AES.new(key, AES.MODE_CBC, get_random_bytes(16))
    padded_message = pad(message, AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    
    response = vulnerable_web_app(ciphertext, cipher.iv)
    print(f"Valid ciphertext response: {response}")
    
    # Test with invalid ciphertext
    invalid_ciphertext = get_random_bytes(16)
    response = vulnerable_web_app(invalid_ciphertext, get_random_bytes(16))
    print(f"Invalid ciphertext response: {response}")
    
    print("\nWARNING: This application is vulnerable to padding oracle attacks!")
    print("The different error messages reveal padding information.")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_padding_oracle_attack()
    demonstrate_padding_oracle_vulnerabilities()
    demonstrate_padding_oracle_prevention()
    demonstrate_authenticated_encryption()
    practical_padding_oracle_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("Padding oracle attacks exploit implementation vulnerabilities:")
    print("• Not algorithm weaknesses, but implementation flaws")
    print("• Exploit information leakage about padding validity")
    print("• Can completely break CBC mode encryption")
    print("• Demonstrate importance of constant-time implementations")
    print("\nPrevention strategies:")
    print("• Use authenticated encryption (GCM, CCM, ChaCha20-Poly1305)")
    print("• Implement constant-time padding validation")
    print("• Use uniform error handling")
    print("• Implement rate limiting")
    print("• Monitor for suspicious patterns")
    print("\nPadding oracle attacks show why authenticated encryption is essential!")
