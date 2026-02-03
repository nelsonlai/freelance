# Lesson 12.1: Templates Fundamentals

## Learning Objectives
- Master function templates and class templates
- Understand template instantiation and specialization
- Learn template parameters and constraints
- Practice with template metaprogramming basics
- Explore modern template features and best practices

## Prerequisites
- Completed Lesson 11.3 (Polymorphism)
- Understanding of classes and functions
- Knowledge of generic programming concepts

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Function Templates

#### Basic Function Templates
```cpp
// Function template declaration
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Multiple template parameters
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

// Template with default parameters
template<typename T, typename U = T>
T multiply(T a, U b) {
    return a * b;
}

// Usage examples
void demonstrateFunctionTemplates() {
    int int_max = maximum(10, 20);
    double double_max = maximum(3.14, 2.71);
    std::string string_max = maximum(std::string("apple"), std::string("banana"));
    
    auto result1 = add(5, 3.14);
    auto result2 = add(std::string("Hello"), std::string("World"));
    
    auto product1 = multiply(5, 3.14);
    auto product2 = multiply(5, 5);  // Uses default parameter
}
```

#### Template Specialization
```cpp
// Primary template
template<typename T>
void print(T value) {
    std::cout << "Generic: " << value << std::endl;
}

// Explicit specialization for int
template<>
void print<int>(int value) {
    std::cout << "Integer: " << value << std::endl;
}

// Partial specialization (for class templates)
template<typename T>
class Container {
    T data_;
public:
    Container(T data) : data_(data) {}
    void display() const {
        std::cout << "Generic container: " << data_ << std::endl;
    }
};

// Partial specialization for pointers
template<typename T>
class Container<T*> {
    T* data_;
public:
    Container(T* data) : data_(data) {}
    void display() const {
        std::cout << "Pointer container: " << *data_ << std::endl;
    }
};
```

### 2. Class Templates

#### Basic Class Templates
```cpp
template<typename T>
class Stack {
private:
    std::vector<T> data_;
    
public:
    void push(const T& item) {
        data_.push_back(item);
    }
    
    void pop() {
        if (!data_.empty()) {
            data_.pop_back();
        }
    }
    
    T& top() {
        if (data_.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_.back();
    }
    
    const T& top() const {
        if (data_.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_.back();
    }
    
    bool empty() const {
        return data_.empty();
    }
    
    size_t size() const {
        return data_.size();
    }
    
    void display() const {
        std::cout << "Stack contents: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Usage
void demonstrateClassTemplates() {
    Stack<int> int_stack;
    Stack<std::string> string_stack;
    
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    string_stack.push("Hello");
    string_stack.push("World");
    
    int_stack.display();
    string_stack.display();
}
```

#### Template with Multiple Parameters
```cpp
template<typename T, typename U>
class Pair {
private:
    T first_;
    U second_;
    
public:
    Pair(const T& first, const U& second) 
        : first_(first), second_(second) {}
    
    T& first() { return first_; }
    const T& first() const { return first_; }
    
    U& second() { return second_; }
    const U& second() const { return second_; }
    
    void display() const {
        std::cout << "Pair(" << first_ << ", " << second_ << ")" << std::endl;
    }
    
    // Template member function
    template<typename V>
    Pair<V, U> transformFirst(V (*func)(const T&)) {
        return Pair<V, U>(func(first_), second_);
    }
};

// Usage
void demonstrateMultipleParameters() {
    Pair<int, std::string> pair1(42, "Hello");
    Pair<double, int> pair2(3.14, 100);
    
    pair1.display();
    pair2.display();
    
    // Transform first element
    auto transformed = pair1.transformFirst([](const int& x) { return x * 2.0; });
    transformed.display();
}
```

### 3. Template Metaprogramming Basics

#### Compile-time Computations
```cpp
// Template metaprogramming for factorial
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// Base case
template<>
struct Factorial<0> {
    static const int value = 1;
};

// Template metaprogramming for Fibonacci
template<int N>
struct Fibonacci {
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static const int value = 0;
};

template<>
struct Fibonacci<1> {
    static const int value = 1;
};

// Usage
void demonstrateMetaprogramming() {
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;
    std::cout << "Fibonacci(10): " << Fibonacci<10>::value << std::endl;
}
```

