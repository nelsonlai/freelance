"""
Cryptographic Hashing - Hash Functions and Message Digests

This module demonstrates cryptographic hash functions, which are one-way
functions that take input data of any size and produce a fixed-size output
(called a hash or digest). Hash functions are fundamental building blocks
in cryptography and are used for data integrity, password storage, and
digital signatures.

Key Properties of Cryptographic Hash Functions:
1. Pre-image Resistance: Given hash h, hard to find input m such that H(m) = h
2. Second Pre-image Resistance: Given m1, hard to find m2 ≠ m1 such that H(m1) = H(m2)
3. Collision Resistance: Hard to find any m1 ≠ m2 such that H(m1) = H(m2)

Author: Cryptography Lecture
Date: 2024
"""

import hashlib
import os
import secrets
import time
from typing import Dict, List, Tuple


def demonstrate_hash_functions():
    """
    Demonstrate various cryptographic hash functions and their properties.
    
    This function shows:
    - Different hash algorithms (SHA-1, SHA-256, SHA-3)
    - The avalanche effect (small input changes cause large output changes)
    - Hash function properties
    """
    print("=" * 60)
    print("CRYPTOGRAPHIC HASH FUNCTIONS DEMONSTRATION")
    print("=" * 60)
    
    # Test message
    message = b"Hello, World!"
    print(f"Original message: {message.decode()}")
    print(f"Message length: {len(message)} bytes")
    
    print("\nHash Results:")
    print("-" * 40)
    
    # SHA-1 (deprecated due to collision attacks)
    sha1_hash = hashlib.sha1(message).hexdigest()
    print(f"SHA-1:     {sha1_hash}")
    print(f"SHA-1 length: {len(sha1_hash) * 4} bits")
    
    # SHA-256 (widely used)
    sha256_hash = hashlib.sha256(message).hexdigest()
    print(f"SHA-256:   {sha256_hash}")
    print(f"SHA-256 length: {len(sha256_hash) * 4} bits")
    
    # SHA-3 (newest standard)
    sha3_hash = hashlib.sha3_256(message).hexdigest()
    print(f"SHA-3:     {sha3_hash}")
    print(f"SHA-3 length: {len(sha3_hash) * 4} bits")
    
    # MD5 (deprecated - collision attacks possible)
    md5_hash = hashlib.md5(message).hexdigest()
    print(f"MD5:       {md5_hash}")
    print(f"MD5 length: {len(md5_hash) * 4} bits")
    
    print("\n" + "=" * 60)
    print("AVALANCHE EFFECT DEMONSTRATION")
    print("=" * 60)
    
    # Demonstrate avalanche effect
    message1 = b"Hello, World!"
    message2 = b"Hello, World?"  # Changed only the last character
    
    hash1 = hashlib.sha256(message1).hexdigest()
    hash2 = hashlib.sha256(message2).hexdigest()
    
    print(f"Message 1: {message1.decode()}")
    print(f"Hash 1:    {hash1}")
    print(f"\nMessage 2: {message2.decode()}")
    print(f"Hash 2:    {hash2}")
    
    # Count bit differences
    bit_differences = sum(c1 != c2 for c1, c2 in zip(hash1, hash2))
    print(f"\nCharacter differences: {bit_differences}")
    print(f"Bit differences: {bit_differences * 4} (out of 256 bits)")
    print(f"Similarity: {((256 - bit_differences * 4) / 256) * 100:.1f}%")


def hash_data(data: bytes, algorithm: str = 'sha256') -> str:
    """
    Hash data using the specified algorithm.
    
    Args:
        data (bytes): The data to hash
        algorithm (str): The hash algorithm to use ('md5', 'sha1', 'sha256', 'sha3_256', etc.)
    
    Returns:
        str: The hexadecimal representation of the hash
        
    Example:
        >>> hash_data(b"Hello", "sha256")
        '185f8db32271fe25f561a6fc938b2e264306ec304eda518007d1764826381969'
    """
    try:
        # Create hash object using the specified algorithm
        hash_obj = hashlib.new(algorithm)
        hash_obj.update(data)
        return hash_obj.hexdigest()
    except ValueError as e:
        raise ValueError(f"Unsupported hash algorithm: {algorithm}") from e


