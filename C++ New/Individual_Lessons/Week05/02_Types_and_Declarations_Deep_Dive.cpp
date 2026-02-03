/*
 * Lesson 5.2: Types and Declarations Deep Dive
 * 
 * This file demonstrates fundamental C++ types, type conversions,
 * type aliases, and type deduction.
 */

#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <limits>
#include <chrono>
#include <string>

// Function to demonstrate fundamental types
void demonstrateFundamentalTypes() {
    std::cout << "=== Fundamental Types Demonstration ===" << std::endl;
    
    // Integer types
    std::cout << "Integer types:" << std::endl;
    std::cout << "char: " << sizeof(char) << " bytes, range: " 
              << (int)std::numeric_limits<char>::min() << " to " 
              << (int)std::numeric_limits<char>::max() << std::endl;
    
    std::cout << "short: " << sizeof(short) << " bytes, range: " 
              << std::numeric_limits<short>::min() << " to " 
              << std::numeric_limits<short>::max() << std::endl;
    
    std::cout << "int: " << sizeof(int) << " bytes, range: " 
              << std::numeric_limits<int>::min() << " to " 
              << std::numeric_limits<int>::max() << std::endl;
    
    std::cout << "long: " << sizeof(long) << " bytes, range: " 
              << std::numeric_limits<long>::min() << " to " 
              << std::numeric_limits<long>::max() << std::endl;
    
    std::cout << "long long: " << sizeof(long long) << " bytes, range: " 
              << std::numeric_limits<long long>::min() << " to " 
              << std::numeric_limits<long long>::max() << std::endl;
    
    // Floating-point types
    std::cout << "
Floating-point types:" << std::endl;
    std::cout << "float: " << sizeof(float) << " bytes, precision: " 
              << std::numeric_limits<float>::digits10 << " digits" << std::endl;
    
    std::cout << "double: " << sizeof(double) << " bytes, precision: " 
              << std::numeric_limits<double>::digits10 << " digits" << std::endl;
    
    std::cout << "long double: " << sizeof(long double) << " bytes, precision: " 
              << std::numeric_limits<long double>::digits10 << " digits" << std::endl;
    
    // Character types
    std::cout << "
Character types:" << std::endl;
    std::cout << "char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "wchar_t: " << sizeof(wchar_t) << " bytes" << std::endl;
    std::cout << "char16_t: " << sizeof(char16_t) << " bytes" << std::endl;
    std::cout << "char32_t: " << sizeof(char32_t) << " bytes" << std::endl;
    
    // Boolean type
    std::cout << "
Boolean type:" << std::endl;
    std::cout << "bool: " << sizeof(bool) << " bytes" << std::endl;
    std::cout << "true: " << true << ", false: " << false << std::endl;
}

// Function to demonstrate type conversions
void demonstrateTypeConversions() {
    std::cout << "
=== Type Conversions Demonstration ===" << std::endl;
    
    // Implicit conversions
    std::cout << "Implicit conversions:" << std::endl;
    char c = 'A';
    int i = c;  // char to int promotion
    std::cout << "char 'A' = " << (int)c << ", int = " << i << std::endl;
    
    float f = 3.14f;
    double d = f;  // float to double promotion
    std::cout << "float = " << f << ", double = " << d << std::endl;
    
    // Explicit conversions
    std::cout << "
Explicit conversions:" << std::endl;
    double pi = 3.14159;
    
    // C-style cast
    int int_pi = (int)pi;
    std::cout << "C-style cast: " << pi << " -> " << int_pi << std::endl;
    
    // Static cast
    int static_pi = static_cast<int>(pi);
    std::cout << "Static cast: " << pi << " -> " << static_pi << std::endl;
    
    // Const cast
    const int const_val = 42;
    int* mutable_ptr = const_cast<int*>(&const_val);
    *mutable_ptr = 100;
    std::cout << "Const cast: " << const_val << " (but modified to " << *mutable_ptr << ")" << std::endl;
    
    // Reinterpret cast
    int value = 0x12345678;
    char* char_ptr = reinterpret_cast<char*>(&value);
    std::cout << "Reinterpret cast: int " << std::hex << value << " -> char* " << (int)*char_ptr << std::dec << std::endl;
}

