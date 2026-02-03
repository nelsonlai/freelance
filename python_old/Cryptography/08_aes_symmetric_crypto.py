"""
Symmetric Cryptography - AES Implementation

This module demonstrates the Advanced Encryption Standard (AES), which is
the most widely used symmetric encryption algorithm. AES is a block cipher
that operates on 128-bit blocks and supports key sizes of 128, 192, and 256 bits.

Key Concepts:
- Block Cipher: Encrypts fixed-size blocks of data
- AES: Advanced Encryption Standard (Rijndael algorithm)
- Modes of Operation: Different ways to apply block ciphers to larger data
- Initialization Vector (IV): Random data used to ensure uniqueness
- Padding: Adding data to make input fit block size

Security Properties:
- Confidentiality: Keeps data secret
- Integrity: Detects tampering (with authenticated modes)
- Authentication: Verifies data origin (with authenticated modes)

Author: Cryptography Lecture
Date: 2024
"""

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import os
import secrets
import time
from typing import Tuple, Optional


class AESCipher:
    """
    A comprehensive AES encryption class supporting multiple modes of operation.
    
    This class provides methods for encrypting and decrypting data using AES
    with various modes including ECB, CBC, and GCM. It handles key generation,
    IV/nonce management, and padding automatically.
    """
    
    def __init__(self, key_size: int = 32):
        """
        Initialize the AES cipher with a random key.
        
        Args:
            key_size (int): Key size in bytes (16, 24, or 32 for AES-128, AES-192, AES-256)
        """
        if key_size not in [16, 24, 32]:
            raise ValueError("Key size must be 16, 24, or 32 bytes")
        
        self.key_size = key_size
        self.key = get_random_bytes(key_size)
        self.block_size = AES.block_size  # 16 bytes (128 bits)
    
    def set_key(self, key: bytes):
        """
        Set a specific key for the cipher.
        
        Args:
            key (bytes): The encryption key
        """
        if len(key) != self.key_size:
            raise ValueError(f"Key must be {self.key_size} bytes long")
        self.key = key
    
    def encrypt_ecb(self, plaintext: bytes) -> bytes:
        """
        Encrypt using Electronic Codebook (ECB) mode.
        
        WARNING: ECB mode is insecure and should not be used for real applications!
        It reveals patterns in the plaintext.
        
        Args:
            plaintext (bytes): The data to encrypt
        
        Returns:
            bytes: The encrypted ciphertext
        """
        # Pad the plaintext to block size
        padded_plaintext = pad(plaintext, self.block_size)
        
        # Create cipher in ECB mode
        cipher = AES.new(self.key, AES.MODE_ECB)
        
        # Encrypt the padded plaintext
        ciphertext = cipher.encrypt(padded_plaintext)
        
        return ciphertext
    
    def decrypt_ecb(self, ciphertext: bytes) -> bytes:
        """
        Decrypt using Electronic Codebook (ECB) mode.
        
        Args:
            ciphertext (bytes): The encrypted data
        
        Returns:
            bytes: The decrypted plaintext
        """
        # Create cipher in ECB mode
        cipher = AES.new(self.key, AES.MODE_ECB)
        
        # Decrypt the ciphertext
        padded_plaintext = cipher.decrypt(ciphertext)
        
        # Remove padding
        plaintext = unpad(padded_plaintext, self.block_size)
        
        return plaintext
    
    def encrypt_cbc(self, plaintext: bytes, iv: Optional[bytes] = None) -> Tuple[bytes, bytes]:
        """
        Encrypt using Cipher Block Chaining (CBC) mode.
        
        CBC mode provides better security than ECB by chaining blocks together.
        Each block is XORed with the previous ciphertext block before encryption.
        
        Args:
            plaintext (bytes): The data to encrypt
            iv (bytes, optional): Initialization Vector. If None, generates random IV
        
        Returns:
            Tuple[bytes, bytes]: (iv, ciphertext) tuple
        """
        # Generate random IV if not provided
        if iv is None:
            iv = get_random_bytes(self.block_size)
        
        # Pad the plaintext to block size
        padded_plaintext = pad(plaintext, self.block_size)
        
        # Create cipher in CBC mode
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        
        # Encrypt the padded plaintext
        ciphertext = cipher.encrypt(padded_plaintext)
        
        return iv, ciphertext
    
    def decrypt_cbc(self, iv: bytes, ciphertext: bytes) -> bytes:
        """
        Decrypt using Cipher Block Chaining (CBC) mode.
        
        Args:
            iv (bytes): The initialization vector used during encryption
            ciphertext (bytes): The encrypted data
        
        Returns:
            bytes: The decrypted plaintext
        """
        # Create cipher in CBC mode
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        
        # Decrypt the ciphertext
        padded_plaintext = cipher.decrypt(ciphertext)
        
        # Remove padding
        plaintext = unpad(padded_plaintext, self.block_size)
        
        return plaintext
    
    def encrypt_gcm(self, plaintext: bytes, nonce: Optional[bytes] = None) -> Tuple[bytes, bytes, bytes]:
        """
        Encrypt using Galois/Counter Mode (GCM).
        
        GCM is an authenticated encryption mode that provides both confidentiality
        and authenticity. It's widely used in modern applications.
        
        Args:
            plaintext (bytes): The data to encrypt
            nonce (bytes, optional): Nonce (IV). If None, generates random nonce
        
        Returns:
            Tuple[bytes, bytes, bytes]: (nonce, ciphertext, authentication_tag) tuple
        """
        # Generate random nonce if not provided
        if nonce is None:
            nonce = get_random_bytes(12)  # 96-bit nonce is recommended for GCM
        
        # Create cipher in GCM mode
        cipher = AES.new(self.key, AES.MODE_GCM, nonce=nonce)
        
        # Encrypt and authenticate
        ciphertext, tag = cipher.encrypt_and_digest(plaintext)
        
        return nonce, ciphertext, tag
    
    def decrypt_gcm(self, nonce: bytes, ciphertext: bytes, tag: bytes) -> bytes:
        """
        Decrypt using Galois/Counter Mode (GCM).
        
        Args:
            nonce (bytes): The nonce used during encryption
            ciphertext (bytes): The encrypted data
            tag (bytes): The authentication tag
        
        Returns:
            bytes: The decrypted plaintext
        
        Raises:
            ValueError: If authentication fails
        """
        # Create cipher in GCM mode
        cipher = AES.new(self.key, AES.MODE_GCM, nonce=nonce)
        
        # Decrypt and verify authentication
        plaintext = cipher.decrypt_and_verify(ciphertext, tag)
        
        return plaintext


