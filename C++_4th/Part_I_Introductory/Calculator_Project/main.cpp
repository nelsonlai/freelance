#include "calculator.h"
#include <iostream>
#include <string>
#include <thread>
#include <future>

// Interactive calculator demonstration
class InteractiveCalculator {
private:
    Calculator calc;
    
    void display_menu() {
        std::cout << "\n=== Interactive Calculator ===" << std::endl;
        std::cout << "1. Calculate expression" << std::endl;
        std::cout << "2. View history" << std::endl;
        std::cout << "3. Clear history" << std::endl;
        std::cout << "4. Async calculation (demo)" << std::endl;
        std::cout << "5. Show help" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "==============================" << std::endl;
    }
    
    void show_help() {
        std::cout << "\n=== Calculator Help ===" << std::endl;
        std::cout << "Basic Operations:" << std::endl;
        std::cout << "  + (addition), - (subtraction), * (multiplication), / (division)" << std::endl;
        std::cout << "  ^ (power), % (modulo)" << std::endl;
        std::cout << "\nScientific Functions:" << std::endl;
        std::cout << "  sqrt(x) - square root" << std::endl;
        std::cout << "  sin(x), cos(x), tan(x) - trigonometric functions" << std::endl;
        std::cout << "  log(x) - logarithm base 10" << std::endl;
        std::cout << "  ln(x) - natural logarithm" << std::endl;
        std::cout << "  abs(x) - absolute value" << std::endl;
        std::cout << "  floor(x), ceil(x), round(x) - rounding functions" << std::endl;
        std::cout << "\nExamples:" << std::endl;
        std::cout << "  2 + 3 * 4" << std::endl;
        std::cout << "  sqrt(16)" << std::endl;
        std::cout << "  sin(3.14159/2)" << std::endl;
        std::cout << "======================" << std::endl;
    }
    
    void handle_calculation() {
        std::string expression;
        std::cout << "Enter expression: ";
        std::getline(std::cin, expression);
        
        if (expression.empty()) {
            std::cout << "Empty expression!" << std::endl;
            return;
        }
        
        try {
            double result = calc.calculate(expression);
            std::cout << "Result: " << result << std::endl;
        } catch (const CalculatorException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
        }
    }
    
    void handle_async_calculation() {
        std::string expression;
        std::cout << "Enter expression for async calculation: ";
        std::getline(std::cin, expression);
        
        if (expression.empty()) {
            std::cout << "Empty expression!" << std::endl;
            return;
        }
        
        std::cout << "Starting async calculation..." << std::endl;
        auto future_result = calc.calculate_async(expression);
        
        // Simulate doing other work
        std::cout << "Doing other work while calculating..." << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "Working... " << (i + 1) << std::endl;
        }
        
        try {
            double result = future_result.get();
            std::cout << "Async result: " << result << std::endl;
        } catch (const CalculatorException& e) {
            std::cout << "Async error: " << e.what() << std::endl;
        }
    }
    
public:
    void run() {
        std::cout << "Welcome to the Advanced Calculator!" << std::endl;
        std::cout << "This calculator demonstrates C++ concepts from Part I:" << std::endl;
        std::cout << "- Object-oriented programming" << std::endl;
        std::cout << "- Exception handling" << std::endl;
        std::cout << "- STL containers and algorithms" << std::endl;
        std::cout << "- Basic threading concepts" << std::endl;
        
        int choice;
        std::string input;
        
        while (true) {
            display_menu();
            std::cout << "Enter choice: ";
            std::getline(std::cin, input);
            
            try {
                choice = std::stoi(input);
            } catch (const std::exception&) {
                std::cout << "Invalid choice! Please enter a number." << std::endl;
                continue;
            }
            
            switch (choice) {
                case 1:
                    handle_calculation();
                    break;
                case 2:
                    calc.display_history();
                    break;
                case 3:
                    calc.clear_history();
                    std::cout << "History cleared." << std::endl;
                    break;
                case 4:
                    handle_async_calculation();
                    break;
                case 5:
                    show_help();
                    break;
                case 0:
                    std::cout << "Thank you for using the calculator!" << std::endl;
                    return;
                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
                    break;
            }
        }
    }
};

// Demonstration of calculator features
void demonstrate_calculator_features() {
    std::cout << "=== Calculator Feature Demonstration ===" << std::endl;
    
    Calculator calc;
    
    // Test basic operations
    std::cout << "\n1. Basic Operations:" << std::endl;
    try {
        std::cout << "2 + 3 = " << calc.calculate("2 + 3") << std::endl;
        std::cout << "10 - 4 = " << calc.calculate("10 - 4") << std::endl;
        std::cout << "6 * 7 = " << calc.calculate("6 * 7") << std::endl;
        std::cout << "15 / 3 = " << calc.calculate("15 / 3") << std::endl;
        std::cout << "2 ^ 8 = " << calc.calculate("2 ^ 8") << std::endl;
    } catch (const CalculatorException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test scientific operations
    std::cout << "\n2. Scientific Operations:" << std::endl;
    try {
        std::cout << "sqrt(16) = " << calc.calculate("sqrt(16)") << std::endl;
        std::cout << "sin(3.14159/2) = " << calc.calculate("sin(3.14159/2)") << std::endl;
        std::cout << "log(100) = " << calc.calculate("log(100)") << std::endl;
        std::cout << "abs(-5) = " << calc.calculate("abs(-5)") << std::endl;
    } catch (const CalculatorException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test error handling
    std::cout << "\n3. Error Handling:" << std::endl;
    try {
        calc.calculate("5 / 0");
    } catch (const CalculatorException& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }
    
    try {
        calc.calculate("sqrt(-4)");
    } catch (const CalculatorException& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }
    
    // Display history
    std::cout << "\n4. Calculation History:" << std::endl;
    calc.display_history();
    
    // Test async calculation
    std::cout << "\n5. Async Calculation:" << std::endl;
    auto future_result = calc.calculate_async("2 ^ 10");
    std::cout << "Async calculation started..." << std::endl;
    
    try {
        double result = future_result.get();
        std::cout << "Async result: " << result << std::endl;
    } catch (const CalculatorException& e) {
        std::cout << "Async error: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Demonstration Complete ===" << std::endl;
}

int main() {
    std::cout << "C++ Calculator Project - Part I Capstone" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    // Run demonstration
    demonstrate_calculator_features();
    
    // Ask user if they want to run interactive mode
    std::cout << "\nWould you like to run the interactive calculator? (y/n): ";
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "y" || choice == "Y" || choice == "yes") {
        InteractiveCalculator interactive_calc;
        interactive_calc.run();
    } else {
        std::cout << "Thank you for trying the calculator!" << std::endl;
    }
    
    return 0;
}
