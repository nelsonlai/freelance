"""
Advanced Hashing Techniques
===========================

This file demonstrates advanced hashing techniques used in modern systems:
- Cuckoo Hashing
- Bloom Filters
- Consistent Hashing
- Perfect Hashing concepts
- Universal Hashing

These techniques address specific challenges in distributed systems,
probabilistic data structures, and performance optimization.

Author: Hash Lecture Series
Purpose: Educational demonstration of advanced hashing methods
"""

import hashlib
import math
import random
import bisect
from typing import Any, List, Set, Optional, Tuple


class CuckooHashTable:
    """
    Cuckoo Hashing Implementation
    
    Cuckoo hashing uses two hash tables and two hash functions.
    When a collision occurs, it "kicks out" the existing element
    and tries to place it in the other table.
    
    Advantages:
    - O(1) worst-case lookup time
    - No clustering issues
    - Simple deletion
    
    Disadvantages:
    - Complex insertion (may require rehashing)
    - Requires two hash functions
    - May fail if cycles occur
    """
    
    def __init__(self, size: int = 10):
        """
        Initialize the cuckoo hash table.
        
        Args:
            size (int): The size of each hash table
        """
        self.size = size
        self.table1 = [None] * size
        self.table2 = [None] * size
        self.max_attempts = size  # Prevent infinite loops
    
    def _hash1(self, key: Any) -> int:
        """
        First hash function.
        
        Args:
            key: The key to hash
            
        Returns:
            int: Index in first table
        """
        return abs(hash(key)) % self.size
    
    def _hash2(self, key: Any) -> int:
        """
        Second hash function.
        
        Args:
            key: The key to hash
            
        Returns:
            int: Index in second table
        """
        # Use a different hash function to ensure different distribution
        return abs(hash(str(key) + "salt")) % self.size
    
    def _find(self, key: Any) -> Tuple[Optional[int], int]:
        """
        Find a key in either table.
        
        Args:
            key: The key to find
            
        Returns:
            Tuple of (table_index, position) or (None, -1) if not found
        """
        # Check table 1
        index1 = self._hash1(key)
        if self.table1[index1] is not None and self.table1[index1][0] == key:
            return 1, index1
        
        # Check table 2
        index2 = self._hash2(key)
        if self.table2[index2] is not None and self.table2[index2][0] == key:
            return 2, index2
        
        return None, -1
    
    def insert(self, key: Any, value: Any) -> bool:
        """
        Insert a key-value pair using cuckoo hashing.
        
        Args:
            key: The key to insert
            value: The value associated with the key
            
        Returns:
            bool: True if inserted successfully, False if failed
        """
        # Check if key already exists
        table_num, index = self._find(key)
        if table_num is not None:
            # Update existing key
            if table_num == 1:
                self.table1[index] = (key, value)
            else:
                self.table2[index] = (key, value)
            return True
        
        # Try to insert in table 1 first
        index1 = self._hash1(key)
        if self.table1[index1] is None:
            self.table1[index1] = (key, value)
            return True
        
        # Try to insert in table 2
        index2 = self._hash2(key)
        if self.table2[index2] is None:
            self.table2[index2] = (key, value)
            return True
        
        # Both positions are occupied, start cuckoo process
        current_key, current_value = key, value
        current_table = 1
        
        for attempt in range(self.max_attempts):
            if current_table == 1:
                # Try to place in table 1
                index = self._hash1(current_key)
                if self.table1[index] is None:
                    self.table1[index] = (current_key, current_value)
                    return True
                
                # Kick out existing element
                evicted_key, evicted_value = self.table1[index]
                self.table1[index] = (current_key, current_value)
                current_key, current_value = evicted_key, evicted_value
                current_table = 2
            
            else:
                # Try to place in table 2
                index = self._hash2(current_key)
                if self.table2[index] is None:
                    self.table2[index] = (current_key, current_value)
                    return True
                
                # Kick out existing element
                evicted_key, evicted_value = self.table2[index]
                self.table2[index] = (current_key, current_value)
                current_key, current_value = evicted_key, evicted_value
                current_table = 1
        
        # Failed to insert after max attempts
        return False
    
    def search(self, key: Any) -> Optional[Any]:
        """
        Search for a key in the cuckoo hash table.
        
        Args:
            key: The key to search for
            
        Returns:
            The value associated with the key, or None if not found
        """
        table_num, index = self._find(key)
        if table_num == 1:
            return self.table1[index][1]
        elif table_num == 2:
            return self.table2[index][1]
        else:
            return None
    
    def delete(self, key: Any) -> bool:
        """
        Delete a key from the cuckoo hash table.
        
        Args:
            key: The key to delete
            
        Returns:
            bool: True if key was found and deleted, False otherwise
        """
        table_num, index = self._find(key)
        if table_num == 1:
            self.table1[index] = None
            return True
        elif table_num == 2:
            self.table2[index] = None
            return True
        else:
            return False
    
    def display(self) -> None:
        """Display the current state of both tables."""
        print("Cuckoo Hash Table:")
        print("Table 1:", self.table1)
        print("Table 2:", self.table2)


