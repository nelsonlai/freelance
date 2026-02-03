/*
 * Lesson 9.1: Exception Handling
 * 
 * This file demonstrates exception throwing, catching,
 * custom exceptions, and exception safety.
 */

#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Custom exception classes
class DivisionByZeroError : public std::runtime_error {
public:
    DivisionByZeroError() : std::runtime_error("Division by zero") {}
};

class FileNotFoundError : public std::runtime_error {
private:
    std::string filename_;
public:
    FileNotFoundError(const std::string& filename) 
        : std::runtime_error("File not found: " + filename), filename_(filename) {}
    
    const std::string& getFilename() const { return filename_; }
};

class ValidationError : public std::logic_error {
private:
    std::string field_name_;
    std::string value_;
public:
    ValidationError(const std::string& field, const std::string& value)
        : std::logic_error("Validation failed for " + field + ": " + value),
          field_name_(field), value_(value) {}
    
    const std::string& getFieldName() const { return field_name_; }
    const std::string& getValue() const { return value_; }
};

// Exception-safe resource class
class SafeResource {
private:
    std::unique_ptr<int[]> data_;
    size_t size_;
    
public:
    SafeResource(size_t size) : size_(size) {
        if (size == 0) {
            throw std::invalid_argument("Size must be greater than 0");
        }
        data_ = std::make_unique<int[]>(size);
        std::cout << "Resource allocated with size " << size << std::endl;
    }
    
    ~SafeResource() {
        std::cout << "Resource deallocated" << std::endl;
    }
    
    // Copy constructor (deleted for simplicity)
    SafeResource(const SafeResource&) = delete;
    SafeResource& operator=(const SafeResource&) = delete;
    
    // Move constructor
    SafeResource(SafeResource&& other) noexcept 
        : data_(std::move(other.data_)), size_(other.size_) {
        other.size_ = 0;
    }
    
