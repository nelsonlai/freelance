# Hashing – Lecture

## 🎯 Learning Objectives
- Understand the concept of hashing and why it is essential in computer science
- Learn how to design robust hash functions for different data types
- Explore collision resolution strategies: separate chaining, linear probing, quadratic probing, double hashing
- Understand rehashing, load factors, and performance optimization
- Apply hashing in real-world scenarios: NLP, cybersecurity, databases, and caching
- Recognize security implications and best practices for hash functions

---

## 0. Introduction to Hashing (10 min)

### Why Hashing Matters
- **Performance**: Achieves O(1) average-case time for insert, delete, and search operations
- **Versatility**: Works with any data type that can be converted to a hash
- **Widespread Use**: Found in databases, caches, compilers, cryptography, and modern applications

### Real-World Motivation
Consider these scenarios where hashing is crucial:
- **Password Security**: Storing hashed passwords instead of plain text
- **Natural Language Processing**: Building word embeddings and similarity detection
- **Cybersecurity**: Malware detection using file hashes
- **Database Indexing**: Fast record retrieval by key
- **Web Caching**: Browser cache management

---

## 1. Fundamentals of Hash Tables (15 min)

### Core Concepts
- **Hash Table**: A data structure combining an array with a hash function
- **Hash Function**: Maps keys to array indices in range `[0, TableSize-1]`
- **Collision**: When different keys map to the same array index

### Hash Function Requirements
1. **Deterministic**: Same input always produces same output
2. **Uniform Distribution**: Keys should be evenly distributed across the table
3. **Fast Computation**: Should be O(1) or O(k) where k is key length
4. **Minimal Collisions**: Reduces performance degradation

### Python Example: Basic Hash Table
```python
class SimpleHashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size
        self.count = 0
    
    def hash_function(self, key):
        """Simple hash function using modulo"""
        return hash(key) % self.size
    
    def insert(self, key, value):
        """Insert key-value pair"""
        index = self.hash_function(key)
        if self.table[index] is None:
            self.table[index] = [(key, value)]
        else:
            # Handle collision with chaining
            self.table[index].append((key, value))
        self.count += 1
    
    def get(self, key):
        """Retrieve value by key"""
        index = self.hash_function(key)
        if self.table[index] is not None:
            for k, v in self.table[index]:
                if k == key:
                    return v
        return None

# Example usage
ht = SimpleHashTable()
ht.insert("apple", 5)
ht.insert("banana", 3)
print(f"Apple count: {ht.get('apple')}")  # Output: Apple count: 5
```

---

## 2. Advanced Hash Functions (20 min)

### Hash Function Design Principles
- **Uniformity**: Distribute keys evenly across the hash table
- **Determinism**: Same input always produces same output
- **Efficiency**: Fast computation for good performance
- **Avalanche Effect**: Small changes in input cause large changes in output

### Hash Function Types

#### 1. Division Method (Modulo Hashing)
```python
def division_hash(key, table_size):
    """Simple division method - best when table_size is prime"""
    return key % table_size

# Example with prime table size
table_size = 97  # Prime number
keys = [4371, 1323, 6173, 4199, 4344, 9679, 1989]
hashes = [division_hash(k, table_size) for k in keys]
print(f"Hashes: {hashes}")
```

#### 2. Multiplication Method
```python
def multiplication_hash(key, table_size):
    """Multiplication method for better distribution"""
    import math
    A = (math.sqrt(5) - 1) / 2  # Golden ratio - 1
    return int(table_size * ((key * A) % 1))

print(f"Multiplication hash: {multiplication_hash(12345, 1000)}")
```

#### 3. Polynomial Rolling Hash (Horner's Method)
```python
def polynomial_hash(s, table_size, base=31):
    """Polynomial rolling hash for strings"""
    hash_value = 0
    for char in s:
        hash_value = (hash_value * base + ord(char)) % table_size
    return hash_value

# Example with different strings
strings = ["hello", "world", "python", "hashing"]
for s in strings:
    print(f"'{s}' -> {polynomial_hash(s, 97)}")
```

