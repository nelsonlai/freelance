"""
Hash Functions Demonstration
============================

This file demonstrates different types of hash functions and their characteristics:
- Division method (modulo hashing)
- Multiplication method
- Polynomial rolling hash (Horner's method)
- Cryptographic hash functions
- Custom hash functions for different data types

Author: Hash Lecture Series
Purpose: Educational demonstration of hash function design principles
"""

import hashlib
import math
from typing import Any, Union


class HashFunctionDemo:
    """
    A comprehensive demonstration of different hash function techniques.
    
    This class shows various approaches to hashing and their trade-offs:
    - Speed vs. distribution quality
    - Security considerations
    - Data type specific optimizations
    """
    
    def __init__(self, table_size=97):
        """
        Initialize the hash function demo.
        
        Args:
            table_size (int): The size of the hash table (should be prime for best results)
        
        Note: Using prime numbers for table size helps reduce clustering and
        improves distribution when using division method.
        """
        self.table_size = table_size
    
    def division_hash(self, key: Union[int, str]) -> int:
        """
        Division method hash function.
        
        This is the simplest and most commonly used hash function.
        Formula: h(key) = key % table_size
        
        Pros:
        - Very fast (O(1))
        - Simple to implement
        - Works well with prime table sizes
        
        Cons:
        - Can produce clustering if keys have patterns
        - Not suitable for cryptographic purposes
        
        Args:
            key: The key to hash (will be converted to integer)
            
        Returns:
            int: Hash value between 0 and table_size - 1
        """
        # Convert key to integer if it's not already
        if isinstance(key, str):
            # Simple string to integer conversion
            key_int = sum(ord(c) for c in key)
        elif isinstance(key, (tuple, list)):
            # Convert sequence to integer
            key_int = hash(key)
        else:
            key_int = int(key)
        
        # Division method: key % table_size
        return abs(key_int) % self.table_size
    
    def multiplication_hash(self, key: Union[int, str]) -> int:
        """
        Multiplication method hash function.
        
        This method often provides better distribution than division method.
        Formula: h(key) = floor(table_size * ((key * A) mod 1))
        where A is a constant (often the golden ratio - 1)
        
        Pros:
        - Better distribution than division method
        - Less sensitive to patterns in keys
        - Good for non-prime table sizes
        
        Cons:
        - Slightly slower than division method
        - Requires careful choice of multiplier A
        
        Args:
            key: The key to hash
            
        Returns:
            int: Hash value between 0 and table_size - 1
        """
        # Convert key to integer
        if isinstance(key, str):
            key_int = sum(ord(c) for c in key)
        elif isinstance(key, (tuple, list)):
            key_int = hash(key)
        else:
            key_int = int(key)
        
        # Use golden ratio - 1 as multiplier (approximately 0.618)
        A = (math.sqrt(5) - 1) / 2
        
        # Multiplication method
        fractional_part = (abs(key_int) * A) % 1
        return int(self.table_size * fractional_part)
    
    def polynomial_hash(self, key: str, base: int = 31) -> int:
        """
        Polynomial rolling hash (Horner's method) for strings.
        
        This is excellent for string hashing and provides good distribution.
        Formula: h(s) = (s[0] * base^(n-1) + s[1] * base^(n-2) + ... + s[n-1]) % table_size
        
        Horner's method: h(s) = (((s[0] * base + s[1]) * base + s[2]) * base + ...) % table_size
        
        Pros:
        - Excellent distribution for strings
        - Can be computed incrementally (rolling hash)
        - Good avalanche effect (small changes cause big hash changes)
        
        Cons:
        - Slower than simple division
        - Requires careful choice of base value
        
        Args:
            key: The string to hash
            base: The base for polynomial computation (should be prime, often 31 or 37)
            
        Returns:
            int: Hash value between 0 and table_size - 1
        """
        if not isinstance(key, str):
            key = str(key)
        
        hash_value = 0
        for char in key:
            # Horner's method: multiply by base and add character value
            hash_value = (hash_value * base + ord(char)) % self.table_size
        
        return hash_value
    
    def crypto_hash(self, key: Any, algorithm: str = 'sha256') -> str:
        """
        Cryptographic hash function.
        
        These are designed for security and provide excellent distribution.
        They are much slower than simple hash functions but are cryptographically secure.
        
        Pros:
        - Excellent distribution
        - Cryptographically secure
        - Deterministic but unpredictable
        - Very low collision probability
        
        Cons:
        - Much slower than simple hash functions
        - Produces large output (not suitable for direct array indexing)
        - Overkill for simple hash table applications
        
        Args:
            key: The data to hash (will be converted to bytes)
            algorithm: The hash algorithm to use ('md5', 'sha1', 'sha256', etc.)
            
        Returns:
            str: Hexadecimal representation of the hash
        """
        # Convert key to bytes
        if isinstance(key, str):
            data = key.encode('utf-8')
        elif isinstance(key, (int, float)):
            data = str(key).encode('utf-8')
        else:
            data = str(key).encode('utf-8')
        
        # Create hash object and compute hash
        hash_obj = hashlib.new(algorithm)
        hash_obj.update(data)
        return hash_obj.hexdigest()
    
    def crypto_hash_modulo(self, key: Any, algorithm: str = 'sha256') -> int:
        """
        Cryptographic hash function with modulo for hash table indexing.
        
        This combines the security of cryptographic hashes with the
        practical need for bounded output for array indexing.
        
        Args:
            key: The data to hash
            algorithm: The hash algorithm to use
            
        Returns:
            int: Hash value between 0 and table_size - 1
        """
        # Get the full cryptographic hash
        full_hash = self.crypto_hash(key, algorithm)
        
        # Convert to integer and take modulo
        # Take first 8 characters to avoid integer overflow
        hash_int = int(full_hash[:8], 16)
        return hash_int % self.table_size
    
    def tuple_hash(self, key: tuple) -> int:
        """
        Custom hash function for tuples.
        
        This demonstrates how to create hash functions for complex data types.
        Each element in the tuple contributes to the final hash.
        
        Args:
            key: The tuple to hash
            
        Returns:
            int: Hash value between 0 and table_size - 1
        """
        hash_value = 0
        prime = 31  # Prime number for good distribution
        
        for item in key:
            if isinstance(item, str):
                # Use polynomial hash for strings
                item_hash = self.polynomial_hash(item)
            elif isinstance(item, (int, float)):
                # Use the value directly
                item_hash = abs(int(item))
            else:
                # Fallback to built-in hash
                item_hash = abs(hash(item))
            
            # Combine hashes using polynomial approach
            hash_value = (hash_value * prime + item_hash) % self.table_size
        
        return hash_value


