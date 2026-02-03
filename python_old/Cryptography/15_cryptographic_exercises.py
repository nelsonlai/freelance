"""
Cryptographic Exercises - Practical Implementation

This module provides practical exercises for implementing cryptographic
solutions. These exercises demonstrate real-world applications of
cryptography and help reinforce the concepts learned in the lecture.

Key Concepts:
- File Encryption: Encrypting files with password-based encryption
- Secure Messaging: Implementing secure communication protocols
- Digital Signatures: Signing and verifying documents
- Key Management: Secure key generation and storage
- Hybrid Encryption: Combining symmetric and asymmetric cryptography

Security Properties:
- Confidentiality: Data is protected from unauthorized access
- Integrity: Data cannot be modified without detection
- Authentication: Parties can verify each other's identity
- Non-repudiation: Senders cannot deny sending messages

Author: Cryptography Lecture
Date: 2024
"""

import os
import json
import time
import hashlib
import secrets
from typing import Tuple, Optional, Dict, Any
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256


class FileEncryption:
    """
    A class for encrypting and decrypting files with password-based encryption.
    
    This class demonstrates how to securely encrypt files using a password,
    including proper key derivation, salt generation, and authenticated encryption.
    """
    
    def __init__(self):
        """Initialize the file encryption system."""
        self.salt_size = 32  # 256-bit salt
        self.key_size = 32   # 256-bit key
        self.iv_size = 16    # 128-bit IV
        self.tag_size = 16   # 128-bit authentication tag
    
    def derive_key(self, password: str, salt: bytes, iterations: int = 100000) -> bytes:
        """
        Derive encryption key from password using PBKDF2.
        
        Args:
            password (str): The password
            salt (bytes): The salt
            iterations (int): Number of PBKDF2 iterations
        
        Returns:
            bytes: The derived key
        """
        return hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            iterations
        )
    
    def encrypt_file(self, input_file: str, output_file: str, password: str) -> bool:
        """
        Encrypt a file with password-based encryption.
        
        Args:
            input_file (str): Path to the input file
            output_file (str): Path to the output file
            password (str): The encryption password
        
        Returns:
            bool: True if encryption successful, False otherwise
        """
        try:
            # Generate salt
            salt = get_random_bytes(self.salt_size)
            
            # Derive key from password
            key = self.derive_key(password, salt)
            
            # Read input file
            with open(input_file, 'rb') as f:
                plaintext = f.read()
            
            # Encrypt using AES-GCM
            iv = get_random_bytes(self.iv_size)
            cipher = AES.new(key, AES.MODE_GCM, nonce=iv)
            ciphertext, tag = cipher.encrypt_and_digest(plaintext)
            
            # Write encrypted file
            with open(output_file, 'wb') as f:
                f.write(salt + iv + tag + ciphertext)
            
            return True
            
        except Exception as e:
            print(f"Encryption failed: {e}")
            return False
    
    def decrypt_file(self, input_file: str, output_file: str, password: str) -> bool:
        """
        Decrypt a file with password-based decryption.
        
        Args:
            input_file (str): Path to the encrypted file
            output_file (str): Path to the output file
            password (str): The decryption password
        
        Returns:
            bool: True if decryption successful, False otherwise
        """
        try:
            # Read encrypted file
            with open(input_file, 'rb') as f:
                encrypted_data = f.read()
            
            # Extract components
            salt = encrypted_data[:self.salt_size]
            iv = encrypted_data[self.salt_size:self.salt_size + self.iv_size]
            tag = encrypted_data[self.salt_size + self.iv_size:self.salt_size + self.iv_size + self.tag_size]
            ciphertext = encrypted_data[self.salt_size + self.iv_size + self.tag_size:]
            
            # Derive key from password
            key = self.derive_key(password, salt)
            
            # Decrypt using AES-GCM
            cipher = AES.new(key, AES.MODE_GCM, nonce=iv)
            plaintext = cipher.decrypt_and_verify(ciphertext, tag)
            
            # Write decrypted file
            with open(output_file, 'wb') as f:
                f.write(plaintext)
            
            return True
            
        except Exception as e:
            print(f"Decryption failed: {e}")
            return False


