/*
 * Lesson 1.2: Basic Program Structure and Variables
 * 
 * This file demonstrates C++ program structure, data types,
 * variable declaration, initialization methods, and the auto keyword.
 */

#include <iostream>
#include <string>
#include <climits>
#include <iomanip>

// Global variable demonstration
int globalCounter = 0;

// Function to demonstrate variable scope
void demonstrateScope() {
    std::cout << "=== Variable Scope Demo ===" << std::endl;
    
    int localVar = 10;
    std::cout << "Local variable: " << localVar << std::endl;
    std::cout << "Global variable: " << globalCounter << std::endl;
    
    {
        int blockVar = 20;
        std::cout << "Block variable: " << blockVar << std::endl;
        
        // Shadowing: local variable hides global
        int globalCounter = 5;  // Local variable with same name
        std::cout << "Shadowed global variable: " << globalCounter << std::endl;
    }
    
    // blockVar is not accessible here
    std::cout << "Back to local scope - localVar: " << localVar << std::endl;
}

// Function to demonstrate different initialization methods
void demonstrateInitialization() {
    std::cout << "\n=== Initialization Methods Demo ===" << std::endl;
    
    // Copy initialization
    int age1 = 25;
    std::string name1 = "Alice";
    
    // Direct initialization
    int age2(30);   // Direct initialization, int age2 = 30;
    std::string name2("Bob");
    
    // Uniform initialization (preferred in modern C++)
    int age3{35};
    std::string name3{"Charlie"};
    
    // Multiple variables
    int x{10}, y{20}, z{30};
    
    std::cout << "Copy initialization: " << name1 << ", " << age1 << std::endl;
    std::cout << "Direct initialization: " << name2 << ", " << age2 << std::endl;
    std::cout << "Uniform initialization: " << name3 << ", " << age3 << std::endl;
    std::cout << "Multiple variables: x=" << x << ", y=" << y << ", z=" << z << std::endl;
}

// Function to demonstrate fundamental data types
void demonstrateDataTypes() {
    std::cout << "\n=== Fundamental Data Types Demo ===" << std::endl;
    
    // Integer types
    char grade = 'A';
    short shortNum = 100;   // short integer
    int intNum = 1000;
    long longNum = 100000L; // long integer
    long long veryLongNum = 1000000000LL;   // long long integer
    
    // Floating-point types
    float floatNum = 3.14f;
    double doubleNum = 3.14159;
    long double longDoubleNum = 3.141592653589793L;
    
    // Boolean type
    bool isStudent = true;
    bool isGraduated = false;
    
    // Display integer types
    std::cout << "Integer Types:" << std::endl;
    std::cout << "  char: " << grade << " (size: " << sizeof(char) << " bytes)" << std::endl;
    std::cout << "  short: " << shortNum << " (size: " << sizeof(short) << " bytes)" << std::endl;
    std::cout << "  int: " << intNum << " (size: " << sizeof(int) << " bytes)" << std::endl;
    std::cout << "  long: " << longNum << " (size: " << sizeof(long) << " bytes)" << std::endl;
    std::cout << "  long long: " << veryLongNum << " (size: " << sizeof(long long) << " bytes)" << std::endl;
    
    // Display floating-point types
    std::cout << "\nFloating-Point Types:" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  float: " << floatNum << " (size: " << sizeof(float) << " bytes)" << std::endl;
    std::cout << "  double: " << doubleNum << " (size: " << sizeof(double) << " bytes)" << std::endl;
    std::cout << "  long double: " << longDoubleNum << " (size: " << sizeof(long double) << " bytes)" << std::endl;
    
    // Display boolean type
    std::cout << "\nBoolean Types:" << std::endl;
    std::cout << "  isStudent: " << std::boolalpha << isStudent << std::endl;
    std::cout << "  isGraduated: " << isGraduated << std::endl;
}

