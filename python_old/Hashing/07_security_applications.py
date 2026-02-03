"""
Cybersecurity Applications of Hashing
=====================================

This file demonstrates how hashing is used in cybersecurity applications:
- Password hashing and verification
- Digital signatures and integrity checking
- Malware detection using file hashes
- Blockchain and cryptocurrency concepts
- Secure hash functions and salt usage
- Hash-based authentication systems

These applications show how hashing provides security, integrity,
and authentication in modern cybersecurity systems.

Author: Hash Lecture Series
Purpose: Educational demonstration of hashing in cybersecurity
"""

import hashlib
import secrets
import time
import os
from typing import Optional, Tuple, Dict, List


class SecurePasswordManager:
    """
    Secure password management using cryptographic hash functions.
    
    This class demonstrates proper password hashing techniques including:
    - Salt generation and usage
    - Key derivation functions (PBKDF2)
    - Secure password verification
    - Protection against rainbow table attacks
    
    Security Features:
    - Salt prevents rainbow table attacks
    - PBKDF2 prevents brute force attacks
    - High iteration count slows down attacks
    """
    
    def __init__(self, iterations: int = 100000):
        """
        Initialize the secure password manager.
        
        Args:
            iterations: Number of iterations for PBKDF2 (higher = more secure but slower)
        """
        self.iterations = iterations
        self.users = {}  # In practice, this would be a database
    
    def _generate_salt(self, length: int = 32) -> str:
        """
        Generate a cryptographically secure random salt.
        
        Args:
            length: Length of salt in bytes
            
        Returns:
            Hexadecimal string representation of the salt
        """
        return secrets.token_hex(length)
    
    def hash_password(self, password: str, salt: Optional[str] = None) -> Tuple[str, str]:
        """
        Hash a password using PBKDF2 with salt.
        
        PBKDF2 (Password-Based Key Derivation Function 2) is designed to be
        computationally expensive to prevent brute force attacks.
        
        Args:
            password: Plain text password to hash
            salt: Optional salt (will be generated if not provided)
            
        Returns:
            Tuple of (salt, hashed_password)
        """
        if salt is None:
            salt = self._generate_salt()
        
        # Convert password and salt to bytes
        password_bytes = password.encode('utf-8')
        salt_bytes = salt.encode('utf-8')
        
        # Use PBKDF2 with SHA-256
        key = hashlib.pbkdf2_hmac('sha256', password_bytes, salt_bytes, self.iterations)
        
        # Convert to hexadecimal string
        hashed_password = key.hex()
        
        return salt, hashed_password
    
    def verify_password(self, password: str, salt: str, hashed_password: str) -> bool:
        """
        Verify a password against its hash.
        
        Args:
            password: Plain text password to verify
            salt: Salt used in original hashing
            hashed_password: Stored hash to verify against
            
        Returns:
            True if password is correct, False otherwise
        """
        _, computed_hash = self.hash_password(password, salt)
        return computed_hash == hashed_password
    
    def register_user(self, username: str, password: str) -> bool:
        """
        Register a new user with hashed password.
        
        Args:
            username: Username
            password: Plain text password
            
        Returns:
            True if registration successful, False if user already exists
        """
        if username in self.users:
            return False
        
        salt, hashed_password = self.hash_password(password)
        
        self.users[username] = {
            'salt': salt,
            'hashed_password': hashed_password,
            'iterations': self.iterations,
            'created_at': time.time()
        }
        
        return True
    
    def authenticate_user(self, username: str, password: str) -> bool:
        """
        Authenticate a user with username and password.
        
        Args:
            username: Username
            password: Plain text password
            
        Returns:
            True if authentication successful, False otherwise
        """
        if username not in self.users:
            return False
        
        user_data = self.users[username]
        return self.verify_password(password, user_data['salt'], user_data['hashed_password'])
    
    def change_password(self, username: str, old_password: str, new_password: str) -> bool:
        """
        Change a user's password.
        
        Args:
            username: Username
            old_password: Current password
            new_password: New password
            
        Returns:
            True if password changed successfully, False otherwise
        """
        if not self.authenticate_user(username, old_password):
            return False
        
        # Generate new hash for new password
        salt, hashed_password = self.hash_password(new_password)
        
        self.users[username]['salt'] = salt
        self.users[username]['hashed_password'] = hashed_password
        self.users[username]['updated_at'] = time.time()
        
        return True
    
    def get_user_info(self, username: str) -> Optional[Dict]:
        """
        Get user information (excluding sensitive data).
        
        Args:
            username: Username
            
        Returns:
            User info dictionary or None if user doesn't exist
        """
        if username not in self.users:
            return None
        
        user_data = self.users[username]
        return {
            'username': username,
            'created_at': user_data['created_at'],
            'updated_at': user_data.get('updated_at', user_data['created_at']),
            'iterations': user_data['iterations']
        }


