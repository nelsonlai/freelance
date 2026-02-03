"""
Asymmetric Cryptography - RSA Implementation

This module demonstrates RSA (Rivest-Shamir-Adleman) public key cryptography,
which is one of the most widely used asymmetric encryption algorithms. RSA
is based on the mathematical difficulty of factoring large integers.

Key Concepts:
- Public Key Cryptography: Different keys for encryption and decryption
- RSA: Rivest-Shamir-Adleman algorithm
- Key Pairs: Public key (for encryption) and private key (for decryption)
- Digital Signatures: Sign with private key, verify with public key
- Key Exchange: Secure exchange of symmetric keys

Security Properties:
- Confidentiality: Only private key holder can decrypt
- Authentication: Digital signatures prove identity
- Non-repudiation: Cannot deny signing a message
- Key Exchange: Secure distribution of symmetric keys

Author: Cryptography Lecture
Date: 2024
"""

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP, PKCS1_v1_5
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256, SHA1
import os
import secrets
import time
from typing import Tuple, Optional


class RSACipher:
    """
    A comprehensive RSA implementation supporting encryption, decryption,
    and digital signatures with various padding schemes.
    """
    
    def __init__(self, key_size: int = 2048):
        """
        Initialize RSA cipher with a new key pair.
        
        Args:
            key_size (int): Key size in bits (1024, 2048, 3072, 4096)
        """
        if key_size < 1024:
            raise ValueError("Key size must be at least 1024 bits")
        
        self.key_size = key_size
        self.key = RSA.generate(key_size)
        self.private_key = self.key.export_key()
        self.public_key = self.key.publickey().export_key()
    
    def set_key(self, private_key: bytes, public_key: bytes):
        """
        Set specific RSA keys.
        
        Args:
            private_key (bytes): The private key in PEM format
            public_key (bytes): The public key in PEM format
        """
        self.private_key = private_key
        self.public_key = public_key
        self.key = RSA.import_key(private_key)
    
    def encrypt_oaep(self, message: bytes, public_key: Optional[bytes] = None) -> bytes:
        """
        Encrypt message using RSA with OAEP padding.
        
        OAEP (Optimal Asymmetric Encryption Padding) is the recommended
        padding scheme for RSA encryption as it provides better security
        than PKCS#1 v1.5 padding.
        
        Args:
            message (bytes): The message to encrypt
            public_key (bytes, optional): Public key to use. If None, uses own public key
        
        Returns:
            bytes: The encrypted ciphertext
        
        Raises:
            ValueError: If message is too long for the key size
        """
        if public_key is None:
            public_key = self.public_key
        
        # Import the public key
        pub_key = RSA.import_key(public_key)
        
        # Create cipher with OAEP padding
        cipher = PKCS1_OAEP.new(pub_key)
        
        # Encrypt the message
        ciphertext = cipher.encrypt(message)
        
        return ciphertext
    
    def decrypt_oaep(self, ciphertext: bytes, private_key: Optional[bytes] = None) -> bytes:
        """
        Decrypt ciphertext using RSA with OAEP padding.
        
        Args:
            ciphertext (bytes): The encrypted data
            private_key (bytes, optional): Private key to use. If None, uses own private key
        
        Returns:
            bytes: The decrypted plaintext
        
        Raises:
            ValueError: If decryption fails
        """
        if private_key is None:
            private_key = self.private_key
        
        # Import the private key
        priv_key = RSA.import_key(private_key)
        
        # Create cipher with OAEP padding
        cipher = PKCS1_OAEP.new(priv_key)
        
        # Decrypt the ciphertext
        plaintext = cipher.decrypt(ciphertext)
        
        return plaintext
    
    def encrypt_pkcs1(self, message: bytes, public_key: Optional[bytes] = None) -> bytes:
        """
        Encrypt message using RSA with PKCS#1 v1.5 padding.
        
        WARNING: PKCS#1 v1.5 padding is vulnerable to certain attacks
        and should only be used for compatibility reasons. Use OAEP instead.
        
        Args:
            message (bytes): The message to encrypt
            public_key (bytes, optional): Public key to use
        
        Returns:
            bytes: The encrypted ciphertext
        """
        if public_key is None:
            public_key = self.public_key
        
        pub_key = RSA.import_key(public_key)
        cipher = PKCS1_v1_5.new(pub_key)
        ciphertext = cipher.encrypt(message)
        
        return ciphertext
    
    def decrypt_pkcs1(self, ciphertext: bytes, private_key: Optional[bytes] = None) -> bytes:
        """
        Decrypt ciphertext using RSA with PKCS#1 v1.5 padding.
        
        Args:
            ciphertext (bytes): The encrypted data
            private_key (bytes, optional): Private key to use
        
        Returns:
            bytes: The decrypted plaintext
        """
        if private_key is None:
            private_key = self.private_key
        
        priv_key = RSA.import_key(private_key)
        cipher = PKCS1_v1_5.new(priv_key)
        plaintext = cipher.decrypt(ciphertext, None)
        
        if plaintext is None:
            raise ValueError("Decryption failed")
        
        return plaintext
    
    def sign(self, message: bytes, hash_algorithm: str = 'sha256', 
             private_key: Optional[bytes] = None) -> bytes:
        """
        Sign a message using RSA digital signature.
        
        Args:
            message (bytes): The message to sign
            hash_algorithm (str): Hash algorithm to use ('sha1', 'sha256')
            private_key (bytes, optional): Private key to use
        
        Returns:
            bytes: The digital signature
        """
        if private_key is None:
            private_key = self.private_key
        
        priv_key = RSA.import_key(private_key)
        
        # Create hash object
        if hash_algorithm == 'sha256':
            hash_obj = SHA256.new(message)
        elif hash_algorithm == 'sha1':
            hash_obj = SHA1.new(message)
        else:
            raise ValueError(f"Unsupported hash algorithm: {hash_algorithm}")
        
        # Sign the hash
        signature = pkcs1_15.new(priv_key).sign(hash_obj)
        
        return signature
    
    def verify(self, message: bytes, signature: bytes, hash_algorithm: str = 'sha256',
               public_key: Optional[bytes] = None) -> bool:
        """
        Verify a digital signature.
        
        Args:
            message (bytes): The original message
            signature (bytes): The digital signature
            hash_algorithm (str): Hash algorithm used for signing
            public_key (bytes, optional): Public key to use
        
        Returns:
            bool: True if signature is valid, False otherwise
        """
        if public_key is None:
            public_key = self.public_key
        
        pub_key = RSA.import_key(public_key)
        
        # Create hash object
        if hash_algorithm == 'sha256':
            hash_obj = SHA256.new(message)
        elif hash_algorithm == 'sha1':
            hash_obj = SHA1.new(message)
        else:
            raise ValueError(f"Unsupported hash algorithm: {hash_algorithm}")
        
        try:
            pkcs1_15.new(pub_key).verify(hash_obj, signature)
            return True
        except ValueError:
            return False
    
    def get_key_info(self) -> dict:
        """
        Get information about the RSA key.
        
        Returns:
            dict: Dictionary containing key information
        """
        return {
            'key_size': self.key.size_in_bits(),
            'public_exponent': self.key.e,
            'modulus': self.key.n,
            'private_exponent': self.key.d,
            'prime_p': self.key.p,
            'prime_q': self.key.q
        }