class BloomFilter:
    """
    Bloom Filter Implementation
    
    A Bloom filter is a space-efficient probabilistic data structure
    that tests whether an element is a member of a set.
    
    Properties:
    - May produce false positives (says element is in set when it's not)
    - Never produces false negatives (says element is not in set when it is)
    - Space efficient
    - Fast insertions and lookups
    
    Applications:
    - Spell checkers
    - Network routers
    - Databases (to avoid expensive disk lookups)
    - Web crawlers (to avoid revisiting URLs)
    """
    
    def __init__(self, size: int, num_hashes: int):
        """
        Initialize the Bloom filter.
        
        Args:
            size (int): The size of the bit array
            num_hashes (int): The number of hash functions to use
        
        Note: The optimal number of hash functions is:
              k = (size / num_elements) * ln(2)
        """
        self.size = size
        self.num_hashes = num_hashes
        self.bit_array = [False] * size
        self.count = 0  # Number of elements inserted
    
    def _hash(self, item: Any, seed: int) -> int:
        """
        Generate a hash value for an item with a given seed.
        
        Args:
            item: The item to hash
            seed: The seed for this hash function
            
        Returns:
            int: Hash value between 0 and size-1
        """
        # Create a hash using MD5 with seed
        hasher = hashlib.md5()
        hasher.update(f"{item}{seed}".encode())
        return int(hasher.hexdigest(), 16) % self.size
    
    def add(self, item: Any) -> None:
        """
        Add an item to the Bloom filter.
        
        Args:
            item: The item to add to the set
        """
        for i in range(self.num_hashes):
            index = self._hash(item, i)
            self.bit_array[index] = True
        
        self.count += 1
    
    def contains(self, item: Any) -> bool:
        """
        Check if an item might be in the set.
        
        Args:
            item: The item to check
            
        Returns:
            bool: True if item might be in set (could be false positive),
                  False if item is definitely not in set
        """
        for i in range(self.num_hashes):
            index = self._hash(item, i)
            if not self.bit_array[index]:
                return False  # Definitely not in set
        
        return True  # Might be in set (could be false positive)
    
    def false_positive_rate(self) -> float:
        """
        Calculate the theoretical false positive rate.
        
        Returns:
            float: The probability of a false positive
        """
        if self.count == 0:
            return 0.0
        
        # Formula: (1 - e^(-k*n/m))^k
        # where k = num_hashes, n = count, m = size
        exponent = -(self.num_hashes * self.count) / self.size
        return (1 - math.exp(exponent)) ** self.num_hashes
    
    def display_stats(self) -> None:
        """Display Bloom filter statistics."""
        bits_set = sum(self.bit_array)
        print(f"Bloom Filter Statistics:")
        print(f"  Size: {self.size}")
        print(f"  Hash functions: {self.num_hashes}")
        print(f"  Elements added: {self.count}")
        print(f"  Bits set: {bits_set}")
        print(f"  False positive rate: {self.false_positive_rate():.4f}")


