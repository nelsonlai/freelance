#include "calculator.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <thread>
#include <chrono>

// OperationHistory class for managing calculation history
class OperationHistory {
private:
    std::vector<std::string> expressions;
    std::vector<double> results;
    mutable std::mutex mutex;
    
public:
    void add_entry(const std::string& expression, double result) {
        std::lock_guard<std::mutex> lock(mutex);
        expressions.push_back(expression);
        results.push_back(result);
    }
    
    void clear() {
        std::lock_guard<std::mutex> lock(mutex);
        expressions.clear();
        results.clear();
    }
    
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return expressions.size();
    }
    
    void display() const {
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << "\n=== Calculation History ===" << std::endl;
        for (size_t i = 0; i < expressions.size(); ++i) {
            std::cout << (i + 1) << ". " << expressions[i] 
                      << " = " << results[i] << std::endl;
        }
        std::cout << "=========================" << std::endl;
    }
    
    std::string get_last_result() const {
        std::lock_guard<std::mutex> lock(mutex);
        if (results.empty()) {
            return "No previous result";
        }
        return std::to_string(results.back());
    }
};

// Calculator implementation
Calculator::Calculator() : history(std::make_unique<OperationHistory>()) {
    initialize_operations();
}

Calculator::~Calculator() = default;

Calculator::Calculator(Calculator&& other) noexcept 
    : history(std::move(other.history)),
      basic_operations(std::move(other.basic_operations)),
      scientific_operations(std::move(other.scientific_operations)) {}

Calculator& Calculator::operator=(Calculator&& other) noexcept {
    if (this != &other) {
        history = std::move(other.history);
        basic_operations = std::move(other.basic_operations);
        scientific_operations = std::move(other.scientific_operations);
    }
    return *this;
}

void Calculator::initialize_operations() {
    // Basic arithmetic operations
    basic_operations["+"] = [](double a, double b) { return a + b; };
    basic_operations["-"] = [](double a, double b) { return a - b; };
    basic_operations["*"] = [](double a, double b) { return a * b; };
    basic_operations["/"] = [](double a, double b) {
        if (std::abs(b) < std::numeric_limits<double>::epsilon()) {
            throw DivisionByZeroException();
        }
        return a / b;
    };
    basic_operations["^"] = [](double a, double b) { return std::pow(a, b); };
    basic_operations["%"] = [](double a, double b) {
        if (std::abs(b) < std::numeric_limits<double>::epsilon()) {
            throw DivisionByZeroException();
        }
        return std::fmod(a, b);
    };
    
    // Scientific operations
    scientific_operations["sqrt"] = [](double x) {
        if (x < 0) {
            throw CalculatorException("Square root of negative number");
        }
        return std::sqrt(x);
    };
    scientific_operations["sin"] = [](double x) { return std::sin(x); };
    scientific_operations["cos"] = [](double x) { return std::cos(x); };
    scientific_operations["tan"] = [](double x) { return std::tan(x); };
    scientific_operations["log"] = [](double x) {
        if (x <= 0) {
            throw CalculatorException("Logarithm of non-positive number");
        }
        return std::log(x);
    };
    scientific_operations["ln"] = [](double x) {
        if (x <= 0) {
            throw CalculatorException("Natural logarithm of non-positive number");
        }
        return std::log(x);
    };
    scientific_operations["abs"] = [](double x) { return std::abs(x); };
    scientific_operations["floor"] = [](double x) { return std::floor(x); };
    scientific_operations["ceil"] = [](double x) { return std::ceil(x); };
    scientific_operations["round"] = [](double x) { return std::round(x); };
}

double Calculator::calculate(const std::string& expression) {
    if (!is_valid_expression(expression)) {
        throw InvalidExpressionException(expression);
    }
    
    try {
        std::string parsed_expr = parse_expression(expression);
        std::vector<std::string> tokens = tokenize(parsed_expr);
        double result = evaluate_tokens(tokens);
        
        // Check for overflow/underflow
        if (std::isinf(result)) {
            throw OverflowException();
        }
        if (std::isnan(result)) {
            throw CalculatorException("Result is not a number");
        }
        
        add_to_history(expression, result);
        return result;
    } catch (const CalculatorException&) {
        throw;
    } catch (const std::exception& e) {
        throw CalculatorException("Calculation error: " + std::string(e.what()));
    }
}

std::future<double> Calculator::calculate_async(const std::string& expression) {
    return std::async(std::launch::async, [this, expression]() {
        // Simulate complex calculation for demonstration
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return calculate(expression);
    });
}

void Calculator::add_to_history(const std::string& expression, double result) {
    history->add_entry(expression, result);
}

