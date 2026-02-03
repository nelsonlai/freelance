# Chapter 13: Exception Handling

## 📘 Learning Objectives

After completing this chapter, you will:
- Master exception handling patterns (try, catch, throw)
- Understand exception safety guarantees
- Learn RAII and exception safety
- Design error-safe programs
- Understand exception propagation and handling

## 🎯 Key Concepts

### 1. Exception Handling Basics

- **try block**: Code that might throw exceptions
- **catch block**: Handles specific exception types
- **throw statement**: Throws an exception
- **Exception propagation**: How exceptions bubble up

### 2. Exception Safety Guarantees

- **No-throw guarantee**: Function never throws
- **Basic guarantee**: Object remains in valid state
- **Strong guarantee**: Operation succeeds or has no effect
- **Exception-neutral**: Exceptions propagate to caller

### 3. RAII and Exception Safety

- **Resource Acquisition Is Initialization**: Manage resources through object lifetime
- **Smart pointers**: Automatic resource management
- **Exception-safe code**: Proper resource cleanup
- **Stack unwinding**: Automatic cleanup during exception propagation

### 4. Exception Types

- **Standard exceptions**: std::exception hierarchy
- **Custom exceptions**: User-defined exception classes
- **Exception specifications**: Deprecated in C++11
- **noexcept**: C++11 exception specification

### 5. Best Practices

- **Throw by value, catch by reference**: Efficient exception handling
- **Use RAII**: Automatic resource management
- **Don't throw from destructors**: Prevents undefined behavior
- **Handle exceptions at appropriate level**: Don't catch what you can't handle

## 🧩 Practice Exercises

### Exercise 13.1: Basic Exception Handling
Create programs with try-catch blocks and exception throwing.

### Exercise 13.2: Custom Exceptions
Design custom exception classes with inheritance.

### Exercise 13.3: RAII and Exception Safety
Implement exception-safe resource management.

### Exercise 13.4: Exception Propagation
Study how exceptions propagate through function calls.

## 💻 Code Examples

### Basic Exception Handling
```cpp
#include <iostream>
#include <stdexcept>
#include <string>

// Custom exception class
class DivisionByZeroException : public std::runtime_error {
public:
    DivisionByZeroException() : std::runtime_error("Division by zero") {}
};

// Function that might throw
double divide(double a, double b) {
    if (b == 0) {
        throw DivisionByZeroException();
    }
    return a / b;
}

int main() {
    try {
        double result = divide(10.0, 0.0);
        std::cout << "Result: " << result << std::endl;
    } catch (const DivisionByZeroException& e) {
        std::cout << "Caught custom exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught standard exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Caught unknown exception" << std::endl;
    }
    
    return 0;
}
```

### RAII and Exception Safety
```cpp
#include <iostream>
#include <memory>
#include <stdexcept>

// RAII wrapper for resource
class Resource {
private:
    int* data;
    
public:
    Resource(size_t size) : data(new int[size]) {
        std::cout << "Resource acquired" << std::endl;
    }
    
    ~Resource() {
        delete[] data;
        std::cout << "Resource released" << std::endl;
    }
    
    int& operator[](size_t index) {
        return data[index];
    }
};

// Exception-safe function
void process_data(size_t size) {
    Resource resource(size);  // RAII - automatic cleanup
    
    // Simulate work that might throw
    if (size > 1000) {
        throw std::runtime_error("Size too large");
    }
    
    // Use resource
    for (size_t i = 0; i < size; ++i) {
        resource[i] = i * i;
    }
    
    std::cout << "Data processed successfully" << std::endl;
}  // Resource automatically cleaned up here

int main() {
    try {
        process_data(500);
        process_data(1500);  // This will throw
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Exception safety**: Design functions with appropriate guarantees
2. **RAII**: Use object lifetime for resource management
3. **Throw by value, catch by reference**: Efficient exception handling
4. **Don't throw from destructors**: Prevents undefined behavior
5. **Handle exceptions appropriately**: Don't catch what you can't handle

## 🔗 Next Steps

After mastering exception handling, proceed to Chapter 14 to learn about namespaces and code organization.

## 📚 Additional Resources

- C++ Reference: Exception Handling
- "Exceptional C++" by Herb Sutter
- C++ Core Guidelines: Exception Safety