class FileIntegrityChecker:
    """
    File integrity checking using cryptographic hash functions.
    
    This class demonstrates how to use hashes to verify file integrity:
    - Calculate file hashes
    - Store and verify file checksums
    - Detect file tampering
    - Malware detection using known bad hashes
    
    Applications:
    - Software distribution verification
    - Malware detection
    - Backup integrity checking
    - Digital forensics
    """
    
    def __init__(self):
        """
        Initialize the file integrity checker.
        """
        self.known_hashes = {}  # filename -> hash
        self.malware_hashes = set()  # Known malicious file hashes
    
    def calculate_file_hash(self, filepath: str, algorithm: str = 'sha256') -> str:
        """
        Calculate the hash of a file.
        
        Args:
            filepath: Path to the file
            algorithm: Hash algorithm to use ('md5', 'sha1', 'sha256', 'sha512')
            
        Returns:
            Hexadecimal string representation of the file hash
        """
        hash_obj = hashlib.new(algorithm)
        
        try:
            with open(filepath, 'rb') as file:
                # Read file in chunks to handle large files efficiently
                for chunk in iter(lambda: file.read(4096), b""):
                    hash_obj.update(chunk)
            
            return hash_obj.hexdigest()
        
        except FileNotFoundError:
            raise FileNotFoundError(f"File not found: {filepath}")
        except Exception as e:
            raise Exception(f"Error reading file {filepath}: {e}")
    
    def store_file_hash(self, filepath: str, algorithm: str = 'sha256') -> str:
        """
        Calculate and store the hash of a file.
        
        Args:
            filepath: Path to the file
            algorithm: Hash algorithm to use
            
        Returns:
            The calculated hash
        """
        file_hash = self.calculate_file_hash(filepath, algorithm)
        self.known_hashes[filepath] = {
            'hash': file_hash,
            'algorithm': algorithm,
            'timestamp': time.time()
        }
        return file_hash
    
    def verify_file_integrity(self, filepath: str) -> Tuple[bool, Optional[str]]:
        """
        Verify the integrity of a file by comparing with stored hash.
        
        Args:
            filepath: Path to the file to verify
            
        Returns:
            Tuple of (is_integrity_ok, current_hash)
        """
        if filepath not in self.known_hashes:
            return False, None
        
        stored_hash_info = self.known_hashes[filepath]
        current_hash = self.calculate_file_hash(filepath, stored_hash_info['algorithm'])
        
        is_integrity_ok = current_hash == stored_hash_info['hash']
        
        return is_integrity_ok, current_hash
    
    def add_malware_hash(self, file_hash: str) -> None:
        """
        Add a known malicious file hash to the database.
        
        Args:
            file_hash: Hash of the malicious file
        """
        self.malware_hashes.add(file_hash.lower())
    
    def is_malware(self, filepath: str) -> Tuple[bool, str]:
        """
        Check if a file is known malware by comparing its hash.
        
        Args:
            filepath: Path to the file to check
            
        Returns:
            Tuple of (is_malware, file_hash)
        """
        file_hash = self.calculate_file_hash(filepath)
        is_malicious = file_hash.lower() in self.malware_hashes
        
        return is_malicious, file_hash
    
    def scan_directory(self, directory: str, recursive: bool = True) -> Dict[str, Dict]:
        """
        Scan a directory for files and calculate their hashes.
        
        Args:
            directory: Directory to scan
            recursive: Whether to scan subdirectories
            
        Returns:
            Dictionary of filepath -> hash information
        """
        results = {}
        
        if recursive:
            for root, dirs, files in os.walk(directory):
                for file in files:
                    filepath = os.path.join(root, file)
                    try:
                        file_hash = self.calculate_file_hash(filepath)
                        results[filepath] = {
                            'hash': file_hash,
                            'size': os.path.getsize(filepath),
                            'timestamp': time.time()
                        }
                    except Exception as e:
                        results[filepath] = {'error': str(e)}
        else:
            try:
                for item in os.listdir(directory):
                    itempath = os.path.join(directory, item)
                    if os.path.isfile(itempath):
                        try:
                            file_hash = self.calculate_file_hash(itempath)
                            results[itempath] = {
                                'hash': file_hash,
                                'size': os.path.getsize(itempath),
                                'timestamp': time.time()
                            }
                        except Exception as e:
                            results[itempath] = {'error': str(e)}
            except Exception as e:
                print(f"Error scanning directory {directory}: {e}")
        
        return results


