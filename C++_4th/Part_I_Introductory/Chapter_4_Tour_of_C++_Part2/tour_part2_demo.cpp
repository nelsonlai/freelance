#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <algorithm>
#include <optional>
#include <functional>

// Demonstrates advanced C++ features - Part 2 of the tour
int main() {
    std::cout << "=== Chapter 4: A Tour of C++ (Part 2) ===" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // 1. Advanced Classes and Inheritance
    std::cout << "\n1. ADVANCED CLASSES AND INHERITANCE:" << std::endl;
    
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
        void draw() const override { std::cout << "Drawing a circle with radius " << radius << std::endl; }
    };
    
    class Rectangle : public Shape {
    private:
        double width, height;
    public:
        Rectangle(double w, double h) : width(w), height(h) {}
        double area() const override { return width * height; }
        void draw() const override { std::cout << "Drawing a rectangle " << width << "x" << height << std::endl; }
    };
    
    class Triangle : public Shape {
    private:
        double base, height;
    public:
        Triangle(double b, double h) : base(b), height(h) {}
        double area() const override { return 0.5 * base * height; }
        void draw() const override { std::cout << "Drawing a triangle with base " << base << " and height " << height << std::endl; }
    };
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0));
    
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "  Area: " << shape->area() << std::endl;
    }
    
    // 2. Templates and Generic Programming
    std::cout << "\n2. TEMPLATES AND GENERIC PROGRAMMING:" << std::endl;
    
    // Function templates
    template<typename T>
    T maximum(const T& a, const T& b) {
        return (a > b) ? a : b;
    }
    
    template<typename T>
    void print_container(const T& container) {
        for (const auto& element : container) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    
    // Class templates
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
        
        size_t size() const {
            return elements.size();
        }
    };
    
    std::cout << "Maximum of 10 and 20: " << maximum(10, 20) << std::endl;
    std::cout << "Maximum of 3.14 and 2.71: " << maximum(3.14, 2.71) << std::endl;
    
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    
    std::cout << "Stack contents (popping): ";
    while (!int_stack.empty()) {
        std::cout << int_stack.pop() << " ";
    }
    std::cout << std::endl;
    
    // 3. Standard Template Library (STL)
    std::cout << "\n3. STANDARD TEMPLATE LIBRARY (STL):" << std::endl;
    
    // Vector operations
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::cout << "Original numbers: ";
    print_container(numbers);
    
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted numbers: ";
    print_container(numbers);
    
    // Find elements
    auto it = std::find(numbers.begin(), numbers.end(), 5);
    if (it != numbers.end()) {
        std::cout << "Found 5 at position: " << (it - numbers.begin()) << std::endl;
    }
    
    // Count elements
    int count = std::count(numbers.begin(), numbers.end(), 5);
    std::cout << "Number of 5s: " << count << std::endl;
    
    // Transform elements
    std::vector<int> doubled_numbers(numbers.size());
    std::transform(numbers.begin(), numbers.end(), doubled_numbers.begin(),
                   [](int x) { return x * 2; });
    std::cout << "Doubled numbers: ";
    print_container(doubled_numbers);
    
    // Map usage
    std::map<std::string, int> ages;
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    ages["Diana"] = 28;
    
    std::cout << "Age map:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    // Set usage
    std::set<int> unique_numbers = {1, 2, 2, 3, 3, 3, 4, 5, 5, 5};
    std::cout << "Unique numbers: ";
    print_container(unique_numbers);
    
    // 4. Memory Management and Smart Pointers
    std::cout << "\n4. MEMORY MANAGEMENT AND SMART POINTERS:" << std::endl;
    
    class Resource {
    public:
        Resource(int id) : id_(id) {
            std::cout << "  Resource " << id_ << " created" << std::endl;
        }
        
        ~Resource() {
            std::cout << "  Resource " << id_ << " destroyed" << std::endl;
        }
        
        int getId() const { return id_; }
        
        void doWork() {
            std::cout << "  Resource " << id_ << " is working" << std::endl;
        }
        
    private:
        int id_;
    };
    
    // unique_ptr
    std::cout << "Using unique_ptr:" << std::endl;
    auto resource1 = std::make_unique<Resource>(1);
    resource1->doWork();
    
    // shared_ptr
    std::cout << "Using shared_ptr:" << std::endl;
    auto resource2 = std::make_shared<Resource>(2);
    resource2->doWork();
    
    // weak_ptr
    std::cout << "Using weak_ptr:" << std::endl;
    std::weak_ptr<Resource> weak_resource = resource2;
    if (auto locked = weak_resource.lock()) {
        std::cout << "  Weak pointer locked, ID: " << locked->getId() << std::endl;
    }
    
    // 5. Modern C++ Features
    std::cout << "\n5. MODERN C++ FEATURES:" << std::endl;
    
    // C++11: auto and lambda
    std::cout << "C++11 features (auto and lambda):" << std::endl;
    std::vector<int> values = {1, 2, 3, 4, 5};
    
    auto square = [](int x) { return x * x; };
    std::vector<int> squared_values(values.size());
    std::transform(values.begin(), values.end(), squared_values.begin(), square);
    
    std::cout << "  Original values: ";
    print_container(values);
    std::cout << "  Squared values: ";
    print_container(squared_values);
    
    // C++17: structured bindings
    std::cout << "C++17 features (structured bindings):" << std::endl;
    std::map<std::string, int> data = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 35}};
    for (const auto& [name, age] : data) {
        std::cout << "  " << name << ": " << age << std::endl;
    }
    
    // C++17: if constexpr
    std::cout << "C++17 features (if constexpr):" << std::endl;
    auto process = [](auto value) {
        if constexpr (std::is_integral_v<decltype(value)>) {
            std::cout << "  Integer: " << value << std::endl;
        } else if constexpr (std::is_floating_point_v<decltype(value)>) {
            std::cout << "  Floating point: " << value << std::endl;
        } else {
            std::cout << "  Other type: " << value << std::endl;
        }
    };
    
    process(42);
    process(3.14);
    process(std::string("hello"));
    
    // 6. Exception Handling
    std::cout << "\n6. EXCEPTION HANDLING:" << std::endl;
    
    auto divide = [](double a, double b) -> double {
        if (b == 0) {
            throw std::runtime_error("Division by zero!");
        }
        return a / b;
    };
    
    try {
        double result1 = divide(10.0, 2.0);
        std::cout << "10.0 / 2.0 = " << result1 << std::endl;
        
        double result2 = divide(10.0, 0.0);  // This will throw an exception
        std::cout << "This won't be printed" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
    
    // 7. Function Objects and Algorithms
    std::cout << "\n7. FUNCTION OBJECTS AND ALGORITHMS:" << std::endl;
    
    std::vector<int> test_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Count even numbers
    int even_count = std::count_if(test_numbers.begin(), test_numbers.end(),
                                   [](int x) { return x % 2 == 0; });
    std::cout << "Even numbers count: " << even_count << std::endl;
    
    // Find first number greater than 5
    auto greater_than_5 = std::find_if(test_numbers.begin(), test_numbers.end(),
                                       [](int x) { return x > 5; });
    if (greater_than_5 != test_numbers.end()) {
        std::cout << "First number greater than 5: " << *greater_than_5 << std::endl;
    }
    
    // Accumulate sum
    int sum = std::accumulate(test_numbers.begin(), test_numbers.end(), 0);
    std::cout << "Sum of all numbers: " << sum << std::endl;
    
    // 8. Optional (C++17)
    std::cout << "\n8. OPTIONAL (C++17):" << std::endl;
    
    auto safe_divide = [](double a, double b) -> std::optional<double> {
        if (b == 0) {
            return std::nullopt;
        }
        return a / b;
    };
    
    auto result1 = safe_divide(10.0, 2.0);
    if (result1) {
        std::cout << "10.0 / 2.0 = " << *result1 << std::endl;
    }
    
    auto result2 = safe_divide(10.0, 0.0);
    if (result2) {
        std::cout << "This won't be printed" << std::endl;
    } else {
        std::cout << "Division by zero - no result" << std::endl;
    }
    
    // 9. RAII (Resource Acquisition Is Initialization)
    std::cout << "\n9. RAII (RESOURCE ACQUISITION IS INITIALIZATION):" << std::endl;
    
    class FileManager {
    private:
        std::string filename;
    public:
        FileManager(const std::string& name) : filename(name) {
            std::cout << "  Opening file: " << filename << std::endl;
        }
        
        ~FileManager() {
            std::cout << "  Closing file: " << filename << std::endl;
        }
        
        void write(const std::string& data) {
            std::cout << "  Writing to file: " << data << std::endl;
        }
    };
    
    {
        FileManager file("data.txt");
        file.write("Hello, World!");
        // File automatically closed when file goes out of scope
    }
    std::cout << "  File automatically closed" << std::endl;
    
    // 10. Move Semantics (Basic)
    std::cout << "\n10. MOVE SEMANTICS (BASIC):" << std::endl;
    
    class MovableClass {
    private:
        std::vector<int> data;
    public:
        MovableClass(size_t size) : data(size) {
            std::iota(data.begin(), data.end(), 0);
            std::cout << "  Created MovableClass with " << size << " elements" << std::endl;
        }
        
        MovableClass(const MovableClass& other) : data(other.data) {
            std::cout << "  Copy constructor called" << std::endl;
        }
        
        MovableClass(MovableClass&& other) noexcept : data(std::move(other.data)) {
            std::cout << "  Move constructor called" << std::endl;
        }
        
        MovableClass& operator=(const MovableClass& other) {
            if (this != &other) {
                data = other.data;
                std::cout << "  Copy assignment called" << std::endl;
            }
            return *this;
        }
        
        MovableClass& operator=(MovableClass&& other) noexcept {
            if (this != &other) {
                data = std::move(other.data);
                std::cout << "  Move assignment called" << std::endl;
            }
            return *this;
        }
        
        size_t size() const { return data.size(); }
    };
    
    MovableClass obj1(1000);
    MovableClass obj2 = std::move(obj1);  // Move constructor
    MovableClass obj3(500);
    obj3 = std::move(obj2);  // Move assignment
    
    std::cout << "  Final object size: " << obj3.size() << std::endl;
    
    std::cout << "\n=== End of Chapter 4 Tour ===" << std::endl;
    return 0;
}
