# Lesson 8.2: Expressions

## Learning Objectives
- Master expression evaluation and precedence
- Understand operator overloading concepts
- Learn type conversions in expressions
- Practice with complex expressions
- Explore expression optimization techniques

## Prerequisites
- Completed Lesson 8.1 (Statements)
- Understanding of operators and operands
- Basic knowledge of data types

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Expression Fundamentals

#### What are Expressions?
- **Computational units:** Expressions compute values
- **Operators and operands:** Expressions consist of operators and operands
- **Evaluation order:** Expressions are evaluated according to precedence rules
- **Type system:** Expressions have types based on their operands

#### Expression Components
```cpp
// Simple expressions
x + y                    // Binary operator
-x                       // Unary operator
++i                      // Pre-increment
i++                      // Post-increment

// Complex expressions
(x + y) * (z - w)        // Multiple operators
function(a, b) + c       // Function call in expression
```

### 2. Operator Precedence

#### Precedence Rules
```cpp
// Precedence order (highest to lowest)
1. () [] -> .            // Function call, subscript, member access
2. ++ -- ! ~ + - * &     // Unary operators
3. * / %                 // Multiplicative
4. + -                   // Additive
5. << >>                 // Bitwise shift
6. < <= > >=             // Relational
7. == !=                 // Equality
8. &                     // Bitwise AND
9. ^                     // Bitwise XOR
10. |                    // Bitwise OR
11. &&                   // Logical AND
12. ||                   // Logical OR
13. ?:                   // Conditional
14. = += -= *= /= %=     // Assignment
15. ,                    // Comma
```

#### Precedence Examples
```cpp
int result = 2 + 3 * 4;        // = 2 + (3 * 4) = 14
int result2 = (2 + 3) * 4;     // = 5 * 4 = 20
bool flag = x > 0 && y < 10;   // = (x > 0) && (y < 10)
```

### 3. Type Conversions

#### Implicit Conversions
```cpp
int x = 5;
double y = 3.14;
double result = x + y;  // int promoted to double

char c = 'A';
int ascii = c;          // char promoted to int
```

#### Explicit Conversions
```cpp
double pi = 3.14159;
int truncated = static_cast<int>(pi);  // Explicit conversion

int value = 42;
double converted = static_cast<double>(value);
```

---

## Demonstration (25 minutes)

### Expression Examples
```cpp
#include <iostream>

void demonstrateExpressions() {
    std::cout << "=== Expression Demonstration ===" << std::endl;
    
    int x = 10, y = 5;
    
    // Arithmetic expressions
    std::cout << "x + y = " << (x + y) << std::endl;
    std::cout << "x - y = " << (x - y) << std::endl;
    std::cout << "x * y = " << (x * y) << std::endl;
    std::cout << "x / y = " << (x / y) << std::endl;
    std::cout << "x % y = " << (x % y) << std::endl;
    
    // Precedence examples
    std::cout << "2 + 3 * 4 = " << (2 + 3 * 4) << std::endl;
    std::cout << "(2 + 3) * 4 = " << ((2 + 3) * 4) << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Expression Evaluation
Practice expression evaluation:

**Tasks:**
1. Evaluate complex expressions with multiple operators
2. Apply precedence rules correctly
3. Use parentheses to control evaluation order
4. Test type conversions in expressions

### Activity 2: Operator Overloading
Implement operator overloading:

**Tasks:**
1. Overload arithmetic operators for custom types
2. Implement comparison operators
3. Create assignment operators
4. Build stream insertion operators

### Activity 3: Expression Optimization
Practice expression optimization:

**Tasks:**
1. Optimize arithmetic expressions
2. Minimize type conversions
3. Use appropriate data types
4. Implement efficient algorithms

---

## Key Concepts

### 1. Expression Evaluation
```cpp
// Expression evaluation order
int result = (a + b) * (c - d) / e;
// 1. Evaluate (a + b)
// 2. Evaluate (c - d)
// 3. Multiply results
// 4. Divide by e
```

### 2. Short-Circuit Evaluation
```cpp
// Logical AND: second operand not evaluated if first is false
if (ptr != nullptr && ptr->isValid()) {
    // ptr->isValid() only called if ptr != nullptr
}

// Logical OR: second operand not evaluated if first is true
if (value < 0 || value > 100) {
    // value > 100 only evaluated if value >= 0
}
```

### 3. Expression Types
```cpp
// Expression types
int x = 5;                    // int expression
double y = 3.14;              // double expression
bool flag = x > 0;            // bool expression
std::string str = "hello";    // string expression
```

---

## Best Practices

### 1. Expression Clarity
- Use parentheses to clarify precedence
- Break complex expressions into simpler parts
- Use meaningful variable names
- Avoid overly complex expressions

### 2. Type Safety
- Be aware of implicit conversions
- Use explicit casts when necessary
- Choose appropriate data types
- Avoid lossy conversions

### 3. Performance
- Minimize unnecessary calculations
- Use appropriate operators
- Consider expression complexity
- Profile critical expressions

---

## Common Pitfalls

### 1. Precedence Errors
```cpp
// Wrong: unexpected precedence
int result = x + y * z;  // Might not be what you intended

// Correct: use parentheses
int result = (x + y) * z;  // Clear intent
```

### 2. Type Conversion Issues
```cpp
// Wrong: unexpected type conversion
int result = 5 / 2;  // Result is 2, not 2.5

// Correct: explicit conversion
double result = static_cast<double>(5) / 2;  // Result is 2.5
```

### 3. Short-Circuit Evaluation
```cpp
// Wrong: assuming both operands are evaluated
if (ptr != nullptr && ptr->isValid()) {
    // If ptr is nullptr, ptr->isValid() is not called
}

// Correct: understand short-circuit behavior
if (ptr != nullptr) {
    if (ptr->isValid()) {
        // Both conditions checked
    }
}
```

---

## Assessment

### Quiz Questions
1. What is operator precedence and why is it important?
2. How does short-circuit evaluation work?
3. What are the different types of type conversions?
4. When should you use parentheses in expressions?

### Practical Assessment
- Evaluate complex expressions correctly
- Apply precedence rules appropriately
- Handle type conversions safely
- Optimize expressions for performance

---

## Homework Assignment

### Task 1: Expression Library
Implement:
1. A collection of utility functions with complex expressions
2. Operator overloading for custom types
3. Type conversion utilities
4. Expression evaluation tools

### Task 2: Expression Applications
Apply expressions to:
1. Mathematical computations
2. Data processing algorithms
3. Performance-critical code
4. User interface calculations

### Task 3: Expression Analysis
Analyze:
1. Expression complexity and performance
2. Type conversion overhead
3. Operator precedence implications
4. Expression optimization techniques

---

## Next Lesson Preview

In the next lesson, we'll learn about functions:
- Function declaration and definition
- Function parameters and return values
- Function overloading and templates
- Lambda expressions and function objects

Make sure you understand expressions before moving on!