def demonstrate_rsa_basic():
    """
    Demonstrate basic RSA encryption and decryption.
    """
    print("=" * 60)
    print("RSA PUBLIC KEY CRYPTOGRAPHY DEMONSTRATION")
    print("=" * 60)
    
    # Create RSA cipher
    rsa = RSACipher(key_size=2048)
    
    print(f"Key size: {rsa.key_size} bits")
    print(f"Public key: {rsa.public_key.decode()[:50]}...")
    print(f"Private key: {rsa.private_key.decode()[:50]}...")
    
    # Test message
    message = b"Secret message for RSA encryption"
    print(f"\nOriginal message: {message.decode()}")
    print(f"Message length: {len(message)} bytes")
    
    print("\n" + "-" * 40)
    
    # Test OAEP encryption
    print("RSA-OAEP Encryption:")
    ciphertext = rsa.encrypt_oaep(message)
    print(f"Ciphertext: {ciphertext.hex()}")
    print(f"Ciphertext length: {len(ciphertext)} bytes")
    
    # Decrypt
    decrypted = rsa.decrypt_oaep(ciphertext)
    print(f"Decrypted: {decrypted.decode()}")
    print(f"Decryption successful: {message == decrypted}")
    
    print("\n" + "-" * 40)
    
    # Test PKCS#1 v1.5 encryption
    print("RSA-PKCS#1 v1.5 Encryption:")
    ciphertext_pkcs1 = rsa.encrypt_pkcs1(message)
    print(f"Ciphertext: {ciphertext_pkcs1.hex()}")
    
    # Decrypt
    decrypted_pkcs1 = rsa.decrypt_pkcs1(ciphertext_pkcs1)
    print(f"Decrypted: {decrypted_pkcs1.decode()}")
    print(f"Decryption successful: {message == decrypted_pkcs1}")


