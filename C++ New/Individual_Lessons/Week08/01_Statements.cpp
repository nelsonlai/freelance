/*
 * Lesson 8.1: Statements
 * 
 * This file demonstrates different types of C++ statements,
 * control flow, and iteration patterns.
 */

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

// Function to demonstrate expression statements
void demonstrateExpressionStatements() {
    std::cout << "=== Expression Statements ===" << std::endl;
    
    // Variable declarations
    int x = 10;
    int y = 20;
    int z;
    
    // Assignment expressions
    z = x + y;
    std::cout << "z = x + y = " << z << std::endl;
    
    // Arithmetic expressions
    x = 5;
    y = 3;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    
    // Increment and decrement
    ++x;
    y--;
    std::cout << "After ++x and y--: x = " << x << ", y = " << y << std::endl;
    
    // Function call expressions
    std::cout << "Function call result: " << std::max(x, y) << std::endl;
    
    // Complex expressions
    z = (x + y) * 2 - 1;
    std::cout << "(x + y) * 2 - 1 = " << z << std::endl;
}

// Function to demonstrate selection statements
void demonstrateSelectionStatements() {
    std::cout << "\n=== Selection Statements ===" << std::endl;
    
    int score = 85;
    
    // Simple if statement
    if (score >= 90) {
        std::cout << "Grade: A" << std::endl;
    }
    
    // if-else statement
    if (score >= 80) {
        std::cout << "Grade: B or better" << std::endl;
    } else {
        std::cout << "Grade: C or below" << std::endl;
    }
    
    // if-else if-else statement
    if (score >= 90) {
        std::cout << "Grade: A" << std::endl;
    } else if (score >= 80) {
        std::cout << "Grade: B" << std::endl;
    } else if (score >= 70) {
        std::cout << "Grade: C" << std::endl;
    } else if (score >= 60) {
        std::cout << "Grade: D" << std::endl;
    } else {
        std::cout << "Grade: F" << std::endl;
    }
    
    // Nested if statements
    int age = 25;
    bool hasLicense = true;
    
    if (age >= 18) {
        if (hasLicense) {
            std::cout << "Can drive" << std::endl;
        } else {
            std::cout << "Can drive but needs license" << std::endl;
        }
    } else {
        std::cout << "Cannot drive" << std::endl;
    }
}

// Function to demonstrate switch statements
void demonstrateSwitchStatements() {
    std::cout << "\n=== Switch Statements ===" << std::endl;
    
    char operation = '+';
    int a = 10, b = 5;
    
    switch (operation) {
        case '+':
            std::cout << a << " + " << b << " = " << (a + b) << std::endl;
            break;
        case '-':
            std::cout << a << " - " << b << " = " << (a - b) << std::endl;
            break;
        case '*':
            std::cout << a << " * " << b << " = " << (a * b) << std::endl;
            break;
        case '/':
            if (b != 0) {
                std::cout << a << " / " << b << " = " << (a / b) << std::endl;
            } else {
                std::cout << "Division by zero!" << std::endl;
            }
            break;
        default:
            std::cout << "Unknown operation: " << operation << std::endl;
            break;
    }
    
    // Switch with fall-through (intentional)
    int month = 2;
    std::cout << "\nDays in month " << month << ": ";
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            std::cout << "31 days" << std::endl;
            break;
        case 4: case 6: case 9: case 11:
            std::cout << "30 days" << std::endl;
            break;
        case 2:
            std::cout << "28 or 29 days (leap year)" << std::endl;
            break;
        default:
            std::cout << "Invalid month" << std::endl;
            break;
    }
}