#### 4. Cryptographic Hash Functions (Python's built-in)
```python
import hashlib

def crypto_hash(data):
    """Cryptographic hash using SHA-256"""
    if isinstance(data, str):
        data = data.encode('utf-8')
    return hashlib.sha256(data).hexdigest()

# Example usage
print(f"SHA-256 of 'hello': {crypto_hash('hello')}")
print(f"SHA-256 of 'Hello': {crypto_hash('Hello')}")  # Different output
```

### Custom Hash Functions for Special Cases

#### Hash Function for Tuples
```python
def tuple_hash(t, table_size):
    """Hash function for tuples"""
    hash_value = 0
    for item in t:
        if isinstance(item, str):
            hash_value = (hash_value + polynomial_hash(item, table_size)) % table_size
        else:
            hash_value = (hash_value + hash(item)) % table_size
    return hash_value

# Example
coordinates = [(1, 2), (3, 4), (1, 2)]  # Note: (1,2) appears twice
for coord in coordinates:
    print(f"Hash of {coord}: {tuple_hash(coord, 10)}")
```

---

## 3. Collision Resolution Strategies (35 min)

### Understanding Collisions
When two keys hash to the same index, we have a collision. The choice of resolution strategy significantly impacts performance.

### 3.1 Separate Chaining (Closed Addressing)

Each table slot contains a linked list (or array) of key-value pairs that hash to the same index.

**Advantages:**
- Simple to implement
- No clustering issues
- Can handle more elements than table size
- Good for unknown data distribution

**Disadvantages:**
- Extra memory for pointers/chains
- Poor cache locality

```python
class SeparateChainingHashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [[] for _ in range(size)]
        self.count = 0
    
    def hash_function(self, key):
        return hash(key) % self.size
    
    def insert(self, key, value):
        index = self.hash_function(key)
        # Check if key already exists
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                self.table[index][i] = (key, value)  # Update existing
                return
        
        # Add new key-value pair
        self.table[index].append((key, value))
        self.count += 1
    
    def get(self, key):
        index = self.hash_function(key)
        for k, v in self.table[index]:
            if k == key:
                return v
        return None
    
    def delete(self, key):
        index = self.hash_function(key)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                del self.table[index][i]
                self.count -= 1
                return True
        return False
    
    def load_factor(self):
        return self.count / self.size

# Example usage
chaining_ht = SeparateChainingHashTable(7)
test_keys = [4371, 1323, 6173, 4199, 4344, 9679, 1989]
for key in test_keys:
    chaining_ht.insert(key, f"value_{key}")

print("Separate Chaining Table:")
for i, chain in enumerate(chaining_ht.table):
    print(f"Index {i}: {chain}")
```

### 3.2 Open Addressing (Probing)

All elements are stored directly in the hash table array. When a collision occurs, we probe for the next available slot.

#### 3.2.1 Linear Probing
Probe sequence: `h(key), h(key)+1, h(key)+2, ..., h(key)+m`

```python
class LinearProbingHashTable:
    def __init__(self, size=11):
        self.size = size
        self.table = [None] * size
        self.count = 0
        self.DELETED = "DELETED"  # Marker for deleted items
    
    def hash_function(self, key):
        return hash(key) % self.size
    
    def insert(self, key, value):
        if self.count >= self.size:
            raise Exception("Hash table is full")
        
        index = self.hash_function(key)
        original_index = index
        
        while self.table[index] is not None and self.table[index] != self.DELETED:
            if self.table[index][0] == key:  # Key already exists
                self.table[index] = (key, value)
                return
            index = (index + 1) % self.size
            if index == original_index:  # Wrapped around
                raise Exception("Hash table is full")
        
        self.table[index] = (key, value)
        self.count += 1
    
    def search(self, key):
        index = self.hash_function(key)
        original_index = index
        
        while self.table[index] is not None:
            if self.table[index] != self.DELETED and self.table[index][0] == key:
                return self.table[index][1]
            index = (index + 1) % self.size
            if index == original_index:
                break
        
        return None
    
    def delete(self, key):
        index = self.hash_function(key)
        original_index = index
        
        while self.table[index] is not None:
            if self.table[index] != self.DELETED and self.table[index][0] == key:
                self.table[index] = self.DELETED
                self.count -= 1
                return True
            index = (index + 1) % self.size
            if index == original_index:
                break
        
        return False

# Example usage
linear_ht = LinearProbingHashTable(11)
for key in test_keys:
    linear_ht.insert(key, f"value_{key}")

print("\nLinear Probing Table:")
for i, item in enumerate(linear_ht.table):
    print(f"Index {i}: {item}")
```

