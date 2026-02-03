# Lesson 11.2: Inheritance

## Learning Objectives
- Master base and derived class relationships
- Understand access specifiers and inheritance
- Learn virtual functions and polymorphism
- Practice with abstract classes and interfaces
- Explore multiple inheritance and virtual inheritance

## Prerequisites
- Completed Lesson 11.1 (Operator Overloading)
- Understanding of basic classes and objects
- Knowledge of constructors and destructors

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Inheritance Fundamentals

#### Base and Derived Classes
```cpp
// Base class
class Animal {
protected:
    std::string name_;
    int age_;
    
public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {}
    
    virtual ~Animal() = default;
    
    // Virtual functions for polymorphism
    virtual void makeSound() const {
        std::cout << name_ << " makes a sound" << std::endl;
    }
    
    virtual void move() const {
        std::cout << name_ << " moves" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << "Animal: " << name_ << ", Age: " << age_ << std::endl;
    }
    
    // Non-virtual function
    void eat() const {
        std::cout << name_ << " is eating" << std::endl;
    }
};

// Derived class
class Dog : public Animal {
private:
    std::string breed_;
    
public:
    Dog(const std::string& name, int age, const std::string& breed)
        : Animal(name, age), breed_(breed) {}
    
    // Override virtual functions
    void makeSound() const override {
        std::cout << name_ << " barks: Woof! Woof!" << std::endl;
    }
    
    void move() const override {
        std::cout << name_ << " runs on four legs" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "Breed: " << breed_ << std::endl;
    }
    
    // Dog-specific method
    void fetch() const {
        std::cout << name_ << " is fetching the ball" << std::endl;
    }
    
    const std::string& getBreed() const { return breed_; }
};
```

### 2. Access Specifiers in Inheritance

#### Public, Protected, and Private Inheritance
```cpp
class Base {
public:
    int public_member;
protected:
    int protected_member;
private:
    int private_member;
};

// Public inheritance
class PublicDerived : public Base {
    // public_member is public
    // protected_member is protected
    // private_member is not accessible
};

// Protected inheritance
class ProtectedDerived : protected Base {
    // public_member becomes protected
    // protected_member remains protected
    // private_member is not accessible
};

// Private inheritance
class PrivateDerived : private Base {
    // public_member becomes private
    // protected_member becomes private
    // private_member is not accessible
};
```

### 3. Virtual Functions and Polymorphism

#### Virtual Function Mechanism
```cpp
class Shape {
protected:
    double area_;
    
public:
    Shape() : area_(0.0) {}
    virtual ~Shape() = default;
    
    // Pure virtual function (makes class abstract)
    virtual double calculateArea() = 0;
    
    // Virtual function with default implementation
    virtual void display() const {
        std::cout << "Shape area: " << area_ << std::endl;
    }
    
    // Non-virtual function
    void printArea() const {
        std::cout << "Area: " << area_ << std::endl;
    }
};

class Circle : public Shape {
private:
    double radius_;
    
public:
    Circle(double radius) : radius_(radius) {
        area_ = calculateArea();
    }
    
    double calculateArea() override {
        return 3.14159 * radius_ * radius_;
    }
    
    void display() const override {
        std::cout << "Circle (radius: " << radius_ << "): " << area_ << std::endl;
    }
    
    double getRadius() const { return radius_; }
};

class Rectangle : public Shape {
private:
    double width_, height_;
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {
        area_ = calculateArea();
    }
    
    double calculateArea() override {
        return width_ * height_;
    }
    
    void display() const override {
        std::cout << "Rectangle (" << width_ << "x" << height_ << "): " << area_ << std::endl;
    }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
};
```

### 4. Abstract Classes and Interfaces

#### Pure Virtual Functions
```cpp
// Abstract base class (interface)
class Drawable {
public:
    virtual ~Drawable() = default;
    
    // Pure virtual functions
    virtual void draw() const = 0;
    virtual void move(double x, double y) = 0;
    virtual double getX() const = 0;
    virtual double getY() const = 0;
};

// Concrete implementation
class Point : public Drawable {
private:
    double x_, y_;
    
public:
    Point(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
    
    void draw() const override {
        std::cout << "Drawing point at (" << x_ << ", " << y_ << ")" << std::endl;
    }
    
    void move(double x, double y) override {
        x_ += x;
        y_ += y;
    }
    
    double getX() const override { return x_; }
    double getY() const override { return y_; }
};
```

