# Lesson 2.3: Introduction to Templates

## Learning Objectives
- Understand the concept of generic programming
- Learn function template syntax and usage
- Master class template implementation
- Understand template instantiation
- Practice template parameter deduction

## Prerequisites
- Completed Lesson 2.2 (Constructors and Destructors)
- Understanding of classes and functions
- Basic knowledge of data types and operators

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Generic Programming Concepts

#### What are Templates?
Templates allow you to write code that works with multiple data types without duplicating code. They enable **generic programming** - writing code once that can be used with different types.

#### Benefits of Templates
- **Code reuse:** Write once, use with many types
- **Type safety:** Compile-time type checking
- **Performance:** No runtime overhead (zero-cost abstraction)
- **Maintainability:** Single implementation for multiple types

### 2. Function Templates

#### Basic Syntax
```cpp
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}
```

#### Template Parameter Types
- `typename T` or `class T` - both are equivalent
- Multiple parameters: `template<typename T, typename U>`
- Non-type parameters: `template<int N>`

### 3. Class Templates

#### Basic Syntax
```cpp
template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    void push(const T& item);
    T pop();
    bool isEmpty() const;
};
```

#### Template Member Functions
- Defined inside class: implicitly templates
- Defined outside: must include template declaration

### 4. Template Instantiation

#### Explicit Instantiation
```cpp
int result1 = maximum<int>(10, 20);
Stack<double> doubleStack;
```

#### Implicit Instantiation (Type Deduction)
```cpp
int result2 = maximum(10, 20);  // T deduced as int
Stack<int> intStack;            // T is int
```

---

## Demonstration (25 minutes)

### Function Template Examples
```cpp
#include <iostream>
#include <string>

// Function template for maximum
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Function template with multiple parameters
template<typename T, typename U>
void printPair(T first, U second) {
    std::cout << "(" << first << ", " << second << ")" << std::endl;
}

// Function template for array operations
template<typename T, int SIZE>
void printArray(T (&arr)[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Using with different types
    std::cout << "Max of 10 and 20: " << maximum(10, 20) << std::endl;
    std::cout << "Max of 3.5 and 2.1: " << maximum(3.5, 2.1) << std::endl;
    std::cout << "Max of 'a' and 'z': " << maximum('a', 'z') << std::endl;
    
    // Mixed types
    printPair(42, "Hello");
    printPair(3.14, true);
    
    // Array template
    int numbers[] = {1, 2, 3, 4, 5};
    printArray(numbers);
    
    return 0;
}
```

