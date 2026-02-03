# Lesson 1.3: Control Structures

## Learning Objectives
- Master conditional statements (if/else, switch)
- Learn loop constructs (for, while, do-while)
- Understand range-based for loops (C++11)
- Learn break and continue statements
- Practice nested control structures

## Prerequisites
- Completed Lesson 1.2 (Basic Program Structure and Variables)
- Understanding of variables and data types
- Basic understanding of boolean logic

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Conditional Statements

#### if/else Statements
```cpp
if (condition) {
    // Code executed if condition is true
} else if (another_condition) {
    // Code executed if another_condition is true
} else {
    // Code executed if all conditions are false
}
```

#### switch Statements
```cpp
switch (expression) {
    case value1:
        // Code for value1
        break;
    case value2:
        // Code for value2
        break;
    default:
        // Code for any other value
        break;
}
```

### 2. Loop Constructs

#### for Loop
```cpp
for (initialization; condition; increment) {
    // Code to repeat
}
```

#### while Loop
```cpp
while (condition) {
    // Code to repeat
}
```

#### do-while Loop
```cpp
do {
    // Code to repeat
} while (condition);
```

#### Range-based for Loop (C++11)
```cpp
for (const auto& element : container) {
    // Code using element
}
```

### 3. Control Flow Statements
- **break:** Exit the current loop or switch statement
- **continue:** Skip to the next iteration of the loop
- **return:** Exit the current function

---

## Demonstration (25 minutes)

### Grade Calculator Example
```cpp
#include <iostream>

char calculateGrade(double percentage) {
    if (percentage >= 90) return 'A';
    else if (percentage >= 80) return 'B';
    else if (percentage >= 70) return 'C';
    else if (percentage >= 60) return 'D';
    else return 'F';
}

int main() {
    double percentage;
    std::cout << "Enter percentage: ";
    std::cin >> percentage;
    
    char grade = calculateGrade(percentage);
    std::cout << "Grade: " << grade << std::endl;
    
    return 0;
}
```

### Loop Examples
```cpp
#include <iostream>
#include <vector>

int main() {
    // Traditional for loop
    std::cout << "Counting 1 to 5: ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    std::cout << "Vector elements: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // while loop
    int count = 0;
    std::cout << "while loop: ";
    while (count < 3) {
        std::cout << count << " ";
        ++count;
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Grade Calculator Enhancement
Enhance the grade calculator with additional features:

**Tasks:**
1. Add grade point calculation (A=4.0, B=3.0, etc.)
2. Handle multiple subjects
3. Calculate overall GPA
4. Add input validation

### Activity 2: Number Pattern Programs
Create programs that generate different number patterns:

**Tasks:**
1. Print multiplication tables
2. Generate Fibonacci sequence
3. Find prime numbers between 1 and 100
4. Create number pyramids

### Activity 3: Menu-Driven Program
Create a menu-driven calculator program:

**Tasks:**
1. Display menu options
2. Handle user choice with switch statement
3. Perform calculations based on choice
4. Allow multiple operations in one session

---

## Key Concepts

### 1. Boolean Expressions
```cpp
// Comparison operators
bool result1 = (5 > 3);        // true
bool result2 = (10 == 10);     // true
bool result3 = (7 != 5);       // true

// Logical operators
bool result4 = (true && false); // false (AND)
bool result5 = (true || false); // true (OR)
bool result6 = !true;           // false (NOT)
```

### 2. Loop Control
```cpp
// break example
for (int i = 1; i <= 10; ++i) {
    if (i == 5) break;  // Exit loop when i equals 5
    std::cout << i << " ";
}

// continue example
for (int i = 1; i <= 10; ++i) {
    if (i % 2 == 0) continue;  // Skip even numbers
    std::cout << i << " ";
}
```

### 3. Nested Control Structures
```cpp
// Nested loops
for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
        std::cout << "(" << i << "," << j << ") ";
    }
    std::cout << std::endl;
}
```

---

## Common Patterns

### 1. Input Validation Loop
```cpp
int getValidInput() {
    int value;
    while (true) {
        std::cout << "Enter a positive number: ";
        std::cin >> value;
        if (value > 0) break;
        std::cout << "Invalid input. Try again." << std::endl;
    }
    return value;
}
```

### 2. Countdown Loop
```cpp
for (int i = 10; i >= 1; --i) {
    std::cout << i << " ";
}
std::cout << "Blast off!" << std::endl;
```

### 3. Accumulation Pattern
```cpp
int sum = 0;
for (int i = 1; i <= 100; ++i) {
    sum += i;
}
std::cout << "Sum of 1 to 100: " << sum << std::endl;
```

---

## Best Practices

### 1. Loop Efficiency
- Use prefix increment (`++i`) instead of postfix (`i++`) in loops
- Minimize work inside loops
- Use appropriate loop type for the task

### 2. Conditional Logic
- Use meaningful variable names for boolean expressions
- Avoid deeply nested conditions
- Use early returns to reduce nesting

### 3. Switch Statements
- Always include `break` statements
- Use `default` case for error handling
- Consider using `enum` or `const` for case values

---

## Assessment

### Quiz Questions
1. What is the difference between `break` and `continue`?
2. When should you use a `for` loop vs a `while` loop?
3. What is the purpose of the `default` case in a switch statement?
4. How does a range-based for loop work?

### Practical Assessment
- Create a working grade calculator program
- Implement a number pattern generator
- Build a menu-driven application
- Demonstrate proper use of loops and conditions

---

## Homework Assignment

### Task 1: Enhanced Grade Calculator
Create a program that:
1. Takes input for multiple subjects
2. Calculates individual grades and GPA
3. Displays a summary report
4. Includes input validation

### Task 2: Number Games
Implement programs for:
1. Guessing game with hints
2. Multiplication table generator
3. Prime number finder
4. Number sequence generator

### Task 3: Text Processing
Create a program that:
1. Counts characters, words, and lines in text
2. Finds the longest word
3. Replaces specific characters
4. Converts text to uppercase/lowercase

---

## Code Examples for Practice

### Simple Calculator with Switch
```cpp
#include <iostream>

int main() {
    double num1, num2, result;
    char operation;
    
    std::cout << "Enter first number: ";
    std::cin >> num1;
    
    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> operation;
    
    std::cout << "Enter second number: ";
    std::cin >> num2;
    
    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                std::cout << "Error: Division by zero!" << std::endl;
                return 1;
            }
            break;
        default:
            std::cout << "Invalid operation!" << std::endl;
            return 1;
    }
    
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

### Prime Number Finder
```cpp
#include <iostream>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << "Prime numbers between 1 and 100:" << std::endl;
    for (int i = 2; i <= 100; ++i) {
        if (isPrime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
```

---

## Next Lesson Preview

In the next lesson, we'll learn about functions:
- Function declaration and definition
- Parameter passing mechanisms
- Return types and return statements
- Function prototypes and forward declarations
- Function overloading basics

Make sure you're comfortable with control structures before moving on!