class DigitalSignature:
    """
    Simplified digital signature implementation using hash functions.
    
    This demonstrates the concept of digital signatures:
    - Message hashing
    - Signature generation (simplified)
    - Signature verification
    - Integrity and authenticity checking
    
    Note: This is a simplified implementation for educational purposes.
    Real digital signatures use asymmetric cryptography (RSA, ECDSA, etc.).
    """
    
    def __init__(self, private_key: str = None):
        """
        Initialize the digital signature system.
        
        Args:
            private_key: Private key for signing (simplified as a string)
        """
        self.private_key = private_key or secrets.token_hex(32)
        self.public_key = self._derive_public_key()
    
    def _derive_public_key(self) -> str:
        """
        Derive public key from private key (simplified).
        
        In real implementations, this would use elliptic curve cryptography
        or RSA key generation.
        
        Returns:
            Public key (simplified as a string)
        """
        return hashlib.sha256(self.private_key.encode()).hexdigest()
    
    def _sign_message(self, message: str) -> str:
        """
        Create a digital signature for a message (simplified).
        
        Args:
            message: Message to sign
            
        Returns:
            Digital signature (simplified)
        """
        # In real implementations, this would use the private key to sign
        # the hash of the message using RSA or ECDSA
        
        # Create message hash
        message_hash = hashlib.sha256(message.encode()).hexdigest()
        
        # Simulate signing by combining private key with message hash
        signature_data = f"{self.private_key}{message_hash}"
        signature = hashlib.sha256(signature_data.encode()).hexdigest()
        
        return signature
    
    def sign(self, message: str) -> Dict[str, str]:
        """
        Sign a message and return signature information.
        
        Args:
            message: Message to sign
            
        Returns:
            Dictionary containing signature information
        """
        signature = self._sign_message(message)
        message_hash = hashlib.sha256(message.encode()).hexdigest()
        
        return {
            'message': message,
            'message_hash': message_hash,
            'signature': signature,
            'public_key': self.public_key,
            'timestamp': time.time()
        }
    
    def verify(self, message: str, signature: str, public_key: str) -> bool:
        """
        Verify a digital signature.
        
        Args:
            message: Original message
            signature: Signature to verify
            public_key: Public key of the signer
            
        Returns:
            True if signature is valid, False otherwise
        """
        # Recreate the signature
        expected_signature = self._sign_message(message)
        
        # In a real implementation, we would use the public key to verify
        # the signature against the message hash
        
        return signature == expected_signature


