# Chapter 30: STL Overview

## 📘 Learning Objectives

After completing this chapter, you will:
- Understand the Standard Template Library (STL) organization
- Learn about containers, algorithms, and iterators
- Master the iterator concept and categories
- Understand generic programming with STL
- Learn about function objects and adapters

## 🎯 Key Concepts

### 1. STL Organization

The STL consists of three main components:
- **Containers**: Data structures for storing elements
- **Algorithms**: Generic algorithms for processing data
- **Iterators**: Abstraction for accessing container elements

### 2. Containers

- **Sequence containers**: vector, list, deque, array, forward_list
- **Associative containers**: set, multiset, map, multimap
- **Unordered containers**: unordered_set, unordered_map, etc.
- **Container adapters**: stack, queue, priority_queue

### 3. Algorithms

- **Non-modifying algorithms**: find, count, search, etc.
- **Modifying algorithms**: transform, replace, remove, etc.
- **Sorting algorithms**: sort, partial_sort, nth_element, etc.
- **Binary search algorithms**: lower_bound, upper_bound, binary_search

### 4. Iterators

- **Input iterators**: Read-only, forward-only
- **Output iterators**: Write-only, forward-only
- **Forward iterators**: Read/write, forward-only
- **Bidirectional iterators**: Read/write, forward and backward
- **Random access iterators**: Read/write, random access

### 5. Function Objects

- **Function objects**: Classes with operator()
- **Predicates**: Functions returning bool
- **Comparators**: Functions for ordering
- **Binders**: Bind arguments to functions

## 🧩 Practice Exercises

### Exercise 30.1: Container Basics
Create programs using different STL containers.

### Exercise 30.2: Algorithm Usage
Use STL algorithms with containers.

### Exercise 30.3: Iterator Operations
Demonstrate different iterator categories.

### Exercise 30.4: Function Objects
Create custom function objects and predicates.

## 💻 Code Examples

### Container Usage
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

int main() {
    // Vector - dynamic array
    std::vector<int> vec{1, 2, 3, 4, 5};
    
    // List - doubly linked list
    std::list<int> lst{10, 20, 30, 40, 50};
    
    // Set - sorted unique elements
    std::set<int> s{5, 2, 8, 1, 9};
    
    // Map - key-value pairs
    std::map<std::string, int> m{
        {"apple", 5},
        {"banana", 3},
        {"orange", 8}
    };
    
    // Display containers
    std::cout << "Vector: ";
    for (int val : vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Set: ";
    for (int val : s) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Map: ";
    for (const auto& pair : m) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Algorithm Usage
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> vec{5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Sort
    std::sort(vec.begin(), vec.end());
    
    // Find
    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Found 5 at position: " << (it - vec.begin()) << std::endl;
    }
    
    // Count
    int count = std::count(vec.begin(), vec.end(), 3);
    std::cout << "Count of 3: " << count << std::endl;
    
    // Transform
    std::vector<int> doubled(vec.size());
    std::transform(vec.begin(), vec.end(), doubled.begin(),
                   [](int x) { return x * 2; });
    
    // Accumulate
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Generic programming**: STL uses templates for type safety
2. **Iterator abstraction**: Uniform interface for different containers
3. **Algorithm separation**: Algorithms work with any container
4. **Performance**: STL is optimized for efficiency
5. **Extensibility**: Easy to add custom containers and algorithms

## 🔗 Next Steps

After understanding STL overview, proceed to Chapter 31 to learn about specific containers.

## 📚 Additional Resources

- C++ Reference: STL
- "The C++ Standard Library" by Josuttis
- STL Source Code Analysis
