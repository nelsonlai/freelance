/*
 * Lesson 1.1: C++ Philosophy and Modern Programming
 * 
 * This file demonstrates basic C++ concepts and modern features
 * to help students understand C++ philosophy and capabilities.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Function to demonstrate zero-cost abstractions
void demonstrateZeroCostAbstractions() {
    std::cout << "=== Zero-Cost Abstractions Demo ===" << std::endl;
    
    // High-level STL container with no runtime overhead
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Modern range-based for loop (C++11)
    std::cout << "Numbers using range-based for loop: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // This is as efficient as a traditional C-style loop
    std::cout << "Numbers using traditional loop: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate RAII (Resource Acquisition Is Initialization)
void demonstrateRAII() {
    std::cout << "\n=== RAII Demo ===" << std::endl;
    
    // Smart pointer automatically manages memory
    auto smartPtr = std::make_unique<std::string>("Hello, RAII!");
    std::cout << "Smart pointer value: " << *smartPtr << std::endl;
    
    // Memory automatically freed when smartPtr goes out of scope
    std::cout << "Smart pointer will automatically clean up memory" << std::endl;
}

// Function to demonstrate modern C++ features
void demonstrateModernFeatures() {
    std::cout << "\n=== Modern C++ Features Demo ===" << std::endl;
    
    // Auto keyword for type deduction (C++11)
    auto name = std::string("Modern C++");
    auto year = 2024;
    auto pi = 3.14159;
    
    std::cout << "Name: " << name << " (type: std::string)" << std::endl;
    std::cout << "Year: " << year << " (type: int)" << std::endl;
    std::cout << "PI: " << pi << " (type: double)" << std::endl;
    
    // Lambda expressions (C++11)
    auto square = [](int x) { return x * x; };
    std::cout << "Square of 5: " << square(5) << std::endl;
    
    // Initializer lists (C++11)
    std::vector<std::string> languages = {"C++", "Python", "Java", "Rust"};
    std::cout << "Programming languages: ";
    for (const auto& lang : languages) {
        std::cout << lang << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate type safety
void demonstrateTypeSafety() {
    std::cout << "\n=== Type Safety Demo ===" << std::endl;
    
    // Strong typing prevents many errors
    int integer = 42;
    double floating = 3.14;
    std::string text = "Hello";
    
    // This would cause a compilation error (uncomment to see):
    // integer = text;  // Error: cannot convert std::string to int
    
    std::cout << "Integer: " << integer << std::endl;
    std::cout << "Floating point: " << floating << std::endl;
    std::cout << "Text: " << text << std::endl;
    
    // Explicit conversion when needed
    int converted = static_cast<int>(floating);
    std::cout << "Converted float to int: " << converted << std::endl;
}

// Function to demonstrate performance characteristics
void demonstratePerformance() {
    std::cout << "\n=== Performance Demo ===" << std::endl;
    
    // C++ allows fine control over performance
    const size_t size = 1000000;
    
    // Allocate array on stack (fast)
    std::vector<int> stackVector(size);
    
    // Allocate array on heap (flexible)
    auto heapArray = std::make_unique<int[]>(size);
    
    std::cout << "Allocated " << size << " integers on stack and heap" << std::endl;
    std::cout << "C++ gives you control over memory allocation strategy" << std::endl;
    
    // Both automatically cleaned up (RAII)
}

// Main function demonstrating C++ program structure
int main() {
    std::cout << "Welcome to C++ Programming!" << std::endl;
    std::cout << "This program demonstrates C++ philosophy and modern features.\n" << std::endl;
    
    // Demonstrate various C++ concepts
    demonstrateZeroCostAbstractions();
    demonstrateRAII();
    demonstrateModernFeatures();
    demonstrateTypeSafety();
    demonstratePerformance();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. C++ provides high-level abstractions with zero runtime cost" << std::endl;
    std::cout << "2. RAII ensures automatic resource management" << std::endl;
    std::cout << "3. Modern C++ features make code more expressive and safe" << std::endl;
    std::cout << "4. Strong typing helps catch errors at compile time" << std::endl;
    std::cout << "5. C++ gives you control over performance when needed" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o cpp_philosophy 01_C++_Philosophy_and_Modern_Programming.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o cpp_philosophy 01_C++_Philosophy_and_Modern_Programming.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 01_C++_Philosophy_and_Modern_Programming.cpp
 * 
 * Running:
 * ./cpp_philosophy (Linux/macOS)
 * cpp_philosophy.exe (Windows)
 */