class BlockchainSimulator:
    """
    Simplified blockchain simulation using hash functions.
    
    This demonstrates how hashing is used in blockchain technology:
    - Block creation and chaining
    - Proof of work (simplified)
    - Hash-based integrity
    - Merkle tree concepts
    
    Note: This is a simplified educational implementation.
    Real blockchains are much more complex.
    """
    
    def __init__(self):
        """
        Initialize the blockchain simulator.
        """
        self.chain = []
        self.current_transactions = []
        self.difficulty = 4  # Number of leading zeros required
    
    def _calculate_hash(self, data: str) -> str:
        """
        Calculate SHA-256 hash of data.
        
        Args:
            data: Data to hash
            
        Returns:
            Hash value
        """
        return hashlib.sha256(data.encode()).hexdigest()
    
    def _proof_of_work(self, block_data: str) -> Tuple[int, str]:
        """
        Simple proof of work algorithm.
        
        Args:
            block_data: Data to find proof of work for
            
        Returns:
            Tuple of (nonce, hash)
        """
        nonce = 0
        target = "0" * self.difficulty
        
        while True:
            data_with_nonce = f"{block_data}{nonce}"
            hash_value = self._calculate_hash(data_with_nonce)
            
            if hash_value.startswith(target):
                return nonce, hash_value
            
            nonce += 1
    
    def create_block(self, previous_hash: str = None) -> Dict:
        """
        Create a new block in the blockchain.
        
        Args:
            previous_hash: Hash of the previous block
            
        Returns:
            Block dictionary
        """
        if previous_hash is None and self.chain:
            previous_hash = self.chain[-1]['hash']
        elif previous_hash is None:
            previous_hash = "0" * 64  # Genesis block
        
        block_data = {
            'index': len(self.chain) + 1,
            'timestamp': time.time(),
            'transactions': self.current_transactions.copy(),
            'previous_hash': previous_hash,
            'nonce': 0
        }
        
        # Find proof of work
        block_string = f"{block_data['index']}{block_data['timestamp']}{block_data['transactions']}{block_data['previous_hash']}"
        nonce, hash_value = self._proof_of_work(block_string)
        
        block_data['nonce'] = nonce
        block_data['hash'] = hash_value
        
        # Add block to chain
        self.chain.append(block_data)
        
        # Clear current transactions
        self.current_transactions = []
        
        return block_data
    
    def add_transaction(self, sender: str, recipient: str, amount: float) -> int:
        """
        Add a transaction to the current block.
        
        Args:
            sender: Transaction sender
            recipient: Transaction recipient
            amount: Transaction amount
            
        Returns:
            Index of the transaction
        """
        transaction = {
            'sender': sender,
            'recipient': recipient,
            'amount': amount,
            'timestamp': time.time()
        }
        
        self.current_transactions.append(transaction)
        return len(self.current_transactions)
    
    def validate_chain(self) -> bool:
        """
        Validate the entire blockchain.
        
        Returns:
            True if chain is valid, False otherwise
        """
        for i in range(1, len(self.chain)):
            current_block = self.chain[i]
            previous_block = self.chain[i - 1]
            
            # Check if current block's previous_hash matches previous block's hash
            if current_block['previous_hash'] != previous_block['hash']:
                return False
            
            # Verify proof of work
            block_string = f"{current_block['index']}{current_block['timestamp']}{current_block['transactions']}{current_block['previous_hash']}"
            expected_hash = self._calculate_hash(f"{block_string}{current_block['nonce']}")
            
            if not expected_hash.startswith("0" * self.difficulty):
                return False
        
        return True
    
    def get_chain_info(self) -> Dict:
        """
        Get blockchain information.
        
        Returns:
            Dictionary with chain statistics
        """
        return {
            'length': len(self.chain),
            'difficulty': self.difficulty,
            'total_transactions': sum(len(block['transactions']) for block in self.chain),
            'last_block_hash': self.chain[-1]['hash'] if self.chain else None,
            'is_valid': self.validate_chain()
        }


