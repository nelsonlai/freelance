# Chapter 37: Memory Management and Smart Pointers

## 📘 Learning Objectives

After completing this chapter, you will:
- Master modern C++ memory management techniques
- Understand smart pointer types and usage
- Learn about custom deleters and allocators
- Master RAII and exception safety
- Understand memory optimization strategies

## 🎯 Key Concepts

### 1. Smart Pointers

- **std::unique_ptr**: Exclusive ownership pointer
- **std::shared_ptr**: Shared ownership pointer
- **std::weak_ptr**: Non-owning reference pointer
- **std::auto_ptr**: Deprecated smart pointer
- **Custom deleters**: Custom cleanup functions

### 2. Memory Management

- **RAII**: Resource Acquisition Is Initialization
- **Exception safety**: Exception-safe memory management
- **Memory leaks**: Prevention and detection
- **Dangling pointers**: Prevention strategies
- **Double deletion**: Avoiding double deletion

### 3. Advanced Smart Pointer Usage

- **Custom deleters**: Function objects and lambdas
- **Array specialization**: Smart pointers for arrays
- **Polymorphic usage**: Smart pointers with inheritance
- **Circular references**: Breaking circular dependencies
- **Performance considerations**: Smart pointer overhead

### 4. Memory Optimization

- **Memory pools**: Efficient memory allocation
- **Custom allocators**: Specialized memory management
- **Memory alignment**: Aligned memory allocation
- **Cache optimization**: Memory access patterns
- **Zero-cost abstractions**: Zero-overhead abstractions

### 5. Best Practices

- **Smart pointer selection**: Choosing appropriate smart pointer
- **Ownership semantics**: Clear ownership models
- **Exception safety**: Exception-safe design
- **Performance optimization**: Optimization strategies
- **Debugging techniques**: Memory debugging tools

## 🧩 Practice Exercises

### Exercise 37.1: Smart Pointer Basics
Use different smart pointer types for memory management.

### Exercise 37.2: Custom Deleters
Implement custom deleters for smart pointers.

### Exercise 37.3: RAII Design
Design RAII classes for resource management.

### Exercise 37.4: Memory Optimization
Optimize memory usage with smart pointers.

## 💻 Code Examples

### Smart Pointer Basics
```cpp
#include <iostream>
#include <memory>
#include <vector>

class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " created" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed" << std::endl;
    }
    
    int getId() const { return id_; }
    
private:
    int id_;
};

int main() {
    // unique_ptr
    auto resource1 = std::make_unique<Resource>(1);
    std::cout << "Resource 1 ID: " << resource1->getId() << std::endl;
    
    // shared_ptr
    auto resource2 = std::make_shared<Resource>(2);
    std::cout << "Resource 2 ID: " << resource2->getId() << std::endl;
    
    // weak_ptr
    std::weak_ptr<Resource> weak_resource = resource2;
    if (auto locked = weak_resource.lock()) {
        std::cout << "Weak pointer locked, ID: " << locked->getId() << std::endl;
    }
    
    return 0;
}
```

### Custom Deleters
```cpp
#include <iostream>
#include <memory>
#include <cstdio>

// Custom deleter for FILE*
struct FileDeleter {
    void operator()(FILE* file) {
        if (file) {
            std::cout << "Closing file" << std::endl;
            fclose(file);
        }
    }
};

int main() {
    // Custom deleter with unique_ptr
    auto file = std::unique_ptr<FILE, FileDeleter>(fopen("data.txt", "w"));
    
    if (file) {
        fprintf(file.get(), "Hello, World!\n");
        std::cout << "File written" << std::endl;
    }
    
    // File automatically closed when file goes out of scope
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use smart pointers** for automatic memory management
2. **Choose appropriate smart pointer** for ownership semantics
3. **Implement RAII** for resource management
4. **Use custom deleters** for specialized cleanup
5. **Optimize memory usage** with proper smart pointer usage

## 🔗 Next Steps

After mastering memory management and smart pointers, proceed to Chapter 38 to learn about utilities.

## 📚 Additional Resources

- C++ Reference: Smart Pointers
- C++ Core Guidelines: Memory Management
- Practice with complex memory management scenarios
