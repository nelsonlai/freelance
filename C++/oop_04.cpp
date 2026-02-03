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

class Animal {
public:
    // constructor
    Animal() {
        cout << "Animal created!" << endl;
    }
    // destructor
    ~Animal() {
        cout << "Animal destroyed!" << endl;
    }
    void eat() {
        cout << "I can eat!" << endl;
    }

    void sleep() {
        cout << "I can sleep!" << endl;
    }
};

class Dog : public Animal {
public:
    // constructor
    Dog() {
        cout << "Dog created!" << endl;
    }
    // destructor
    ~Dog() {
        cout << "Dog destroyed!" << endl;
    }
    void bark() {
        cout << "Woof! Woof!" << endl;
    }
};

int main() {
    Dog myPuffy;        // Dog myPuffy; is a Dog object
    myPuffy.eat();     // Inherited
    myPuffy.sleep();   // Inherited
    myPuffy.bark();    // Own method
    return 0;
}