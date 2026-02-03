# Lesson 10.3: Copy and Move Semantics

## Learning Objectives
- Master deep vs shallow copying concepts
- Understand move semantics and performance optimization
- Learn perfect forwarding and universal references
- Practice with Rule of Zero implementation
- Explore advanced copy/move patterns and best practices

## Prerequisites
- Completed Lesson 10.2 (Constructors and Destructors)
- Understanding of basic constructors and destructors
- Knowledge of RAII principles

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Copy Semantics Deep Dive

#### Shallow vs Deep Copy
```cpp
class ShallowCopyExample {
private:
    int* data_;
    size_t size_;
    
public:
    ShallowCopyExample(size_t size) : size_(size) {
        data_ = new int[size_];
    }
    
    // Shallow copy (problematic)
    ShallowCopyExample(const ShallowCopyExample& other)
        : data_(other.data_), size_(other.size_) {
        // Both objects share the same memory!
    }
    
    ~ShallowCopyExample() {
        delete[] data_;  // Double deletion error!
    }
};

class DeepCopyExample {
private:
    int* data_;
    size_t size_;
    
public:
    DeepCopyExample(size_t size) : size_(size) {
        data_ = new int[size_];
    }
    
    // Deep copy (correct)
    DeepCopyExample(const DeepCopyExample& other) : size_(other.size_) {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    ~DeepCopyExample() {
        delete[] data_;  // Safe cleanup
    }
};
```

#### Copy Assignment Operator
```cpp
class CopyAssignmentExample {
private:
    std::string* name_;
    int* value_;
    
public:
    CopyAssignmentExample(const std::string& name, int value)
        : name_(new std::string(name)), value_(new int(value)) {}
    
    // Copy assignment with self-assignment check
    CopyAssignmentExample& operator=(const CopyAssignmentExample& other) {
        if (this != &other) {  // Self-assignment check
            delete name_;
            delete value_;
            
            name_ = new std::string(*other.name_);
            value_ = new int(*other.value_);
        }
        return *this;
    }
    
    ~CopyAssignmentExample() {
        delete name_;
        delete value_;
    }
};
```

### 2. Move Semantics (C++11)

#### Move Constructor and Assignment
```cpp
class MoveSemanticsExample {
private:
    std::string name_;
    std::vector<int> data_;
    int* resource_;
    
public:
    MoveSemanticsExample(const std::string& name, size_t size)
        : name_(name), data_(size), resource_(new int[size]) {}
    
    // Move constructor
    MoveSemanticsExample(MoveSemanticsExample&& other) noexcept
        : name_(std::move(other.name_)),
          data_(std::move(other.data_)),
          resource_(other.resource_) {
        other.resource_ = nullptr;
        std::cout << "Move constructor called" << std::endl;
    }
    
    // Move assignment operator
    MoveSemanticsExample& operator=(MoveSemanticsExample&& other) noexcept {
        if (this != &other) {
            delete[] resource_;
            
            name_ = std::move(other.name_);
            data_ = std::move(other.data_);
            resource_ = other.resource_;
            
            other.resource_ = nullptr;
        }
        return *this;
    }
    
    ~MoveSemanticsExample() {
        delete[] resource_;
    }
};
```

#### std::move and Perfect Forwarding
```cpp
template<typename T>
class PerfectForwardingExample {
private:
    T data_;
    
public:
    // Perfect forwarding constructor
    template<typename U>
    PerfectForwardingExample(U&& data) : data_(std::forward<U>(data)) {}
    
    // Perfect forwarding assignment
    template<typename U>
    PerfectForwardingExample& operator=(U&& data) {
        data_ = std::forward<U>(data);
        return *this;
    }
};

void demonstratePerfectForwarding() {
    std::string str = "Hello";
    
    // lvalue reference
    PerfectForwardingExample<std::string> obj1(str);
    
    // rvalue reference
    PerfectForwardingExample<std::string> obj2(std::move(str));
    
    // Temporary object
    PerfectForwardingExample<std::string> obj3("World");
}
```

### 3. Rule of Zero

