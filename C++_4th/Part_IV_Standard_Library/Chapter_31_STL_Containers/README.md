# Chapter 31: STL Containers

## 📘 Learning Objectives

After completing this chapter, you will:
- Master all STL container types and their characteristics
- Understand when to use each container type
- Learn about container adapters and their usage
- Master iterator categories and container compatibility
- Understand performance characteristics of different containers

## 🎯 Key Concepts

### 1. Sequence Containers

- **vector**: Dynamic array with random access
- **list**: Doubly linked list with bidirectional access
- **deque**: Double-ended queue with random access
- **array**: Fixed-size array with STL interface
- **forward_list**: Singly linked list with forward access

### 2. Associative Containers

- **set**: Sorted unique elements
- **multiset**: Sorted elements allowing duplicates
- **map**: Sorted key-value pairs with unique keys
- **multimap**: Sorted key-value pairs allowing duplicate keys

### 3. Unordered Containers

- **unordered_set**: Hash table with unique elements
- **unordered_multiset**: Hash table allowing duplicates
- **unordered_map**: Hash table with unique keys
- **unordered_multimap**: Hash table allowing duplicate keys

### 4. Container Adapters

- **stack**: LIFO (Last In, First Out) container
- **queue**: FIFO (First In, First Out) container
- **priority_queue**: Heap-based priority queue

### 5. Container Characteristics

- **Iterator categories**: Input, output, forward, bidirectional, random access
- **Memory layout**: Contiguous vs. linked vs. tree-based
- **Performance**: Time complexity for different operations
- **Memory overhead**: Space efficiency considerations

## 🧩 Practice Exercises

### Exercise 31.1: Sequence Containers
Compare and use different sequence containers.

### Exercise 31.2: Associative Containers
Work with sorted containers and their operations.

### Exercise 31.3: Unordered Containers
Use hash-based containers for fast lookups.

### Exercise 31.4: Container Adapters
Implement algorithms using container adapters.

## 💻 Code Examples

### Sequence Containers
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>

int main() {
    // Vector - dynamic array
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    vec.insert(vec.begin() + 2, 10);
    
    std::cout << "Vector: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // List - doubly linked list
    std::list<int> lst = {1, 2, 3, 4, 5};
    lst.push_front(0);
    lst.push_back(6);
    
    std::cout << "List: ";
    for (const auto& val : lst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Deque - double-ended queue
    std::deque<int> deq = {1, 2, 3, 4, 5};
    deq.push_front(0);
    deq.push_back(6);
    
    std::cout << "Deque: ";
    for (const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Associative Containers
```cpp
#include <iostream>
#include <set>
#include <map>

int main() {
    // Set - sorted unique elements
    std::set<int> s = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Set: ";
    for (const auto& val : s) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Map - sorted key-value pairs
    std::map<std::string, int> m = {
        {"apple", 5},
        {"banana", 3},
        {"orange", 8},
        {"grape", 2}
    };
    
    std::cout << "Map: ";
    for (const auto& pair : m) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Choose the right container** for your use case
2. **Understand performance characteristics** of different containers
3. **Use iterators effectively** for container traversal
4. **Consider memory layout** for performance optimization
5. **Use container adapters** for specific data structures

## 🔗 Next Steps

After mastering STL containers, proceed to Chapter 32 to learn about STL algorithms.

## 📚 Additional Resources

- C++ Reference: STL Containers
- C++ Core Guidelines: Containers
- Practice with different container types
