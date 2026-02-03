/*
 * OBJECT-ORIENTED PROGRAMMING (OOP) INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate OOP concepts in C++:
 * - Inheritance (single, multilevel, hierarchical)
 * - Types of inheritance
 * - Function overriding
 * - Virtual functions
 * - Polymorphism
 * - Abstract classes and interfaces
 * - Operator overloading
 * - Copy constructor and assignment operator
 * - Shallow vs deep copy
 * - Object composition
 * 
 * Learning Objectives:
 * - Master inheritance concepts
 * - Understand polymorphism
 * - Create abstract classes
 * - Overload operators
 * - Implement proper copy semantics
 * 
 * Prerequisites:
 * - Completed oop_beginner.cpp
 * - Understanding of classes and objects
 * - Familiarity with pointers
 * 
 * Key Topics Covered:
 * - Inheritance types
 * - Virtual functions and polymorphism
 * - Abstract classes
 * - Operator overloading
 * - Rule of Three
 * - Composition vs Inheritance
 */

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ==============================================================================
// SECTION 1: INHERITANCE BASICS
// ==============================================================================
/*
 * INHERITANCE:
 * 
 * Mechanism where a new class (derived/child) is created from
 * an existing class (base/parent).
 * 
 * Syntax:
 * class Derived : accessSpecifier Base {
 *     // members
 * };
 * 
 * Benefits:
 * - Code reusability
 * - Establishing relationships
 * - Polymorphism support
 * - Logical hierarchy
 * 
 * "IS-A" relationship: Derived IS-A Base
 * Example: Dog IS-A Animal
 */

// Base class
class Animal {
protected:  // Accessible in derived classes
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "   Animal constructor: " << name << endl;
    }
    
    void eat() const {
        cout << "   " << name << " is eating" << endl;
    }
    
    void sleep() const {
        cout << "   " << name << " is sleeping" << endl;
    }
    
    void displayInfo() const {
        cout << "   Name: " << name << ", Age: " << age << endl;
    }
};

// Derived class
class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "   Dog constructor: " << name << endl;
    }
    
    void bark() const {
        cout << "   " << name << " says: Woof! Woof!" << endl;
    }
    
    void displayInfo() const {
        Animal::displayInfo();  // Call base class method
        cout << "   Breed: " << breed << endl;
    }
};

class Cat : public Animal {
private:
    string color;
    
public:
    Cat(string n, int a, string c) : Animal(n, a), color(c) {
        cout << "   Cat constructor: " << name << endl;
    }
    
    void meow() const {
        cout << "   " << name << " says: Meow!" << endl;
    }
    
    void displayInfo() const {
        Animal::displayInfo();
        cout << "   Color: " << color << endl;
    }
};

void inheritanceBasics() {
    cout << "=== INHERITANCE BASICS ===" << endl << endl;
    
    cout << "1. Creating Derived Objects:" << endl;
    Dog dog("Buddy", 3, "Golden Retriever");
    Cat cat("Whiskers", 2, "Orange");
    cout << endl;
    
    cout << "2. Using Inherited Methods:" << endl;
    dog.eat();     // From Animal
    dog.sleep();   // From Animal
    dog.bark();    // From Dog
    cout << endl;
    
    cat.eat();     // From Animal
    cat.sleep();   // From Animal
    cat.meow();    // From Cat
    cout << endl;
    
    cout << "3. Displaying Information:" << endl;
    dog.displayInfo();
    cout << endl;
    cat.displayInfo();
    cout << endl;
}

// ==============================================================================
// SECTION 2: TYPES OF INHERITANCE
// ==============================================================================
/*
 * TYPES OF INHERITANCE:
 * 
 * 1. Single Inheritance: A -> B
 * 2. Multilevel Inheritance: A -> B -> C
 * 3. Multiple Inheritance: A, B -> C
 * 4. Hierarchical Inheritance: A -> B, A -> C
 * 5. Hybrid Inheritance: Combination of above
 */

// Multilevel Inheritance Example
class LivingBeing {
protected:
    bool isAlive;
    
public:
    LivingBeing() : isAlive(true) {
        cout << "   LivingBeing created" << endl;
    }
    
    void breathe() const {
        cout << "   Breathing..." << endl;
    }
};