def demonstrate_rsa_digital_signatures():
    """
    Demonstrate RSA digital signatures.
    """
    print("\n" + "=" * 60)
    print("RSA DIGITAL SIGNATURES DEMONSTRATION")
    print("=" * 60)
    
    rsa = RSACipher(key_size=2048)
    
    # Test message
    message = b"Important document to sign"
    print(f"Message: {message.decode()}")
    
    # Sign the message
    signature = rsa.sign(message)
    print(f"Signature: {signature.hex()}")
    print(f"Signature length: {len(signature)} bytes")
    
    print("\n" + "-" * 40)
    
    # Verify signature
    print("Signature Verification:")
    is_valid = rsa.verify(message, signature)
    print(f"Valid signature: {is_valid}")
    
    # Test with tampered message
    tampered_message = b"Important document to sign (modified)"
    is_invalid = rsa.verify(tampered_message, signature)
    print(f"Tampered message signature: {is_invalid}")
    
    print("\n" + "-" * 40)
    
    # Test with different hash algorithms
    print("Different Hash Algorithms:")
    
    hash_algorithms = ['sha1', 'sha256']
    
    for hash_algo in hash_algorithms:
        signature_hash = rsa.sign(message, hash_algo)
        is_valid_hash = rsa.verify(message, signature_hash, hash_algo)
        print(f"{hash_algo.upper()}: {is_valid_hash}")


def demonstrate_rsa_key_exchange():
    """
    Demonstrate RSA key exchange for symmetric encryption.
    """
    print("\n" + "=" * 60)
    print("RSA KEY EXCHANGE DEMONSTRATION")
    print("=" * 60)
    
    # Alice generates RSA key pair
    alice_rsa = RSACipher(key_size=2048)
    print("Alice generated RSA key pair")
    
    # Bob generates RSA key pair
    bob_rsa = RSACipher(key_size=2048)
    print("Bob generated RSA key pair")
    
    # Alice wants to send a message to Bob
    message = b"Secret message from Alice to Bob"
    print(f"\nAlice's message: {message.decode()}")
    
    # Alice encrypts message with Bob's public key
    ciphertext = alice_rsa.encrypt_oaep(message, bob_rsa.public_key)
    print(f"Encrypted with Bob's public key: {ciphertext.hex()}")
    
    # Bob decrypts with his private key
    decrypted_message = bob_rsa.decrypt_oaep(ciphertext)
    print(f"Bob decrypted: {decrypted_message.decode()}")
    print(f"Decryption successful: {message == decrypted_message}")
    
    print("\n" + "-" * 40)
    
    # Demonstrate hybrid encryption (RSA + AES)
    print("Hybrid Encryption (RSA + AES):")
    
    # Generate random AES key
    aes_key = os.urandom(32)  # 256-bit key
    print(f"Generated AES key: {aes_key.hex()}")
    
    # Encrypt AES key with Bob's public key
    encrypted_aes_key = alice_rsa.encrypt_oaep(aes_key, bob_rsa.public_key)
    print(f"Encrypted AES key: {encrypted_aes_key.hex()}")
    
    # Encrypt message with AES (simplified)
    from Crypto.Cipher import AES
    from Crypto.Random import get_random_bytes
    
    iv = get_random_bytes(16)
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    padded_message = message + b'\x00' * (16 - len(message) % 16)  # Simple padding
    encrypted_message = cipher.encrypt(padded_message)
    
    print(f"AES encrypted message: {encrypted_message.hex()}")
    
    # Bob's side: decrypt AES key and message
    decrypted_aes_key = bob_rsa.decrypt_oaep(encrypted_aes_key)
    print(f"Bob decrypted AES key: {decrypted_aes_key.hex()}")
    
    cipher_bob = AES.new(decrypted_aes_key, AES.MODE_CBC, iv)
    decrypted_message_bob = cipher_bob.decrypt(encrypted_message)
    decrypted_message_bob = decrypted_message_bob.rstrip(b'\x00')  # Remove padding
    
    print(f"Bob decrypted message: {decrypted_message_bob.decode()}")
    print(f"Hybrid encryption successful: {message == decrypted_message_bob}")


