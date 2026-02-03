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
#include <vector>
using namespace std;

class Animal {
private:
    int *age;
public:
    // constructor
    Animal() {
        age = new int(1);
        cout << "Animal created!" << endl;
    }
    // destructor
    ~Animal() {
        delete age;
        cout << "Animal destroyed!" << endl;
    }
    virtual void makeSound() = 0;   // pure virtual function
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
    void makeSound() override {
        cout << "Woof!" << endl;
    }

    void bark() {
        cout << "Woof! Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    // constructor
    Cat() {
        cout << "Cat created!" << endl;
    }
    // destructor
    ~Cat() {
        cout << "Cat destroyed!" << endl;
    }
    void makeSound() override {
        cout << "Meow!" << endl;
    }

    void meow() {
        cout << "Meow! Meow!" << endl;
    }
};

int main() {
    // Dog myPuffy; // Dog myPuffy; is a Dog object // int a, b, c, d, e;

    Animal* myPet1; // pointer to Animal type address // int *age;
    myPet1 = new Dog(); // new Dog() is a Dog object // age = new int;
    Animal* myPet2; // pointer to Animal type address // int *age;
    myPet2 = new Cat(); // new Cat() is a Cat object // age = new int;
    // New an array that containt 10 animals
    myPet1->makeSound();  // Woof!
    //  myPet1->bark();
    myPet2->makeSound();  // Meow!
    // myPet2->meow();

    delete myPet1;
    delete myPet2;
    return 0;
}
