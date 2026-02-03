# Lesson 9.1: Exception Handling

## Learning Objectives
- Master exception throwing and catching
- Understand exception safety and RAII
- Learn custom exception classes
- Practice with exception specifications
- Explore modern exception handling patterns

## Prerequisites
- Completed Lesson 8.3 (Functions)
- Understanding of control flow
- Basic knowledge of classes and inheritance

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Exception Fundamentals

#### What are Exceptions?
- **Error handling mechanism:** Exceptions provide a way to handle errors
- **Separation of concerns:** Separate error handling from normal code flow
- **Stack unwinding:** Automatic cleanup when exceptions occur
- **Type safety:** Exceptions are typed objects

#### Exception Syntax
```cpp
try {
    // Code that might throw exceptions
    risky_function();
} catch (const std::exception& e) {
    // Handle specific exception type
    std::cout << "Error: " << e.what() << std::endl;
} catch (...) {
    // Handle any exception
    std::cout << "Unknown error occurred" << std::endl;
}
```

### 2. Throwing Exceptions

#### Standard Exceptions
```cpp
#include <stdexcept>

void function(int value) {
    if (value < 0) {
        throw std::invalid_argument("Value must be non-negative");
    }
    if (value > 100) {
        throw std::out_of_range("Value must be <= 100");
    }
}
```

#### Custom Exceptions
```cpp
class CustomException : public std::exception {
private:
    std::string message_;
public:
    CustomException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
};
```

### 3. Exception Safety

#### Exception Safety Levels
- **No-throw guarantee:** Function never throws exceptions
- **Basic guarantee:** No resource leaks, objects remain in valid state
- **Strong guarantee:** Operations either complete or have no effect
- **No guarantee:** Function might leave objects in invalid state

#### RAII and Exceptions
```cpp
class Resource {
public:
    Resource() { /* acquire resource */ }
    ~Resource() { /* release resource */ }
    // Resource automatically released even if exception occurs
};
```

---

## Demonstration (25 minutes)

### Exception Examples
```cpp
#include <iostream>
#include <stdexcept>

class DivisionByZeroError : public std::runtime_error {
public:
    DivisionByZeroError() : std::runtime_error("Division by zero") {}
};

double safe_divide(double a, double b) {
    if (b == 0) {
        throw DivisionByZeroError();
    }
    return a / b;
}

void demonstrateExceptions() {
    std::cout << "=== Exception Demonstration ===" << std::endl;
    
    try {
        double result = safe_divide(10.0, 2.0);
        std::cout << "Result: " << result << std::endl;
        
        result = safe_divide(10.0, 0.0);  // This will throw
        std::cout << "Result: " << result << std::endl;
    } catch (const DivisionByZeroError& e) {
        std::cout << "Caught division by zero: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Exception Implementation
Implement exception handling:

**Tasks:**
1. Create custom exception classes
2. Implement exception-safe functions
3. Use RAII with exceptions
4. Handle multiple exception types

### Activity 2: Exception Safety
Practice exception safety:

**Tasks:**
1. Implement strong exception safety
2. Use smart pointers with exceptions
3. Handle resource cleanup
4. Design exception-safe classes

### Activity 3: Exception Applications
Apply exceptions to real problems:

**Tasks:**
1. Implement file I/O with exceptions
2. Create network error handling
3. Build validation systems
4. Design error reporting systems

---

## Key Concepts

### 1. Exception Propagation
```cpp
void function_a() {
    throw std::runtime_error("Error in function_a");
}

void function_b() {
    function_a();  // Exception propagates up
}

void function_c() {
    try {
        function_b();
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}
```

### 2. Exception Specifications
```cpp
// C++11 noexcept specification
void safe_function() noexcept {
    // This function promises not to throw
}

// Conditional noexcept
template<typename T>
void copy_function(T&& value) noexcept(std::is_nothrow_copy_constructible_v<T>) {
    // Implementation
}
```

### 3. Exception Safety Patterns
```cpp
class SafeClass {
private:
    std::unique_ptr<Resource> resource_;
public:
    SafeClass() : resource_(std::make_unique<Resource>()) {}
    
    void operation() {
        auto temp = std::make_unique<Resource>();  // Create new resource
        // Perform operations that might throw
        resource_ = std::move(temp);  // Commit only if successful
    }
};
```

---

## Best Practices

### 1. Exception Design
- Use standard exceptions when possible
- Create meaningful exception messages
- Inherit from appropriate base classes
- Keep exception classes simple

### 2. Exception Handling
- Catch exceptions by const reference
- Handle exceptions at appropriate levels
- Don't ignore exceptions silently
- Use RAII for automatic cleanup

### 3. Performance
- Don't use exceptions for control flow
- Minimize exception throwing in hot paths
- Use noexcept when appropriate
- Consider exception safety guarantees

---

## Common Pitfalls

### 1. Exception in Destructors
```cpp
// Wrong: throwing in destructor
class BadClass {
public:
    ~BadClass() {
        throw std::runtime_error("Error");  // Dangerous!
    }
};

// Correct: handle exceptions in destructor
class GoodClass {
public:
    ~GoodClass() noexcept {
        try {
            cleanup();
        } catch (...) {
            // Log error but don't throw
        }
    }
};
```

### 2. Exception Safety Violations
```cpp
// Wrong: not exception-safe
class UnsafeClass {
    int* data_;
public:
    void resize(size_t new_size) {
        delete[] data_;           // If new throws, data_ is lost!
        data_ = new int[new_size];
    }
};

// Correct: exception-safe
class SafeClass {
    std::unique_ptr<int[]> data_;
public:
    void resize(size_t new_size) {
        auto new_data = std::make_unique<int[]>(new_size);
        data_ = std::move(new_data);  // Atomic operation
    }
};
```

### 3. Catching by Value
```cpp
// Wrong: catching by value
try {
    throw std::runtime_error("Error");
} catch (std::exception e) {  // Creates copy
    std::cout << e.what() << std::endl;
}

// Correct: catching by reference
try {
    throw std::runtime_error("Error");
} catch (const std::exception& e) {  // No copy
    std::cout << e.what() << std::endl;
}
```

---

## Assessment

### Quiz Questions
1. What are the different levels of exception safety?
2. Why should you catch exceptions by const reference?
3. What happens when an exception is thrown in a destructor?
4. How does RAII help with exception safety?

### Practical Assessment
- Implement working exception handling
- Use exceptions safely and correctly
- Apply RAII principles with exceptions
- Handle multiple exception types

---

## Homework Assignment

### Task 1: Exception Library
Implement:
1. A collection of custom exception classes
2. Exception-safe utility functions
3. RAII-based resource management
4. Exception handling utilities

### Task 2: Exception Applications
Apply exceptions to:
1. File I/O operations
2. Network programming
3. Data validation systems
4. Error reporting mechanisms

### Task 3: Exception Analysis
Analyze:
1. Exception safety guarantees
2. Performance implications of exceptions
3. Exception handling patterns
4. Modern exception handling techniques

---

## Next Lesson Preview

In the next lesson, we'll learn about namespaces:
- Namespace declaration and definition
- Namespace aliases and using declarations
- Anonymous namespaces
- Namespace organization

Make sure you understand exception handling before moving on!
