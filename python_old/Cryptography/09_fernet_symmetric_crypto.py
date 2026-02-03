"""
Symmetric Cryptography - Fernet Implementation

This module demonstrates Fernet, a high-level symmetric encryption library
that provides authenticated encryption. Fernet is built on top of AES in CBC
mode with HMAC authentication, making it easy to use securely.

Key Features of Fernet:
- Authenticated encryption (confidentiality + integrity + authentication)
- Simple API for encryption and decryption
- Automatic key generation and management
- Built-in timestamp support for token expiration
- Protection against common attacks (padding oracle, etc.)

Fernet Format:
- Version (1 byte)
- Timestamp (8 bytes)
- IV (16 bytes)
- Ciphertext (variable length)
- HMAC (32 bytes)

Author: Cryptography Lecture
Date: 2024
"""

from cryptography.fernet import Fernet
import os
import time
from typing import Optional, Tuple


class FernetCipher:
    """
    A wrapper class for Fernet encryption with additional features.
    
    Fernet provides authenticated encryption using AES-128 in CBC mode
    with HMAC-SHA256 for authentication. It's designed to be secure
    and easy to use.
    """
    
    def __init__(self, key: Optional[bytes] = None):
        """
        Initialize Fernet cipher with a key.
        
        Args:
            key (bytes, optional): The encryption key. If None, generates a new key.
        """
        if key is None:
            self.key = Fernet.generate_key()
        else:
            self.key = key
        
        self.fernet = Fernet(self.key)
    
    def generate_key(self) -> bytes:
        """
        Generate a new Fernet key.
        
        Returns:
            bytes: A new Fernet key
        """
        return Fernet.generate_key()
    
    def encrypt(self, data: bytes) -> bytes:
        """
        Encrypt data using Fernet.
        
        Args:
            data (bytes): The data to encrypt
        
        Returns:
            bytes: The encrypted token
        
        Example:
            >>> fernet = FernetCipher()
            >>> token = fernet.encrypt(b"Hello, World!")
            >>> len(token)
            95
        """
        return self.fernet.encrypt(data)
    
    def decrypt(self, token: bytes, ttl: Optional[int] = None) -> bytes:
        """
        Decrypt a Fernet token.
        
        Args:
            token (bytes): The encrypted token
            ttl (int, optional): Time-to-live in seconds. If provided,
                               the token will be rejected if it's older than ttl seconds.
        
        Returns:
            bytes: The decrypted data
        
        Raises:
            cryptography.fernet.InvalidToken: If the token is invalid or expired
        
        Example:
            >>> fernet = FernetCipher()
            >>> token = fernet.encrypt(b"Hello, World!")
            >>> decrypted = fernet.decrypt(token)
            >>> decrypted
            b'Hello, World!'
        """
        return self.fernet.decrypt(token, ttl=ttl)
    
    def encrypt_at_time(self, data: bytes, current_time: int) -> bytes:
        """
        Encrypt data with a specific timestamp.
        
        Args:
            data (bytes): The data to encrypt
            current_time (int): Unix timestamp to embed in the token
        
        Returns:
            bytes: The encrypted token with the specified timestamp
        """
        return self.fernet.encrypt_at_time(data, current_time)
    
    def decrypt_at_time(self, token: bytes, ttl: int, current_time: int) -> bytes:
        """
        Decrypt a token with a specific current time.
        
        Args:
            token (bytes): The encrypted token
            ttl (int): Time-to-live in seconds
            current_time (int): Current Unix timestamp
        
        Returns:
            bytes: The decrypted data
        """
        return self.fernet.decrypt_at_time(token, ttl, current_time)
    
    def extract_timestamp(self, token: bytes) -> int:
        """
        Extract the timestamp from a Fernet token.
        
        Args:
            token (bytes): The encrypted token
        
        Returns:
            int: The Unix timestamp embedded in the token
        """
        return self.fernet.extract_timestamp(token)


