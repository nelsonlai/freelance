# Lesson 1.4: Functions and Basic I/O

## Learning Objectives
- Learn function declaration and definition
- Master parameter passing mechanisms
- Understand return types and return statements
- Learn basic I/O operations
- Practice function design and usage

## Prerequisites
- Completed Lesson 1.3 (Control Structures)
- Understanding of variables and data types
- Basic knowledge of program structure

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Function Basics

#### Function Declaration vs Definition
- **Declaration:** Tells compiler about function's signature
- **Definition:** Actually implements the function
- **Prototype:** Function declaration without body

#### Function Syntax
```cpp
return_type function_name(parameter_list) {
    // Function body
    return value; // Optional
}
```

### 2. Parameter Passing

#### By Value
```cpp
void function(int value) {
    // Receives a copy of the argument
}
```

#### By Reference
```cpp
void function(int& reference) {
    // Receives direct access to the argument
}
```

#### By Const Reference
```cpp
void function(const std::string& str) {
    // Receives read-only access to the argument
}
```

### 3. Return Types

#### Void Functions
```cpp
void printMessage() {
    std::cout << "Hello, World!" << std::endl;
}
```

#### Value-Returning Functions
```cpp
int add(int a, int b) {
    return a + b;
}
```

### 4. Basic I/O Operations

#### Input Operations
```cpp
std::cin >> variable;           // Read single value
std::getline(std::cin, string); // Read entire line
```

#### Output Operations
```cpp
std::cout << value << std::endl; // Print with newline
std::cout << value;               // Print without newline
```

---

## Demonstration (25 minutes)

### Basic Function Examples
```cpp
#include <iostream>
#include <string>

// Function declarations
int add(int a, int b);
double multiply(double x, double y);
void greet(const std::string& name);
bool isEven(int number);

int main() {
    // Function calls
    int sum = add(10, 20);
    std::cout << "Sum: " << sum << std::endl;
    
    double product = multiply(3.5, 2.0);
    std::cout << "Product: " << product << std::endl;
    
    greet("Alice");
    
    std::cout << "Is 7 even? " << (isEven(7) ? "Yes" : "No") << std::endl;
    
    return 0;
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

double multiply(double x, double y) {
    return x * y;
}

void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

bool isEven(int number) {
    return number % 2 == 0;
}
```

### I/O Examples
```cpp
#include <iostream>
#include <string>

void demonstrateIO() {
    // Output examples
    std::cout << "Enter your name: ";
    
    std::string name;
    std::getline(std::cin, name);
    
    std::cout << "Hello, " << name << "!" << std::endl;
    
    // Number input
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;
    
    std::cout << "You are " << age << " years old." << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Calculator Functions
Create a calculator with separate functions for each operation:

**Tasks:**
1. Create functions for add, subtract, multiply, divide
2. Handle division by zero
3. Create a main function that uses all operations
4. Add input validation

### Activity 2: String Processing Functions
Create functions to manipulate strings:

**Tasks:**
1. Function to count characters in a string
2. Function to reverse a string
3. Function to check if string is palindrome
4. Function to convert string to uppercase

### Activity 3: Number Processing Functions
Create mathematical utility functions:

**Tasks:**
1. Function to find maximum of two numbers
2. Function to find minimum of three numbers
3. Function to calculate factorial
4. Function to check if number is prime

---

## Key Concepts

### 1. Function Design Principles
```cpp
// Good: Single responsibility
double calculateArea(double length, double width) {
    return length * width;
}

// Good: Clear parameter names
void displayStudentInfo(const std::string& name, int age, double gpa) {
    std::cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << std::endl;
}
```

### 2. Parameter Passing Guidelines
```cpp
// Use const reference for large objects
void processString(const std::string& text);

// Use reference for output parameters
void getTwoNumbers(int& a, int& b);

// Use value for simple types
int add(int a, int b);
```

### 3. Return Value Best Practices
```cpp
// Return meaningful values
bool isValid(int value) {
    return value > 0 && value < 100;
}

