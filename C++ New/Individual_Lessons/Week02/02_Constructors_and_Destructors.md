# Lesson 2.2: Constructors and Destructors

## Learning Objectives
- Master different types of constructors
- Understand constructor initialization lists
- Learn about destructor behavior and RAII
- Understand object lifecycle management
- Practice constructor and destructor implementation

## Prerequisites
- Completed Lesson 2.1 (Classes and Objects)
- Understanding of classes and member functions
- Basic knowledge of memory management concepts

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Constructor Types

#### Default Constructor
```cpp
class MyClass {
public:
    MyClass() {
        // Default constructor
    }
};
```

#### Parameterized Constructor
```cpp
class MyClass {
public:
    MyClass(int value) {
        // Parameterized constructor
    }
};
```

#### Copy Constructor
```cpp
class MyClass {
public:
    MyClass(const MyClass& other) {
        // Copy constructor
    }
};
```

### 2. Constructor Initialization Lists

#### Basic Initialization List
```cpp
class Student {
private:
    std::string name;
    int age;
    
public:
    Student(const std::string& n, int a) : name(n), age(a) {
        // Initialization list is more efficient
    }
};
```

#### Initialization vs Assignment
```cpp
// Less efficient (assignment)
Student(const std::string& n, int a) {
    name = n;  // Assignment
    age = a;   // Assignment
}

// More efficient (initialization)
Student(const std::string& n, int a) : name(n), age(a) {
    // Direct initialization
}
```

### 3. Destructors

#### Basic Destructor
```cpp
class MyClass {
public:
    ~MyClass() {
        // Destructor - cleanup code
    }
};
```

#### RAII (Resource Acquisition Is Initialization)
- Resources are acquired in constructor
- Resources are released in destructor
- Automatic cleanup when object goes out of scope

### 4. Object Lifecycle

#### Creation and Destruction Order
1. Constructor called when object is created
2. Object exists and can be used
3. Destructor called when object goes out of scope
4. Object memory is freed

---

## Demonstration (25 minutes)

### Basic Constructor and Destructor Example
```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    
public:
    // Default constructor
    Person() : name("Unknown"), age(0) {
        std::cout << "Default constructor called for " << name << std::endl;
    }
    
    // Parameterized constructor
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Parameterized constructor called for " << name << std::endl;
    }
    
    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Copy constructor called for " << name << std::endl;
    }
    
    // Destructor
    ~Person() {
        std::cout << "Destructor called for " << name << std::endl;
    }
    
    // Member functions
    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
};

int main() {
    std::cout << "=== Object Lifecycle Demo ===" << std::endl;
    
    {
        Person p1;  // Default constructor
        p1.displayInfo();
        
        Person p2("Alice", 25);  // Parameterized constructor
        p2.displayInfo();
        
        Person p3 = p2;  // Copy constructor
        p3.displayInfo();
        
    }  // Destructors called here when objects go out of scope
    
    std::cout << "Objects destroyed!" << std::endl;
    return 0;
}
```

### Resource Management Example
```cpp
#include <iostream>
#include <string>

class FileManager {
private:
    std::string filename;
    bool isOpen;
    
public:
    // Constructor opens file
    FileManager(const std::string& name) : filename(name), isOpen(true) {
        std::cout << "Opening file: " << filename << std::endl;
        // Simulate file opening
    }
    
    // Destructor closes file
    ~FileManager() {
        if (isOpen) {
            std::cout << "Closing file: " << filename << std::endl;
            isOpen = false;
        }
    }
    
    void writeData(const std::string& data) {
        if (isOpen) {
            std::cout << "Writing to " << filename << ": " << data << std::endl;
        }
    }
};

void demonstrateRAII() {
    FileManager file("data.txt");
    file.writeData("Hello, World!");
    file.writeData("This is RAII in action!");
    // File automatically closed when file object goes out of scope
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Bank Account with Constructors
Enhance the BankAccount class with proper constructors and destructor:

**Tasks:**
1. Add default constructor
2. Add parameterized constructor with initialization list
3. Add copy constructor
4. Add destructor with cleanup
5. Test object creation and destruction

### Activity 2: Student Management System
Create a Student class with comprehensive constructors:

**Tasks:**
1. Multiple constructors for different initialization scenarios
2. Proper initialization lists
3. Destructor for cleanup
4. Demonstrate object lifecycle

### Activity 3: Resource Management Class
Create a class that manages a resource (like a connection or file):

**Tasks:**
1. Acquire resource in constructor
2. Release resource in destructor
3. Demonstrate RAII principles
4. Handle resource cleanup properly

---

## Key Concepts

### 1. Constructor Initialization Lists
```cpp
class Rectangle {
private:
    double width;
    double height;
    
public:
    // Initialization list - more efficient
    Rectangle(double w, double h) : width(w), height(h) {
        std::cout << "Rectangle created with " << width << " x " << height << std::endl;
    }
};
```

### 2. RAII Pattern
```cpp
class DatabaseConnection {
private:
    std::string connectionString;
    bool connected;
    
public:
    // Acquire resource in constructor
    DatabaseConnection(const std::string& connStr) : connectionString(connStr), connected(true) {
        std::cout << "Connected to database: " << connectionString << std::endl;
    }
    
