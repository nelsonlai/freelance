"""
Asymmetric Cryptography - Elliptic Curve Cryptography (ECC)

This module demonstrates Elliptic Curve Cryptography (ECC), which provides
the same security as RSA but with much smaller key sizes. ECC is based on
the mathematical properties of elliptic curves over finite fields.

Key Concepts:
- Elliptic Curve: A mathematical curve defined by y² = x³ + ax + b
- ECC: Elliptic Curve Cryptography
- ECDSA: Elliptic Curve Digital Signature Algorithm
- ECDH: Elliptic Curve Diffie-Hellman key exchange
- Curve Parameters: Different curves with different security levels

Security Properties:
- Confidentiality: Only private key holder can decrypt
- Authentication: Digital signatures prove identity
- Key Exchange: Secure distribution of symmetric keys
- Efficiency: Smaller keys than RSA for same security level

Author: Cryptography Lecture
Date: 2024
"""

from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric.utils import encode_dss_signature, decode_dss_signature
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
import os
import secrets
import time
from typing import Tuple, Optional


class ECCCipher:
    """
    A comprehensive ECC implementation supporting digital signatures
    and key exchange using various elliptic curves.
    """
    
    def __init__(self, curve: ec.EllipticCurve = ec.SECP256R1):
        """
        Initialize ECC cipher with a new key pair.
        
        Args:
            curve (ec.EllipticCurve): The elliptic curve to use
        """
        self.curve = curve
        self.private_key = ec.generate_private_key(curve)
        self.public_key = self.private_key.public_key()
    
    def set_key(self, private_key: ec.EllipticPrivateKey):
        """
        Set a specific private key.
        
        Args:
            private_key (ec.EllipticPrivateKey): The private key to use
        """
        self.private_key = private_key
        self.public_key = private_key.public_key()
    
    def sign(self, message: bytes, hash_algorithm: hashes.HashAlgorithm = hashes.SHA256()) -> bytes:
        """
        Sign a message using ECDSA.
        
        Args:
            message (bytes): The message to sign
            hash_algorithm (hashes.HashAlgorithm): Hash algorithm to use
        
        Returns:
            bytes: The digital signature
        """
        signature = self.private_key.sign(message, ec.ECDSA(hash_algorithm))
        return signature
    
    def verify(self, message: bytes, signature: bytes, 
               hash_algorithm: hashes.HashAlgorithm = hashes.SHA256()) -> bool:
        """
        Verify a digital signature.
        
        Args:
            message (bytes): The original message
            signature (bytes): The digital signature
            hash_algorithm (hashes.HashAlgorithm): Hash algorithm used for signing
        
        Returns:
            bool: True if signature is valid, False otherwise
        """
        try:
            self.public_key.verify(signature, message, ec.ECDSA(hash_algorithm))
            return True
        except Exception:
            return False
    
    def get_public_key_bytes(self) -> bytes:
        """
        Get the public key as bytes.
        
        Returns:
            bytes: The public key in DER format
        """
        return self.public_key.public_bytes(
            encoding=serialization.Encoding.DER,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )
    
    def get_private_key_bytes(self) -> bytes:
        """
        Get the private key as bytes.
        
        Returns:
            bytes: The private key in DER format
        """
        return self.private_key.private_bytes(
            encoding=serialization.Encoding.DER,
            format=serialization.PrivateFormat.PKCS8,
            encryption_algorithm=serialization.NoEncryption()
        )
    
    def get_key_info(self) -> dict:
        """
        Get information about the ECC key.
        
        Returns:
            dict: Dictionary containing key information
        """
        return {
            'curve_name': self.curve.name,
            'key_size': self.private_key.key_size,
            'public_key': self.get_public_key_bytes().hex(),
            'private_key': self.get_private_key_bytes().hex()
        }