class SecureMessaging:
    """
    A class for implementing secure messaging between two parties.
    
    This class demonstrates how to implement secure communication
    using hybrid encryption (RSA + AES) and digital signatures.
    """
    
    def __init__(self, name: str):
        """
        Initialize the secure messaging system.
        
        Args:
            name (str): The name of the user
        """
        self.name = name
        self.private_key, self.public_key = self._generate_key_pair()
        self.session_key = None
        self.peer_public_key = None
    
    def _generate_key_pair(self) -> Tuple[bytes, bytes]:
        """
        Generate RSA key pair.
        
        Returns:
            Tuple[bytes, bytes]: (private_key, public_key)
        """
        key = RSA.generate(2048)
        private_key = key.export_key()
        public_key = key.publickey().export_key()
        return private_key, public_key
    
    def establish_session(self, peer_public_key: bytes) -> bytes:
        """
        Establish a secure session with a peer.
        
        Args:
            peer_public_key (bytes): The peer's public key
        
        Returns:
            bytes: The encrypted session key
        """
        # Generate session key
        self.session_key = get_random_bytes(32)  # 256-bit key
        self.peer_public_key = peer_public_key
        
        # Encrypt session key with peer's public key
        public_key = RSA.import_key(peer_public_key)
        cipher = PKCS1_OAEP.new(public_key)
        encrypted_session_key = cipher.encrypt(self.session_key)
        
        return encrypted_session_key
    
    def receive_session(self, encrypted_session_key: bytes) -> bool:
        """
        Receive and decrypt the session key from a peer.
        
        Args:
            encrypted_session_key (bytes): The encrypted session key
        
        Returns:
            bool: True if session established successfully
        """
        try:
            # Decrypt session key
            private_key = RSA.import_key(self.private_key)
            cipher = PKCS1_OAEP.new(private_key)
            self.session_key = cipher.decrypt(encrypted_session_key)
            
            return True
            
        except Exception as e:
            print(f"Session establishment failed: {e}")
            return False
    
    def send_message(self, message: str) -> Tuple[bytes, bytes, bytes, bytes]:
        """
        Send a secure message.
        
        Args:
            message (str): The message to send
        
        Returns:
            Tuple[bytes, bytes, bytes, bytes]: (iv, ciphertext, tag, signature)
        """
        if self.session_key is None:
            raise ValueError("Session not established")
        
        # Encrypt message
        iv = get_random_bytes(16)
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=iv)
        ciphertext, tag = cipher.encrypt_and_digest(message.encode('utf-8'))
        
        # Sign message
        signature = self._sign_message(message)
        
        return iv, ciphertext, tag, signature
    
    def receive_message(self, iv: bytes, ciphertext: bytes, tag: bytes, 
                       signature: bytes, sender_public_key: bytes) -> str:
        """
        Receive and decrypt a secure message.
        
        Args:
            iv (bytes): The initialization vector
            ciphertext (bytes): The encrypted message
            tag (bytes): The authentication tag
            signature (bytes): The digital signature
            sender_public_key (bytes): The sender's public key
        
        Returns:
            str: The decrypted message
        
        Raises:
            ValueError: If decryption or verification fails
        """
        if self.session_key is None:
            raise ValueError("Session not established")
        
        # Decrypt message
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=iv)
        plaintext = cipher.decrypt_and_verify(ciphertext, tag)
        message = plaintext.decode('utf-8')
        
        # Verify signature
        if not self._verify_message(message, signature, sender_public_key):
            raise ValueError("Signature verification failed")
        
        return message
    
    def _sign_message(self, message: str) -> bytes:
        """
        Sign a message with the private key.
        
        Args:
            message (str): The message to sign
        
        Returns:
            bytes: The digital signature
        """
        private_key = RSA.import_key(self.private_key)
        hash_obj = SHA256.new(message.encode('utf-8'))
        signature = pkcs1_15.new(private_key).sign(hash_obj)
        return signature
    
    def _verify_message(self, message: str, signature: bytes, 
                       public_key: bytes) -> bool:
        """
        Verify a message signature.
        
        Args:
            message (str): The message
            signature (bytes): The signature
            public_key (bytes): The public key
        
        Returns:
            bool: True if signature is valid
        """
        try:
            public_key_obj = RSA.import_key(public_key)
            hash_obj = SHA256.new(message.encode('utf-8'))
            pkcs1_15.new(public_key_obj).verify(hash_obj, signature)
            return True
        except ValueError:
            return False


