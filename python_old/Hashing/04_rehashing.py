"""
Rehashing Implementation
========================

This file demonstrates dynamic hash table resizing through rehashing:
- Load factor monitoring
- Automatic table expansion
- Prime number table sizing
- Performance optimization through rehashing
- Memory vs. performance trade-offs

Rehashing is crucial for maintaining O(1) average-case performance as
the hash table grows and the load factor increases.

Author: Hash Lecture Series
Purpose: Educational demonstration of dynamic hash table management
"""

import time
from typing import Any, Optional, List, Tuple


class RehashingHashTable:
    """
    A hash table that automatically resizes itself through rehashing.
    
    This implementation demonstrates how to maintain optimal performance
    by monitoring the load factor and expanding the table when necessary.
    
    Key Features:
    - Automatic rehashing when load factor exceeds threshold
    - Prime number table sizing for better distribution
    - Linear probing for collision resolution
    - Performance monitoring and statistics
    """
    
    def __init__(self, initial_size: int = 11, load_factor_threshold: float = 0.7):
        """
        Initialize the rehashing hash table.
        
        Args:
            initial_size (int): Starting size of the hash table (should be prime)
            load_factor_threshold (float): When to trigger rehashing (0.0 to 1.0)
        
        Note: 
        - Lower load factor threshold means more frequent rehashing but better performance
        - Higher threshold means less rehashing but potentially worse performance
        """
        self.size = initial_size
        self.table = [None] * self.size
        self.count = 0
        self.load_factor_threshold = load_factor_threshold
        self.growth_factor = 2  # How much to grow the table by
        self.DELETED = "DELETED"
        
        # Statistics tracking
        self.rehash_count = 0
        self.total_insertions = 0
        self.total_searches = 0
        
        # Verify initial size is prime
        if not self._is_prime(self.size):
            print(f"Warning: Initial size {self.size} is not prime. Consider using a prime number.")
    
    def _is_prime(self, n: int) -> bool:
        """
        Check if a number is prime.
        
        Args:
            n (int): The number to check
            
        Returns:
            bool: True if n is prime, False otherwise
            
        Time Complexity: O(√n)
        """
        if n < 2:
            return False
        if n == 2:
            return True
        if n % 2 == 0:
            return False
        
        # Check odd divisors up to √n
        for i in range(3, int(n ** 0.5) + 1, 2):
            if n % i == 0:
                return False
        
        return True
    
    def _next_prime(self, n: int) -> int:
        """
        Find the next prime number greater than n.
        
        Args:
            n (int): The number to start from
            
        Returns:
            int: The next prime number greater than n
            
        Time Complexity: O(n * √n) in worst case
        """
        candidate = n + 1
        while not self._is_prime(candidate):
            candidate += 1
        return candidate
    
    def _hash(self, key: Any) -> int:
        """
        Hash function using division method.
        
        Args:
            key: The key to hash
            
        Returns:
            int: Array index between 0 and self.size - 1
        """
        return abs(hash(key)) % self.size
    
    def _should_rehash(self) -> bool:
        """
        Check if the table should be rehashed based on load factor.
        
        Returns:
            bool: True if rehashing is needed, False otherwise
        """
        return self.count >= self.size * self.load_factor_threshold
    
    def _rehash(self) -> None:
        """
        Rehash the table to a larger size.
        
        This operation:
        1. Creates a new larger table (next prime number)
        2. Re-inserts all existing elements into the new table
        3. Updates the table reference and size
        
        Time Complexity: O(n) where n is the number of elements
        Space Complexity: O(n) for the new table
        
        Note: This is an expensive operation, but it's amortized over
        many insertions, maintaining O(1) average-case performance.
        """
        print(f"Rehashing: {self.size} -> ", end="")
        
        # Store old table and size
        old_table = self.table
        old_size = self.size
        
        # Calculate new size (usually 2x + some buffer, then find next prime)
        new_size = self._next_prime(int(old_size * self.growth_factor + 1))
        
        # Create new table
        self.size = new_size
        self.table = [None] * self.size
        self.count = 0  # Reset count - will be updated as we re-insert
        
        print(f"{self.size} (Load factor: {self.load_factor():.3f})")
        
        # Re-insert all existing elements
        for item in old_table:
            if item is not None and item != self.DELETED:
                # Recursively call insert, but without triggering another rehash
                self._insert_without_rehash(item[0], item[1])
        
        self.rehash_count += 1
        
        print(f"  Rehashing completed. Re-inserted {self.count} elements.")
    
    def _insert_without_rehash(self, key: Any, value: Any) -> bool:
        """
        Internal insert method that doesn't trigger rehashing.
        Used during the rehashing process to avoid infinite recursion.
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully
        """
        index = self._hash(key)
        original_index = index
        
        # Linear probing
        while self.table[index] is not None and self.table[index] != self.DELETED:
            # Check if this is the same key (update case)
            if isinstance(self.table[index], tuple) and self.table[index][0] == key:
                self.table[index] = (key, value)  # Update existing key
                return True
            
            index = (index + 1) % self.size
            
            # This should not happen during rehashing since we're expanding
            if index == original_index:
                raise Exception("Table full during rehashing - this should not happen!")
        
        # Found empty slot or deleted slot
        self.table[index] = (key, value)
        self.count += 1
        return True
    
    def insert(self, key: Any, value: Any) -> bool:
        """
        Insert a key-value pair into the hash table.
        Automatically triggers rehashing if load factor exceeds threshold.
        
        Time Complexity: O(1) amortized (due to rehashing)
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully
        """
        self.total_insertions += 1
        
        # Check if we need to rehash before inserting
        if self._should_rehash():
            self._rehash()
        
        # Insert the new element
        success = self._insert_without_rehash(key, value)
        
        return success
    
    def search(self, key: Any) -> Optional[Any]:
        """
        Search for a key in the hash table.
        
        Time Complexity: O(1) average case
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if not found
        """
        self.total_searches += 1
        
        index = self._hash(key)
        original_index = index
        
        # Linear probing
        while self.table[index] is not None:
            # Check if this is the key we're looking for
            if (isinstance(self.table[index], tuple) and 
                self.table[index] != self.DELETED and 
                self.table[index][0] == key):
                return self.table[index][1]
            
            index = (index + 1) % self.size
            
            # Stop if we've wrapped around
            if index == original_index:
                break
        
        return None  # Key not found
    
    def delete(self, key: Any) -> bool:
        """
        Delete a key-value pair from the hash table.
        
        Time Complexity: O(1) average case
        
        Args:
            key: The key to delete
            
        Returns:
            bool: True if key was found and deleted, False otherwise
        """
        index = self._hash(key)
        original_index = index
        
        # Linear probing
        while self.table[index] is not None:
            # Check if this is the key we want to delete
            if (isinstance(self.table[index], tuple) and 
                self.table[index] != self.DELETED and 
                self.table[index][0] == key):
                self.table[index] = self.DELETED  # Mark as deleted
                self.count -= 1
                return True
            
            index = (index + 1) % self.size
            
            # Stop if we've wrapped around
            if index == original_index:
                break
        
        return False  # Key not found
    
    def load_factor(self) -> float:
        """
        Calculate the current load factor.
        
        Returns:
            float: Current load factor (count / size)
        """
        return self.count / self.size if self.size > 0 else 0.0
    
    def get_statistics(self) -> dict:
        """
        Get performance statistics for the hash table.
        
        Returns:
            dict: Statistics including rehash count, load factor, etc.
        """
        return {
            'size': self.size,
            'count': self.count,
            'load_factor': self.load_factor(),
            'rehash_count': self.rehash_count,
            'total_insertions': self.total_insertions,
            'total_searches': self.total_searches,
            'threshold': self.load_factor_threshold
        }
    
    def display(self) -> None:
        """
        Display the current state of the hash table.
        """
        stats = self.get_statistics()
        
        print(f"Rehashing Hash Table:")
        print(f"  Size: {stats['size']}")
        print(f"  Elements: {stats['count']}")
        print(f"  Load Factor: {stats['load_factor']:.3f}")
        print(f"  Rehash Count: {stats['rehash_count']}")
        print(f"  Total Insertions: {stats['total_insertions']}")
        print(f"  Total Searches: {stats['total_searches']}")
        print("-" * 60)
        
        # Show non-empty slots
        for i, item in enumerate(self.table):
            if item is not None:
                if item == self.DELETED:
                    print(f"Index {i}: [DELETED]")
                else:
                    print(f"Index {i}: {item}")
        
        print("-" * 60)


