# Lesson 8.1: Statements

## Learning Objectives
- Master different types of C++ statements
- Understand expression statements and declarations
- Learn compound statements and blocks
- Practice with selection statements (if, switch)
- Explore iteration statements (for, while, do-while)

## Prerequisites
- Completed Lesson 7.3 (Enumerations)
- Understanding of expressions and operators
- Basic knowledge of control flow

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Statement Fundamentals

#### What are Statements?
- **Executable units:** Statements are the executable units of a C++ program
- **Control flow:** Statements control the execution flow of a program
- **Termination:** Most statements end with a semicolon
- **Categories:** Expression, declaration, compound, selection, iteration

#### Statement Categories
```cpp
// Expression statement
x = 5;                    // Assignment
++i;                      // Increment
function_call();          // Function call

// Declaration statement
int x = 10;
double y;

// Compound statement (block)
{
    int temp = x;
    x = y;
    y = temp;
}
```

### 2. Selection Statements

#### if Statement
```cpp
if (condition) {
    // Execute if condition is true
}

if (condition) {
    // Execute if condition is true
} else {
    // Execute if condition is false
}

if (condition1) {
    // Execute if condition1 is true
} else if (condition2) {
    // Execute if condition2 is true
} else {
    // Execute if all conditions are false
}
```

#### switch Statement
```cpp
switch (expression) {
    case value1:
        // Execute if expression == value1
        break;
    case value2:
        // Execute if expression == value2
        break;
    default:
        // Execute if no case matches
        break;
}
```

### 3. Iteration Statements

#### for Loop
```cpp
for (initialization; condition; increment) {
    // Loop body
}

for (int i = 0; i < 10; ++i) {
    std::cout << i << std::endl;
}
```

#### while Loop
```cpp
while (condition) {
    // Loop body
}

int i = 0;
while (i < 10) {
    std::cout << i << std::endl;
    ++i;
}
```

#### do-while Loop
```cpp
do {
    // Loop body
} while (condition);

int i = 0;
do {
    std::cout << i << std::endl;
    ++i;
} while (i < 10);
```

---

## Demonstration (25 minutes)

### Statement Examples
```cpp
#include <iostream>

void demonstrateStatements() {
    std::cout << "=== Statement Demonstration ===" << std::endl;
    
    // Expression statements
    int x = 5;
    int y = 10;
    
    // Selection statements
    if (x < y) {
        std::cout << "x is less than y" << std::endl;
    } else {
        std::cout << "x is not less than y" << std::endl;
    }
    
    // Iteration statements
    std::cout << "Counting from 1 to 5:" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Statement Implementation
Implement different statement types:

**Tasks:**
1. Create expression statements with various operations
2. Implement selection statements with multiple conditions
3. Build iteration statements with different loop types
4. Practice compound statements and blocks

### Activity 2: Control Flow
Apply control flow to real problems:

**Tasks:**
1. Implement a menu system
2. Create a number guessing game
3. Build a simple calculator
4. Design a data validation system

### Activity 3: Loop Optimization
Practice loop optimization:

**Tasks:**
1. Optimize loop performance
2. Handle loop edge cases
3. Implement nested loops
4. Use loop control statements

---

## Key Concepts

### 1. Statement Execution
```cpp
// Sequential execution
int a = 1;
int b = 2;
int c = a + b;  // Executed in order
```

### 2. Conditional Execution
```cpp
// Conditional execution
if (x > 0) {
    std::cout << "Positive" << std::endl;
} else if (x < 0) {
    std::cout << "Negative" << std::endl;
} else {
    std::cout << "Zero" << std::endl;
}
```

### 3. Repetitive Execution
```cpp
// Repetitive execution
for (int i = 0; i < n; ++i) {
    process(i);
}
```

---

## Best Practices

### 1. Statement Clarity
- Use meaningful variable names
- Keep statements simple and focused
- Avoid deeply nested structures
- Use appropriate loop types

### 2. Control Flow
- Use early returns to reduce nesting
- Prefer switch for multiple conditions
- Use break and continue appropriately
- Handle edge cases properly

### 3. Performance
- Minimize loop overhead
- Use appropriate loop bounds
- Avoid unnecessary computations
- Consider loop unrolling for critical code

---

## Common Pitfalls

### 1. Missing Semicolons
```cpp
// Wrong: missing semicolon
int x = 5
std::cout << x << std::endl;

// Correct: semicolon required
int x = 5;
std::cout << x << std::endl;
```

### 2. Infinite Loops
```cpp
// Wrong: infinite loop
int i = 0;
while (i < 10) {
    std::cout << i << std::endl;
    // Forgot to increment i!
}

// Correct: increment loop variable
int i = 0;
while (i < 10) {
    std::cout << i << std::endl;
    ++i;
}
```

### 3. Switch Statement Issues
```cpp
// Wrong: missing break statements
switch (value) {
    case 1:
        std::cout << "One" << std::endl;
        // Missing break!
    case 2:
        std::cout << "Two" << std::endl;
        break;
}

// Correct: include break statements
switch (value) {
    case 1:
        std::cout << "One" << std::endl;
        break;
    case 2:
        std::cout << "Two" << std::endl;
        break;
}
```

---

## Assessment

### Quiz Questions
1. What are the different types of C++ statements?
2. What is the difference between if and switch statements?
3. When should you use for vs while loops?
4. What happens when you forget a break statement in a switch?

### Practical Assessment
- Implement working statement code
- Use control flow statements correctly
- Handle edge cases and error conditions
- Apply statements to solve problems

---

## Homework Assignment

### Task 1: Statement Library
Implement:
1. A collection of utility functions using different statements
2. A menu system with selection statements
3. A data processing system with iteration statements
4. A validation system with compound statements

### Task 2: Control Flow Applications
Apply control flow to:
1. Game logic implementations
2. Data analysis algorithms
3. User interface systems
4. Error handling mechanisms

### Task 3: Loop Analysis
Analyze:
1. Performance characteristics of different loops
2. Loop optimization techniques
3. Nested loop complexity
4. Loop termination conditions

---

## Next Lesson Preview

In the next lesson, we'll learn about expressions:
- Expression evaluation and precedence
- Operator overloading
- Type conversions in expressions
- Expression optimization

Make sure you understand statements before moving on!
