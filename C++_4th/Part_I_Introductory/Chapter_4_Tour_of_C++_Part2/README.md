# Chapter 4: A Tour of C++ (Part 2)

## 📘 Learning Objectives

After completing this chapter, you will:
- Understand advanced C++ features and concepts
- Learn about object-oriented programming in C++
- Explore the Standard Template Library (STL)
- Understand memory management and RAII
- Get introduced to modern C++ features

## 🎯 Key Concepts

### 1. Advanced Classes and Inheritance

- **Class inheritance**: Base and derived classes
- **Virtual functions**: Polymorphism and dynamic dispatch
- **Abstract classes**: Pure virtual functions
- **Constructor and destructor**: Object lifecycle
- **Access control**: Public, private, protected inheritance

### 2. Templates and Generic Programming

- **Function templates**: Generic functions
- **Class templates**: Generic classes
- **Template specialization**: Specialized implementations
- **Template instantiation**: How templates work
- **Generic algorithms**: Template-based algorithms

### 3. Standard Template Library (STL)

- **Containers**: vector, list, map, set, etc.
- **Iterators**: Container traversal
- **Algorithms**: sort, find, transform, etc.
- **Function objects**: Predicates and comparators
- **STL design**: Generic programming principles

### 4. Memory Management

- **Dynamic memory**: new and delete
- **Smart pointers**: unique_ptr, shared_ptr
- **RAII**: Resource Acquisition Is Initialization
- **Memory leaks**: Prevention and detection
- **Exception safety**: Exception-safe memory management

### 5. Modern C++ Features

- **C++11 features**: auto, lambda, range-based for
- **C++14 features**: Generic lambdas, auto return
- **C++17 features**: Structured bindings, if constexpr
- **C++20 features**: Concepts, ranges, coroutines
- **Best practices**: Modern C++ coding style

## 🧩 Practice Exercises

### Exercise 4.1: Inheritance and Polymorphism
Create a class hierarchy with virtual functions.

### Exercise 4.2: Templates
Implement function and class templates.

### Exercise 4.3: STL Usage
Use STL containers and algorithms.

### Exercise 4.4: Smart Pointers
Use smart pointers for memory management.

### Exercise 4.5: Modern C++ Features
Apply modern C++ features in your code.

## 💻 Code Examples

### Inheritance and Polymorphism
```cpp
#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual double area() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    void draw() const override { std::cout << "Drawing a circle" << std::endl; }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
    void draw() const override { std::cout << "Drawing a rectangle" << std::endl; }
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

### Templates
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
T maximum(const T& a, const T& b) {
    return (a > b) ? a : b;
}

template<typename T>
class Stack {
private:
    std::vector<T> elements;
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    T pop() {
        if (elements.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }
    
    bool empty() const {
        return elements.empty();
    }
};

int main() {
    std::cout << maximum(10, 20) << std::endl;
    std::cout << maximum(3.14, 2.71) << std::endl;
    
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    
    while (!int_stack.empty()) {
        std::cout << int_stack.pop() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### STL Usage
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

int main() {
    // Vector operations
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Map usage
    std::map<std::string, int> ages;
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Set usage
    std::set<int> unique_numbers = {1, 2, 2, 3, 3, 3, 4, 5};
    std::cout << "Unique numbers: ";
    for (int num : unique_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Smart Pointers
```cpp
#include <iostream>
#include <memory>

class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " created" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed" << std::endl;
    }
    
    int getId() const { return id_; }
    
private:
    int id_;
};

int main() {
    // unique_ptr
    auto resource1 = std::make_unique<Resource>(1);
    std::cout << "Resource 1 ID: " << resource1->getId() << std::endl;
    
    // shared_ptr
    auto resource2 = std::make_shared<Resource>(2);
    std::cout << "Resource 2 ID: " << resource2->getId() << std::endl;
    
    // weak_ptr
    std::weak_ptr<Resource> weak_resource = resource2;
    if (auto locked = weak_resource.lock()) {
        std::cout << "Weak pointer locked, ID: " << locked->getId() << std::endl;
    }
    
    return 0;
}
```

### Modern C++ Features
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>

int main() {
    // C++11: auto and lambda
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    auto doubled = [](int x) { return x * 2; };
    
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), doubled);
    
    // C++17: structured bindings
    std::map<std::string, int> data = {{"Alice", 25}, {"Bob", 30}};
    for (const auto& [name, age] : data) {
        std::cout << name << ": " << age << std::endl;
    }
    
    // C++17: if constexpr
    template<typename T>
    void process(T value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Integer: " << value << std::endl;
        } else {
            std::cout << "Non-integer: " << value << std::endl;
        }
    }
    
    process(42);
    process(3.14);
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **C++ supports multiple programming paradigms** - procedural, object-oriented, and generic
2. **Templates provide powerful generic programming** capabilities
3. **STL offers comprehensive containers and algorithms** for common tasks
4. **Smart pointers automate memory management** and prevent leaks
5. **Modern C++ features make code more expressive** and safer

## 🔗 Next Steps

After completing the tour of C++, proceed to Chapter 5 to learn about user-defined types.

## 📚 Additional Resources

- C++ Reference: Advanced Features
- C++ Core Guidelines: Modern C++
- Practice with advanced C++ features