#### 3.2.2 Quadratic Probing
Probe sequence: `h(key), h(key)+1², h(key)+2², h(key)+3², ...`

```python
class QuadraticProbingHashTable:
    def __init__(self, size=11):
        self.size = size
        self.table = [None] * size
        self.count = 0
        self.DELETED = "DELETED"
    
    def hash_function(self, key):
        return hash(key) % self.size
    
    def insert(self, key, value):
        if self.count >= self.size:
            raise Exception("Hash table is full")
        
        index = self.hash_function(key)
        original_index = index
        i = 1
        
        while self.table[index] is not None and self.table[index] != self.DELETED:
            if self.table[index][0] == key:
                self.table[index] = (key, value)
                return
            index = (original_index + i * i) % self.size
            i += 1
            if i > self.size:  # Prevent infinite loop
                raise Exception("Hash table is full")
        
        self.table[index] = (key, value)
        self.count += 1

# Example usage
quadratic_ht = QuadraticProbingHashTable(11)
for key in test_keys:
    quadratic_ht.insert(key, f"value_{key}")

print("\nQuadratic Probing Table:")
for i, item in enumerate(quadratic_ht.table):
    print(f"Index {i}: {item}")
```

#### 3.2.3 Double Hashing
Uses a second hash function to determine the probe step size.

```python
class DoubleHashingHashTable:
    def __init__(self, size=11):
        self.size = size
        self.table = [None] * size
        self.count = 0
        self.DELETED = "DELETED"
    
    def hash_function1(self, key):
        return hash(key) % self.size
    
    def hash_function2(self, key):
        # Second hash function should be relatively prime to table size
        return 7 - (hash(key) % 7)
    
    def insert(self, key, value):
        if self.count >= self.size:
            raise Exception("Hash table is full")
        
        index = self.hash_function1(key)
        step = self.hash_function2(key)
        original_index = index
        
        while self.table[index] is not None and self.table[index] != self.DELETED:
            if self.table[index][0] == key:
                self.table[index] = (key, value)
                return
            index = (index + step) % self.size
            if index == original_index:
                raise Exception("Hash table is full")
        
        self.table[index] = (key, value)
        self.count += 1

# Example usage
double_ht = DoubleHashingHashTable(11)
for key in test_keys:
    double_ht.insert(key, f"value_{key}")

print("\nDouble Hashing Table:")
for i, item in enumerate(double_ht.table):
    print(f"Index {i}: {item}")
```

### Performance Comparison
```python
import time

def performance_test():
    """Compare performance of different collision resolution methods"""
    test_data = [(i, f"value_{i}") for i in range(1000)]
    
    # Test separate chaining
    start = time.time()
    chaining_ht = SeparateChainingHashTable(1000)
    for key, value in test_data:
        chaining_ht.insert(key, value)
    chaining_time = time.time() - start
    
    # Test linear probing
    start = time.time()
    linear_ht = LinearProbingHashTable(1000)
    for key, value in test_data:
        linear_ht.insert(key, value)
    linear_time = time.time() - start
    
    print(f"Separate Chaining Time: {chaining_time:.6f}s")
    print(f"Linear Probing Time: {linear_time:.6f}s")

performance_test()
```

---

## 4. Load Factor and Rehashing (15 min)

### Load Factor
The load factor (α) is the ratio of stored elements to table size: `α = n/m`
- **n**: number of elements stored
- **m**: table size

**Optimal Load Factors:**
- Separate Chaining: α ≈ 1 (can exceed 1)
- Linear Probing: α ≈ 0.5-0.7
- Quadratic Probing: α ≈ 0.5-0.8
- Double Hashing: α ≈ 0.7-0.9

### Rehashing Implementation
When load factor exceeds threshold, we create a larger table and rehash all elements.

