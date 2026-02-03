# Chapter 11: Functions

## 📘 Learning Objectives

After completing this chapter, you will:
- Master function declaration and definition
- Understand parameter passing mechanisms
- Learn function overloading and templates
- Master constexpr and inline functions
- Understand function pointers and lambdas

## 🎯 Key Concepts

### 1. Function Basics

- **Function declaration**: Interface specification
- **Function definition**: Implementation
- **Function signature**: Name, parameters, return type
- **Function call**: Invoking a function
- **Return values**: Single return or void

### 2. Parameter Passing

- **Pass by value**: Copy of argument
- **Pass by reference**: Direct access to argument
- **Pass by const reference**: Read-only access
- **Pass by pointer**: Address of argument
- **Default arguments**: Optional parameters

### 3. Function Overloading

- **Same name, different signatures**: Overloaded functions
- **Parameter type differences**: Overload resolution
- **Parameter count differences**: Overload resolution
- **Return type**: Not part of signature

### 4. Special Functions

- **constexpr functions**: Compile-time evaluation
- **inline functions**: Request for inlining
- **static functions**: File scope functions
- **friend functions**: Access to private members

### 5. Advanced Features

- **Function templates**: Generic functions
- **Function pointers**: Pointers to functions
- **Lambda functions**: Anonymous functions
- **Variadic functions**: Variable argument lists

## 🧩 Practice Exercises

### Exercise 11.1: Basic Functions
Create functions with different parameter types.

### Exercise 11.2: Function Overloading
Implement overloaded functions.

### Exercise 11.3: Function Templates
Create generic functions using templates.

### Exercise 11.4: Lambda Functions
Use lambda functions and function pointers.

## 💻 Code Examples

### Basic Functions
```cpp
#include <iostream>
#include <string>

// Function declaration
int add(int a, int b);
void print_message(const std::string& message);

// Function definition
int add(int a, int b) {
    return a + b;
}

void print_message(const std::string& message) {
    std::cout << message << std::endl;
}

int main() {
    int result = add(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;
    
    print_message("Hello, Functions!");
    
    return 0;
}
```

### Function Overloading
```cpp
#include <iostream>

// Overloaded functions
int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}

int multiply(int a, int b, int c) {
    return a * b * c;
}

int main() {
    std::cout << "multiply(3, 4) = " << multiply(3, 4) << std::endl;
    std::cout << "multiply(3.5, 4.2) = " << multiply(3.5, 4.2) << std::endl;
    std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use const references** for large objects
2. **Prefer function overloading** over default arguments
3. **Use constexpr** for compile-time computation
4. **Consider inline** for small, frequently called functions
5. **Understand parameter passing** mechanisms

## 🔗 Next Steps

After mastering functions, proceed to Chapter 12 to learn about function objects and lambdas.

## 📚 Additional Resources

- C++ Reference: Functions
- C++ Core Guidelines: Functions
- Practice with different function patterns
