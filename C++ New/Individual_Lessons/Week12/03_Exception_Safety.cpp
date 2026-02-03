/*
 * Lesson 12.3: Exception Safety
 * 
 * This file demonstrates advanced C++ concepts including
 * exception safety guarantees, raii with exceptions
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

// Advanced class demonstrating professional patterns
class AdvancedExample {
private:
    std::unique_ptr<std::vector<int>> data;
    std::string name;
    
public:
    // Advanced constructor with initialization
    explicit AdvancedExample(const std::string& n) 
        : data(std::make_unique<std::vector<int>>()), name(n) {
        std::cout << "Advanced example created: " << name << std::endl;
    }
    
    // Copy constructor (deep copy)
    AdvancedExample(const AdvancedExample& other) 
        : data(std::make_unique<std::vector<int>>(*other.data)), name(other.name) {
        std::cout << "Advanced example copied: " << name << std::endl;
    }
    
    // Move constructor
    AdvancedExample(AdvancedExample&& other) noexcept 
        : data(std::move(other.data)), name(std::move(other.name)) {
        std::cout << "Advanced example moved: " << name << std::endl;
    }
    
    // Destructor
    ~AdvancedExample() {
        std::cout << "Advanced example destroyed: " << name << std::endl;
    }
    
    // Assignment operator
    AdvancedExample& operator=(const AdvancedExample& other) {
        if (this != &other) {
            *data = *other.data;
            name = other.name;
        }
        return *this;
    }
    
    // Move assignment operator
    AdvancedExample& operator=(AdvancedExample&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            name = std::move(other.name);
        }
        return *this;
    }
    
    // Advanced member functions
    void addData(int value) {
        data->push_back(value);
        std::cout << "Added value " << value << " to " << name << std::endl;
    }
    
    void processData() {
        std::cout << "Processing data for " << name << ":" << std::endl;
        for (const auto& value : *data) {
            std::cout << "  " << value << std::endl;
        }
    }
    
    void sortData() {
        std::sort(data->begin(), data->end());
        std::cout << "Data sorted for " << name << std::endl;
    }
    
    size_t getDataSize() const {
        return data->size();
    }
    
    const std::string& getName() const {
        return name;
    }
};

// Function to demonstrate advanced concepts
void demonstrateAdvancedConcepts() {
    std::cout << "=== Advanced Concepts Demo ===" << std::endl;
    
    AdvancedExample example1("Example 1");
    example1.addData(42);
    example1.addData(17);
    example1.addData(99);
    example1.processData();
    
    AdvancedExample example2("Example 2");
    example2.addData(100);
    example2.addData(50);
    example2.processData();
}

// Function to demonstrate professional patterns
void demonstrateProfessionalPatterns() {
    std::cout << "\n=== Professional Patterns Demo ===" << std::endl;
    
    // RAII with smart pointers
    auto smartPtr = std::make_unique<AdvancedExample>("Smart Pointer Example");
    smartPtr->addData(200);
    smartPtr->processData();
    
    // Move semantics
    AdvancedExample movedExample = std::move(*smartPtr);
    movedExample.processData();
    
    // STL algorithms
    std::vector<int> numbers = {1, 5, 3, 9, 2, 8, 4};
    std::cout << "Original numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    auto evenCount = std::count_if(numbers.begin(), numbers.end(), 
                                  [](int n) { return n % 2 == 0; });
    std::cout << "Even numbers count: " << evenCount << std::endl;
}

// Function to demonstrate performance considerations
void demonstratePerformanceConsiderations() {
    std::cout << "\n=== Performance Considerations Demo ===" << std::endl;
    
    // Reserve space to avoid reallocations
    std::vector<int> optimizedVector;
    optimizedVector.reserve(1000);
    
    std::cout << "Adding 1000 elements with reserve..." << std::endl;
    for (int i = 0; i < 1000; ++i) {
        optimizedVector.push_back(i);
    }
    
    std::cout << "Vector size: " << optimizedVector.size() << std::endl;
    std::cout << "Vector capacity: " << optimizedVector.capacity() << std::endl;
}

// Function to demonstrate error handling
void demonstrateErrorHandling() {
    std::cout << "\n=== Error Handling Demo ===" << std::endl;
    
    try {
        // Simulate some operation that might fail
        std::vector<int> testVector;
        if (testVector.empty()) {
            throw std::runtime_error("Vector is empty!");
        }
        
        int value = testVector.at(0);  // This would throw
        std::cout << "Value: " << value << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Template function demonstrating generic programming
template<typename Container>
void processContainer(const Container& container, const std::string& name) {
    std::cout << "\nProcessing " << name << ":" << std::endl;
    std::cout << "Size: " << container.size() << std::endl;
    
    // Use range-based for loop
    for (const auto& element : container) {
        std::cout << "  " << element << std::endl;
    }
}

// Function to demonstrate template usage
void demonstrateTemplateUsage() {
    std::cout << "\n=== Template Usage Demo ===" << std::endl;
    
    std::vector<int> intVector = {1, 2, 3, 4, 5};
    std::vector<std::string> stringVector = {"Hello", "World", "C++"};
    
    processContainer(intVector, "Integer Vector");
    processContainer(stringVector, "String Vector");
}

int main() {
    std::cout << "=== Advanced C++ Exception Safety Demo ===" << std::endl;
    std::cout << "This program demonstrates advanced C++ concepts.\n" << std::endl;
    
    // Demonstrate various advanced concepts
    demonstrateAdvancedConcepts();
    demonstrateProfessionalPatterns();
    demonstratePerformanceConsiderations();
    demonstrateErrorHandling();
    demonstrateTemplateUsage();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Advanced C++ concepts and techniques" << std::endl;
    std::cout << "2. Professional coding patterns and practices" << std::endl;
    std::cout << "3. Performance optimization strategies" << std::endl;
    std::cout << "4. Error handling and safety considerations" << std::endl;
    std::cout << "5. Template programming and generic design" << std::endl;
    std::cout << "6. Modern C++ features and best practices" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o advanced_demo 12_3_Exception_Safety.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o advanced_demo 12_3_Exception_Safety.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 12_3_Exception_Safety.cpp
 * 
 * Running:
 * ./advanced_demo (Linux/macOS)
 * advanced_demo.exe (Windows)
 * 
 * Note: This is an advanced lesson requiring modern C++ compiler support.
 * Ensure your compiler supports C++17 features.
 */