```python
class RehashingHashTable:
    def __init__(self, initial_size=11):
        self.size = initial_size
        self.table = [None] * self.size
        self.count = 0
        self.load_factor_threshold = 0.7
        self.growth_factor = 2
    
    def hash_function(self, key):
        return hash(key) % self.size
    
    def _is_prime(self, n):
        """Check if a number is prime"""
        if n < 2:
            return False
        for i in range(2, int(n**0.5) + 1):
            if n % i == 0:
                return False
        return True
    
    def _next_prime(self, n):
        """Find next prime number greater than n"""
        candidate = n + 1
        while not self._is_prime(candidate):
            candidate += 1
        return candidate
    
    def _rehash(self):
        """Rehash table when load factor exceeds threshold"""
        old_table = self.table
        old_size = self.size
        
        # Calculate new size (usually 2x + 1, then find next prime)
        new_size = self._next_prime(old_size * self.growth_factor + 1)
        
        self.size = new_size
        self.table = [None] * self.size
        self.count = 0
        
        # Rehash all existing elements
        for item in old_table:
            if item is not None:
                self.insert(item[0], item[1])
    
    def insert(self, key, value):
        # Check if rehashing is needed
        if self.count >= self.size * self.load_factor_threshold:
            self._rehash()
        
        index = self.hash_function(key)
        original_index = index
        
        # Linear probing for simplicity
        while self.table[index] is not None:
            if self.table[index][0] == key:
                self.table[index] = (key, value)
                return
            index = (index + 1) % self.size
            if index == original_index:
                self._rehash()  # Force rehash if table is full
                index = self.hash_function(key)
                original_index = index
        
        self.table[index] = (key, value)
        self.count += 1
    
    def get_load_factor(self):
        return self.count / self.size

# Example demonstrating rehashing
rehashing_ht = RehashingHashTable(5)
print(f"Initial size: {rehashing_ht.size}")

# Insert elements to trigger rehashing
for i in range(10):
    rehashing_ht.insert(f"key_{i}", f"value_{i}")
    print(f"After inserting key_{i}: size={rehashing_ht.size}, count={rehashing_ht.count}, load_factor={rehashing_ht.get_load_factor():.3f}")
```

---

## 5. Advanced Hashing Techniques (25 min)

### 5.1 Cuckoo Hashing
Uses two hash tables and two hash functions. If a collision occurs, it "kicks out" the existing element.

```python
class CuckooHashTable:
    def __init__(self, size=10):
        self.size = size
        self.table1 = [None] * size
        self.table2 = [None] * size
        self.max_attempts = size  # Prevent infinite loops
    
    def hash1(self, key):
        return hash(key) % self.size
    
    def hash2(self, key):
        return (hash(key) // self.size) % self.size
    
    def insert(self, key, value):
        # Try table1 first
        index1 = self.hash1(key)
        if self.table1[index1] is None:
            self.table1[index1] = (key, value)
            return
        
        # If occupied, try table2
        index2 = self.hash2(key)
        if self.table2[index2] is None:
            self.table2[index2] = (key, value)
            return
        
        # Both occupied, start cuckoo process
        current_key, current_value = key, value
        current_table = 1
        
        for _ in range(self.max_attempts):
            if current_table == 1:
                index = self.hash1(current_key)
                if self.table1[index] is None:
                    self.table1[index] = (current_key, current_value)
                    return
                # Kick out existing element
                current_key, current_value = self.table1[index]
                self.table1[index] = (key, value)
                current_table = 2
            else:
                index = self.hash2(current_key)
                if self.table2[index] is None:
                    self.table2[index] = (current_key, current_value)
                    return
                # Kick out existing element
                current_key, current_value = self.table2[index]
                self.table2[index] = (key, value)
                current_table = 1
        
        raise Exception("Cuckoo hashing failed - need to rehash")
```

### 5.2 Bloom Filters
Space-efficient probabilistic data structure for membership testing.