def demonstrate_rsa_key_sizes():
    """
    Demonstrate different RSA key sizes and their security implications.
    """
    print("\n" + "=" * 60)
    print("RSA KEY SIZES DEMONSTRATION")
    print("=" * 60)
    
    message = b"Test message for key size comparison"
    
    key_sizes = [1024, 2048, 3072, 4096]
    
    print(f"Message: {message.decode()}")
    print(f"Message length: {len(message)} bytes")
    
    print("\nKey size comparison:")
    print("-" * 40)
    
    for key_size in key_sizes:
        rsa = RSACipher(key_size=key_size)
        
        # Time encryption
        start_time = time.time()
        ciphertext = rsa.encrypt_oaep(message)
        encryption_time = time.time() - start_time
        
        # Time decryption
        start_time = time.time()
        decrypted = rsa.decrypt_oaep(ciphertext)
        decryption_time = time.time() - start_time
        
        # Time signing
        start_time = time.time()
        signature = rsa.sign(message)
        signing_time = time.time() - start_time
        
        # Time verification
        start_time = time.time()
        is_valid = rsa.verify(message, signature)
        verification_time = time.time() - start_time
        
        print(f"RSA-{key_size}:")
        print(f"  Encryption: {encryption_time*1000:.2f} ms")
        print(f"  Decryption: {decryption_time*1000:.2f} ms")
        print(f"  Signing: {signing_time*1000:.2f} ms")
        print(f"  Verification: {verification_time*1000:.2f} ms")
        print(f"  Success: {message == decrypted and is_valid}")
        print()
    
    print("Security recommendations:")
    print("• RSA-1024: Deprecated, vulnerable to factorization")
    print("• RSA-2048: Minimum recommended size")
    print("• RSA-3072: Good for high-security applications")
    print("• RSA-4096: Maximum security, slower performance")