def demonstrate_aes_basic():
    """
    Demonstrate basic AES encryption and decryption.
    """
    print("=" * 60)
    print("AES (ADVANCED ENCRYPTION STANDARD) DEMONSTRATION")
    print("=" * 60)
    
    # Create AES cipher
    aes = AESCipher(key_size=32)  # AES-256
    
    print(f"Key size: {aes.key_size * 8} bits (AES-256)")
    print(f"Block size: {aes.block_size * 8} bits")
    print(f"Key: {aes.key.hex()}")
    
    # Test message
    message = b"This is a secret message that needs to be encrypted."
    print(f"\nOriginal message: {message.decode()}")
    print(f"Message length: {len(message)} bytes")
    
    print("\n" + "-" * 40)
    
    # Test CBC mode
    print("CBC Mode Encryption:")
    iv, ciphertext = aes.encrypt_cbc(message)
    
    print(f"IV: {iv.hex()}")
    print(f"Ciphertext: {ciphertext.hex()}")
    print(f"Ciphertext length: {len(ciphertext)} bytes")
    
    # Decrypt
    decrypted = aes.decrypt_cbc(iv, ciphertext)
    print(f"Decrypted: {decrypted.decode()}")
    print(f"Decryption successful: {message == decrypted}")
    
    print("\n" + "-" * 40)
    
    # Test GCM mode
    print("GCM Mode Encryption:")
    nonce, ciphertext_gcm, tag = aes.encrypt_gcm(message)
    
    print(f"Nonce: {nonce.hex()}")
    print(f"Ciphertext: {ciphertext_gcm.hex()}")
    print(f"Authentication tag: {tag.hex()}")
    
    # Decrypt
    decrypted_gcm = aes.decrypt_gcm(nonce, ciphertext_gcm, tag)
    print(f"Decrypted: {decrypted_gcm.decode()}")
    print(f"Decryption successful: {message == decrypted_gcm}")