class ECDHKeyExchange:
    """
    Elliptic Curve Diffie-Hellman key exchange implementation.
    """
    
    def __init__(self, curve: ec.EllipticCurve = ec.SECP256R1):
        """
        Initialize ECDH key exchange.
        
        Args:
            curve (ec.EllipticCurve): The elliptic curve to use
        """
        self.curve = curve
        self.private_key = ec.generate_private_key(curve)
        self.public_key = self.private_key.public_key()
    
    def get_public_key(self) -> ec.EllipticPublicKey:
        """
        Get the public key.
        
        Returns:
            ec.EllipticPublicKey: The public key
        """
        return self.public_key
    
    def get_public_key_bytes(self) -> bytes:
        """
        Get the public key as bytes.
        
        Returns:
            bytes: The public key in DER format
        """
        return self.public_key.public_bytes(
            encoding=serialization.Encoding.DER,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )
    
    def compute_shared_secret(self, peer_public_key: ec.EllipticPublicKey) -> bytes:
        """
        Compute the shared secret with a peer's public key.
        
        Args:
            peer_public_key (ec.EllipticPublicKey): The peer's public key
        
        Returns:
            bytes: The shared secret
        """
        shared_secret = self.private_key.exchange(ec.ECDH(), peer_public_key)
        return shared_secret
    
    def derive_key(self, shared_secret: bytes, salt: Optional[bytes] = None, 
                   info: Optional[bytes] = None) -> bytes:
        """
        Derive a symmetric key from the shared secret.
        
        Args:
            shared_secret (bytes): The shared secret
            salt (bytes, optional): Salt for key derivation
            info (bytes, optional): Additional information
        
        Returns:
            bytes: The derived symmetric key
        """
        hkdf = HKDF(
            algorithm=hashes.SHA256(),
            length=32,  # 256-bit key
            salt=salt,
            info=info
        )
        return hkdf.derive(shared_secret)


def demonstrate_ecc_basic():
    """
    Demonstrate basic ECC digital signatures.
    """
    print("=" * 60)
    print("ELLIPTIC CURVE CRYPTOGRAPHY (ECC) DEMONSTRATION")
    print("=" * 60)
    
    # Create ECC cipher
    ecc = ECCCipher()
    
    print(f"Curve: {ecc.curve.name}")
    print(f"Key size: {ecc.private_key.key_size} bits")
    print(f"Public key: {ecc.get_public_key_bytes().hex()}")
    
    # Test message
    message = b"Important message for ECC signing"
    print(f"\nMessage: {message.decode()}")
    
    # Sign the message
    signature = ecc.sign(message)
    print(f"Signature: {signature.hex()}")
    print(f"Signature length: {len(signature)} bytes")
    
    print("\n" + "-" * 40)
    
    # Verify signature
    print("Signature Verification:")
    is_valid = ecc.verify(message, signature)
    print(f"Valid signature: {is_valid}")
    
    # Test with tampered message
    tampered_message = b"Important message for ECC signing (modified)"
    is_invalid = ecc.verify(tampered_message, signature)
    print(f"Tampered message signature: {is_invalid}")
    
    print("\n" + "-" * 40)
    
    # Test with different hash algorithms
    print("Different Hash Algorithms:")
    
    hash_algorithms = [hashes.SHA1(), hashes.SHA256(), hashes.SHA384(), hashes.SHA512()]
    
    for hash_algo in hash_algorithms:
        signature_hash = ecc.sign(message, hash_algo)
        is_valid_hash = ecc.verify(message, signature_hash, hash_algo)
        print(f"{hash_algo.name}: {is_valid_hash}")


def demonstrate_ecc_curves():
    """
    Demonstrate different elliptic curves and their properties.
    """
    print("\n" + "=" * 60)
    print("ELLIPTIC CURVES DEMONSTRATION")
    print("=" * 60)
    
    # Different elliptic curves
    curves = [
        ec.SECP192R1,  # 192-bit
        ec.SECP224R1,  # 224-bit
        ec.SECP256R1,  # 256-bit (P-256)
        ec.SECP384R1,  # 384-bit (P-384)
        ec.SECP521R1,  # 521-bit (P-521)
    ]
    
    message = b"Test message for curve comparison"
    
    print(f"Message: {message.decode()}")
    print("\nCurve comparison:")
    print("-" * 40)
    
    for curve in curves:
        ecc = ECCCipher(curve)
        
        # Time signing
        start_time = time.time()
        signature = ecc.sign(message)
        signing_time = time.time() - start_time
        
        # Time verification
        start_time = time.time()
        is_valid = ecc.verify(message, signature)
        verification_time = time.time() - start_time
        
        print(f"{curve.name}:")
        print(f"  Key size: {ecc.private_key.key_size} bits")
        print(f"  Signature length: {len(signature)} bytes")
        print(f"  Signing time: {signing_time*1000:.2f} ms")
        print(f"  Verification time: {verification_time*1000:.2f} ms")
        print(f"  Success: {is_valid}")
        print()
    
    print("Curve recommendations:")
    print("• SECP256R1 (P-256): Most widely used, good balance of security and performance")
    print("• SECP384R1 (P-384): Higher security, used in government applications")
    print("• SECP521R1 (P-521): Maximum security, slower performance")
    print("• SECP192R1: Deprecated, insufficient security")
    print("• SECP224R1: Deprecated, insufficient security")


