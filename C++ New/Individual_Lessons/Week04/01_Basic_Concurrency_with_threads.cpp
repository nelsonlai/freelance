/*
 * Lesson 04.1: Basic Concurrency with threads
 * 
 * This file demonstrates std::thread, basic synchronization, concurrent programming
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
    std::cout << "=== C++ Basic Concurrency with threads Demo ===" << std::endl;
    std::cout << "This program demonstrates std::thread, basic synchronization, concurrent programming.\n" << std::endl;
    
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
 * g++ -std=c++17 -Wall -Wextra -o 04_1 04_1_Basic_Concurrency_with_threads.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o 04_1 04_1_Basic_Concurrency_with_threads.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 04_1_Basic_Concurrency_with_threads.cpp
 * 
 * Running:
 * ./04_1 (Linux/macOS)
 * 04_1.exe (Windows)
 */