def demonstrate_aes_modes():
    """
    Demonstrate different AES modes of operation.
    """
    print("\n" + "=" * 60)
    print("AES MODES OF OPERATION DEMONSTRATION")
    print("=" * 60)
    
    aes = AESCipher(key_size=32)
    
    # Test data with patterns (to show ECB weakness)
    test_data = b"AAAAAAAAAAAAAAAA" + b"BBBBBBBBBBBBBBBB"  # 32 bytes with clear pattern
    
    print(f"Test data: {test_data.hex()}")
    print(f"Test data (ASCII): {test_data}")
    
    print("\n" + "-" * 40)
    
    # ECB Mode (INSECURE - shows patterns)
    print("ECB Mode (INSECURE - shows patterns):")
    ecb_ciphertext = aes.encrypt_ecb(test_data)
    print(f"ECB Ciphertext: {ecb_ciphertext.hex()}")
    print("Notice the repeating pattern!")
    
    # Decrypt ECB
    ecb_decrypted = aes.decrypt_ecb(ecb_ciphertext)
    print(f"ECB Decrypted: {ecb_decrypted}")
    print(f"ECB successful: {test_data == ecb_decrypted}")
    
    print("\n" + "-" * 40)
    
    # CBC Mode (secure)
    print("CBC Mode (secure):")
    iv, cbc_ciphertext = aes.encrypt_cbc(test_data)
    print(f"IV: {iv.hex()}")
    print(f"CBC Ciphertext: {cbc_ciphertext.hex()}")
    print("No repeating patterns!")
    
    # Decrypt CBC
    cbc_decrypted = aes.decrypt_cbc(iv, cbc_ciphertext)
    print(f"CBC Decrypted: {cbc_decrypted}")
    print(f"CBC successful: {test_data == cbc_decrypted}")
    
    print("\n" + "-" * 40)
    
    # GCM Mode (authenticated encryption)
    print("GCM Mode (authenticated encryption):")
    nonce, gcm_ciphertext, tag = aes.encrypt_gcm(test_data)
    print(f"Nonce: {nonce.hex()}")
    print(f"GCM Ciphertext: {gcm_ciphertext.hex()}")
    print(f"Authentication tag: {tag.hex()}")
    
    # Decrypt GCM
    gcm_decrypted = aes.decrypt_gcm(nonce, gcm_ciphertext, tag)
    print(f"GCM Decrypted: {gcm_decrypted}")
    print(f"GCM successful: {test_data == gcm_decrypted}")


def demonstrate_iv_importance():
    """
    Demonstrate why IVs/nonces are important for security.
    """
    print("\n" + "=" * 60)
    print("IV/NONCE IMPORTANCE DEMONSTRATION")
    print("=" * 60)
    
    aes = AESCipher(key_size=32)
    
    # Same message encrypted multiple times
    message = b"Secret message"
    
    print(f"Message: {message.decode()}")
    print("\nEncrypting same message multiple times:")
    
    # Encrypt with different IVs
    for i in range(3):
        iv, ciphertext = aes.encrypt_cbc(message)
        print(f"Encryption {i+1}: IV={iv.hex()[:16]}..., Ciphertext={ciphertext.hex()[:16]}...")
    
    print("\nNotice: Same message produces different ciphertexts!")
    print("This prevents pattern analysis attacks.")
    
    print("\n" + "-" * 40)
    
    # Demonstrate what happens with reused IV
    print("Danger of reusing IV:")
    
    # Encrypt two messages with same IV
    iv_reused = get_random_bytes(16)
    
    message1 = b"First message"
    message2 = b"Second message"
    
    _, ciphertext1 = aes.encrypt_cbc(message1, iv_reused)
    _, ciphertext2 = aes.encrypt_cbc(message2, iv_reused)
    
    print(f"Message 1: {message1.decode()}")
    print(f"Ciphertext 1: {ciphertext1.hex()}")
    print(f"Message 2: {message2.decode()}")
    print(f"Ciphertext 2: {ciphertext2.hex()}")
    
    print("\nWARNING: Reusing IVs can leak information!")
    print("Always use unique IVs/nonces for each encryption!")


