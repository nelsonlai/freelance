# Lesson 5.1: Smart Pointers

## Learning Objectives
- Master unique_ptr, shared_ptr, and weak_ptr
- Understand RAII principles with smart pointers
- Learn custom deleters and allocators
- Practice memory management best practices
- Compare smart pointers with raw pointers

## Prerequisites
- Completed Lesson 4.1 (Concurrency Basics)
- Understanding of RAII and resource management
- Basic knowledge of memory management

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Smart Pointer Overview

#### Why Smart Pointers?
- **Automatic memory management:** No manual delete required
- **Exception safety:** Guaranteed cleanup even with exceptions
- **RAII compliance:** Resource Acquisition Is Initialization
- **Type safety:** Compile-time checks for ownership

#### Types of Smart Pointers
- **unique_ptr:** Exclusive ownership, movable
- **shared_ptr:** Shared ownership with reference counting
- **weak_ptr:** Non-owning reference to shared_ptr

### 2. unique_ptr

#### Characteristics
- **Exclusive ownership:** Only one unique_ptr can own an object
- **Movable:** Can transfer ownership
- **Non-copyable:** Prevents multiple ownership
- **Zero overhead:** Same performance as raw pointers

#### Usage Patterns
```cpp
std::unique_ptr<int> ptr = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = std::move(ptr);  // Transfer ownership
// ptr is now nullptr, ptr2 owns the object
```

### 3. shared_ptr

#### Characteristics
- **Shared ownership:** Multiple shared_ptr can own same object
- **Reference counting:** Automatically deletes when count reaches zero
- **Thread-safe:** Reference counting is atomic
- **Overhead:** Slight performance cost for reference counting

#### Usage Patterns
```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = ptr1;  // Share ownership
// Both ptr1 and ptr2 own the same object
```

### 4. weak_ptr

#### Characteristics
- **Non-owning:** Doesn't affect reference count
- **Cycle breaking:** Prevents circular references
- **Expiration checking:** Can check if object still exists
- **Lock operation:** Can get shared_ptr if object exists

#### Usage Patterns
```cpp
std::weak_ptr<int> weak = shared_ptr;
if (auto locked = weak.lock()) {
    // Object still exists, use locked shared_ptr
} else {
    // Object has been destroyed
}
```

---

## Demonstration (25 minutes)

### Smart Pointer Examples
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
    
    void use() const {
        std::cout << "Using resource " << id_ << std::endl;
    }
    
private:
    int id_;
};

void demonstrateUniquePtr() {
    std::cout << "=== unique_ptr Demonstration ===" << std::endl;
    
    // Create unique_ptr
    std::unique_ptr<Resource> ptr = std::make_unique<Resource>(1);
    ptr->use();
    
    // Transfer ownership
    std::unique_ptr<Resource> ptr2 = std::move(ptr);
    if (!ptr) {
        std::cout << "ptr is now nullptr" << std::endl;
    }
    ptr2->use();
    
    // Automatic cleanup when ptr2 goes out of scope
}

void demonstrateSharedPtr() {
    std::cout << "
=== shared_ptr Demonstration ===" << std::endl;
    
    // Create shared_ptr
    std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>(2);
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    // Share ownership
    std::shared_ptr<Resource> ptr2 = ptr1;
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    // Use both pointers
    ptr1->use();
    ptr2->use();
    
    // Reset one pointer
    ptr1.reset();
    std::cout << "After reset, reference count: " << ptr2.use_count() << std::endl;
    
    // Automatic cleanup when ptr2 goes out of scope
}