### Class Template Example
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    // Constructor
    Stack() = default;
    
    // Push element onto stack
    void push(const T& item) {
        data.push_back(item);
    }
    
    // Pop element from stack
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty!");
        }
        T item = data.back();
        data.pop_back();
        return item;
    }
    
    // Check if stack is empty
    bool isEmpty() const {
        return data.empty();
    }
    
    // Get current size
    size_t size() const {
        return data.size();
    }
    
    // Display stack contents
    void display() const {
        std::cout << "Stack contents: ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Integer stack
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    
    std::cout << "Popped: " << intStack.pop() << std::endl;
    intStack.display();
    
    // String stack
    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("C++");
    stringStack.display();
    
    return 0;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Function Template Library
Create a library of template functions:

**Tasks:**
1. Template function to find minimum of two values
2. Template function to swap two values
3. Template function to calculate average of an array
4. Template function to search for an element in an array

### Activity 2: Generic Container Classes
Implement template container classes:

**Tasks:**
1. Template Queue class
2. Template Pair class for key-value pairs
3. Template Vector class (simplified)
4. Template Calculator class

### Activity 3: Template Utility Functions
Create utility functions using templates:

**Tasks:**
1. Template function to print any container
2. Template function to sort any array
3. Template function to find maximum element
4. Template function to count occurrences

---

## Key Concepts

### 1. Template Parameter Deduction
```cpp
// Compiler deduces T as int
auto result = maximum(10, 20);

// Compiler deduces T as double
auto result2 = maximum(3.14, 2.71);

// Explicit specification
auto result3 = maximum<double>(10, 20);  // 10 and 20 converted to double
```

### 2. Template Specialization
```cpp
// General template
template<typename T>
void print(T value) {
    std::cout << value << std::endl;
}

// Specialization for strings
template<>
void print<std::string>(std::string value) {
    std::cout << "String: " << value << std::endl;
}
```

### 3. Non-Type Template Parameters
```cpp
template<typename T, int SIZE>
class FixedArray {
private:
    T data[SIZE];
    
public:
    T& operator[](int index) {
        return data[index];
    }
    
    int size() const { return SIZE; }
};

// Usage
FixedArray<int, 10> numbers;  // Array of 10 integers
FixedArray<double, 5> values; // Array of 5 doubles
```

---

## Best Practices

### 1. Template Design
- Use meaningful template parameter names
- Prefer `typename` over `class` for clarity
- Keep templates simple and focused
- Document template requirements

### 2. Type Safety
- Use `const` references for large objects
- Validate template parameters when possible
- Consider template specialization for special cases
- Use `static_assert` for compile-time checks

### 3. Performance Considerations
- Templates are instantiated at compile time
- Each instantiation creates separate code
- Be aware of code bloat with many instantiations
- Use template specialization to optimize specific types

---

## Common Pitfalls

### 1. Template Definition Location
```cpp
// Wrong: Template definition in .cpp file
// This won't work - templates must be in header files

// Correct: Template definition in header file
// templates.h
template<typename T>
void function(T value) {
    // Implementation here
}
```

### 2. Template Instantiation Issues
```cpp
// Problem: Template instantiation with incompatible types
template<typename T>
T add(T a, T b) {
    return a + b;
}

// This might not work if T doesn't support +
add("Hello", "World");  // Error: no operator+ for strings
```

### 3. Template Parameter Mismatch
```cpp
// Problem: Multiple template parameters
template<typename T, typename U>
void process(T t, U u) {
    // Implementation
}

// Error: Too few template arguments
process(10, 20);  // Need to specify both T and U or use auto
```

---

## Assessment

### Quiz Questions
1. What is the difference between function templates and function overloading?
2. When are templates instantiated?
3. What is template parameter deduction?
4. Why must template definitions be in header files?

### Practical Assessment
- Implement working function templates
- Create functional class templates
- Demonstrate template instantiation
- Use templates to solve real problems

---

## Homework Assignment

### Task 1: Template Math Library
Create a template math library with functions for:
1. Basic arithmetic operations (add, subtract, multiply, divide)
2. Statistical functions (mean, variance, standard deviation)
3. Comparison functions (max, min, equal)
4. Mathematical constants and utilities

### Task 2: Generic Data Structures
Implement template versions of:
1. Linked list
2. Binary tree
3. Hash table
4. Priority queue

### Task 3: Template Algorithms
Create template algorithms for:
1. Sorting (bubble sort, selection sort)
2. Searching (linear search, binary search)
3. Array operations (reverse, rotate, shuffle)
4. Mathematical operations (factorial, fibonacci)

---

## Code Examples for Practice

### Complete Template Example
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Template function for finding maximum element
template<typename Iterator>
auto findMax(Iterator begin, Iterator end) -> decltype(*begin) {
    if (begin == end) {
        throw std::runtime_error("Empty range!");
    }
    
    auto maxElement = begin;
    for (auto it = begin + 1; it != end; ++it) {
        if (*it > *maxElement) {
            maxElement = it;
        }
    }
    return *maxElement;
}

// Template class for generic container
template<typename T>
class SimpleVector {
private:
    std::vector<T> data;
    
public:
    void add(const T& item) {
        data.push_back(item);
    }
    
    T get(size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }
    
    size_t size() const {
        return data.size();
    }
    
    void sort() {
        std::sort(data.begin(), data.end());
    }
    
    void display() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Test with integers
    SimpleVector<int> intVector;
    intVector.add(30);
    intVector.add(10);
    intVector.add(50);
    intVector.add(20);
    
    std::cout << "Original: ";
    intVector.display();
    
    intVector.sort();
    std::cout << "Sorted: ";
    intVector.display();
    
    // Test with strings
    SimpleVector<std::string> stringVector;
    stringVector.add("Charlie");
    stringVector.add("Alice");
    stringVector.add("Bob");
    
    std::cout << "Original strings: ";
    stringVector.display();
    
    stringVector.sort();
    std::cout << "Sorted strings: ";
    stringVector.display();
    
    return 0;
}
```

---

## Next Lesson Preview

In the next lesson (Week 3), we'll learn about STL containers:
- Sequential containers (vector, list, deque)
- Container operations and iterators
- Performance characteristics of different containers

Make sure you understand template syntax and instantiation before moving on!