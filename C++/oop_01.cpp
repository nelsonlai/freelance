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

class Car {
public:
    Car() {     // constructor
        cout << "Car is created!" << endl;
    }
    
    ~Car() {    // destructor
        cout << "Car is destroyed!" << endl;
    }
};

int main() {
    // Car myCar;

    Car *myCar = new Car();

    delete myCar;

    return 0;
}