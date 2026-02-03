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
#include <memory>  // For smart pointers
using namespace std;

// Base class
class Animal {
public:
    Animal() {
        cout << "[Animal] Constructor\n";
    }

    virtual ~Animal() {
        cout << "[Animal] Destructor\n";
    }

    virtual void speak() const = 0;
};

// Ability class 1
class Flyable {
public:
    Flyable() {
        cout << "[Flyable] Constructor\n";
    }

    virtual ~Flyable() {
        cout << "[Flyable] Destructor\n";
    }

    virtual void fly() const = 0;
};

// Ability class 2
class Swimmable {
public:
    Swimmable() {
        cout << "[Swimmable] Constructor\n";
    }

    virtual ~Swimmable() {
        cout << "[Swimmable] Destructor\n";
    }

    virtual void swim() const = 0;
};

// Derived class
class Bird : public Animal, public Flyable {
public:
    Bird() {
        cout << "[Bird] Constructor\n";
    }

    ~Bird() {
        cout << "[Bird] Destructor\n";
    }

    void speak() const override {
        cout << "Bird says: Tweet!\n";
    }

    void fly() const override {
        cout << "Bird is flying high!\n";
    }
};

// Derived class
class Fish : public Animal, public Swimmable {
public:
    Fish() {
        cout << "[Fish] Constructor\n";
    }

    ~Fish() {
        cout << "[Fish] Destructor\n";
    }

    void speak() const override {
        cout << "Fish says: Blub!\n";
    }

    void swim() const override {
        cout << "Fish is swimming!\n";
    }
};

// Multiple Inheritance
class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck() {
        cout << "[Duck] Constructor\n";
    }

    ~Duck() {
        cout << "[Duck] Destructor\n";
    }

    void speak() const override {
        cout << "Duck says: Quack!\n";
    }

    void fly() const override {
        cout << "Duck flies a little!\n";
    }

    void swim() const override {
        cout << "Duck swims well!\n";
    }
};

// ================================
int main() {
    vector<Animal*> zoo;

    cout << "\n== Creating animals ==" << endl;
    zoo.push_back(new Bird());
    zoo.push_back(new Fish());
    zoo.push_back(new Duck());

    cout << "\n== Interacting with animals ==" << endl;
    for (Animal* animal : zoo) {
        animal->speak();

        // Try casting to ability interfaces
        if (Flyable* f = dynamic_cast<Flyable*>(animal)) {
            f->fly();
        }
        if (Swimmable* s = dynamic_cast<Swimmable*>(animal)) {
            s->swim();
        }

        cout << "---" << endl;
    }

    cout << "\n== Deleting animals ==" << endl;
    for (Animal* animal : zoo) {
        delete animal;  // Virtual destructors ensure correct cleanup
    }

    zoo.clear();

    return 0;
}