    // Release resource in destructor
    ~DatabaseConnection() {
        if (connected) {
            std::cout << "Disconnected from database: " << connectionString << std::endl;
            connected = false;
        }
    }
};
```

### 3. Copy Constructor Deep Copy
```cpp
class DynamicArray {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    DynamicArray(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Array created with " << size << " elements" << std::endl;
    }
    
    // Copy constructor - deep copy
    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Array copied with " << size << " elements" << std::endl;
    }
    
    // Destructor
    ~DynamicArray() {
        delete[] data;
        std::cout << "Array destroyed" << std::endl;
    }
};
```

---

## Best Practices

### 1. Constructor Design
- Use initialization lists whenever possible
- Initialize all member variables
- Validate parameters in constructors
- Keep constructors simple and focused

### 2. Destructor Guidelines
- Always implement destructor for classes with resources
- Make destructors virtual for base classes (inheritance)
- Don't throw exceptions from destructors
- Clean up all acquired resources

### 3. RAII Principles
- Acquire resources in constructors
- Release resources in destructors
- Use smart pointers for automatic memory management
- Follow the rule of three/five (copy constructor, assignment, destructor)

---

## Common Pitfalls

### 1. Forgetting Initialization Lists
```cpp
// Wrong: Assignment in constructor body
Student(const std::string& n, int a) {
    name = n;  // Less efficient
    age = a;   // Less efficient
}

// Correct: Initialization list
Student(const std::string& n, int a) : name(n), age(a) {
    // More efficient
}
```

### 2. Resource Leaks
```cpp
// Wrong: Not cleaning up resources
class BadClass {
private:
    int* data;
public:
    BadClass() { data = new int[100]; }
    // Missing destructor - memory leak!
};

// Correct: Proper cleanup
class GoodClass {
private:
    int* data;
public:
    GoodClass() { data = new int[100]; }
    ~GoodClass() { delete[] data; }  // Proper cleanup
};
```

### 3. Shallow Copy Issues
```cpp
// Wrong: Shallow copy
class BadCopy {
private:
    int* data;
public:
    BadCopy(const BadCopy& other) : data(other.data) {
        // Shallow copy - both objects share same memory!
    }
};

// Correct: Deep copy
class GoodCopy {
private:
    int* data;
    size_t size;
public:
    GoodCopy(const GoodCopy& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
};
```

---

## Assessment

### Quiz Questions
1. What is the difference between initialization and assignment in constructors?
2. When is the destructor called?
3. What is RAII and why is it important?
4. What is the purpose of a copy constructor?

### Practical Assessment
- Implement constructors and destructors correctly
- Demonstrate RAII principles
- Handle object lifecycle properly
- Avoid common pitfalls

---

## Homework Assignment

### Task 1: Enhanced Bank Account
Enhance the BankAccount class with:
1. Multiple constructors (default, parameterized, copy)
2. Proper initialization lists
3. Destructor with transaction logging
4. Copy constructor for account duplication

### Task 2: Library Book Management
Create a LibraryBook class with:
1. Constructors for different book types
2. Resource management for book status
3. Copy constructor for book duplication
4. Destructor for cleanup

### Task 3: Memory Management Class
Create a class that manages dynamic memory:
1. Constructor allocates memory
2. Destructor frees memory
3. Copy constructor performs deep copy
4. Demonstrate RAII principles

---

## Code Examples for Practice

### Complete Constructor/Destructor Example
```cpp
#include <iostream>
#include <string>
#include <vector>

class Course {
private:
    std::string courseName;
    std::string instructor;
    std::vector<std::string> students;
    int maxStudents;
    
public:
    // Default constructor
    Course() : courseName("Unknown"), instructor("TBA"), maxStudents(30) {
        std::cout << "Default constructor: " << courseName << std::endl;
    }
    
    // Parameterized constructor
    Course(const std::string& name, const std::string& instructor, int max = 30)
        : courseName(name), instructor(instructor), maxStudents(max) {
        std::cout << "Parameterized constructor: " << courseName << std::endl;
    }
    
    // Copy constructor
    Course(const Course& other) 
        : courseName(other.courseName), instructor(other.instructor),
          students(other.students), maxStudents(other.maxStudents) {
        std::cout << "Copy constructor: " << courseName << std::endl;
    }
    
    // Destructor
    ~Course() {
        std::cout << "Destructor: " << courseName << " (Students: " 
                  << students.size() << ")" << std::endl;
    }
    
    // Member functions
    void addStudent(const std::string& studentName) {
        if (students.size() < maxStudents) {
            students.push_back(studentName);
            std::cout << "Added student: " << studentName << std::endl;
        } else {
            std::cout << "Course is full!" << std::endl;
        }
    }
    
    void displayInfo() const {
        std::cout << "Course: " << courseName << std::endl;
        std::cout << "Instructor: " << instructor << std::endl;
        std::cout << "Students: " << students.size() << "/" << maxStudents << std::endl;
    }
};

int main() {
    {
        Course c1;  // Default constructor
        c1.displayInfo();
        
        Course c2("C++ Programming", "Dr. Smith", 25);  // Parameterized
        c2.addStudent("Alice");
        c2.addStudent("Bob");
        c2.displayInfo();
        
        Course c3 = c2;  // Copy constructor
        c3.displayInfo();
    }  // Destructors called here
    
    return 0;
}
```

---

## Next Lesson Preview

In the next lesson, we'll learn about templates:
- Function templates
- Class templates
- Template instantiation
- Generic programming concepts

Make sure you understand constructors, destructors, and RAII before moving on!
