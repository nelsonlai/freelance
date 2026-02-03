# Lesson 10.2: Constructors and Destructors

## Learning Objectives
- Master constructor types and initialization
- Understand destructor implementation and RAII
- Learn copy and move semantics
- Practice with the Rule of Three/Five/Zero
- Explore advanced initialization techniques

## Prerequisites
- Completed Lesson 10.1 (Classes Deep Dive)
- Understanding of basic classes and objects
- Knowledge of memory management basics

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Constructor Fundamentals

#### Constructor Types
```cpp
class MyClass {
private:
    int value_;
    std::string name_;
    
public:
    // Default constructor
    MyClass();
    
    // Parameterized constructor
    MyClass(int value, const std::string& name);
    
    // Copy constructor
    MyClass(const MyClass& other);
    
    // Move constructor
    MyClass(MyClass&& other) noexcept;
    
    // Destructor
    ~MyClass();
};
```

#### Initialization Methods
```cpp
class Student {
private:
    std::string name_;
    int age_;
    double gpa_;
    
public:
    // Constructor initializer list (preferred)
    Student(const std::string& name, int age, double gpa)
        : name_(name), age_(age), gpa_(gpa) {
        // Constructor body
    }
    
    // Member initialization (C++11)
    Student() : name_("Unknown"), age_(18), gpa_(0.0) {}
    
    // Delegate constructors (C++11)
    Student(const std::string& name) : Student(name, 18, 0.0) {}
};
```

### 2. Destructor and RAII

#### Resource Acquisition Is Initialization (RAII)
```cpp
class FileManager {
private:
    std::string filename_;
    std::fstream file_;
    
public:
    FileManager(const std::string& filename) : filename_(filename) {
        file_.open(filename_);
        if (!file_.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename_);
        }
    }
    
    ~FileManager() {
        if (file_.is_open()) {
            file_.close();
        }
    }
    
    // Copy and move semantics to be implemented
};
```

### 3. Copy Semantics

#### Rule of Three
```cpp
class ResourceManager {
private:
    int* data_;
    size_t size_;
    
public:
    // Constructor
    ResourceManager(size_t size) : size_(size) {
        data_ = new int[size_];
        std::fill(data_, data_ + size_, 0);
    }
    
    // Destructor
    ~ResourceManager() {
        delete[] data_;
    }
    
    // Copy constructor
    ResourceManager(const ResourceManager& other) : size_(other.size_) {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    // Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
};
```

### 4. Move Semantics (C++11)

#### Rule of Five
```cpp
class ModernResourceManager {
private:
    std::unique_ptr<int[]> data_;
    size_t size_;
    
public:
    // Constructor
    ModernResourceManager(size_t size) : size_(size) {
        data_ = std::make_unique<int[]>(size_);
        std::fill(data_.get(), data_.get() + size_, 0);
    }
    
    // Destructor (defaulted)
    ~ModernResourceManager() = default;
    
    // Copy constructor
    ModernResourceManager(const ModernResourceManager& other) : size_(other.size_) {
        data_ = std::make_unique<int[]>(size_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }
    
    // Copy assignment operator
    ModernResourceManager& operator=(const ModernResourceManager& other) {
        if (this != &other) {
            data_ = std::make_unique<int[]>(other.size_);
            size_ = other.size_;
            std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        }
        return *this;
    }
    
    // Move constructor
    ModernResourceManager(ModernResourceManager&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_) {
        other.size_ = 0;
    }
    
    // Move assignment operator
    ModernResourceManager& operator=(ModernResourceManager&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
};
```

---

## Demonstration (25 minutes)

### Constructor and Destructor Examples
```cpp
#include <iostream>
#include <string>
#include <memory>
#include <vector>

class DatabaseConnection {
private:
    std::string connection_string_;
    bool connected_;
    static int connection_count_;
    
public:
    DatabaseConnection(const std::string& conn_str) 
        : connection_string_(conn_str), connected_(false) {
        std::cout << "DatabaseConnection created: " << conn_str << std::endl;
        connect();
    }
    
    ~DatabaseConnection() {
        disconnect();
        std::cout << "DatabaseConnection destroyed: " << connection_string_ << std::endl;
    }
    
    void connect() {
        if (!connected_) {
            connected_ = true;
            connection_count_++;
            std::cout << "Connected to database (Total connections: " 
                      << connection_count_ << ")" << std::endl;
        }
    }
    
    void disconnect() {
        if (connected_) {
            connected_ = false;
            connection_count_--;
            std::cout << "Disconnected from database (Remaining connections: " 
                      << connection_count_ << ")" << std::endl;
        }
    }
    
    bool isConnected() const { return connected_; }
    static int getConnectionCount() { return connection_count_; }
};

int DatabaseConnection::connection_count_ = 0;

void demonstrateConstructorsDestructors() {
    std::cout << "=== Constructors and Destructors ===" << std::endl;
    
    {
        DatabaseConnection db1("localhost:5432");
        DatabaseConnection db2("localhost:3306");
        
        std::cout << "Active connections: " << DatabaseConnection::getConnectionCount() << std::endl;
    }  // Destructors called here
    
    std::cout << "Active connections: " << DatabaseConnection::getConnectionCount() << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Constructor Implementation
Implement various constructor types:

**Tasks:**
1. Create default and parameterized constructors
2. Implement constructor initializer lists
3. Use delegate constructors
4. Handle constructor exceptions

### Activity 2: RAII Implementation
Implement RAII patterns:

**Tasks:**
1. Create resource management classes
2. Implement proper destructor cleanup
3. Handle resource acquisition failures
4. Apply RAII to file and memory management

### Activity 3: Copy and Move Semantics
Implement copy and move operations:

**Tasks:**
1. Implement Rule of Three/Five
2. Create efficient move constructors
3. Handle self-assignment
4. Use smart pointers for resource management

---

## Key Concepts

### 1. Constructor Initializer Lists
```cpp
class Point {
private:
    double x_, y_;
    std::string name_;
    
public:
    Point(double x, double y, const std::string& name)
        : x_(x), y_(y), name_(name) {  // Initializer list
        // Constructor body
    }
    