---

## Demonstration (25 minutes)

### Inheritance Examples
```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Vehicle {
protected:
    std::string brand_;
    std::string model_;
    int year_;
    double speed_;
    
public:
    Vehicle(const std::string& brand, const std::string& model, int year)
        : brand_(brand), model_(model), year_(year), speed_(0.0) {}
    
    virtual ~Vehicle() = default;
    
    virtual void start() {
        std::cout << brand_ << " " << model_ << " is starting" << std::endl;
        speed_ = 0.0;
    }
    
    virtual void stop() {
        std::cout << brand_ << " " << model_ << " is stopping" << std::endl;
        speed_ = 0.0;
    }
    
    virtual void accelerate(double increment) {
        speed_ += increment;
        std::cout << brand_ << " " << model_ << " speed: " << speed_ << " mph" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << year_ << " " << brand_ << " " << model_ << std::endl;
    }
    
    double getSpeed() const { return speed_; }
};

class Car : public Vehicle {
private:
    int doors_;
    std::string fuel_type_;
    
public:
    Car(const std::string& brand, const std::string& model, int year,
        int doors, const std::string& fuel_type)
        : Vehicle(brand, model, year), doors_(doors), fuel_type_(fuel_type) {}
    
    void start() override {
        std::cout << "Starting car engine..." << std::endl;
        Vehicle::start();
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Doors: " << doors_ << ", Fuel: " << fuel_type_ << std::endl;
    }
    
    void openTrunk() const {
        std::cout << "Opening trunk of " << brand_ << " " << model_ << std::endl;
    }
    
    int getDoors() const { return doors_; }
    const std::string& getFuelType() const { return fuel_type_; }
};

class Motorcycle : public Vehicle {
private:
    bool has_sidecar_;
    std::string engine_type_;
    
public:
    Motorcycle(const std::string& brand, const std::string& model, int year,
               bool sidecar, const std::string& engine_type)
        : Vehicle(brand, model, year), has_sidecar_(sidecar), engine_type_(engine_type) {}
    
    void start() override {
        std::cout << "Starting motorcycle engine..." << std::endl;
        Vehicle::start();
    }
    
    void accelerate(double increment) override {
        speed_ += increment * 1.5;  // Motorcycles accelerate faster
        std::cout << brand_ << " " << model_ << " speed: " << speed_ << " mph" << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Sidecar: " << (has_sidecar_ ? "Yes" : "No") 
                  << ", Engine: " << engine_type_ << std::endl;
    }
    
    void wheelie() const {
        std::cout << brand_ << " " << model_ << " is doing a wheelie!" << std::endl;
    }
    
    bool hasSidecar() const { return has_sidecar_; }
    const std::string& getEngineType() const { return engine_type_; }
};

void demonstrateInheritance() {
    std::cout << "=== Inheritance Demonstration ===" << std::endl;
    
    Car car("Toyota", "Camry", 2023, 4, "Gasoline");
    Motorcycle bike("Honda", "CBR600", 2023, false, "Inline-4");
    
    std::cout << "\nVehicle information:" << std::endl;
    car.displayInfo();
    bike.displayInfo();
    
    std::cout << "\nStarting vehicles:" << std::endl;
    car.start();
    bike.start();
    
    std::cout << "\nAccelerating:" << std::endl;
    car.accelerate(20.0);
    bike.accelerate(20.0);
    
    std::cout << "\nVehicle-specific operations:" << std::endl;
    car.openTrunk();
    bike.wheelie();
    
    std::cout << "\nStopping vehicles:" << std::endl;
    car.stop();
    bike.stop();
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Class Hierarchy Design
Design inheritance hierarchies:

**Tasks:**
1. Create base and derived classes
2. Implement virtual functions
3. Use different access specifiers
4. Test polymorphism

### Activity 2: Abstract Classes
Implement abstract classes:

**Tasks:**
1. Create abstract base classes
2. Implement pure virtual functions
3. Create concrete derived classes
4. Test interface contracts

### Activity 3: Multiple Inheritance
Explore multiple inheritance:

**Tasks:**
1. Implement multiple inheritance
2. Handle diamond inheritance
3. Use virtual inheritance
4. Resolve inheritance conflicts

---

## Key Concepts

### 1. Virtual Function Table
```cpp
class Base {
public:
    virtual void func1() { std::cout << "Base::func1" << std::endl; }
    virtual void func2() { std::cout << "Base::func2" << std::endl; }
    void func3() { std::cout << "Base::func3" << std::endl; }
};