    // Move assignment
    SafeResource& operator=(SafeResource&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    int& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const int& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const { return size_; }
};

// Function to demonstrate basic exception handling
void demonstrateBasicExceptions() {
    std::cout << "=== Basic Exception Handling ===" << std::endl;
    
    // Function that throws exceptions
    auto risky_function = [](int value) -> double {
        if (value < 0) {
            throw std::invalid_argument("Value must be non-negative");
        }
        if (value > 100) {
            throw std::out_of_range("Value must be <= 100");
        }
        return static_cast<double>(value) / 2.0;
    };
    
    // Test with valid input
    try {
        double result = risky_function(50);
        std::cout << "risky_function(50) = " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Test with invalid input
    try {
        double result = risky_function(-5);
        std::cout << "risky_function(-5) = " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught invalid_argument: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Test with out of range input
    try {
        double result = risky_function(150);
        std::cout << "risky_function(150) = " << result << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught out_of_range: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Function to demonstrate custom exceptions
void demonstrateCustomExceptions() {
    std::cout << "\n=== Custom Exceptions ===" << std::endl;
    
    // Division function with custom exception
    auto safe_divide = [](double a, double b) -> double {
        if (b == 0) {
            throw DivisionByZeroError();
        }
        return a / b;
    };
    
    // Test division
    try {
        double result = safe_divide(10.0, 2.0);
        std::cout << "10.0 / 2.0 = " << result << std::endl;
        
        result = safe_divide(10.0, 0.0);  // This will throw
        std::cout << "10.0 / 0.0 = " << result << std::endl;
    } catch (const DivisionByZeroError& e) {
        std::cout << "Caught DivisionByZeroError: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // File operation with custom exception
    auto read_file = [](const std::string& filename) -> std::string {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw FileNotFoundError(filename);
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    };
    
    // Test file reading
    try {
        std::string content = read_file("nonexistent.txt");
        std::cout << "File content: " << content << std::endl;
    } catch (const FileNotFoundError& e) {
        std::cout << "Caught FileNotFoundError: " << e.what() << std::endl;
        std::cout << "Filename: " << e.getFilename() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Function to demonstrate exception propagation
void demonstrateExceptionPropagation() {
    std::cout << "\n=== Exception Propagation ===" << std::endl;
    
    // Function that throws
    auto function_a = []() {
        std::cout << "In function_a" << std::endl;
        throw std::runtime_error("Error in function_a");
    };
    
    // Function that calls function_a
    auto function_b = []() {
        std::cout << "In function_b" << std::endl;
        function_a();
        std::cout << "This won't be printed" << std::endl;
    };
    
    // Function that calls function_b
    auto function_c = []() {
        std::cout << "In function_c" << std::endl;
        function_b();
        std::cout << "This won't be printed" << std::endl;
    };
    
    // Catch exception at top level
    try {
        function_c();
    } catch (const std::exception& e) {
        std::cout << "Caught at top level: " << e.what() << std::endl;
    }
}

// Function to demonstrate exception safety
void demonstrateExceptionSafety() {
    std::cout << "\n=== Exception Safety ===" << std::endl;
    
    // Exception-safe resource management
    try {
        SafeResource resource(5);
        
        // Initialize resource
        for (size_t i = 0; i < resource.size(); ++i) {
            resource[i] = static_cast<int>(i * 10);
        }
        
        std::cout << "Resource initialized:" << std::endl;
        for (size_t i = 0; i < resource.size(); ++i) {
            std::cout << "resource[" << i << "] = " << resource[i] << std::endl;
        }
        
        // This will throw an exception
        resource[10] = 100;  // Out of range
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        std::cout << "Resource was automatically cleaned up" << std::endl;
    }
    
    // Demonstrate move semantics with exceptions
    try {
        SafeResource resource1(3);
        SafeResource resource2 = std::move(resource1);
        
        std::cout << "resource2 size: " << resource2.size() << std::endl;
        std::cout << "resource1 size after move: " << resource1.size() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Function to demonstrate noexcept specifications
void demonstrateNoexceptSpecifications() {
    std::cout << "\n=== Noexcept Specifications ===" << std::endl;
    
    // Function that never throws
    auto safe_function = []() noexcept {
        std::cout << "This function never throws" << std::endl;
        return 42;
    };
    
    // Function that might throw
    auto risky_function = []() {
        std::cout << "This function might throw" << std::endl;
        throw std::runtime_error("Something went wrong");
    };
    
    // Conditional noexcept
    auto conditional_noexcept = []() noexcept(std::is_nothrow_copy_constructible_v<int>) {
        std::cout << "This function is conditionally noexcept" << std::endl;
        return 100;
    };
    
    try {
        int result1 = safe_function();
        std::cout << "safe_function() = " << result1 << std::endl;
        
        int result2 = conditional_noexcept();
        std::cout << "conditional_noexcept() = " << result2 << std::endl;
        
        risky_function();
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Function to demonstrate exception handling patterns
void demonstrateExceptionPatterns() {
    std::cout << "\n=== Exception Handling Patterns ===" << std::endl;
    
    // Pattern 1: Resource acquisition with exception safety
    auto acquire_resource = [](const std::string& resource_name) -> std::unique_ptr<std::string> {
        std::cout << "Acquiring resource: " << resource_name << std::endl;
        if (resource_name.empty()) {
            throw std::invalid_argument("Resource name cannot be empty");
        }
        return std::make_unique<std::string>(resource_name);
    };
    
    // Pattern 2: Exception-safe operations
    auto safe_operation = [](const std::vector<int>& input) -> std::vector<int> {
        std::vector<int> result;
        result.reserve(input.size());
        
        for (const auto& value : input) {
            if (value < 0) {
                throw std::invalid_argument("Negative values not allowed");
            }
            result.push_back(value * 2);
        }
        
        return result;
    };
    
    // Pattern 3: Exception handling with cleanup
    auto operation_with_cleanup = []() {
        std::cout << "Starting operation with cleanup" << std::endl;
        
        try {
            // Simulate some work that might fail
            throw std::runtime_error("Operation failed");
        } catch (...) {
            std::cout << "Cleaning up after exception" << std::endl;
            throw;  // Re-throw the exception
        }
    };
    
    // Test patterns
    try {
        auto resource = acquire_resource("test_resource");
        std::cout << "Resource acquired: " << *resource << std::endl;
        
        std::vector<int> input = {1, 2, 3, 4, 5};
        auto result = safe_operation(input);
        
        std::cout << "Safe operation result: ";
        for (const auto& value : result) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Test cleanup pattern
    try {
        operation_with_cleanup();
    } catch (const std::exception& e) {
        std::cout << "Caught exception after cleanup: " << e.what() << std::endl;
    }
}

// Function to demonstrate exception handling with containers
void demonstrateExceptionWithContainers() {
    std::cout << "\n=== Exception Handling with Containers ===" << std::endl;
    
    // Exception-safe container operations
    std::vector<std::unique_ptr<SafeResource>> resources;
    
    try {
        // Add resources
        resources.push_back(std::make_unique<SafeResource>(2));
        resources.push_back(std::make_unique<SafeResource>(3));
        resources.push_back(std::make_unique<SafeResource>(4));
        
        std::cout << "Added " << resources.size() << " resources" << std::endl;
        
        // Simulate an exception during resource creation
        resources.push_back(std::make_unique<SafeResource>(0));  // This will throw
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        std::cout << "Resources before exception: " << resources.size() << std::endl;
    }
    
    // Resources are automatically cleaned up
    std::cout << "All resources cleaned up automatically" << std::endl;
}

// Function to demonstrate exception handling best practices
void demonstrateExceptionBestPractices() {
    std::cout << "\n=== Exception Handling Best Practices ===" << std::endl;
    
    // Best practice 1: Catch by const reference
    try {
        throw std::runtime_error("Test exception");
    } catch (const std::runtime_error& e) {  // Good: catch by const reference
        std::cout << "Caught by const reference: " << e.what() << std::endl;
    }
    
    // Best practice 2: Specific exception handling
    try {
        throw std::invalid_argument("Invalid argument");
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught specific exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught general exception: " << e.what() << std::endl;
    }
    
    // Best practice 3: RAII for automatic cleanup
    {
        SafeResource resource(2);
        resource[0] = 10;
        resource[1] = 20;
        std::cout << "Resource will be automatically cleaned up" << std::endl;
    }
    
    // Best practice 4: Use smart pointers for exception safety
    auto create_resource = []() -> std::unique_ptr<SafeResource> {
        return std::make_unique<SafeResource>(3);
    };
    
    try {
        auto resource = create_resource();
        std::cout << "Resource created with smart pointer" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Exception Handling Demonstration ===" << std::endl;
    std::cout << "This program demonstrates exception throwing, catching,\n"
              << "custom exceptions, and exception safety.\n" << std::endl;
    
    // Demonstrate various exception concepts
    demonstrateBasicExceptions();
    demonstrateCustomExceptions();
    demonstrateExceptionPropagation();
    demonstrateExceptionSafety();
    demonstrateNoexceptSpecifications();
    demonstrateExceptionPatterns();
    demonstrateExceptionWithContainers();
    demonstrateExceptionBestPractices();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Exceptions provide a mechanism for error handling" << std::endl;
    std::cout << "2. Custom exceptions should inherit from standard exception classes" << std::endl;
    std::cout << "3. RAII ensures automatic cleanup when exceptions occur" << std::endl;
    std::cout << "4. Exception safety has different levels of guarantees" << std::endl;
    std::cout << "5. noexcept specifications indicate functions that don't throw" << std::endl;
    std::cout << "6. Catch exceptions by const reference for efficiency" << std::endl;
    std::cout << "7. Use smart pointers for exception-safe resource management" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o exception_handling 01_Exception_Handling.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o exception_handling 01_Exception_Handling.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Exception_Handling.cpp
 * 
 * Running:
 * ./exception_handling (Linux/macOS)
 * exception_handling.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best exception handling support.
 * 
 * Exception Notes:
 * - Use exceptions for error handling, not control flow
 * - Catch exceptions by const reference
 * - Use RAII for automatic resource cleanup
 * - Design for exception safety
 * - Use noexcept specifications appropriately
 * - Prefer smart pointers for exception safety
 */"""
