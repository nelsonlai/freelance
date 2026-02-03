#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>

// Demonstrates exception handling in C++
int main() {
    std::cout << "Exception Handling Demonstration" << std::endl;
    std::cout << "================================" << std::endl;
    
    // 1. Basic exception handling
    std::cout << "\n1. BASIC EXCEPTION HANDLING:" << std::endl;
    
    auto divide = [](double a, double b) -> double {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    };
    
    try {
        double result = divide(10.0, 2.0);
        std::cout << "10.0 / 2.0 = " << result << std::endl;
        
        result = divide(10.0, 0.0);  // This will throw
        std::cout << "10.0 / 0.0 = " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught runtime_error: " << e.what() << std::endl;
    }
    
    // 2. Custom exception classes
    std::cout << "\n2. CUSTOM EXCEPTION CLASSES:" << std::endl;
    
    class ValidationException : public std::runtime_error {
    public:
        ValidationException(const std::string& message) 
            : std::runtime_error("Validation error: " + message) {}
    };
    
    class NetworkException : public std::runtime_error {
    public:
        NetworkException(const std::string& message) 
            : std::runtime_error("Network error: " + message) {}
    };
    
    auto validate_input = [](const std::string& input) {
        if (input.empty()) {
            throw ValidationException("Input cannot be empty");
        }
        if (input.length() < 3) {
            throw ValidationException("Input must be at least 3 characters");
        }
    };
    
    auto connect_to_server = [](const std::string& server) {
        if (server == "invalid") {
            throw NetworkException("Cannot connect to invalid server");
        }
        std::cout << "Connected to " << server << std::endl;
    };
    
    try {
        validate_input("ab");  // This will throw
    } catch (const ValidationException& e) {
        std::cout << "Caught validation exception: " << e.what() << std::endl;
    }
    
    try {
        connect_to_server("invalid");  // This will throw
    } catch (const NetworkException& e) {
        std::cout << "Caught network exception: " << e.what() << std::endl;
    }
    
    // 3. Exception propagation
    std::cout << "\n3. EXCEPTION PROPAGATION:" << std::endl;
    
    auto function_a = []() {
        std::cout << "Function A called" << std::endl;
        throw std::runtime_error("Error in function A");
    };
    
    auto function_b = [&function_a]() {
        std::cout << "Function B called" << std::endl;
        function_a();
    };
    
    auto function_c = [&function_b]() {
        std::cout << "Function C called" << std::endl;
        function_b();
    };
    
    try {
        function_c();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught propagated exception: " << e.what() << std::endl;
    }
    
    // 4. RAII and exception safety
    std::cout << "\n4. RAII AND EXCEPTION SAFETY:" << std::endl;
    
    class FileHandler {
    private:
        std::string filename;
        bool is_open;
        
    public:
        FileHandler(const std::string& name) : filename(name), is_open(true) {
            std::cout << "File " << filename << " opened" << std::endl;
        }
        
        ~FileHandler() {
            if (is_open) {
                std::cout << "File " << filename << " closed" << std::endl;
            }
        }
        
        void close() {
            if (is_open) {
                is_open = false;
                std::cout << "File " << filename << " manually closed" << std::endl;
            }
        }
        
        void write(const std::string& data) {
            if (!is_open) {
                throw std::runtime_error("File is not open");
            }
            std::cout << "Writing to " << filename << ": " << data << std::endl;
        }
    };
    
    auto process_file = [](const std::string& filename) {
        FileHandler file(filename);  // RAII - automatic cleanup
        
        file.write("Hello, World!");
        
        if (filename == "error.txt") {
            throw std::runtime_error("Simulated error during processing");
        }
        
        file.write("Processing completed");
    };
    
    try {
        process_file("normal.txt");
        std::cout << "File processed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error processing file: " << e.what() << std::endl;
    }
    
    try {
        process_file("error.txt");  // This will throw
    } catch (const std::exception& e) {
        std::cout << "Error processing file: " << e.what() << std::endl;
    }
    
    // 5. Smart pointers and exception safety
    std::cout << "\n5. SMART POINTERS AND EXCEPTION SAFETY:" << std::endl;
    
    class Resource {
    private:
        std::string name;
        
    public:
        Resource(const std::string& name) : name(name) {
            std::cout << "Resource " << name << " created" << std::endl;
        }
        
        ~Resource() {
            std::cout << "Resource " << name << " destroyed" << std::endl;
        }
        
        void use() {
            std::cout << "Using resource " << name << std::endl;
        }
    };
    
    auto use_resources = [](const std::vector<std::string>& names) {
        std::vector<std::unique_ptr<Resource>> resources;
        
        for (const auto& name : names) {
            resources.push_back(std::make_unique<Resource>(name));
            resources.back()->use();
            
            if (name == "error") {
                throw std::runtime_error("Error using resource");
            }
        }
    };
    
    try {
        std::vector<std::string> names = {"resource1", "resource2", "resource3"};
        use_resources(names);
        std::cout << "All resources used successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error using resources: " << e.what() << std::endl;
    }
    
    try {
        std::vector<std::string> names = {"resource1", "error", "resource3"};
        use_resources(names);  // This will throw
    } catch (const std::exception& e) {
        std::cout << "Error using resources: " << e.what() << std::endl;
    }
    
    // 6. Exception specifications (noexcept)
    std::cout << "\n6. EXCEPTION SPECIFICATIONS (NOEXCEPT):" << std::endl;
    
    auto safe_function = [](int value) noexcept -> int {
        return value * 2;  // This function never throws
    };
    auto potentially_unsafe_function = [](int value) {
        if (value < 0) {
            throw std::invalid_argument("Value cannot be negative");
        }
        return value * 2;
    };
    
    try {
        int result1 = safe_function(5);
        std::cout << "Safe function result: " << result1 << std::endl;
        
        int result2 = potentially_unsafe_function(-1);  // This will throw
        std::cout << "Unsafe function result: " << result2 << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\nException handling demonstration completed!" << std::endl;
    return 0;
}