def demonstrate_rehashing():
    """
    Demonstrate rehashing behavior with controlled data insertion.
    Shows how the table grows and when rehashing occurs.
    """
    print("=== Rehashing Demonstration ===\n")
    
    # Create hash table with small initial size to force rehashing
    ht = RehashingHashTable(initial_size=5, load_factor_threshold=0.6)
    
    print(f"Initial table size: {ht.size}")
    print(f"Load factor threshold: {ht.load_factor_threshold}")
    print(f"Growth factor: {ht.growth_factor}")
    
    # Test data designed to show rehashing behavior
    test_data = [
        ("apple", 1), ("banana", 2), ("cherry", 3), ("date", 4),
        ("elderberry", 5), ("fig", 6), ("grape", 7), ("honeydew", 8),
        ("kiwi", 9), ("lemon", 10), ("mango", 11), ("orange", 12),
        ("papaya", 13), ("quince", 14), ("raspberry", 15), ("strawberry", 16)
    ]
    
    print(f"\nInserting {len(test_data)} elements:")
    print("=" * 50)
    
    for i, (key, value) in enumerate(test_data):
        print(f"\nStep {i+1}: Inserting '{key}' -> {value}")
        ht.insert(key, value)
        
        print(f"  Current load factor: {ht.load_factor():.3f}")
        print(f"  Table size: {ht.size}")
        print(f"  Element count: {ht.count}")
        
        # Show if rehashing occurred
        if ht.rehash_count > 0:
            print(f"  Total rehashes: {ht.rehash_count}")
    
    print(f"\n" + "=" * 50)
    print("Final Statistics:")
    stats = ht.get_statistics()
    for key, value in stats.items():
        print(f"  {key}: {value}")
    
    # Test search operations
    print(f"\n" + "=" * 50)
    print("Testing search operations:")
    search_keys = ["apple", "banana", "kiwi", "grape", "watermelon"]
    
    for key in search_keys:
        value = ht.search(key)
        if value is not None:
            print(f"  Found '{key}': {value}")
        else:
            print(f"  Not found: '{key}'")


