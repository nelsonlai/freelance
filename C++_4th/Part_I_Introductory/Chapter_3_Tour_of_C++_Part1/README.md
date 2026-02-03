# Chapter 3: A Tour of C++ (Part 1)

## 📘 Learning Objectives

After completing this chapter, you will:
- Get a comprehensive overview of C++ language features
- Understand the fundamental building blocks of C++
- Learn about C++ design philosophy and principles
- See how different language features work together
- Understand the structure of a C++ program

## 🎯 Key Concepts

### 1. Hello, World! and Beyond

- **Basic program structure**: main function and program flow
- **Input/output**: std::cout and std::cin
- **Comments**: Single-line and multi-line comments
- **Namespaces**: std namespace usage
- **Headers**: #include directives

### 2. Types and Variables

- **Fundamental types**: int, double, char, bool
- **Variable declarations**: Type and initialization
- **Constants**: const and constexpr
- **Type inference**: auto keyword
- **User-defined types**: struct and class basics

### 3. Control Structures

- **Conditional statements**: if, else, switch
- **Loops**: for, while, do-while
- **Range-based for**: Modern loop syntax
- **Break and continue**: Loop control
- **Exception handling**: try, catch, throw

### 4. Functions

- **Function definition**: Return type, parameters, body
- **Function calls**: Passing arguments and return values
- **Function overloading**: Multiple functions with same name
- **Default arguments**: Optional parameters
- **Function templates**: Generic functions

### 5. Classes and Objects

- **Class definition**: Member variables and functions
- **Object creation**: Constructors and instantiation
- **Member access**: Public, private, protected
- **Encapsulation**: Data hiding and interface
- **Operator overloading**: Custom operators

## 🧩 Practice Exercises

### Exercise 3.1: Basic Program Structure
Write your first C++ program with input/output.

### Exercise 3.2: Types and Variables
Work with different data types and variables.

### Exercise 3.3: Control Structures
Use conditional statements and loops.

### Exercise 3.4: Functions
Create and use functions with parameters.

### Exercise 3.5: Simple Classes
Define and use basic classes.

## 💻 Code Examples

### Hello, World!
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Basic Types and Variables
```cpp
#include <iostream>
#include <string>

int main() {
    // Fundamental types
    int age = 25;
    double height = 1.75;
    char grade = 'A';
    bool isStudent = true;
    std::string name = "Alice";
    
    // Output variables
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Is student: " << (isStudent ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

### Control Structures
```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    
    // Conditional statement
    if (number > 0) {
        std::cout << "Positive number" << std::endl;
    } else if (number < 0) {
        std::cout << "Negative number" << std::endl;
    } else {
        std::cout << "Zero" << std::endl;
    }
    
    // Loop
    std::cout << "Counting from 1 to " << number << ": ";
    for (int i = 1; i <= number; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Simple Functions
```cpp
#include <iostream>
#include <string>

// Function definition
int add(int a, int b) {
    return a + b;
}

double multiply(double x, double y) {
    return x * y;
}

void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {
    // Function calls
    int sum = add(5, 3);
    std::cout << "5 + 3 = " << sum << std::endl;
    
    double product = multiply(2.5, 4.0);
    std::cout << "2.5 * 4.0 = " << product << std::endl;
    
    greet("World");
    
    return 0;
}
```

### Simple Class
```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    
public:
    // Constructor
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    // Member functions
    void introduce() {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old." << std::endl;
    }
    
    void haveBirthday() {
        age++;
        std::cout << "Happy birthday! Now I'm " << age << " years old." << std::endl;
    }
};

int main() {
    // Create objects
    Person alice("Alice", 25);
    Person bob("Bob", 30);
    
    // Use objects
    alice.introduce();
    bob.introduce();
    
    alice.haveBirthday();
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **C++ is a multi-paradigm language** supporting procedural, object-oriented, and generic programming
2. **Types are fundamental** - every variable and expression has a type
3. **Functions are building blocks** for organizing code and reusability
4. **Classes provide encapsulation** and object-oriented programming features
5. **C++ emphasizes efficiency** and performance while maintaining readability

## 🔗 Next Steps

After getting familiar with basic C++ concepts, proceed to Chapter 4 to continue the tour with more advanced features.

## 📚 Additional Resources

- C++ Reference: Basic Concepts
- C++ Core Guidelines: Getting Started
- Practice with simple C++ programs