def demonstrate_fernet_basic():
    """
    Demonstrate basic Fernet encryption and decryption.
    """
    print("=" * 60)
    print("FERNET AUTHENTICATED ENCRYPTION DEMONSTRATION")
    print("=" * 60)
    
    # Create Fernet cipher
    fernet = FernetCipher()
    
    print(f"Generated key: {fernet.key.decode()}")
    print(f"Key length: {len(fernet.key)} bytes")
    
    # Test message
    message = b"My deep secret message that needs to be protected."
    print(f"\nOriginal message: {message.decode()}")
    print(f"Message length: {len(message)} bytes")
    
    # Encrypt
    token = fernet.encrypt(message)
    print(f"\nEncrypted token: {token.decode()}")
    print(f"Token length: {len(token)} bytes")
    
    # Decrypt
    decrypted = fernet.decrypt(token)
    print(f"\nDecrypted message: {decrypted.decode()}")
    print(f"Decryption successful: {message == decrypted}")
    
    print("\n" + "-" * 40)
    
    # Show token structure
    print("Fernet Token Structure:")
    print(f"Token (hex): {token.hex()}")
    print(f"Token length: {len(token)} bytes")
    print("Structure: Version(1) + Timestamp(8) + IV(16) + Ciphertext + HMAC(32)")


def demonstrate_fernet_timestamp():
    """
    Demonstrate Fernet's timestamp functionality.
    """
    print("\n" + "=" * 60)
    print("FERNET TIMESTAMP FUNCTIONALITY")
    print("=" * 60)
    
    fernet = FernetCipher()
    message = b"Time-sensitive message"
    
    # Encrypt with current time
    current_time = int(time.time())
    print(f"Current time: {current_time}")
    print(f"Current time (readable): {time.ctime(current_time)}")
    
    token = fernet.encrypt_at_time(message, current_time)
    print(f"Encrypted token: {token.decode()}")
    
    # Extract timestamp
    extracted_time = fernet.extract_timestamp(token)
    print(f"Extracted timestamp: {extracted_time}")
    print(f"Extracted time (readable): {time.ctime(extracted_time)}")
    
    print("\n" + "-" * 40)
    
    # Test TTL (Time To Live)
    print("Time To Live (TTL) demonstration:")
    
    # Encrypt with timestamp from 10 seconds ago
    past_time = current_time - 10
    token_past = fernet.encrypt_at_time(message, past_time)
    
    print(f"Token created 10 seconds ago")
    
    # Try to decrypt with TTL of 5 seconds (should fail)
    try:
        decrypted = fernet.decrypt_at_time(token_past, ttl=5, current_time=current_time)
        print("Decryption successful (unexpected)")
    except Exception as e:
        print(f"Decryption failed (expected): {type(e).__name__}")
    
    # Try to decrypt with TTL of 15 seconds (should succeed)
    try:
        decrypted = fernet.decrypt_at_time(token_past, ttl=15, current_time=current_time)
        print(f"Decryption successful: {decrypted.decode()}")
    except Exception as e:
        print(f"Decryption failed (unexpected): {type(e).__name__}")


def demonstrate_fernet_authentication():
    """
    Demonstrate Fernet's authentication capabilities.
    """
    print("\n" + "=" * 60)
    print("FERNET AUTHENTICATION DEMONSTRATION")
    print("=" * 60)
    
    fernet = FernetCipher()
    message = b"Important authenticated message"
    
    # Encrypt message
    token = fernet.encrypt(message)
    print(f"Original message: {message.decode()}")
    print(f"Token: {token.decode()}")
    
    print("\n" + "-" * 40)
    
    # Test 1: Valid decryption
    print("Test 1: Valid decryption")
    try:
        decrypted = fernet.decrypt(token)
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except Exception as e:
        print(f"Authentication failed: {type(e).__name__}")
    
    print("\n" + "-" * 40)
    
    # Test 2: Tampered token
    print("Test 2: Tampered token")
    tampered_token = bytearray(token)
    tampered_token[10] ^= 1  # Flip one bit
    
    try:
        decrypted = fernet.decrypt(bytes(tampered_token))
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except Exception as e:
        print(f"Authentication failed: {type(e).__name__}")
        print("Tampering detected!")
    
    print("\n" + "-" * 40)
    
    # Test 3: Wrong key
    print("Test 3: Wrong key")
    wrong_fernet = FernetCipher()
    
    try:
        decrypted = wrong_fernet.decrypt(token)
        print(f"Decrypted: {decrypted.decode()}")
        print("Authentication successful!")
    except Exception as e:
        print(f"Authentication failed: {type(e).__name__}")
        print("Wrong key detected!")


