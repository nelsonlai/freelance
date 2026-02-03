"""
Basic Hash Table Implementation
==============================

This file demonstrates the fundamental concepts of hash tables:
- Hash function design
- Collision handling with separate chaining
- Basic operations: insert, search, delete
- Load factor calculation

Author: Hash Lecture Series
Purpose: Educational demonstration of hash table fundamentals
"""

class SimpleHashTable:
    """
    A simple hash table implementation using separate chaining for collision resolution.
    
    This class demonstrates the core concepts of hash tables:
    - Mapping keys to array indices using hash functions
    - Handling collisions by storing multiple items at the same index
    - Basic operations with O(1) average-case performance
    """
    
    def __init__(self, size=10):
        """
        Initialize the hash table.
        
        Args:
            size (int): The initial size of the hash table array.
                       Using a prime number helps with distribution.
        
        Time Complexity: O(n) where n is the table size
        Space Complexity: O(n) where n is the table size
        """
        self.size = size
        # Create a list of empty lists - each index will hold a chain of key-value pairs
        self.table = [[] for _ in range(size)]
        self.count = 0  # Track number of elements for load factor calculation
    
    def hash_function(self, key):
        """
        Hash function that maps keys to array indices.
        
        This is a simple modulo hash function. In practice, you might use
        more sophisticated hash functions depending on your data.
        
        Args:
            key: The key to hash (can be string, int, etc.)
            
        Returns:
            int: Array index between 0 and self.size - 1
            
        Time Complexity: O(1) for most data types
        """
        # Use Python's built-in hash function, then take modulo
        # The abs() ensures we get a positive index even if hash() returns negative
        return abs(hash(key)) % self.size
    
    def insert(self, key, value):
        """
        Insert a key-value pair into the hash table.
        
        If the key already exists, update its value.
        If there's a collision, add to the chain at that index.
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Time Complexity: O(1 + α) where α is the load factor
                         In the worst case O(n) if all keys hash to same index
        """
        index = self.hash_function(key)
        
        # Check if key already exists in the chain
        for i, (existing_key, existing_value) in enumerate(self.table[index]):
            if existing_key == key:
                # Update existing key-value pair
                self.table[index][i] = (key, value)
                return
        
        # Key doesn't exist, add new key-value pair to the chain
        self.table[index].append((key, value))
        self.count += 1
    
    def get(self, key):
        """
        Retrieve the value associated with a key.
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if key not found
            
        Time Complexity: O(1 + α) where α is the load factor
        """
        index = self.hash_function(key)
        
        # Search through the chain at the calculated index
        for existing_key, value in self.table[index]:
            if existing_key == key:
                return value
        
        # Key not found
        return None
    
    def delete(self, key):
        """
        Remove a key-value pair from the hash table.
        
        Args:
            key: The key to remove
            
        Returns:
            bool: True if key was found and removed, False otherwise
            
        Time Complexity: O(1 + α) where α is the load factor
        """
        index = self.hash_function(key)
        
        # Search for the key in the chain and remove it
        for i, (existing_key, existing_value) in enumerate(self.table[index]):
            if existing_key == key:
                del self.table[index][i]  # Remove the key-value pair
                self.count -= 1
                return True
        
        # Key not found
        return False
    
    def contains(self, key):
        """
        Check if a key exists in the hash table.
        
        Args:
            key: The key to check for
            
        Returns:
            bool: True if key exists, False otherwise
            
        Time Complexity: O(1 + α) where α is the load factor
        """
        return self.get(key) is not None
    
    def load_factor(self):
        """
        Calculate the current load factor of the hash table.
        
        Load factor = number of elements / table size
        A high load factor (>1.0) indicates many collisions and poor performance.
        
        Returns:
            float: Current load factor
            
        Time Complexity: O(1)
        """
        return self.count / self.size
    
    def display(self):
        """
        Display the current state of the hash table.
        Useful for debugging and understanding how keys are distributed.
        
        Time Complexity: O(n) where n is the number of elements
        """
        print(f"Hash Table (Size: {self.size}, Elements: {self.count}, Load Factor: {self.load_factor():.3f})")
        print("-" * 50)
        
        for i, chain in enumerate(self.table):
            if chain:  # Only show non-empty chains
                print(f"Index {i}: {chain}")
        
        print("-" * 50)