// Function to demonstrate type aliases
void demonstrateTypeAliases() {
    std::cout << "
=== Type Aliases Demonstration ===" << std::endl;
    
    // Traditional typedef
    typedef std::vector<int> IntVector;
    typedef std::map<std::string, int> StringIntMap;
    
    // Modern using aliases
    using StringVector = std::vector<std::string>;
    using IntPair = std::pair<int, int>;
    using FunctionPtr = int (*)(int, int);
    
    // Use the aliases
    IntVector numbers = {1, 2, 3, 4, 5};
    StringIntMap word_count = {{"hello", 1}, {"world", 2}};
    StringVector words = {"apple", "banana", "cherry"};
    IntPair coordinates = {10, 20};
    
    std::cout << "IntVector size: " << numbers.size() << std::endl;
    std::cout << "StringIntMap size: " << word_count.size() << std::endl;
    std::cout << "StringVector size: " << words.size() << std::endl;
    std::cout << "IntPair: (" << coordinates.first << ", " << coordinates.second << ")" << std::endl;
    
    // Function pointer example
    auto add_function = [](int a, int b) -> int { return a + b; };
    FunctionPtr func_ptr = add_function;
    std::cout << "Function pointer result: " << func_ptr(5, 3) << std::endl;
}

// Function to demonstrate const and volatile
void demonstrateConstVolatile() {
    std::cout << "
=== Const and Volatile Demonstration ===" << std::endl;
    
    // Const examples
    const int immutable = 42;
    std::cout << "Immutable value: " << immutable << std::endl;
    
    int mutable_var = 100;
    const int* ptr_to_const = &mutable_var;
    std::cout << "Pointer to const: " << *ptr_to_const << std::endl;
    
    int* const const_ptr = &mutable_var;
    *const_ptr = 200;
    std::cout << "Const pointer (modified value): " << *const_ptr << std::endl;
    
    const int* const both_const = &mutable_var;
    std::cout << "Const pointer to const: " << *both_const << std::endl;
    
    // Volatile example
    volatile int counter = 0;
    std::cout << "Volatile counter: " << counter << std::endl;
    
    // Const methods
    class ConstDemo {
    private:
        int value_;
    public:
        ConstDemo(int v) : value_(v) {}
        
        int getValue() const {
            return value_;  // Can't modify members in const method
        }
        
        void setValue(int v) {
            value_ = v;  // Can modify in non-const method
        }
    };
    
    const ConstDemo const_obj(42);
    std::cout << "Const object value: " << const_obj.getValue() << std::endl;
    // const_obj.setValue(100);  // Error: cannot call non-const method
}

