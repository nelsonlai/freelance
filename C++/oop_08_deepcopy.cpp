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

class Box {
private:
    int length;
    int *pdata;

public:
    Box(int l) {
        length = l;
        pdata = new int;
        *pdata = 12; // *pdata = 12;
        cout << "Constructor called!" << endl;
    }

    // Copy constructor for deepcopy
    Box(const Box& b) {
        length = b.length;
        pdata = new int;
        *pdata = *b.pdata;
        cout << "Copy constructor called!" << endl;
    }

    void show() {
        cout << "Length: " << length << endl;
    }
};

int main() {
    Box b1(10); // int a(12);
    Box b2 = b1;   // Copy constructor is called
    // b2.pdata = 13; // b2.pdata = 13;
    b2.show();
    return 0;
}
// Deep copy