```python
import hashlib

class BloomFilter:
    def __init__(self, size, hash_count):
        self.size = size
        self.hash_count = hash_count
        self.bit_array = [False] * size
    
    def _hash(self, item, seed):
        """Generate hash with seed for different hash functions"""
        hasher = hashlib.md5()
        hasher.update(f"{item}{seed}".encode())
        return int(hasher.hexdigest(), 16) % self.size
    
    def add(self, item):
        """Add item to bloom filter"""
        for i in range(self.hash_count):
            index = self._hash(item, i)
            self.bit_array[index] = True
    
    def contains(self, item):
        """Check if item might be in the set"""
        for i in range(self.hash_count):
            index = self._hash(item, i)
            if not self.bit_array[index]:
                return False  # Definitely not in set
        return True  # Might be in set (could be false positive)

# Example usage
bloom = BloomFilter(1000, 3)
words = ["hello", "world", "python", "hashing", "bloom", "filter"]

for word in words:
    bloom.add(word)

# Test membership
test_words = ["hello", "world", "java", "python", "c++"]
for word in test_words:
    print(f"'{word}' might be in set: {bloom.contains(word)}")
```

### 5.3 Consistent Hashing
Used in distributed systems for load balancing and caching.

```python
import hashlib
import bisect

class ConsistentHashRing:
    def __init__(self, nodes=None):
        self.ring = {}
        self.sorted_keys = []
        if nodes:
            for node in nodes:
                self.add_node(node)
    
    def _hash(self, key):
        """Generate hash for key"""
        return int(hashlib.md5(key.encode()).hexdigest(), 16)
    
    def add_node(self, node):
        """Add a node to the hash ring"""
        key = self._hash(node)
        self.ring[key] = node
        self.sorted_keys.append(key)
        self.sorted_keys.sort()
    
    def remove_node(self, node):
        """Remove a node from the hash ring"""
        key = self._hash(node)
        if key in self.ring:
            del self.ring[key]
            self.sorted_keys.remove(key)
    
    def get_node(self, item):
        """Get the node responsible for an item"""
        if not self.ring:
            return None
        
        key = self._hash(item)
        # Find the first node with hash >= item's hash
        index = bisect.bisect_right(self.sorted_keys, key)
        if index == len(self.sorted_keys):
            index = 0  # Wrap around to first node
        
        return self.ring[self.sorted_keys[index]]

# Example usage
ring = ConsistentHashRing(['server1', 'server2', 'server3'])
items = ['user1', 'user2', 'user3', 'user4', 'user5']

print("Consistent Hashing Assignment:")
for item in items:
    server = ring.get_node(item)
    print(f"{item} -> {server}")
```

---

## 6. Real-World Applications (20 min)

### 6.1 Natural Language Processing (NLP)

#### Word Frequency Analysis
```python
def word_frequency_analysis(text):
    """Analyze word frequency using hash table"""
    word_count = {}
    words = text.lower().split()
    
    for word in words:
        # Remove punctuation
        word = ''.join(c for c in word if c.isalnum())
        if word:
            word_count[word] = word_count.get(word, 0) + 1
    
    return word_count

# Example usage
text = "The quick brown fox jumps over the lazy dog. The fox is quick."
freq = word_frequency_analysis(text)
print("Word frequencies:", freq)
```

#### Document Similarity with MinHash
```python
import hashlib
from collections import defaultdict

def shingle(text, k=3):
    """Create k-shingles from text"""
    text = text.lower().replace(" ", "")
    return [text[i:i+k] for i in range(len(text)-k+1)]

def minhash_signature(shingles, num_hashes=100):
    """Create MinHash signature for document"""
    signature = []
    for i in range(num_hashes):
        min_hash = float('inf')
        for shingle in shingles:
            hash_val = int(hashlib.md5(f"{shingle}{i}".encode()).hexdigest(), 16)
            min_hash = min(min_hash, hash_val)
        signature.append(min_hash)
    return signature

def jaccard_similarity(sig1, sig2):
    """Calculate Jaccard similarity between two MinHash signatures"""
    matches = sum(1 for a, b in zip(sig1, sig2) if a == b)
    return matches / len(sig1)

# Example usage
doc1 = "The quick brown fox jumps over the lazy dog"
doc2 = "A quick brown fox jumps over a lazy dog"
doc3 = "The slow red cat walks under the active bird"

shingles1 = shingle(doc1)
shingles2 = shingle(doc2)
shingles3 = shingle(doc3)

sig1 = minhash_signature(shingles1)
sig2 = minhash_signature(shingles2)
sig3 = minhash_signature(shingles3)

print(f"Similarity between doc1 and doc2: {jaccard_similarity(sig1, sig2):.3f}")
print(f"Similarity between doc1 and doc3: {jaccard_similarity(sig1, sig3):.3f}")
```

