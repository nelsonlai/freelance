# Lesson 8.3: Functions

## Learning Objectives
- Master function declaration and definition
- Understand function parameters and return values
- Learn function overloading and templates
- Practice with lambda expressions
- Explore function objects and callable types

## Prerequisites
- Completed Lesson 8.2 (Expressions)
- Understanding of basic C++ syntax
- Knowledge of data types and operators

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Function Fundamentals

#### What are Functions?
- **Reusable code blocks:** Functions encapsulate reusable code
- **Parameters:** Functions can accept input parameters
- **Return values:** Functions can return values to the caller
- **Scope:** Functions have their own scope and local variables

#### Function Declaration and Definition
```cpp
// Function declaration (prototype)
int add(int a, int b);

// Function definition
int add(int a, int b) {
    return a + b;
}

// Function call
int result = add(5, 3);
```

### 2. Function Parameters

#### Parameter Types
```cpp
// Value parameters (copy)
void function1(int x) {
    x = 10;  // Modifies local copy
}

// Reference parameters
void function2(int& x) {
    x = 10;  // Modifies original variable
}

// Const reference parameters
void function3(const int& x) {
    // x = 10;  // Error: cannot modify const reference
    std::cout << x << std::endl;
}

// Pointer parameters
void function4(int* x) {
    *x = 10;  // Modifies value pointed to
}
```

#### Default Parameters
```cpp
void greet(const std::string& name = "World") {
    std::cout << "Hello, " << name << "!" << std::endl;
}

greet();           // "Hello, World!"
greet("Alice");    // "Hello, Alice!"
```

### 3. Function Overloading

#### Overloaded Functions
```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

std::string add(const std::string& a, const std::string& b) {
    return a + b;
}
```

#### Function Templates
```cpp
template<typename T>
T add(T a, T b) {
    return a + b;
}

// Usage
int result1 = add<int>(5, 3);
double result2 = add<double>(3.14, 2.71);
```

---

## Demonstration (25 minutes)

### Function Examples
```cpp
#include <iostream>
#include <string>

// Function declaration
int multiply(int a, int b);

// Function definition
int multiply(int a, int b) {
    return a * b;
}

// Function with default parameters
void print_info(const std::string& name, int age = 0) {
    std::cout << "Name: " << name;
    if (age > 0) {
        std::cout << ", Age: " << age;
    }
    std::cout << std::endl;
}

void demonstrateFunctions() {
    std::cout << "=== Function Demonstration ===" << std::endl;
    
    int result = multiply(4, 5);
    std::cout << "4 * 5 = " << result << std::endl;
    
    print_info("Alice");
    print_info("Bob", 25);
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Function Implementation
Implement various functions:

**Tasks:**
1. Create mathematical utility functions
2. Implement string manipulation functions
3. Build data processing functions
4. Design validation functions

### Activity 2: Function Overloading
Practice function overloading:

**Tasks:**
1. Create overloaded arithmetic functions
2. Implement overloaded I/O functions
3. Build overloaded utility functions
4. Design overloaded comparison functions

### Activity 3: Advanced Functions
Work with advanced function features:

**Tasks:**
1. Implement function templates
2. Create lambda expressions
3. Build function objects
4. Design callback functions

---

## Key Concepts

### 1. Function Scope
```cpp
void function() {
    int local_var = 42;  // Local variable
    // local_var is destroyed when function ends
}

int global_var = 100;    // Global variable
```

### 2. Function Recursion
```cpp
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

### 3. Lambda Expressions
```cpp
auto lambda = [](int x) -> int {
    return x * x;
};

int result = lambda(5);  // result = 25
```

---

## Best Practices

### 1. Function Design
- Keep functions focused and single-purpose
- Use meaningful function names
- Limit parameter count
- Provide clear documentation

### 2. Parameter Passing
- Use const references for large objects
- Pass by value for small, simple types
- Use pointers for optional parameters
- Consider move semantics for large objects

### 3. Return Values
- Use appropriate return types
- Return by value for small objects
- Return by reference for large objects
- Use std::optional for optional returns

---

## Common Pitfalls

### 1. Missing Return Statement
```cpp
// Wrong: missing return statement
int function() {
    std::cout << "Hello" << std::endl;
    // Missing return statement!
}

// Correct: include return statement
int function() {
    std::cout << "Hello" << std::endl;
    return 0;
}
```

### 2. Parameter Mismatch
```cpp
// Wrong: parameter type mismatch
void function(int x) { /* ... */ }
function(3.14);  // Implicit conversion

// Correct: explicit conversion
function(static_cast<int>(3.14));
```

### 3. Infinite Recursion
```cpp
// Wrong: infinite recursion
int bad_factorial(int n) {
    return n * bad_factorial(n - 1);  // No base case!
}

// Correct: include base case
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

---

## Assessment

### Quiz Questions
1. What is the difference between function declaration and definition?
2. How do you pass parameters by reference vs by value?
3. What is function overloading and when should you use it?
4. How do lambda expressions work?

### Practical Assessment
- Implement working functions
- Use function parameters correctly
- Apply function overloading appropriately
- Handle return values properly

---

## Homework Assignment

### Task 1: Function Library
Implement:
1. A collection of mathematical utility functions
2. String processing functions
3. Data validation functions
4. Algorithm utility functions

### Task 2: Function Applications
Apply functions to:
1. Data processing algorithms
2. User interface components
3. Game logic systems
4. System programming tasks

### Task 3: Function Analysis
Analyze:
1. Function performance characteristics
2. Parameter passing efficiency
3. Function call overhead
4. Recursion vs iteration trade-offs

---

## Next Lesson Preview

In the next lesson, we'll learn about exception handling:
- Exception throwing and catching
- Exception safety and RAII
- Custom exception classes
- Exception specifications

Make sure you understand functions before moving on!
