/*
 * Lesson 9.3: Source Files and Programs
 * 
 * This file demonstrates source file organization,
 * compilation, linking, and program structure.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>

// Forward declarations (demonstrating proper header organization)
class FileManager;
class ConfigManager;
class Logger;

// Utility functions (would typically be in separate files)
namespace FileUtils {
    bool fileExists(const std::string& filename);
    std::string readFile(const std::string& filename);
    bool writeFile(const std::string& filename, const std::string& content);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
}

namespace MathUtils {
    double calculateAverage(const std::vector<double>& numbers);
    double calculateStandardDeviation(const std::vector<double>& numbers);
    int factorial(int n);
    bool isPrime(int n);
}

// Class demonstrating proper encapsulation and file organization
class Calculator {
private:
    std::string name_;
    std::vector<double> history_;
    
public:
    Calculator(const std::string& name);
    
    // Basic operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    // Advanced operations
    double power(double base, double exponent);
    double squareRoot(double value);
    double logarithm(double value);
    
    // History management
    void addToHistory(double result);
    void clearHistory();
    const std::vector<double>& getHistory() const;
    
    // Utility methods
    const std::string& getName() const;
    void displayHistory() const;
};

// Configuration management class
class ConfigManager {
private:
    std::string config_file_;
    std::map<std::string, std::string> settings_;
    
public:
    ConfigManager(const std::string& config_file);
    
    bool loadConfig();
    bool saveConfig();
    std::string getSetting(const std::string& key, const std::string& default_value = "");
    void setSetting(const std::string& key, const std::string& value);
    void displaySettings() const;
};

// Logger class for demonstration
class Logger {
private:
    std::string log_file_;
    bool enabled_;
    
public:
    Logger(const std::string& log_file = "app.log");
    
    void enable() { enabled_ = true; }
    void disable() { enabled_ = false; }
    
    void log(const std::string& level, const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    
    void displayLogFile() const;
};

// Function to demonstrate file organization
void demonstrateFileOrganization() {
    std::cout << "=== File Organization Demonstration ===" << std::endl;
    
    // Create calculator instance
    Calculator calc("Advanced Calculator");
    
    // Perform calculations
    double result1 = calc.add(10.5, 20.3);
    double result2 = calc.multiply(5.0, 4.0);
    double result3 = calc.power(2.0, 8.0);
    
    std::cout << "Calculator: " << calc.getName() << std::endl;
    std::cout << "10.5 + 20.3 = " << result1 << std::endl;
    std::cout << "5.0 * 4.0 = " << result2 << std::endl;
    std::cout << "2.0^8 = " << result3 << std::endl;
    
    calc.displayHistory();
}

// Function to demonstrate compilation concepts
void demonstrateCompilationConcepts() {
    std::cout << "\n=== Compilation Concepts ===" << std::endl;
    
    // External linkage (default)
    auto external_function = []() -> int {
        return 42;
    };
    
    // Internal linkage (static)
    static auto internal_function = []() -> int {
        return 24;
    };
    
    std::cout << "External function result: " << external_function() << std::endl;
    std::cout << "Internal function result: " << internal_function() << std::endl;
    
    // No linkage (local)
    auto local_function = [](int value) -> int {
        return value * 2;
    };
    
    std::cout << "Local function result: " << local_function(10) << std::endl;
}

// Function to demonstrate forward declarations
void demonstrateForwardDeclarations() {
    std::cout << "\n=== Forward Declarations ===" << std::endl;
    
    // Forward declarations allow us to use types without full definitions
    // This is useful for reducing compilation dependencies
    
    class ForwardDeclaredClass;
    
    // We can use pointers to forward-declared classes
    ForwardDeclaredClass* ptr = nullptr;
    
    // But we cannot use the class directly without definition
    // ForwardDeclaredClass obj;  // Error: incomplete type
    
    std::cout << "Forward declaration allows pointer usage: " << (ptr == nullptr ? "nullptr" : "valid") << std::endl;
}

// Function to demonstrate build system concepts
void demonstrateBuildSystemConcepts() {
    std::cout << "\n=== Build System Concepts ===" << std::endl;
    
    std::cout << "Build system concepts:" << std::endl;
    std::cout << "1. Preprocessing: Expand macros and includes" << std::endl;
    std::cout << "2. Compilation: Convert source to object files" << std::endl;
    std::cout << "3. Linking: Combine object files into executable" << std::endl;
    
    std::cout << "\nExample compilation commands:" << std::endl;
    std::cout << "g++ -c source.cpp -o source.o          # Compile to object file" << std::endl;
    std::cout << "g++ main.cpp utils.cpp -o program      # Compile and link" << std::endl;
    std::cout << "g++ -Wall -Wextra -O2 main.cpp -o program  # With warnings and optimization" << std::endl;
    
    std::cout << "\nModern build tools:" << std::endl;
    std::cout << "- CMake: Cross-platform build system" << std::endl;
    std::cout << "- Meson: Fast and user-friendly build system" << std::endl;
    std::cout << "- Bazel: Scalable build system" << std::endl;
}

// Function to demonstrate program structure
void demonstrateProgramStructure() {
    std::cout << "\n=== Program Structure ===" << std::endl;
    
    // Create configuration manager
    ConfigManager config("config.txt");
    config.setSetting("app_name", "C++ Learning Program");
    config.setSetting("version", "1.0.0");
    config.setSetting("debug", "true");
    
    std::cout << "Configuration settings:" << std::endl;
    config.displaySettings();
    
    // Create logger
    Logger logger("demo.log");
    logger.enable();
    
    logger.info("Program started");
    logger.warning("This is a demonstration");
    logger.error("Simulated error for demonstration");
    
    std::cout << "\nLog entries:" << std::endl;
    logger.displayLogFile();
}

// Function to demonstrate modular design
void demonstrateModularDesign() {
    std::cout << "\n=== Modular Design ===" << std::endl;
    
    // Demonstrate utility functions
    std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    std::cout << "Numbers: ";
    for (double num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Average: " << MathUtils::calculateAverage(numbers) << std::endl;
    std::cout << "Standard deviation: " << MathUtils::calculateStandardDeviation(numbers) << std::endl;
    std::cout << "Factorial of 5: " << MathUtils::factorial(5) << std::endl;
    
    // Test prime numbers
    std::cout << "\nPrime numbers from 1 to 20:" << std::endl;
    for (int i = 1; i <= 20; ++i) {
        if (MathUtils::isPrime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

// Function to demonstrate error handling in multi-file programs
void demonstrateErrorHandling() {
    std::cout << "\n=== Error Handling ===" << std::endl;
    
    // Test file operations
    std::string test_file = "test_output.txt";
    std::string test_content = "This is a test file for demonstration purposes.";
    
    if (FileUtils::writeFile(test_file, test_content)) {
        std::cout << "Successfully wrote to file: " << test_file << std::endl;
        
        if (FileUtils::fileExists(test_file)) {
            std::string read_content = FileUtils::readFile(test_file);
            std::cout << "File content: " << read_content << std::endl;
        }
    } else {
        std::cout << "Failed to write to file: " << test_file << std::endl;
    }
    
    // Test string splitting
    std::string test_string = "apple,banana,cherry,date";
    auto parts = FileUtils::splitString(test_string, ',');
    
    std::cout << "Split string \"" << test_string << "\":" << std::endl;
    for (const auto& part : parts) {
        std::cout << "  " << part << std::endl;
    }
}

// Function to demonstrate best practices
void demonstrateBestPractices() {
    std::cout << "\n=== Best Practices ===" << std::endl;
    
    std::cout << "Source file organization best practices:" << std::endl;
    std::cout << "1. One class per header file" << std::endl;
    std::cout << "2. Group related functions together" << std::endl;
    std::cout << "3. Use consistent naming conventions" << std::endl;
    std::cout << "4. Keep files focused and cohesive" << std::endl;
    std::cout << "5. Include only what you need" << std::endl;
    std::cout << "6. Use forward declarations when possible" << std::endl;
    std::cout << "7. Avoid circular dependencies" << std::endl;
    std::cout << "8. Order includes consistently" << std::endl;
    
    std::cout << "\nBuild system best practices:" << std::endl;
    std::cout << "1. Use modern build tools (CMake, Meson)" << std::endl;
    std::cout << "2. Configure appropriate compiler flags" << std::endl;
    std::cout << "3. Set up proper dependency management" << std::endl;
    std::cout << "4. Enable warnings and optimizations" << std::endl;
    std::cout << "5. Use version control for build files" << std::endl;
    std::cout << "6. Document build requirements" << std::endl;
}

// Implementation of Calculator class
Calculator::Calculator(const std::string& name) : name_(name) {}

double Calculator::add(double a, double b) {
    double result = a + b;
    addToHistory(result);
    return result;
}

double Calculator::subtract(double a, double b) {
    double result = a - b;
    addToHistory(result);
    return result;
}

double Calculator::multiply(double a, double b) {
    double result = a * b;
    addToHistory(result);
    return result;
}

double Calculator::divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    double result = a / b;
    addToHistory(result);
    return result;
}

double Calculator::power(double base, double exponent) {
    double result = std::pow(base, exponent);
    addToHistory(result);
    return result;
}

double Calculator::squareRoot(double value) {
    if (value < 0) {
        throw std::invalid_argument("Square root of negative number");
    }
    double result = std::sqrt(value);
    addToHistory(result);
    return result;
}

double Calculator::logarithm(double value) {
    if (value <= 0) {
        throw std::invalid_argument("Logarithm of non-positive number");
    }
    double result = std::log(value);
    addToHistory(result);
    return result;
}

void Calculator::addToHistory(double result) {
    history_.push_back(result);
}

void Calculator::clearHistory() {
    history_.clear();
}

const std::vector<double>& Calculator::getHistory() const {
    return history_;
}

const std::string& Calculator::getName() const {
    return name_;
}

void Calculator::displayHistory() const {
    std::cout << "Calculation history:" << std::endl;
    for (size_t i = 0; i < history_.size(); ++i) {
        std::cout << "  " << (i + 1) << ": " << history_[i] << std::endl;
    }
}

// Implementation of ConfigManager class
ConfigManager::ConfigManager(const std::string& config_file) : config_file_(config_file) {}

bool ConfigManager::loadConfig() {
    if (!FileUtils::fileExists(config_file_)) {
        return false;
    }
    
    std::string content = FileUtils::readFile(config_file_);
    auto lines = FileUtils::splitString(content, '\n');
    
    for (const auto& line : lines) {
        auto parts = FileUtils::splitString(line, '=');
        if (parts.size() == 2) {
            settings_[parts[0]] = parts[1];
        }
    }
    
    return true;
}

bool ConfigManager::saveConfig() {
    std::string content;
    for (const auto& pair : settings_) {
        content += pair.first + "=" + pair.second + "\n";
    }
    
    return FileUtils::writeFile(config_file_, content);
}

std::string ConfigManager::getSetting(const std::string& key, const std::string& default_value) {
    auto it = settings_.find(key);
    return (it != settings_.end()) ? it->second : default_value;
}

void ConfigManager::setSetting(const std::string& key, const std::string& value) {
    settings_[key] = value;
}

void ConfigManager::displaySettings() const {
    for (const auto& pair : settings_) {
        std::cout << "  " << pair.first << " = " << pair.second << std::endl;
    }
}

// Implementation of Logger class
Logger::Logger(const std::string& log_file) : log_file_(log_file), enabled_(true) {}

void Logger::log(const std::string& level, const std::string& message) {
    if (!enabled_) return;
    
    std::string log_entry = "[" + level + "] " + message;
    std::cout << log_entry << std::endl;
    
    // In a real application, you would write to the log file
    // For demonstration, we'll just print to console
}

void Logger::info(const std::string& message) {
    log("INFO", message);
}

void Logger::warning(const std::string& message) {
    log("WARNING", message);
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}

void Logger::displayLogFile() const {
    std::cout << "Log file: " << log_file_ << std::endl;
    std::cout << "Status: " << (enabled_ ? "Enabled" : "Disabled") << std::endl;
}

// Implementation of utility functions
namespace FileUtils {
    bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
    
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return "";
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    bool writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << content;
        return file.good();
    }
    
    std::vector<std::string> splitString(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string item;
        
        while (std::getline(ss, item, delimiter)) {
            result.push_back(item);
        }
        
        return result;
    }
}

namespace MathUtils {
    double calculateAverage(const std::vector<double>& numbers) {
        if (numbers.empty()) return 0.0;
        double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
        return sum / numbers.size();
    }
    
    double calculateStandardDeviation(const std::vector<double>& numbers) {
        if (numbers.size() < 2) return 0.0;
        
        double avg = calculateAverage(numbers);
        double sum_sq_diff = 0.0;
        
        for (double num : numbers) {
            double diff = num - avg;
            sum_sq_diff += diff * diff;
        }
        
        return std::sqrt(sum_sq_diff / (numbers.size() - 1));
    }
    
    int factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
    
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        
        return true;
    }
}

int main() {
    std::cout << "=== Source Files and Programs Demonstration ===" << std::endl;
    std::cout << "This program demonstrates source file organization,\n"
              << "compilation, linking, and program structure.\n" << std::endl;
    
    // Demonstrate various concepts
    demonstrateFileOrganization();
    demonstrateCompilationConcepts();
    demonstrateForwardDeclarations();
    demonstrateBuildSystemConcepts();
    demonstrateProgramStructure();
    demonstrateModularDesign();
    demonstrateErrorHandling();
    demonstrateBestPractices();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Source files organize code into logical units" << std::endl;
    std::cout << "2. Header files contain declarations and interfaces" << std::endl;
    std::cout << "3. Include guards prevent multiple inclusions" << std::endl;
    std::cout << "4. Forward declarations reduce compilation dependencies" << std::endl;
    std::cout << "5. Separate compilation improves build times" << std::endl;
    std::cout << "6. Modern build tools simplify project management" << std::endl;
    std::cout << "7. Proper file organization improves maintainability" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o source_files 03_Source_Files_and_Programs.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o source_files 03_Source_Files_and_Programs.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Source_Files_and_Programs.cpp
 * 
 * Running:
 * ./source_files (Linux/macOS)
 * source_files.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best program organization support.
 * 
 * Source File Notes:
 * - Organize code into logical files
 * - Use include guards or #pragma once
 * - Forward declarations reduce dependencies
 * - Separate interface from implementation
 * - Use modern build tools
 * - Follow consistent naming conventions
 * - Document file purposes and dependencies
 */"""