def demonstrate_ecdh_key_exchange():
    """
    Demonstrate Elliptic Curve Diffie-Hellman key exchange.
    """
    print("\n" + "=" * 60)
    print("ELLIPTIC CURVE DIFFIE-HELLMAN (ECDH) DEMONSTRATION")
    print("=" * 60)
    
    # Alice generates her key pair
    alice_ecdh = ECDHKeyExchange()
    print("Alice generated ECDH key pair")
    
    # Bob generates his key pair
    bob_ecdh = ECDHKeyExchange()
    print("Bob generated ECDH key pair")
    
    print(f"Curve: {alice_ecdh.curve.name}")
    print(f"Key size: {alice_ecdh.private_key.key_size} bits")
    
    print("\n" + "-" * 40)
    
    # Exchange public keys
    alice_public = alice_ecdh.get_public_key()
    bob_public = bob_ecdh.get_public_key()
    
    print("Public key exchange:")
    print(f"Alice's public key: {alice_ecdh.get_public_key_bytes().hex()}")
    print(f"Bob's public key: {bob_ecdh.get_public_key_bytes().hex()}")
    
    print("\n" + "-" * 40)
    
    # Compute shared secrets
    alice_shared = alice_ecdh.compute_shared_secret(bob_public)
    bob_shared = bob_ecdh.compute_shared_secret(alice_public)
    
    print("Shared secret computation:")
    print(f"Alice's shared secret: {alice_shared.hex()}")
    print(f"Bob's shared secret: {bob_shared.hex()}")
    print(f"Shared secrets match: {alice_shared == bob_shared}")
    
    print("\n" + "-" * 40)
    
    # Derive symmetric keys
    salt = b"ECDH key derivation salt"
    info = b"ECDH key derivation info"
    
    alice_key = alice_ecdh.derive_key(alice_shared, salt, info)
    bob_key = bob_ecdh.derive_key(bob_shared, salt, info)
    
    print("Symmetric key derivation:")
    print(f"Alice's derived key: {alice_key.hex()}")
    print(f"Bob's derived key: {bob_key.hex()}")
    print(f"Derived keys match: {alice_key == bob_key}")
    
    print("\n" + "-" * 40)
    
    # Use derived keys for symmetric encryption
    print("Using derived keys for symmetric encryption:")
    
    message = b"Secret message encrypted with ECDH-derived key"
    print(f"Message: {message.decode()}")
    
    # Encrypt with Alice's key
    from Crypto.Cipher import AES
    from Crypto.Random import get_random_bytes
    
    iv = get_random_bytes(16)
    cipher = AES.new(alice_key, AES.MODE_CBC, iv)
    padded_message = message + b'\x00' * (16 - len(message) % 16)
    encrypted_message = cipher.encrypt(padded_message)
    
    print(f"Encrypted message: {encrypted_message.hex()}")
    
    # Decrypt with Bob's key
    cipher_bob = AES.new(bob_key, AES.MODE_CBC, iv)
    decrypted_message = cipher_bob.decrypt(encrypted_message)
    decrypted_message = decrypted_message.rstrip(b'\x00')
    
    print(f"Decrypted message: {decrypted_message.decode()}")
    print(f"Decryption successful: {message == decrypted_message}")


