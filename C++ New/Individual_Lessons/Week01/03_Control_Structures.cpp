/*
 * Lesson 1.3: Control Structures
 * 
 * This file demonstrates various control structures in C++ including
 * conditional statements, loops, and control flow statements.
 */

#include <iostream>
#include <vector>
#include <string>
#include <limits>

// Function to demonstrate if/else statements
void demonstrateIfElse() {
    std::cout << "=== If/Else Statements Demo ===" << std::endl;
    
    int score;
    std::cout << "Enter a test score (0-100): ";
    std::cin >> score;
    
    if (score >= 90) {
        std::cout << "Grade: A (Excellent!)" << std::endl;
    } else if (score >= 80) {
        std::cout << "Grade: B (Good!)" << std::endl;
    } else if (score >= 70) {
        std::cout << "Grade: C (Average)" << std::endl;
    } else if (score >= 60) {
        std::cout << "Grade: D (Below Average)" << std::endl;
    } else {
        std::cout << "Grade: F (Fail)" << std::endl;
    }
}

// Function to demonstrate switch statements
void demonstrateSwitch() {
    std::cout << "\n=== Switch Statements Demo ===" << std::endl;
    
    char choice;
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "a) Addition" << std::endl;
    std::cout << "b) Subtraction" << std::endl;
    std::cout << "c) Multiplication" << std::endl;
    std::cout << "d) Division" << std::endl;
    std::cout << "Enter choice (a-d): ";
    std::cin >> choice;
    
    switch (choice) {
        case 'a':
        case 'A':
            std::cout << "You chose: Addition" << std::endl;
            break;
        case 'b':
        case 'B':
            std::cout << "You chose: Subtraction" << std::endl;
            break;
        case 'c':
        case 'C':
            std::cout << "You chose: Multiplication" << std::endl;
            break;
        case 'd':
        case 'D':
            std::cout << "You chose: Division" << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
    }
}

