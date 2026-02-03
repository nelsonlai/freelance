"""
Collision Resolution Strategies
===============================

This file demonstrates different collision resolution strategies for hash tables:
- Separate Chaining (Closed Addressing)
- Linear Probing (Open Addressing)
- Quadratic Probing (Open Addressing)
- Double Hashing (Open Addressing)

Each strategy has different trade-offs in terms of:
- Memory usage
- Performance characteristics
- Implementation complexity
- Clustering behavior

Author: Hash Lecture Series
Purpose: Educational demonstration of collision resolution techniques
"""

import time
from typing import Any, Optional, Tuple, List


class SeparateChainingHashTable:
    """
    Hash table using separate chaining for collision resolution.
    
    In separate chaining, each table slot contains a linked list (or array)
    of all key-value pairs that hash to that index.
    
    Advantages:
    - Simple to implement
    - No clustering issues
    - Can store more elements than table size
    - Good for unknown data distribution
    
    Disadvantages:
    - Extra memory overhead for pointers/chains
    - Poor cache locality
    - Memory fragmentation
    """
    
    def __init__(self, size: int = 11):
        """
        Initialize the hash table with separate chaining.
        
        Args:
            size (int): The size of the hash table (should be prime for best results)
        """
        self.size = size
        # Create a list of empty lists - each index will hold a chain
        self.table = [[] for _ in range(size)]
        self.count = 0
    
    def _hash(self, key: Any) -> int:
        """
        Hash function using division method.
        
        Args:
            key: The key to hash
            
        Returns:
            int: Array index between 0 and self.size - 1
        """
        return abs(hash(key)) % self.size
    
    def insert(self, key: Any, value: Any) -> bool:
        """
        Insert a key-value pair into the hash table.
        
        Time Complexity: O(1 + α) where α is the load factor
        - O(1) to compute hash and access chain
        - O(α) to search through the chain
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully, False if key already exists
        """
        index = self._hash(key)
        
        # Check if key already exists in the chain
        for i, (existing_key, existing_value) in enumerate(self.table[index]):
            if existing_key == key:
                # Update existing key-value pair
                self.table[index][i] = (key, value)
                return False  # Key already existed
        
        # Key doesn't exist, add new key-value pair to the chain
        self.table[index].append((key, value))
        self.count += 1
        return True  # New key inserted
    
    def search(self, key: Any) -> Optional[Any]:
        """
        Search for a key in the hash table.
        
        Time Complexity: O(1 + α) where α is the load factor
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if not found
        """
        index = self._hash(key)
        
        # Search through the chain at the calculated index
        for existing_key, value in self.table[index]:
            if existing_key == key:
                return value
        
        return None  # Key not found
    
    def delete(self, key: Any) -> bool:
        """
        Delete a key-value pair from the hash table.
        
        Time Complexity: O(1 + α) where α is the load factor
        
        Args:
            key: The key to delete
            
        Returns:
            bool: True if key was found and deleted, False otherwise
        """
        index = self._hash(key)
        
        # Search for the key in the chain and remove it
        for i, (existing_key, existing_value) in enumerate(self.table[index]):
            if existing_key == key:
                del self.table[index][i]  # Remove the key-value pair
                self.count -= 1
                return True
        
        return False  # Key not found
    
    def load_factor(self) -> float:
        """Calculate the current load factor."""
        return self.count / self.size
    
    def display(self) -> None:
        """Display the current state of the hash table."""
        print(f"Separate Chaining Hash Table (Size: {self.size}, Elements: {self.count}, Load Factor: {self.load_factor():.3f})")
        print("-" * 60)
        
        for i, chain in enumerate(self.table):
            if chain:  # Only show non-empty chains
                print(f"Index {i}: {chain}")
        
        print("-" * 60)