def demonstrate_ecc_vs_rsa():
    """
    Compare ECC with RSA in terms of security and performance.
    """
    print("\n" + "=" * 60)
    print("ECC vs RSA COMPARISON")
    print("=" * 60)
    
    message = b"Comparison test message for ECC vs RSA"
    
    # ECC implementation
    ecc = ECCCipher()
    
    start_time = time.time()
    ecc_signature = ecc.sign(message)
    ecc_signing_time = time.time() - start_time
    
    start_time = time.time()
    ecc_valid = ecc.verify(message, ecc_signature)
    ecc_verification_time = time.time() - start_time
    
    print("ECC Implementation:")
    print(f"  Curve: {ecc.curve.name}")
    print(f"  Key size: {ecc.private_key.key_size} bits")
    print(f"  Signature length: {len(ecc_signature)} bytes")
    print(f"  Signing time: {ecc_signing_time*1000:.2f} ms")
    print(f"  Verification time: {ecc_verification_time*1000:.2f} ms")
    print(f"  Success: {ecc_valid}")
    
    print("\n" + "-" * 40)
    
    # RSA implementation
    from Crypto.PublicKey import RSA
    from Crypto.Signature import pkcs1_15
    from Crypto.Hash import SHA256
    
    rsa_key = RSA.generate(2048)
    
    start_time = time.time()
    hash_obj = SHA256.new(message)
    rsa_signature = pkcs1_15.new(rsa_key).sign(hash_obj)
    rsa_signing_time = time.time() - start_time
    
    start_time = time.time()
    hash_obj = SHA256.new(message)
    try:
        pkcs1_15.new(rsa_key.publickey()).verify(hash_obj, rsa_signature)
        rsa_valid = True
    except ValueError:
        rsa_valid = False
    rsa_verification_time = time.time() - start_time
    
    print("RSA Implementation:")
    print(f"  Key size: {rsa_key.size_in_bits()} bits")
    print(f"  Signature length: {len(rsa_signature)} bytes")
    print(f"  Signing time: {rsa_signing_time*1000:.2f} ms")
    print(f"  Verification time: {rsa_verification_time*1000:.2f} ms")
    print(f"  Success: {rsa_valid}")
    
    print("\n" + "-" * 40)
    
    print("Comparison Summary:")
    print("• ECC: Smaller keys, faster operations, same security level")
    print("• RSA: Larger keys, slower operations, widely supported")
    print("• ECC-256 ≈ RSA-3072 in security level")
    print("• ECC: Better for mobile and IoT devices")
    print("• RSA: Better for legacy compatibility")


def demonstrate_ecc_security():
    """
    Demonstrate ECC security considerations.
    """
    print("\n" + "=" * 60)
    print("ECC SECURITY CONSIDERATIONS")
    print("=" * 60)
    
    print("ECC Security Properties:")
    print("✓ Confidentiality: Only private key holder can decrypt")
    print("✓ Authentication: Digital signatures prove identity")
    print("✓ Key Exchange: Secure distribution of symmetric keys")
    print("✓ Efficiency: Smaller keys than RSA for same security level")
    print("✓ Forward Secrecy: ECDH provides forward secrecy")
    
    print("\n" + "-" * 40)
    
    print("ECC Security Limitations:")
    print("✗ Vulnerable to side-channel attacks")
    print("✗ Vulnerable to timing attacks")
    print("✗ Vulnerable to fault injection attacks")
    print("✗ Vulnerable to invalid curve attacks")
    print("✗ Vulnerable to small subgroup attacks")
    
    print("\n" + "-" * 40)
    
    print("Attack Vectors:")
    print("1. Side-Channel Attacks: Use power/electromagnetic analysis")
    print("2. Timing Attacks: Use timing differences in operations")
    print("3. Fault Injection: Inject faults during computation")
    print("4. Invalid Curve Attacks: Use invalid curve points")
    print("5. Small Subgroup Attacks: Use points in small subgroups")
    
    print("\n" + "-" * 40)
    
    print("Mitigation Strategies:")
    print("• Use constant-time implementations")
    print("• Use hardware security modules")
    print("• Validate curve parameters")
    print("• Use secure random number generators")
    print("• Implement proper key management")
    print("• Use established libraries")
    
    print("\n" + "-" * 40)
    
    print("Curve Security Levels:")
    print("• SECP256R1: 128-bit security level")
    print("• SECP384R1: 192-bit security level")
    print("• SECP521R1: 256-bit security level")
    print("• SECP192R1: 96-bit security level (deprecated)")
    print("• SECP224R1: 112-bit security level (deprecated)")