def verify_data_integrity(original_data: bytes, received_data: bytes, 
                         algorithm: str = 'sha256') -> bool:
    """
    Verify data integrity by comparing hashes.
    
    Args:
        original_data (bytes): The original data
        received_data (bytes): The data to verify
        algorithm (str): The hash algorithm to use
    
    Returns:
        bool: True if data is intact, False if corrupted
        
    Example:
        >>> verify_data_integrity(b"Hello", b"Hello", "sha256")
        True
        >>> verify_data_integrity(b"Hello", b"World", "sha256")
        False
    """
    original_hash = hash_data(original_data, algorithm)
    received_hash = hash_data(received_data, algorithm)
    
    return original_hash == received_hash


def demonstrate_data_integrity():
    """
    Demonstrate how hash functions are used for data integrity verification.
    """
    print("\n" + "=" * 60)
    print("DATA INTEGRITY VERIFICATION DEMONSTRATION")
    print("=" * 60)
    
    # Simulate file transfer
    original_file = b"This is an important document that needs to be transferred securely."
    print(f"Original file content: {original_file.decode()}")
    
    # Calculate hash of original file
    original_hash = hash_data(original_file, 'sha256')
    print(f"Original file hash: {original_hash}")
    
    print("\nSimulating file transfer...")
    
    # Case 1: File transferred correctly
    received_file_correct = original_file
    is_intact = verify_data_integrity(original_file, received_file_correct)
    print(f"File transferred correctly: {is_intact}")
    
    # Case 2: File corrupted during transfer
    received_file_corrupted = b"This is an important document that needs to be transferred securly."  # typo
    is_intact = verify_data_integrity(original_file, received_file_corrupted)
    print(f"File corrupted during transfer: {not is_intact}")
    
    # Show hash differences
    corrupted_hash = hash_data(received_file_corrupted, 'sha256')
    print(f"Corrupted file hash: {corrupted_hash}")
    
    print("\nHash comparison:")
    print(f"Original:  {original_hash}")
    print(f"Corrupted: {corrupted_hash}")
    print("Even a single character change produces a completely different hash!")


def hash_file(filepath: str, algorithm: str = 'sha256') -> str:
    """
    Calculate the hash of a file.
    
    Args:
        filepath (str): Path to the file
        algorithm (str): Hash algorithm to use
    
    Returns:
        str: The hexadecimal hash of the file
        
    Example:
        >>> hash_file("document.txt", "sha256")
        'a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3'
    """
    hash_obj = hashlib.new(algorithm)
    
    try:
        with open(filepath, 'rb') as f:
            # Read file in chunks to handle large files efficiently
            while chunk := f.read(8192):  # Read 8KB chunks
                hash_obj.update(chunk)
        
        return hash_obj.hexdigest()
    except FileNotFoundError:
        raise FileNotFoundError(f"File not found: {filepath}")
    except Exception as e:
        raise Exception(f"Error reading file: {e}")


def demonstrate_file_hashing():
    """
    Demonstrate file hashing for integrity verification.
    """
    print("\n" + "=" * 60)
    print("FILE HASHING DEMONSTRATION")
    print("=" * 60)
    
    # Create a sample file
    sample_content = """This is a sample file for demonstrating file hashing.
It contains multiple lines of text.
File hashing is useful for verifying file integrity.
"""
    
    filename = "sample_file.txt"
    
    try:
        # Write sample file
        with open(filename, 'w') as f:
            f.write(sample_content)
        
        print(f"Created sample file: {filename}")
        print(f"File content:\n{sample_content}")
        
        # Calculate file hash
        file_hash = hash_file(filename, 'sha256')
        print(f"File hash (SHA-256): {file_hash}")
        
        # Modify file slightly
        modified_content = sample_content.replace("demonstrating", "showing")
        with open(filename, 'w') as f:
            f.write(modified_content)
        
        print(f"\nModified file content:\n{modified_content}")
        
        # Calculate new hash
        modified_hash = hash_file(filename, 'sha256')
        print(f"Modified file hash: {modified_hash}")
        
        print(f"\nHashes are different: {file_hash != modified_hash}")
        
    finally:
        # Clean up
        if os.path.exists(filename):
            os.remove(filename)
            print(f"\nCleaned up: {filename}")