def performance_analysis():
    """
    Analyze the performance impact of different load factor thresholds.
    Shows the trade-off between memory usage and rehashing frequency.
    """
    print("\n=== Performance Analysis ===\n")
    
    # Test different load factor thresholds
    thresholds = [0.5, 0.6, 0.7, 0.8, 0.9]
    num_elements = 1000
    
    print(f"Testing with {num_elements} elements:")
    print("Threshold | Final Size | Rehashes | Avg Load Factor")
    print("-" * 55)
    
    for threshold in thresholds:
        # Create hash table with specific threshold
        ht = RehashingHashTable(initial_size=11, load_factor_threshold=threshold)
        
        # Insert elements and measure performance
        start_time = time.time()
        
        for i in range(num_elements):
            ht.insert(f"key_{i}", f"value_{i}")
        
        end_time = time.time()
        insertion_time = end_time - start_time
        
        # Get final statistics
        stats = ht.get_statistics()
        
        print(f"{threshold:8.1f} | {stats['size']:10d} | {stats['rehash_count']:8d} | {stats['load_factor']:13.3f}")
    
    print("\nAnalysis:")
    print("- Lower thresholds: More rehashes, better performance, more memory")
    print("- Higher thresholds: Fewer rehashes, worse performance, less memory")
    print("- Choose threshold based on your performance vs. memory requirements")