### 6.2 Cybersecurity Applications

#### Password Hashing
```python
import hashlib
import secrets

def hash_password(password, salt=None):
    """Hash password with salt using PBKDF2"""
    if salt is None:
        salt = secrets.token_hex(16)
    
    # Use PBKDF2 with SHA-256
    key = hashlib.pbkdf2_hmac('sha256', 
                             password.encode('utf-8'), 
                             salt.encode('utf-8'), 
                             100000)  # 100,000 iterations
    
    return salt + key.hex()

def verify_password(password, hashed_password):
    """Verify password against hash"""
    salt = hashed_password[:32]  # First 32 chars are salt
    stored_hash = hashed_password[32:]
    
    # Hash the provided password with the same salt
    key = hashlib.pbkdf2_hmac('sha256',
                             password.encode('utf-8'),
                             salt.encode('utf-8'),
                             100000)
    
    return key.hex() == stored_hash

# Example usage
password = "my_secure_password"
hashed = hash_password(password)
print(f"Hashed password: {hashed}")

# Verify password
is_valid = verify_password(password, hashed)
print(f"Password verification: {is_valid}")
```

### 6.3 Database and Caching

#### LRU Cache Implementation
```python
from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()
    
    def get(self, key):
        if key in self.cache:
            # Move to end (most recently used)
            self.cache.move_to_end(key)
            return self.cache[key]
        return None
    
    def put(self, key, value):
        if key in self.cache:
            # Update existing key
            self.cache.move_to_end(key)
        elif len(self.cache) >= self.capacity:
            # Remove least recently used (first item)
            self.cache.popitem(last=False)
        
        self.cache[key] = value

# Example usage
lru = LRUCache(3)
lru.put("a", 1)
lru.put("b", 2)
lru.put("c", 3)
print(f"Cache after adding a,b,c: {dict(lru.cache)}")

lru.get("a")  # Access 'a' to make it recently used
lru.put("d", 4)  # This should evict 'b'
print(f"Cache after accessing 'a' and adding 'd': {dict(lru.cache)}")
```

---

## 7. Best Practices and Security Considerations (15 min)

### 7.1 Hash Function Selection Guidelines

#### For General-Purpose Hash Tables
- Use built-in `hash()` function for basic cases
- Consider polynomial rolling hash for strings
- Use prime table sizes for better distribution

#### For Cryptographic Applications
- **SHA-256**: For passwords and sensitive data
- **MD5**: Avoid for security (vulnerable to collisions)
- **bcrypt/scrypt/Argon2**: For password hashing with salt

### 7.2 Performance Optimization Tips

```python
# Good: Pre-compute hash values for frequently accessed keys
class OptimizedHashTable:
    def __init__(self):
        self.table = {}
        self._hash_cache = {}
    
    def _get_hash(self, key):
        """Cache hash values for performance"""
        if key not in self._hash_cache:
            self._hash_cache[key] = hash(key)
        return self._hash_cache[key]
    
    def insert(self, key, value):
        hash_key = self._get_hash(key)
        self.table[hash_key] = value
    
    def get(self, key):
        hash_key = self._get_hash(key)
        return self.table.get(hash_key)
```

---

## 8. Hands-On Exercises (20 min)

### Exercise 1: Collision Analysis
Insert the following keys into hash tables of different sizes and collision resolution strategies:
`{4371, 1323, 6173, 4199, 4344, 9679, 1989}`