void Calculator::clear_history() {
    history->clear();
}

void Calculator::display_history() const {
    history->display();
}

size_t Calculator::get_history_size() const {
    return history->size();
}

void Calculator::add_custom_operation(const std::string& name, 
                                    std::function<double(double, double)> operation) {
    basic_operations[name] = operation;
}

void Calculator::add_custom_scientific_operation(const std::string& name,
                                               std::function<double(double)> operation) {
    scientific_operations[name] = operation;
}

bool Calculator::is_valid_expression(const std::string& expression) const {
    if (expression.empty()) return false;
    
    // Basic validation: check for balanced parentheses
    int paren_count = 0;
    for (char c : expression) {
        if (c == '(') paren_count++;
        else if (c == ')') paren_count--;
        if (paren_count < 0) return false;
    }
    return paren_count == 0;
}

std::string Calculator::get_last_result() const {
    return history->get_last_result();
}

// Static utility methods
double Calculator::factorial(int n) {
    if (n < 0) {
        throw CalculatorException("Factorial of negative number");
    }
    if (n > 20) {  // Prevent overflow
        throw OverflowException();
    }
    
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double Calculator::power(double base, double exponent) {
    return std::pow(base, exponent);
}

double Calculator::square_root(double value) {
    if (value < 0) {
        throw CalculatorException("Square root of negative number");
    }
    return std::sqrt(value);
}

double Calculator::logarithm(double value) {
    if (value <= 0) {
        throw CalculatorException("Logarithm of non-positive number");
    }
    return std::log10(value);
}

double Calculator::sine(double value) {
    return std::sin(value);
}

double Calculator::cosine(double value) {
    return std::cos(value);
}

double Calculator::tangent(double value) {
    return std::tan(value);
}

// Helper methods
double Calculator::perform_basic_operation(const std::string& op, double a, double b) {
    auto it = basic_operations.find(op);
    if (it != basic_operations.end()) {
        return it->second(a, b);
    }
    throw CalculatorException("Unknown operation: " + op);
}

double Calculator::perform_scientific_operation(const std::string& op, double value) {
    auto it = scientific_operations.find(op);
    if (it != scientific_operations.end()) {
        return it->second(value);
    }
    throw CalculatorException("Unknown scientific operation: " + op);
}

std::string Calculator::parse_expression(const std::string& expression) {
    // Simple parsing - in a real implementation, this would be more sophisticated
    std::string result = expression;
    
    // Remove spaces
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    
    return result;
}

std::vector<std::string> Calculator::tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string current_token;
    
    for (char c : expression) {
        if (std::isdigit(c) || c == '.') {
            current_token += c;
        } else if (std::isalpha(c)) {
            current_token += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(std::string(1, c));
        } else if (c == '(' || c == ')') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(std::string(1, c));
        }
    }
    
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    
    return tokens;
}

double Calculator::evaluate_tokens(const std::vector<std::string>& tokens) {
    // Simplified evaluation - in a real implementation, this would use proper parsing
    if (tokens.empty()) {
        throw InvalidExpressionException("Empty expression");
    }
    
    if (tokens.size() == 1) {
        if (is_number(tokens[0])) {
            return std::stod(tokens[0]);
        } else {
            throw InvalidExpressionException("Invalid number: " + tokens[0]);
        }
    }
    
    // For simplicity, handle basic expressions like "a + b"
    if (tokens.size() == 3 && is_number(tokens[0]) && is_operator(tokens[1]) && is_number(tokens[2])) {
        double a = std::stod(tokens[0]);
        double b = std::stod(tokens[2]);
        return perform_basic_operation(tokens[1], a, b);
    }
    
    // Handle scientific functions like "sqrt(16)"
    if (tokens.size() == 4 && tokens[1] == "(" && tokens[3] == ")") {
        if (is_number(tokens[2])) {
            double value = std::stod(tokens[2]);
            return perform_scientific_operation(tokens[0], value);
        }
    }
    
    throw InvalidExpressionException("Unsupported expression format");
}

bool Calculator::is_number(const std::string& str) const {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-') start = 1;
    
    bool has_digit = false;
    bool has_dot = false;
    
    for (size_t i = start; i < str.length(); ++i) {
        if (std::isdigit(str[i])) {
            has_digit = true;
        } else if (str[i] == '.' && !has_dot) {
            has_dot = true;
        } else {
            return false;
        }
    }
    
    return has_digit;
}

bool Calculator::is_operator(const std::string& str) const {
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "^" || str == "%";
}

// Friend function implementation
std::ostream& operator<<(std::ostream& os, const Calculator& calc) {
    os << "Calculator with " << calc.get_history_size() << " operations in history";
    return os;
}