class ConsistentHashRing:
    """
    Consistent Hashing Implementation
    
    Consistent hashing is used in distributed systems to minimize
    the number of keys that need to be remapped when servers are
    added or removed.
    
    Applications:
    - Load balancing
    - Distributed caching
    - Database sharding
    - CDN routing
    
    Properties:
    - Minimal remapping when nodes are added/removed
    - Load balancing across nodes
    - Fault tolerance
    """
    
    def __init__(self, nodes: Optional[List[str]] = None, replicas: int = 3):
        """
        Initialize the consistent hash ring.
        
        Args:
            nodes: List of node identifiers
            replicas: Number of virtual nodes per physical node
        """
        self.replicas = replicas
        self.ring = {}  # hash_value -> node
        self.sorted_keys = []  # Sorted list of hash values
        
        if nodes:
            for node in nodes:
                self.add_node(node)
    
    def _hash(self, key: str) -> int:
        """
        Generate a hash value for a key.
        
        Args:
            key: The key to hash
            
        Returns:
            int: Hash value
        """
        return int(hashlib.md5(key.encode()).hexdigest(), 16)
    
    def add_node(self, node: str) -> None:
        """
        Add a node to the hash ring.
        
        Args:
            node: The node identifier to add
        """
        for i in range(self.replicas):
            # Create virtual node
            virtual_node = f"{node}:{i}"
            key = self._hash(virtual_node)
            
            self.ring[key] = node
            self.sorted_keys.append(key)
        
        # Keep keys sorted for efficient lookup
        self.sorted_keys.sort()
    
    def remove_node(self, node: str) -> None:
        """
        Remove a node from the hash ring.
        
        Args:
            node: The node identifier to remove
        """
        keys_to_remove = []
        
        for key, ring_node in self.ring.items():
            if ring_node == node:
                keys_to_remove.append(key)
        
        for key in keys_to_remove:
            del self.ring[key]
            self.sorted_keys.remove(key)
    
    def get_node(self, item: str) -> Optional[str]:
        """
        Get the node responsible for an item.
        
        Args:
            item: The item to find a node for
            
        Returns:
            str: The node responsible for the item, or None if no nodes
        """
        if not self.ring:
            return None
        
        key = self._hash(item)
        
        # Find the first node with hash >= item's hash
        index = bisect.bisect_right(self.sorted_keys, key)
        
        if index == len(self.sorted_keys):
            # Wrap around to first node
            index = 0
        
        return self.ring[self.sorted_keys[index]]
    
    def get_nodes(self, item: str, count: int = 1) -> List[str]:
        """
        Get multiple nodes responsible for an item (for replication).
        
        Args:
            item: The item to find nodes for
            count: Number of nodes to return
            
        Returns:
            List of node identifiers
        """
        if not self.ring:
            return []
        
        key = self._hash(item)
        nodes = []
        visited = set()
        
        # Find the first node
        index = bisect.bisect_right(self.sorted_keys, key)
        if index == len(self.sorted_keys):
            index = 0
        
        # Collect unique nodes
        while len(nodes) < count and len(visited) < len(self.ring):
            node_key = self.sorted_keys[index]
            node = self.ring[node_key]
            
            if node not in visited:
                nodes.append(node)
                visited.add(node)
            
            index = (index + 1) % len(self.sorted_keys)
        
        return nodes
    
    def display(self) -> None:
        """Display the hash ring."""
        print(f"Consistent Hash Ring ({len(self.ring)} virtual nodes):")
        for key in sorted(self.ring.keys()):
            print(f"  {key:10d} -> {self.ring[key]}")


