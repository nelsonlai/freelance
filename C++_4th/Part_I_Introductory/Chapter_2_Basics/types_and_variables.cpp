#include <iostream>
#include <limits>
#include <string>

// Demonstrates fundamental types, variables, and their properties
int main() {
    std::cout << "C++ Fundamental Types Demonstration" << std::endl;
    std::cout << "====================================" << std::endl;
    
    // 1. Integer types
    std::cout << "\n1. INTEGER TYPES:" << std::endl;
    
    char c = 'A';
    short s = 100;
    int i = 1000;
    long l = 10000L;
    long long ll = 100000LL;
    
    std::cout << "char: " << c << " (size: " << sizeof(char) << " bytes)" << std::endl;
    std::cout << "short: " << s << " (size: " << sizeof(short) << " bytes)" << std::endl;
    std::cout << "int: " << i << " (size: " << sizeof(int) << " bytes)" << std::endl;
    std::cout << "long: " << l << " (size: " << sizeof(long) << " bytes)" << std::endl;
    std::cout << "long long: " << ll << " (size: " << sizeof(long long) << " bytes)" << std::endl;
    
    // 2. Floating-point types
    std::cout << "\n2. FLOATING-POINT TYPES:" << std::endl;
    
    float f = 3.14f;
    double d = 3.14159265359;
    long double ld = 3.141592653589793238L;
    
    std::cout << "float: " << f << " (size: " << sizeof(float) << " bytes)" << std::endl;
    std::cout << "double: " << d << " (size: " << sizeof(double) << " bytes)" << std::endl;
    std::cout << "long double: " << ld << " (size: " << sizeof(long double) << " bytes)" << std::endl;
    
    // 3. Boolean type
    std::cout << "\n3. BOOLEAN TYPE:" << std::endl;
    
    bool is_true = true;
    bool is_false = false;
    
    std::cout << "true: " << std::boolalpha << is_true << std::endl;
    std::cout << "false: " << std::boolalpha << is_false << std::endl;
    
    // 4. String type (from standard library)
    std::cout << "\n4. STRING TYPE:" << std::endl;
    
    std::string name = "Alice";
    std::string greeting = "Hello, " + name + "!";
    
    std::cout << "Name: " << name << std::endl;
    std::cout << "Greeting: " << greeting << std::endl;
    
    // 5. Type limits
    std::cout << "\n5. TYPE LIMITS:" << std::endl;
    std::cout << "int range: " << std::numeric_limits<int>::min() 
              << " to " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "double range: " << std::numeric_limits<double>::min() 
              << " to " << std::numeric_limits<double>::max() << std::endl;
    
    // 6. Type conversions
    std::cout << "\n6. TYPE CONVERSIONS:" << std::endl;
    
    int int_val = 42;
    double double_val = 3.14;
    
    // Implicit conversions
    double sum = int_val + double_val;  // int promoted to double
    std::cout << "42 + 3.14 = " << sum << std::endl;
    
    // Explicit conversions
    int truncated = static_cast<int>(double_val);
    std::cout << "3.14 truncated to int: " << truncated << std::endl;
    
    // 7. Constants
    std::cout << "\n7. CONSTANTS:" << std::endl;
    
    const int MAX_SIZE = 100;
    const double PI = 3.14159;
    constexpr int ARRAY_SIZE = 10;  // Compile-time constant

    MAX_SIZE = 200; // This would cause a compile error
    ARRAY_SIZE = 20; // This would cause a compile error
    
    std::cout << "MAX_SIZE: " << MAX_SIZE << std::endl;
    std::cout << "PI: " << PI << std::endl;
    std::cout << "ARRAY_SIZE: " << ARRAY_SIZE << std::endl;
    
    return 0;
}