class Mammal : public LivingBeing {
protected:
    bool hasHair;
    
public:
    Mammal() : hasHair(true) {
        cout << "   Mammal created" << endl;
    }
    
    void feedMilk() const {
        cout << "   Feeding milk to young" << endl;
    }
};

class Human : public Mammal {
private:
    string name;
    
public:
    Human(string n) : name(n) {
        cout << "   Human created: " << name << endl;
    }
    
    void speak() const {
        cout << "   " << name << " says: Hello!" << endl;
    }
    
    void displayCapabilities() const {
        cout << "   " << name << "'s capabilities:" << endl;
        breathe();      // From LivingBeing
        feedMilk();     // From Mammal
        speak();        // From Human
    }
};

void typesOfInheritance() {
    cout << "=== TYPES OF INHERITANCE ===" << endl << endl;
    
    cout << "1. Multilevel Inheritance:" << endl;
    cout << "   LivingBeing -> Mammal -> Human" << endl;
    Human human("Alice");
    cout << endl;
    
    cout << "2. Using Multilevel Inherited Methods:" << endl;
    human.displayCapabilities();
    cout << endl;
}

// ==============================================================================
// SECTION 3: FUNCTION OVERRIDING
// ==============================================================================
/*
 * FUNCTION OVERRIDING:
 * 
 * Redefining a base class function in derived class
 * with SAME signature.
 * 
 * Rules:
 * - Same function name
 * - Same parameters
 * - Same return type (or covariant)
 * - Use virtual for runtime polymorphism
 */

class Shape {
protected:
    string color;
    
public:
    Shape(string c) : color(c) {}
    
    // Function to be overridden
    void draw() const {
        cout << "   Drawing a shape in " << color << endl;
    }
    
    void displayColor() const {
        cout << "   Color: " << color << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {}
    
    // Override draw function
    void draw() const {
        cout << "   Drawing a circle (radius: " << radius 
             << ") in " << color << endl;
    }
};

class Square : public Shape {
private:
    double side;
    
public:
    Square(string c, double s) : Shape(c), side(s) {}
    
    // Override draw function
    void draw() const {
        cout << "   Drawing a square (side: " << side 
             << ") in " << color << endl;
    }
};

void functionOverriding() {
    cout << "=== FUNCTION OVERRIDING ===" << endl << endl;
    
    cout << "1. Creating Shapes:" << endl;
    Circle circle("red", 5.0);
    Square square("blue", 4.0);
    cout << endl;
    
    cout << "2. Calling Overridden Methods:" << endl;
    circle.draw();  // Calls Circle's draw
    square.draw();  // Calls Square's draw
    cout << endl;
    
    cout << "3. Calling Non-overridden Methods:" << endl;
    circle.displayColor();  // Inherited from Shape
    square.displayColor();  // Inherited from Shape
    cout << endl;
}

// ==============================================================================
// SECTION 4: VIRTUAL FUNCTIONS AND POLYMORPHISM
// ==============================================================================
/*
 * VIRTUAL FUNCTIONS:
 * 
 * Functions declared with 'virtual' keyword in base class.
 * Enable runtime polymorphism (dynamic binding).
 * 
 * POLYMORPHISM:
 * "Many forms" - same interface, different implementations.
 * 
 * Runtime Polymorphism:
 * - Achieved through virtual functions
 * - Function call resolved at runtime
 * - Uses vtable (virtual table)
 */

class Employee {
protected:
    string name;
    int id;
    
public:
    Employee(string n, int i) : name(n), id(i) {}
    
    // Virtual function
    virtual double calculateSalary() const {
        return 0.0;
    }
    
    virtual void displayInfo() const {
        cout << "   Employee: " << name << " (ID: " << id << ")" << endl;
    }
    
    // Virtual destructor (important!)
    virtual ~Employee() {
        cout << "   Employee destructor: " << name << endl;
    }
};

class FullTimeEmployee : public Employee {
private:
    double monthlySalary;
    
public:
    FullTimeEmployee(string n, int i, double salary)
        : Employee(n, i), monthlySalary(salary) {}
    
    // Override virtual function
    double calculateSalary() const override {
        return monthlySalary;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "   Type: Full-time" << endl;
        cout << "   Monthly Salary: $" << monthlySalary << endl;
    }
    