def demonstrate_hash_functions():
    """
    Demonstrate different hash functions with the same input data.
    This shows how different methods produce different distributions.
    """
    print("=== Hash Functions Demonstration ===\n")
    
    demo = HashFunctionDemo(table_size=17)  # Use prime number
    
    # Test data
    test_keys = [
        "hello",
        "world", 
        "python",
        "hashing",
        "algorithm",
        "computer",
        "science",
        "programming",
        12345,
        67890,
        ("apple", 5),
        ("banana", 3),
        ("cherry", 8)
    ]
    
    print(f"Testing hash functions with table size {demo.table_size}\n")
    print("Key".ljust(15), "Division".ljust(10), "Multiply".ljust(10), "Polynomial".ljust(10), "Crypto".ljust(10))
    print("-" * 70)
    
    for key in test_keys:
        # Calculate different hash values
        div_hash = demo.division_hash(key)
        mult_hash = demo.multiplication_hash(key)
        
        # For polynomial hash, convert to string if needed
        if isinstance(key, str):
            poly_hash = demo.polynomial_hash(key)
        else:
            poly_hash = demo.polynomial_hash(str(key))
        
        crypto_hash = demo.crypto_hash_modulo(key)
        
        # Display results
        key_str = str(key)[:14]  # Truncate long keys
        print(f"{key_str.ljust(15)} {div_hash:<10} {mult_hash:<10} {poly_hash:<10} {crypto_hash:<10}")


