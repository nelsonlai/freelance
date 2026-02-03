# Chapter 25: Advanced Class Design

## 📘 Learning Objectives

After completing this chapter, you will:
- Master advanced class design patterns and techniques
- Understand RAII and resource management
- Learn about move semantics and perfect forwarding
- Master exception safety and error handling
- Understand class design best practices

## 🎯 Key Concepts

### 1. RAII (Resource Acquisition Is Initialization)

- **Resource management**: Automatic resource cleanup
- **Smart pointers**: Automatic memory management
- **RAII patterns**: Resource management patterns
- **Exception safety**: Exception-safe resource management
- **Custom RAII**: User-defined RAII classes

### 2. Move Semantics

- **Move constructors**: Efficient object transfer
- **Move assignment**: Efficient assignment
- **Perfect forwarding**: Forwarding arguments
- **Move optimization**: Performance optimization
- **Move-only types**: Non-copyable types

### 3. Exception Safety

- **Exception safety levels**: Basic, strong, no-throw
- **RAII exception safety**: Automatic cleanup
- **Exception specifications**: C++17 noexcept
- **Exception handling**: Proper error handling
- **Exception propagation**: Exception flow control

### 4. Advanced Class Patterns

- **PIMPL idiom**: Pointer to implementation
- **Singleton pattern**: Single instance classes
- **Factory pattern**: Object creation patterns
- **Builder pattern**: Complex object construction
- **Observer pattern**: Event handling

### 5. Class Design Best Practices

- **Encapsulation**: Data hiding and access control
- **Inheritance design**: Proper inheritance hierarchies
- **Interface design**: Clean interface design
- **Performance considerations**: Class design optimization
- **Maintainability**: Code maintainability patterns

## 🧩 Practice Exercises

### Exercise 25.1: RAII Implementation
Implement RAII classes for resource management.

### Exercise 25.2: Move Semantics
Create classes with move semantics.

### Exercise 25.3: Exception Safety
Design exception-safe classes.

### Exercise 25.4: Design Patterns
Implement common design patterns.

## 💻 Code Examples

### RAII Implementation
```cpp
#include <iostream>
#include <memory>

class RAIIFile {
private:
    FILE* file;
public:
    RAIIFile(const char* filename) : file(fopen(filename, "r")) {
        if (!file) throw std::runtime_error("Cannot open file");
    }
    
    ~RAIIFile() {
        if (file) fclose(file);
    }
    
    // Delete copy constructor and assignment
    RAIIFile(const RAIIFile&) = delete;
    RAIIFile& operator=(const RAIIFile&) = delete;
    
    // Move constructor
    RAIIFile(RAIIFile&& other) : file(other.file) {
        other.file = nullptr;
    }
    
    // Move assignment
    RAIIFile& operator=(RAIIFile&& other) {
        if (this != &other) {
            if (file) fclose(file);
            file = other.file;
            other.file = nullptr;
        }
        return *this;
    }
    
    FILE* get() const { return file; }
};

int main() {
    try {
        RAIIFile file("data.txt");
        // File automatically closed when file goes out of scope
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
```

### Move Semantics
```cpp
#include <iostream>
#include <vector>
#include <utility>

class MoveOnlyClass {
private:
    std::vector<int> data;
public:
    MoveOnlyClass(size_t size) : data(size) {
        std::iota(data.begin(), data.end(), 0);
    }
    
    // Delete copy constructor and assignment
    MoveOnlyClass(const MoveOnlyClass&) = delete;
    MoveOnlyClass& operator=(const MoveOnlyClass&) = delete;
    
    // Move constructor
    MoveOnlyClass(MoveOnlyClass&& other) noexcept 
        : data(std::move(other.data)) {
        std::cout << "Move constructor called" << std::endl;
    }
    
    // Move assignment
    MoveOnlyClass& operator=(MoveOnlyClass&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            std::cout << "Move assignment called" << std::endl;
        }
        return *this;
    }
    
    const std::vector<int>& getData() const { return data; }
};

int main() {
    MoveOnlyClass obj1(1000);
    MoveOnlyClass obj2 = std::move(obj1);  // Move constructor
    MoveOnlyClass obj3(500);
    obj3 = std::move(obj2);  // Move assignment
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use RAII** for automatic resource management
2. **Implement move semantics** for performance optimization
3. **Design for exception safety** with proper error handling
4. **Apply design patterns** for flexible class design
5. **Follow best practices** for maintainable code

## 🔗 Next Steps

After mastering advanced class design, proceed to Chapter 26 to learn about memory management.

## 📚 Additional Resources

- C++ Reference: Classes
- C++ Core Guidelines: Classes
- Practice with complex class hierarchies
