# Lesson 10.1: Classes Deep Dive

## Learning Objectives
- Master advanced class design and encapsulation
- Understand access specifiers and member functions
- Learn static members and nested classes
- Practice with class relationships and composition
- Explore modern class features and best practices

## Prerequisites
- Completed Lesson 9.3 (Source Files and Programs)
- Understanding of basic classes and objects
- Knowledge of constructors and destructors

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Advanced Class Design

#### Encapsulation Principles
- **Data hiding:** Private members protect internal state
- **Interface design:** Public methods provide controlled access
- **Abstraction:** Hide implementation details from users
- **Modularity:** Classes represent cohesive units of functionality

#### Access Specifiers
```cpp
class MyClass {
public:
    // Public interface - accessible from anywhere
    void publicMethod();
    int publicData;
    
protected:
    // Protected interface - accessible by derived classes
    void protectedMethod();
    int protectedData;
    
private:
    // Private implementation - only accessible within class
    void privateMethod();
    int privateData;
};
```

### 2. Member Functions

#### Function Types
```cpp
class BankAccount {
private:
    double balance_;
    
public:
    // Constructor
    BankAccount(double initial_balance);
    
    // Destructor
    ~BankAccount();
    
    // Regular member functions
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;  // Const member function
    
    // Static member functions
    static int getAccountCount();
    
    // Virtual functions (for inheritance)
    virtual void displayInfo() const;
};
```

#### Const Correctness
```cpp
class Container {
private:
    std::vector<int> data_;
    
public:
    // Const member function - cannot modify object state
    size_t size() const {
        return data_.size();
    }
    
    // Non-const member function - can modify object state
    void add(int value) {
        data_.push_back(value);
    }
    
    // Const reference parameter
    void process(const std::vector<int>& input) const;
};
```

### 3. Static Members

#### Static Data Members
```cpp
class Counter {
private:
    static int total_count_;  // Shared across all instances
    int instance_id_;
    
public:
    Counter() : instance_id_(++total_count_) {}
    
    static int getTotalCount() {
        return total_count_;
    }
    
    int getInstanceId() const {
        return instance_id_;
    }
};

// Static member definition (outside class)
int Counter::total_count_ = 0;
```

#### Static Member Functions
```cpp
class MathUtils {
public:
    static double pi() { return 3.14159; }
    static double square(double x) { return x * x; }
    static int max(int a, int b) { return (a > b) ? a : b; }
};

// Usage
double area = MathUtils::pi() * MathUtils::square(radius);
```

---

## Demonstration (25 minutes)

### Advanced Class Examples
```cpp
#include <iostream>
#include <vector>
#include <string>

class Student {
private:
    std::string name_;
    int id_;
    std::vector<double> grades_;
    static int next_id_;
    
public:
    Student(const std::string& name);
    
    void addGrade(double grade);
    double getAverage() const;
    void displayInfo() const;
    
    static int getNextId();
    static void resetIdCounter();
};

int Student::next_id_ = 1000;

Student::Student(const std::string& name) : name_(name), id_(++next_id_) {}

void Student::addGrade(double grade) {
    grades_.push_back(grade);
}

double Student::getAverage() const {
    if (grades_.empty()) return 0.0;
    double sum = 0.0;
    for (double grade : grades_) {
        sum += grade;
    }
    return sum / grades_.size();
}

void Student::displayInfo() const {
    std::cout << "Student: " << name_ << " (ID: " << id_ << ")" << std::endl;
    std::cout << "Average: " << getAverage() << std::endl;
}

int Student::getNextId() {
    return next_id_;
}

void demonstrateAdvancedClasses() {
    std::cout << "=== Advanced Classes Demonstration ===" << std::endl;
    
    Student s1("Alice");
    Student s2("Bob");
    
    s1.addGrade(85.5);
    s1.addGrade(92.0);
    s1.addGrade(78.5);
    
    s2.addGrade(90.0);
    s2.addGrade(88.5);
    
    s1.displayInfo();
    s2.displayInfo();
    
    std::cout << "Next student ID: " << Student::getNextId() << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Advanced Class Design
Design advanced classes:

**Tasks:**
1. Create classes with proper encapsulation
2. Implement static members and functions
3. Design const-correct interfaces
4. Build nested class structures

### Activity 2: Class Relationships
Implement class relationships:

**Tasks:**
1. Design composition relationships
2. Implement aggregation patterns
3. Create association relationships
4. Build complex object hierarchies

### Activity 3: Modern Class Features
Use modern class features:

**Tasks:**
1. Implement move semantics
2. Use smart pointers in classes
3. Apply RAII principles
4. Design exception-safe classes

---

## Key Concepts

### 1. Encapsulation
```cpp
class BankAccount {
private:
    double balance_;  // Hidden implementation detail
    
public:
    void deposit(double amount) {
        if (amount > 0) {
            balance_ += amount;  // Controlled access
        }
    }
    
