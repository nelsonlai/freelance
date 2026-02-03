#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <thread>
#include <future>
#include <mutex>
#include "calculator_exception.h"

// Forward declarations
class Operation;
class OperationHistory;

// Main Calculator class demonstrating OOP principles and STL usage
class Calculator {
private:
    std::unique_ptr<OperationHistory> history;
    std::map<std::string, std::function<double(double, double)>> basic_operations;
    std::map<std::string, std::function<double(double)>> scientific_operations;
    mutable std::mutex history_mutex;
    
    // Helper functions
    void initialize_operations();
    double perform_basic_operation(const std::string& op, double a, double b);
    double perform_scientific_operation(const std::string& op, double value);
    std::string parse_expression(const std::string& expression);
    std::vector<std::string> tokenize(const std::string& expression);
    double evaluate_tokens(const std::vector<std::string>& tokens);
    bool is_number(const std::string& str) const;
    bool is_operator(const std::string& str) const;
    
public:
    // Constructors and destructor
    Calculator();
    ~Calculator();
    
    // Copy constructor and assignment operator (disabled for simplicity)
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    
    // Move constructor and assignment operator
    Calculator(Calculator&&) noexcept;
    Calculator& operator=(Calculator&&) noexcept;
    
    // Main calculation methods
    double calculate(const std::string& expression);
    std::future<double> calculate_async(const std::string& expression);
    
    // History management
    void add_to_history(const std::string& expression, double result);
    void clear_history();
    void display_history() const;
    size_t get_history_size() const;
    
    // Operation management
    void add_custom_operation(const std::string& name, 
                            std::function<double(double, double)> operation);
    void add_custom_scientific_operation(const std::string& name,
                                       std::function<double(double)> operation);
    
    // Utility methods
    bool is_valid_expression(const std::string& expression) const;
    std::string get_last_result() const;
    
    // Static utility methods
    static double factorial(int n);
    static double power(double base, double exponent);
    static double square_root(double value);
    static double logarithm(double value);
    static double sine(double value);
    static double cosine(double value);
    static double tangent(double value);
    
    // Friend function for stream output
    friend std::ostream& operator<<(std::ostream& os, const Calculator& calc);
};

// Custom exception classes
class CalculatorException : public std::exception {
private:
    std::string message;
    
public:
    explicit CalculatorException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class DivisionByZeroException : public CalculatorException {
public:
    DivisionByZeroException() : CalculatorException("Division by zero") {}
};

class InvalidExpressionException : public CalculatorException {
public:
    InvalidExpressionException(const std::string& expr) 
        : CalculatorException("Invalid expression: " + expr) {}
};

class OverflowException : public CalculatorException {
public:
    OverflowException() : CalculatorException("Arithmetic overflow") {}
};

class UnderflowException : public CalculatorException {
public:
    UnderflowException() : CalculatorException("Arithmetic underflow") {}
};

#endif // CALCULATOR_H