def demonstrate_authentication():
    """
    Demonstrate authentication in GCM mode.
    """
    print("\n" + "=" * 60)
    print("AUTHENTICATION IN GCM MODE DEMONSTRATION")
    print("=" * 60)
    
    aes = AESCipher(key_size=32)
    
    message = b"Important authenticated message"
    print(f"Original message: {message.decode()}")
    
    # Encrypt with GCM
    nonce, ciphertext, tag = aes.encrypt_gcm(message)
    print(f"Nonce: {nonce.hex()}")
    print(f"Ciphertext: {ciphertext.hex()}")
    print(f"Authentication tag: {tag.hex()}")
    
    print("\n" + "-" * 40)
    
    # Test 1: Valid decryption
    print("Test 1: Valid decryption")
    try:
        decrypted = aes.decrypt_gcm(nonce, ciphertext, tag)
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except ValueError as e:
        print(f"Authentication failed: {e}")
    
    print("\n" + "-" * 40)
    
    # Test 2: Tampered ciphertext
    print("Test 2: Tampered ciphertext")
    tampered_ciphertext = bytearray(ciphertext)
    tampered_ciphertext[0] ^= 1  # Flip one bit
    
    try:
        decrypted = aes.decrypt_gcm(nonce, bytes(tampered_ciphertext), tag)
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except ValueError as e:
        print(f"Authentication failed: {e}")
        print("Tampering detected!")
    
    print("\n" + "-" * 40)
    
    # Test 3: Tampered tag
    print("Test 3: Tampered authentication tag")
    tampered_tag = bytearray(tag)
    tampered_tag[0] ^= 1  # Flip one bit
    
    try:
        decrypted = aes.decrypt_gcm(nonce, ciphertext, bytes(tampered_tag))
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except ValueError as e:
        print(f"Authentication failed: {e}")
        print("Tag tampering detected!")


def demonstrate_key_sizes():
    """
    Demonstrate different AES key sizes and their security implications.
    """
    print("\n" + "=" * 60)
    print("AES KEY SIZES DEMONSTRATION")
    print("=" * 60)
    
    message = b"Test message for key size comparison"
    
    key_sizes = [
        (16, "AES-128"),
        (24, "AES-192"),
        (32, "AES-256")
    ]
    
    print(f"Message: {message.decode()}")
    print(f"Message length: {len(message)} bytes")
    
    print("\nKey size comparison:")
    print("-" * 40)
    
    for key_size, name in key_sizes:
        aes = AESCipher(key_size=key_size)
        
        # Time encryption
        start_time = time.time()
        iv, ciphertext = aes.encrypt_cbc(message)
        encryption_time = time.time() - start_time
        
        # Time decryption
        start_time = time.time()
        decrypted = aes.decrypt_cbc(iv, ciphertext)
        decryption_time = time.time() - start_time
        
        print(f"{name}:")
        print(f"  Key size: {key_size * 8} bits")
        print(f"  Key: {aes.key.hex()}")
        print(f"  Encryption time: {encryption_time*1000:.3f} ms")
        print(f"  Decryption time: {decryption_time*1000:.3f} ms")
        print(f"  Success: {message == decrypted}")
        print()
    
    print("Security recommendations:")
    print("• AES-128: Sufficient for most applications")
    print("• AES-192: Good for high-security applications")
    print("• AES-256: Maximum security, required for some government applications")
    print("• All AES variants are secure against known attacks")


def demonstrate_padding():
    """
    Demonstrate padding in block ciphers.
    """
    print("\n" + "=" * 60)
    print("PADDING DEMONSTRATION")
    print("=" * 60)
    
    aes = AESCipher(key_size=32)
    
    # Test different message lengths
    test_messages = [
        b"A",                    # 1 byte
        b"Hello",               # 5 bytes
        b"Hello World!",        # 12 bytes
        b"Hello World!123",     # 15 bytes
        b"Hello World!1234",    # 16 bytes (exactly one block)
        b"Hello World!12345",   # 17 bytes
    ]
    
    print("Padding demonstration:")
    print("-" * 40)
    
    for message in test_messages:
        print(f"Original: {message.decode()} ({len(message)} bytes)")
        
        # Show padding
        padded = pad(message, aes.block_size)
        print(f"Padded:   {padded.hex()} ({len(padded)} bytes)")
        
        # Encrypt and decrypt
        iv, ciphertext = aes.encrypt_cbc(message)
        decrypted = aes.decrypt_cbc(iv, ciphertext)
        
        print(f"Decrypted: {decrypted.decode()} ({len(decrypted)} bytes)")
        print(f"Success: {message == decrypted}")
        print()


