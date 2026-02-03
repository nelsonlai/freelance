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
using namespace std;

// Base class 1
class Animal {
public:
    void eat() {
        cout << "Animal eats food." << endl;
    }
};

// Base class 2
class Bird {
public:
    void fly() {
        cout << "Bird flies in the sky." << endl;
    }
};

// Derived class inherits from both Animal and Bird
class Bat : public Animal, public Bird {
public:
    void sleep() {
        cout << "Bat sleeps upside down." << endl;
    }
};

int main() {
    Bat b;
    b.eat();   // from Animal
    b.fly();   // from Bird
    b.sleep(); // own method
    return 0;
}