class LinearProbingHashTable:
    """
    Hash table using linear probing for collision resolution.
    
    In linear probing, when a collision occurs, we probe the next consecutive
    slots until we find an empty one.
    
    Probe sequence: h(key), h(key)+1, h(key)+2, ..., h(key)+m
    
    Advantages:
    - Cache-friendly (sequential memory access)
    - Simple to implement
    - Good for small tables
    
    Disadvantages:
    - Primary clustering (long runs of occupied slots)
    - Performance degrades as table fills up
    - Complex deletion (requires special markers)
    """
    
    def __init__(self, size: int = 11):
        """
        Initialize the hash table with linear probing.
        
        Args:
            size (int): The size of the hash table (should be prime for best results)
        """
        self.size = size
        # Initialize table with None values
        self.table = [None] * size
        self.count = 0
        # Special marker for deleted items to maintain probe sequences
        self.DELETED = "DELETED"
    
    def _hash(self, key: Any) -> int:
        """Hash function using division method."""
        return abs(hash(key)) % self.size
    
    def insert(self, key: Any, value: Any) -> bool:
        """
        Insert a key-value pair into the hash table using linear probing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully, False if table is full
        """
        if self.count >= self.size:
            return False  # Table is full
        
        index = self._hash(key)
        original_index = index
        
        # Linear probing: search for empty slot or existing key
        while self.table[index] is not None and self.table[index] != self.DELETED:
            # Check if this is the same key (update case)
            if isinstance(self.table[index], tuple) and self.table[index][0] == key:
                self.table[index] = (key, value)  # Update existing key
                return True
            
            index = (index + 1) % self.size  # Move to next slot
            
            # Check if we've wrapped around (table is full)
            if index == original_index:
                return False
        
        # Found empty slot or deleted slot
        self.table[index] = (key, value)
        self.count += 1
        return True
    
    def search(self, key: Any) -> Optional[Any]:
        """
        Search for a key in the hash table using linear probing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if not found
        """
        index = self._hash(key)
        original_index = index
        
        # Linear probing: search for the key
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
        Delete a key-value pair from the hash table using linear probing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to delete
            
        Returns:
            bool: True if key was found and deleted, False otherwise
        """
        index = self._hash(key)
        original_index = index
        
        # Linear probing: search for the key
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
        """Calculate the current load factor."""
        return self.count / self.size
    
    def display(self) -> None:
        """Display the current state of the hash table."""
        print(f"Linear Probing Hash Table (Size: {self.size}, Elements: {self.count}, Load Factor: {self.load_factor():.3f})")
        print("-" * 60)
        
        for i, item in enumerate(self.table):
            if item is not None:
                if item == self.DELETED:
                    print(f"Index {i}: [DELETED]")
                else:
                    print(f"Index {i}: {item}")
        
        print("-" * 60)


class QuadraticProbingHashTable:
    """
    Hash table using quadratic probing for collision resolution.
    
    In quadratic probing, when a collision occurs, we probe slots at
    increasing quadratic distances from the original hash position.
    
    Probe sequence: h(key), h(key)+1², h(key)+2², h(key)+3², ...
    
    Advantages:
    - Reduces primary clustering compared to linear probing
    - Better distribution than linear probing
    - Cache-friendly for small probe sequences
    
    Disadvantages:
    - Secondary clustering (keys that hash to the same position follow same probe sequence)
    - Complex deletion
    - May not find empty slot even if one exists
    """
    
    def __init__(self, size: int = 11):
        """
        Initialize the hash table with quadratic probing.
        
        Args:
            size (int): The size of the hash table (should be prime and 4k+3 for best results)
        """
        self.size = size
        self.table = [None] * size
        self.count = 0
        self.DELETED = "DELETED"
    
    def _hash(self, key: Any) -> int:
        """Hash function using division method."""
        return abs(hash(key)) % self.size
    
    def insert(self, key: Any, value: Any) -> bool:
        """
        Insert a key-value pair using quadratic probing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully, False if table is full
        """
        if self.count >= self.size:
            return False  # Table is full
        
        index = self._hash(key)
        original_index = index
        i = 0
        
        # Quadratic probing: h(key) + i²
        while self.table[index] is not None and self.table[index] != self.DELETED:
            # Check if this is the same key (update case)
            if isinstance(self.table[index], tuple) and self.table[index][0] == key:
                self.table[index] = (key, value)  # Update existing key
                return True
            
            i += 1
            index = (original_index + i * i) % self.size
            
            # Prevent infinite loop
            if i > self.size:
                return False
        
        # Found empty slot or deleted slot
        self.table[index] = (key, value)
        self.count += 1
        return True
    
    def search(self, key: Any) -> Optional[Any]:
        """
        Search for a key using quadratic probing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if not found
        """
        index = self._hash(key)
        original_index = index
        i = 0
        
        # Quadratic probing: search for the key
        while self.table[index] is not None:
            # Check if this is the key we're looking for
            if (isinstance(self.table[index], tuple) and 
                self.table[index] != self.DELETED and 
                self.table[index][0] == key):
                return self.table[index][1]
            
            i += 1
            index = (original_index + i * i) % self.size
            
            # Stop if we've tried too many times
            if i > self.size:
                break
        
        return None  # Key not found
    
    def load_factor(self) -> float:
        """Calculate the current load factor."""
        return self.count / self.size
    
    def display(self) -> None:
        """Display the current state of the hash table."""
        print(f"Quadratic Probing Hash Table (Size: {self.size}, Elements: {self.count}, Load Factor: {self.load_factor():.3f})")
        print("-" * 60)
        
        for i, item in enumerate(self.table):
            if item is not None:
                if item == self.DELETED:
                    print(f"Index {i}: [DELETED]")
                else:
                    print(f"Index {i}: {item}")
        
        print("-" * 60)


class DoubleHashingHashTable:
    """
    Hash table using double hashing for collision resolution.
    
    In double hashing, we use a second hash function to determine
    the probe step size. This provides the best distribution among
    open addressing methods.
    
    Probe sequence: h1(key), h1(key)+h2(key), h1(key)+2*h2(key), ...
    
    Advantages:
    - Best distribution among open addressing methods
    - Minimal clustering
    - Good performance even with high load factors
    
    Disadvantages:
    - Requires two hash functions
    - More complex implementation
    - Complex deletion
    """
    
    def __init__(self, size: int = 11):
        """
        Initialize the hash table with double hashing.
        
        Args:
            size (int): The size of the hash table (should be prime for best results)
        """
        self.size = size
        self.table = [None] * size
        self.count = 0
        self.DELETED = "DELETED"
    
    def _hash1(self, key: Any) -> int:
        """
        Primary hash function.
        
        Args:
            key: The key to hash
            
        Returns:
            int: Primary hash value
        """
        return abs(hash(key)) % self.size
    
    def _hash2(self, key: Any) -> int:
        """
        Secondary hash function for step size.
        
        This function should:
        - Never return 0 (to avoid infinite loops)
        - Be relatively prime to table size
        - Provide good distribution
        
        Args:
            key: The key to hash
            
        Returns:
            int: Step size for probing
        """
        # Use a different hash function and ensure result is relatively prime to size
        step = 7 - (abs(hash(key)) % 7)  # Returns 1-7, relatively prime to most sizes
        return step
    
    def insert(self, key: Any, value: Any) -> bool:
        """
        Insert a key-value pair using double hashing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully, False if table is full
        """
        if self.count >= self.size:
            return False  # Table is full
        
        index = self._hash1(key)
        step = self._hash2(key)
        original_index = index
        
        # Double hashing: h1(key) + i * h2(key)
        while self.table[index] is not None and self.table[index] != self.DELETED:
            # Check if this is the same key (update case)
            if isinstance(self.table[index], tuple) and self.table[index][0] == key:
                self.table[index] = (key, value)  # Update existing key
                return True
            
            index = (index + step) % self.size
            
            # Check if we've wrapped around (table is full)
            if index == original_index:
                return False
        
        # Found empty slot or deleted slot
        self.table[index] = (key, value)
        self.count += 1
        return True
    
    def search(self, key: Any) -> Optional[Any]:
        """
        Search for a key using double hashing.
        
        Time Complexity: O(1) average case, O(n) worst case
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if not found
        """
        index = self._hash1(key)
        step = self._hash2(key)
        original_index = index
        
        # Double hashing: search for the key
        while self.table[index] is not None:
            # Check if this is the key we're looking for
            if (isinstance(self.table[index], tuple) and 
                self.table[index] != self.DELETED and 
                self.table[index][0] == key):
                return self.table[index][1]
            
            index = (index + step) % self.size
            
            # Stop if we've wrapped around
            if index == original_index:
                break
        
        return None  # Key not found
    
    def load_factor(self) -> float:
        """Calculate the current load factor."""
        return self.count / self.size
    
    def display(self) -> None:
        """Display the current state of the hash table."""
        print(f"Double Hashing Hash Table (Size: {self.size}, Elements: {self.count}, Load Factor: {self.load_factor():.3f})")
        print("-" * 60)
        
        for i, item in enumerate(self.table):
            if item is not None:
                if item == self.DELETED:
                    print(f"Index {i}: [DELETED]")
                else:
                    print(f"Index {i}: {item}")
        
        print("-" * 60)


def demonstrate_collision_resolution():
    """
    Demonstrate different collision resolution strategies with the same data.
    This shows how different methods handle collisions and their trade-offs.
    """
    print("=== Collision Resolution Strategies Demonstration ===\n")
    
    # Test data designed to cause collisions
    test_data = [
        ("apple", 5),
        ("banana", 3),
        ("cherry", 8),
        ("date", 2),
        ("elderberry", 7),
        ("fig", 4),
        ("grape", 6),
        ("honeydew", 9),
        ("kiwi", 1),
        ("lemon", 10),
        ("mango", 11),
        ("orange", 12)
    ]
    
    # Create different hash table implementations
    tables = {
        "Separate Chaining": SeparateChainingHashTable(11),
        "Linear Probing": LinearProbingHashTable(11),
        "Quadratic Probing": QuadraticProbingHashTable(11),
        "Double Hashing": DoubleHashingHashTable(11)
    }
    
    # Insert data into all tables
    print("Inserting data into all hash tables:")
    for key, value in test_data:
        print(f"Inserting: {key} -> {value}")
        for name, table in tables.items():
            success = table.insert(key, value)
            if not success:
                print(f"  Warning: {name} failed to insert {key}")
    
    print("\n" + "="*70)
    
    # Display all tables
    for name, table in tables.items():
        print(f"\n{name}:")
        table.display()
    
    # Test search operations
    print("\n" + "="*70)
    print("Testing search operations:")
    search_keys = ["apple", "banana", "kiwi", "grape", "watermelon"]
    
    for key in search_keys:
        print(f"\nSearching for '{key}':")
        for name, table in tables.items():
            value = table.search(key)
            if value is not None:
                print(f"  {name}: Found -> {value}")
            else:
                print(f"  {name}: Not found")


def performance_comparison():
    """
    Compare the performance of different collision resolution strategies.
    This demonstrates the practical implications of each approach.
    """
    print("\n=== Performance Comparison ===\n")
    
    import random
    import time
    
    # Generate test data
    num_items = 1000
    test_data = [(f"key_{i}", f"value_{i}") for i in range(num_items)]
    
    # Shuffle data to simulate random insertion order
    random.shuffle(test_data)
    
    # Create hash tables
    tables = {
        "Separate Chaining": SeparateChainingHashTable(1000),
        "Linear Probing": LinearProbingHashTable(1000),
        "Quadratic Probing": QuadraticProbingHashTable(1000),
        "Double Hashing": DoubleHashingHashTable(1000)
    }
    
    # Test insertion performance
    print("Insertion Performance:")
    for name, table in tables.items():
        start_time = time.time()
        
        for key, value in test_data:
            table.insert(key, value)
        
        end_time = time.time()
        insertion_time = end_time - start_time
        
        print(f"  {name}: {insertion_time:.6f} seconds (Load Factor: {table.load_factor():.3f})")
    
    # Test search performance
    print("\nSearch Performance:")
    search_keys = [f"key_{i}" for i in range(0, num_items, 10)]  # Search every 10th key
    
    for name, table in tables.items():
        start_time = time.time()
        
        for key in search_keys:
            table.search(key)
        
        end_time = time.time()
        search_time = end_time - start_time
        
        print(f"  {name}: {search_time:.6f} seconds")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will demonstrate:
    1. Different collision resolution strategies
    2. Performance comparison
    3. Trade-offs between different approaches
    """
    
    # Run demonstrations
    demonstrate_collision_resolution()
    performance_comparison()
    
    print("\n" + "="*70)
    print("EDUCATIONAL NOTES:")
    print("="*70)
    print("1. Collision Resolution Strategy Comparison:")
    print("   - Separate Chaining: Simple, no clustering, but uses extra memory")
    print("   - Linear Probing: Cache-friendly, but suffers from primary clustering")
    print("   - Quadratic Probing: Reduces primary clustering, but has secondary clustering")
    print("   - Double Hashing: Best distribution, but requires two hash functions")
    print()
    print("2. Performance Characteristics:")
    print("   - All methods provide O(1) average-case performance")
    print("   - Performance degrades as load factor approaches 1.0")
    print("   - Deletion is complex in open addressing methods")
    print()
    print("3. When to Use Each Method:")
    print("   - Separate Chaining: When memory is not a concern, unknown data patterns")
    print("   - Linear Probing: When cache performance is important, small tables")
    print("   - Quadratic Probing: When you want to reduce clustering")
    print("   - Double Hashing: When you need best possible distribution")
    print()
    print("4. Best Practices:")
    print("   - Keep load factor below 0.7 for open addressing methods")
    print("   - Use prime table sizes for better distribution")
    print("   - Monitor performance and consider rehashing when needed")
    print("   - Choose method based on your specific requirements")
