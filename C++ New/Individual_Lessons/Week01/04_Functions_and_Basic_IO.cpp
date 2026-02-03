/*
 * Lesson 1.4: Functions and Basic I/O
 * 
 * This file demonstrates function declaration, definition, parameter passing,
 * return types, and basic input/output operations.
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

// Function declarations
int add(int a, int b);
double multiply(double x, double y);
void greet(const std::string& name);
bool isEven(int number);
int getValidInput(const std::string& prompt, int min, int max);
void displayMenu();
double calculateArea(double length, double width);
double calculatePerimeter(double length, double width);
int factorial(int n);
bool isPrime(int n);
void swapValues(int& a, int& b);
void clearInputBuffer();

// Function to demonstrate basic function calls
void demonstrateBasicFunctions() {
    std::cout << "=== Basic Functions Demo ===" << std::endl;
    
    // Function calls with different return types
    int sum = add(15, 25);
    std::cout << "Sum of 15 and 25: " << sum << std::endl;
    
    double product = multiply(3.5, 4.2);
    std::cout << "Product of 3.5 and 4.2: " << product << std::endl;
    
    greet("Alice");
    greet("Bob");
    
    // Boolean function
    std::cout << "Is 8 even? " << (isEven(8) ? "Yes" : "No") << std::endl;
    std::cout << "Is 7 even? " << (isEven(7) ? "Yes" : "No") << std::endl;
}

// Function to demonstrate parameter passing
void demonstrateParameterPassing() {
    std::cout << "\n=== Parameter Passing Demo ===" << std::endl;
    
    // Pass by value
    int x = 10, y = 20;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    
    // Pass by reference
    swapValues(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    // Pass by const reference
    std::string message = "Hello, Functions!";
    greet(message);
}

// Function to demonstrate mathematical functions
void demonstrateMathematicalFunctions() {
    std::cout << "\n=== Mathematical Functions Demo ===" << std::endl;
    
    // Area and perimeter calculations
    double length = 5.5, width = 3.2;
    std::cout << "Rectangle with length " << length << " and width " << width << ":" << std::endl;
    std::cout << "Area: " << calculateArea(length, width) << std::endl;
    std::cout << "Perimeter: " << calculatePerimeter(length, width) << std::endl;
    
    // Factorial calculation
    std::cout << "\nFactorial calculations:" << std::endl;
    for (int i = 1; i <= 6; ++i) {
        std::cout << i << "! = " << factorial(i) << std::endl;
    }
    
    // Prime number checking
    std::cout << "\nPrime number checking:" << std::endl;
    std::vector<int> numbers = {2, 3, 4, 5, 17, 25, 29, 100};
    for (int num : numbers) {
        std::cout << num << " is " << (isPrime(num) ? "" : "not ") << "prime" << std::endl;
    }
}

// Function to demonstrate input validation
void demonstrateInputValidation() {
    std::cout << "\n=== Input Validation Demo ===" << std::endl;
    
    int age = getValidInput("Enter your age (1-120): ", 1, 120);
    std::cout << "You entered: " << age << std::endl;
    
    int grade = getValidInput("Enter your grade (1-12): ", 1, 12);
    std::cout << "You entered: " << grade << std::endl;
}

// Function to demonstrate I/O operations
void demonstrateIOOperations() {
    std::cout << "\n=== I/O Operations Demo ===" << std::endl;
    
    std::string name;
    int age;
    double height;
    
    // Clear input buffer before reading string
    clearInputBuffer();
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter your age: ";
    std::cin >> age;
    
    std::cout << "Enter your height (in feet): ";
    std::cin >> height;
    
    std::cout << "\n=== Your Information ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Height: " << height << " feet" << std::endl;
}

// Function to demonstrate menu system
void demonstrateMenuSystem() {
    std::cout << "\n=== Menu System Demo ===" << std::endl;
    
    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::cout << "You selected: Addition" << std::endl;
                int a, b;
                std::cout << "Enter two numbers: ";
                std::cin >> a >> b;
                std::cout << "Sum: " << add(a, b) << std::endl;
                break;
            }
            case 2: {
                std::cout << "You selected: Multiplication" << std::endl;
                double x, y;
                std::cout << "Enter two numbers: ";
                std::cin >> x >> y;
                std::cout << "Product: " << multiply(x, y) << std::endl;
                break;
            }
            case 3: {
                std::cout << "You selected: Area Calculation" << std::endl;
                double length, width;
                std::cout << "Enter length: ";
                std::cin >> length;
                std::cout << "Enter width: ";
                std::cin >> width;
                std::cout << "Area: " << calculateArea(length, width) << std::endl;
                break;
            }
            case 4: {
                std::cout << "You selected: Prime Check" << std::endl;
                int num;
                std::cout << "Enter a number: ";
                std::cin >> num;
                std::cout << num << " is " << (isPrime(num) ? "" : "not ") << "prime" << std::endl;
                break;
            }
            case 5:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                break;
        }
        
        if (choice != 5) {
            std::cout << "\nPress Enter to continue...";
            clearInputBuffer();
            std::cin.get();
        }
        
    } while (choice != 5);
}

// Function to demonstrate function overloading concept (preview)
void demonstrateFunctionOverloading() {
    std::cout << "\n=== Function Overloading Preview ===" << std::endl;
    
    // Different ways to call similar functions
    std::cout << "Adding integers: " << add(10, 20) << std::endl;
    std::cout << "Multiplying doubles: " << multiply(2.5, 3.0) << std::endl;
    
    // Same function name, different parameters (concept)
    std::cout << "This demonstrates how functions can have the same name but different parameters." << std::endl;
}

// Function implementations

int add(int a, int b) {
    return a + b;
}

double multiply(double x, double y) {
    return x * y;
}

void greet(const std::string& name) {
    std::cout << "Hello, " << name << "! Welcome to functions!" << std::endl;
}

bool isEven(int number) {
    return number % 2 == 0;
}

int getValidInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cout << "Invalid input! Please enter a number." << std::endl;
            std::cin.clear();
            clearInputBuffer();
            continue;
        }
        
        if (value >= min && value <= max) {
            return value;
        }
        
        std::cout << "Invalid input! Please enter a value between " 
                  << min << " and " << max << std::endl;
    }
}

void displayMenu() {
    std::cout << "\n=== Function Demo Menu ===" << std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Multiplication" << std::endl;
    std::cout << "3. Area Calculation" << std::endl;
    std::cout << "4. Prime Check" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

double calculateArea(double length, double width) {
    return length * width;
}

double calculatePerimeter(double length, double width) {
    return 2 * (length + width);
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

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Utility functions for advanced examples
void demonstrateUtilityFunctions() {
    std::cout << "\n=== Utility Functions Demo ===" << std::endl;
    
    // Function to get maximum of two numbers
    auto getMax = [](int a, int b) { return (a > b) ? a : b; };
    
    std::cout << "Maximum of 15 and 25: " << getMax(15, 25) << std::endl;
    std::cout << "Maximum of 100 and 50: " << getMax(100, 50) << std::endl;
    
    // Function to calculate power
    auto power = [](int base, int exp) {
        int result = 1;
        for (int i = 0; i < exp; ++i) {
            result *= base;
        }
        return result;
    };
    
    std::cout << "2^5 = " << power(2, 5) << std::endl;
    std::cout << "3^3 = " << power(3, 3) << std::endl;
}

int main() {
    std::cout << "=== C++ Functions and Basic I/O Demo ===" << std::endl;
    std::cout << "This program demonstrates various aspects of functions and I/O.\n" << std::endl;
    
    // Demonstrate various function concepts
    demonstrateBasicFunctions();
    demonstrateParameterPassing();
    demonstrateMathematicalFunctions();
    demonstrateInputValidation();
    demonstrateIOOperations();
    demonstrateMenuSystem();
    demonstrateFunctionOverloading();
    demonstrateUtilityFunctions();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Functions allow code reuse and modularity" << std::endl;
    std::cout << "2. Parameters can be passed by value or reference" << std::endl;
    std::cout << "3. Functions can return values or be void" << std::endl;
    std::cout << "4. Input validation is important for robust programs" << std::endl;
    std::cout << "5. Clear function names and documentation improve readability" << std::endl;
    std::cout << "6. Functions help organize code into logical units" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o functions_io 04_Functions_and_Basic_IO.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o functions_io 04_Functions_and_Basic_IO.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 04_Functions_and_Basic_IO.cpp
 * 
 * Running:
 * ./functions_io (Linux/macOS)
 * functions_io.exe (Windows)
 */
