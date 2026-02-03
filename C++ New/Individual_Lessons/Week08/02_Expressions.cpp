/*
 * Lesson 8.2: Expressions
 * 
 * This file demonstrates expression evaluation, precedence,
 * type conversions, and operator overloading.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// Custom class for operator overloading demonstration
class Complex {
private:
    double real_, imag_;
    
public:
    Complex(double real = 0.0, double imag = 0.0) : real_(real), imag_(imag) {}
    
    // Getter methods
    double real() const { return real_; }
    double imag() const { return imag_; }
    
    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(
            real_ * other.real_ - imag_ * other.imag_,
            real_ * other.imag_ + imag_ * other.real_
        );
    }
    
    // Comparison operators
    bool operator==(const Complex& other) const {
        return real_ == other.real_ && imag_ == other.imag_;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Assignment operators
    Complex& operator+=(const Complex& other) {
        real_ += other.real_;
        imag_ += other.imag_;
        return *this;
    }
    
    Complex& operator*=(const Complex& other) {
        double new_real = real_ * other.real_ - imag_ * other.imag_;
        double new_imag = real_ * other.imag_ + imag_ * other.real_;
        real_ = new_real;
        imag_ = new_imag;
        return *this;
    }
    
    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real_;
        if (c.imag_ >= 0) {
            os << " + " << c.imag_ << "i";
        } else {
            os << " - " << -c.imag_ << "i";
        }
        return os;
    }
    
    // Magnitude calculation
    double magnitude() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }
};

// Function to demonstrate basic expressions
void demonstrateBasicExpressions() {
    std::cout << "=== Basic Expressions ===" << std::endl;
    
    int x = 10, y = 5;
    
    // Arithmetic expressions
    std::cout << "Arithmetic expressions:" << std::endl;
    std::cout << "x + y = " << (x + y) << std::endl;
    std::cout << "x - y = " << (x - y) << std::endl;
    std::cout << "x * y = " << (x * y) << std::endl;
    std::cout << "x / y = " << (x / y) << std::endl;
    std::cout << "x % y = " << (x % y) << std::endl;
    
    // Unary expressions
    std::cout << "\nUnary expressions:" << std::endl;
    std::cout << "+x = " << (+x) << std::endl;
    std::cout << "-x = " << (-x) << std::endl;
    std::cout << "++x = " << (++x) << std::endl;
    std::cout << "x++ = " << (x++) << std::endl;
    std::cout << "x after post-increment = " << x << std::endl;
    
    // Relational expressions
    std::cout << "\nRelational expressions:" << std::endl;
    std::cout << "x > y = " << (x > y) << std::endl;
    std::cout << "x < y = " << (x < y) << std::endl;
    std::cout << "x >= y = " << (x >= y) << std::endl;
    std::cout << "x <= y = " << (x <= y) << std::endl;
    std::cout << "x == y = " << (x == y) << std::endl;
    std::cout << "x != y = " << (x != y) << std::endl;
    
    // Logical expressions
    std::cout << "\nLogical expressions:" << std::endl;
    bool a = true, b = false;
    std::cout << "a && b = " << (a && b) << std::endl;
    std::cout << "a || b = " << (a || b) << std::endl;
    std::cout << "!a = " << (!a) << std::endl;
    std::cout << "!b = " << (!b) << std::endl;
}

// Function to demonstrate operator precedence
void demonstrateOperatorPrecedence() {
    std::cout << "\n=== Operator Precedence ===" << std::endl;
    
    int a = 2, b = 3, c = 4, d = 5;
    
    // Precedence examples
    std::cout << "a + b * c = " << (a + b * c) << std::endl;
    std::cout << "(a + b) * c = " << ((a + b) * c) << std::endl;
    std::cout << "a * b + c * d = " << (a * b + c * d) << std::endl;
    std::cout << "(a * b) + (c * d) = " << ((a * b) + (c * d)) << std::endl;
    
    // Complex precedence
    std::cout << "\nComplex precedence:" << std::endl;
    std::cout << "a + b * c - d = " << (a + b * c - d) << std::endl;
    std::cout << "(a + b) * (c - d) = " << ((a + b) * (c - d)) << std::endl;
    std::cout << "a * b / c + d = " << (a * b / c + d) << std::endl;
    std::cout << "a * (b / c) + d = " << (a * (b / c) + d) << std::endl;
    
    // Logical precedence
    std::cout << "\nLogical precedence:" << std::endl;
    bool x = true, y = false, z = true;
    std::cout << "x && y || z = " << (x && y || z) << std::endl;
    std::cout << "x && (y || z) = " << (x && (y || z)) << std::endl;
    std::cout << "(x && y) || z = " << ((x && y) || z) << std::endl;
    
    // Assignment precedence
    std::cout << "\nAssignment precedence:" << std::endl;
    int result = 0;
    result = a + b * c;
    std::cout << "result = a + b * c = " << result << std::endl;
    
    result += a * b;
    std::cout << "result += a * b = " << result << std::endl;
}

// Function to demonstrate type conversions
void demonstrateTypeConversions() {
    std::cout << "\n=== Type Conversions ===" << std::endl;
    
    // Implicit conversions
    int int_val = 42;
    double double_val = 3.14159;
    char char_val = 'A';
    
    std::cout << "Implicit conversions:" << std::endl;
    std::cout << "int + double = " << (int_val + double_val) << std::endl;
    std::cout << "char to int = " << static_cast<int>(char_val) << std::endl;
    std::cout << "double to int = " << static_cast<int>(double_val) << std::endl;
    
    // Explicit conversions
    std::cout << "\nExplicit conversions:" << std::endl;
    double pi = 3.14159;
    int truncated = static_cast<int>(pi);
    std::cout << "pi = " << pi << ", truncated = " << truncated << std::endl;
    
    // C-style cast
    int c_style = (int)pi;
    std::cout << "C-style cast: " << c_style << std::endl;
    
    // Functional cast
    int func_cast = int(pi);
    std::cout << "Functional cast: " << func_cast << std::endl;
    
    // Const cast example
    const int const_val = 100;
    int* mutable_ptr = const_cast<int*>(&const_val);
    *mutable_ptr = 200;
    std::cout << "Const cast: " << *mutable_ptr << std::endl;
    
    // Reinterpret cast example
    int value = 0x12345678;
    char* char_ptr = reinterpret_cast<char*>(&value);
    std::cout << "Reinterpret cast: " << std::hex << static_cast<int>(*char_ptr) << std::dec << std::endl;
}

// Function to demonstrate short-circuit evaluation
void demonstrateShortCircuitEvaluation() {
    std::cout << "\n=== Short-Circuit Evaluation ===" << std::endl;
    
    // Logical AND short-circuit
    std::cout << "Logical AND short-circuit:" << std::endl;
    int x = 0;
    bool result1 = (x > 0) && (++x > 0);
    std::cout << "x = " << x << ", result = " << result1 << std::endl;
    
    x = 5;
    bool result2 = (x > 0) && (++x > 0);
    std::cout << "x = " << x << ", result = " << result2 << std::endl;
    
    // Logical OR short-circuit
    std::cout << "\nLogical OR short-circuit:" << std::endl;
    x = 10;
    bool result3 = (x < 5) || (++x < 15);
    std::cout << "x = " << x << ", result = " << result3 << std::endl;
    
    x = 2;
    bool result4 = (x < 5) || (++x < 15);
    std::cout << "x = " << x << ", result = " << result4 << std::endl;
    
    // Practical example with null pointer check
    std::cout << "\nPractical example with null pointer check:" << std::endl;
    int* ptr = nullptr;
    bool safe_check = (ptr != nullptr) && (*ptr > 0);
    std::cout << "Safe check with null pointer: " << safe_check << std::endl;
    
    int val = 42;
    ptr = &val;
    bool safe_check2 = (ptr != nullptr) && (*ptr > 0);
    std::cout << "Safe check with valid pointer: " << safe_check2 << std::endl;
}

// Function to demonstrate operator overloading
void demonstrateOperatorOverloading() {
    std::cout << "\n=== Operator Overloading ===" << std::endl;
    
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    
    // Arithmetic operations
    Complex sum = c1 + c2;
    std::cout << "c1 + c2 = " << sum << std::endl;
    
    Complex diff = c1 - c2;
    std::cout << "c1 - c2 = " << diff << std::endl;
    
    Complex product = c1 * c2;
    std::cout << "c1 * c2 = " << product << std::endl;
    
    // Comparison operations
    std::cout << "c1 == c2 = " << (c1 == c2) << std::endl;
    std::cout << "c1 != c2 = " << (c1 != c2) << std::endl;
    
    // Assignment operations
    Complex c3 = c1;
    c3 += c2;
    std::cout << "c3 += c2 = " << c3 << std::endl;
    
    Complex c4 = c1;
    c4 *= c2;
    std::cout << "c4 *= c2 = " << c4 << std::endl;
    
    // Magnitude calculation
    std::cout << "|c1| = " << c1.magnitude() << std::endl;
    std::cout << "|c2| = " << c2.magnitude() << std::endl;
}

// Function to demonstrate expression types
void demonstrateExpressionTypes() {
    std::cout << "\n=== Expression Types ===" << std::endl;
    
    // Integer expressions
    int x = 5, y = 3;
    std::cout << "Integer expression: " << (x + y) << std::endl;
    
    // Floating-point expressions
    double a = 3.14, b = 2.71;
    std::cout << "Double expression: " << (a * b) << std::endl;
    
    // Boolean expressions
    bool flag1 = true, flag2 = false;
    std::cout << "Boolean expression: " << (flag1 && !flag2) << std::endl;
    
    // String expressions
    std::string str1 = "Hello", str2 = "World";
    std::cout << "String expression: " << (str1 + " " + str2) << std::endl;
    
    // Mixed type expressions
    std::cout << "Mixed type: " << (x + a) << std::endl;
    
    // Conditional expressions
    int max_val = (x > y) ? x : y;
    std::cout << "Conditional expression: " << max_val << std::endl;
    
    // Function call expressions
    std::cout << "Function call expression: " << std::max(x, y) << std::endl;
    
    // Array subscript expressions
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "Array subscript expression: " << arr[2] << std::endl;
    
    // Member access expressions
    Complex c(1.0, 2.0);
    std::cout << "Member access expression: " << c.real() << std::endl;
}

// Function to demonstrate expression optimization
void demonstrateExpressionOptimization() {
    std::cout << "\n=== Expression Optimization ===" << std::endl;
    
    // Common subexpression elimination
    int x = 5, y = 3, z = 7;
    
    // Inefficient: computes (x + y) twice
    int result1 = (x + y) * (x + y) + (x + y);
    std::cout << "Inefficient: " << result1 << std::endl;
    
    // Efficient: computes (x + y) once
    int temp = x + y;
    int result2 = temp * temp + temp;
    std::cout << "Efficient: " << result2 << std::endl;
    
    // Loop optimization
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Inefficient: calls size() in every iteration
    std::cout << "Inefficient loop:" << std::endl;
    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Efficient: calls size() once
    std::cout << "Efficient loop:" << std::endl;
    size_t size = numbers.size();
    for (size_t i = 0; i < size; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop (most efficient)
    std::cout << "Range-based for loop:" << std::endl;
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate expression errors
void demonstrateExpressionErrors() {
    std::cout << "\n=== Common Expression Errors ===" << std::endl;
    
    std::cout << "Common errors to avoid:" << std::endl;
    std::cout << "1. Integer division: 5 / 2 = " << (5 / 2) << std::endl;
    std::cout << "2. Floating-point division: 5.0 / 2 = " << (5.0 / 2) << std::endl;
    std::cout << "3. Modulo with floating-point: 5.5 % 2 = " << std::fmod(5.5, 2) << std::endl;
    
    // Overflow example
    std::cout << "\nOverflow example:" << std::endl;
    int max_int = std::numeric_limits<int>::max();
    std::cout << "max_int = " << max_int << std::endl;
    std::cout << "max_int + 1 = " << (max_int + 1) << " (overflow!)" << std::endl;
    
    // Underflow example
    std::cout << "\nUnderflow example:" << std::endl;
    int min_int = std::numeric_limits<int>::min();
    std::cout << "min_int = " << min_int << std::endl;
    std::cout << "min_int - 1 = " << (min_int - 1) << " (underflow!)" << std::endl;
    
    // Precision loss
    std::cout << "\nPrecision loss example:" << std::endl;
    double precise = 0.1 + 0.2;
    std::cout << "0.1 + 0.2 = " << precise << std::endl;
    std::cout << "Expected: 0.3" << std::endl;
}

// Function to demonstrate complex expressions
void demonstrateComplexExpressions() {
    std::cout << "\n=== Complex Expressions ===" << std::endl;
    
    // Mathematical expression
    double x = 2.0, y = 3.0, z = 4.0;
    double result = std::sqrt(x * x + y * y + z * z);
    std::cout << "sqrt(x² + y² + z²) = " << result << std::endl;
    
    // Conditional expression with function calls
    int a = 10, b = 20;
    int max_val = (a > b) ? std::abs(a) : std::abs(b);
    std::cout << "max(|a|, |b|) = " << max_val << std::endl;
    
    // String expression with conditional
    std::string status = (a > b) ? "greater" : "less or equal";
    std::cout << "a is " << status << " than b" << std::endl;
    
    // Array expression with conditional
    int arr[] = {1, 2, 3, 4, 5};
    int index = (a > b) ? 0 : 2;
    std::cout << "arr[index] = " << arr[index] << std::endl;
    
    // Nested function calls
    double nested_result = std::sin(std::cos(std::atan(1.0)));
    std::cout << "sin(cos(atan(1))) = " << nested_result << std::endl;
}

int main() {
    std::cout << "=== Expressions Demonstration ===" << std::endl;
    std::cout << "This program demonstrates expression evaluation, precedence,\n"
              << "type conversions, and operator overloading.\n" << std::endl;
    
    // Demonstrate various expression concepts
    demonstrateBasicExpressions();
    demonstrateOperatorPrecedence();
    demonstrateTypeConversions();
    demonstrateShortCircuitEvaluation();
    demonstrateOperatorOverloading();
    demonstrateExpressionTypes();
    demonstrateExpressionOptimization();
    demonstrateExpressionErrors();
    demonstrateComplexExpressions();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Expressions compute values using operators and operands" << std::endl;
    std::cout << "2. Operator precedence determines evaluation order" << std::endl;
    std::cout << "3. Type conversions can be implicit or explicit" << std::endl;
    std::cout << "4. Short-circuit evaluation optimizes logical expressions" << std::endl;
    std::cout << "5. Operator overloading allows custom behavior for user-defined types" << std::endl;
    std::cout << "6. Expression optimization improves performance" << std::endl;
    std::cout << "7. Be aware of common expression errors like overflow and precision loss" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o expressions 02_Expressions.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o expressions 02_Expressions.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Expressions.cpp
 * 
 * Running:
 * ./expressions (Linux/macOS)
 * expressions.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best expression support.
 * 
 * Expression Notes:
 * - Use parentheses to clarify precedence
 * - Be aware of type conversions
 * - Understand short-circuit evaluation
 * - Use operator overloading judiciously
 * - Optimize expressions for performance
 * - Handle overflow and precision issues
 */