// Function to demonstrate auto and decltype
void demonstrateAutoDecltype() {
    std::cout << "
=== Auto and Decltype Demonstration ===" << std::endl;
    
    // Auto type deduction
    auto int_val = 42;
    auto double_val = 3.14159;
    auto string_val = std::string("Hello, World!");
    auto vector_val = std::vector<int>{1, 2, 3, 4, 5};
    
    std::cout << "Auto deduction:" << std::endl;
    std::cout << "int_val: " << typeid(int_val).name() << " = " << int_val << std::endl;
    std::cout << "double_val: " << typeid(double_val).name() << " = " << double_val << std::endl;
    std::cout << "string_val: " << typeid(string_val).name() << " = " << string_val << std::endl;
    std::cout << "vector_val: " << typeid(vector_val).name() << " size = " << vector_val.size() << std::endl;
    
    // Decltype examples
    int x = 42;
    decltype(x) y = x;  // y is int
    decltype(x + 3.14) z;  // z is double
    
    std::cout << "
Decltype:" << std::endl;
    std::cout << "decltype(x): " << typeid(y).name() << std::endl;
    std::cout << "decltype(x + 3.14): " << typeid(z).name() << std::endl;
    
    // Auto with containers
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
    
    std::cout << "
Auto with containers:" << std::endl;
    for (const auto& pair : scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Auto with lambdas
    auto lambda = [](int a, int b) -> int { return a * b; };
    std::cout << "Lambda result: " << lambda(5, 6) << std::endl;
}

// Function to demonstrate type safety
void demonstrateTypeSafety() {
    std::cout << "
=== Type Safety Demonstration ===" << std::endl;
    
    // Type-safe function
    auto safeAdd = [](const int& a, const int& b) -> int {
        return a + b;
    };
    
    int result = safeAdd(10, 20);
    std::cout << "Safe addition: " << result << std::endl;
    
    // Type-safe container operations
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Type-safe iteration
    for (const auto& num : numbers) {
        std::cout << "Number: " << num << std::endl;
    }
    
    // Type-safe access
    if (!numbers.empty()) {
        int first = numbers.front();
        int last = numbers.back();
        std::cout << "First: " << first << ", Last: " << last << std::endl;
    }
    
    // Type-safe function pointer
    using MathFunction = std::function<int(int, int)>;
    
    MathFunction add = [](int a, int b) { return a + b; };
    MathFunction multiply = [](int a, int b) { return a * b; };
    
    std::cout << "Add: " << add(5, 3) << std::endl;
    std::cout << "Multiply: " << multiply(5, 3) << std::endl;
}

// Function to demonstrate performance implications
void demonstratePerformance() {
    std::cout << "
=== Performance Demonstration ===" << std::endl;
    
    const int iterations = 1000000;
    
    // Integer arithmetic
    auto start = std::chrono::high_resolution_clock::now();
    
    int sum = 0;
    for (int i = 0; i < iterations; ++i) {
        sum += i;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto int_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Integer arithmetic time: " << int_time.count() << " microseconds" << std::endl;
    
    // Floating-point arithmetic
    start = std::chrono::high_resolution_clock::now();
    
    double sum_double = 0.0;
    for (int i = 0; i < iterations; ++i) {
        sum_double += i;
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto double_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Double arithmetic time: " << double_time.count() << " microseconds" << std::endl;
    
    // Performance comparison
    std::cout << "Floating-point overhead: " << (double)double_time.count() / int_time.count() << "x" << std::endl;
}

int main() {
    std::cout << "=== Types and Declarations Deep Dive Demonstration ===" << std::endl;
    std::cout << "This program demonstrates fundamental C++ types, type conversions,
"
              << "type aliases, and type deduction.
" << std::endl;
    
    // Demonstrate various type concepts
    demonstrateFundamentalTypes();
    demonstrateTypeConversions();
    demonstrateTypeAliases();
    demonstrateConstVolatile();
    demonstrateAutoDecltype();
    demonstrateTypeSafety();
    demonstratePerformance();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. Choose appropriate types based on requirements" << std::endl;
    std::cout << "2. Use explicit conversions to avoid surprises" << std::endl;
    std::cout << "3. Type aliases improve code readability" << std::endl;
    std::cout << "4. Const correctness prevents accidental modifications" << std::endl;
    std::cout << "5. Auto and decltype simplify type declarations" << std::endl;
    std::cout << "6. Type safety prevents runtime errors" << std::endl;
    std::cout << "7. Different types have different performance characteristics" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o types_deep_dive 02_Types_and_Declarations_Deep_Dive.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o types_deep_dive 02_Types_and_Declarations_Deep_Dive.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Types_and_Declarations_Deep_Dive.cpp
 * 
 * Running:
 * ./types_deep_dive (Linux/macOS)
 * types_deep_dive.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for auto and decltype.
 * C++17 is recommended for best type system support.
 * 
 * Type System Notes:
 * - Type sizes may vary between platforms
 * - Use std::numeric_limits for type information
 * - Prefer explicit conversions over implicit ones
 * - Const correctness is essential for maintainable code
 */