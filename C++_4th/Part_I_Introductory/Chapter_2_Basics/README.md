# Chapter 2: The Basics

## 📘 Learning Objectives

After completing this chapter, you will:
- Master C++ fundamental types and variables
- Understand declarations, definitions, and scope
- Learn control structures (if, while, for)
- Master functions and their parameters
- Understand the basics of user-defined types
- Learn about const and references

## 🎯 Key Concepts

### 1. Types and Variables

C++ fundamental types:
- **Integral types**: `int`, `char`, `bool`, `short`, `long`, `long long`
- **Floating-point types**: `float`, `double`, `long double`
- **Void type**: `void` (no value)

### 2. Declarations and Definitions

- **Declaration**: Introduces a name and specifies its type
- **Definition**: Provides the implementation for a declared name
- **Scope**: Region where a name is valid

### 3. Control Structures

- **Selection**: `if`, `switch`
- **Iteration**: `while`, `for`, `do-while`
- **Jump**: `break`, `continue`, `return`, `goto`

### 4. Functions

- Function declarations and definitions
- Parameter passing (by value, by reference)
- Return values
- Function overloading

### 5. User-Defined Types

- **Structures**: `struct`
- **Enumerations**: `enum`
- **Classes**: Introduction to `class`

## 🧩 Practice Exercises

### Exercise 2.1: Variable Types and Operations
Create a program that demonstrates all fundamental types and basic operations.

### Exercise 2.2: Control Flow Practice
Write programs using different control structures to solve problems.

### Exercise 2.3: Function Fundamentals
Create various functions demonstrating parameter passing and return values.

### Exercise 2.4: User-Defined Types
Create simple structures and enumerations.

## 💻 Code Examples

### Basic Types and Variables
```cpp
#include <iostream>

int main() {
    // Fundamental types
    int age = 25;
    double height = 5.9;
    char grade = 'A';
    bool is_student = true;
    
    // Operations
    int sum = age + 10;
    double ratio = height / 2.0;
    
    std::cout << "Age: " << age << ", Sum: " << sum << std::endl;
    return 0;
}
```

### Control Structures
```cpp
#include <iostream>

int main() {
    int score = 85;
    
    // if statement
    if (score >= 90) {
        std::cout << "Grade: A" << std::endl;
    } else if (score >= 80) {
        std::cout << "Grade: B" << std::endl;
    } else {
        std::cout << "Grade: C or below" << std::endl;
    }
    
    // for loop
    for (int i = 1; i <= 5; ++i) {
        std::cout << "Count: " << i << std::endl;
    }
    
    // while loop
    int count = 0;
    while (count < 3) {
        std::cout << "While count: " << count << std::endl;
        ++count;
    }
    
    return 0;
}
```

### Functions
```cpp
#include <iostream>

// Function declaration
int add(int a, int b);
void print_message(const std::string& message);

// Function definitions
int add(int a, int b) {
    return a + b;
}

void print_message(const std::string& message) {
    std::cout << "Message: " << message << std::endl;
}

int main() {
    int result = add(10, 20);
    std::cout << "Sum: " << result << std::endl;
    
    print_message("Hello from function!");
    return 0;
}
```

## 🎓 Key Takeaways

1. **Strong typing**: C++ requires explicit type declarations
2. **Scope matters**: Variables are only accessible within their scope
3. **Functions are first-class**: Can be declared, defined, and called
4. **Control structures**: Provide program flow control
5. **User-defined types**: Allow creating custom data structures

## 🔗 Next Steps

After mastering the basics, proceed to Chapter 3 to learn about user-defined types and object-oriented programming concepts.

## 📚 Additional Resources

- C++ Reference: Fundamental Types
- C++ Core Guidelines: Type Safety
- Practice on HackerRank or LeetCode with C++
