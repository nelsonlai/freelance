# Lesson 1.2: Basic Program Structure and Variables

## Learning Objectives
- Understand C++ program structure and anatomy
- Learn fundamental data types and their characteristics
- Master variable declaration and initialization methods
- Understand the `auto` keyword and type deduction
- Learn about scope and lifetime of variables

## Prerequisites
- Completed Lesson 1.1 (C++ Philosophy and Modern Programming)
- Working C++ development environment

## Duration
90 minutes

---

## Lecture Content (25 minutes)

### 1. C++ Program Structure
Every C++ program has a basic structure:

```cpp
#include <iostream>  // Preprocessor directive
using namespace std; // Optional namespace usage

int main() {         // Main function entry point
    // Program code goes here
    return 0;        // Return statement
}
```

**Key Components:**
- **Preprocessor directives** (`#include`)
- **Main function** (program entry point)
- **Statements** (instructions to the computer)
- **Return statement** (program exit)

### 2. Fundamental Data Types

#### Integer Types
- `int` - Standard integer (typically 32-bit)
- `short` - Short integer (typically 16-bit)
- `long` - Long integer (typically 32-bit or 64-bit)
- `long long` - Very long integer (typically 64-bit)
- `char` - Character (typically 8-bit)

#### Floating-Point Types
- `float` - Single precision (typically 32-bit)
- `double` - Double precision (typically 64-bit)
- `long double` - Extended precision

#### Other Types
- `bool` - Boolean (true/false)
- `void` - No type (used for functions)

### 3. Variable Declaration vs Definition
- **Declaration:** Tells compiler about a variable's type and name
- **Definition:** Actually creates the variable in memory
- In C++, declaration is usually also a definition

### 4. Initialization Methods
- **Copy initialization:** `int x = 5;`
- **Direct initialization:** `int x(5);`
- **Uniform initialization:** `int x{5};` (C++11)
- **Auto initialization:** `auto x = 5;` (C++11)

---

## Demonstration (25 minutes)

### Program Structure Example
```cpp
#include <iostream>
#include <string>

int main() {
    // Variable declarations and initializations
    std::string name = "Alice";
    int age = 25;
    double height = 5.6;
    bool isStudent = true;
    
    // Display information
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << " feet" << std::endl;
    std::cout << "Is Student: " << (isStudent ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

### Type Sizes and Ranges
```cpp
#include <iostream>
#include <climits>

int main() {
    std::cout << "Type sizes and ranges:" << std::endl;
    std::cout << "int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "char: " << sizeof(char) << " bytes" << std::endl;
    
    std::cout << "int range: " << INT_MIN << " to " << INT_MAX << std::endl;
    
    return 0;
}
```

---

## Hands-on Practice (40 minutes)

### Activity 1: Variable Creation and Display
Create variables for personal information and display them.

**Tasks:**
1. Create variables for your name, age, GPA, and student status
2. Use different initialization methods
3. Display all information in a formatted way

### Activity 2: Type Experimentation
Experiment with different data types and their behavior.

**Tasks:**
1. Create variables of different types
2. Try different initialization methods
3. Observe type sizes and ranges
4. Experiment with type conversions

### Activity 3: Auto Keyword Practice
Practice using the `auto` keyword for type deduction.

**Tasks:**
1. Use `auto` with different types
2. Compare with explicit type declarations
3. Understand when to use `auto` vs explicit types

---

## Key Concepts

### 1. Variable Scope
```cpp
int globalVar = 10;  // Global scope

int main() {
    int localVar = 20;  // Local scope
    
    {
        int blockVar = 30;  // Block scope
        // blockVar accessible here
    }
    // blockVar not accessible here
    
    return 0;
}
```

### 2. Variable Lifetime
- **Automatic variables:** Created when declared, destroyed when out of scope
- **Static variables:** Created once, persist for program lifetime
- **Global variables:** Created at program start, destroyed at program end

### 3. Constants
```cpp
const int MAX_SIZE = 100;        // Compile-time constant
constexpr int BUFFER_SIZE = 256; // Compile-time constant (C++11)
```

### 4. Type Deduction with Auto
```cpp
auto name = std::string("Hello");  // Deduced as std::string
auto number = 42;                  // Deduced as int
auto decimal = 3.14;               // Deduced as double
```

---

## Common Pitfalls and Best Practices

### Pitfalls to Avoid
1. **Uninitialized variables:** Always initialize variables
2. **Type mismatches:** Be careful with implicit conversions
3. **Scope confusion:** Understand where variables are accessible
4. **Overuse of auto:** Use explicit types when clarity is important

### Best Practices
1. **Initialize variables:** Use uniform initialization `{}` when possible
2. **Use meaningful names:** Choose descriptive variable names
3. **Prefer const:** Use `const` for values that don't change
4. **Use auto judiciously:** Use when type is obvious or verbose

---

## Assessment

### Quiz Questions
1. What is the difference between variable declaration and definition?
2. Name three initialization methods in C++.
3. What does the `auto` keyword do?
4. Explain the difference between `const` and `constexpr`.

### Practical Assessment
- Create a program with variables of different types
- Demonstrate proper initialization methods
- Use `auto` keyword appropriately
- Handle type conversions correctly

---

## Homework Assignment

### Task 1: Personal Information Program
Create a program that:
1. Declares variables for your personal information (name, age, height, etc.)
2. Uses different initialization methods
3. Uses the `auto` keyword for at least one variable
4. Displays all information in a nicely formatted way

### Task 2: Type Investigation
Create a program that:
1. Investigates the size of different data types
2. Finds the range of values for integer types
3. Demonstrates type conversion between different numeric types

### Task 3: Scope Experiment
Create a program that demonstrates:
1. Global variables
2. Local variables
3. Block scope variables
4. Variable shadowing (same name in different scopes)

---

## Code Examples for Practice

### Basic Variable Usage
```cpp
#include <iostream>
#include <string>

int main() {
    // Different initialization methods
    int age1 = 25;           // Copy initialization
    int age2(25);            // Direct initialization
    int age3{25};            // Uniform initialization (preferred)
    
    // Auto keyword usage
    auto name = std::string("Alice");
    auto salary = 50000.0;   // Deduced as double
    auto count = 10;         // Deduced as int
    
    // Display variables
    std::cout << "Age: " << age3 << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Salary: " << salary << std::endl;
    
    return 0;
}
```

### Type Size Investigation
```cpp
#include <iostream>
#include <climits>

int main() {
    std::cout << "Data Type Sizes:" << std::endl;
    std::cout << "char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "double: " << sizeof(double) << " bytes" << std::endl;
    
    std::cout << "\nInteger Ranges:" << std::endl;
    std::cout << "int: " << INT_MIN << " to " << INT_MAX << std::endl;
    
    return 0;
}
```

---

## Next Lesson Preview

In the next lesson, we'll learn about control structures:
- Conditional statements (`if`, `else`, `switch`)
- Loop constructs (`for`, `while`, `do-while`)
- Range-based for loops
- Break and continue statements

Make sure you're comfortable with variable declaration and initialization before moving on!