class DigitalSignature:
    """
    A class for implementing digital signatures for document authentication.
    
    This class demonstrates how to sign and verify documents using
    RSA digital signatures with SHA-256 hashing.
    """
    
    def __init__(self):
        """Initialize the digital signature system."""
        self.private_key, self.public_key = self._generate_key_pair()
    
    def _generate_key_pair(self) -> Tuple[bytes, bytes]:
        """
        Generate RSA key pair.
        
        Returns:
            Tuple[bytes, bytes]: (private_key, public_key)
        """
        key = RSA.generate(2048)
        private_key = key.export_key()
        public_key = key.publickey().export_key()
        return private_key, public_key
    
    def sign_document(self, document: str) -> bytes:
        """
        Sign a document with the private key.
        
        Args:
            document (str): The document to sign
        
        Returns:
            bytes: The digital signature
        """
        private_key = RSA.import_key(self.private_key)
        hash_obj = SHA256.new(document.encode('utf-8'))
        signature = pkcs1_15.new(private_key).sign(hash_obj)
        return signature
    
    def verify_document(self, document: str, signature: bytes, 
                       public_key: bytes) -> bool:
        """
        Verify a document signature.
        
        Args:
            document (str): The document
            signature (bytes): The signature
            public_key (bytes): The public key
        
        Returns:
            bool: True if signature is valid
        """
        try:
            public_key_obj = RSA.import_key(public_key)
            hash_obj = SHA256.new(document.encode('utf-8'))
            pkcs1_15.new(public_key_obj).verify(hash_obj, signature)
            return True
        except ValueError:
            return False
    
    def create_signed_document(self, document: str) -> Dict[str, Any]:
        """
        Create a signed document with metadata.
        
        Args:
            document (str): The document to sign
        
        Returns:
            Dict[str, Any]: The signed document with metadata
        """
        signature = self.sign_document(document)
        
        return {
            'document': document,
            'signature': signature.hex(),
            'public_key': self.public_key.hex(),
            'timestamp': int(time.time()),
            'hash': hashlib.sha256(document.encode('utf-8')).hexdigest()
        }
    
    def verify_signed_document(self, signed_document: Dict[str, Any]) -> bool:
        """
        Verify a signed document.
        
        Args:
            signed_document (Dict[str, Any]): The signed document
        
        Returns:
            bool: True if signature is valid
        """
        document = signed_document['document']
        signature = bytes.fromhex(signed_document['signature'])
        public_key = bytes.fromhex(signed_document['public_key'])
        
        return self.verify_document(document, signature, public_key)


def exercise_1_file_encryption():
    """
    Exercise 1: File Encryption
    Implement password-based file encryption and decryption.
    """
    print("=" * 60)
    print("EXERCISE 1: FILE ENCRYPTION")
    print("=" * 60)
    
    # Create file encryption system
    file_encryption = FileEncryption()
    
    # Create a sample file
    sample_content = """This is a sensitive document that needs to be encrypted.
It contains confidential information that should not be accessible
to unauthorized parties. The file encryption system will protect
this data using password-based encryption with proper key derivation."""
    
    input_file = "sensitive_document.txt"
    encrypted_file = "sensitive_document.txt.enc"
    decrypted_file = "sensitive_document.txt.dec"
    
    try:
        # Write sample file
        with open(input_file, 'w') as f:
            f.write(sample_content)
        
        print(f"Created sample file: {input_file}")
        print(f"File content:\n{sample_content}")
        
        # Encrypt file
        password = "secure_password_123"
        print(f"\nEncrypting file with password: {password}")
        
        if file_encryption.encrypt_file(input_file, encrypted_file, password):
            print(f"File encrypted successfully: {encrypted_file}")
            
            # Show encrypted file size
            encrypted_size = os.path.getsize(encrypted_file)
            original_size = os.path.getsize(input_file)
            print(f"Original file size: {original_size} bytes")
            print(f"Encrypted file size: {encrypted_size} bytes")
            
            # Decrypt file
            print(f"\nDecrypting file...")
            if file_encryption.decrypt_file(encrypted_file, decrypted_file, password):
                print(f"File decrypted successfully: {decrypted_file}")
                
                # Verify decryption
                with open(decrypted_file, 'r') as f:
                    decrypted_content = f.read()
                
                if decrypted_content == sample_content:
                    print("Decryption verification: SUCCESS")
                else:
                    print("Decryption verification: FAILED")
            else:
                print("Decryption failed!")
        else:
            print("Encryption failed!")
    
    finally:
        # Clean up
        for filename in [input_file, encrypted_file, decrypted_file]:
            if os.path.exists(filename):
                os.remove(filename)
                print(f"Cleaned up: {filename}")


