# Lesson 3.2: STL Containers - Associative

## Learning Objectives
- Master set and multiset containers
- Understand map and multimap containers
- Learn key-value pair handling
- Compare ordered vs unordered containers
- Practice container operations and algorithms

## Prerequisites
- Completed Lesson 3.1 (STL Containers Sequential)
- Understanding of iterators and container operations
- Basic knowledge of binary trees and hash tables

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Associative Container Overview

#### Characteristics
- **Ordered containers:** Elements sorted by key
- **Fast lookup:** O(log n) search time
- **Unique keys:** set and map allow only unique keys
- **Duplicate keys:** multiset and multimap allow duplicates

#### Container Types
- **set:** Unique keys, sorted order
- **multiset:** Duplicate keys allowed, sorted order
- **map:** Unique key-value pairs, sorted by key
- **multimap:** Duplicate keys allowed, sorted by key

### 2. Set Container

#### Characteristics
- **Unique elements:** No duplicates allowed
- **Sorted order:** Elements automatically sorted
- **Fast search:** O(log n) find operations
- **Immutable keys:** Keys cannot be modified

#### Key Operations
```cpp
std::set<int> s;
s.insert(10);              // Insert element
s.erase(10);               // Remove element
s.find(10);                // Find element
s.count(10);               // Count occurrences (0 or 1)
s.lower_bound(10);         // First element >= 10
s.upper_bound(10);         // First element > 10
```

### 3. Map Container

#### Characteristics
- **Key-value pairs:** Each element is a pair
- **Unique keys:** No duplicate keys
- **Sorted by key:** Automatically sorted
- **Fast lookup:** O(log n) access time

#### Key Operations
```cpp
std::map<std::string, int> m;
m["key"] = 42;             // Insert/update
m.insert({"key", 42});     // Insert pair
m.erase("key");            // Remove by key
m.find("key");             // Find element
m.count("key");            // Count occurrences (0 or 1)
```

---

## Demonstration (25 minutes)

### Set Demonstration
```cpp
#include <iostream>
#include <set>

void demonstrateSet() {
    std::cout << "=== Set Demonstration ===" << std::endl;
    
    std::set<int> s;
    
    // Insert elements
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(30);  // Duplicate - won't be added
    
    std::cout << "Set contents: ";
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Search operations
    auto it = s.find(20);
    if (it != s.end()) {
        std::cout << "Found 20 in set" << std::endl;
    }
    
    // Count occurrences
    std::cout << "Count of 20: " << s.count(20) << std::endl;
    std::cout << "Count of 25: " << s.count(25) << std::endl;
    
    // Range operations
    auto lower = s.lower_bound(15);
    auto upper = s.upper_bound(25);
    
    std::cout << "Elements in range [15, 25]: ";
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

### Map Demonstration
```cpp
#include <iostream>
#include <map>

void demonstrateMap() {
    std::cout << "=== Map Demonstration ===" << std::endl;
    
    std::map<std::string, int> ages;
    
    // Insert key-value pairs
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    
    // Access elements
    std::cout << "Alice's age: " << ages["Alice"] << std::endl;
    std::cout << "Bob's age: " << ages["Bob"] << std::endl;
    
    // Iterate through map
    std::cout << "All ages: ";
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
    
    // Search operations
    auto it = ages.find("Charlie");
    if (it != ages.end()) {
        std::cout << "Found Charlie: " << it->second << std::endl;
    }
    
    // Update value
    ages["Alice"] = 26;
    std::cout << "Updated Alice's age: " << ages["Alice"] << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Container Operations
Practice with associative containers:

**Tasks:**
1. Create a set of student IDs
2. Implement a phone directory using map
3. Build a word frequency counter
4. Create a grade book system

### Activity 2: Algorithm Integration
Use algorithms with associative containers:

**Tasks:**
1. Find common elements between sets
2. Merge two maps
3. Filter map based on values
4. Sort map by values

### Activity 3: Performance Analysis
Compare performance of different containers:

**Tasks:**
1. Measure search time for set vs vector
2. Compare insertion time for map vs vector
3. Analyze memory usage patterns
4. Test with different data sizes

---

## Key Concepts

### 1. Key-Value Pairs
```cpp
// Creating pairs
std::pair<std::string, int> p1("Alice", 25);
auto p2 = std::make_pair("Bob", 30);

// Using in map
std::map<std::string, int> m;
m.insert(p1);
m.insert(p2);
```

### 2. Iterator Types
```cpp
// Set iterator
std::set<int>::iterator it = s.begin();
std::set<int>::const_iterator cit = s.cbegin();

// Map iterator
std::map<std::string, int>::iterator mit = m.begin();
std::map<std::string, int>::const_iterator cmit = m.cbegin();
```

### 3. Range Operations
```cpp
// Find range of elements
auto lower = s.lower_bound(10);
auto upper = s.upper_bound(20);

// Count elements in range
int count = std::distance(lower, upper);
```

---

## Best Practices

### 1. Container Selection
- Use set for unique elements with fast search
- Use map for key-value associations
- Use multiset/multimap when duplicates are needed
- Consider unordered containers for better performance

### 2. Performance Optimization
- Use insert() with hint for better performance
- Prefer find() over count() for existence checks
- Use lower_bound/upper_bound for range queries
- Consider reserve() for unordered containers

### 3. Memory Management
- Be aware of iterator invalidation
- Use const references for large keys/values
- Consider custom comparators for complex types
- Monitor memory usage with large datasets

---

## Common Pitfalls

### 1. Key Modification
```cpp
// Wrong: Modifying key in set
std::set<int> s = {1, 2, 3};
auto it = s.find(2);
// *it = 4;  // Undefined behavior!

// Correct: Remove and reinsert
s.erase(it);
s.insert(4);
```

### 2. Map Access
```cpp
// Wrong: Accessing non-existent key
std::map<std::string, int> m;
int value = m["nonexistent"];  // Creates entry with 0

// Correct: Check existence first
auto it = m.find("nonexistent");
if (it != m.end()) {
    int value = it->second;
}
```

### 3. Iterator Invalidation
```cpp
// Wrong: Iterator becomes invalid after erase
auto it = s.begin();
s.erase(it);
// ++it;  // Undefined behavior!

// Correct: Get new iterator
it = s.erase(it);  // Returns iterator to next element
```

---

## Assessment

### Quiz Questions
1. When should you use set vs multiset?
2. What are the performance characteristics of map?
3. How do you handle duplicate keys in associative containers?
4. What is the difference between find() and count()?

### Practical Assessment
- Implement working associative containers
- Use appropriate operations for different scenarios
- Handle iterator invalidation correctly
- Optimize performance for large datasets

---

## Homework Assignment

### Task 1: Data Structures Implementation
Implement:
1. A student database using map
2. A word frequency counter using map
3. A set operations library
4. A priority queue using map

### Task 2: Algorithm Development
Create algorithms for:
1. Set intersection and union
2. Map merging and filtering
3. Range queries on associative containers
4. Custom comparison functions

### Task 3: Performance Analysis
Analyze performance of:
1. Different associative containers
2. Various insertion strategies
3. Search algorithms
4. Memory usage patterns

---

## Next Lesson Preview

In the next lesson, we'll learn about STL algorithms:
- Algorithm categories and usage
- Iterator-based operations
- Function objects and lambdas
- Performance considerations

Make sure you understand associative containers before moving on!