class Derived : public Base {
public:
    void func1() override { std::cout << "Derived::func1" << std::endl; }
    void func2() override { std::cout << "Derived::func2" << std::endl; }
    void func3() { std::cout << "Derived::func3" << std::endl; }
};

void demonstrateVirtualFunctions() {
    Base* ptr = new Derived();
    ptr->func1();  // Calls Derived::func1 (virtual)
    ptr->func2();  // Calls Derived::func2 (virtual)
    ptr->func3();  // Calls Base::func3 (non-virtual)
    delete ptr;
}
```

### 2. Constructor and Destructor in Inheritance
```cpp
class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor" << std::endl; }
    ~Derived() override { std::cout << "Derived destructor" << std::endl; }
};

// Constructor order: Base -> Derived
// Destructor order: Derived -> Base
```

### 3. Function Overriding vs Overloading
```cpp
class Base {
public:
    virtual void func(int x) { std::cout << "Base::func(int)" << std::endl; }
    virtual void func(double x) { std::cout << "Base::func(double)" << std::endl; }
};

class Derived : public Base {
public:
    void func(int x) override { std::cout << "Derived::func(int)" << std::endl; }
    // func(double) is inherited from Base
};
```

---

## Best Practices

### 1. Inheritance Design
- Use inheritance for "is-a" relationships
- Prefer composition over inheritance when possible
- Make destructors virtual in base classes
- Use override keyword for clarity

### 2. Virtual Functions
- Use virtual functions for polymorphic behavior
- Implement pure virtual functions in derived classes
- Consider performance implications of virtual functions
- Use final keyword to prevent further overriding

### 3. Access Control
- Use protected for derived class access
- Keep private members truly private
- Consider using public inheritance by default
- Use private inheritance for implementation inheritance

---

## Common Pitfalls

### 1. Slicing Problem
```cpp
// Wrong: object slicing
void processAnimal(Animal animal) {  // Pass by value
    animal.makeSound();
}

Dog dog("Buddy", 3, "Golden Retriever");
processAnimal(dog);  // Only Animal part is copied

// Correct: use pointers or references
void processAnimal(const Animal& animal) {  // Pass by reference
    animal.makeSound();
}

processAnimal(dog);  // Polymorphism works
```

### 2. Missing Virtual Destructor
```cpp
// Wrong: non-virtual destructor
class Base {
public:
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
private:
    int* data_;
public:
    Derived() : data_(new int[100]) {}
    ~Derived() { 
        delete[] data_;
        std::cout << "Derived destructor" << std::endl; 
    }
};

Base* ptr = new Derived();
delete ptr;  // Only Base destructor called - memory leak!

// Correct: virtual destructor
class Base {
public:
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};
```

### 3. Function Hiding
```cpp
class Base {
public:
    void func(int x) { std::cout << "Base::func(int)" << std::endl; }
};

class Derived : public Base {
public:
    void func(double x) { std::cout << "Derived::func(double)" << std::endl; }
    // This hides Base::func(int)
};

Derived d;
d.func(5);    // Calls Derived::func(double) - unexpected!
d.Base::func(5);  // Explicitly call Base version
```

---

## Assessment

### Quiz Questions
1. What is the difference between virtual and non-virtual functions?
2. When should you use virtual destructors?
3. What are pure virtual functions and abstract classes?
4. How does polymorphism work in C++?

### Practical Assessment
- Design proper inheritance hierarchies
- Implement virtual functions correctly
- Use abstract classes appropriately
- Handle inheritance-related issues

---

## Homework Assignment

### Task 1: Animal Hierarchy
Implement:
1. A base Animal class with virtual functions
2. Multiple derived animal classes
3. Polymorphic behavior demonstration
4. Abstract animal behaviors

### Task 2: Shape System
Create:
1. An abstract Shape base class
2. Concrete shape implementations
3. Polymorphic shape operations
4. Shape hierarchy with common interface

### Task 3: Employee System
Design:
1. A base Employee class
2. Different types of employees
3. Virtual functions for calculations
4. Employee management system

---

## Next Lesson Preview

In the next lesson, we'll learn about polymorphism:
- Virtual function mechanisms
- Dynamic binding and late binding
- Virtual function tables
- Runtime type information (RTTI)

Make sure you understand inheritance before moving on!
