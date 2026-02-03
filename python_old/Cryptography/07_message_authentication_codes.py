"""
Message Authentication Codes (MACs) - HMAC Implementation

This module demonstrates Message Authentication Codes (MACs), specifically HMAC
(Hash-based Message Authentication Code). MACs provide authentication and
integrity verification for messages using a shared secret key.

Key Concepts:
- MAC: A cryptographic checksum that provides authentication and integrity
- HMAC: A specific MAC construction using hash functions
- Keyed Hash: A hash function that uses a secret key
- Authentication: Verifies the message came from someone who knows the key
- Integrity: Detects if the message has been modified

Security Properties:
- Authentication: Only someone with the key can generate a valid MAC
- Integrity: Any modification to the message will invalidate the MAC
- Non-repudiation: Cannot prove who sent the message (shared key)

Author: Cryptography Lecture
Date: 2024
"""

import hmac
import hashlib
import os
import secrets
import time
from typing import Tuple, Optional


def create_hmac(message: bytes, key: bytes, algorithm: str = 'sha256') -> bytes:
    """
    Create HMAC using the specified hash algorithm.
    
    HMAC (Hash-based Message Authentication Code) is a specific construction
    for creating MACs using hash functions. It's defined in RFC 2104.
    
    The HMAC algorithm:
    1. Pad the key to the hash block size
    2. XOR the padded key with an inner padding constant
    3. Hash the result concatenated with the message
    4. XOR the padded key with an outer padding constant
    5. Hash the result concatenated with the inner hash
    
    Args:
        message (bytes): The message to authenticate
        key (bytes): The secret key
        algorithm (str): The hash algorithm to use ('sha256', 'sha1', 'md5', etc.)
    
    Returns:
        bytes: The HMAC value
        
    Example:
        >>> key = b"secret_key"
        >>> message = b"Hello, World!"
        >>> mac = create_hmac(message, key)
        >>> len(mac)
        32
    """
    try:
        # Create HMAC using the specified algorithm
        mac = hmac.new(key, message, algorithm)
        return mac.digest()
    except ValueError as e:
        raise ValueError(f"Unsupported hash algorithm: {algorithm}") from e


def verify_hmac(message: bytes, key: bytes, received_mac: bytes, 
                algorithm: str = 'sha256') -> bool:
    """
    Verify HMAC using constant-time comparison.
    
    Args:
        message (bytes): The original message
        key (bytes): The secret key
        received_mac (bytes): The MAC received with the message
        algorithm (str): The hash algorithm used
    
    Returns:
        bool: True if MAC is valid, False otherwise
        
    Example:
        >>> key = b"secret_key"
        >>> message = b"Hello, World!"
        >>> mac = create_hmac(message, key)
        >>> verify_hmac(message, key, mac)
        True
    """
    # Compute expected MAC
    expected_mac = create_hmac(message, key, algorithm)
    
    # Use constant-time comparison to prevent timing attacks
    return hmac.compare_digest(expected_mac, received_mac)


def create_hmac_hex(message: bytes, key: bytes, algorithm: str = 'sha256') -> str:
    """
    Create HMAC and return as hexadecimal string.
    
    Args:
        message (bytes): The message to authenticate
        key (bytes): The secret key
        algorithm (str): The hash algorithm to use
    
    Returns:
        str: The HMAC value as hexadecimal string
    """
    mac = create_hmac(message, key, algorithm)
    return mac.hex()


