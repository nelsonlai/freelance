/*
 * Lesson 08.2: Exception Handling Basics
 * 
 * This file demonstrates try-catch blocks, exception types, raii with exceptions
 */

#include <iostream>
#include <string>
#include <vector>

// Example class demonstrating concepts
class ExampleClass {
private:
    std::string name;
    int value;
    
public:
    // Constructor
    ExampleClass(const std::string& n, int v) : name(n), value(v) {
        std::cout << "ExampleClass created: " << name << std::endl;
    }
    
    // Destructor
    ~ExampleClass() {
        std::cout << "ExampleClass destroyed: " << name << std::endl;
    }
    
    // Member functions
    void displayInfo() const {
        std::cout << "Name: " << name << ", Value: " << value << std::endl;
    }
    
    void setName(const std::string& n) { name = n; }
    void setValue(int v) { value = v; }
    
    const std::string& getName() const { return name; }
    int getValue() const { return value; }
};

// Function to demonstrate basic concepts
void demonstrateBasicConcepts() {
    std::cout << "=== Basic Concepts Demo ===" << std::endl;
    
    ExampleClass obj("Test Object", 42);
    obj.displayInfo();
    
    obj.setValue(100);
    obj.displayInfo();
}

// Function to demonstrate advanced features
void demonstrateAdvancedFeatures() {
    std::cout << "\n=== Advanced Features Demo ===" << std::endl;
    
    std::vector<ExampleClass> objects;
    objects.emplace_back("Object 1", 10);
    objects.emplace_back("Object 2", 20);
    objects.emplace_back("Object 3", 30);
    
    for (const auto& obj : objects) {
        obj.displayInfo();
    }
}

int main() {
    std::cout << "=== C++ Exception Handling Basics Demo ===" << std::endl;
    std::cout << "This program demonstrates try-catch blocks, exception types, raii with exceptions.\n" << std::endl;
    
    // Demonstrate various concepts
    demonstrateBasicConcepts();
    demonstrateAdvancedFeatures();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Core concepts and principles" << std::endl;
    std::cout << "2. Implementation techniques" << std::endl;
    std::cout << "3. Best practices and patterns" << std::endl;
    std::cout << "4. Performance considerations" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o 08_2 08_2_Exception_Handling_Basics.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o 08_2 08_2_Exception_Handling_Basics.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 08_2_Exception_Handling_Basics.cpp
 * 
 * Running:
 * ./08_2 (Linux/macOS)
 * 08_2.exe (Windows)
 */