// Function to demonstrate for loops
void demonstrateForLoops() {
    std::cout << "\n=== For Loops Demo ===" << std::endl;
    
    // Basic for loop
    std::cout << "Counting 1 to 5: ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Countdown for loop
    std::cout << "Countdown from 5 to 1: ";
    for (int i = 5; i >= 1; --i) {
        std::cout << i << " ";
    }
    std::cout << "Blast off!" << std::endl;
    
    // For loop with step
    std::cout << "Even numbers 2 to 10: ";
    for (int i = 2; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate while loops
void demonstrateWhileLoops() {
    std::cout << "\n=== While Loops Demo ===" << std::endl;
    
    // Basic while loop
    int count = 1;
    std::cout << "While loop counting: ";
    while (count <= 5) {
        std::cout << count << " ";
        ++count;
    }
    std::cout << std::endl;
    
    // Input validation while loop
    int number;
    std::cout << "Enter a positive number: ";
    while (true) {
        std::cin >> number;
        if (number > 0) {
            break;
        }
        std::cout << "Invalid input. Enter a positive number: ";
    }
    std::cout << "Thank you! You entered: " << number << std::endl;
}

// Function to demonstrate do-while loops
void demonstrateDoWhileLoops() {
    std::cout << "\n=== Do-While Loops Demo ===" << std::endl;
    
    char repeat;
    do {
        std::cout << "This is a do-while loop example." << std::endl;
        std::cout << "Do you want to see it again? (y/n): ";
        std::cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
    
    std::cout << "Do-while loop completed!" << std::endl;
}

// Function to demonstrate range-based for loops
void demonstrateRangeBasedFor() {
    std::cout << "\n=== Range-Based For Loops Demo ===" << std::endl;
    
    // Range-based for with vector
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    std::cout << "Vector elements: ";

    for (int i=0; i < numbers.size(); ++i) {   // traditional style
        std::cout << numbers[i] << " ";
    }

    for (const auto& num : numbers) {   // modern C++ style
        std::cout << num << " ";
    }

    std::cout << std::endl;
    
    // Range-based for with string
    std::string text = "Hello";
    std::cout << "String characters: ";
    for (const auto& ch : text) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;
    
    // Range-based for with array
    int array[] = {1, 3, 5, 7, 9};
    std::cout << "Array elements: ";
    for (const auto& elem : array) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate break and continue
void demonstrateBreakContinue() {
    std::cout << "\n=== Break and Continue Demo ===" << std::endl;
    
    // break example
    std::cout << "Loop with break (stops at 5): ";
    for (int i = 1; i <= 10; ++i) {
        if (i == 5) {
            std::cout << "BREAK ";
            break;
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // continue example
    std::cout << "Loop with continue (skips even numbers): ";
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            std::cout << "SKIP ";
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate nested loops
void demonstrateNestedLoops() {
    std::cout << "\n=== Nested Loops Demo ===" << std::endl;
    
    // Multiplication table
    std::cout << "Multiplication table (3x3):" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            std::cout << i * j << "\t";
        }
        std::cout << std::endl;
    }
    
    // Pattern generation
    std::cout << "\nNumber pattern:" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= i; ++j) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

// Function to demonstrate boolean expressions
void demonstrateBooleanExpressions() {
    std::cout << "\n=== Boolean Expressions Demo ===" << std::endl;
    
    int a = 10, b = 20, c = 10;
    
    // Comparison operators
    std::cout << "Comparison operators:" << std::endl;
    std::cout << "  " << a << " > " << b << " = " << std::boolalpha << (a > b) << std::endl;
    std::cout << "  " << a << " < " << b << " = " << (a < b) << std::endl;
    std::cout << "  " << a << " == " << c << " = " << (a == c) << std::endl;
    std::cout << "  " << a << " != " << b << " = " << (a != b) << std::endl;
    
    // Logical operators
    std::cout << "\nLogical operators:" << std::endl;
    bool x = true, y = false;
    std::cout << "  " << x << " && " << y << " = " << (x && y) << std::endl;
    std::cout << "  " << x << " || " << y << " = " << (x || y) << std::endl;
    std::cout << "  !" << x << " = " << (!x) << std::endl;
}

// Function to demonstrate practical examples
void demonstratePracticalExamples() {
    std::cout << "\n=== Practical Examples Demo ===" << std::endl;
    
    // Sum of numbers
    int sum = 0;
    for (int i = 1; i <= 100; ++i) {
        sum += i;
    }
    std::cout << "Sum of numbers 1 to 100: " << sum << std::endl;
    
    // Factorial calculation
    int n = 5;
    long long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    std::cout << "Factorial of " << n << ": " << factorial << std::endl;
    
    // Finding maximum in array
    std::vector<int> numbers = {45, 12, 78, 23, 56, 89, 34};
    int maxNum = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] > maxNum) {
            maxNum = numbers[i];
        }
    }
    // morden C++ style
    for (const auto& num : numbers) {
        if (num > maxNum) {
            maxNum = num;
        }
    }
    std::cout << "Maximum number in array: " << maxNum << std::endl;
}

// Function to demonstrate menu-driven program
void demonstrateMenuDriven() {
    std::cout << "\n=== Menu-Driven Program Demo ===" << std::endl;
    
    int choice;
    do {
        std::cout << "\n=== Calculator Menu ===" << std::endl;
        std::cout << "1. Add two numbers" << std::endl;
        std::cout << "2. Subtract two numbers" << std::endl;
        std::cout << "3. Multiply two numbers" << std::endl;
        std::cout << "4. Divide two numbers" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                double a, b;
                std::cout << "Enter two numbers: ";
                std::cin >> a >> b;
                std::cout << "Sum: " << (a + b) << std::endl;
                break;
            }
            case 2: {
                double a, b;
                std::cout << "Enter two numbers: ";
                std::cin >> a >> b;
                std::cout << "Difference: " << (a - b) << std::endl;
                break;
            }
            case 3: {
                double a, b;
                std::cout << "Enter two numbers: ";
                std::cin >> a >> b;
                std::cout << "Product: " << (a * b) << std::endl;
                break;
            }
            case 4: {
                double a, b;
                std::cout << "Enter two numbers: ";
                std::cin >> a >> b;
                if (b != 0) {
                    std::cout << "Quotient: " << (a / b) << std::endl;
                } else {
                    std::cout << "Error: Division by zero!" << std::endl;
                }
                break;
            }
            case 5:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                break;
        }
    } while (choice != 5);
}

int main() {
    std::cout << "=== C++ Control Structures Demo ===" << std::endl;
    std::cout << "This program demonstrates various control structures.\n" << std::endl;
    
    // Demonstrate various control structures
    demonstrateIfElse();
    demonstrateSwitch();
    demonstrateForLoops();
    demonstrateWhileLoops();
    demonstrateDoWhileLoops();
    demonstrateRangeBasedFor();
    demonstrateBreakContinue();
    demonstrateNestedLoops();
    demonstrateBooleanExpressions();
    demonstratePracticalExamples();
    demonstrateMenuDriven();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Use if/else for simple conditions, switch for multiple values" << std::endl;
    std::cout << "2. for loops are good for known iterations, while for unknown" << std::endl;
    std::cout << "3. Range-based for loops simplify iteration over containers" << std::endl;
    std::cout << "4. break exits loops, continue skips to next iteration" << std::endl;
    std::cout << "5. Nested loops are powerful but can be complex" << std::endl;
    std::cout << "6. Boolean expressions control program flow" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o control_structures 03_Control_Structures.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o control_structures 03_Control_Structures.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 03_Control_Structures.cpp
 * 
 * Running:
 * ./control_structures (Linux/macOS)
 * control_structures.exe (Windows)
 */