```python
def collision_analysis():
    """Analyze collisions for different hash table implementations"""
    keys = [4371, 1323, 6173, 4199, 4344, 9679, 1989]
    table_size = 10
    
    print("=== Collision Analysis ===")
    
    # Test with different hash functions
    for name, hash_func in [
        ("Division", lambda k: k % table_size),
        ("Multiplication", lambda k: int(table_size * ((k * 0.618) % 1)))
    ]:
        print(f"\n{name} Method:")
        collisions = 0
        used_indices = set()
        
        for key in keys:
            index = hash_func(key)
            if index in used_indices:
                collisions += 1
            used_indices.add(index)
            print(f"  {key} -> {index}")
        
        print(f"  Total collisions: {collisions}")

collision_analysis()
```

### Exercise 2: Implement a Spell Checker
```python
class SpellChecker:
    def __init__(self):
        self.dictionary = set()
    
    def load_dictionary(self, words):
        """Load dictionary words into hash set"""
        for word in words:
            self.dictionary.add(word.lower())
    
    def is_correct(self, word):
        """Check if word is in dictionary"""
        return word.lower() in self.dictionary
    
    def get_suggestions(self, word, max_distance=2):
        """Get suggestions for misspelled words"""
        suggestions = []
        word = word.lower()
        
        for dict_word in self.dictionary:
            if self._edit_distance(word, dict_word) <= max_distance:
                suggestions.append(dict_word)
        
        return sorted(suggestions)
    
    def _edit_distance(self, s1, s2):
        """Calculate edit distance between two strings"""
        if len(s1) < len(s2):
            return self._edit_distance(s2, s1)
        
        if len(s2) == 0:
            return len(s1)
        
        previous_row = list(range(len(s2) + 1))
        for i, c1 in enumerate(s1):
            current_row = [i + 1]
            for j, c2 in enumerate(s2):
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)
                current_row.append(min(insertions, deletions, substitutions))
            previous_row = current_row
        
        return previous_row[-1]

# Example usage
checker = SpellChecker()
checker.load_dictionary(["hello", "world", "python", "programming", "computer", "science"])

test_words = ["helo", "world", "pythn", "programing"]
for word in test_words:
    if checker.is_correct(word):
        print(f"'{word}' is spelled correctly")
    else:
        suggestions = checker.get_suggestions(word)
        print(f"'{word}' is misspelled. Suggestions: {suggestions}")
```

---

## 🕑 Updated Timing Breakdown
- Introduction to Hashing: 10 min
- Fundamentals of Hash Tables: 15 min
- Advanced Hash Functions: 20 min
- Collision Resolution Strategies: 35 min
- Load Factor and Rehashing: 15 min
- Advanced Hashing Techniques: 25 min
- Real-World Applications: 20 min
- Best Practices and Security: 15 min
- Hands-On Exercises: 20 min
- Q&A and Discussion: 10 min
**Total = 2 hours 25 min**

---

## ✅ Key Takeaways

### Performance Characteristics
- **Average Case**: O(1) for insert, delete, search
- **Worst Case**: O(n) with poor hash functions or high load factors
- **Space Complexity**: O(n) where n is number of elements

### Hash Function Design
- **Uniformity**: Distribute keys evenly to minimize collisions
- **Determinism**: Same input always produces same output
- **Efficiency**: Fast computation for good performance
- **Security**: Use cryptographic hashes for sensitive applications

### Collision Resolution Trade-offs
- **Separate Chaining**: Simple, handles clustering well, but uses extra memory
- **Linear Probing**: Cache-friendly, but suffers from clustering
- **Quadratic Probing**: Reduces clustering, but complex deletion
- **Double Hashing**: Best distribution, but requires two hash functions

### Real-World Impact
- **Databases**: Indexing and fast lookups
- **Web Development**: Session management, caching
- **Security**: Password storage, digital signatures
- **NLP**: Document similarity, word frequency analysis
- **Distributed Systems**: Load balancing, consistent hashing

### Best Practices
- Choose appropriate hash functions for your use case
- Monitor load factors and rehash when necessary
- Use cryptographic hashes for security-sensitive applications
- Implement proper collision resolution strategies
- Consider memory vs. performance trade-offs

Hashing is a fundamental technique that enables efficient data storage and retrieval across countless applications in computer science, from basic data structures to advanced distributed systems and cybersecurity applications.