def demonstrate_cuckoo_hashing():
    """
    Demonstrate cuckoo hashing with examples.
    """
    print("=== Cuckoo Hashing Demonstration ===\n")
    
    cuckoo_ht = CuckooHashTable(size=8)
    
    # Test data
    test_data = [
        ("apple", 1), ("banana", 2), ("cherry", 3), ("date", 4),
        ("elderberry", 5), ("fig", 6), ("grape", 7), ("honeydew", 8)
    ]
    
    print("Inserting elements:")
    for key, value in test_data:
        success = cuckoo_ht.insert(key, value)
        print(f"Inserted '{key}' -> {value}: {'Success' if success else 'Failed'}")
    
    cuckoo_ht.display()
    
    print("\nSearching for elements:")
    search_keys = ["apple", "banana", "kiwi", "grape"]
    for key in search_keys:
        value = cuckoo_ht.search(key)
        if value is not None:
            print(f"Found '{key}': {value}")
        else:
            print(f"Not found: '{key}'")
    
    print("\nDeleting 'banana':")
    if cuckoo_ht.delete("banana"):
        print("Successfully deleted 'banana'")
    
    print("\nFinal state:")
    cuckoo_ht.display()


def demonstrate_bloom_filter():
    """
    Demonstrate Bloom filter with examples.
    """
    print("\n=== Bloom Filter Demonstration ===\n")
    
    # Create Bloom filter
    bloom = BloomFilter(size=1000, num_hashes=3)
    
    # Add some words
    words = ["hello", "world", "python", "hashing", "bloom", "filter", "data", "structure"]
    
    print("Adding words to Bloom filter:")
    for word in words:
        bloom.add(word)
        print(f"Added: {word}")
    
    bloom.display_stats()
    
    # Test membership
    print(f"\nTesting membership:")
    test_words = ["hello", "world", "java", "python", "c++", "bloom", "algorithm"]
    
    for word in test_words:
        result = bloom.contains(word)
        actual_in_set = word in words
        print(f"'{word}': {result} (Actually in set: {actual_in_set}) {'✓' if result == actual_in_set else '✗ (False Positive)'}")


def demonstrate_consistent_hashing():
    """
    Demonstrate consistent hashing with examples.
    """
    print("\n=== Consistent Hashing Demonstration ===\n")
    
    # Create hash ring with some servers
    servers = ["server1", "server2", "server3"]
    ring = ConsistentHashRing(servers, replicas=3)
    
    print("Initial hash ring:")
    ring.display()
    
    # Test key assignment
    print(f"\nTesting key assignment:")
    test_keys = ["user1", "user2", "user3", "user4", "user5", "user6", "user7", "user8"]
    
    for key in test_keys:
        server = ring.get_node(key)
        print(f"'{key}' -> {server}")
    
    # Show load distribution
    print(f"\nLoad distribution:")
    server_counts = {}
    for key in test_keys:
        server = ring.get_node(key)
        server_counts[server] = server_counts.get(server, 0) + 1
    
    for server, count in server_counts.items():
        print(f"{server}: {count} keys")
    
    # Add a new server
    print(f"\nAdding server4...")
    ring.add_node("server4")
    
    print(f"\nKey assignment after adding server4:")
    for key in test_keys:
        server = ring.get_node(key)
        print(f"'{key}' -> {server}")
    
    # Remove a server
    print(f"\nRemoving server2...")
    ring.remove_node("server2")
    
    print(f"\nKey assignment after removing server2:")
    for key in test_keys:
        server = ring.get_node(key)
        print(f"'{key}' -> {server}")


def analyze_bloom_filter_performance():
    """
    Analyze Bloom filter performance with different parameters.
    """
    print("\n=== Bloom Filter Performance Analysis ===\n")
    
    # Test different configurations
    configurations = [
        (1000, 3, 100),
        (1000, 5, 100),
        (2000, 3, 100),
        (1000, 3, 200),
    ]
    
    for size, num_hashes, num_elements in configurations:
        print(f"Configuration: size={size}, hashes={num_hashes}, elements={num_elements}")
        
        bloom = BloomFilter(size, num_hashes)
        
        # Add elements
        for i in range(num_elements):
            bloom.add(f"item_{i}")
        
        # Test false positives
        false_positives = 0
        tests = 1000
        
        for i in range(tests):
            test_item = f"test_{i}"
            if bloom.contains(test_item):  # This should always be False
                false_positives += 1
        
        actual_fp_rate = false_positives / tests
        theoretical_fp_rate = bloom.false_positive_rate()
        
        print(f"  Theoretical FP rate: {theoretical_fp_rate:.4f}")
        print(f"  Actual FP rate: {actual_fp_rate:.4f}")
        print(f"  Difference: {abs(theoretical_fp_rate - actual_fp_rate):.4f}")
        print()