def collision_resistance_demo():
    """
    Demonstrate collision resistance by showing how hard it is to find collisions.
    """
    print("\n" + "=" * 60)
    print("COLLISION RESISTANCE DEMONSTRATION")
    print("=" * 60)
    
    print("Collision resistance means it's computationally infeasible")
    print("to find two different inputs that produce the same hash.")
    
    # Try to find a collision (this will likely fail, demonstrating collision resistance)
    print("\nAttempting to find a collision in SHA-256...")
    print("(This may take a while and will likely not find a collision)")
    
    seen_hashes = {}
    attempts = 0
    max_attempts = 100000  # Limit attempts for demonstration
    
    start_time = time.time()
    
    for i in range(max_attempts):
        # Generate random data
        random_data = os.urandom(16)  # 16 random bytes
        hash_value = hashlib.sha256(random_data).hexdigest()
        
        # Check if we've seen this hash before
        if hash_value in seen_hashes:
            print(f"COLLISION FOUND!")
            print(f"Data 1: {seen_hashes[hash_value].hex()}")
            print(f"Data 2: {random_data.hex()}")
            print(f"Hash: {hash_value}")
            print(f"Attempts needed: {attempts}")
            break
        
        seen_hashes[hash_value] = random_data
        attempts += 1
        
        # Progress indicator
        if attempts % 10000 == 0:
            elapsed = time.time() - start_time
            print(f"Attempts: {attempts}, Time: {elapsed:.1f}s")
    
    else:
        elapsed = time.time() - start_time
        print(f"No collision found in {attempts} attempts")
        print(f"Time elapsed: {elapsed:.1f} seconds")
        print("This demonstrates the collision resistance of SHA-256")
    
    print(f"\nTotal unique hashes generated: {len(seen_hashes)}")


def hash_properties_analysis():
    """
    Analyze the properties of different hash functions.
    """
    print("\n" + "=" * 60)
    print("HASH FUNCTION PROPERTIES ANALYSIS")
    print("=" * 60)
    
    algorithms = {
        'MD5': {'length': 128, 'status': 'Deprecated', 'reason': 'Collision attacks possible'},
        'SHA-1': {'length': 160, 'status': 'Deprecated', 'reason': 'Collision attacks possible'},
        'SHA-256': {'length': 256, 'status': 'Secure', 'reason': 'Widely used, no known attacks'},
        'SHA-3': {'length': 256, 'status': 'Secure', 'reason': 'Newest standard, designed to resist attacks'},
        'BLAKE2': {'length': 256, 'status': 'Secure', 'reason': 'Fast, secure alternative'}
    }
    
    print("Hash Algorithm Comparison:")
    print("-" * 60)
    print(f"{'Algorithm':<10} {'Length':<8} {'Status':<12} {'Notes'}")
    print("-" * 60)
    
    for algo, info in algorithms.items():
        print(f"{algo:<10} {info['length']:<8} {info['status']:<12} {info['reason']}")
    
    print("\nSecurity Recommendations:")
    print("✓ Use SHA-256 or SHA-3 for new applications")
    print("✓ Avoid MD5 and SHA-1 (deprecated)")
    print("✓ Consider BLAKE2 for performance-critical applications")
    print("✓ Use appropriate salt for password hashing")
    print("✓ Verify hash integrity in secure environments")


def performance_comparison():
    """
    Compare the performance of different hash algorithms.
    """
    print("\n" + "=" * 60)
    print("HASH FUNCTION PERFORMANCE COMPARISON")
    print("=" * 60)
    
    # Test data
    test_data = b"Performance test data for hash function comparison" * 1000  # ~50KB
    algorithms = ['md5', 'sha1', 'sha256', 'sha3_256']
    
    print(f"Test data size: {len(test_data)} bytes")
    print("\nPerformance Results:")
    print("-" * 40)
    
    for algo in algorithms:
        # Time the hashing operation
        start_time = time.time()
        
        # Perform multiple iterations for better timing accuracy
        iterations = 1000
        for _ in range(iterations):
            hashlib.new(algo).update(test_data).hexdigest()
        
        end_time = time.time()
        total_time = end_time - start_time
        avg_time = total_time / iterations
        
        # Calculate throughput
        throughput = len(test_data) / avg_time / (1024 * 1024)  # MB/s
        
        print(f"{algo.upper():<8}: {avg_time*1000:6.2f} ms, {throughput:6.1f} MB/s")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_hash_functions()
    demonstrate_data_integrity()
    demonstrate_file_hashing()
    collision_resistance_demo()
    hash_properties_analysis()
    performance_comparison()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("Hash functions are fundamental cryptographic primitives that provide:")
    print("• Data integrity verification")
    print("• Password storage (with proper salting)")
    print("• Digital signature support")
    print("• Blockchain and cryptocurrency applications")
    print("\nKey properties:")
    print("• One-way function (pre-image resistance)")
    print("• Collision resistance")
    print("• Avalanche effect")
    print("• Deterministic output")
    print("\nAlways use secure, well-tested hash functions like SHA-256 or SHA-3!")