def exercise_2_secure_messaging():
    """
    Exercise 2: Secure Messaging
    Implement secure messaging between two parties.
    """
    print("\n" + "=" * 60)
    print("EXERCISE 2: SECURE MESSAGING")
    print("=" * 60)
    
    # Create two users
    alice = SecureMessaging("Alice")
    bob = SecureMessaging("Bob")
    
    print(f"Alice's public key: {alice.public_key.hex()[:50]}...")
    print(f"Bob's public key: {bob.public_key.hex()[:50]}...")
    
    # Establish secure session
    print("\nEstablishing secure session...")
    
    # Alice establishes session with Bob
    encrypted_session_key = alice.establish_session(bob.public_key)
    print(f"Alice encrypted session key: {encrypted_session_key.hex()}")
    
    # Bob receives session key
    if bob.receive_session(encrypted_session_key):
        print("Bob received session key successfully")
    else:
        print("Bob failed to receive session key")
        return
    
    # Alice sends a message to Bob
    message = "Hello Bob, this is Alice. How are you doing?"
    print(f"\nAlice's message: {message}")
    
    iv, ciphertext, tag, signature = alice.send_message(message)
    print(f"Encrypted message: {ciphertext.hex()}")
    print(f"Digital signature: {signature.hex()}")
    
    # Bob receives and decrypts the message
    try:
        decrypted_message = bob.receive_message(iv, ciphertext, tag, signature, alice.public_key)
        print(f"Bob decrypted message: {decrypted_message}")
        print(f"Message verification: SUCCESS")
    except ValueError as e:
        print(f"Message verification failed: {e}")
        return
    
    # Bob sends a response to Alice
    response = "Hello Alice, I'm doing well! Thanks for asking."
    print(f"\nBob's response: {response}")
    
    iv, ciphertext, tag, signature = bob.send_message(response)
    print(f"Encrypted response: {ciphertext.hex()}")
    print(f"Digital signature: {signature.hex()}")
    
    # Alice receives and decrypts the response
    try:
        decrypted_response = alice.receive_message(iv, ciphertext, tag, signature, bob.public_key)
        print(f"Alice decrypted response: {decrypted_response}")
        print(f"Response verification: SUCCESS")
    except ValueError as e:
        print(f"Response verification failed: {e}")


def exercise_3_digital_signatures():
    """
    Exercise 3: Digital Signatures
    Implement digital signatures for document authentication.
    """
    print("\n" + "=" * 60)
    print("EXERCISE 3: DIGITAL SIGNATURES")
    print("=" * 60)
    
    # Create digital signature system
    signer = DigitalSignature()
    
    # Document to sign
    document = """CONTRACT AGREEMENT
    
This contract is between Alice and Bob for the provision of
cryptographic services. The terms and conditions are as follows:

1. Alice will provide cryptographic consulting services
2. Bob will pay $1000 per hour for these services
3. The contract is valid for one year from the signing date
4. Both parties agree to maintain confidentiality

Signed by: Alice
Date: 2024-01-01"""
    
    print(f"Document to sign:\n{document}")
    
    # Sign the document
    print("\nSigning document...")
    signed_document = signer.create_signed_document(document)
    
    print(f"Document signed successfully!")
    print(f"Signature: {signed_document['signature']}")
    print(f"Timestamp: {signed_document['timestamp']}")
    print(f"Document hash: {signed_document['hash']}")
    
    # Verify the signature
    print("\nVerifying signature...")
    if signer.verify_signed_document(signed_document):
        print("Signature verification: SUCCESS")
    else:
        print("Signature verification: FAILED")
    
    # Test with tampered document
    print("\nTesting with tampered document...")
    tampered_document = signed_document.copy()
    tampered_document['document'] = document.replace("$1000", "$10000")
    
    if signer.verify_signed_document(tampered_document):
        print("Tampered document verification: SUCCESS (UNEXPECTED)")
    else:
        print("Tampered document verification: FAILED (EXPECTED)")
    
    # Test with different signer
    print("\nTesting with different signer...")
    different_signer = DigitalSignature()
    different_signed_document = different_signer.create_signed_document(document)
    
    if signer.verify_signed_document(different_signed_document):
        print("Different signer verification: SUCCESS (UNEXPECTED)")
    else:
        print("Different signer verification: FAILED (EXPECTED)")