    double getBalance() const {
        return balance_;  // Read-only access
    }
};
```

### 2. Static Members
```cpp
class Database {
private:
    static int connection_count_;
    
public:
    static int getConnectionCount() {
        return connection_count_;
    }
    
    static void incrementConnections() {
        ++connection_count_;
    }
};
```

### 3. Nested Classes
```cpp
class LinkedList {
public:
    class Node {
    private:
        int data_;
        Node* next_;
        
    public:
        Node(int data) : data_(data), next_(nullptr) {}
        int getData() const { return data_; }
        Node* getNext() const { return next_; }
        void setNext(Node* next) { next_ = next; }
    };
    
private:
    Node* head_;
    
public:
    LinkedList() : head_(nullptr) {}
    void add(int data);
    void display() const;
};
```

---

## Best Practices

### 1. Class Design
- Keep classes focused and cohesive
- Use appropriate access specifiers
- Implement const-correct interfaces
- Follow single responsibility principle

### 2. Member Functions
- Use const member functions for read-only operations
- Implement proper error handling
- Use static functions for utility operations
- Document function purposes and parameters

### 3. Data Members
- Make data members private by default
- Use static members for shared state
- Initialize members in constructor initializer lists
- Use smart pointers for dynamic memory

---

## Common Pitfalls

### 1. Inappropriate Access Levels
```cpp
// Wrong: exposing implementation details
class BadClass {
public:
    std::vector<int> data_;  // Should be private
    void sort_data();        // Should be private
};

// Correct: proper encapsulation
class GoodClass {
private:
    std::vector<int> data_;
    void sort_data();
    
public:
    void add(int value);
    void display() const;
};
```

### 2. Missing Const Correctness
```cpp
// Wrong: non-const getter
class BadClass {
private:
    int value_;
public:
    int getValue() { return value_; }  // Should be const
};

// Correct: const getter
class GoodClass {
private:
    int value_;
public:
    int getValue() const { return value_; }
};
```

### 3. Static Member Issues
```cpp
// Wrong: missing static member definition
class BadClass {
private:
    static int count_;  // Declared but not defined
public:
    static int getCount() { return count_; }
};

// Correct: define static member
class GoodClass {
private:
    static int count_;
public:
    static int getCount() { return count_; }
};

int GoodClass::count_ = 0;  // Definition outside class
```

---

## Assessment

### Quiz Questions
1. What are the benefits of encapsulation?
2. When should you use static members?
3. What is the difference between const and non-const member functions?
4. How do you properly implement static data members?

### Practical Assessment
- Design classes with proper encapsulation
- Implement static members correctly
- Use const-correct interfaces
- Handle class relationships appropriately

---

## Homework Assignment

### Task 1: Advanced Class Library
Implement:
1. A collection of advanced classes with proper encapsulation
2. Classes with static members and functions
3. Nested class structures
4. Const-correct interfaces

### Task 2: Class Relationships
Design:
1. Composition relationships between classes
2. Aggregation patterns
3. Association relationships
4. Complex object hierarchies

### Task 3: Modern Class Features
Apply:
1. Move semantics in class design
2. Smart pointers for memory management
3. RAII principles
4. Exception-safe class implementations

---

## Next Lesson Preview

In the next lesson, we'll learn about constructors and destructors:
- Constructor types and initialization
- Destructor implementation and RAII
- Copy and move semantics
- Rule of Three/Five/Zero

Make sure you understand advanced class design before moving on!