def demonstrate_fernet_key_management():
    """
    Demonstrate Fernet key management.
    """
    print("\n" + "=" * 60)
    print("FERNET KEY MANAGEMENT")
    print("=" * 60)
    
    # Generate multiple keys
    print("Generating multiple Fernet keys:")
    
    keys = []
    for i in range(3):
        key = Fernet.generate_key()
        keys.append(key)
        print(f"Key {i+1}: {key.decode()}")
    
    print("\n" + "-" * 40)
    
    # Test key compatibility
    print("Key compatibility test:")
    
    message = b"Test message for key compatibility"
    
    # Encrypt with first key
    fernet1 = FernetCipher(keys[0])
    token = fernet1.encrypt(message)
    print(f"Encrypted with key 1: {token.decode()}")
    
    # Try to decrypt with different keys
    for i, key in enumerate(keys):
        fernet_test = FernetCipher(key)
        try:
            decrypted = fernet_test.decrypt(token)
            print(f"Decryption with key {i+1}: SUCCESS - {decrypted.decode()}")
        except Exception as e:
            print(f"Decryption with key {i+1}: FAILED - {type(e).__name__}")
    
    print("\n" + "-" * 40)
    
    # Key derivation from password
    print("Key derivation from password:")
    
    password = b"my_secret_password"
    
    # Derive key from password using PBKDF2
    import hashlib
    salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password, salt, 100000)
    
    print(f"Password: {password.decode()}")
    print(f"Salt: {salt.hex()}")
    print(f"Derived key: {key.hex()}")
    
    # Use derived key with Fernet
    fernet_password = FernetCipher(key)
    token_password = fernet_password.encrypt(message)
    print(f"Token with password-derived key: {token_password.decode()}")
    
    # Decrypt with same key
    decrypted_password = fernet_password.decrypt(token_password)
    print(f"Decrypted: {decrypted_password.decode()}")


def demonstrate_fernet_performance():
    """
    Demonstrate Fernet performance characteristics.
    """
    print("\n" + "=" * 60)
    print("FERNET PERFORMANCE ANALYSIS")
    print("=" * 60)
    
    fernet = FernetCipher()
    
    # Test different message sizes
    message_sizes = [16, 64, 256, 1024, 4096]  # bytes
    
    print("Performance by message size:")
    print("-" * 40)
    
    for size in message_sizes:
        message = b"A" * size
        
        # Time encryption
        start_time = time.time()
        iterations = 1000
        
        for _ in range(iterations):
            token = fernet.encrypt(message)
        
        encryption_time = time.time() - start_time
        avg_encryption_time = encryption_time / iterations
        
        # Time decryption
        start_time = time.time()
        
        for _ in range(iterations):
            fernet.decrypt(token)
        
        decryption_time = time.time() - start_time
        avg_decryption_time = decryption_time / iterations
        
        # Calculate throughput
        encryption_throughput = size / avg_encryption_time / (1024 * 1024)  # MB/s
        decryption_throughput = size / avg_decryption_time / (1024 * 1024)  # MB/s
        
        print(f"Size {size:4d} bytes: Encrypt {avg_encryption_time*1000:6.2f} ms, "
              f"{encryption_throughput:6.1f} MB/s | "
              f"Decrypt {avg_decryption_time*1000:6.2f} ms, {decryption_throughput:6.1f} MB/s")


