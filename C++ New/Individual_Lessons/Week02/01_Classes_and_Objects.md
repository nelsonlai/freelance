# Lesson 2.1: Classes and Objects

## Learning Objectives
- Understand object-oriented programming concepts
- Learn class definition and object creation
- Master access specifiers (public, private, protected)
- Learn member variables and functions
- Understand encapsulation principles

## Prerequisites
- Completed all Week 1 lessons
- Understanding of variables, functions, and control structures
- Basic understanding of data types and memory concepts

## Duration
90 minutes

---

## Lecture Content (35 minutes)

### 1. Object-Oriented Programming Concepts

#### Core OOP Principles
- **Encapsulation:** Bundling data and methods together
- **Abstraction:** Hiding implementation details
- **Inheritance:** Creating new classes from existing ones
- **Polymorphism:** Same interface, different implementations

#### Class vs Object
- **Class:** Blueprint or template (like a cookie cutter)
- **Object:** Instance of a class (like a specific cookie)

### 2. Class Definition

#### Basic Class Syntax
```cpp
class ClassName {
private:
    // Private members (data and functions)
    
public:
    // Public members (interface)
    
protected:
    // Protected members (for inheritance)
};
```

#### Access Specifiers
- **private:** Only accessible within the class
- **public:** Accessible from anywhere
- **protected:** Accessible within class and derived classes

### 3. Member Variables and Functions

#### Member Variables (Data Members)
```cpp
class BankAccount {
private:
    std::string accountNumber;
    double balance;
    std::string ownerName;
};
```

#### Member Functions (Methods)
```cpp
class BankAccount {
public:
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
    void displayInfo() const;
};
```

### 4. Object Creation and Usage

#### Creating Objects
```cpp
// Different ways to create objects
BankAccount account1;                    // Default constructor
BankAccount account2("12345", 1000.0);   // Parameterized constructor
BankAccount account3 = account2;         // Copy constructor
```

#### Using Objects
```cpp
account1.deposit(500.0);
double balance = account1.getBalance();
account1.displayInfo();
```

---

## Demonstration (25 minutes)

### BankAccount Class Example
```cpp
#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string ownerName;
    double balance;
    
public:
    // Constructor
    BankAccount(const std::string& accNum, const std::string& name, double initialBalance = 0.0)
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {}
    
    // Member functions
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << amount << std::endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew $" << amount << std::endl;
            return true;
        }
        std::cout << "Insufficient funds or invalid amount!" << std::endl;
        return false;
    }
    
    double getBalance() const {
        return balance;
    }
    
    void displayInfo() const {
        std::cout << "Account: " << accountNumber << std::endl;
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }
};

int main() {
    BankAccount account("12345", "Alice Johnson", 1000.0);
    
    account.displayInfo();
    account.deposit(500.0);
    account.withdraw(200.0);
    account.displayInfo();
    
    return 0;
}
```

### Student Class Example
```cpp
class Student {
private:
    std::string name;
    int studentId;
    std::vector<double> grades;
    
public:
    Student(const std::string& n, int id) : name(n), studentId(id) {}
    
    void addGrade(double grade) {
        grades.push_back(grade);
    }
    
    double getAverage() const {
        if (grades.empty()) return 0.0;
        double sum = 0.0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
    
    void displayInfo() const {
        std::cout << "Student: " << name << " (ID: " << studentId << ")" << std::endl;
        std::cout << "Grades: ";
        for (double grade : grades) {
            std::cout << grade << " ";
        }
        std::cout << std::endl;
        std::cout << "Average: " << getAverage() << std::endl;
    }
};
```

---

## Hands-on Practice (30 minutes)

### Activity 1: Library Book Class
Create a `LibraryBook` class with:

**Requirements:**
- Private members: title, author, ISBN, isAvailable
- Public methods: constructor, getters, setters, borrow, return
- Display information method

**Tasks:**
1. Design the class interface
2. Implement the class
3. Create objects and test functionality
4. Demonstrate encapsulation

### Activity 2: Rectangle Class
Create a `Rectangle` class with:

**Requirements:**
- Private members: width, height
- Public methods: constructor, getters, setters
- Methods: area, perimeter, displayInfo

**Tasks:**
1. Implement the Rectangle class
2. Create multiple rectangle objects
3. Calculate and display areas and perimeters
4. Demonstrate data hiding

### Activity 3: Car Class Enhancement
Enhance a basic `Car` class with:

