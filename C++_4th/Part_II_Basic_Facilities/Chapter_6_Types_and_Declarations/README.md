# Chapter 6: Types and Declarations

## 📘 Learning Objectives

After completing this chapter, you will:
- Master C++ fundamental types and type system
- Understand variable declarations and definitions
- Learn scope, lifetime, and initialization
- Master type conversions and casts
- Understand constants and constexpr

## 🎯 Key Concepts

### 1. Fundamental Types

C++ provides several fundamental types:
- **Integral types**: `int`, `char`, `bool`, `short`, `long`, `long long`
- **Floating-point types**: `float`, `double`, `long double`
- **Void type**: `void` (represents no value)

### 2. Type Modifiers

- **Signed/Unsigned**: `signed`, `unsigned`
- **Size modifiers**: `short`, `long`, `long long`
- **Const**: `const` (read-only)
- **Volatile**: `volatile` (may change unexpectedly)

### 3. Declarations vs Definitions

- **Declaration**: Introduces a name and specifies its type
- **Definition**: Provides the implementation for a declared name
- **One Definition Rule**: Each entity must be defined exactly once

### 4. Scope and Lifetime

- **Scope**: Region where a name is valid
- **Lifetime**: Duration for which an object exists
- **Storage duration**: Automatic, static, thread, dynamic

### 5. Initialization

- **Default initialization**: `int x;`
- **Value initialization**: `int x{};`
- **Direct initialization**: `int x(42);`
- **Copy initialization**: `int x = 42;`
- **List initialization**: `int x{42};`

## 🧩 Practice Exercises

### Exercise 6.1: Type System Exploration
Create a program that demonstrates all fundamental types and their properties.

### Exercise 6.2: Scope and Lifetime
Write programs showing different scopes and lifetimes.

### Exercise 6.3: Initialization Methods
Demonstrate different initialization techniques.

### Exercise 6.4: Type Conversions
Show implicit and explicit type conversions.

## 💻 Code Examples

### Fundamental Types
```cpp
#include <iostream>
#include <limits>

int main() {
    // Integral types
    char c = 'A';
    int i = 42;
    long l = 1000L;
    
    // Floating-point types
    float f = 3.14f;
    double d = 3.14159;
    
    // Boolean type
    bool b = true;
    
    // Display type information
    std::cout << "char: " << c << " (size: " << sizeof(char) << ")" << std::endl;
    std::cout << "int: " << i << " (size: " << sizeof(int) << ")" << std::endl;
    std::cout << "double: " << d << " (size: " << sizeof(double) << ")" << std::endl;
    
    return 0;
}
```

### Scope and Lifetime
```cpp
#include <iostream>

int global_var = 100;  // Global scope

void function_scope() {
    int local_var = 200;  // Local scope
    static int static_var = 300;  // Static storage
    
    std::cout << "Local: " << local_var << std::endl;
    std::cout << "Static: " << static_var << std::endl;
    static_var++;  // Persists between calls
}

int main() {
    std::cout << "Global: " << global_var << std::endl;
    
    function_scope();
    function_scope();  // Static variable persists
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Strong typing**: C++ requires explicit type declarations
2. **Scope matters**: Variables are only accessible within their scope
3. **Initialization**: Choose the right initialization method
4. **Type safety**: Use explicit casts when necessary
5. **Constants**: Use const and constexpr for compile-time constants

## 🔗 Next Steps

After mastering types and declarations, proceed to Chapter 7 to learn about pointers, arrays, and references.

## 📚 Additional Resources

- C++ Reference: Fundamental Types
- C++ Core Guidelines: Type Safety
- Practice with different compilers to see type size variations