def exercise_4_hybrid_encryption():
    """
    Exercise 4: Hybrid Encryption
    Implement hybrid encryption combining RSA and AES.
    """
    print("\n" + "=" * 60)
    print("EXERCISE 4: HYBRID ENCRYPTION")
    print("=" * 60)
    
    # Generate RSA key pair
    rsa_key = RSA.generate(2048)
    private_key = rsa_key.export_key()
    public_key = rsa_key.publickey().export_key()
    
    print("Generated RSA key pair (2048 bits)")
    
    # Message to encrypt
    message = "This is a large message that needs to be encrypted using hybrid encryption."
    print(f"Message to encrypt: {message}")
    print(f"Message length: {len(message)} bytes")
    
    # Generate random AES key
    aes_key = get_random_bytes(32)  # 256-bit key
    print(f"Generated AES key: {aes_key.hex()}")
    
    # Encrypt AES key with RSA
    print("\nEncrypting AES key with RSA...")
    public_key_obj = RSA.import_key(public_key)
    cipher = PKCS1_OAEP.new(public_key_obj)
    encrypted_aes_key = cipher.encrypt(aes_key)
    print(f"Encrypted AES key: {encrypted_aes_key.hex()}")
    
    # Encrypt message with AES
    print("Encrypting message with AES...")
    iv = get_random_bytes(16)
    aes_cipher = AES.new(aes_key, AES.MODE_GCM, nonce=iv)
    ciphertext, tag = aes_cipher.encrypt_and_digest(message.encode('utf-8'))
    print(f"AES ciphertext: {ciphertext.hex()}")
    print(f"Authentication tag: {tag.hex()}")
    
    # Decrypt AES key with RSA
    print("\nDecrypting AES key with RSA...")
    private_key_obj = RSA.import_key(private_key)
    cipher = PKCS1_OAEP.new(private_key_obj)
    decrypted_aes_key = cipher.decrypt(encrypted_aes_key)
    print(f"Decrypted AES key: {decrypted_aes_key.hex()}")
    print(f"AES key recovery: {aes_key == decrypted_aes_key}")
    
    # Decrypt message with AES
    print("Decrypting message with AES...")
    aes_cipher = AES.new(decrypted_aes_key, AES.MODE_GCM, nonce=iv)
    decrypted_message = aes_cipher.decrypt_and_verify(ciphertext, tag)
    decrypted_message = decrypted_message.decode('utf-8')
    print(f"Decrypted message: {decrypted_message}")
    print(f"Message recovery: {message == decrypted_message}")
    
    # Show hybrid encryption benefits
    print("\nHybrid Encryption Benefits:")
    print("• RSA: Secure key exchange")
    print("• AES: Fast bulk encryption")
    print("• GCM: Authenticated encryption")
    print("• Combines best of both worlds")


