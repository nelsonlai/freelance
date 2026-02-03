# Lesson 6.2: Arrays and Pointers

## Learning Objectives
- Master array declaration and initialization
- Understand array-pointer relationship
- Learn multi-dimensional arrays
- Practice with dynamic arrays
- Explore array algorithms and operations

## Prerequisites
- Completed Lesson 6.1 (Pointers Fundamentals)
- Understanding of pointer concepts
- Basic knowledge of memory management

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Array Fundamentals

#### Array Declaration
```cpp
int arr[5];                    // Uninitialized array
int arr[5] = {1, 2, 3, 4, 5}; // Initialized array
int arr[] = {1, 2, 3};         // Size deduced
int arr[5] = {1, 2};           // Partial initialization
```

#### Array Characteristics
- **Fixed size:** Size determined at compile time
- **Contiguous memory:** Elements stored sequentially
- **Zero-based indexing:** First element at index 0
- **No bounds checking:** Access beyond bounds is undefined

### 2. Array-Pointer Relationship

#### Equivalence
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;  // arr is equivalent to &arr[0]

// These are equivalent:
arr[i] == *(arr + i) == *(ptr + i) == ptr[i]
```

#### Array Decay
```cpp
void function(int arr[]);      // Equivalent to int* arr
void function(int* arr);       // Same as above
```

### 3. Multi-dimensional Arrays

#### Declaration
```cpp
int matrix[3][4];              // 3x4 matrix
int cube[2][3][4];             // 3D array
int matrix[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
```

#### Memory Layout
- **Row-major order:** Elements stored row by row
- **Pointer arithmetic:** Navigate through dimensions
- **Array of arrays:** Each row is an array

---

## Demonstration (25 minutes)

### Array Examples
```cpp
#include <iostream>

void demonstrateArrays() {
    std::cout << "=== Array Demonstration ===" << std::endl;
    
    int arr[5] = {10, 20, 30, 40, 50};
    
    std::cout << "Array elements:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    std::cout << "Array size: " << sizeof(arr) / sizeof(arr[0]) << std::endl;
}

void demonstrateArrayPointerRelationship() {
    std::cout << "
=== Array-Pointer Relationship ===" << std::endl;
    
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr = arr;
    
    std::cout << "Equivalent access methods:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] 
                  << ", *(arr + " << i << ") = " << *(arr + i)
                  << ", ptr[" << i << "] = " << ptr[i] << std::endl;
    }
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Array Operations
Practice array operations:

**Tasks:**
1. Create and initialize arrays
2. Implement array algorithms
3. Use array-pointer equivalence
4. Handle multi-dimensional arrays

### Activity 2: Dynamic Arrays
Implement dynamic arrays:

**Tasks:**
1. Allocate dynamic arrays
2. Resize arrays dynamically
3. Implement array utilities
4. Handle memory management

### Activity 3: Array Applications
Apply arrays to real problems:

**Tasks:**
1. Implement sorting algorithms
2. Build search functions
3. Create matrix operations
4. Design array-based data structures

---

## Key Concepts

### 1. Array Bounds
```cpp
int arr[5] = {1, 2, 3, 4, 5};
// arr[5] is undefined behavior!
// Always stay within bounds: 0 to size-1
```

### 2. Array Size
```cpp
int arr[5];
size_t size = sizeof(arr) / sizeof(arr[0]);  // Calculate size
```

### 3. Array Passing
```cpp
void processArray(int arr[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] *= 2;
    }
}
```

---

## Best Practices

### 1. Array Safety
- Always check bounds
- Use size_t for indices
- Initialize arrays properly
- Avoid array decay when possible

### 2. Performance
- Use contiguous memory layout
- Minimize cache misses
- Consider vectorization
- Profile array operations

### 3. Code Clarity
- Use meaningful array names
- Document array dimensions
- Use const when appropriate
- Prefer std::array for fixed sizes

---

## Common Pitfalls

### 1. Array Bounds
```cpp
// Wrong: out of bounds access
int arr[5] = {1, 2, 3, 4, 5};
int value = arr[5];  // Undefined behavior!

// Correct: stay within bounds
int value = arr[4];  // Last valid element
```

### 2. Array Size
```cpp
// Wrong: hardcoded size
void function(int arr[]) {
    for (int i = 0; i < 5; ++i) {  // What if array size changes?
        // ...
    }
}

// Correct: pass size parameter
void function(int arr[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        // ...
    }
}
```

### 3. Array Decay
```cpp
// Wrong: array decays to pointer
int arr[5] = {1, 2, 3, 4, 5};
size_t size = sizeof(arr);  // 20 bytes
function(arr);  // Array decays to pointer
// Inside function: sizeof(arr) is 8 bytes (pointer size)

// Correct: pass size explicitly
function(arr, sizeof(arr) / sizeof(arr[0]));
```

---

## Assessment

### Quiz Questions
1. What is the relationship between arrays and pointers?
2. How do you calculate array size?
3. What happens when arrays are passed to functions?
4. How do multi-dimensional arrays work?

### Practical Assessment
- Implement working array code
- Use arrays safely and correctly
- Handle array operations efficiently
- Apply arrays to solve problems

---

## Homework Assignment

### Task 1: Array Library
Implement:
1. A dynamic array class
2. Array sorting algorithms
3. Array search functions
4. Matrix operations library

### Task 2: Array Algorithms
Create:
1. Bubble sort implementation
2. Binary search function
3. Array reversal algorithm
4. Array rotation function

### Task 3: Array Applications
Apply arrays to:
1. Image processing operations
2. Mathematical computations
3. Data structure implementations
4. Algorithm optimizations

---

## Next Lesson Preview

In the next lesson, we'll learn about references:
- Reference declaration and initialization
- Reference vs pointer differences
- Const references
- Reference parameters

Make sure you understand arrays and pointers before moving on!