def demonstrate_basic_hash_table():
    """
    Demonstrate the basic hash table operations with detailed output.
    This function shows how keys are distributed and how collisions are handled.
    """
    print("=== Basic Hash Table Demonstration ===\n")
    
    # Create a hash table with size 7 to demonstrate collisions
    ht = SimpleHashTable(7)
    
    # Test data with known hash values to show collisions
    test_data = [
        ("apple", 5),
        ("banana", 3),
        ("cherry", 8),
        ("date", 2),
        ("elderberry", 7),
        ("fig", 4),
        ("grape", 6),
        ("honeydew", 9),
        ("apple", 10),  # This should update the existing "apple" entry
    ]
    
    print("Inserting key-value pairs:")
    for key, value in test_data:
        print(f"Inserting: {key} -> {value}")
        ht.insert(key, value)
        print(f"Load factor: {ht.load_factor():.3f}")
    
    print("\n" + "="*50)
    ht.display()
    
    print("\nSearching for keys:")
    search_keys = ["apple", "banana", "kiwi", "grape"]
    for key in search_keys:
        value = ht.get(key)
        if value is not None:
            print(f"Found {key}: {value}")
        else:
            print(f"Not found: {key}")
    
    print(f"\nChecking if 'cherry' exists: {ht.contains('cherry')}")
    print(f"Checking if 'kiwi' exists: {ht.contains('kiwi')}")
    
    print("\nDeleting 'banana':")
    if ht.delete("banana"):
        print("Successfully deleted 'banana'")
    else:
        print("Failed to delete 'banana'")
    
    print(f"Checking if 'banana' exists after deletion: {ht.contains('banana')}")
    
    print("\n" + "="*50)
    print("Final hash table state:")
    ht.display()


def analyze_hash_distribution():
    """
    Analyze how well our hash function distributes keys.
    This helps students understand the importance of good hash functions.
    """
    print("\n=== Hash Distribution Analysis ===\n")
    
    ht = SimpleHashTable(10)
    
    # Test with different types of keys
    test_keys = [
        "hello", "world", "python", "hashing", "algorithm",
        123, 456, 789, 101112, 131415,
        ("tuple", 1), ("tuple", 2), ("tuple", 3),
        [1, 2, 3], [4, 5, 6], [7, 8, 9]  # Note: lists are not hashable!
    ]
    
    print("Testing hash distribution:")
    hash_counts = {}  # Count how many keys hash to each index
    
    for key in test_keys:
        try:
            index = ht.hash_function(key)
            hash_counts[index] = hash_counts.get(index, 0) + 1
            print(f"Key: {key} -> Index: {index}")
        except TypeError as e:
            print(f"Key: {key} -> Error: {e}")
    
    print(f"\nHash distribution:")
    for index in range(ht.size):
        count = hash_counts.get(index, 0)
        print(f"Index {index}: {count} keys")
    
    # Calculate distribution quality
    total_keys = sum(hash_counts.values())
    expected_per_index = total_keys / ht.size
    variance = sum((count - expected_per_index) ** 2 for count in hash_counts.values()) / ht.size
    
    print(f"\nDistribution Analysis:")
    print(f"Total keys: {total_keys}")
    print(f"Expected keys per index: {expected_per_index:.2f}")
    print(f"Variance: {variance:.2f} (lower is better)")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will:
    1. Demonstrate basic hash table operations
    2. Show hash distribution analysis
    3. Provide educational output for students
    """
    # Run the demonstrations
    demonstrate_basic_hash_table()
    analyze_hash_distribution()
    
    print("\n" + "="*60)
    print("EDUCATIONAL NOTES:")
    print("="*60)
    print("1. Hash tables provide O(1) average-case performance for search, insert, delete")
    print("2. The quality of the hash function directly affects performance")
    print("3. Collisions are inevitable - good collision resolution is crucial")
    print("4. Load factor affects performance - consider rehashing when it gets too high")
    print("5. Separate chaining is simple but uses extra memory for pointers/chains")
    print("6. Hash tables work best when keys are distributed uniformly")