    // Benefits of initializer lists:
    // 1. More efficient (direct initialization)
    // 2. Required for const members
    // 3. Required for reference members
    // 4. Required for base class initialization
};
```

### 2. RAII Pattern
```cpp
class LockGuard {
private:
    std::mutex& mutex_;
    
public:
    LockGuard(std::mutex& m) : mutex_(m) {
        mutex_.lock();
    }
    
    ~LockGuard() {
        mutex_.unlock();
    }
    
    // Prevent copying
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
};
```

### 3. Rule of Zero
```cpp
class SimpleClass {
private:
    std::string name_;
    std::vector<int> data_;
    std::unique_ptr<int> value_;
    
public:
    SimpleClass(const std::string& name) : name_(name) {
        value_ = std::make_unique<int>(42);
    }
    
    // No need to implement destructor, copy constructor, etc.
    // Compiler-generated versions work correctly with smart pointers and standard containers
};
```

---

## Best Practices

### 1. Constructor Design
- Use initializer lists for member initialization
- Prefer delegation over code duplication
- Handle exceptions in constructors properly
- Make constructors explicit when appropriate

### 2. Destructor Implementation
- Implement destructors for resource cleanup
- Make destructors virtual in base classes
- Use RAII for automatic resource management
- Avoid throwing exceptions from destructors

### 3. Copy and Move Semantics
- Follow Rule of Three/Five/Zero
- Implement move semantics for performance
- Use smart pointers to avoid manual memory management
- Handle self-assignment correctly

---

## Common Pitfalls

### 1. Missing Initialization
```cpp
// Wrong: uninitialized members
class BadClass {
private:
    int value_;  // Uninitialized!
public:
    BadClass() {}  // value_ has indeterminate value
};

// Correct: proper initialization
class GoodClass {
private:
    int value_;
public:
    GoodClass() : value_(0) {}  // value_ initialized to 0
};
```

### 2. Resource Leaks
```cpp
// Wrong: resource leak
class BadResourceManager {
private:
    int* data_;
public:
    BadResourceManager(int size) : data_(new int[size]) {}
    // Missing destructor! Memory leak!
};

// Correct: proper cleanup
class GoodResourceManager {
private:
    int* data_;
public:
    GoodResourceManager(int size) : data_(new int[size]) {}
    ~GoodResourceManager() { delete[] data_; }
};
```

### 3. Shallow Copy Issues
```cpp
// Wrong: shallow copy
class BadArray {
private:
    int* data_;
    size_t size_;
public:
    BadArray(const BadArray& other) 
        : data_(other.data_), size_(other.size_) {}  // Shallow copy!
    // Both objects share the same memory!
};

// Correct: deep copy
class GoodArray {
private:
    int* data_;
    size_t size_;
public:
    GoodArray(const GoodArray& other) : size_(other.size_) {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
};
```

---

## Assessment

### Quiz Questions
1. What is the difference between assignment and initialization?
2. Why are initializer lists preferred over assignment in constructors?
3. What is RAII and why is it important?
4. When should you implement the Rule of Three/Five?

### Practical Assessment
- Implement constructors and destructors correctly
- Apply RAII principles to resource management
- Implement proper copy and move semantics
- Handle constructor exceptions appropriately

---

## Homework Assignment

### Task 1: Resource Management Class
Implement:
1. A class that manages a resource (file, memory, network connection)
2. Proper constructor and destructor implementation
3. RAII pattern for automatic cleanup
4. Exception handling for resource acquisition

### Task 2: Copy and Move Semantics
Create:
1. A class that requires custom copy and move operations
2. Implementation following Rule of Five
3. Efficient move semantics
4. Self-assignment handling

### Task 3: Advanced Initialization
Apply:
1. Constructor initializer lists
2. Delegate constructors
3. Member initialization
4. Exception-safe initialization

---

## Next Lesson Preview

In the next lesson, we'll learn about copy and move semantics:
- Deep vs shallow copying
- Move semantics optimization
- Perfect forwarding
- Rule of Zero implementation

Make sure you understand constructors and destructors before moving on!
