# Chapter 32: STL Algorithms

## 📘 Learning Objectives

After completing this chapter, you will:
- Master the STL algorithm library and its categories
- Understand non-modifying sequence operations
- Learn about modifying sequence operations
- Master sorting and searching algorithms
- Understand set operations and heap algorithms

## 🎯 Key Concepts

### 1. Non-Modifying Sequence Operations

- **find**: Find first occurrence of value
- **count**: Count occurrences of value
- **search**: Search for subsequence
- **mismatch**: Find first difference
- **equal**: Test equality of sequences
- **all_of, any_of, none_of**: Test predicates

### 2. Modifying Sequence Operations

- **copy**: Copy elements to destination
- **move**: Move elements to destination
- **transform**: Apply function to elements
- **replace**: Replace elements with new value
- **fill**: Fill range with value
- **generate**: Generate values using function

### 3. Sorting and Related Operations

- **sort**: Sort elements in ascending order
- **stable_sort**: Sort with stable ordering
- **partial_sort**: Sort first N elements
- **nth_element**: Find nth element
- **binary_search**: Binary search in sorted range
- **lower_bound, upper_bound**: Find insertion points

### 4. Set Operations

- **set_union**: Union of two sorted sets
- **set_intersection**: Intersection of two sorted sets
- **set_difference**: Difference of two sorted sets
- **set_symmetric_difference**: Symmetric difference
- **includes**: Test if one set includes another
- **merge**: Merge two sorted sequences

### 5. Heap Operations

- **make_heap**: Create heap from range
- **push_heap**: Add element to heap
- **pop_heap**: Remove largest element
- **sort_heap**: Sort heap
- **is_heap**: Test if range is heap

### 6. Permutation Operations

- **next_permutation**: Generate next permutation
- **prev_permutation**: Generate previous permutation
- **is_permutation**: Test if ranges are permutations

## 🧩 Practice Exercises

### Exercise 32.1: Non-Modifying Operations
Use find, count, and search algorithms.

### Exercise 32.2: Modifying Operations
Apply copy, transform, and replace algorithms.

### Exercise 32.3: Sorting Operations
Use sorting and searching algorithms.

### Exercise 32.4: Set Operations
Perform set operations on sorted ranges.

## 💻 Code Examples

### Non-Modifying Operations
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Find first occurrence
    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Found 5 at position: " << (it - vec.begin()) << std::endl;
    }
    
    // Count occurrences
    int count = std::count(vec.begin(), vec.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    // Test predicates
    bool all_even = std::all_of(vec.begin(), vec.end(), 
                               [](int x) { return x % 2 == 0; });
    std::cout << "All even: " << std::boolalpha << all_even << std::endl;
    
    return 0;
}
```

### Modifying Operations
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> result(vec.size());
    
    // Copy elements
    std::copy(vec.begin(), vec.end(), result.begin());
    
    // Transform elements
    std::transform(vec.begin(), vec.end(), result.begin(),
                   [](int x) { return x * 2; });
    
    // Replace elements
    std::replace(result.begin(), result.end(), 10, 100);
    
    // Display result
    for (const auto& val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use appropriate algorithms** for your operations
2. **Understand iterator requirements** for different algorithms
3. **Use predicates effectively** for custom comparisons
4. **Combine algorithms** for complex operations
5. **Consider performance implications** of algorithm choices

## 🔗 Next Steps

After mastering STL algorithms, proceed to Chapter 33 to learn about iterators and ranges.

## 📚 Additional Resources

- C++ Reference: STL Algorithms
- C++ Core Guidelines: Algorithms
- Practice with different algorithm combinations
