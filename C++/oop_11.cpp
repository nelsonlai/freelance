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

#include <iostream>
#include <cmath>
using namespace std;

// Abstract base class
class Shape {
private:
    int age;
protected:
    void friendFunction() {
        cout << "This is a friend function." << endl;
    }
public:
    Shape(const string& n) : name(n) {}

    // Virtual destructor
    virtual ~Shape() {}

    // Pure virtual function
    virtual double area() const = 0;

    // Declare ShapePrinter as friend
    friend class ShapePrinter;
};

// Derived class: Circle
class Circle : public Shape {
protected:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }
};

// Derived class: Rectangle
class Rectangle : public Shape {
protected:
    double width, height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {}

    double area() const override {
        return width * height;
    }
};

// Friend class: can access protected members of Shape and derived classes
class ShapePrinter {
public:
    void print(const Shape& s) {
        cout << "Shape: " << s.name << ", Area: " << s.area() << endl;
    }
};

// Main function to demonstrate
int main() {
    Circle c(5.0);
    Rectangle r(4.0, 6.0);
    
    ShapePrinter printer;
    printer.print(c); // Access protected name via friend class
    printer.print(r);

    return 0;
}