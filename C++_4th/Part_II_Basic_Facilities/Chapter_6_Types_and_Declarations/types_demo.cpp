#include <iostream>
#include <limits>
#include <typeinfo>
#include <string>

// Demonstrates C++ fundamental types and their properties
int main() {
    std::cout << "C++ Types and Declarations Demonstration" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    // 1. Fundamental types
    std::cout << "\n1. FUNDAMENTAL TYPES:" << std::endl;
    
    // Integral types
    char c = 'A';
    signed char sc = -128;
    unsigned char uc = 255;
    short s = -32768;
    unsigned short us = 65535;
    int i = -2147483648;
    unsigned int ui = 4294967295U;
    long l = -9223372036854775808L;
    unsigned long ul = 18446744073709551615UL;
    long long ll = -9223372036854775808LL;
    unsigned long long ull = 18446744073709551615ULL;
    
    // Floating-point types
    float f = 3.14159f;
    double d = 3.141592653589793;
    long double ld = 3.141592653589793238L;
    
    // Boolean type
    bool b = true;
    
    // Void type (cannot have variables)
    // void v;  // This would cause a compile error
    
    // Display type information
    std::cout << "char: " << c << " (size: " << sizeof(char) << " bytes)" << std::endl;
    std::cout << "signed char: " << static_cast<int>(sc) << " (size: " << sizeof(signed char) << " bytes)" << std::endl;
    std::cout << "unsigned char: " << static_cast<int>(uc) << " (size: " << sizeof(unsigned char) << " bytes)" << std::endl;
    std::cout << "short: " << s << " (size: " << sizeof(short) << " bytes)" << std::endl;
    std::cout << "unsigned short: " << us << " (size: " << sizeof(unsigned short) << " bytes)" << std::endl;
    std::cout << "int: " << i << " (size: " << sizeof(int) << " bytes)" << std::endl;
    std::cout << "unsigned int: " << ui << " (size: " << sizeof(unsigned int) << " bytes)" << std::endl;
    std::cout << "long: " << l << " (size: " << sizeof(long) << " bytes)" << std::endl;
    std::cout << "unsigned long: " << ul << " (size: " << sizeof(unsigned long) << " bytes)" << std::endl;
    std::cout << "long long: " << ll << " (size: " << sizeof(long long) << " bytes)" << std::endl;
    std::cout << "unsigned long long: " << ull << " (size: " << sizeof(unsigned long long) << " bytes)" << std::endl;
    std::cout << "float: " << f << " (size: " << sizeof(float) << " bytes)" << std::endl;
    std::cout << "double: " << d << " (size: " << sizeof(double) << " bytes)" << std::endl;
    std::cout << "long double: " << ld << " (size: " << sizeof(long double) << " bytes)" << std::endl;
    std::cout << "bool: " << std::boolalpha << b << " (size: " << sizeof(bool) << " bytes)" << std::endl;
    
    // 2. Type limits
    std::cout << "\n2. TYPE LIMITS:" << std::endl;
    std::cout << "char range: " << static_cast<int>(std::numeric_limits<char>::min()) 
              << " to " << static_cast<int>(std::numeric_limits<char>::max()) << std::endl;
    std::cout << "int range: " << std::numeric_limits<int>::min() 
              << " to " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "float range: " << std::numeric_limits<float>::min() 
              << " to " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "double range: " << std::numeric_limits<double>::min() 
              << " to " << std::numeric_limits<double>::max() << std::endl;
    
    // 3. Type modifiers
    std::cout << "\n3. TYPE MODIFIERS:" << std::endl;
    
    const int const_int = 42;
    volatile int volatile_int = 100;
    const volatile int const_volatile_int = 200;
    
    std::cout << "const int: " << const_int << std::endl;
    std::cout << "volatile int: " << volatile_int << std::endl;
    std::cout << "const volatile int: " << const_volatile_int << std::endl;
    
    // 4. Initialization methods
    std::cout << "\n4. INITIALIZATION METHODS:" << std::endl;
    
    // Default initialization
    int default_init;
    std::cout << "Default initialization: " << default_init << " (uninitialized)" << std::endl;
    
    // Value initialization
    int value_init{};
    std::cout << "Value initialization: " << value_init << std::endl;
    
    // Direct initialization
    int direct_init(42);
    std::cout << "Direct initialization: " << direct_init << std::endl;
    
    // Copy initialization
    int copy_init = 42;
    std::cout << "Copy initialization: " << copy_init << std::endl;
    
    // List initialization
    int list_init{42};
    std::cout << "List initialization: " << list_init << std::endl;
    
    // 5. Type conversions
    std::cout << "\n5. TYPE CONVERSIONS:" << std::endl;
    
    int int_val = 42;
    double double_val = 3.14;
    
    // Implicit conversions
    double implicit_conversion = int_val;  // int to double
    std::cout << "Implicit conversion (int to double): " << implicit_conversion << std::endl;
    
    // Explicit conversions
    int explicit_conversion = static_cast<int>(double_val);
    std::cout << "Explicit conversion (double to int): " << explicit_conversion << std::endl;
    
    // C-style cast (not recommended)
    int c_style_cast = (int)double_val;
    std::cout << "C-style cast: " << c_style_cast << std::endl;
    
    // 6. Auto keyword (C++11)
    std::cout << "\n6. AUTO KEYWORD:" << std::endl;
    
    auto auto_int = 42;  // int
    auto auto_double = 3.14;  // double
    auto auto_string = std::string("Hello");  // std::string
    
    std::cout << "auto int: " << auto_int << " (type: " << typeid(auto_int).name() << ")" << std::endl;
    std::cout << "auto double: " << auto_double << " (type: " << typeid(auto_double).name() << ")" << std::endl;
    std::cout << "auto string: " << auto_string << " (type: " << typeid(auto_string).name() << ")" << std::endl;
    
    // 7. Decltype (C++11)
    std::cout << "\n7. DECLTYPE:" << std::endl;
    
    int x = 42;
    double y = 3.14;
    decltype(x) decltype_x = 100;  // Same type as x (int)
    decltype(x + y) decltype_sum = x + y;  // Type of expression (double)
    
    std::cout << "decltype(x): " << decltype_x << " (type: " << typeid(decltype_x).name() << ")" << std::endl;
    std::cout << "decltype(x + y): " << decltype_sum << " (type: " << typeid(decltype_sum).name() << ")" << std::endl;
    
    // 8. Constexpr (C++11)
    std::cout << "\n8. CONSTEXPR:" << std::endl;
    
    constexpr int constexpr_int = 42;
    constexpr double constexpr_double = 3.14159;
    
    std::cout << "constexpr int: " << constexpr_int << std::endl;
    std::cout << "constexpr double: " << constexpr_double << std::endl;
    
    // 9. Type aliases
    std::cout << "\n9. TYPE ALIASES:" << std::endl;
    
    typedef int Integer;
    using Double = double;
    
    Integer typedef_int = 42;
    Double using_double = 3.14;
    
    std::cout << "typedef int: " << typedef_int << std::endl;
    std::cout << "using double: " << using_double << std::endl;
    
    // 10. Type traits (C++11)
    std::cout << "\n10. TYPE TRAITS:" << std::endl;
    
    std::cout << "std::is_integral<int>: " << std::boolalpha << std::is_integral<int>::value << std::endl;
    std::cout << "std::is_floating_point<double>: " << std::boolalpha << std::is_floating_point<double>::value << std::endl;
    std::cout << "std::is_pointer<int*>: " << std::boolalpha << std::is_pointer<int*>::value << std::endl;
    std::cout << "std::is_const<const int>: " << std::boolalpha << std::is_const<const int>::value << std::endl;
    
    return 0;
}