// Function to demonstrate auto keyword
void demonstrateAuto() {
    std::cout << "\n=== Auto Keyword Demo ===" << std::endl;
    
    // Auto with different types
    auto name = std::string("David");      // Deduced as std::string
    auto age = 28;                         // Deduced as int
    auto salary = 75000.0;                 // Deduced as double
    auto isEmployed = true;                // Deduced as bool
    auto grade = 'B';                      // Deduced as char
    
    // Auto with complex types
    auto numbers = std::vector<int>{1, 2, 3, 4, 5};  // Deduced as std::vector<int>
    
    std::cout << "Auto deductions:" << std::endl;
    std::cout << "  name: " << name << " (type: std::string)" << std::endl;
    std::cout << "  age: " << age << " (type: int)" << std::endl;
    std::cout << "  salary: " << salary << " (type: double)" << std::endl;
    std::cout << "  isEmployed: " << std::boolalpha << isEmployed << " (type: bool)" << std::endl;
    std::cout << "  grade: " << grade << " (type: char)" << std::endl;
    
    std::cout << "\nVector elements: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate constants
void demonstrateConstants() {
    std::cout << "\n=== Constants Demo ===" << std::endl;
    
    // const keyword    runtime constants
    const int MAX_SIZE = 100;
    const double PI = 3.14159;
    const std::string APP_NAME = "C++ Learning";
    
    // constexpr keyword (C++11)    compile-time constants
    constexpr int BUFFER_SIZE = 256;
    constexpr double E = 2.71828;
    
    std::cout << "Constants:" << std::endl;
    std::cout << "  MAX_SIZE: " << MAX_SIZE << std::endl;
    std::cout << "  PI: " << PI << std::endl;
    std::cout << "  APP_NAME: " << APP_NAME << std::endl;
    std::cout << "  BUFFER_SIZE: " << BUFFER_SIZE << std::endl;
    std::cout << "  E: " << E << std::endl;
    
    // This would cause a compilation error:
    // MAX_SIZE = 200;  // Error: cannot assign to const variable
}

// Function to demonstrate type sizes and ranges
void demonstrateTypeInfo() {
    std::cout << "\n=== Type Information Demo ===" << std::endl;
    
    std::cout << "Type sizes (in bytes):" << std::endl;
    std::cout << "  char: " << sizeof(char) << std::endl;
    std::cout << "  short: " << sizeof(short) << std::endl;
    std::cout << "  int: " << sizeof(int) << std::endl;
    std::cout << "  long: " << sizeof(long) << std::endl;
    std::cout << "  long long: " << sizeof(long long) << std::endl;
    std::cout << "  float: " << sizeof(float) << std::endl;
    std::cout << "  double: " << sizeof(double) << std::endl;
    std::cout << "  bool: " << sizeof(bool) << std::endl;
    
    std::cout << "\nInteger ranges:" << std::endl;
    std::cout << "  char: " << CHAR_MIN << " to " << CHAR_MAX << std::endl;
    std::cout << "  short: " << SHRT_MIN << " to " << SHRT_MAX << std::endl;
    std::cout << "  int: " << INT_MIN << " to " << INT_MAX << std::endl;
    std::cout << "  long: " << LONG_MIN << " to " << LONG_MAX << std::endl;
}

// Function to demonstrate type conversion
void demonstrateTypeConversion() {
    std::cout << "\n=== Type Conversion Demo ===" << std::endl;
    
    int intVal = 42;
    double doubleVal = 3.14159;
    char charVal = 'A';
    
    // Implicit conversions
    double result1 = intVal + doubleVal;  // int promoted to double
    int result2 = charVal;                // char converted to int (ASCII value)
    
    std::cout << "Implicit conversions:" << std::endl;
    std::cout << "  int(" << intVal << ") + double(" << doubleVal << ") = " << result1 << std::endl;
    std::cout << "  char('" << charVal << "') as int = " << result2 << std::endl;
    
    // Explicit conversions
    int explicitInt = static_cast<int>(doubleVal);
    char explicitChar = static_cast<char>(intVal);
    
    std::cout << "\nExplicit conversions:" << std::endl;
    std::cout << "  static_cast<int>(" << doubleVal << ") = " << explicitInt << std::endl;
    std::cout << "  static_cast<char>(" << intVal << ") = '" << explicitChar << "'" << std::endl;
}

// Function to demonstrate best practices
void demonstrateBestPractices() {
    std::cout << "\n=== Best Practices Demo ===" << std::endl;
    
    // 1. Always initialize variables
    int initializedVar{100};  // Good: initialized
    // int uninitializedVar;  // Bad: uninitialized (commented out)
    
    // 2. Use meaningful names
    int studentAge{20};
    double courseGPA{3.8};
    bool hasScholarship{true};
    
    // 3. Use const when possible
    const int MAX_STUDENTS{100};
    const std::string SCHOOL_NAME{"University of C++"};
    
    // 4. Use uniform initialization
    std::vector<int> grades{85, 92, 78, 96, 88};
    
    std::cout << "Best practices applied:" << std::endl;
    std::cout << "  Student age: " << studentAge << std::endl;
    std::cout << "  Course GPA: " << courseGPA << std::endl;
    std::cout << "  Has scholarship: " << std::boolalpha << hasScholarship << std::endl;
    std::cout << "  Max students: " << MAX_STUDENTS << std::endl;
    std::cout << "  School: " << SCHOOL_NAME << std::endl;
    std::cout << "  Grades: ";
    for (const auto& grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== C++ Program Structure and Variables Demo ===" << std::endl;
    std::cout << "This program demonstrates basic C++ concepts.\n" << std::endl;
    
    // Demonstrate various concepts
    demonstrateScope();
    demonstrateInitialization();
    demonstrateDataTypes();
    demonstrateAuto();
    demonstrateConstants();
    demonstrateTypeInfo();
    demonstrateTypeConversion();
    demonstrateBestPractices();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. C++ programs have a specific structure with main() as entry point" << std::endl;
    std::cout << "2. Variables must be declared before use and should be initialized" << std::endl;
    std::cout << "3. C++ has strong typing with many fundamental data types" << std::endl;
    std::cout << "4. The auto keyword helps with type deduction in modern C++" << std::endl;
    std::cout << "5. Constants provide immutability and better code safety" << std::endl;
    std::cout << "6. Understanding variable scope and lifetime is crucial" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o variables_demo 02_Basic_Program_Structure_and_Variables.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o variables_demo 02_Basic_Program_Structure_and_Variables.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 02_Basic_Program_Structure_and_Variables.cpp
 * 
 * Running:
 * ./variables_demo (Linux/macOS)
 * variables_demo.exe (Windows)
 */