    ~FullTimeEmployee() {
        cout << "   FullTimeEmployee destructor: " << name << endl;
    }
};

class HourlyEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;
    
public:
    HourlyEmployee(string n, int i, double rate, int hours)
        : Employee(n, i), hourlyRate(rate), hoursWorked(hours) {}
    
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "   Type: Hourly" << endl;
        cout << "   Hourly Rate: $" << hourlyRate << endl;
        cout << "   Hours Worked: " << hoursWorked << endl;
    }
    
    ~HourlyEmployee() {
        cout << "   HourlyEmployee destructor: " << name << endl;
    }
};

// Polymorphic function
void printEmployeeSalary(const Employee* emp) {
    emp->displayInfo();
    cout << "   Calculated Salary: $" << emp->calculateSalary() << endl;
}

void virtualFunctionsAndPolymorphism() {
    cout << "=== VIRTUAL FUNCTIONS AND POLYMORPHISM ===" << endl << endl;
    
    cout << "1. Creating Employees:" << endl;
    Employee* emp1 = new FullTimeEmployee("Alice", 101, 5000.0);
    Employee* emp2 = new HourlyEmployee("Bob", 102, 25.0, 160);
    cout << endl;
    
    cout << "2. Runtime Polymorphism:" << endl;
    cout << "Employee 1:" << endl;
    printEmployeeSalary(emp1);  // Calls FullTimeEmployee's version
    cout << endl;
    
    cout << "Employee 2:" << endl;
    printEmployeeSalary(emp2);  // Calls HourlyEmployee's version
    cout << endl;
    
    cout << "3. Cleanup (virtual destructors):" << endl;
    delete emp1;
    delete emp2;
    cout << endl;
}

// ==============================================================================
// SECTION 5: ABSTRACT CLASSES AND INTERFACES
// ==============================================================================
/*
 * ABSTRACT CLASS:
 * 
 * Class with at least one pure virtual function.
 * Cannot be instantiated directly.
 * 
 * Pure Virtual Function:
 * virtual returnType functionName() = 0;
 * 
 * INTERFACE:
 * Abstract class with only pure virtual functions.
 * 
 * Purpose:
 * - Define contract for derived classes
 * - Force implementation in derived classes
 * - Achieve abstraction
 */

// Abstract class
class Vehicle {
protected:
    string brand;
    int year;
    
public:
    Vehicle(string b, int y) : brand(b), year(y) {}
    
    // Pure virtual functions (must be overridden)
    virtual void start() const = 0;
    virtual void stop() const = 0;
    virtual double getFuelEfficiency() const = 0;
    
    // Regular virtual function (can be overridden)
    virtual void displayInfo() const {
        cout << "   Brand: " << brand << ", Year: " << year << endl;
    }
    
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
    int doors;
    
public:
    Car(string b, int y, int d) : Vehicle(b, y), doors(d) {}
    
    void start() const override {
        cout << "   Car starting: Turn key" << endl;
    }
    
    void stop() const override {
        cout << "   Car stopping: Apply brakes" << endl;
    }
    
    double getFuelEfficiency() const override {
        return 35.5;  // MPG
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "   Type: Car, Doors: " << doors << endl;
        cout << "   Fuel Efficiency: " << getFuelEfficiency() << " MPG" << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(string b, int y, bool sidecar) 
        : Vehicle(b, y), hasSidecar(sidecar) {}
    
    void start() const override {
        cout << "   Motorcycle starting: Press ignition button" << endl;
    }
    
    void stop() const override {
        cout << "   Motorcycle stopping: Apply hand and foot brakes" << endl;
    }
    
    double getFuelEfficiency() const override {
        return 55.0;  // MPG
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "   Type: Motorcycle" << endl;
        cout << "   Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
        cout << "   Fuel Efficiency: " << getFuelEfficiency() << " MPG" << endl;
    }
};

void abstractClassesAndInterfaces() {
    cout << "=== ABSTRACT CLASSES AND INTERFACES ===" << endl << endl;
    
    // Vehicle v("Generic", 2023);  // ERROR! Can't instantiate abstract class
    
    cout << "1. Creating Concrete Objects:" << endl;
    Vehicle* vehicles[2];
    vehicles[0] = new Car("Toyota", 2023, 4);
    vehicles[1] = new Motorcycle("Harley", 2022, false);
    cout << endl;
    
    cout << "2. Polymorphic Behavior:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "Vehicle " << (i + 1) << ":" << endl;
        vehicles[i]->displayInfo();
        vehicles[i]->start();
        vehicles[i]->stop();
        cout << endl;
    }
    