**Requirements:**
- Private members: make, model, year, mileage, fuelLevel
- Public methods: constructor, getters, setters
- Methods: drive, refuel, displayInfo

**Tasks:**
1. Start with basic Car class
2. Add fuel management
3. Add mileage tracking
4. Test all functionality

---

## Key Concepts

### 1. Encapsulation
```cpp
class Circle {
private:
    double radius;  // Hidden from outside
    
public:
    void setRadius(double r) {
        if (r > 0) radius = r;  // Validation
    }
    
    double getRadius() const {
        return radius;  // Controlled access
    }
};
```

### 2. Data Hiding
```cpp
class BankAccount {
private:
    double balance;  // Cannot be directly modified
    
public:
    double getBalance() const {
        return balance;  // Read-only access
    }
    
    bool withdraw(double amount) {
        if (amount <= balance) {  // Validation
            balance -= amount;
            return true;
        }
        return false;
    }
};
```

### 3. Interface Design
```cpp
class Temperature {
private:
    double celsius;
    
public:
    // Clear, simple interface
    void setCelsius(double temp) { celsius = temp; }
    double getCelsius() const { return celsius; }
    double getFahrenheit() const { return celsius * 9.0/5.0 + 32; }
    double getKelvin() const { return celsius + 273.15; }
};
```

---

## Best Practices

### 1. Class Design Principles
- Keep data members private
- Provide public interface methods
- Use meaningful names
- Keep classes focused (single responsibility)

### 2. Member Function Guidelines
- Use `const` for functions that don't modify state
- Validate input parameters
- Return meaningful values
- Handle error conditions

### 3. Naming Conventions
- Class names: PascalCase (e.g., `BankAccount`)
- Member variables: camelCase or with prefix (e.g., `m_balance`)
- Member functions: camelCase (e.g., `getBalance`)

---

## Common Pitfalls

### 1. Access Violations
```cpp
// Wrong: Direct access to private members
BankAccount account;
account.balance = 1000;  // Error: balance is private

// Correct: Use public interface
account.deposit(1000);
```

### 2. Missing const Correctness
```cpp
// Wrong: Non-const getter
double getBalance() { return balance; }  // Allows modification

// Correct: const getter
double getBalance() const { return balance; }  // Read-only
```

### 3. Poor Encapsulation
```cpp
// Wrong: Public data members
class BadClass {
public:
    int x, y;  // Direct access allows invalid states
};

// Correct: Private data with validation
class GoodClass {
private:
    int x, y;
public:
    void setX(int value) { if (value >= 0) x = value; }
    int getX() const { return x; }
};
```

---

## Assessment

### Quiz Questions
1. What is the difference between a class and an object?
2. Explain the purpose of access specifiers.
3. What is encapsulation and why is it important?
4. When should you use `const` member functions?

### Practical Assessment
- Design and implement a class from specifications
- Demonstrate proper encapsulation
- Use appropriate access specifiers
- Create and use objects correctly

---

## Homework Assignment

### Task 1: Book Management System
Create a `Book` class with:
1. Private members: title, author, ISBN, pages, isAvailable
2. Public methods: constructor, getters, setters
3. Methods: borrow, return, displayInfo
4. Create a library with multiple books

### Task 2: Bank Account System
Enhance the BankAccount class with:
1. Transaction history tracking
2. Interest calculation
3. Account type (checking/savings)
4. Overdraft protection

### Task 3: Student Grade System
Create a `Student` class with:
1. Personal information (name, ID, email)
2. Course enrollment
3. Grade management
4. GPA calculation

---

## Code Examples for Practice

### Basic Class Template
```cpp
#include <iostream>
#include <string>

class MyClass {
private:
    // Private data members
    std::string name;
    int value;
    
public:
    // Constructor
    MyClass(const std::string& n, int v) : name(n), value(v) {}
    
    // Getter methods
    std::string getName() const { return name; }
    int getValue() const { return value; }
    
    // Setter methods
    void setName(const std::string& n) { name = n; }
    void setValue(int v) { value = v; }
    
    // Other methods
    void displayInfo() const {
        std::cout << "Name: " << name << ", Value: " << value << std::endl;
    }
};

int main() {
    MyClass obj("Test", 42);
    obj.displayInfo();
    return 0;
}
```

---

## Next Lesson Preview

In the next lesson, we'll learn about constructors and destructors:
- Different types of constructors
- Constructor initialization lists
- Destructor behavior
- Object lifecycle management
- RAII principles

Make sure you understand class design and encapsulation before moving on!