#### Smart Pointer Implementation
```cpp
class RuleOfZeroExample {
private:
    std::unique_ptr<std::string> name_;
    std::shared_ptr<std::vector<int>> data_;
    std::weak_ptr<std::string> reference_;
    
public:
    RuleOfZeroExample(const std::string& name, size_t size)
        : name_(std::make_unique<std::string>(name)),
          data_(std::make_shared<std::vector<int>>(size)),
          reference_(name_) {}
    
    // No need to implement destructor, copy constructor, etc.
    // Smart pointers handle resource management automatically
    
    const std::string& getName() const { return *name_; }
    size_t getDataSize() const { return data_->size(); }
    bool isReferenceValid() const { return !reference_.expired(); }
};
```

---

## Demonstration (25 minutes)

### Copy and Move Semantics Examples
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

class PerformanceTestClass {
private:
    std::string name_;
    std::vector<int> data_;
    
public:
    PerformanceTestClass(const std::string& name, size_t size)
        : name_(name), data_(size) {
        std::iota(data_.begin(), data_.end(), 0);
    }
    
    // Copy constructor
    PerformanceTestClass(const PerformanceTestClass& other)
        : name_(other.name_), data_(other.data_) {
        std::cout << "Copy constructor called" << std::endl;
    }
    
    // Move constructor
    PerformanceTestClass(PerformanceTestClass&& other) noexcept
        : name_(std::move(other.name_)), data_(std::move(other.data_)) {
        std::cout << "Move constructor called" << std::endl;
    }
    
    // Copy assignment
    PerformanceTestClass& operator=(const PerformanceTestClass& other) {
        if (this != &other) {
            name_ = other.name_;
            data_ = other.data_;
        }
        return *this;
    }
    
    // Move assignment
    PerformanceTestClass& operator=(PerformanceTestClass&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            data_ = std::move(other.data_);
        }
        return *this;
    }
    
    size_t getDataSize() const { return data_.size(); }
};