def exercise_5_key_management():
    """
    Exercise 5: Key Management
    Implement secure key generation and storage.
    """
    print("\n" + "=" * 60)
    print("EXERCISE 5: KEY MANAGEMENT")
    print("=" * 60)
    
    # Generate different types of keys
    print("Generating different types of keys:")
    
    # AES key
    aes_key = get_random_bytes(32)
    print(f"AES-256 key: {aes_key.hex()}")
    
    # RSA key
    rsa_key = RSA.generate(2048)
    print(f"RSA-2048 key size: {rsa_key.size_in_bits()} bits")
    
    # HMAC key
    hmac_key = get_random_bytes(32)
    print(f"HMAC key: {hmac_key.hex()}")
    
    # Salt for key derivation
    salt = get_random_bytes(32)
    print(f"Salt: {salt.hex()}")
    
    print("\n" + "-" * 40)
    
    # Key derivation from password
    print("Key derivation from password:")
    
    password = "my_secure_password"
    iterations = 100000
    
    derived_key = hashlib.pbkdf2_hmac(
        'sha256',
        password.encode('utf-8'),
        salt,
        iterations
    )
    
    print(f"Password: {password}")
    print(f"Salt: {salt.hex()}")
    print(f"Iterations: {iterations}")
    print(f"Derived key: {derived_key.hex()}")
    
    print("\n" + "-" * 40)
    
    # Key storage simulation
    print("Key storage simulation:")
    
    # Simulate key storage with encryption
    master_key = get_random_bytes(32)
    
    def encrypt_key(key: bytes, master_key: bytes) -> Tuple[bytes, bytes]:
        """Encrypt a key with a master key."""
        iv = get_random_bytes(16)
        cipher = AES.new(master_key, AES.MODE_GCM, nonce=iv)
        ciphertext, tag = cipher.encrypt_and_digest(key)
        return iv + tag + ciphertext, iv
    
    def decrypt_key(encrypted_key: bytes, master_key: bytes) -> bytes:
        """Decrypt a key with a master key."""
        iv = encrypted_key[:16]
        tag = encrypted_key[16:32]
        ciphertext = encrypted_key[32:]
        
        cipher = AES.new(master_key, AES.MODE_GCM, nonce=iv)
        return cipher.decrypt_and_verify(ciphertext, tag)
    
    # Encrypt keys
    encrypted_aes_key, _ = encrypt_key(aes_key, master_key)
    encrypted_hmac_key, _ = encrypt_key(hmac_key, master_key)
    
    print(f"Master key: {master_key.hex()}")
    print(f"Encrypted AES key: {encrypted_aes_key.hex()}")
    print(f"Encrypted HMAC key: {encrypted_hmac_key.hex()}")
    
    # Decrypt keys
    decrypted_aes_key = decrypt_key(encrypted_aes_key, master_key)
    decrypted_hmac_key = decrypt_key(encrypted_hmac_key, master_key)
    
    print(f"Decrypted AES key: {decrypted_aes_key.hex()}")
    print(f"Decrypted HMAC key: {decrypted_hmac_key.hex()}")
    print(f"AES key recovery: {aes_key == decrypted_aes_key}")
    print(f"HMAC key recovery: {hmac_key == decrypted_hmac_key}")
    
    print("\n" + "-" * 40)
    
    print("Key Management Best Practices:")
    print("• Use cryptographically secure random number generators")
    print("• Use appropriate key sizes")
    print("• Store keys securely")
    print("• Rotate keys regularly")
    print("• Use key derivation functions")
    print("• Implement proper access controls")


if __name__ == "__main__":
    # Run all exercises
    exercise_1_file_encryption()
    exercise_2_secure_messaging()
    exercise_3_digital_signatures()
    exercise_4_hybrid_encryption()
    exercise_5_key_management()
    
    print("\n" + "=" * 60)
    print("EXERCISE SUMMARY")
    print("=" * 60)
    print("These exercises demonstrate practical cryptographic applications:")
    print("• File encryption with password-based key derivation")
    print("• Secure messaging with hybrid encryption and digital signatures")
    print("• Digital signatures for document authentication")
    print("• Hybrid encryption combining RSA and AES")
    print("• Key management and secure key storage")
    print("\nKey takeaways:")
    print("• Always use established cryptographic libraries")
    print("• Implement proper key management")
    print("• Use authenticated encryption when possible")
    print("• Verify digital signatures")
    print("• Store keys securely")
    print("\nThese exercises provide a foundation for implementing")
    print("secure cryptographic systems in real-world applications!")
