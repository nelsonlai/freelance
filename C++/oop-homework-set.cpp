/*
 * OBJECT-ORIENTED PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates OOP concepts including classes, inheritance, and polymorphism:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental OBJECT-ORIENTED PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

// === Homework 1: Encapsulation and Constructor ===
#include <iostream>
using namespace std;

class Laptop {
private:
    string brand;
    double price;
    int ram;

public:
    Laptop(string b, double p, int r) {
        brand = b;
        setPrice(p);
        ram = r;
    }

    void setPrice(double p) {
        if (p > 0) price = p;
    }

    double getPrice() const { return price; }
    string getBrand() const { return brand; }
    int getRAM() const { return ram; }
};

// === Homework 2: Inheritance ===
class Employee {
public:
    virtual double calculateSalary() const = 0;
};

class FullTimeEmployee : public Employee {
public:
    double calculateSalary() const override { return 5000.0; }
};

class PartTimeEmployee : public Employee {
public:
    double calculateSalary() const override { return 2000.0; }
};

// === Homework 3: Friend Class ===
class BankAccount {
protected:
    double balance = 1000;
    friend class Auditor;
};

class Auditor {
public:
    void audit(const BankAccount& acc) {
        cout << "Auditing balance: $" << acc.balance << endl;
    }
};

// === Homework 4: Abstract Class ===
class Appliance {
public:
    virtual double powerUsage() const = 0;
};

class Fan : public Appliance {
public:
    double powerUsage() const override { return 50.0; }
};

class AirConditioner : public Appliance {
public:
    double powerUsage() const override { return 2000.0; }
};

// === Homework 5: Multiple Inheritance ===
class Walkable {
public:
    virtual void walk() const = 0;
};

class Swimmable {
public:
    virtual void swim() const = 0;
};

class Frog : public Walkable, public Swimmable {
public:
    void walk() const override { cout << "Frog hops.\n"; }
    void swim() const override { cout << "Frog swims.\n"; }
};

// === Homework 6: Polymorphism with Base Pointers ===
class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape {
public:
    double area() const override { return 10 * 5; }
};

class Circle : public Shape {
public:
    double area() const override { return 3.14 * 3 * 3; }
};

// === Homework 7: Deep Copy ===
class Sensor {
private:
    int* readings;

public:
    Sensor() {
        readings = new int[3]{1, 2, 3};
    }

    Sensor(const Sensor& other) {
        readings = new int[3];
        for (int i = 0; i < 3; i++) readings[i] = other.readings[i];
    }

    ~Sensor() { delete[] readings; }
};

// === Homework 8: Smart Pointer ===
#include <memory>
class Image {
public:
    Image() { cout << "Image loaded.\n"; }
    ~Image() { cout << "Image freed.\n"; }
};

// === Homework 9: UML to Code ===
class Book {
private:
    string title;
    string state;

public:
    Book(string t) : title(t), state("New") {}
    void borrow() { if (state == "New") state = "Borrowed"; }
    void returnBook() { state = "Returned"; }
    string getTitle() { return title; }
    string getState() { return state; }
};

class User {
protected:
    string name;
public:
    User(string n) : name(n) {}
};

class Admin : public User {
public:
    Admin(string n) : User(n) {}
};

// === Homework 10: Enum and State ===
class TrafficLight {
public:
    enum State { RED, GREEN, YELLOW };
    State current;

    TrafficLight() : current(RED) {}

    void nextState() {
        switch (current) {
            case RED: current = GREEN; break;
            case GREEN: current = YELLOW; break;
            case YELLOW: current = RED; break;
        }
    }

    void printState() {
        switch (current) {
            case RED: cout << "RED\n"; break;
            case GREEN: cout << "GREEN\n"; break;
            case YELLOW: cout << "YELLOW\n"; break;
        }
    }
};

// === Main function to demonstrate ===
int main() {
    Laptop l("Dell", 1000, 16);
    cout << l.getBrand() << " costs $" << l.getPrice() << endl;

    FullTimeEmployee f;
    PartTimeEmployee p;
    cout << "FT Salary: " << f.calculateSalary() << endl;
    cout << "PT Salary: " << p.calculateSalary() << endl;

    BankAccount acc;
    Auditor aud;
    aud.audit(acc);

    Fan fan;
    cout << "Fan uses: " << fan.powerUsage() << "W\n";

    Frog frog;
    frog.walk();
    frog.swim();

    vector<Shape*> shapes;
    shapes.push_back(new Rectangle());
    shapes.push_back(new Circle());
    for (Shape* s : shapes) cout << "Area: " << s->area() << endl;

    Sensor s1;
    Sensor s2 = s1; // deep copy

    unique_ptr<Image> img = make_unique<Image>();

    Book book("1984");
    book.borrow();
    cout << book.getTitle() << " is " << book.getState() << endl;

    TrafficLight light;
    for (int i = 0; i < 4; i++) {
        light.printState();
        light.nextState();
    }

    for (Shape* s : shapes) delete s;

    return 0;
}