def demonstrate_hmac_basic():
    """
    Demonstrate basic HMAC functionality.
    """
    print("=" * 60)
    print("HMAC (HASH-BASED MESSAGE AUTHENTICATION CODE) DEMONSTRATION")
    print("=" * 60)
    
    # Example 1: Basic HMAC creation and verification
    message = b"Important message"
    key = os.urandom(32)  # 256-bit key
    
    print(f"Message: {message.decode()}")
    print(f"Key: {key.hex()}")
    
    # Create HMAC
    mac = create_hmac(message, key)
    print(f"HMAC: {mac.hex()}")
    print(f"HMAC length: {len(mac) * 8} bits")
    
    # Verify HMAC
    is_valid = verify_hmac(message, key, mac)
    print(f"HMAC verification: {is_valid}")
    
    # Test with wrong key
    wrong_key = os.urandom(32)
    is_invalid = verify_hmac(message, wrong_key, mac)
    print(f"Wrong key verification: {is_invalid}")
    
    # Test with modified message
    modified_message = b"Important message!"
    is_invalid = verify_hmac(modified_message, key, mac)
    print(f"Modified message verification: {is_invalid}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Different hash algorithms
    print("HMAC with different hash algorithms:")
    
    algorithms = ['md5', 'sha1', 'sha256', 'sha3_256']
    
    for algo in algorithms:
        mac_algo = create_hmac(message, key, algo)
        print(f"{algo.upper():<8}: {mac_algo.hex()}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Same message, different keys
    print("Same message with different keys:")
    
    keys = [os.urandom(16) for _ in range(3)]
    
    for i, key in enumerate(keys):
        mac_key = create_hmac(message, key)
        print(f"Key {i+1}: {key.hex()}")
        print(f"HMAC {i+1}: {mac_key.hex()}")


def demonstrate_hmac_properties():
    """
    Demonstrate key properties of HMAC.
    """
    print("\n" + "=" * 60)
    print("HMAC PROPERTIES DEMONSTRATION")
    print("=" * 60)
    
    # Property 1: Deterministic
    print("1. Deterministic: Same input always produces same output")
    message = b"Test message"
    key = b"test_key"
    
    mac1 = create_hmac(message, key)
    mac2 = create_hmac(message, key)
    
    print(f"HMAC 1: {mac1.hex()}")
    print(f"HMAC 2: {mac2.hex()}")
    print(f"Are identical: {mac1 == mac2}")
    
    print("\n" + "-" * 40)
    
    # Property 2: Avalanche effect
    print("2. Avalanche Effect: Small input changes cause large output changes")
    
    message1 = b"Hello, World!"
    message2 = b"Hello, World?"  # Changed only last character
    
    mac1 = create_hmac(message1, key)
    mac2 = create_hmac(message2, key)
    
    print(f"Message 1: {message1.decode()}")
    print(f"HMAC 1:    {mac1.hex()}")
    print(f"Message 2: {message2.decode()}")
    print(f"HMAC 2:    {mac2.hex()}")
    
    # Count bit differences
    bit_differences = sum(c1 != c2 for c1, c2 in zip(mac1.hex(), mac2.hex()))
    print(f"Character differences: {bit_differences}")
    print(f"Bit differences: {bit_differences * 4} (out of 256 bits)")
    
    print("\n" + "-" * 40)
    
    # Property 3: Key sensitivity
    print("3. Key Sensitivity: Small key changes cause large output changes")
    
    key1 = b"test_key"
    key2 = b"test_key!"  # Added one character
    
    mac1 = create_hmac(message, key1)
    mac2 = create_hmac(message, key2)
    
    print(f"Key 1: {key1.decode()}")
    print(f"HMAC 1: {mac1.hex()}")
    print(f"Key 2: {key2.decode()}")
    print(f"HMAC 2: {mac2.hex()}")
    
    bit_differences = sum(c1 != c2 for c1, c2 in zip(mac1.hex(), mac2.hex()))
    print(f"Character differences: {bit_differences}")


def hmac_vs_hash_demo():
    """
    Demonstrate the difference between HMAC and regular hash functions.
    """
    print("\n" + "=" * 60)
    print("HMAC vs REGULAR HASH COMPARISON")
    print("=" * 60)
    
    message = b"Sensitive data"
    key = b"secret_key"
    
    # Regular hash (no key)
    regular_hash = hashlib.sha256(message).hexdigest()
    print(f"Message: {message.decode()}")
    print(f"Regular SHA-256: {regular_hash}")
    
    # HMAC (with key)
    hmac_value = create_hmac(message, key)
    print(f"HMAC-SHA256:     {hmac_value.hex()}")
    
    print("\nKey differences:")
    print("• Regular hash: Anyone can compute it")
    print("• HMAC: Only someone with the key can compute it")
    print("• Regular hash: Provides integrity only")
    print("• HMAC: Provides both integrity and authentication")
    
    print("\nSecurity implications:")
    print("• Regular hash: Vulnerable to extension attacks")
    print("• HMAC: Resistant to extension attacks")
    print("• Regular hash: No authentication")
    print("• HMAC: Authenticates the sender")


def hmac_extension_attack_demo():
    """
    Demonstrate why HMAC is resistant to extension attacks.
    """
    print("\n" + "=" * 60)
    print("EXTENSION ATTACK RESISTANCE DEMONSTRATION")
    print("=" * 60)
    
    print("Extension Attack on Regular Hash:")
    print("If you know H(message), you can compute H(message || additional_data)")
    print("without knowing the original message!")
    
    # Demonstrate extension attack on regular hash
    original_message = b"user=admin"
    additional_data = b"&role=administrator"
    
    # Original hash
    original_hash = hashlib.sha256(original_message).hexdigest()
    print(f"Original message: {original_message.decode()}")
    print(f"Original hash: {original_hash}")
    
    # Extended message
    extended_message = original_message + additional_data
    extended_hash = hashlib.sha256(extended_message).hexdigest()
    print(f"Extended message: {extended_message.decode()}")
    print(f"Extended hash: {extended_hash}")
    
    print("\nHMAC Extension Attack Resistance:")
    print("With HMAC, you cannot compute HMAC(message || additional_data)")
    print("from HMAC(message) without knowing the key!")
    
    key = b"secret_key"
    
    # Original HMAC
    original_hmac = create_hmac(original_message, key)
    print(f"Original HMAC: {original_hmac.hex()}")
    
    # Extended HMAC (requires knowing the key)
    extended_hmac = create_hmac(extended_message, key)
    print(f"Extended HMAC: {extended_hmac.hex()}")
    
    print("\nNote: You cannot compute the extended HMAC from the original")
    print("HMAC without knowing the secret key!")


def hmac_key_management():
    """
    Demonstrate HMAC key management considerations.
    """
    print("\n" + "=" * 60)
    print("HMAC KEY MANAGEMENT")
    print("=" * 60)
    
    print("Key Generation:")
    
    # Generate keys of different lengths
    key_lengths = [16, 32, 64]  # 128, 256, 512 bits
    
    for length in key_lengths:
        key = os.urandom(length)
        print(f"Key length {length*8:3d} bits: {key.hex()}")
    
    print("\nKey Derivation:")
    print("• Use cryptographically secure random number generators")
    print("• Use sufficient key length (at least 128 bits)")
    print("• Derive keys from passwords using PBKDF2, bcrypt, etc.")
    print("• Use different keys for different purposes")
    
    print("\nKey Storage:")
    print("• Store keys securely (encrypted, access controlled)")
    print("• Never hardcode keys in source code")
    print("• Use environment variables or secure key management systems")
    print("• Rotate keys regularly")
    
    print("\nKey Distribution:")
    print("• Use secure key exchange protocols")
    print("• Never transmit keys over insecure channels")
    print("• Use key derivation functions for shared secrets")


def hmac_performance_analysis():
    """
    Analyze HMAC performance with different algorithms.
    """
    print("\n" + "=" * 60)
    print("HMAC PERFORMANCE ANALYSIS")
    print("=" * 60)
    
    # Test data
    test_data = b"Performance test data for HMAC analysis" * 100  # ~4KB
    key = os.urandom(32)
    
    algorithms = ['md5', 'sha1', 'sha256', 'sha3_256']
    
    print(f"Test data size: {len(test_data)} bytes")
    print("\nPerformance Results:")
    print("-" * 40)
    
    for algo in algorithms:
        # Time the HMAC operation
        start_time = time.time()
        
        # Perform multiple iterations for better timing accuracy
        iterations = 1000
        for _ in range(iterations):
            create_hmac(test_data, key, algo)
        
        end_time = time.time()
        total_time = end_time - start_time
        avg_time = total_time / iterations
        
        # Calculate throughput
        throughput = len(test_data) / avg_time / (1024 * 1024)  # MB/s
        
        print(f"{algo.upper():<8}: {avg_time*1000:6.2f} ms, {throughput:6.1f} MB/s")


def hmac_security_considerations():
    """
    Discuss security considerations for HMAC usage.
    """
    print("\n" + "=" * 60)
    print("HMAC SECURITY CONSIDERATIONS")
    print("=" * 60)
    
    print("Security Properties:")
    print("✓ Authentication: Verifies message origin")
    print("✓ Integrity: Detects message modification")
    print("✓ Resistance to extension attacks")
    print("✓ Resistance to collision attacks (if underlying hash is secure)")
    
    print("\nSecurity Limitations:")
    print("✗ No confidentiality (message is not encrypted)")
    print("✗ No non-repudiation (shared key)")
    print("✗ Vulnerable if key is compromised")
    print("✗ Vulnerable to replay attacks (without additional measures)")
    
    print("\nAttack Vectors:")
    print("1. Key compromise: Attacker gains access to the secret key")
    print("2. Replay attacks: Attacker replays old valid messages")
    print("3. Timing attacks: Attacker uses timing differences in verification")
    print("4. Side-channel attacks: Attacker uses power/timing analysis")
    
    print("\nMitigation Strategies:")
    print("• Use strong, randomly generated keys")
    print("• Use constant-time comparison (hmac.compare_digest)")
    print("• Include timestamps or nonces to prevent replay attacks")
    print("• Use different keys for different purposes")
    print("• Implement proper key rotation")
    print("• Use secure key storage and distribution")


def practical_hmac_examples():
    """
    Show practical examples of HMAC usage.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL HMAC EXAMPLES")
    print("=" * 60)
    
    # Example 1: API Authentication
    print("1. API Authentication:")
    
    api_key = b"api_secret_key_12345"
    user_id = "user123"
    timestamp = str(int(time.time()))
    endpoint = "/api/data"
    
    # Create message to authenticate
    message = f"{user_id}:{timestamp}:{endpoint}".encode()
    
    # Generate HMAC
    api_hmac = create_hmac(message, api_key)
    
    print(f"User ID: {user_id}")
    print(f"Timestamp: {timestamp}")
    print(f"Endpoint: {endpoint}")
    print(f"Message: {message.decode()}")
    print(f"HMAC: {api_hmac.hex()}")
    
    # Verify on server side
    is_valid = verify_hmac(message, api_key, api_hmac)
    print(f"Server verification: {is_valid}")
    
    print("\n" + "-" * 40)
    
    # Example 2: File Integrity
    print("2. File Integrity Verification:")
    
    file_content = b"This is important file content that needs to be protected."
    file_key = b"file_integrity_key"
    
    # Generate file HMAC
    file_hmac = create_hmac(file_content, file_key)
    
    print(f"File content: {file_content.decode()}")
    print(f"File HMAC: {file_hmac.hex()}")
    
    # Simulate file modification
    modified_content = file_content + b" (modified)"
    
    # Verify original file
    is_valid_original = verify_hmac(file_content, file_key, file_hmac)
    print(f"Original file verification: {is_valid_original}")
    
    # Verify modified file
    is_valid_modified = verify_hmac(modified_content, file_key, file_hmac)
    print(f"Modified file verification: {is_valid_modified}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Session Token
    print("3. Session Token Generation:")
    
    session_key = b"session_secret_key"
    user_id = "user456"
    session_id = "sess_789"
    expiration = str(int(time.time()) + 3600)  # 1 hour from now
    
    # Create session token
    session_data = f"{user_id}:{session_id}:{expiration}".encode()
    session_hmac = create_hmac(session_data, session_key)
    
    # Combine data and HMAC
    session_token = f"{session_data.decode()}:{session_hmac.hex()}"
    
    print(f"User ID: {user_id}")
    print(f"Session ID: {session_id}")
    print(f"Expiration: {expiration}")
    print(f"Session token: {session_token}")
    
    # Verify session token
    parts = session_token.split(':')
    if len(parts) == 4:
        user_id_verify, session_id_verify, expiration_verify, hmac_verify = parts
        session_data_verify = f"{user_id_verify}:{session_id_verify}:{expiration_verify}".encode()
        
        is_valid_session = verify_hmac(session_data_verify, session_key, bytes.fromhex(hmac_verify))
        print(f"Session verification: {is_valid_session}")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_hmac_basic()
    demonstrate_hmac_properties()
    hmac_vs_hash_demo()
    hmac_extension_attack_demo()
    hmac_key_management()
    hmac_performance_analysis()
    hmac_security_considerations()
    practical_hmac_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("HMAC provides message authentication and integrity:")
    print("• Authentication: Verifies message origin")
    print("• Integrity: Detects message modification")
    print("• Key-based: Only key holders can generate valid MACs")
    print("• Resistant to extension attacks")
    print("\nCommon use cases:")
    print("• API authentication")
    print("• File integrity verification")
    print("• Session token generation")
    print("• Message authentication in protocols")
    print("\nAlways use constant-time comparison and secure key management!")