#### SFINAE (Substitution Failure Is Not An Error)
```cpp
#include <type_traits>

// SFINAE example
template<typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_even(T value) {
    return value % 2 == 0;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
is_even(T value) {
    return std::fmod(value, 2.0) == 0.0;
}

// Modern SFINAE with if constexpr (C++17)
template<typename T>
bool is_even_modern(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value % 2 == 0;
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::fmod(value, 2.0) == 0.0;
    } else {
        return false;
    }
}
```

### 4. Modern Template Features

#### Variadic Templates (C++11)
```cpp
// Variadic function template
template<typename T>
void print(T&& t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void print(T&& t, Args&&... args) {
    std::cout << t << " ";
    print(std::forward<Args>(args)...);
}

// Variadic class template
template<typename... Types>
class Tuple {};

template<typename T>
class Tuple<T> {
private:
    T value_;
public:
    Tuple(T value) : value_(value) {}
    T& get() { return value_; }
    const T& get() const { return value_; }
};

template<typename T, typename... Rest>
class Tuple<T, Rest...> {
private:
    T value_;
    Tuple<Rest...> rest_;
public:
    Tuple(T value, Rest... rest) : value_(value), rest_(rest...) {}
    
    T& get() { return value_; }
    const T& get() const { return value_; }
    
    template<size_t N>
    auto get() -> decltype(rest_.template get<N-1>()) {
        return rest_.template get<N-1>();
    }
};
```

#### Template Constraints (C++20)
```cpp
#include <concepts>

// Concept definition
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Constrained template
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

// Concept with requirements
template<typename T>
concept Printable = requires(T t) {
    std::cout << t;
};

template<Printable T>
void print_value(T value) {
    std::cout << "Value: " << value << std::endl;
}
```

---

## Demonstration (25 minutes)

### Template Examples
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>

// Generic container template
template<typename T>
class GenericContainer {
private:
    std::vector<T> data_;
    
public:
    void add(const T& item) {
        data_.push_back(item);
    }
    
    void remove(const T& item) {
        auto it = std::find(data_.begin(), data_.end(), item);
        if (it != data_.end()) {
            data_.erase(it);
        }
    }
    
    bool contains(const T& item) const {
        return std::find(data_.begin(), data_.end(), item) != data_.end();
    }
    
    size_t size() const {
        return data_.size();
    }
    
