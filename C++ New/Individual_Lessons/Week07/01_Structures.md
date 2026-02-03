# Lesson 7.1: Structures

## Learning Objectives
- Master structure declaration and definition
- Understand structure members and access
- Learn structure initialization and assignment
- Practice with nested structures
- Explore structure arrays and pointers

## Prerequisites
- Completed Lesson 6.3 (References)
- Understanding of basic data types
- Knowledge of variable declarations

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Structure Fundamentals

#### What are Structures?
- **User-defined type:** Custom data type combining multiple variables
- **Members:** Individual variables within the structure
- **Encapsulation:** Group related data together
- **Memory layout:** Members stored sequentially in memory

#### Structure Declaration
```cpp
struct Person {
    std::string name;
    int age;
    double height;
    bool is_student;
};
```

### 2. Structure Usage

#### Creating Structure Objects
```cpp
Person person1;                    // Default initialization
Person person2 = {"Alice", 25, 5.6, true};  // Initialization
Person person3{"Bob", 30, 6.0, false};       // C++11 initialization
```

#### Accessing Members
```cpp
person1.name = "Charlie";
person1.age = 35;
std::cout << person1.name << " is " << person1.age << " years old" << std::endl;
```

### 3. Structure Operations

#### Assignment
```cpp
Person person1 = {"Alice", 25, 5.6, true};
Person person2 = person1;  // Copy assignment
Person person3;
person3 = person1;         // Assignment operator
```

#### Arrays of Structures
```cpp
Person people[3] = {
    {"Alice", 25, 5.6, true},
    {"Bob", 30, 6.0, false},
    {"Charlie", 35, 5.8, true}
};
```

---

## Demonstration (25 minutes)

### Structure Examples
```cpp
#include <iostream>
#include <string>

struct Point {
    double x, y;
    
    void display() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
    
    double distance() const {
        return sqrt(x*x + y*y);
    }
};

void demonstrateStructures() {
    std::cout << "=== Structure Demonstration ===" << std::endl;
    
    Point p1 = {3.0, 4.0};
    Point p2{1.0, 2.0};
    
    std::cout << "Point 1: ";
    p1.display();
    std::cout << "Distance from origin: " << p1.distance() << std::endl;
    
    std::cout << "Point 2: ";
    p2.display();
    std::cout << "Distance from origin: " << p2.distance() << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Structure Design
Design and implement structures:

**Tasks:**
1. Create a Student structure
2. Design a Book structure
3. Implement a Date structure
4. Build a Rectangle structure

### Activity 2: Structure Operations
Practice structure operations:

**Tasks:**
1. Initialize structure objects
2. Access and modify members
3. Use structure arrays
4. Implement structure functions

### Activity 3: Structure Applications
Apply structures to real problems:

**Tasks:**
1. Create a simple database
2. Implement a graphics system
3. Build a student management system
4. Design a game object system

---

## Key Concepts

### 1. Structure Initialization
```cpp
struct Student {
    std::string name;
    int age;
    double gpa;
};

Student s1 = {"Alice", 20, 3.8};  // C-style initialization
Student s2{"Bob", 22, 3.5};       // C++11 initialization
Student s3;                        // Default initialization
```

### 2. Member Access
```cpp
Student student;
student.name = "Charlie";
student.age = 21;
student.gpa = 3.9;

std::cout << student.name << " has GPA " << student.gpa << std::endl;
```

### 3. Structure Functions
```cpp
struct Rectangle {
    double width, height;
    
    double area() const {
        return width * height;
    }
    
    double perimeter() const {
        return 2 * (width + height);
    }
};
```

---

## Best Practices

### 1. Structure Design
- Group related data together
- Use meaningful member names
- Consider data alignment
- Keep structures focused

### 2. Initialization
- Always initialize structures
- Use appropriate initialization syntax
- Consider default values
- Validate input data

### 3. Code Organization
- Define structures in headers
- Use const for read-only operations
- Implement member functions when appropriate
- Document structure purpose

---

## Common Pitfalls

### 1. Uninitialized Members
```cpp
// Wrong: uninitialized structure
Student student;
std::cout << student.name << std::endl;  // Undefined behavior!

// Correct: initialize structure
Student student = {"Alice", 20, 3.8};
```

### 2. Member Access Errors
```cpp
// Wrong: accessing non-existent member
struct Point { double x, y; };
Point p = {1.0, 2.0};
// std::cout << p.z << std::endl;  // Error: no member 'z'

// Correct: access existing members
std::cout << p.x << ", " << p.y << std::endl;
```

### 3. Structure Size Issues
```cpp
// Wrong: assuming structure size
struct Small { int a; };
struct Large { int a[1000]; };

// Correct: use sizeof operator
std::cout << "Small size: " << sizeof(Small) << std::endl;
std::cout << "Large size: " << sizeof(Large) << std::endl;
```

---

## Assessment

### Quiz Questions
1. How do you declare and define a structure?
2. What are the different ways to initialize a structure?
3. How do you access structure members?
4. What is the difference between structure declaration and definition?

### Practical Assessment
- Implement working structure code
- Use structures correctly and safely
- Apply structures to solve problems
- Handle structure operations properly

---

## Homework Assignment

### Task 1: Structure Library
Implement:
1. A Student management structure
2. A Book catalog structure
3. A Date/time structure
4. A geometric shape structure

### Task 2: Structure Operations
Create:
1. Structure comparison functions
2. Structure input/output operations
3. Structure sorting algorithms
4. Structure serialization

### Task 3: Structure Applications
Apply structures to:
1. Database record management
2. Graphics programming
3. Game object systems
4. Configuration management

---

## Next Lesson Preview

In the next lesson, we'll learn about unions:
- Union declaration and usage
- Union vs structure differences
- Union memory layout
- Anonymous unions

Make sure you understand structures before moving on!