def analyze_hash_distribution():
    """
    Analyze the distribution quality of different hash functions.
    This helps students understand which hash functions work best.
    """
    print("\n=== Hash Distribution Analysis ===\n")
    
    demo = HashFunctionDemo(table_size=11)
    
    # Generate test data with patterns to test hash function quality
    test_strings = [
        "user001", "user002", "user003", "user004", "user005",
        "admin01", "admin02", "admin03", "admin04", "admin05",
        "guest01", "guest02", "guest03", "guest04", "guest05",
        "test123", "test456", "test789", "test012", "test345"
    ]
    
    # Test different hash functions
    hash_methods = [
        ("Division", demo.division_hash),
        ("Multiplication", demo.multiplication_hash),
        ("Polynomial", lambda k: demo.polynomial_hash(str(k))),
        ("Crypto", demo.crypto_hash_modulo)
    ]
    
    for method_name, hash_func in hash_methods:
        print(f"\n{method_name} Method:")
        
        # Count how many keys hash to each index
        distribution = [0] * demo.table_size
        
        for key in test_strings:
            index = hash_func(key)
            distribution[index] += 1
        
        # Display distribution
        print("Index:", end="")
        for i in range(demo.table_size):
            print(f"{i:4}", end="")
        print()
        
        print("Count:", end="")
        for count in distribution:
            print(f"{count:4}", end="")
        print()
        
        # Calculate distribution quality metrics
        total_keys = len(test_strings)
        expected_per_index = total_keys / demo.table_size
        
        # Calculate variance (lower is better)
        variance = sum((count - expected_per_index) ** 2 for count in distribution) / demo.table_size
        
        # Calculate standard deviation
        std_dev = math.sqrt(variance)
        
        print(f"Expected per index: {expected_per_index:.2f}")
        print(f"Variance: {variance:.2f}")
        print(f"Standard deviation: {std_dev:.2f}")
        print(f"Distribution quality: {'Good' if std_dev < 1.5 else 'Fair' if std_dev < 2.5 else 'Poor'}")


def demonstrate_cryptographic_hashes():
    """
    Demonstrate cryptographic hash functions and their properties.
    Shows avalanche effect and security characteristics.
    """
    print("\n=== Cryptographic Hash Functions ===\n")
    
    demo = HashFunctionDemo()
    
    # Test avalanche effect - small changes should cause large hash changes
    test_strings = [
        "hello",
        "Hello",  # Capital H
        "hellp",  # Different last character
        "hallo",  # Different middle character
        "hello ",  # Extra space
        " hello"   # Leading space
    ]
    
    algorithms = ['md5', 'sha1', 'sha256', 'sha512']
    
    print("Avalanche Effect Demonstration:")
    print("Small changes in input should cause large changes in output\n")
    
    for algorithm in algorithms:
        print(f"{algorithm.upper()} hashes:")
        for text in test_strings:
            hash_value = demo.crypto_hash(text, algorithm)
            # Show only first 16 characters for readability
            short_hash = hash_value[:16] + "..."
            print(f"  '{text}' -> {short_hash}")
        print()


def demonstrate_custom_hash_functions():
    """
    Demonstrate how to create custom hash functions for specific data types.
    """
    print("\n=== Custom Hash Functions ===\n")
    
    demo = HashFunctionDemo(table_size=13)
    
    # Test tuples with different structures
    test_tuples = [
        ("apple", 5),
        ("banana", 3),
        ("apple", 10),  # Same first element, different second
        ("cherry", 5),  # Different first element, same second
        ("apple", 5),   # Identical tuple
        (1, 2, 3),
        (1, 2, 4),
        (2, 2, 3),
    ]
    
    print("Custom tuple hash function:")
    print("Tuple".ljust(20), "Hash Value")
    print("-" * 35)
    
    for tup in test_tuples:
        hash_value = demo.tuple_hash(tup)
        print(f"{str(tup).ljust(20)} {hash_value}")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will demonstrate:
    1. Different hash function implementations
    2. Distribution analysis
    3. Cryptographic hash properties
    4. Custom hash function design
    """
    
    # Run all demonstrations
    demonstrate_hash_functions()
    analyze_hash_distribution()
    demonstrate_cryptographic_hashes()
    demonstrate_custom_hash_functions()
    
    print("\n" + "="*70)
    print("EDUCATIONAL NOTES:")
    print("="*70)
    print("1. Hash Function Selection Guidelines:")
    print("   - Division method: Fast, good for general use with prime table sizes")
    print("   - Multiplication method: Better distribution, good for non-prime sizes")
    print("   - Polynomial method: Excellent for strings, good avalanche effect")
    print("   - Cryptographic: Best distribution but slower, use for security")
    print()
    print("2. Key Properties to Consider:")
    print("   - Uniformity: Keys should be evenly distributed")
    print("   - Determinism: Same input always produces same output")
    print("   - Efficiency: Fast computation for good performance")
    print("   - Avalanche effect: Small input changes cause large output changes")
    print()
    print("3. Best Practices:")
    print("   - Use prime numbers for table sizes with division method")
    print("   - Choose appropriate base values for polynomial hashing")
    print("   - Avoid predictable patterns in your keys")
    print("   - Consider your data type when selecting hash function")
    print("   - Test distribution with your actual data")