// Function to demonstrate for loops
void demonstrateForLoops() {
    std::cout << "\n=== For Loops ===" << std::endl;
    
    // Basic for loop
    std::cout << "Counting from 1 to 5:" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // For loop with different increment
    std::cout << "Even numbers from 2 to 10:" << std::endl;
    for (int i = 2; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Reverse for loop
    std::cout << "Counting down from 5 to 1:" << std::endl;
    for (int i = 5; i >= 1; --i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // For loop with multiple variables
    std::cout << "Multiple variables in for loop:" << std::endl;
    for (int i = 0, j = 10; i < 5; ++i, --j) {
        std::cout << "i=" << i << ", j=" << j << std::endl;
    }
    
    // Range-based for loop (C++11)
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "\nRange-based for loop:" << std::endl;
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate while loops
void demonstrateWhileLoops() {
    std::cout << "\n=== While Loops ===" << std::endl;
    
    // Basic while loop
    int count = 0;
    std::cout << "Counting from 0 to 4:" << std::endl;
    while (count < 5) {
        std::cout << count << " ";
        ++count;
    }
    std::cout << std::endl;
    
    // While loop with condition
    int number = 64;
    std::cout << "Halving " << number << " until it's less than 10:" << std::endl;
    while (number >= 10) {
        std::cout << number << " ";
        number /= 2;
    }
    std::cout << number << std::endl;
    
    // While loop with user input simulation
    std::cout << "Simulating user input (1-5):" << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    
    int userInput;
    do {
        userInput = dis(gen);
        std::cout << "Generated: " << userInput << std::endl;
    } while (userInput > 5);
    
    std::cout << "Valid input received: " << userInput << std::endl;
}

// Function to demonstrate do-while loops
void demonstrateDoWhileLoops() {
    std::cout << "\n=== Do-While Loops ===" << std::endl;
    
    // Basic do-while loop
    int count = 0;
    std::cout << "Do-while counting from 0 to 4:" << std::endl;
    do {
        std::cout << count << " ";
        ++count;
    } while (count < 5);
    std::cout << std::endl;
    
    // Do-while loop that executes at least once
    std::cout << "Do-while with condition that's false initially:" << std::endl;
    int value = 10;
    do {
        std::cout << "Value: " << value << std::endl;
        value -= 2;
    } while (value > 20);  // Condition is false initially
    
    std::cout << "Loop executed once even though condition was false" << std::endl;
}

// Function to demonstrate compound statements (blocks)
void demonstrateCompoundStatements() {
    std::cout << "\n=== Compound Statements (Blocks) ===" << std::endl;
    
    int x = 10;
    int y = 20;
    
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    
    // Compound statement for swapping
    {
        int temp = x;
        x = y;
        y = temp;
        std::cout << "Inside block: temp = " << temp << std::endl;
    }
    
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    // std::cout << temp << std::endl;  // Error: temp is out of scope
    
    // Nested blocks
    {
        int outer = 100;
        std::cout << "Outer block: outer = " << outer << std::endl;
        
        {
            int inner = 200;
            std::cout << "Inner block: inner = " << inner << std::endl;
            std::cout << "Inner block: outer = " << outer << std::endl;  // Can access outer
        }
        
        // std::cout << inner << std::endl;  // Error: inner is out of scope
        std::cout << "Outer block: outer = " << outer << std::endl;
    }
}

// Function to demonstrate nested loops
void demonstrateNestedLoops() {
    std::cout << "\n=== Nested Loops ===" << std::endl;
    
    // Nested for loops
    std::cout << "Multiplication table (3x3):" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            std::cout << i << " x " << j << " = " << (i * j) << "\t";
        }
        std::cout << std::endl;
    }
    
    // Nested loops with different types
    std::cout << "\nPattern with nested loops:" << std::endl;
    int rows = 5;
    for (int i = 1; i <= rows; ++i) {
        int j = 1;
        while (j <= i) {
            std::cout << "* ";
            ++j;
        }
        std::cout << std::endl;
    }
}

// Function to demonstrate loop control statements
void demonstrateLoopControl() {
    std::cout << "\n=== Loop Control Statements ===" << std::endl;
    
    // Break statement
    std::cout << "Break statement example:" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        if (i == 6) {
            std::cout << "Breaking at " << i << std::endl;
            break;
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Continue statement
    std::cout << "Continue statement example (skip even numbers):" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Nested loop with break
    std::cout << "Nested loop with break:" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            if (i == 2 && j == 2) {
                std::cout << "Breaking inner loop" << std::endl;
                break;  // Breaks only inner loop
            }
            std::cout << "(" << i << "," << j << ") ";
        }
        std::cout << std::endl;
    }
}

// Function to demonstrate loop optimization
void demonstrateLoopOptimization() {
    std::cout << "\n=== Loop Optimization ===" << std::endl;
    
    const int size = 1000000;
    std::vector<int> data(size);
    
    // Initialize data
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }
    
    // Measure loop performance
    auto start = std::chrono::high_resolution_clock::now();
    
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Loop time: " << duration.count() << " microseconds" << std::endl;
    
    // Optimized loop (range-based for)
    start = std::chrono::high_resolution_clock::now();
    
    sum = 0;
    for (const auto& value : data) {
        sum += value;
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Optimized loop time: " << duration.count() << " microseconds" << std::endl;
}

// Function to demonstrate statement errors
void demonstrateStatementErrors() {
    std::cout << "\n=== Common Statement Errors ===" << std::endl;
    
    std::cout << "Common errors to avoid:" << std::endl;
    std::cout << "1. Missing semicolons" << std::endl;
    std::cout << "2. Infinite loops" << std::endl;
    std::cout << "3. Missing break statements in switch" << std::endl;
    std::cout << "4. Off-by-one errors in loops" << std::endl;
    std::cout << "5. Uninitialized variables" << std::endl;
    
    // Example of off-by-one error
    std::cout << "\nOff-by-one error example:" << std::endl;
    std::cout << "Correct loop (0 to 4):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Incorrect loop (0 to 5):" << std::endl;
    for (int i = 0; i <= 5; ++i) {  // Off-by-one error
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Statements Demonstration ===" << std::endl;
    std::cout << "This program demonstrates different types of C++ statements,\n"
              << "control flow, and iteration patterns.\n" << std::endl;
    
    // Demonstrate various statement types
    demonstrateExpressionStatements();
    demonstrateSelectionStatements();
    demonstrateSwitchStatements();
    demonstrateForLoops();
    demonstrateWhileLoops();
    demonstrateDoWhileLoops();
    demonstrateCompoundStatements();
    demonstrateNestedLoops();
    demonstrateLoopControl();
    demonstrateLoopOptimization();
    demonstrateStatementErrors();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Statements are the executable units of a C++ program" << std::endl;
    std::cout << "2. Selection statements control program flow based on conditions" << std::endl;
    std::cout << "3. Iteration statements repeat code execution" << std::endl;
    std::cout << "4. Compound statements group multiple statements together" << std::endl;
    std::cout << "5. Loop control statements (break, continue) modify loop behavior" << std::endl;
    std::cout << "6. Proper loop design prevents infinite loops and off-by-one errors" << std::endl;
    std::cout << "7. Range-based for loops provide cleaner iteration over containers" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o statements 01_Statements.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o statements 01_Statements.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Statements.cpp
 * 
 * Running:
 * ./statements (Linux/macOS)
 * statements.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for range-based for loops.
 * C++17 is recommended for best statement support.
 * 
 * Statement Notes:
 * - Statements control program execution flow
 * - Use appropriate loop types for different scenarios
 * - Always include break statements in switch cases
 * - Be careful with loop bounds to avoid off-by-one errors
 * - Use compound statements to limit variable scope
 * - Loop control statements provide flexibility in loop behavior
 */"""
