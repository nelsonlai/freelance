# Lesson 3.1: STL Containers - Sequential

## Learning Objectives
- Understand the STL container design philosophy
- Master vector, list, and deque containers
- Learn container operations and member functions
- Understand iterator concepts and usage
- Compare performance characteristics of different containers

## Prerequisites
- Completed Lesson 2.3 (Introduction to Templates)
- Understanding of templates and generic programming
- Basic knowledge of arrays and data structures

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. STL Design Philosophy

#### Standard Template Library Overview
- **Containers:** Store collections of objects
- **Algorithms:** Operate on containers
- **Iterators:** Provide access to container elements
- **Function Objects:** Define operations for algorithms

#### Container Categories
- **Sequential Containers:** vector, list, deque, array, forward_list
- **Associative Containers:** set, map, multiset, multimap
- **Unordered Containers:** unordered_set, unordered_map
- **Container Adapters:** stack, queue, priority_queue

### 2. Vector Container

#### Characteristics
- **Dynamic array:** Grows and shrinks as needed
- **Random access:** O(1) access to any element
- **Contiguous memory:** Elements stored in sequence
- **Automatic reallocation:** Handles memory management

#### Key Operations
```cpp
std::vector<int> vec;           // Create empty vector
vec.push_back(10);              // Add element at end
vec.pop_back();                 // Remove last element
vec.insert(vec.begin() + 2, 5); // Insert at position
vec.erase(vec.begin() + 1);     // Remove at position
vec.size();                     // Get size
vec.capacity();                 // Get capacity
```

### 3. List Container

#### Characteristics
- **Doubly linked list:** Bidirectional traversal
- **No random access:** Must traverse to reach elements
- **Efficient insertion/deletion:** O(1) at any position
- **No memory reallocation:** Elements scattered in memory

#### Key Operations
```cpp
std::list<int> lst;             // Create empty list
lst.push_back(10);              // Add at end
lst.push_front(5);              // Add at beginning
lst.insert(it, 15);             // Insert at iterator position
lst.erase(it);                  // Remove at iterator position
lst.sort();                     // Sort elements
lst.merge(other_list);          // Merge with another list
```

### 4. Deque Container

#### Characteristics
- **Double-ended queue:** Efficient insertion at both ends
- **Random access:** O(1) access to elements
- **Chunked memory:** Not contiguous like vector
- **Automatic growth:** Handles memory management

#### Key Operations
```cpp
std::deque<int> dq;             // Create empty deque
dq.push_back(10);               // Add at end
dq.push_front(5);               // Add at beginning
dq.pop_back();                  // Remove from end
dq.pop_front();                 // Remove from beginning
dq[2];                          // Random access
```

---

## Demonstration (25 minutes)

### Vector Demonstration
```cpp
#include <iostream>
#include <vector>

void demonstrateVector() {
    std::cout << "=== Vector Demonstration ===" << std::endl;
    
    // Create and populate vector
    std::vector<int> vec;
    std::cout << "Initial size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    
    // Add elements
    for (int i = 1; i <= 10; ++i) {
        vec.push_back(i * 10);
        std::cout << "Added " << (i * 10) << " - size: " << vec.size() 
                  << ", capacity: " << vec.capacity() << std::endl;
    }
    
    // Access elements
    std::cout << "\nVector contents: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    // Insert in middle
    vec.insert(vec.begin() + 5, 999);
    std::cout << "After inserting 999 at position 5: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Remove element
    vec.erase(vec.begin() + 3);
    std::cout << "After removing element at position 3: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
```

### List Demonstration
```cpp
#include <iostream>
#include <list>

void demonstrateList() {
    std::cout << "\n=== List Demonstration ===" << std::endl;
    
    std::list<int> lst;
    
    // Add elements at both ends
    lst.push_back(100);
    lst.push_front(50);
    lst.push_back(200);
    lst.push_front(25);
    lst.push_back(300);
    
    std::cout << "List contents: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Insert in middle
    auto it = lst.begin();
    std::advance(it, 2);  // Move iterator to position 2
    lst.insert(it, 999);
    
    std::cout << "After inserting 999 at position 2: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Remove elements
    lst.remove(200);  // Remove all occurrences of 200
    std::cout << "After removing 200: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Sort list
    lst.sort();
    std::cout << "After sorting: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
```

### Deque Demonstration
```cpp
#include <iostream>
#include <deque>

void demonstrateDeque() {
    std::cout << "\n=== Deque Demonstration ===" << std::endl;
    
    std::deque<int> dq;
    
    // Add elements at both ends
    dq.push_back(10);
    dq.push_front(5);
    dq.push_back(20);
    dq.push_front(1);
    dq.push_back(30);
    
    std::cout << "Deque contents: ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Random access
    std::cout << "Element at index 2: " << dq[2] << std::endl;
    std::cout << "Element at index 4: " << dq[4] << std::endl;
    
    // Remove from both ends
    std::cout << "Removed from front: " << dq.front() << std::endl;
    dq.pop_front();
    
    std::cout << "Removed from back: " << dq.back() << std::endl;
    dq.pop_back();
    
    std::cout << "After removals: ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Container Performance Comparison
Compare the performance of different containers:

**Tasks:**
1. Measure insertion time for vector, list, and deque
2. Measure random access time
3. Measure deletion time from different positions
4. Analyze memory usage patterns

### Activity 2: Container Selection Exercise
Choose appropriate containers for different scenarios:

**Tasks:**
1. Implement a simple database with frequent lookups
2. Create a text editor with frequent insertions/deletions
3. Build a cache system with LRU eviction
4. Design a game inventory system

### Activity 3: Iterator Usage Practice
Practice using iterators with different containers:

**Tasks:**
1. Traverse containers using different iterator types
2. Use iterators for insertion and deletion
3. Implement algorithms using iterators
4. Handle iterator invalidation scenarios

---

## Key Concepts

### 1. Iterator Categories
```cpp
// Input iterator - read-only, forward only
std::vector<int>::iterator it = vec.begin();
int value = *it;  // Read value
++it;             // Move forward