    // Cleanup
    for (int i = 0; i < 2; i++) {
        delete vehicles[i];
    }
}

// ==============================================================================
// SECTION 6: OPERATOR OVERLOADING
// ==============================================================================
/*
 * OPERATOR OVERLOADING:
 * 
 * Giving special meaning to operators for user-defined types.
 * 
 * Syntax:
 * returnType operator symbol(parameters) {
 *     // implementation
 * }
 * 
 * Can overload: +, -, *, /, ==, !=, <, >, <<, >>, etc.
 * Cannot overload: ::, ., .*, ?:, sizeof
 */

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    
    // Comparison operator
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Unary operator
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    // Compound assignment
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    void display() const {
        cout << real;
        if (imag >= 0)
            cout << " + " << imag << "i";
        else
            cout << " - " << (-imag) << "i";
    }
    
    // Friend function for output stream
    friend ostream& operator<<(ostream& out, const Complex& c);
};

// Stream insertion operator
ostream& operator<<(ostream& out, const Complex& c) {
    out << c.real;
    if (c.imag >= 0)
        out << " + " << c.imag << "i";
    else
        out << " - " << (-c.imag) << "i";
    return out;
}

void operatorOverloading() {
    cout << "=== OPERATOR OVERLOADING ===" << endl << endl;
    
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    
    cout << "1. Complex Numbers:" << endl;
    cout << "   c1 = " << c1 << endl;
    cout << "   c2 = " << c2 << endl;
    cout << endl;
    
    cout << "2. Arithmetic Operations:" << endl;
    Complex c3 = c1 + c2;
    cout << "   c1 + c2 = " << c3 << endl;
    
    Complex c4 = c1 - c2;
    cout << "   c1 - c2 = " << c4 << endl;
    
    Complex c5 = c1 * c2;
    cout << "   c1 * c2 = " << c5 << endl;
    cout << endl;
    
    cout << "3. Comparison:" << endl;
    cout << "   c1 == c2? " << (c1 == c2 ? "Yes" : "No") << endl;
    cout << "   c1 != c2? " << (c1 != c2 ? "Yes" : "No") << endl;
    cout << endl;
    
    cout << "4. Unary Operator:" << endl;
    Complex c6 = -c1;
    cout << "   -c1 = " << c6 << endl;
    cout << endl;
    
    cout << "5. Compound Assignment:" << endl;
    c1 += c2;
    cout << "   c1 += c2 => c1 = " << c1 << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 7: COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR
// ==============================================================================
/*
 * COPY CONSTRUCTOR:
 * Constructor that creates object by copying another object.
 * 
 * Syntax: ClassName(const ClassName& other)
 * 
 * COPY ASSIGNMENT OPERATOR:
 * Assigns one existing object to another.
 * 
 * Syntax: ClassName& operator=(const ClassName& other)
 * 
 * RULE OF THREE:
 * If you define one of these, define all three:
 * 1. Destructor
 * 2. Copy constructor
 * 3. Copy assignment operator
 */

class Array {
private:
    int* data;
    int size;
    
public:
    // Constructor
    Array(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        cout << "   Constructor: Array of size " << size << endl;
    }
    
    // Destructor
    ~Array() {
        delete[] data;
        cout << "   Destructor: Array freed" << endl;
    }
    
    // Copy constructor (deep copy)
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "   Copy constructor: Deep copy created" << endl;
    }
    
    // Copy assignment operator
    Array& operator=(const Array& other) {
        cout << "   Copy assignment operator called" << endl;
        
        if (this != &other) {  // Check for self-assignment
            // Free existing resources
            delete[] data;
            
            // Copy data
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    void set(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }
    
    void display() const {
        cout << "   Array: [";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

void copyConstructorAndAssignment() {
    cout << "=== COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR ===" << endl << endl;
    
    cout << "1. Creating Original Array:" << endl;
    Array arr1(5);
    arr1.set(0, 10);
    arr1.set(1, 20);
    arr1.set(2, 30);
    arr1.display();
    cout << endl;
    
    cout << "2. Copy Constructor (Array arr2 = arr1):" << endl;
    Array arr2 = arr1;  // Copy constructor
    arr2.display();
    cout << endl;
    
    cout << "3. Copy Assignment (arr3 = arr1):" << endl;
    Array arr3(3);
    arr3 = arr1;  // Copy assignment
    arr3.display();
    cout << endl;
    
    cout << "4. Modifying Copy (arr2):" << endl;
    arr2.set(0, 999);
    cout << "   arr1: ";
    arr1.display();
    cout << "   arr2: ";
    arr2.display();
    cout << "   (Deep copy: arr1 unchanged)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 8: SHALLOW VS DEEP COPY
// ==============================================================================
/*
 * SHALLOW COPY:
 * Copies pointer values (addresses), not pointed-to data.
 * Multiple objects share same resource.
 * Problem: Double deletion!
 * 
 * DEEP COPY:
 * Copies actual data, creating independent copy.
 * Each object has its own resource.
 * Solution: Implement proper copy constructor and assignment.
 */

class ShallowCopyExample {
private:
    int* data;
    
public:
    ShallowCopyExample(int value) {
        data = new int(value);
        cout << "   Constructor: Created with value " << *data << endl;
    }
    
    ~ShallowCopyExample() {
        delete data;
        cout << "   Destructor: Freed memory" << endl;
    }
    
    // Default copy constructor does shallow copy
    // ShallowCopyExample(const ShallowCopyExample& other) = default;
    
    void setValue(int value) {
        *data = value;
    }
    
    int getValue() const {
        return *data;
    }
};

class DeepCopyExample {
private:
    int* data;
    
public:
    DeepCopyExample(int value) {
        data = new int(value);
        cout << "   Constructor: Created with value " << *data << endl;
    }
    
    ~DeepCopyExample() {
        delete data;
        cout << "   Destructor: Freed memory" << endl;
    }
    
    // Deep copy constructor
    DeepCopyExample(const DeepCopyExample& other) {
        data = new int(*other.data);  // Create new memory
        cout << "   Deep copy constructor: Independent copy created" << endl;
    }
    
    void setValue(int value) {
        *data = value;
    }
    
    int getValue() const {
        return *data;
    }
};

void shallowVsDeepCopy() {
    cout << "=== SHALLOW VS DEEP COPY ===" << endl << endl;
    
    cout << "1. Deep Copy (Correct Way):" << endl;
    {
        DeepCopyExample obj1(100);
        DeepCopyExample obj2 = obj1;  // Deep copy
        
        obj2.setValue(200);
        cout << "   obj1 value: " << obj1.getValue() << endl;
        cout << "   obj2 value: " << obj2.getValue() << endl;
        cout << "   (Independent copies)" << endl;
    }
    cout << "   (Both destructors called safely)" << endl;
    cout << endl;
    
    cout << "Problem with Shallow Copy:" << endl;
    cout << "   - Multiple objects point to same memory" << endl;
    cout << "   - Modifying one affects others" << endl;
    cout << "   - Double deletion causes crash" << endl;
    cout << endl;
    
    cout << "Solution:" << endl;
    cout << "   ✓ Implement deep copy constructor" << endl;
    cout << "   ✓ Implement deep copy assignment" << endl;
    cout << "   ✓ Follow Rule of Three" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 9: COMPOSITION
// ==============================================================================
/*
 * COMPOSITION:
 * 
 * "HAS-A" relationship: One class contains objects of another class.
 * 
 * Composition vs Inheritance:
 * - Composition: HAS-A (Car HAS-A Engine)
 * - Inheritance: IS-A (Car IS-A Vehicle)
 * 
 * Prefer composition over inheritance when:
 * - No clear IS-A relationship
 * - Want more flexibility
 * - Avoid deep inheritance hierarchies
 */

class Engine {
private:
    int horsepower;
    string type;
    
public:
    Engine(int hp, string t) : horsepower(hp), type(t) {
        cout << "   Engine created: " << horsepower << " HP, " << type << endl;
    }
    
    void start() const {
        cout << "   Engine starting..." << endl;
    }
    
    void stop() const {
        cout << "   Engine stopping..." << endl;
    }
    
    void displayInfo() const {
        cout << "   Engine: " << horsepower << " HP, Type: " << type << endl;
    }
};

class Wheel {
private:
    int size;
    
public:
    Wheel(int s) : size(s) {}
    
    void displayInfo() const {
        cout << "   Wheel size: " << size << " inches" << endl;
    }
};

class CarComposition {
private:
    string brand;
    Engine engine;      // Composition: Car HAS-A Engine
    Wheel wheels[4];    // Composition: Car HAS 4 Wheels
    
public:
    CarComposition(string b, int hp, string engineType, int wheelSize)
        : brand(b), engine(hp, engineType),
          wheels{Wheel(wheelSize), Wheel(wheelSize), 
                 Wheel(wheelSize), Wheel(wheelSize)} {
        cout << "   Car created: " << brand << endl;
    }
    
    void start() {
        cout << "   Starting " << brand << endl;
        engine.start();
    }
    
    void stop() {
        cout << "   Stopping " << brand << endl;
        engine.stop();
    }
    
    void displayInfo() const {
        cout << "   Car: " << brand << endl;
        engine.displayInfo();
        wheels[0].displayInfo();
    }
};

void composition() {
    cout << "=== COMPOSITION ===" << endl << endl;
    
    cout << "1. Creating Car with Composition:" << endl;
    CarComposition car("Tesla", 350, "Electric", 19);
    cout << endl;
    
    cout << "2. Using Composed Objects:" << endl;
    car.start();
    car.displayInfo();
    car.stop();
    cout << endl;
    
    cout << "Composition Benefits:" << endl;
    cout << "   ✓ More flexible than inheritance" << endl;
    cout << "   ✓ Can change components at runtime" << endl;
    cout << "   ✓ Better encapsulation" << endl;
    cout << "   ✓ Avoids deep inheritance hierarchies" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: BEST PRACTICES
// ==============================================================================

void bestPractices() {
    cout << "=== OOP INTERMEDIATE BEST PRACTICES ===" << endl << endl;
    
    cout << "Inheritance:" << endl;
    cout << "   ✓ Use inheritance for IS-A relationships" << endl;
    cout << "   ✓ Make destructors virtual in base classes" << endl;
    cout << "   ✓ Use override keyword for clarity" << endl;
    cout << "   ✓ Prefer composition over inheritance" << endl;
    cout << endl;
    
    cout << "Polymorphism:" << endl;
    cout << "   ✓ Use virtual functions for runtime polymorphism" << endl;
    cout << "   ✓ Mark pure virtual for abstract classes" << endl;
    cout << "   ✓ Use abstract classes to define interfaces" << endl;
    cout << "   ✓ Program to interfaces, not implementations" << endl;
    cout << endl;
    
    cout << "Operator Overloading:" << endl;
    cout << "   ✓ Overload operators intuitively" << endl;
    cout << "   ✓ Return by value for arithmetic operators" << endl;
    cout << "   ✓ Return by reference for assignment operators" << endl;
    cout << "   ✓ Make binary operators friends or members appropriately" << endl;
    cout << endl;
    
    cout << "Rule of Three:" << endl;
    cout << "   ✓ If you define destructor, define copy constructor" << endl;
    cout << "   ✓ If you define copy constructor, define assignment" << endl;
    cout << "   ✓ Implement deep copy for dynamic resources" << endl;
    cout << "   ✓ Check for self-assignment in operator=" << endl;
    cout << endl;
    
    cout << "General:" << endl;
    cout << "   ✓ Follow SOLID principles" << endl;
    cout << "   ✓ Keep inheritance hierarchies shallow" << endl;
    cout << "   ✓ Use composition when appropriate" << endl;
    cout << "   ✓ Make interfaces simple and focused" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        OOP INTERMEDIATE TUTORIAL - C++                     ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Master inheritance, polymorphism, and advanced OOP        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    inheritanceBasics();
    typesOfInheritance();
    functionOverriding();
    virtualFunctionsAndPolymorphism();
    abstractClassesAndInterfaces();
    operatorOverloading();
    copyConstructorAndAssignment();
    shallowVsDeepCopy();
    composition();
    bestPractices();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of OOP Intermediate Tutorial                          ║" << endl;
    cout << "║  Next: Move on to oop_advanced.cpp                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