def memory_vs_performance_tradeoff():
    """
    Demonstrate the memory vs. performance trade-off in hash table design.
    """
    print("\n=== Memory vs. Performance Trade-off ===\n")
    
    # Test with different growth factors
    growth_factors = [1.5, 2.0, 3.0, 4.0]
    num_elements = 500
    
    print(f"Testing with {num_elements} elements:")
    print("Growth Factor | Final Size | Rehashes | Memory Usage")
    print("-" * 55)
    
    for growth_factor in growth_factors:
        # Create hash table with specific growth factor
        ht = RehashingHashTable(initial_size=11, load_factor_threshold=0.7)
        ht.growth_factor = growth_factor
        
        # Insert elements
        for i in range(num_elements):
            ht.insert(f"key_{i}", f"value_{i}")
        
        # Calculate memory usage (simplified - just table size)
        memory_usage = ht.size * 8  # Assuming 8 bytes per slot
        
        stats = ht.get_statistics()
        print(f"{growth_factor:12.1f} | {stats['size']:10d} | {stats['rehash_count']:8d} | {memory_usage:12d} bytes")
    
    print("\nAnalysis:")
    print("- Smaller growth factors: More rehashes, less memory waste")
    print("- Larger growth factors: Fewer rehashes, more memory waste")
    print("- Growth factor of 2.0 is commonly used as a good balance")


def stress_test():
    """
    Stress test the rehashing hash table with a large number of operations.
    """
    print("\n=== Stress Test ===\n")
    
    ht = RehashingHashTable(initial_size=7, load_factor_threshold=0.75)
    
    # Insert many elements
    num_elements = 2000
    print(f"Inserting {num_elements} elements...")
    
    start_time = time.time()
    for i in range(num_elements):
        ht.insert(f"key_{i}", f"value_{i}")
    end_time = time.time()
    
    insertion_time = end_time - start_time
    
    print(f"Insertion completed in {insertion_time:.6f} seconds")
    print(f"Average time per insertion: {insertion_time/num_elements*1000000:.2f} microseconds")
    
    # Test search performance
    search_keys = [f"key_{i}" for i in range(0, num_elements, 10)]
    
    start_time = time.time()
    for key in search_keys:
        ht.search(key)
    end_time = time.time()
    
    search_time = end_time - start_time
    
    print(f"\nSearching {len(search_keys)} keys...")
    print(f"Search completed in {search_time:.6f} seconds")
    print(f"Average time per search: {search_time/len(search_keys)*1000000:.2f} microseconds")
    
    # Display final statistics
    print(f"\nFinal Statistics:")
    stats = ht.get_statistics()
    for key, value in stats.items():
        print(f"  {key}: {value}")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will demonstrate:
    1. Rehashing behavior with controlled data
    2. Performance analysis of different thresholds
    3. Memory vs. performance trade-offs
    4. Stress testing with large datasets
    """
    
    # Run all demonstrations
    demonstrate_rehashing()
    performance_analysis()
    memory_vs_performance_tradeoff()
    stress_test()
    
    print("\n" + "="*70)
    print("EDUCATIONAL NOTES:")
    print("="*70)
    print("1. Rehashing is essential for maintaining O(1) average-case performance")
    print("2. Load factor threshold affects the frequency of rehashing:")
    print("   - Lower threshold: More rehashes, better performance, more memory")
    print("   - Higher threshold: Fewer rehashes, worse performance, less memory")
    print()
    print("3. Growth factor affects memory efficiency:")
    print("   - Smaller factor: More rehashes, less memory waste")
    print("   - Larger factor: Fewer rehashes, more memory waste")
    print()
    print("4. Best Practices:")
    print("   - Use prime numbers for table sizes")
    print("   - Choose load factor threshold based on performance requirements")
    print("   - Growth factor of 2.0 is commonly used")
    print("   - Monitor rehashing frequency in production systems")
    print()
    print("5. Trade-offs:")
    print("   - Memory vs. Performance")
    print("   - Rehashing cost vs. Search performance")
    print("   - Initial size vs. Growth factor")
    print("   - Load factor threshold vs. Memory usage")
