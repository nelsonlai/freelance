# Lesson 3.3: STL Algorithms

## Learning Objectives
- Master STL algorithm categories and usage
- Learn iterator-based operations
- Understand function objects and lambdas
- Practice algorithm customization
- Compare algorithm performance

## Prerequisites
- Completed Lesson 3.2 (STL Containers Associative)
- Understanding of iterators and containers
- Basic knowledge of function pointers

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. STL Algorithm Overview

#### Categories
- **Non-modifying algorithms:** find, count, search
- **Modifying algorithms:** transform, replace, remove
- **Sorting algorithms:** sort, partial_sort, nth_element
- **Binary search algorithms:** binary_search, lower_bound
- **Set algorithms:** set_union, set_intersection

#### Design Principles
- **Iterator-based:** Work with any container
- **Generic:** Work with any data type
- **Efficient:** Optimized implementations
- **Composable:** Can be combined

### 2. Non-Modifying Algorithms

#### Search Algorithms
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = std::find(vec.begin(), vec.end(), 3);
auto count = std::count(vec.begin(), vec.end(), 3);
auto result = std::search(vec.begin(), vec.end(), pattern.begin(), pattern.end());
```

#### Comparison Algorithms
```cpp
bool equal = std::equal(vec1.begin(), vec1.end(), vec2.begin());
bool lex_less = std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
```

### 3. Modifying Algorithms

#### Transformation Algorithms
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return x * 2; });
std::replace(vec.begin(), vec.end(), 3, 30);
```

#### Removal Algorithms
```cpp
auto new_end = std::remove(vec.begin(), vec.end(), 3);
vec.erase(new_end, vec.end());
auto unique_end = std::unique(vec.begin(), vec.end());
vec.erase(unique_end, vec.end());
```

### 4. Sorting Algorithms

#### Basic Sorting
```cpp
std::vector<int> vec = {5, 2, 8, 1, 9};
std::sort(vec.begin(), vec.end());
std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
std::nth_element(vec.begin(), vec.begin() + 2, vec.end());
```

#### Binary Search
```cpp
bool found = std::binary_search(vec.begin(), vec.end(), 5);
auto lower = std::lower_bound(vec.begin(), vec.end(), 5);
auto upper = std::upper_bound(vec.begin(), vec.end(), 5);
```

---

## Demonstration (25 minutes)

### Algorithm Examples
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void demonstrateAlgorithms() {
    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Original vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Find operations
    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Found 5 at position: " << std::distance(vec.begin(), it) << std::endl;
    }
    
    // Count operations
    int count = std::count(vec.begin(), vec.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    // Transform
    std::vector<int> doubled;
    std::transform(vec.begin(), vec.end(), std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled vector: ";
    for (int x : doubled) std::cout << x << " ";
    std::cout << std::endl;
    
    // Sort
    std::sort(vec.begin(), vec.end());
    std::cout << "Sorted vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Binary search
    bool found = std::binary_search(vec.begin(), vec.end(), 5);
    std::cout << "5 found in sorted vector: " << (found ? "Yes" : "No") << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Algorithm Implementation
Implement custom algorithms:

**Tasks:**
1. Create a generic search function
2. Implement a sorting algorithm
3. Build a transformation pipeline
4. Design a filtering system

### Activity 2: Performance Analysis
Compare algorithm performance:

**Tasks:**
1. Measure sorting algorithm performance
2. Compare search algorithm efficiency
3. Analyze memory usage patterns
4. Test with different data sizes

### Activity 3: Real-World Applications
Apply algorithms to practical problems:

**Tasks:**
1. Implement a text search engine
2. Build a data analysis pipeline
3. Create a recommendation system
4. Design a caching mechanism

---

## Key Concepts

### 1. Function Objects
```cpp
// Function object for comparison
struct Greater {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

// Usage
std::sort(vec.begin(), vec.end(), Greater());
```

### 2. Lambda Expressions
```cpp
// Lambda for transformation
auto square = [](int x) { return x * x; };
std::transform(vec.begin(), vec.end(), vec.begin(), square);

// Lambda with capture
int multiplier = 2;
auto multiply = [multiplier](int x) { return x * multiplier; };
```

### 3. Iterator Categories
```cpp
// Input iterator
std::find(vec.begin(), vec.end(), 5);

// Output iterator
std::copy(vec.begin(), vec.end(), std::back_inserter(result));

// Forward iterator
std::unique(vec.begin(), vec.end());

// Bidirectional iterator
std::reverse(vec.begin(), vec.end());

// Random access iterator
std::sort(vec.begin(), vec.end());
```

---

## Best Practices

### 1. Algorithm Selection
- Choose appropriate algorithm for your use case
- Consider performance characteristics
- Use specialized algorithms when available
- Combine algorithms for complex operations

### 2. Iterator Usage
- Use appropriate iterator types
- Be aware of iterator invalidation
- Use iterator adaptors when needed
- Prefer range-based operations

### 3. Performance Optimization
- Use algorithms instead of manual loops
- Consider algorithm complexity
- Use move semantics when possible
- Profile and measure performance

---

## Common Pitfalls

### 1. Iterator Invalidation
```cpp
// Wrong: Iterator becomes invalid after modification
auto it = vec.begin();
vec.insert(vec.begin(), 0);
// ++it;  // Undefined behavior!

// Correct: Get new iterator after modification
it = vec.insert(vec.begin(), 0);
```

### 2. Algorithm Complexity
```cpp
// Wrong: Using O(n) algorithm for O(log n) operation
std::vector<int> sorted_vec = {1, 2, 3, 4, 5};
auto it = std::find(sorted_vec.begin(), sorted_vec.end(), 3);  // O(n)

// Correct: Use binary search for sorted data
bool found = std::binary_search(sorted_vec.begin(), sorted_vec.end(), 3);  // O(log n)
```

### 3. Memory Management
```cpp
// Wrong: Not handling removed elements
std::vector<int> vec = {1, 2, 3, 4, 5};
std::remove(vec.begin(), vec.end(), 3);  // Doesn't resize vector

// Correct: Erase removed elements
auto new_end = std::remove(vec.begin(), vec.end(), 3);
vec.erase(new_end, vec.end());
```

---

## Assessment

### Quiz Questions
1. What are the different categories of STL algorithms?
2. When should you use binary search vs linear search?
3. What is the difference between remove and erase?
4. How do you choose the right algorithm for a task?

### Practical Assessment
- Implement working algorithms
- Use appropriate iterator types
- Handle algorithm complexity correctly
- Apply algorithms to real problems

---

## Homework Assignment

### Task 1: Algorithm Library
Implement:
1. A generic search library
2. A sorting algorithm collection
3. A transformation pipeline
4. A filtering system

### Task 2: Performance Analysis
Analyze performance of:
1. Different sorting algorithms
2. Various search strategies
3. Algorithm combinations
4. Memory usage patterns

### Task 3: Real-World Applications
Apply algorithms to:
1. Text processing tasks
2. Data analysis problems
3. Image processing operations
4. Network protocol handling

---

## Next Lesson Preview

In the next lesson, we'll learn about concurrency:
- Thread creation and management
- Synchronization primitives
- Race conditions and deadlocks
- Modern concurrency features

Make sure you understand STL algorithms before moving on!