def demonstrate_password_security():
    """
    Demonstrate secure password hashing and verification.
    """
    print("=== Password Security Demonstration ===\n")
    
    # Create password manager
    password_manager = SecurePasswordManager(iterations=10000)  # Reduced for demo
    
    # Register users
    users = [
        ("alice", "password123"),
        ("bob", "mypassword"),
        ("charlie", "secretpass")
    ]
    
    print("Registering users:")
    for username, password in users:
        success = password_manager.register_user(username, password)
        print(f"  {username}: {'✓ Registered' if success else '✗ Failed'}")
    
    # Show user info (without sensitive data)
    print(f"\nUser information:")
    for username, _ in users:
        info = password_manager.get_user_info(username)
        if info:
            print(f"  {username}: Created at {info['created_at']:.0f}")
    
    # Test authentication
    print(f"\nTesting authentication:")
    test_credentials = [
        ("alice", "password123", True),
        ("alice", "wrongpass", False),
        ("bob", "mypassword", True),
        ("nonexistent", "anypass", False)
    ]
    
    for username, password, expected in test_credentials:
        result = password_manager.authenticate_user(username, password)
        status = "✓ Correct" if result == expected else "✗ Unexpected"
        print(f"  {username}/{password}: {result} {status}")
    
    # Test password change
    print(f"\nTesting password change:")
    success = password_manager.change_password("alice", "password123", "newpassword")
    print(f"  Password change: {'✓ Success' if success else '✗ Failed'}")
    
    # Verify new password
    old_auth = password_manager.authenticate_user("alice", "password123")
    new_auth = password_manager.authenticate_user("alice", "newpassword")
    print(f"  Old password works: {old_auth}")
    print(f"  New password works: {new_auth}")


def demonstrate_file_integrity():
    """
    Demonstrate file integrity checking.
    """
    print("\n=== File Integrity Checking Demonstration ===\n")
    
    integrity_checker = FileIntegrityChecker()
    
    # Create a test file
    test_file = "test_file.txt"
    with open(test_file, 'w') as f:
        f.write("This is a test file for integrity checking.")
    
    try:
        # Calculate and store file hash
        print("Calculating file hash:")
        file_hash = integrity_checker.store_file_hash(test_file)
        print(f"  File: {test_file}")
        print(f"  Hash: {file_hash}")
        
        # Verify file integrity
        print(f"\nVerifying file integrity:")
        is_ok, current_hash = integrity_checker.verify_file_integrity(test_file)
        print(f"  Integrity check: {'✓ OK' if is_ok else '✗ FAILED'}")
        print(f"  Current hash: {current_hash}")
        
        # Tamper with the file
        print(f"\nTampering with file...")
        with open(test_file, 'a') as f:
            f.write(" TAMPERED!")
        
        # Verify integrity again
        print(f"Verifying integrity after tampering:")
        is_ok, current_hash = integrity_checker.verify_file_integrity(test_file)
        print(f"  Integrity check: {'✓ OK' if is_ok else '✗ FAILED'}")
        print(f"  Current hash: {current_hash}")
        
        # Add some malware hashes
        print(f"\nAdding malware hashes to database:")
        malware_hashes = [
            "a1b2c3d4e5f6789012345678901234567890abcdef1234567890abcdef123456",
            "f6e5d4c3b2a1987654321098765432109876543210fedcba0987654321fedcba"
        ]
        
        for malware_hash in malware_hashes:
            integrity_checker.add_malware_hash(malware_hash)
            print(f"  Added malware hash: {malware_hash[:16]}...")
        
        # Check if our test file is malware
        print(f"\nChecking if test file is malware:")
        is_malware, file_hash = integrity_checker.is_malware(test_file)
        print(f"  Is malware: {'✓ YES' if is_malware else '✗ NO'}")
        print(f"  File hash: {file_hash}")
    
    finally:
        # Clean up test file
        if os.path.exists(test_file):
            os.remove(test_file)


def demonstrate_digital_signatures():
    """
    Demonstrate digital signature creation and verification.
    """
    print("\n=== Digital Signature Demonstration ===\n")
    
    # Create signer
    signer = DigitalSignature()
    
    # Messages to sign
    messages = [
        "Hello, this is a test message.",
        "Transfer $1000 to account 12345",
        "I agree to the terms and conditions."
    ]
    
    print("Creating digital signatures:")
    signatures = []
    
    for message in messages:
        signature_info = signer.sign(message)
        signatures.append(signature_info)
        
        print(f"  Message: {message}")
        print(f"  Signature: {signature_info['signature'][:16]}...")
        print(f"  Public Key: {signature_info['public_key'][:16]}...")
        print()
    
    # Verify signatures
    print("Verifying digital signatures:")
    for i, (message, signature_info) in enumerate(zip(messages, signatures)):
        is_valid = signer.verify(message, signature_info['signature'], signature_info['public_key'])
        print(f"  Message {i+1}: {'✓ Valid' if is_valid else '✗ Invalid'}")
    
    # Test tampered message
    print(f"\nTesting tampered message:")
    tampered_message = "Transfer $10000 to account 12345"  # Changed amount
    original_signature = signatures[1]['signature']  # Use signature from second message
    is_valid = signer.verify(tampered_message, original_signature, signatures[1]['public_key'])
    print(f"  Tampered message: {'✓ Valid' if is_valid else '✗ Invalid (as expected)'}")