def demonstrate_universal_hashing():
    """
    Demonstrate universal hashing concept.
    """
    print("\n=== Universal Hashing Demonstration ===\n")
    
    class UniversalHashFamily:
        """
        A simple universal hash family for demonstration.
        """
        
        def __init__(self, table_size: int, num_hashes: int = 100):
            self.table_size = table_size
            self.num_hashes = num_hashes
            # Generate random hash functions
            self.hash_functions = []
            for _ in range(num_hashes):
                a = random.randint(1, table_size - 1)
                b = random.randint(0, table_size - 1)
                self.hash_functions.append((a, b))
        
        def hash(self, key: Any, function_index: int) -> int:
            """
            Hash a key using a specific hash function.
            
            Args:
                key: The key to hash
                function_index: Index of the hash function to use
                
            Returns:
                int: Hash value
            """
            a, b = self.hash_functions[function_index]
            key_int = abs(hash(key))
            return (a * key_int + b) % self.table_size
    
    # Test universal hashing
    table_size = 11
    num_functions = 10
    universal_hash = UniversalHashFamily(table_size, num_functions)
    
    test_keys = ["key1", "key2", "key3", "key4", "key5"]
    
    print("Universal hash family demonstration:")
    print("Key".ljust(10), end="")
    for i in range(num_functions):
        print(f"Hash{i}".ljust(8), end="")
    print()
    
    print("-" * (10 + 8 * num_functions))
    
    for key in test_keys:
        print(f"{key.ljust(10)}", end="")
        for i in range(num_functions):
            hash_value = universal_hash.hash(key, i)
            print(f"{hash_value}".ljust(8), end="")
        print()
    
    print("\nNote: Universal hashing provides good distribution")
    print("across different hash functions, reducing worst-case behavior.")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will demonstrate:
    1. Cuckoo hashing
    2. Bloom filters
    3. Consistent hashing
    4. Universal hashing
    """
    
    # Run all demonstrations
    demonstrate_cuckoo_hashing()
    demonstrate_bloom_filter()
    demonstrate_consistent_hashing()
    analyze_bloom_filter_performance()
    demonstrate_universal_hashing()
    
    print("\n" + "="*70)
    print("EDUCATIONAL NOTES:")
    print("="*70)
    print("1. Cuckoo Hashing:")
    print("   - Provides O(1) worst-case lookup time")
    print("   - Uses two hash tables and two hash functions")
    print("   - May require rehashing if insertion fails")
    print("   - Good for applications requiring guaranteed performance")
    print()
    print("2. Bloom Filters:")
    print("   - Space-efficient probabilistic data structure")
    print("   - May have false positives, never false negatives")
    print("   - Useful for pre-filtering expensive operations")
    print("   - False positive rate depends on size and number of hash functions")
    print()
    print("3. Consistent Hashing:")
    print("   - Minimizes remapping when nodes are added/removed")
    print("   - Essential for distributed systems")
    print("   - Provides load balancing and fault tolerance")
    print("   - Used in CDNs, databases, and caching systems")
    print()
    print("4. Universal Hashing:")
    print("   - Randomly selects hash function from a family")
    print("   - Reduces worst-case behavior")
    print("   - Provides good average-case performance")
    print("   - Useful when input distribution is unknown")
    print()
    print("5. When to Use Each Technique:")
    print("   - Cuckoo: When you need guaranteed O(1) performance")
    print("   - Bloom Filter: When you can tolerate false positives")
    print("   - Consistent Hashing: In distributed systems")
    print("   - Universal Hashing: When input patterns are unknown")
