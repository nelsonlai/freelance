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
#include <memory>  // For unique_ptr
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

    virtual void speak() const = 0;     // Abstract method (function with no body)

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

    void speak() const override {       // Overriding the speak() method
        cout << "Bird says: Tweet!\n";
    }

    void fly() const override {
        cout << "Bird is flying high!\n";   // Overriding the fly() method
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

int main() {
    // Using unique_ptr for automatic memory management, automatically calling destructors for garbage collection
    vector<unique_ptr<Animal>> zoo;     // C++17 smart pointer

    cout << "\n== Creating animals ==" << endl;
    zoo.push_back(make_unique<Bird>());  // C++17 smart pointer
    zoo.push_back(make_unique<Fish>());  // C++17 smart pointer
    zoo.push_back(make_unique<Duck>());

    cout << "\n== Interacting with animals ==" << endl;
    for (const auto& animal : zoo) {
        animal->speak();

        if (auto f = dynamic_cast<Flyable*>(animal.get())) {
            f->fly();
        }
        if (auto s = dynamic_cast<Swimmable*>(animal.get())) {
            s->swim();
        }

        cout << "---" << endl;
    }

    cout << "\n== Zoo closing. All destructors will be called automatically ==\n";

    return 0;
}