void demonstrateCopyVsMove() {
    std::cout << "=== Copy vs Move Semantics ===" << std::endl;
    
    // Create original object
    PerformanceTestClass original("Original", 1000000);
    
    // Copy semantics
    std::cout << "\nCopy semantics:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    PerformanceTestClass copied = original;
    auto end = std::chrono::high_resolution_clock::now();
    auto copy_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Move semantics
    std::cout << "\nMove semantics:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    PerformanceTestClass moved = std::move(original);
    end = std::chrono::high_resolution_clock::now();
    auto move_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Copy time: " << copy_time.count() << " microseconds" << std::endl;
    std::cout << "Move time: " << move_time.count() << " microseconds" << std::endl;
    std::cout << "Move is " << (double)copy_time.count() / move_time.count() 
              << "x faster than copy" << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Copy Semantics Implementation
Implement proper copy semantics:

**Tasks:**
1. Create classes with deep copy constructors
2. Implement copy assignment operators
3. Handle self-assignment correctly
4. Test copy behavior with complex objects

### Activity 2: Move Semantics Implementation
Implement move semantics:

**Tasks:**
1. Create move constructors and assignment operators
2. Use std::move for performance optimization
3. Implement noexcept specifications
4. Test move behavior and performance

### Activity 3: Rule of Zero Application
Apply Rule of Zero:

**Tasks:**
1. Use smart pointers for resource management
2. Implement classes without manual copy/move operations
3. Compare performance with manual implementations
4. Apply modern C++ patterns

---

## Key Concepts

### 1. Value Categories
```cpp
void demonstrateValueCategories() {
    std::string str = "Hello";
    
    // lvalue - has identity and can be assigned
    std::string& lvalue_ref = str;
    
    // rvalue - temporary or moved object
    std::string&& rvalue_ref = std::move(str);
    
    // prvalue - pure rvalue (temporary)
    std::string prvalue = "World";
    
    // xvalue - expiring value
    std::string xvalue = std::move(prvalue);
}
```

### 2. Copy Elision and RVO
```cpp
class CopyElisionExample {
public:
    static CopyElisionExample createObject() {
        return CopyElisionExample("Created");  // RVO - no copy
    }
    
    CopyElisionExample(const std::string& name) : name_(name) {}
    
private:
    std::string name_;
};

void demonstrateCopyElision() {
    // Copy elision - compiler optimizes away unnecessary copies
    CopyElisionExample obj = CopyElisionExample::createObject();
}
```

### 3. Perfect Forwarding
```cpp
template<typename T>
void perfectForward(T&& arg) {
    // Universal reference - can bind to lvalue or rvalue
    process(std::forward<T>(arg));
}

void process(const std::string& str) {
    std::cout << "Processing lvalue: " << str << std::endl;
}

void process(std::string&& str) {
    std::cout << "Processing rvalue: " << str << std::endl;
}

void demonstratePerfectForwarding() {
    std::string str = "Hello";
    perfectForward(str);           // Calls process(const std::string&)
    perfectForward(std::move(str)); // Calls process(std::string&&)
    perfectForward("World");       // Calls process(std::string&&)
}
```

---

## Best Practices

### 1. Copy Semantics
- Always implement deep copy for pointer members
- Check for self-assignment in copy assignment
- Use const-correctness in copy constructors
- Consider copy-on-write for large objects

### 2. Move Semantics
- Mark move operations as noexcept
- Leave moved-from objects in valid state
- Use std::move to indicate intention to move
- Prefer move over copy when possible

### 3. Rule of Zero
- Use smart pointers instead of raw pointers
- Let compiler generate copy/move operations
- Use standard containers for data storage
- Avoid manual resource management

---

## Common Pitfalls

### 1. Shallow Copy Issues
```cpp
// Wrong: shallow copy
class BadCopy {
private:
    int* data_;
public:
    BadCopy(const BadCopy& other) : data_(other.data_) {}  // Shallow copy!
    ~BadCopy() { delete data_; }  // Double deletion!
};

// Correct: deep copy
class GoodCopy {
private:
    int* data_;
public:
    GoodCopy(const GoodCopy& other) : data_(new int(*other.data_)) {}  // Deep copy
    ~GoodCopy() { delete data_; }
};
```

### 2. Missing noexcept
```cpp
// Wrong: missing noexcept
class BadMove {
public:
    BadMove(BadMove&& other) {  // Should be noexcept
        // Move implementation
    }
};

// Correct: with noexcept
class GoodMove {
public:
    GoodMove(GoodMove&& other) noexcept {  // noexcept specification
        // Move implementation
    }
};
```

### 3. Inefficient Move Implementation
```cpp
// Wrong: inefficient move
class BadMoveImpl {
private:
    std::vector<int> data_;
public:
    BadMoveImpl(BadMoveImpl&& other) : data_(other.data_) {}  // Copy instead of move!
};

// Correct: efficient move
class GoodMoveImpl {
private:
    std::vector<int> data_;
public:
    GoodMoveImpl(GoodMoveImpl&& other) : data_(std::move(other.data_)) {}  // Move
};
```

---

## Assessment

### Quiz Questions
1. What is the difference between shallow and deep copy?
2. When should you use move semantics?
3. What is perfect forwarding and why is it useful?
4. How does the Rule of Zero simplify code?

### Practical Assessment
- Implement proper copy and move semantics
- Use std::move and perfect forwarding correctly
- Apply Rule of Zero for resource management
- Optimize performance with move semantics

---

## Homework Assignment

### Task 1: Copy/Move Implementation
Implement:
1. A class with proper copy and move semantics
2. Performance comparison between copy and move
3. Self-assignment handling
4. Exception safety in copy/move operations

### Task 2: Perfect Forwarding
Create:
1. Template functions with perfect forwarding
2. Universal reference parameters
3. Forwarding constructors
4. Performance optimization with forwarding

### Task 3: Rule of Zero Application
Apply:
1. Smart pointers for resource management
2. Standard containers for data storage
3. Modern C++ patterns
4. Comparison with manual implementations

---

## Next Lesson Preview

In the next lesson, we'll learn about operator overloading:
- Arithmetic and assignment operators
- Comparison and logical operators
- Function call and subscript operators
- Type conversion operators

Make sure you understand copy and move semantics before moving on!