// Handle error cases
double divide(double a, double b) {
    if (b == 0) {
        std::cout << "Error: Division by zero!" << std::endl;
        return 0.0; // Or throw an exception
    }
    return a / b;
}
```

---

## Common Patterns

### 1. Input Validation Function
```cpp
int getValidInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (value >= min && value <= max) {
            return value;
        }
        std::cout << "Invalid input. Please enter a value between " 
                  << min << " and " << max << std::endl;
    }
}
```

### 2. Menu System Function
```cpp
int showMenu() {
    std::cout << "\n=== Menu ===" << std::endl;
    std::cout << "1. Option 1" << std::endl;
    std::cout << "2. Option 2" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter choice: ";
    
    int choice;
    std::cin >> choice;
    return choice;
}
```

### 3. Utility Functions
```cpp
void clearScreen() {
    // Platform-specific screen clearing
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseProgram() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
```

---

## Best Practices

### 1. Function Naming
- Use descriptive names: `calculateArea`, `isValid`, `displayMenu`
- Use verbs for functions that do something
- Use adjectives for functions that return boolean values

### 2. Parameter Design
- Keep parameter lists short (ideally 3 or fewer)
- Use const reference for large objects
- Group related parameters together

### 3. Return Values
- Return meaningful values
- Handle error cases appropriately
- Use void for functions that don't need to return anything

---

## Assessment

### Quiz Questions
1. What is the difference between function declaration and definition?
2. When should you use const reference parameters?
3. What are the benefits of using functions?
4. How do you handle input validation in functions?

### Practical Assessment
- Create a working calculator program with functions
- Implement string processing functions
- Build a menu-driven program
- Demonstrate proper function design

---

## Homework Assignment

### Task 1: Grade Calculator with Functions
Create a program with functions to:
1. Input student information
2. Calculate letter grade from percentage
3. Calculate GPA from letter grades
4. Display student report

### Task 2: Text Processing Toolkit
Implement functions for:
1. Word count in text
2. Character frequency analysis
3. Text encryption (simple substitution)
4. Text formatting (justify, center)

### Task 3: Mathematical Functions Library
Create functions for:
1. Statistical calculations (mean, median, mode)
2. Geometric calculations (area, perimeter, volume)
3. Number theory (prime factorization, GCD, LCM)
4. Trigonometric approximations

---

## Code Examples for Practice

### Complete Calculator Program
```cpp
#include <iostream>

// Function declarations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
void displayResult(double result);
int getMenuChoice();

int main() {
    int choice;
    double num1, num2, result;
    
    do {
        choice = getMenuChoice();
        
        if (choice >= 1 && choice <= 4) {
            std::cout << "Enter first number: ";
            std::cin >> num1;
            std::cout << "Enter second number: ";
            std::cin >> num2;
            
            switch (choice) {
                case 1:
                    result = add(num1, num2);
                    break;
                case 2:
                    result = subtract(num1, num2);
                    break;
                case 3:
                    result = multiply(num1, num2);
                    break;
                case 4:
                    result = divide(num1, num2);
                    break;
            }
            
            displayResult(result);
        }
    } while (choice != 5);
    
    return 0;
}

// Function implementations
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        std::cout << "Error: Division by zero!" << std::endl;
        return 0.0;
    }
    return a / b;
}

void displayResult(double result) {
    std::cout << "Result: " << result << std::endl;
}

int getMenuChoice() {
    std::cout << "\n=== Calculator Menu ===" << std::endl;
    std::cout << "1. Add" << std::endl;
    std::cout << "2. Subtract" << std::endl;
    std::cout << "3. Multiply" << std::endl;
    std::cout << "4. Divide" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter choice: ";
    
    int choice;
    std::cin >> choice;
    return choice;
}
```

---

## Next Lesson Preview

In the next lesson (Week 2), we'll start object-oriented programming:
- Class definition and object creation
- Access specifiers (public, private, protected)
- Member variables and functions
- Encapsulation principles

Make sure you're comfortable with functions and basic I/O before moving on!