def practical_ecc_examples():
    """
    Show practical examples of ECC usage.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL ECC EXAMPLES")
    print("=" * 60)
    
    # Example 1: Secure messaging
    print("1. Secure Messaging:")
    
    # Alice generates her key pair
    alice_ecc = ECCCipher()
    
    # Bob generates his key pair
    bob_ecc = ECCCipher()
    
    # Alice's message
    message = b"Hello Bob, this is Alice. Let's meet at 3 PM."
    print(f"Alice's message: {message.decode()}")
    
    # Alice signs the message
    alice_signature = alice_ecc.sign(message)
    print(f"Alice's signature: {alice_signature.hex()}")
    
    # Bob verifies Alice's signature
    is_valid_signature = alice_ecc.verify(message, alice_signature)
    print(f"Signature verification: {is_valid_signature}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Secure file transfer
    print("2. Secure File Transfer:")
    
    # File content
    file_content = b"This is sensitive file content that needs to be transferred securely."
    print(f"File content: {file_content.decode()}")
    
    # Alice signs the file
    file_signature = alice_ecc.sign(file_content)
    print(f"File signature: {file_signature.hex()}")
    
    # Bob verifies the file signature
    is_valid_file = alice_ecc.verify(file_content, file_signature)
    print(f"File verification: {is_valid_file}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Key exchange for symmetric encryption
    print("3. Key Exchange for Symmetric Encryption:")
    
    # Alice and Bob perform ECDH key exchange
    alice_ecdh = ECDHKeyExchange()
    bob_ecdh = ECDHKeyExchange()
    
    # Exchange public keys
    alice_public = alice_ecdh.get_public_key()
    bob_public = bob_ecdh.get_public_key()
    
    # Compute shared secrets
    alice_shared = alice_ecdh.compute_shared_secret(bob_public)
    bob_shared = bob_ecdh.compute_shared_secret(alice_public)
    
    # Derive symmetric keys
    alice_key = alice_ecdh.derive_key(alice_shared)
    bob_key = bob_ecdh.derive_key(bob_shared)
    
    print(f"Alice's derived key: {alice_key.hex()}")
    print(f"Bob's derived key: {bob_key.hex()}")
    print(f"Keys match: {alice_key == bob_key}")
    
    # Use keys for symmetric encryption
    from Crypto.Cipher import AES
    from Crypto.Random import get_random_bytes
    
    symmetric_message = b"Message encrypted with ECDH-derived key"
    print(f"Symmetric message: {symmetric_message.decode()}")
    
    # Encrypt with Alice's key
    iv = get_random_bytes(16)
    cipher = AES.new(alice_key, AES.MODE_CBC, iv)
    padded_message = symmetric_message + b'\x00' * (16 - len(symmetric_message) % 16)
    encrypted_symmetric = cipher.encrypt(padded_message)
    
    print(f"Encrypted symmetric message: {encrypted_symmetric.hex()}")
    
    # Decrypt with Bob's key
    cipher_bob = AES.new(bob_key, AES.MODE_CBC, iv)
    decrypted_symmetric = cipher_bob.decrypt(encrypted_symmetric)
    decrypted_symmetric = decrypted_symmetric.rstrip(b'\x00')
    
    print(f"Decrypted symmetric message: {decrypted_symmetric.decode()}")
    print(f"Symmetric encryption successful: {symmetric_message == decrypted_symmetric}")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_ecc_basic()
    demonstrate_ecc_curves()
    demonstrate_ecdh_key_exchange()
    demonstrate_ecc_vs_rsa()
    demonstrate_ecc_security()
    practical_ecc_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("ECC provides efficient public key cryptography:")
    print("• Smaller keys than RSA for same security level")
    print("• Faster operations than RSA")
    print("• Supports digital signatures and key exchange")
    print("• Based on elliptic curve discrete logarithm problem")
    print("\nKey advantages:")
    print("• Efficiency: Smaller keys, faster operations")
    print("• Security: Same security level as RSA with smaller keys")
    print("• Forward Secrecy: ECDH provides forward secrecy")
    print("• Mobile Friendly: Better for resource-constrained devices")
    print("\nUse cases:")
    print("• Digital signatures")
    print("• Key exchange")
    print("• Mobile and IoT applications")
    print("• Blockchain and cryptocurrency")
    print("\nECC is the future of public key cryptography!")