    void display() const {
        std::cout << "Container contents: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    // Template member function
    template<typename U>
    GenericContainer<U> transform(U (*func)(const T&)) const {
        GenericContainer<U> result;
        for (const auto& item : data_) {
            result.add(func(item));
        }
        return result;
    }
};

// Generic algorithm template
template<typename Container, typename Predicate>
auto filter(const Container& container, Predicate pred) {
    Container result;
    for (const auto& item : container) {
        if (pred(item)) {
            result.add(item);
        }
    }
    return result;
}

void demonstrateTemplates() {
    std::cout << "=== Template Demonstration ===" << std::endl;
    
    // Test with different types
    GenericContainer<int> int_container;
    GenericContainer<std::string> string_container;
    
    int_container.add(1);
    int_container.add(2);
    int_container.add(3);
    int_container.add(4);
    int_container.add(5);
    
    string_container.add("apple");
    string_container.add("banana");
    string_container.add("cherry");
    string_container.add("date");
    
    std::cout << "Integer container:" << std::endl;
    int_container.display();
    
    std::cout << "String container:" << std::endl;
    string_container.display();
    
    // Filter even numbers
    auto even_numbers = filter(int_container, [](int n) { return n % 2 == 0; });
    std::cout << "Even numbers: ";
    even_numbers.display();
    
    // Transform integers to strings
    auto string_numbers = int_container.transform([](int n) { return std::to_string(n); });
    std::cout << "Numbers as strings: ";
    string_numbers.display();
    
    // Filter strings by length
    auto long_strings = filter(string_container, [](const std::string& s) { return s.length() > 5; });
    std::cout << "Long strings: ";
    long_strings.display();
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Function Template Implementation
Implement function templates:

**Tasks:**
1. Create generic utility functions
2. Implement template specializations
3. Use template parameters and constraints
4. Test with different data types

### Activity 2: Class Template Design
Design class templates:

**Tasks:**
1. Create generic container classes
2. Implement template member functions
3. Use multiple template parameters
4. Handle template instantiation

### Activity 3: Template Metaprogramming
Apply template metaprogramming:

**Tasks:**
1. Implement compile-time computations
2. Use SFINAE techniques
3. Create template specializations
4. Explore modern template features

---

## Key Concepts

### 1. Template Instantiation
```cpp
template<typename T>
void func(T value) {
    std::cout << value << std::endl;
}

// Explicit instantiation
template void func<int>(int);
template void func<double>(double);

// Implicit instantiation
func(42);        // Instantiates func<int>
func(3.14);      // Instantiates func<double>
func("Hello");   // Instantiates func<const char*>
```

### 2. Template Parameters
```cpp
// Type parameters
template<typename T>
class Container {};

// Non-type parameters
template<int N>
class Array {};

// Template template parameters
template<template<typename> class Container, typename T>
class Wrapper {};

// Default template arguments
template<typename T = int>
class DefaultContainer {};
```

### 3. Template Specialization
```cpp
// Primary template
template<typename T>
class Vector {};

// Full specialization
template<>
class Vector<bool> {};

// Partial specialization
template<typename T>
class Vector<T*> {};
```

---

## Best Practices

### 1. Template Design
- Use meaningful template parameter names
- Provide clear documentation for template requirements
- Use concepts or SFINAE for type constraints
- Consider template instantiation costs

### 2. Template Implementation
- Put template definitions in header files
- Use explicit instantiation for common types
- Avoid unnecessary template instantiations
- Use template specialization judiciously

### 3. Template Usage
- Prefer generic algorithms over specific implementations
- Use auto for template return types
- Consider template metaprogramming for compile-time optimizations
- Test templates with various types

---

## Common Pitfalls

### 1. Template Definition Location
```cpp
// Wrong: template definition in .cpp file
// template.h
template<typename T>
void func(T value);

// template.cpp
template<typename T>
void func(T value) {  // Linker error!
    std::cout << value << std::endl;
}

// Correct: template definition in header
// template.h
template<typename T>
void func(T value) {
    std::cout << value << std::endl;
}
```

### 2. Template Instantiation Issues
```cpp
// Wrong: incomplete type
template<typename T>
class Container {
    T data_;  // T might be incomplete
};

// Correct: use pointers or references
template<typename T>
class Container {
    T* data_;  // T can be incomplete
};
```

### 3. Template Specialization Order
```cpp
// Wrong: specialization before primary template
template<>
class Vector<bool> {};  // Error!

template<typename T>
class Vector {};

// Correct: specialization after primary template
template<typename T>
class Vector {};

template<>
class Vector<bool> {};
```

---

## Assessment

### Quiz Questions
1. What is the difference between function templates and class templates?
2. When should you use template specialization?
3. What is SFINAE and how is it useful?
4. How do variadic templates work?

### Practical Assessment
- Implement function and class templates correctly
- Use template specialization appropriately
- Apply template metaprogramming techniques
- Handle template instantiation issues

---

## Homework Assignment

### Task 1: Generic Data Structures
Implement:
1. A generic linked list template
2. A generic binary tree template
3. Template specializations for specific types
4. Generic algorithms for the data structures

### Task 2: Template Metaprogramming
Create:
1. Compile-time mathematical functions
2. Type traits and type checking
3. SFINAE-based function selection
4. Template-based design patterns

### Task 3: Modern Template Features
Apply:
1. Variadic templates for generic functions
2. Template constraints and concepts
3. if constexpr for conditional compilation
4. Template parameter packs and fold expressions

---

## Next Lesson Preview

In the next lesson, we'll learn about advanced templates:
- Template metaprogramming techniques
- Template specialization and partial specialization
- Template argument deduction and forwarding
- Modern template features and best practices

Make sure you understand template fundamentals before moving on!
