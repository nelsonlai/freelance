#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <bitset>

// Demonstrates C++ expressions and operators
int main() {
    std::cout << "C++ Expressions Demonstration" << std::endl;
    std::cout << "=============================" << std::endl;
    
    // 1. Arithmetic operators
    std::cout << "\n1. ARITHMETIC OPERATORS:" << std::endl;
    
    int a = 15, b = 4;
    double x = 15.0, y = 4.0;
    
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << " (integer division)" << std::endl;
    std::cout << "x / y = " << (x / y) << " (floating-point division)" << std::endl;
    std::cout << "a % b = " << (a % b) << std::endl;
    
    // 2. Unary operators
    std::cout << "\n2. UNARY OPERATORS:" << std::endl;
    
    int unary_var = 10;
    std::cout << "Original value: " << unary_var << std::endl;
    std::cout << "+unary_var = " << (+unary_var) << std::endl;
    std::cout << "-unary_var = " << (-unary_var) << std::endl;
    std::cout << "Value after unary operations: " << unary_var << std::endl;
    
    // 3. Increment and decrement operators
    std::cout << "\n3. INCREMENT AND DECREMENT OPERATORS:" << std::endl;
    
    int inc_var = 5;
    std::cout << "Original value: " << inc_var << std::endl;
    std::cout << "++inc_var = " << (++inc_var) << " (pre-increment)" << std::endl;
    std::cout << "Value after pre-increment: " << inc_var << std::endl;
    std::cout << "inc_var++ = " << (inc_var++) << " (post-increment)" << std::endl;
    std::cout << "Value after post-increment: " << inc_var << std::endl;
    std::cout << "--inc_var = " << (--inc_var) << " (pre-decrement)" << std::endl;
    std::cout << "Value after pre-decrement: " << inc_var << std::endl;
    std::cout << "inc_var-- = " << (inc_var--) << " (post-decrement)" << std::endl;
    std::cout << "Value after post-decrement: " << inc_var << std::endl;
    
    // 4. Assignment operators
    std::cout << "\n4. ASSIGNMENT OPERATORS:" << std::endl;
    
    int assign_var = 10;
    std::cout << "Original value: " << assign_var << std::endl;
    
    assign_var += 5;
    std::cout << "After += 5: " << assign_var << std::endl;
    
    assign_var -= 3;
    std::cout << "After -= 3: " << assign_var << std::endl;
    
    assign_var *= 2;
    std::cout << "After *= 2: " << assign_var << std::endl;
    
    assign_var /= 4;
    std::cout << "After /= 4: " << assign_var << std::endl;
    
    assign_var %= 3;
    std::cout << "After %= 3: " << assign_var << std::endl;
    
    // 5. Relational operators
    std::cout << "\n5. RELATIONAL OPERATORS:" << std::endl;
    
    int rel_a = 10, rel_b = 20, rel_c = 10;
    
    std::cout << "a = " << rel_a << ", b = " << rel_b << ", c = " << rel_c << std::endl;
    std::cout << "a == b: " << std::boolalpha << (rel_a == rel_b) << std::endl;
    std::cout << "a == c: " << std::boolalpha << (rel_a == rel_c) << std::endl;
    std::cout << "a != b: " << std::boolalpha << (rel_a != rel_b) << std::endl;
    std::cout << "a < b: " << std::boolalpha << (rel_a < rel_b) << std::endl;
    std::cout << "a > b: " << std::boolalpha << (rel_a > rel_b) << std::endl;
    std::cout << "a <= b: " << std::boolalpha << (rel_a <= rel_b) << std::endl;
    std::cout << "a >= b: " << std::boolalpha << (rel_a >= rel_b) << std::endl;
    
    // 6. Logical operators
    std::cout << "\n6. LOGICAL OPERATORS:" << std::endl;
    
    bool bool_a = true, bool_b = false;
    
    std::cout << "a = " << std::boolalpha << bool_a << ", b = " << bool_b << std::endl;
    std::cout << "a && b: " << (bool_a && bool_b) << std::endl;
    std::cout << "a || b: " << (bool_a || bool_b) << std::endl;
    std::cout << "!a: " << (!bool_a) << std::endl;
    std::cout << "!b: " << (!bool_b) << std::endl;
    
    // 7. Short-circuit evaluation
    std::cout << "\n7. SHORT-CIRCUIT EVALUATION:" << std::endl;
    
    auto side_effect = [](bool val) {
        std::cout << "Side effect function called with " << std::boolalpha << val << std::endl;
        return val;
    };
    
    std::cout << "true && side_effect(true): " << std::boolalpha << (true && side_effect(true)) << std::endl;
    std::cout << "false && side_effect(true): " << std::boolalpha << (false && side_effect(true)) << std::endl;
    std::cout << "true || side_effect(true): " << std::boolalpha << (true || side_effect(true)) << std::endl;
    std::cout << "false || side_effect(true): " << std::boolalpha << (false || side_effect(true)) << std::endl;
    
    // 8. Bitwise operators
    std::cout << "\n8. BITWISE OPERATORS:" << std::endl;
    
    int bit_a = 12;  // 1100 in binary
    int bit_b = 10;  // 1010 in binary
    
    std::cout << "a = " << bit_a << " (binary: " << std::bitset<8>(bit_a) << ")" << std::endl;
    std::cout << "b = " << bit_b << " (binary: " << std::bitset<8>(bit_b) << ")" << std::endl;
    std::cout << "a & b = " << (bit_a & bit_b) << " (binary: " << std::bitset<8>(bit_a & bit_b) << ")" << std::endl;
    std::cout << "a | b = " << (bit_a | bit_b) << " (binary: " << std::bitset<8>(bit_a | bit_b) << ")" << std::endl;
    std::cout << "a ^ b = " << (bit_a ^ bit_b) << " (binary: " << std::bitset<8>(bit_a ^ bit_b) << ")" << std::endl;
    std::cout << "~a = " << (~bit_a) << " (binary: " << std::bitset<8>(~bit_a) << ")" << std::endl;
    
    // 9. Shift operators
    std::cout << "\n9. SHIFT OPERATORS:" << std::endl;
    
    int shift_var = 8;  // 1000 in binary
    
    std::cout << "Original: " << shift_var << " (binary: " << std::bitset<8>(shift_var) << ")" << std::endl;
    std::cout << "Left shift by 1: " << (shift_var << 1) << " (binary: " << std::bitset<8>(shift_var << 1) << ")" << std::endl;
    std::cout << "Left shift by 2: " << (shift_var << 2) << " (binary: " << std::bitset<8>(shift_var << 2) << ")" << std::endl;
    std::cout << "Right shift by 1: " << (shift_var >> 1) << " (binary: " << std::bitset<8>(shift_var >> 1) << ")" << std::endl;
    std::cout << "Right shift by 2: " << (shift_var >> 2) << " (binary: " << std::bitset<8>(shift_var >> 2) << ")" << std::endl;
    
    // 10. Conditional operator (ternary)
    std::cout << "\n10. CONDITIONAL OPERATOR (TERNARY):" << std::endl;
    
    int cond_a = 15, cond_b = 10;
    std::string result = (cond_a > cond_b) ? "a is greater" : "b is greater or equal";
    std::cout << "a = " << cond_a << ", b = " << cond_b << " -> " << result << std::endl;
    
    int max_val = (cond_a > cond_b) ? cond_a : cond_b;
    std::cout << "Maximum value: " << max_val << std::endl;
    
    // 11. Comma operator
    std::cout << "\n11. COMMA OPERATOR:" << std::endl;
    
    int comma_result = (5, 10, 15);  // Returns the last expression
    std::cout << "Comma operator result: " << comma_result << std::endl;
    
    // Comma operator in for loop
    std::cout << "Comma operator in for loop: ";
    for (int i = 0, j = 10; i < 5; ++i, --j) {
        std::cout << "(" << i << "," << j << ") ";
    }
    std::cout << std::endl;
    
    // 12. Sizeof operator
    std::cout << "\n12. SIZEOF OPERATOR:" << std::endl;
    
    std::cout << "sizeof(int): " << sizeof(int) << " bytes" << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << " bytes" << std::endl;
    std::cout << "sizeof(char): " << sizeof(char) << " bytes" << std::endl;
    std::cout << "sizeof(bool): " << sizeof(bool) << " bytes" << std::endl;
    
    int array[10];
    std::cout << "sizeof(array[10]): " << sizeof(array) << " bytes" << std::endl;
    std::cout << "Number of elements: " << (sizeof(array) / sizeof(array[0])) << std::endl;
    
    // 13. Type casting
    std::cout << "\n13. TYPE CASTING:" << std::endl;
    
    double cast_double = 3.14159;
    int cast_int = static_cast<int>(cast_double);
    std::cout << "Original double: " << cast_double << std::endl;
    std::cout << "Casted to int: " << cast_int << std::endl;
    
    // C-style cast
    int c_style_cast = (int)cast_double;
    std::cout << "C-style cast: " << c_style_cast << std::endl;
    
    // 14. Operator precedence demonstration
    std::cout << "\n14. OPERATOR PRECEDENCE:" << std::endl;
    
    int prec_a = 2, prec_b = 3, prec_c = 4;
    
    std::cout << "a = " << prec_a << ", b = " << prec_b << ", c = " << prec_c << std::endl;
    std::cout << "a + b * c = " << (prec_a + prec_b * prec_c) << " (multiplication first)" << std::endl;
    std::cout << "(a + b) * c = " << ((prec_a + prec_b) * prec_c) << " (parentheses override)" << std::endl;
    std::cout << "a * b + c = " << (prec_a * prec_b + prec_c) << std::endl;
    std::cout << "a * (b + c) = " << (prec_a * (prec_b + prec_c)) << std::endl;
    
    // 15. Complex expressions
    std::cout << "\n15. COMPLEX EXPRESSIONS:" << std::endl;
    
    int complex_a = 5, complex_b = 3, complex_c = 2;
    bool complex_result = (complex_a > complex_b) && (complex_b > complex_c) || (complex_a == complex_c);
    std::cout << "(" << complex_a << " > " << complex_b << ") && (" << complex_b << " > " << complex_c << ") || (" << complex_a << " == " << complex_c << ") = " << std::boolalpha << complex_result << std::endl;
    
    // 16. Function calls in expressions
    std::cout << "\n16. FUNCTION CALLS IN EXPRESSIONS:" << std::endl;
    
    auto square = [](int x) { return x * x; };
    auto add = [](int a, int b) { return a + b; };
    
    int func_result = add(square(3), square(4));
    std::cout << "add(square(3), square(4)) = " << func_result << std::endl;
    
    // 17. String concatenation
    std::cout << "\n17. STRING CONCATENATION:" << std::endl;
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    std::string str3 = str1 + " " + str2;
    std::cout << "str1 + \" \" + str2 = " << str3 << std::endl;
    
    // 18. Array subscripting
    std::cout << "\n18. ARRAY SUBSCRIPTING:" << std::endl;
    
    int array_sub[5] = {10, 20, 30, 40, 50};
    std::cout << "array[2] = " << array_sub[2] << std::endl;
    std::cout << "array[1 + 2] = " << array_sub[1 + 2] << std::endl;
    
    // 19. Member access
    std::cout << "\n19. MEMBER ACCESS:" << std::endl;
    
    struct Point {
        int x, y;
        void display() const {
            std::cout << "Point(" << x << ", " << y << ")";
        }
    };
    
    Point p = {5, 10};
    std::cout << "p.x = " << p.x << ", p.y = " << p.y << std::endl;
    p.display();
    std::cout << std::endl;
    
    // 20. Operator overloading demonstration
    std::cout << "\n20. OPERATOR OVERLOADING DEMONSTRATION:" << std::endl;
    
    class Complex {
    private:
        double real, imag;
        
    public:
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}
        
        Complex operator+(const Complex& other) const {
            return Complex(real + other.real, imag + other.imag);
        }
        
        Complex operator*(const Complex& other) const {
            return Complex(real * other.real - imag * other.imag,
                          real * other.imag + imag * other.real);
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
            os << "(" << c.real << " + " << c.imag << "i)";
            return os;
        }
    };
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    Complex c3 = c1 + c2;
    Complex c4 = c1 * c2;
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    std::cout << "c1 * c2 = " << c4 << std::endl;
    
    std::cout << "\nExpressions demonstration completed!" << std::endl;
    return 0;
}