def demonstrate_fernet_vs_aes():
    """
    Compare Fernet with raw AES implementation.
    """
    print("\n" + "=" * 60)
    print("FERNET vs RAW AES COMPARISON")
    print("=" * 60)
    
    message = b"Comparison test message"
    
    # Fernet implementation
    fernet = FernetCipher()
    
    start_time = time.time()
    fernet_token = fernet.encrypt(message)
    fernet_time = time.time() - start_time
    
    start_time = time.time()
    fernet_decrypted = fernet.decrypt(fernet_token)
    fernet_decrypt_time = time.time() - start_time
    
    print("Fernet Implementation:")
    print(f"  Encryption time: {fernet_time*1000:.3f} ms")
    print(f"  Decryption time: {fernet_decrypt_time*1000:.3f} ms")
    print(f"  Token size: {len(fernet_token)} bytes")
    print(f"  Success: {message == fernet_decrypted}")
    
    print("\n" + "-" * 40)
    
    # Raw AES implementation (simplified)
    from Crypto.Cipher import AES
    from Crypto.Random import get_random_bytes
    from Crypto.Util.Padding import pad, unpad
    import hmac
    import hashlib
    
    key = get_random_bytes(32)
    iv = get_random_bytes(16)
    
    # Encrypt
    start_time = time.time()
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_message = pad(message, AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    
    # Create HMAC
    mac_key = get_random_bytes(32)
    mac = hmac.new(mac_key, iv + ciphertext, hashlib.sha256).digest()
    
    aes_time = time.time() - start_time
    
    # Decrypt
    start_time = time.time()
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_decrypted = cipher.decrypt(ciphertext)
    aes_decrypted = unpad(padded_decrypted, AES.block_size)
    
    # Verify HMAC
    expected_mac = hmac.new(mac_key, iv + ciphertext, hashlib.sha256).digest()
    mac_valid = hmac.compare_digest(mac, expected_mac)
    
    aes_decrypt_time = time.time() - start_time
    
    print("Raw AES Implementation:")
    print(f"  Encryption time: {aes_time*1000:.3f} ms")
    print(f"  Decryption time: {aes_decrypt_time*1000:.3f} ms")
    print(f"  Ciphertext size: {len(iv + ciphertext + mac)} bytes")
    print(f"  Success: {message == aes_decrypted and mac_valid}")
    
    print("\nComparison:")
    print("• Fernet: Simple, secure, automatic key management")
    print("• Raw AES: More control, but requires careful implementation")
    print("• Fernet: Built-in authentication and timestamp support")
    print("• Raw AES: Manual HMAC and timestamp handling required")


def demonstrate_fernet_security():
    """
    Demonstrate Fernet's security features.
    """
    print("\n" + "=" * 60)
    print("FERNET SECURITY FEATURES")
    print("=" * 60)
    
    print("Fernet Security Properties:")
    print("✓ Authenticated encryption (confidentiality + integrity + authentication)")
    print("✓ Protection against padding oracle attacks")
    print("✓ Protection against timing attacks")
    print("✓ Built-in timestamp support")
    print("✓ Secure key generation")
    print("✓ Protection against chosen ciphertext attacks")
    
    print("\n" + "-" * 40)
    
    print("Fernet Construction:")
    print("• AES-128 in CBC mode for encryption")
    print("• HMAC-SHA256 for authentication")
    print("• PKCS7 padding")
    print("• Random IV for each encryption")
    print("• Timestamp embedded in token")
    
    print("\n" + "-" * 40)
    
    print("Attack Resistance:")
    print("• Padding Oracle Attacks: Prevented by HMAC verification before decryption")
    print("• Timing Attacks: Prevented by constant-time comparison")
    print("• Chosen Ciphertext Attacks: Prevented by authentication")
    print("• Replay Attacks: Prevented by timestamp support")
    print("• Key Recovery Attacks: Prevented by secure key generation")
    
    print("\n" + "-" * 40)
    
    print("Best Practices:")
    print("• Use Fernet.generate_key() for key generation")
    print("• Store keys securely")
    print("• Use TTL for time-sensitive data")
    print("• Rotate keys regularly")
    print("• Never reuse keys across different applications")


def practical_fernet_examples():
    """
    Show practical examples of Fernet usage.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL FERNET EXAMPLES")
    print("=" * 60)
    
    # Example 1: File encryption
    print("1. File Encryption:")
    
    # Create a sample file
    filename = "sample_file.txt"
    file_content = b"This is sensitive file content that needs to be encrypted."
    
    try:
        # Write file
        with open(filename, 'wb') as f:
            f.write(file_content)
        
        print(f"Created file: {filename}")
        print(f"File content: {file_content.decode()}")
        
        # Encrypt file
        fernet = FernetCipher()
        with open(filename, 'rb') as f:
            file_data = f.read()
        
        encrypted_data = fernet.encrypt(file_data)
        
        # Save encrypted file
        encrypted_filename = filename + ".encrypted"
        with open(encrypted_filename, 'wb') as f:
            f.write(encrypted_data)
        
        print(f"Encrypted file: {encrypted_filename}")
        print(f"Encrypted data: {encrypted_data.decode()}")
        
        # Decrypt file
        with open(encrypted_filename, 'rb') as f:
            encrypted_data_read = f.read()
        
        decrypted_data = fernet.decrypt(encrypted_data_read)
        
        print(f"Decrypted data: {decrypted_data.decode()}")
        print(f"Decryption successful: {file_content == decrypted_data}")
        
    finally:
        # Clean up
        for fname in [filename, encrypted_filename]:
            if os.path.exists(fname):
                os.remove(fname)
                print(f"Cleaned up: {fname}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Session token
    print("2. Session Token Generation:")
    
    session_data = {
        "user_id": "12345",
        "username": "alice",
        "role": "admin",
        "login_time": int(time.time())
    }
    
    # Convert to bytes
    import json
    session_json = json.dumps(session_data).encode()
    
    # Encrypt session data
    session_fernet = FernetCipher()
    session_token = session_fernet.encrypt(session_json)
    
    print(f"Session data: {session_data}")
    print(f"Session token: {session_token.decode()}")
    
    # Decrypt and verify session
    decrypted_session = session_fernet.decrypt(session_token)
    session_data_decrypted = json.loads(decrypted_session.decode())
    
    print(f"Decrypted session: {session_data_decrypted}")
    print(f"Session verification: {session_data == session_data_decrypted}")
    
    print("\n" + "-" * 40)
    
    # Example 3: API token with expiration
    print("3. API Token with Expiration:")
    
    api_data = {
        "user_id": "67890",
        "permissions": ["read", "write"],
        "expires_at": int(time.time()) + 3600  # 1 hour from now
    }
    
    api_json = json.dumps(api_data).encode()
    
    # Encrypt with current time
    current_time = int(time.time())
    api_token = session_fernet.encrypt_at_time(api_json, current_time)
    
    print(f"API data: {api_data}")
    print(f"API token: {api_token.decode()}")
    
    # Verify token with TTL
    try:
        decrypted_api = session_fernet.decrypt_at_time(api_token, ttl=3600, current_time=current_time)
        api_data_decrypted = json.loads(decrypted_api.decode())
        print(f"API token valid: {api_data_decrypted}")
    except Exception as e:
        print(f"API token expired: {type(e).__name__}")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_fernet_basic()
    demonstrate_fernet_timestamp()
    demonstrate_fernet_authentication()
    demonstrate_fernet_key_management()
    demonstrate_fernet_performance()
    demonstrate_fernet_vs_aes()
    demonstrate_fernet_security()
    practical_fernet_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("Fernet provides easy-to-use authenticated encryption:")
    print("• Simple API for encryption and decryption")
    print("• Built-in authentication and integrity protection")
    print("• Timestamp support for token expiration")
    print("• Protection against common attacks")
    print("\nUse cases:")
    print("• File encryption")
    print("• Session token generation")
    print("• API token with expiration")
    print("• Secure data storage")
    print("\nFernet is perfect for applications that need secure, easy-to-use encryption!")
