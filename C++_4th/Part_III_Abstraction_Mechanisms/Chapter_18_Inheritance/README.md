# Chapter 18: Inheritance

## 📘 Learning Objectives

After completing this chapter, you will:
- Master inheritance hierarchies and relationships
- Understand virtual functions and polymorphism
- Learn about abstract classes and interfaces
- Master multiple inheritance and virtual bases
- Understand access control and inheritance

## 🎯 Key Concepts

### 1. Inheritance Basics

- **Base class**: Parent class providing common functionality
- **Derived class**: Child class inheriting from base class
- **Access control**: public, protected, private inheritance
- **Inheritance hierarchy**: Tree of related classes
- **Is-a relationship**: Derived class is a type of base class

### 2. Virtual Functions

- **Virtual functions**: Runtime polymorphism
- **Pure virtual functions**: Abstract functions
- **Virtual destructors**: Proper cleanup in hierarchies
- **Override keyword**: Explicit virtual function override
- **Final keyword**: Prevent further inheritance

### 3. Abstract Classes

- **Abstract classes**: Cannot be instantiated
- **Pure virtual functions**: Must be implemented by derived classes
- **Interface classes**: Pure virtual functions only
- **Abstract base classes**: Common interface for derived classes

### 4. Multiple Inheritance

- **Multiple inheritance**: Inheriting from multiple base classes
- **Virtual inheritance**: Resolving diamond problem
- **Virtual base classes**: Shared base class instances
- **Ambiguity resolution**: Resolving naming conflicts

### 5. Access Control

- **Public inheritance**: Is-a relationship
- **Protected inheritance**: Implementation inheritance
- **Private inheritance**: Has-a relationship
- **Access specifiers**: public, protected, private

## 🧩 Practice Exercises

### Exercise 18.1: Basic Inheritance
Create inheritance hierarchies with different access levels.

### Exercise 18.2: Virtual Functions
Implement runtime polymorphism with virtual functions.

### Exercise 18.3: Abstract Classes
Design abstract base classes and interfaces.

### Exercise 18.4: Multiple Inheritance
Handle complex inheritance scenarios.

## 💻 Code Examples

### Basic Inheritance
```cpp
#include <iostream>
#include <string>

// Base class
class Animal {
protected:
    std::string name;
    int age;
    
public:
    Animal(const std::string& name, int age) : name(name), age(age) {}
    
    virtual void make_sound() const = 0;  // Pure virtual function
    virtual void display_info() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    
    virtual ~Animal() = default;  // Virtual destructor
};

// Derived class
class Dog : public Animal {
private:
    std::string breed;
    
public:
    Dog(const std::string& name, int age, const std::string& breed)
        : Animal(name, age), breed(breed) {}
    
    void make_sound() const override {
        std::cout << name << " barks!" << std::endl;
    }
    
    void display_info() const override {
        Animal::display_info();
        std::cout << "Breed: " << breed << std::endl;
    }
};

int main() {
    Dog dog("Buddy", 3, "Golden Retriever");
    dog.display_info();
    dog.make_sound();
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use public inheritance** for is-a relationships
2. **Implement virtual destructors** in base classes
3. **Use pure virtual functions** for abstract interfaces
4. **Prefer composition over inheritance** when possible
5. **Use override keyword** for clarity and safety

## 🔗 Next Steps

After mastering inheritance, proceed to Chapter 19 to learn about templates and generic programming.

## 📚 Additional Resources

- C++ Reference: Inheritance
- C++ Core Guidelines: Inheritance
- Practice with complex inheritance hierarchies
