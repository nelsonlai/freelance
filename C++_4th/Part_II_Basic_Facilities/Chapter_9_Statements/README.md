# Chapter 9: Statements

## 📘 Learning Objectives

After completing this chapter, you will:
- Master all C++ control flow statements
- Understand statement syntax and semantics
- Learn when to use different control structures
- Master nested and complex control flows
- Understand statement scope and lifetime

## 🎯 Key Concepts

### 1. Expression Statements

- **Expression statements**: Execute expressions for side effects
- **Null statements**: Empty statements using semicolon
- **Compound statements**: Blocks of statements in braces

### 2. Selection Statements

- **if statement**: Conditional execution
- **if-else statement**: Two-way branching
- **switch statement**: Multi-way branching
- **Nested selection**: Complex decision making

### 3. Iteration Statements

- **while loop**: Pre-test loop
- **do-while loop**: Post-test loop
- **for loop**: Counting loop
- **Range-based for loop**: Modern C++ iteration

### 4. Jump Statements

- **break**: Exit loops and switch
- **continue**: Skip loop iteration
- **return**: Exit functions
- **goto**: Unconditional jump (avoid)

### 5. Declaration Statements

- **Local declarations**: Variables in blocks
- **Initialization**: Various initialization methods
- **Scope**: Variable visibility and lifetime

## 🧩 Practice Exercises

### Exercise 9.1: Control Flow Practice
Create programs using different control structures.

### Exercise 9.2: Nested Statements
Implement complex nested control flows.

### Exercise 9.3: Loop Variations
Demonstrate different loop types and patterns.

### Exercise 9.4: Statement Scope
Study variable scope and lifetime in statements.

## 💻 Code Examples

### Basic Control Structures
```cpp
#include <iostream>
#include <vector>

int main() {
    // if statement
    int x = 42;
    if (x > 0) {
        std::cout << "x is positive" << std::endl;
    }
    
    // if-else statement
    if (x % 2 == 0) {
        std::cout << "x is even" << std::endl;
    } else {
        std::cout << "x is odd" << std::endl;
    }
    
    // switch statement
    switch (x % 3) {
        case 0:
            std::cout << "x is divisible by 3" << std::endl;
            break;
        case 1:
            std::cout << "x mod 3 is 1" << std::endl;
            break;
        case 2:
            std::cout << "x mod 3 is 2" << std::endl;
            break;
        default:
            std::cout << "This should never happen" << std::endl;
            break;
    }
    
    return 0;
}
```

### Loop Statements
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // for loop
    std::cout << "For loop: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // while loop
    std::cout << "While loop: ";
    int i = 0;
    while (i < 5) {
        std::cout << i << " ";
        ++i;
    }
    std::cout << std::endl;
    
    // do-while loop
    std::cout << "Do-while loop: ";
    i = 0;
    do {
        std::cout << i << " ";
        ++i;
    } while (i < 5);
    std::cout << std::endl;
    
    // Range-based for loop
    std::cout << "Range-based for: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Choose appropriate control structures** for the task
2. **Use braces consistently** for compound statements
3. **Avoid deep nesting** - consider refactoring
4. **Use range-based for loops** when possible
5. **Avoid goto statements** - use structured alternatives

## 🔗 Next Steps

After mastering statements, proceed to Chapter 10 to learn about expressions and operators.

## 📚 Additional Resources

- C++ Reference: Statements
- C++ Core Guidelines: Control Flow
- Practice with different control patterns
