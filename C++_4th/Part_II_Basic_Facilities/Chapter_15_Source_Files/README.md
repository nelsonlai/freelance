# Chapter 15: Source Files and Programs

## 📘 Learning Objectives

After completing this chapter, you will:
- Master header and source file organization
- Understand compilation and linking process
- Learn about header guards and includes
- Master linkage and storage duration
- Understand program organization best practices

## 🎯 Key Concepts

### 1. Header Files

- **Header files**: Interface declarations (.h, .hpp)
- **Source files**: Implementation definitions (.cpp, .cc)
- **Include directives**: #include "header.h" or #include <header>
- **Header guards**: Preventing multiple inclusion

### 2. Compilation Process

- **Preprocessing**: Handle #include, #define, #ifdef
- **Compilation**: Convert source to object code
- **Linking**: Combine object files into executable
- **Static linking**: Link at compile time
- **Dynamic linking**: Link at runtime

### 3. Linkage

- **External linkage**: Accessible from other translation units
- **Internal linkage**: Accessible only within translation unit
- **No linkage**: Local variables and parameters
- **Linkage specifications**: extern "C" for C compatibility

### 4. Storage Duration

- **Static storage**: Program lifetime
- **Automatic storage**: Block lifetime
- **Dynamic storage**: Manual allocation
- **Thread storage**: Thread lifetime

### 5. Program Organization

- **Modular design**: Separate interface and implementation
- **Dependency management**: Minimize header dependencies
- **Build systems**: Make, CMake, etc.
- **Library organization**: Static and dynamic libraries

## 🧩 Practice Exercises

### Exercise 15.1: Header and Source Files
Create separate header and source files.

### Exercise 15.2: Header Guards
Implement proper header guards.

### Exercise 15.3: Linkage
Demonstrate different linkage types.

### Exercise 15.4: Build System
Create a simple build system.

## 💻 Code Examples

### Header File (example.h)
```cpp
#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <string>
#include <vector>

namespace example {
    // Function declarations
    int add(int a, int b);
    std::string get_message();
    
    // Class declaration
    class Calculator {
    private:
        int value;
        
    public:
        Calculator(int initial = 0);
        void add(int x);
        void subtract(int x);
        int get_value() const;
    };
}

#endif // EXAMPLE_H
```

### Source File (example.cpp)
```cpp
#include "example.h"
#include <iostream>

namespace example {
    // Function implementations
    int add(int a, int b) {
        return a + b;
    }
    
    std::string get_message() {
        return "Hello from example namespace!";
    }
    
    // Class implementation
    Calculator::Calculator(int initial) : value(initial) {}
    
    void Calculator::add(int x) {
        value += x;
    }
    
    void Calculator::subtract(int x) {
        value -= x;
    }
    
    int Calculator::get_value() const {
        return value;
    }
}
```

## 🎓 Key Takeaways

1. **Separate interface and implementation** in different files
2. **Use header guards** to prevent multiple inclusion
3. **Minimize header dependencies** for faster compilation
4. **Understand linkage** for proper program organization
5. **Use build systems** for complex projects

## 🔗 Next Steps

After mastering source files, proceed to Part III to learn about abstraction mechanisms.

## 📚 Additional Resources

- C++ Reference: Source Files
- C++ Core Guidelines: Source Files
- Build system documentation (Make, CMake)