def performance_analysis():
    """
    Analyze AES performance with different modes and key sizes.
    """
    print("\n" + "=" * 60)
    print("AES PERFORMANCE ANALYSIS")
    print("=" * 60)
    
    # Test data
    test_data = b"Performance test data for AES analysis" * 100  # ~4KB
    
    print(f"Test data size: {len(test_data)} bytes")
    print("\nPerformance Results:")
    print("-" * 40)
    
    # Test different modes
    modes = [
        ("ECB", "encrypt_ecb", "decrypt_ecb"),
        ("CBC", "encrypt_cbc", "decrypt_cbc"),
        ("GCM", "encrypt_gcm", "decrypt_gcm")
    ]
    
    for mode_name, encrypt_method, decrypt_method in modes:
        aes = AESCipher(key_size=32)
        
        # Time encryption
        start_time = time.time()
        iterations = 100
        
        for _ in range(iterations):
            if mode_name == "ECB":
                ciphertext = getattr(aes, encrypt_method)(test_data)
            elif mode_name == "CBC":
                iv, ciphertext = getattr(aes, encrypt_method)(test_data)
            elif mode_name == "GCM":
                nonce, ciphertext, tag = getattr(aes, encrypt_method)(test_data)
        
        encryption_time = time.time() - start_time
        avg_encryption_time = encryption_time / iterations
        
        # Time decryption
        start_time = time.time()
        
        for _ in range(iterations):
            if mode_name == "ECB":
                getattr(aes, decrypt_method)(ciphertext)
            elif mode_name == "CBC":
                getattr(aes, decrypt_method)(iv, ciphertext)
            elif mode_name == "GCM":
                getattr(aes, decrypt_method)(nonce, ciphertext, tag)
        
        decryption_time = time.time() - start_time
        avg_decryption_time = decryption_time / iterations
        
        # Calculate throughput
        encryption_throughput = len(test_data) / avg_encryption_time / (1024 * 1024)  # MB/s
        decryption_throughput = len(test_data) / avg_decryption_time / (1024 * 1024)  # MB/s
        
        print(f"{mode_name:<4}: Encrypt {avg_encryption_time*1000:6.2f} ms, "
              f"{encryption_throughput:6.1f} MB/s | "
              f"Decrypt {avg_decryption_time*1000:6.2f} ms, {decryption_throughput:6.1f} MB/s")


def security_considerations():
    """
    Discuss security considerations for AES usage.
    """
    print("\n" + "=" * 60)
    print("AES SECURITY CONSIDERATIONS")
    print("=" * 60)
    
    print("Security Properties:")
    print("✓ Confidentiality: Keeps data secret")
    print("✓ Integrity: Detects tampering (with authenticated modes)")
    print("✓ Authentication: Verifies data origin (with authenticated modes)")
    print("✓ Resistance to known attacks")
    
    print("\nMode Recommendations:")
    print("✓ GCM: Best choice for most applications (authenticated encryption)")
    print("✓ CBC: Good for legacy compatibility (requires separate MAC)")
    print("✗ ECB: Never use (reveals patterns)")
    
    print("\nKey Management:")
    print("• Use cryptographically secure random number generators")
    print("• Use appropriate key sizes (128+ bits)")
    print("• Store keys securely")
    print("• Rotate keys regularly")
    print("• Never hardcode keys in source code")
    
    print("\nIV/Nonce Management:")
    print("• Always use unique IVs/nonces")
    print("• Use cryptographically secure random number generators")
    print("• Never reuse IVs/nonces")
    print("• Use appropriate nonce sizes (96 bits for GCM)")
    
    print("\nCommon Pitfalls:")
    print("• Reusing IVs/nonces")
    print("• Using ECB mode")
    print("• Weak key generation")
    print("• Poor key storage")
    print("• Not using authenticated encryption")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_aes_basic()
    demonstrate_aes_modes()
    demonstrate_iv_importance()
    demonstrate_authentication()
    demonstrate_key_sizes()
    demonstrate_padding()
    performance_analysis()
    security_considerations()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("AES is the gold standard for symmetric encryption:")
    print("• Block cipher operating on 128-bit blocks")
    print("• Supports 128, 192, and 256-bit keys")
    print("• Multiple modes of operation (GCM recommended)")
    print("• Provides confidentiality and integrity")
    print("\nBest practices:")
    print("• Use GCM mode for authenticated encryption")
    print("• Always use unique IVs/nonces")
    print("• Use strong, randomly generated keys")
    print("• Never use ECB mode")
    print("• Implement proper key management")
    print("\nAES is secure against all known practical attacks!")