// Bidirectional iterator (list)
std::list<int>::iterator lit = lst.begin();
++lit;  // Move forward
--lit;  // Move backward

// Random access iterator (vector, deque)
std::vector<int>::iterator vit = vec.begin();
vit += 5;        // Jump 5 positions
int diff = vit - vec.begin();  // Calculate distance
```

### 2. Container Selection Guidelines
```cpp
// Use vector when:
// - You need random access
// - You mostly add/remove at the end
// - Memory efficiency is important
std::vector<int> scores;

// Use list when:
// - You frequently insert/delete in middle
// - You don't need random access
// - You need stable iterators
std::list<std::string> playlist;

// Use deque when:
// - You need random access
// - You add/remove at both ends
// - You don't need contiguous memory
std::deque<int> sliding_window;
```

### 3. Memory Management
```cpp
// Vector memory management
std::vector<int> vec;
vec.reserve(1000);  // Reserve capacity
vec.shrink_to_fit();  // Reduce capacity to fit size

// List doesn't need capacity management
std::list<int> lst;  // No reserve() method

// Deque memory management
std::deque<int> dq;  // Automatically managed
```

---

## Best Practices

### 1. Container Selection
- **Vector:** Default choice for most applications
- **List:** Use when frequent insertion/deletion in middle
- **Deque:** Use when frequent operations at both ends
- **Array:** Use when size is known at compile time

### 2. Performance Optimization
- Use `reserve()` for vectors when you know the size
- Use `emplace_back()` instead of `push_back()` when possible
- Prefer range-based for loops for traversal
- Use appropriate iterator types for algorithms

### 3. Memory Management
- Be aware of iterator invalidation
- Use `shrink_to_fit()` for vectors when appropriate
- Consider memory fragmentation with lists
- Monitor capacity vs size for vectors

---

## Common Pitfalls

### 1. Iterator Invalidation
```cpp
// Wrong: Iterator becomes invalid after insertion
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = vec.begin() + 2;
vec.insert(vec.begin() + 1, 999);  // Iterator invalidated
// *it;  // Undefined behavior!

// Correct: Get new iterator after insertion
vec.insert(vec.begin() + 1, 999);
it = vec.begin() + 3;  // New iterator
```

### 2. Performance Issues
```cpp
// Wrong: Frequent insertions at beginning of vector
std::vector<int> vec;
for (int i = 0; i < 1000; ++i) {
    vec.insert(vec.begin(), i);  // O(n) each time!
}

// Correct: Use deque for frequent front insertions
std::deque<int> dq;
for (int i = 0; i < 1000; ++i) {
    dq.push_front(i);  // O(1) each time
}
```

### 3. Memory Leaks with Custom Objects
```cpp
// Wrong: Raw pointers in containers
std::vector<int*> vec;
vec.push_back(new int(42));  // Memory leak if not deleted

// Correct: Use smart pointers or value objects
std::vector<std::unique_ptr<int>> vec;
vec.push_back(std::make_unique<int>(42));  // Automatic cleanup
```

---

## Assessment

### Quiz Questions
1. When should you use vector vs list vs deque?
2. What are the performance characteristics of each container?
3. What is iterator invalidation and when does it occur?
4. How do you choose the right container for a specific use case?

### Practical Assessment
- Implement container operations correctly
- Choose appropriate containers for scenarios
- Use iterators properly
- Handle performance considerations

---

## Homework Assignment

### Task 1: Container Performance Analysis
Write programs to measure and compare:
1. Insertion performance for different containers
2. Access time for random vs sequential access
3. Memory usage patterns
4. Iterator performance

### Task 2: Real-World Container Applications
Implement:
1. A simple spreadsheet using vector of vectors
2. A text editor with undo/redo using deque
3. A playlist manager using list
4. A priority queue using vector with heap operations

### Task 3: Container Utilities
Create utility functions for:
1. Container statistics (size, capacity, memory usage)
2. Container comparison and equality testing
3. Container serialization and deserialization
4. Container performance profiling

---

## Code Examples for Practice

### Complete Container Comparison
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>

template<typename Container>
void measureInsertion(Container& container, const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; ++i) {
        container.push_back(i);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << name << " insertion time: " << duration.count() << " microseconds" << std::endl;
}

int main() {
    std::vector<int> vec;
    std::list<int> lst;
    std::deque<int> dq;
    
    std::cout << "=== Container Performance Comparison ===" << std::endl;
    
    measureInsertion(vec, "Vector");
    measureInsertion(lst, "List");
    measureInsertion(dq, "Deque");
    
    return 0;
}
```

---

## Next Lesson Preview

In the next lesson, we'll learn about associative containers:
- set and multiset containers
- map and multimap containers
- Key-value pair handling
- Ordered vs unordered containers

Make sure you understand sequential containers and iterators before moving on!