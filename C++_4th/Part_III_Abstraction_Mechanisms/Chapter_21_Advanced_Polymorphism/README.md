# Chapter 21: Advanced Polymorphism

## 📘 Learning Objectives

After completing this chapter, you will:
- Master advanced polymorphism techniques and patterns
- Understand virtual function tables and their implementation
- Learn about polymorphic containers and type erasure
- Master visitor pattern and double dispatch
- Understand performance implications of virtual functions

## 🎯 Key Concepts

### 1. Virtual Function Tables (VTables)

- **VTable structure**: Virtual function pointer arrays
- **VTable inheritance**: How VTables are inherited and modified
- **Virtual function calls**: Runtime dispatch mechanism
- **Memory layout**: Object memory organization with VTables
- **Performance overhead**: Virtual function call costs

### 2. Polymorphic Containers

- **Heterogeneous containers**: Storing different types in same container
- **Type erasure**: Hiding concrete types behind interfaces
- **Polymorphic algorithms**: Algorithms working on polymorphic objects
- **Container polymorphism**: Different container implementations
- **Iterator polymorphism**: Polymorphic iteration patterns

### 3. Visitor Pattern

- **Double dispatch**: Runtime method selection based on two types
- **Visitor hierarchy**: Visitor class design patterns
- **Accept method**: Element acceptance of visitors
- **Extensibility**: Adding new operations without modifying classes
- **Performance considerations**: Visitor pattern overhead

### 4. Type Erasure

- **Interface-based design**: Hiding implementation details
- **Type-safe polymorphism**: Maintaining type safety
- **Storage optimization**: Efficient polymorphic storage
- **Function objects**: Polymorphic function wrappers
- **Any type**: Universal type containers

### 5. Advanced Polymorphic Patterns

- **Factory pattern**: Polymorphic object creation
- **Strategy pattern**: Polymorphic algorithm selection
- **Command pattern**: Polymorphic command objects
- **Observer pattern**: Polymorphic event handling
- **Template method**: Polymorphic algorithm structure

## 🧩 Practice Exercises

### Exercise 21.1: VTable Implementation
Implement and analyze virtual function table behavior.

### Exercise 21.2: Polymorphic Containers
Create containers that store polymorphic objects.

### Exercise 21.3: Visitor Pattern
Implement the visitor pattern for a complex hierarchy.

### Exercise 21.4: Type Erasure
Use type erasure to create flexible polymorphic systems.

## 💻 Code Examples

### Virtual Function Tables
```cpp
#include <iostream>
#include <vector>

class Base {
public:
    virtual void func1() { std::cout << "Base::func1" << std::endl; }
    virtual void func2() { std::cout << "Base::func2" << std::endl; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void func1() override { std::cout << "Derived::func1" << std::endl; }
    void func2() override { std::cout << "Derived::func2" << std::endl; }
    virtual void func3() { std::cout << "Derived::func3" << std::endl; }
};

int main() {
    Base* base_ptr = new Derived();
    base_ptr->func1();  // Calls Derived::func1
    base_ptr->func2();  // Calls Derived::func2
    
    delete base_ptr;
    return 0;
}
```

### Polymorphic Containers
```cpp
#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual double area() const = 0;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    void draw() const override { std::cout << "Drawing circle" << std::endl; }
    double area() const override { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    void draw() const override { std::cout << "Drawing rectangle" << std::endl; }
    double area() const override { return width * height; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->area() << std::endl;
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Understand VTable mechanics** for debugging and optimization
2. **Use polymorphic containers** for heterogeneous collections
3. **Apply visitor pattern** for extensible operations
4. **Implement type erasure** for flexible interfaces
5. **Consider performance implications** of virtual functions

## 🔗 Next Steps

After mastering advanced polymorphism, proceed to Chapter 22 to learn about template metaprogramming.

## 📚 Additional Resources

- C++ Reference: Virtual Functions
- C++ Core Guidelines: Polymorphism
- Practice with complex polymorphic hierarchies
