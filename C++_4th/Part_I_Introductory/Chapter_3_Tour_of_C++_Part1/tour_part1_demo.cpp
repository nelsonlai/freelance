#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Demonstrates basic C++ features - Part 1 of the tour
int main() {
    std::cout << "=== Chapter 3: A Tour of C++ (Part 1) ===" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // 1. Hello, World! and Basic I/O
    std::cout << "\n1. HELLO, WORLD! AND BASIC I/O:" << std::endl;
    
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Welcome to C++ programming!" << std::endl;
    
    // Basic input/output
    std::string name;
    int age;
    
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Please enter your age: ";
    std::cin >> age;
    
    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;
    
    // 2. Types and Variables
    std::cout << "\n2. TYPES AND VARIABLES:" << std::endl;
    
    // Fundamental types
    int integer_var = 42;
    double double_var = 3.14159;
    char char_var = 'A';
    bool bool_var = true;
    std::string string_var = "Hello, C++!";
    
    std::cout << "Integer: " << integer_var << std::endl;
    std::cout << "Double: " << double_var << std::endl;
    std::cout << "Character: " << char_var << std::endl;
    std::cout << "Boolean: " << std::boolalpha << bool_var << std::endl;
    std::cout << "String: " << string_var << std::endl;
    
    // Constants
    const int MAX_SIZE = 100;
    constexpr double PI = 3.14159265359;
    
    std::cout << "Constant integer: " << MAX_SIZE << std::endl;
    std::cout << "Constexpr double: " << PI << std::endl;
    
    // Type inference with auto
    auto inferred_int = 42;
    auto inferred_double = 3.14;
    auto inferred_string = std::string("Auto string");
    
    std::cout << "Auto int: " << inferred_int << std::endl;
    std::cout << "Auto double: " << inferred_double << std::endl;
    std::cout << "Auto string: " << inferred_string << std::endl;
    
    // 3. Control Structures
    std::cout << "\n3. CONTROL STRUCTURES:" << std::endl;
    
    // Conditional statements
    int number = 15;
    
    if (number > 10) {
        std::cout << number << " is greater than 10" << std::endl;
    } else if (number > 5) {
        std::cout << number << " is greater than 5 but not greater than 10" << std::endl;
    } else {
        std::cout << number << " is 5 or less" << std::endl;
    }
    
    // Switch statement
    char grade = 'B';
    switch (grade) {
        case 'A':
            std::cout << "Excellent!" << std::endl;
            break;
        case 'B':
            std::cout << "Good!" << std::endl;
            break;
        case 'C':
            std::cout << "Average" << std::endl;
            break;
        default:
            std::cout << "Needs improvement" << std::endl;
            break;
    }
    
    // Loops
    std::cout << "\nFor loop (1 to 5): ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "While loop (countdown from 3): ";
    int count = 3;
    while (count > 0) {
        std::cout << count << " ";
        count--;
    }
    std::cout << "Blast off!" << std::endl;
    
    // Range-based for loop
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Range-based for loop: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 4. Functions
    std::cout << "\n4. FUNCTIONS:" << std::endl;
    
    // Function definitions
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    
    auto multiply = [](double x, double y) -> double {
        return x * y;
    };
    
    auto greet = [](const std::string& name) -> void {
        std::cout << "Hello, " << name << "!" << std::endl;
    };
    
    // Function calls
    int sum = add(10, 20);
    std::cout << "10 + 20 = " << sum << std::endl;
    
    double product = multiply(2.5, 4.0);
    std::cout << "2.5 * 4.0 = " << product << std::endl;
    
    greet("C++ Programmer");
    
    // 5. Simple Classes and Objects
    std::cout << "\n5. SIMPLE CLASSES AND OBJECTS:" << std::endl;
    
    // Simple class definition
    class Rectangle {
    private:
        double width;
        double height;
        
    public:
        // Constructor
        Rectangle(double w, double h) : width(w), height(h) {}
        
        // Member functions
        double area() const {
            return width * height;
        }
        
        double perimeter() const {
            return 2 * (width + height);
        }
        
        void display() const {
            std::cout << "Rectangle: " << width << " x " << height 
                      << " (area: " << area() << ", perimeter: " << perimeter() << ")" << std::endl;
        }
    };
    
    // Create objects
    Rectangle rect1(5.0, 3.0);
    Rectangle rect2(4.0, 4.0);
    
    rect1.display();
    rect2.display();
    
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
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // 7. Standard Library Introduction
    std::cout << "\n7. STANDARD LIBRARY INTRODUCTION:" << std::endl;
    
    // Vector usage
    std::vector<std::string> fruits = {"apple", "banana", "orange", "grape"};
    
    std::cout << "Fruits: ";
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;
    
    // Algorithm usage
    std::sort(fruits.begin(), fruits.end());
    std::cout << "Sorted fruits: ";
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;
    
    // 8. Pointers and References (Basic)
    std::cout << "\n8. POINTERS AND REFERENCES (BASIC):" << std::endl;
    
    int value = 42;
    int* ptr = &value;        // Pointer to value
    int& ref = value;         // Reference to value
    
    std::cout << "Original value: " << value << std::endl;
    std::cout << "Pointer value: " << *ptr << std::endl;
    std::cout << "Reference value: " << ref << std::endl;
    
    // Modify through pointer and reference
    *ptr = 100;
    std::cout << "After modifying through pointer: " << value << std::endl;
    
    ref = 200;
    std::cout << "After modifying through reference: " << value << std::endl;
    
    // 9. Arrays and Vectors
    std::cout << "\n9. ARRAYS AND VECTORS:" << std::endl;
    
    // Traditional array
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << "Array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Vector (dynamic array)
    std::vector<int> vec = {10, 20, 30, 40, 50};
    std::cout << "Vector: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // Vector operations
    vec.push_back(60);
    std::cout << "After push_back: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // 10. String Operations
    std::cout << "\n10. STRING OPERATIONS:" << std::endl;
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    
    // String concatenation
    std::string combined = str1 + ", " + str2 + "!";
    std::cout << "Combined string: " << combined << std::endl;
    
    // String methods
    std::cout << "String length: " << combined.length() << std::endl;
    std::cout << "Substring (0, 5): " << combined.substr(0, 5) << std::endl;
    
    // String comparison
    if (str1 == "Hello") {
        std::cout << "String comparison works!" << std::endl;
    }
    
    std::cout << "\n=== End of Chapter 3 Tour ===" << std::endl;
    return 0;
}
