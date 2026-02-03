# Chapter 20: Advanced Inheritance

## 📘 Learning Objectives

After completing this chapter, you will:
- Master advanced inheritance patterns and techniques
- Understand virtual inheritance and diamond problem resolution
- Learn about abstract base classes and pure virtual functions
- Master multiple inheritance and interface segregation
- Understand runtime type information (RTTI) and dynamic casting

## 🎯 Key Concepts

### 1. Virtual Inheritance

- **Diamond inheritance problem**: Multiple inheritance ambiguity
- **Virtual base classes**: Shared base class instances
- **Virtual inheritance syntax**: virtual keyword in inheritance
- **Constructor initialization**: Virtual base constructor order
- **Memory layout**: Virtual base class memory organization

### 2. Abstract Base Classes

- **Pure virtual functions**: Functions without implementation
- **Abstract classes**: Classes that cannot be instantiated
- **Interface design**: Pure virtual function interfaces
- **Implementation inheritance**: Concrete derived classes
- **Virtual destructors**: Proper cleanup in inheritance hierarchies

### 3. Multiple Inheritance

- **Multiple base classes**: Inheriting from multiple classes
- **Name resolution**: Ambiguous function resolution
- **Virtual inheritance**: Solving diamond inheritance
- **Interface segregation**: Multiple interface inheritance
- **Composition vs inheritance**: When to use each approach

### 4. Runtime Type Information (RTTI)

- **typeid operator**: Runtime type identification
- **dynamic_cast**: Safe downcasting
- **Virtual function tables**: RTTI implementation
- **Type safety**: Runtime type checking
- **Performance considerations**: RTTI overhead

### 5. Advanced Polymorphism

- **Virtual function overriding**: Proper override syntax
- **Covariant return types**: Derived class return types
- **Virtual function tables**: VTable implementation
- **Virtual inheritance**: Virtual base class handling
- **Performance optimization**: Virtual function calls

## 🧩 Practice Exercises

### Exercise 20.1: Virtual Inheritance
Implement a diamond inheritance hierarchy with virtual inheritance.

### Exercise 20.2: Abstract Base Classes
Create abstract base classes with pure virtual functions.

### Exercise 20.3: Multiple Inheritance
Use multiple inheritance to create complex class hierarchies.

### Exercise 20.4: RTTI and Dynamic Casting
Use RTTI for safe type conversions and runtime type checking.

## 💻 Code Examples

### Virtual Inheritance
```cpp
#include <iostream>
#include <string>

class Animal {
protected:
    std::string name;
public:
    Animal(const std::string& n) : name(n) {}
    virtual ~Animal() = default;
    virtual void makeSound() = 0;
    virtual void eat() = 0;
};

class Mammal : public virtual Animal {
public:
    Mammal(const std::string& n) : Animal(n) {}
    void breathe() { std::cout << name << " breathes with lungs" << std::endl; }
};

class WingedAnimal : public virtual Animal {
public:
    WingedAnimal(const std::string& n) : Animal(n) {}
    void fly() { std::cout << name << " can fly" << std::endl; }
};

class Bat : public Mammal, public WingedAnimal {
public:
    Bat(const std::string& n) : Animal(n), Mammal(n), WingedAnimal(n) {}
    void makeSound() override { std::cout << name << " makes bat sounds" << std::endl; }
    void eat() override { std::cout << name << " eats insects" << std::endl; }
};

int main() {
    Bat bat("Vampire Bat");
    bat.makeSound();
    bat.eat();
    bat.breathe();
    bat.fly();
    return 0;
}
```

### Abstract Base Classes
```cpp
#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    double perimeter() const override { return 2 * 3.14159 * radius; }
    void draw() const override { std::cout << "Drawing a circle" << std::endl; }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
    double perimeter() const override { return 2 * (width + height); }
    void draw() const override { std::cout << "Drawing a rectangle" << std::endl; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    
    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->area() << std::endl;
        std::cout << "Perimeter: " << shape->perimeter() << std::endl;
        shape->draw();
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use virtual inheritance** to solve diamond inheritance problems
2. **Design abstract base classes** with pure virtual functions
3. **Be careful with multiple inheritance** - prefer composition when possible
4. **Use RTTI judiciously** - it has performance overhead
5. **Always use virtual destructors** in inheritance hierarchies

## 🔗 Next Steps

After mastering advanced inheritance, proceed to Chapter 21 to learn about advanced polymorphism.

## 📚 Additional Resources

- C++ Reference: Virtual Inheritance
- C++ Core Guidelines: Inheritance
- Practice with complex inheritance hierarchies