def demonstrate_rsa_limitations():
    """
    Demonstrate RSA limitations and message size constraints.
    """
    print("\n" + "=" * 60)
    print("RSA LIMITATIONS DEMONSTRATION")
    print("=" * 60)
    
    rsa = RSACipher(key_size=2048)
    
    print("RSA Message Size Limitations:")
    print("-" * 40)
    
    # Calculate maximum message size for different padding schemes
    key_size_bytes = rsa.key_size // 8
    
    # OAEP padding overhead
    oaep_overhead = 2 * 32 + 2  # 2 * hash_size + 2
    max_oaep_message = key_size_bytes - oaep_overhead
    
    # PKCS#1 v1.5 padding overhead
    pkcs1_overhead = 11  # 11 bytes overhead
    max_pkcs1_message = key_size_bytes - pkcs1_overhead
    
    print(f"Key size: {rsa.key_size} bits ({key_size_bytes} bytes)")
    print(f"OAEP max message: {max_oaep_message} bytes")
    print(f"PKCS#1 v1.5 max message: {max_pkcs1_message} bytes")
    
    print("\n" + "-" * 40)
    
    # Test with different message sizes
    test_messages = [
        b"A",  # 1 byte
        b"Hello World!",  # 12 bytes
        b"A" * 100,  # 100 bytes
        b"A" * 200,  # 200 bytes
    ]
    
    print("Testing different message sizes:")
    
    for message in test_messages:
        print(f"\nMessage length: {len(message)} bytes")
        
        if len(message) <= max_oaep_message:
            try:
                ciphertext = rsa.encrypt_oaep(message)
                decrypted = rsa.decrypt_oaep(ciphertext)
                print(f"OAEP: SUCCESS - {message == decrypted}")
            except Exception as e:
                print(f"OAEP: FAILED - {type(e).__name__}")
        else:
            print("OAEP: FAILED - Message too long")
        
        if len(message) <= max_pkcs1_message:
            try:
                ciphertext = rsa.encrypt_pkcs1(message)
                decrypted = rsa.decrypt_pkcs1(ciphertext)
                print(f"PKCS#1: SUCCESS - {message == decrypted}")
            except Exception as e:
                print(f"PKCS#1: FAILED - {type(e).__name__}")
        else:
            print("PKCS#1: FAILED - Message too long")
    
    print("\n" + "-" * 40)
    
    print("Solutions for large messages:")
    print("• Use hybrid encryption (RSA + AES)")
    print("• Use RSA for key exchange only")
    print("• Use RSA for digital signatures")
    print("• Use RSA for small messages only")


def demonstrate_rsa_security():
    """
    Demonstrate RSA security considerations.
    """
    print("\n" + "=" * 60)
    print("RSA SECURITY CONSIDERATIONS")
    print("=" * 60)
    
    print("RSA Security Properties:")
    print("✓ Confidentiality: Only private key holder can decrypt")
    print("✓ Authentication: Digital signatures prove identity")
    print("✓ Non-repudiation: Cannot deny signing a message")
    print("✓ Key Exchange: Secure distribution of symmetric keys")
    
    print("\n" + "-" * 40)
    
    print("RSA Security Limitations:")
    print("✗ Slow performance for large messages")
    print("✗ Message size limitations")
    print("✗ Vulnerable to timing attacks")
    print("✗ Vulnerable to side-channel attacks")
    print("✗ Vulnerable to factorization attacks (with small keys)")
    
    print("\n" + "-" * 40)
    
    print("Attack Vectors:")
    print("1. Factorization Attacks: Factor the modulus n = p * q")
    print("2. Timing Attacks: Use timing differences in decryption")
    print("3. Side-Channel Attacks: Use power/electromagnetic analysis")
    print("4. Chosen Ciphertext Attacks: Exploit padding vulnerabilities")
    print("5. Key Recovery Attacks: Recover private key from public key")
    
    print("\n" + "-" * 40)
    
    print("Mitigation Strategies:")
    print("• Use large key sizes (2048+ bits)")
    print("• Use OAEP padding instead of PKCS#1 v1.5")
    print("• Use constant-time implementations")
    print("• Use hardware security modules")
    print("• Use hybrid encryption for large messages")
    print("• Implement proper key management")
    
    print("\n" + "-" * 40)
    
    print("Best Practices:")
    print("• Generate keys securely")
    print("• Use appropriate key sizes")
    print("• Use OAEP padding")
    print("• Implement proper key storage")
    print("• Use hybrid encryption")
    print("• Regular key rotation")
    print("• Use established libraries")