def demonstrate_blockchain():
    """
    Demonstrate simplified blockchain using hashing.
    """
    print("\n=== Blockchain Demonstration ===\n")
    
    # Create blockchain
    blockchain = BlockchainSimulator()
    
    # Add some transactions
    print("Adding transactions:")
    blockchain.add_transaction("Alice", "Bob", 50.0)
    blockchain.add_transaction("Bob", "Charlie", 25.0)
    blockchain.add_transaction("Charlie", "Alice", 10.0)
    
    print("  Added 3 transactions")
    
    # Create first block (genesis block)
    print(f"\nCreating genesis block...")
    genesis_block = blockchain.create_block()
    print(f"  Block #{genesis_block['index']} created")
    print(f"  Hash: {genesis_block['hash']}")
    print(f"  Nonce: {genesis_block['nonce']}")
    print(f"  Transactions: {len(genesis_block['transactions'])}")
    
    # Add more transactions
    blockchain.add_transaction("Alice", "David", 30.0)
    blockchain.add_transaction("David", "Bob", 15.0)
    
    # Create second block
    print(f"\nCreating second block...")
    second_block = blockchain.create_block()
    print(f"  Block #{second_block['index']} created")
    print(f"  Hash: {second_block['hash']}")
    print(f"  Nonce: {second_block['nonce']}")
    print(f"  Transactions: {len(second_block['transactions'])}")
    
    # Validate blockchain
    print(f"\nValidating blockchain:")
    is_valid = blockchain.validate_chain()
    print(f"  Blockchain valid: {'✓ YES' if is_valid else '✗ NO'}")
    
    # Show chain info
    chain_info = blockchain.get_chain_info()
    print(f"\nBlockchain information:")
    print(f"  Length: {chain_info['length']}")
    print(f"  Total transactions: {chain_info['total_transactions']}")
    print(f"  Difficulty: {chain_info['difficulty']}")
    print(f"  Last block hash: {chain_info['last_block_hash'][:16]}...")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will demonstrate:
    1. Secure password hashing and verification
    2. File integrity checking and malware detection
    3. Digital signature creation and verification
    4. Simplified blockchain implementation
    """
    
    # Run all demonstrations
    demonstrate_password_security()
    demonstrate_file_integrity()
    demonstrate_digital_signatures()
    demonstrate_blockchain()
    
    print("\n" + "="*70)
    print("EDUCATIONAL NOTES:")
    print("="*70)
    print("1. Password Security:")
    print("   - Always use salt to prevent rainbow table attacks")
    print("   - Use key derivation functions like PBKDF2, scrypt, or Argon2")
    print("   - High iteration counts slow down brute force attacks")
    print("   - Never store plain text passwords")
    print()
    print("2. File Integrity:")
    print("   - Cryptographic hashes verify file integrity")
    print("   - SHA-256 is preferred over MD5 or SHA-1")
    print("   - Useful for software distribution and malware detection")
    print("   - Can detect even single bit changes in files")
    print()
    print("3. Digital Signatures:")
    print("   - Provide authenticity and integrity")
    print("   - Use asymmetric cryptography in real implementations")
    print("   - Prevent message tampering and repudiation")
    print("   - Essential for secure communications")
    print()
    print("4. Blockchain:")
    print("   - Uses hashing for block chaining and integrity")
    print("   - Proof of work prevents spam and ensures security")
    print("   - Immutable ledger through hash-based verification")
    print("   - Foundation for cryptocurrencies and smart contracts")
    print()
    print("5. Security Best Practices:")
    print("   - Use cryptographically secure random number generators")
    print("   - Keep private keys secure and never share them")
    print("   - Regularly update hash algorithms as they become obsolete")
    print("   - Implement proper key management systems")
    print("   - Use established cryptographic libraries, don't implement your own")