void demonstrateWeakPtr() {
    std::cout << "
=== weak_ptr Demonstration ===" << std::endl;
    
    std::shared_ptr<Resource> shared = std::make_shared<Resource>(3);
    std::weak_ptr<Resource> weak = shared;
    
    std::cout << "Shared reference count: " << shared.use_count() << std::endl;
    
    // Check if object exists
    if (auto locked = weak.lock()) {
        std::cout << "Object exists, reference count: " << locked.use_count() << std::endl;
        locked->use();
    }
    
    // Reset shared_ptr
    shared.reset();
    std::cout << "Shared pointer reset" << std::endl;
    
    // Check if object still exists
    if (auto locked = weak.lock()) {
        std::cout << "Object still exists" << std::endl;
    } else {
        std::cout << "Object has been destroyed" << std::endl;
    }
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Smart Pointer Implementation
Implement smart pointer functionality:

**Tasks:**
1. Create a simple unique_ptr class
2. Implement reference counting for shared_ptr
3. Build a weak_ptr implementation
4. Test memory management

### Activity 2: Real-World Applications
Apply smart pointers to practical problems:

**Tasks:**
1. Implement a file manager with smart pointers
2. Build a resource pool system
3. Create a cache with weak_ptr
4. Design a plugin system

### Activity 3: Performance Analysis
Compare smart pointer performance:

**Tasks:**
1. Measure overhead of different smart pointers
2. Compare with raw pointer performance
3. Analyze memory usage patterns
4. Test thread safety

---

## Key Concepts

### 1. RAII with Smart Pointers
```cpp
class FileManager {
private:
    std::unique_ptr<FILE, decltype(&fclose)> file_;
    
public:
    FileManager(const char* filename) 
        : file_(fopen(filename, "r"), &fclose) {
        if (!file_) {
            throw std::runtime_error("Failed to open file");
        }
    }
    
    // File automatically closed when FileManager is destroyed
};
```

### 2. Custom Deleters
```cpp
// Custom deleter for arrays
auto array_deleter = [](int* ptr) {
    delete[] ptr;
};

std::unique_ptr<int[], decltype(array_deleter)> 
    array_ptr(new int[100], array_deleter);

// Custom deleter for C-style resources
auto c_deleter = [](void* ptr) {
    free(ptr);
};

std::unique_ptr<void, decltype(c_deleter)> 
    c_ptr(malloc(1024), c_deleter);
```

### 3. Circular Reference Prevention
```cpp
class Node {
public:
    std::shared_ptr<Node> parent;
    std::weak_ptr<Node> child;  // Use weak_ptr to break cycle
    
    Node() = default;
    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};
```

---

## Best Practices

### 1. Smart Pointer Selection
- Use unique_ptr for exclusive ownership
- Use shared_ptr for shared ownership
- Use weak_ptr to break circular references
- Prefer make_unique and make_shared

### 2. Memory Management
- Avoid raw new/delete with smart pointers
- Use custom deleters for non-standard resources
- Be aware of reference counting overhead
- Consider move semantics for performance

### 3. Exception Safety
- Smart pointers provide strong exception safety
- Use RAII for all resource management
- Prefer stack allocation when possible
- Handle exceptions in constructors

---

## Common Pitfalls

### 1. Circular References
```cpp
// Wrong: Circular reference with shared_ptr
class BadNode {
public:
    std::shared_ptr<BadNode> parent;
    std::shared_ptr<BadNode> child;  // Circular reference!
};

// Correct: Use weak_ptr to break cycle
class GoodNode {
public:
    std::shared_ptr<GoodNode> parent;
    std::weak_ptr<GoodNode> child;  // Breaks circular reference
};
```

### 2. Performance Issues
```cpp
// Wrong: Creating shared_ptr from raw pointer
void function(int* raw_ptr) {
    std::shared_ptr<int> ptr(raw_ptr);  // Dangerous!
    // If function is called multiple times, double delete!
}

// Correct: Use make_shared
std::shared_ptr<int> ptr = std::make_shared<int>(42);
```

### 3. Ownership Confusion
```cpp
// Wrong: Mixing raw and smart pointers
int* raw_ptr = new int(42);
std::unique_ptr<int> smart_ptr(raw_ptr);
// Don't use raw_ptr after this point!

// Correct: Use smart pointers throughout
std::unique_ptr<int> smart_ptr = std::make_unique<int>(42);
```

---

## Assessment

### Quiz Questions
1. What are the differences between unique_ptr and shared_ptr?
2. When should you use weak_ptr?
3. How do smart pointers prevent memory leaks?
4. What is the performance cost of shared_ptr?

### Practical Assessment
- Implement working smart pointer code
- Use appropriate smart pointer types
- Handle resource management correctly
- Apply smart pointers to real problems

---

## Homework Assignment

### Task 1: Smart Pointer Library
Implement:
1. A custom unique_ptr class
2. A reference-counted shared_ptr
3. A weak_ptr implementation
4. Custom deleters for different resources

### Task 2: Resource Management
Apply smart pointers to:
1. File I/O operations
2. Network connections
3. Database connections
4. Graphics resources

### Task 3: Performance Analysis
Analyze performance of:
1. Different smart pointer types
2. Custom deleters vs standard deleters
3. Memory usage patterns
4. Thread safety implications

---

## Next Lesson Preview

In the next lesson, we'll learn about advanced class design:
- Composition vs inheritance
- The Pimpl idiom
- Rule of Zero, Three, Five, and Six
- Class design patterns

Make sure you understand smart pointers before moving on!