def practical_rsa_examples():
    """
    Show practical examples of RSA usage.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL RSA EXAMPLES")
    print("=" * 60)
    
    # Example 1: Secure file transfer
    print("1. Secure File Transfer:")
    
    # Sender (Alice)
    alice_rsa = RSACipher(key_size=2048)
    
    # Receiver (Bob)
    bob_rsa = RSACipher(key_size=2048)
    
    # File content
    file_content = b"This is sensitive file content that needs to be transferred securely."
    print(f"File content: {file_content.decode()}")
    
    # Encrypt file with Bob's public key
    encrypted_file = alice_rsa.encrypt_oaep(file_content, bob_rsa.public_key)
    print(f"Encrypted file: {encrypted_file.hex()}")
    
    # Bob decrypts the file
    decrypted_file = bob_rsa.decrypt_oaep(encrypted_file)
    print(f"Decrypted file: {decrypted_file.decode()}")
    print(f"Transfer successful: {file_content == decrypted_file}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Digital contract signing
    print("2. Digital Contract Signing:")
    
    # Contract content
    contract = b"Contract: Alice agrees to pay Bob $1000 for services rendered."
    print(f"Contract: {contract.decode()}")
    
    # Alice signs the contract
    alice_signature = alice_rsa.sign(contract)
    print(f"Alice's signature: {alice_signature.hex()}")
    
    # Verify Alice's signature
    is_valid_signature = alice_rsa.verify(contract, alice_signature)
    print(f"Signature valid: {is_valid_signature}")
    
    # Test with tampered contract
    tampered_contract = b"Contract: Alice agrees to pay Bob $10000 for services rendered."
    is_valid_tampered = alice_rsa.verify(tampered_contract, alice_signature)
    print(f"Tampered contract signature: {is_valid_tampered}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Secure communication protocol
    print("3. Secure Communication Protocol:")
    
    # Alice wants to send a message to Bob
    message = b"Hello Bob, this is Alice. Let's meet at 3 PM."
    print(f"Alice's message: {message.decode()}")
    
    # Alice signs the message
    message_signature = alice_rsa.sign(message)
    
    # Alice encrypts the message with Bob's public key
    encrypted_message = alice_rsa.encrypt_oaep(message, bob_rsa.public_key)
    
    # Alice encrypts the signature with Bob's public key
    encrypted_signature = alice_rsa.encrypt_oaep(message_signature, bob_rsa.public_key)
    
    print(f"Encrypted message: {encrypted_message.hex()}")
    print(f"Encrypted signature: {encrypted_signature.hex()}")
    
    # Bob receives and processes the message
    # Bob decrypts the message
    decrypted_message = bob_rsa.decrypt_oaep(encrypted_message)
    print(f"Bob decrypted message: {decrypted_message.decode()}")
    
    # Bob decrypts the signature
    decrypted_signature = bob_rsa.decrypt_oaep(encrypted_signature)
    
    # Bob verifies Alice's signature
    is_valid_message = alice_rsa.verify(decrypted_message, decrypted_signature)
    print(f"Message authenticity verified: {is_valid_message}")
    
    print(f"Communication successful: {message == decrypted_message and is_valid_message}")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_rsa_basic()
    demonstrate_rsa_digital_signatures()
    demonstrate_rsa_key_exchange()
    demonstrate_rsa_key_sizes()
    demonstrate_rsa_limitations()
    demonstrate_rsa_security()
    practical_rsa_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("RSA is a fundamental public key cryptography algorithm:")
    print("• Provides confidentiality, authentication, and non-repudiation")
    print("• Based on the difficulty of factoring large integers")
    print("• Supports encryption, decryption, and digital signatures")
    print("• Widely used for key exchange and digital signatures")
    print("\nKey characteristics:")
    print("• Asymmetric: Different keys for encryption and decryption")
    print("• Slow: Not suitable for large messages")
    print("• Secure: Resistant to known attacks with proper implementation")
    print("• Versatile: Supports multiple cryptographic operations")
    print("\nBest practices:")
    print("• Use large key sizes (2048+ bits)")
    print("• Use OAEP padding for encryption")
    print("• Use hybrid encryption for large messages")
    print("• Implement proper key management")
    print("• Use established libraries and implementations")
    print("\nRSA is essential for modern cryptographic systems!")
