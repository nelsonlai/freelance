# Chapter 33: Iterators and Ranges

## 📘 Learning Objectives

After completing this chapter, you will:
- Master all iterator categories and their characteristics
- Understand iterator concepts and requirements
- Learn about range-based for loops and views
- Master iterator adaptors and utilities
- Understand iterator safety and invalidation

## 🎯 Key Concepts

### 1. Iterator Categories

- **Input iterators**: Read-only, single-pass
- **Output iterators**: Write-only, single-pass
- **Forward iterators**: Read/write, multi-pass
- **Bidirectional iterators**: Forward + reverse traversal
- **Random access iterators**: Bidirectional + random access
- **Contiguous iterators**: Random access + contiguous memory

### 2. Iterator Concepts

- **Iterator traits**: Type information about iterators
- **Iterator requirements**: Operations each category must support
- **Iterator validity**: When iterators become invalid
- **Iterator invalidation**: Rules for container modification

### 3. Range-Based For Loops

- **Range-based for**: Modern C++ iteration syntax
- **Range requirements**: What makes a valid range
- **Custom ranges**: Implementing range support
- **Range views**: Lazy evaluation and composition

### 4. Iterator Adaptors

- **Insert iterators**: back_inserter, front_inserter, inserter
- **Stream iterators**: istream_iterator, ostream_iterator
- **Reverse iterators**: rbegin, rend
- **Move iterators**: make_move_iterator

### 5. Iterator Utilities

- **Distance**: Calculate distance between iterators
- **Advance**: Move iterator by specified distance
- **Next/Prev**: Get next/previous iterator
- **Begin/End**: Get begin/end iterators

## 🧩 Practice Exercises

### Exercise 33.1: Iterator Categories
Work with different iterator categories.

### Exercise 33.2: Range-Based For Loops
Use modern range-based iteration.

### Exercise 33.3: Iterator Adaptors
Use iterator adaptors for different purposes.

### Exercise 33.4: Custom Iterators
Implement custom iterator classes.

## 💻 Code Examples

### Iterator Categories
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Random access iterator
    auto it = vec.begin();
    it += 2;  // Random access
    std::cout << "Element at position 2: " << *it << std::endl;
    
    // Bidirectional iterator
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto list_it = lst.begin();
    ++list_it;  // Forward
    --list_it;  // Backward
    
    // Forward iterator
    std::set<int> s = {1, 2, 3, 4, 5};
    auto set_it = s.begin();
    ++set_it;  // Forward only
    
    return 0;
}
```

### Range-Based For Loops
```cpp
#include <iostream>
#include <vector>
#include <map>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Range-based for loop
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // With map
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}};
    
    for (const auto& pair : m) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Understand iterator categories** for algorithm compatibility
2. **Use range-based for loops** for cleaner code
3. **Be aware of iterator invalidation** when modifying containers
4. **Use iterator adaptors** for flexible iteration
5. **Implement custom iterators** when needed

## 🔗 Next Steps

After mastering iterators and ranges, proceed to Chapter 34 to learn about concurrency.

## 📚 Additional Resources

- C++ Reference: Iterators
- C++ Core Guidelines: Iterators
- Practice with different iterator patterns
