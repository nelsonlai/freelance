# Chapter 10: Expressions

## 📘 Learning Objectives

After completing this chapter, you will:
- Master C++ expression syntax and semantics
- Understand operator precedence and associativity
- Learn about type conversions in expressions
- Master arithmetic, logical, and relational operators
- Understand function calls and operator overloading

## 🎯 Key Concepts

### 1. Expression Basics

- **Expressions**: Compute values from operands and operators
- **Operators**: Symbols that perform operations
- **Operands**: Values that operators act upon
- **Precedence**: Order of operator evaluation
- **Associativity**: Order when precedence is equal

### 2. Arithmetic Operators

- **Unary operators**: +, -, ++, --
- **Binary operators**: +, -, *, /, %
- **Assignment operators**: =, +=, -=, *=, /=, %=
- **Increment/decrement**: Pre and post forms

### 3. Relational and Logical Operators

- **Relational**: ==, !=, <, >, <=, >=
- **Logical**: &&, ||, !
- **Short-circuit evaluation**: Logical operators
- **Boolean conversion**: Truth values

### 4. Bitwise Operators

- **Bitwise**: &, |, ^, ~
- **Shift operators**: <<, >>
- **Bitwise assignment**: &=, |=, ^=, <<=, >>=

### 5. Other Operators

- **Conditional operator**: ? :
- **Comma operator**: ,
- **Sizeof operator**: sizeof
- **Type cast**: (type) or static_cast<type>

### 6. Function Calls

- **Function invocation**: function_name(arguments)
- **Operator overloading**: Custom operator behavior
- **Member access**: . and ->
- **Subscripting**: []

## 🧩 Practice Exercises

### Exercise 10.1: Arithmetic Expressions
Create programs demonstrating arithmetic operations.

### Exercise 10.2: Logical Expressions
Implement complex logical expressions.

### Exercise 10.3: Bitwise Operations
Demonstrate bitwise manipulation.

### Exercise 10.4: Operator Precedence
Study operator precedence and associativity.

## 💻 Code Examples

### Arithmetic Expressions
```cpp
#include <iostream>

int main() {
    int a = 10, b = 3;
    
    // Basic arithmetic
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    std::cout << "a % b = " << (a % b) << std::endl;
    
    // Increment and decrement
    int x = 5;
    std::cout << "x = " << x << std::endl;
    std::cout << "++x = " << (++x) << std::endl;
    std::cout << "x++ = " << (x++) << std::endl;
    std::cout << "x = " << x << std::endl;
    
    return 0;
}
```

### Logical and Relational Expressions
```cpp
#include <iostream>

int main() {
    int x = 5, y = 10;
    
    // Relational operators
    std::cout << "x == y: " << (x == y) << std::endl;
    std::cout << "x != y: " << (x != y) << std::endl;
    std::cout << "x < y: " << (x < y) << std::endl;
    std::cout << "x > y: " << (x > y) << std::endl;
    
    // Logical operators
    bool a = true, b = false;
    std::cout << "a && b: " << (a && b) << std::endl;
    std::cout << "a || b: " << (a || b) << std::endl;
    std::cout << "!a: " << (!a) << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Understand precedence**: Know which operators execute first
2. **Use parentheses**: Clarify intent and override precedence
3. **Be careful with side effects**: Understand increment/decrement behavior
4. **Use logical operators efficiently**: Leverage short-circuit evaluation
5. **Understand type conversions**: Know when implicit conversions occur

## 🔗 Next Steps

After mastering expressions, proceed to Chapter 11 to learn about functions and function design.

## 📚 Additional Resources

- C++ Reference: Operators
- C++ Core Guidelines: Expressions
- Practice with operator precedence tables
