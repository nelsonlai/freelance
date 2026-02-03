/*
 * Lesson 12.1: Templates Fundamentals
 * 
 * This file demonstrates function templates, class templates,
 * template instantiation, specialization, and metaprogramming basics.
 */

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>
#include <memory>
#include <cmath>

// Example 1: Function Templates
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

template<typename T, typename U = T>
T multiply(T a, U b) {
    return a * b;
}

// Function template with multiple parameters
template<typename T, typename U, typename V>
auto calculate(T a, U b, V c) -> decltype(a + b + c) {
    return a + b + c;
}

// Function template specialization
template<typename T>
void print(T value) {
    std::cout << "Generic: " << value << std::endl;
}

template<>
void print<int>(int value) {
    std::cout << "Integer: " << value << std::endl;
}

template<>
void print<double>(double value) {
    std::cout << "Double: " << value << std::endl;
}

template<>
void print<std::string>(std::string value) {
    std::cout << "String: " << value << std::endl;
}

// Example 2: Class Templates
template<typename T>
class Stack {
private:
    std::vector<T> data_;
    
public:
    void push(const T& item) {
        data_.push_back(item);
    }
    
    void pop() {
        if (!data_.empty()) {
            data_.pop_back();
        }
    }
    
    T& top() {
        if (data_.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_.back();
    }
    
    const T& top() const {
        if (data_.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_.back();
    }
    
    bool empty() const {
        return data_.empty();
    }
    
    size_t size() const {
        return data_.size();
    }
    
    void display() const {
        std::cout << "Stack contents: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    // Template member function
    template<typename U>
    Stack<U> transform(U (*func)(const T&)) const {
        Stack<U> result;
        for (const auto& item : data_) {
            result.push(func(item));
        }
        return result;
    }
};

// Class template with multiple parameters
template<typename T, typename U>
class Pair {
private:
    T first_;
    U second_;
    
public:
    Pair(const T& first, const U& second) 
        : first_(first), second_(second) {}
    
    T& first() { return first_; }
    const T& first() const { return first_; }
    
    U& second() { return second_; }
    const U& second() const { return second_; }
    
    void display() const {
        std::cout << "Pair(" << first_ << ", " << second_ << ")" << std::endl;
    }
    
    // Template member function
    template<typename V>
    Pair<V, U> transformFirst(V (*func)(const T&)) const {
        return Pair<V, U>(func(first_), second_);
    }
    
    // Template member function with lambda
    template<typename F>
    auto apply(F func) -> decltype(func(first_, second_)) {
        return func(first_, second_);
    }
};

// Example 3: Template Metaprogramming
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

template<int N>
struct Fibonacci {
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static const int value = 0;
};

template<>
struct Fibonacci<1> {
    static const int value = 1;
};

// Power calculation at compile time
template<int Base, int Exponent>
struct Power {
    static const int value = Base * Power<Base, Exponent - 1>::value;
};

template<int Base>
struct Power<Base, 0> {
    static const int value = 1;
};

// Example 4: SFINAE (Substitution Failure Is Not An Error)
template<typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_even(T value) {
    return value % 2 == 0;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
is_even(T value) {
    return std::fmod(value, 2.0) == 0.0;
}

// Modern SFINAE with if constexpr (C++17)
template<typename T>
bool is_even_modern(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value % 2 == 0;
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::fmod(value, 2.0) == 0.0;
    } else {
        return false;
    }
}

// Example 5: Variadic Templates (C++11)
template<typename T>
void print_variadic(T&& t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void print_variadic(T&& t, Args&&... args) {
    std::cout << t << " ";
    print_variadic(std::forward<Args>(args)...);
}

// Variadic function with fold expression (C++17)
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

template<typename... Args>
auto product(Args... args) {
    return (args * ...);
}

// Example 6: Generic Container Template
template<typename T>
class GenericContainer {
private:
    std::vector<T> data_;
    
public:
    void add(const T& item) {
        data_.push_back(item);
    }
    
    void remove(const T& item) {
        auto it = std::find(data_.begin(), data_.end(), item);
        if (it != data_.end()) {
            data_.erase(it);
        }
    }
    
    bool contains(const T& item) const {
        return std::find(data_.begin(), data_.end(), item) != data_.end();
    }
    
    size_t size() const {
        return data_.size();
    }
    
    void display() const {
        std::cout << "Container contents: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    // Template member function
    template<typename U>
    GenericContainer<U> transform(U (*func)(const T&)) const {
        GenericContainer<U> result;
        for (const auto& item : data_) {
            result.add(func(item));
        }
        return result;
    }
    
    // Template member function with lambda
    template<typename F>
    void forEach(F func) const {
        for (const auto& item : data_) {
            func(item);
        }
    }
    
    // Template member function for filtering
    template<typename Predicate>
    GenericContainer<T> filter(Predicate pred) const {
        GenericContainer<T> result;
        for (const auto& item : data_) {
            if (pred(item)) {
                result.add(item);
            }
        }
        return result;
    }
};

// Example 7: Template Specialization
template<typename T>
class Vector {
private:
    std::vector<T> data_;
    
public:
    void add(const T& item) {
        data_.push_back(item);
    }
    
    void display() const {
        std::cout << "Generic Vector: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Full specialization for bool
template<>
class Vector<bool> {
private:
    std::vector<bool> data_;
    
public:
    void add(bool item) {
        data_.push_back(item);
    }
    
    void display() const {
        std::cout << "Bool Vector: ";
        for (const auto& item : data_) {
            std::cout << (item ? "true" : "false") << " ";
        }
        std::cout << std::endl;
    }
};

// Partial specialization for pointers
template<typename T>
class Vector<T*> {
private:
    std::vector<T*> data_;
    
public:
    void add(T* item) {
        data_.push_back(item);
    }
    
    void display() const {
        std::cout << "Pointer Vector: ";
        for (const auto& item : data_) {
            std::cout << *item << " ";
        }
        std::cout << std::endl;
    }
};

// Example 8: Template Constraints (C++20 concepts simulation)
template<typename T>
struct is_numeric {
    static const bool value = std::is_arithmetic<T>::value;
};

template<typename T>
typename std::enable_if<is_numeric<T>::value, T>::type
square(T value) {
    return value * value;
}

template<typename T>
typename std::enable_if<!is_numeric<T>::value, void>::type
square(T value) {
    std::cout << "Cannot square non-numeric type" << std::endl;
}

// Function to demonstrate function templates
void demonstrateFunctionTemplates() {
    std::cout << "=== Function Templates Demonstration ===" << std::endl;
    
    std::cout << "\nMaximum function:" << std::endl;
    std::cout << "max(10, 20) = " << maximum(10, 20) << std::endl;
    std::cout << "max(3.14, 2.71) = " << maximum(3.14, 2.71) << std::endl;
    std::cout << "max('a', 'z') = " << maximum('a', 'z') << std::endl;
    
    std::cout << "\nAdd function:" << std::endl;
    std::cout << "add(5, 3.14) = " << add(5, 3.14) << std::endl;
    std::cout << "add(10, 20) = " << add(10, 20) << std::endl;
    
    std::cout << "\nMultiply function:" << std::endl;
    std::cout << "multiply(5, 3.14) = " << multiply(5, 3.14) << std::endl;
    std::cout << "multiply(5, 5) = " << multiply(5, 5) << std::endl;
    
    std::cout << "\nCalculate function:" << std::endl;
    std::cout << "calculate(1, 2.5, 3) = " << calculate(1, 2.5, 3) << std::endl;
    
    std::cout << "\nPrint function specialization:" << std::endl;
    print(42);
    print(3.14159);
    print(std::string("Hello"));
    print('A');
}

// Function to demonstrate class templates
void demonstrateClassTemplates() {
    std::cout << "\n=== Class Templates Demonstration ===" << std::endl;
    
    std::cout << "\nStack template:" << std::endl;
    Stack<int> int_stack;
    Stack<std::string> string_stack;
    
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    string_stack.push("Hello");
    string_stack.push("World");
    string_stack.push("Template");
    
    int_stack.display();
    string_stack.display();
    
    std::cout << "Top of int stack: " << int_stack.top() << std::endl;
    std::cout << "Top of string stack: " << string_stack.top() << std::endl;
    
    std::cout << "\nPair template:" << std::endl;
    Pair<int, std::string> pair1(42, "Hello");
    Pair<double, int> pair2(3.14, 100);
    
    pair1.display();
    pair2.display();
    
    // Transform first element
    auto transformed = pair1.transformFirst([](const int& x) { return x * 2.0; });
    transformed.display();
    
    // Apply function to pair
    auto result = pair2.apply([](double x, int y) { return x + y; });
    std::cout << "Pair2 sum: " << result << std::endl;
}

// Function to demonstrate template metaprogramming
void demonstrateMetaprogramming() {
    std::cout << "\n=== Template Metaprogramming Demonstration ===" << std::endl;
    
    std::cout << "\nCompile-time calculations:" << std::endl;
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;
    std::cout << "Factorial of 10: " << Factorial<10>::value << std::endl;
    
    std::cout << "Fibonacci(10): " << Fibonacci<10>::value << std::endl;
    std::cout << "Fibonacci(15): " << Fibonacci<15>::value << std::endl;
    
    std::cout << "Power(2, 10): " << Power<2, 10>::value << std::endl;
    std::cout << "Power(3, 5): " << Power<3, 5>::value << std::endl;
}

// Function to demonstrate SFINAE
void demonstrateSFINAE() {
    std::cout << "\n=== SFINAE Demonstration ===" << std::endl;
    
    std::cout << "\nTraditional SFINAE:" << std::endl;
    std::cout << "is_even(10) = " << (is_even(10) ? "true" : "false") << std::endl;
    std::cout << "is_even(11) = " << (is_even(11) ? "true" : "false") << std::endl;
    std::cout << "is_even(10.0) = " << (is_even(10.0) ? "true" : "false") << std::endl;
    std::cout << "is_even(11.0) = " << (is_even(11.0) ? "true" : "false") << std::endl;
    
    std::cout << "\nModern SFINAE (if constexpr):" << std::endl;
    std::cout << "is_even_modern(10) = " << (is_even_modern(10) ? "true" : "false") << std::endl;
    std::cout << "is_even_modern(11) = " << (is_even_modern(11) ? "true" : "false") << std::endl;
    std::cout << "is_even_modern(10.0) = " << (is_even_modern(10.0) ? "true" : "false") << std::endl;
    std::cout << "is_even_modern(11.0) = " << (is_even_modern(11.0) ? "true" : "false") << std::endl;
}

// Function to demonstrate variadic templates
void demonstrateVariadicTemplates() {
    std::cout << "\n=== Variadic Templates Demonstration ===" << std::endl;
    
    std::cout << "\nVariadic print:" << std::endl;
    print_variadic(1, 2, 3, 4, 5);
    print_variadic("Hello", "World", "Template", "Variadic");
    print_variadic(3.14, 2.71, 1.41);
    
    std::cout << "\nFold expressions:" << std::endl;
    std::cout << "sum(1, 2, 3, 4, 5) = " << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << "sum(1.5, 2.5, 3.5) = " << sum(1.5, 2.5, 3.5) << std::endl;
    std::cout << "product(1, 2, 3, 4, 5) = " << product(1, 2, 3, 4, 5) << std::endl;
    std::cout << "product(2, 3, 4) = " << product(2, 3, 4) << std::endl;
}

// Function to demonstrate generic containers
void demonstrateGenericContainers() {
    std::cout << "\n=== Generic Containers Demonstration ===" << std::endl;
    
    GenericContainer<int> int_container;
    GenericContainer<std::string> string_container;
    
    // Add elements
    for (int i = 1; i <= 10; ++i) {
        int_container.add(i);
    }
    
    string_container.add("apple");
    string_container.add("banana");
    string_container.add("cherry");
    string_container.add("date");
    string_container.add("elderberry");
    
    std::cout << "\nInteger container:" << std::endl;
    int_container.display();
    
    std::cout << "\nString container:" << std::endl;
    string_container.display();
    
    // Filter even numbers
    auto even_numbers = int_container.filter([](int n) { return n % 2 == 0; });
    std::cout << "\nEven numbers: ";
    even_numbers.display();
    
    // Filter long strings
    auto long_strings = string_container.filter([](const std::string& s) { return s.length() > 5; });
    std::cout << "Long strings: ";
    long_strings.display();
    
    // Transform integers to strings
    auto string_numbers = int_container.transform([](int n) { return std::to_string(n); });
    std::cout << "Numbers as strings: ";
    string_numbers.display();
    
    // For each with lambda
    std::cout << "\nFor each integer: ";
    int_container.forEach([](int n) { std::cout << n * 2 << " "; });
    std::cout << std::endl;
}

// Function to demonstrate template specialization
void demonstrateTemplateSpecialization() {
    std::cout << "\n=== Template Specialization Demonstration ===" << std::endl;
    
    Vector<int> int_vector;
    Vector<bool> bool_vector;
    Vector<std::string*> string_ptr_vector;
    
    // Add elements
    int_vector.add(1);
    int_vector.add(2);
    int_vector.add(3);
    
    bool_vector.add(true);
    bool_vector.add(false);
    bool_vector.add(true);
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    std::string str3 = "Template";
    
    string_ptr_vector.add(&str1);
    string_ptr_vector.add(&str2);
    string_ptr_vector.add(&str3);
    
    std::cout << "\nGeneric vector:" << std::endl;
    int_vector.display();
    
    std::cout << "\nBool vector (specialized):" << std::endl;
    bool_vector.display();
    
    std::cout << "\nPointer vector (partial specialization):" << std::endl;
    string_ptr_vector.display();
}

// Function to demonstrate template constraints
void demonstrateTemplateConstraints() {
    std::cout << "\n=== Template Constraints Demonstration ===" << std::endl;
    
    std::cout << "\nSquare function with constraints:" << std::endl;
    std::cout << "square(5) = " << square(5) << std::endl;
    std::cout << "square(3.14) = " << square(3.14) << std::endl;
    std::cout << "square(2.5) = " << square(2.5) << std::endl;
    
    // This would cause compilation error without proper handling
    // square("Hello");  // Non-numeric type
}

// Function to demonstrate template instantiation
void demonstrateTemplateInstantiation() {
    std::cout << "\n=== Template Instantiation Demonstration ===" << std::endl;
    
    std::cout << "\nExplicit template instantiation:" << std::endl;
    
    // Explicit instantiation
    Stack<int> explicit_int_stack;
    Stack<double> explicit_double_stack;
    Stack<std::string> explicit_string_stack;
    
    explicit_int_stack.push(100);
    explicit_double_stack.push(3.14159);
    explicit_string_stack.push("Explicit");
    
    explicit_int_stack.display();
    explicit_double_stack.display();
    explicit_string_stack.display();
    
    std::cout << "\nImplicit template instantiation:" << std::endl;
    
    // Implicit instantiation through function calls
    auto max_int = maximum(10, 20);
    auto max_double = maximum(3.14, 2.71);
    auto max_string = maximum(std::string("apple"), std::string("banana"));
    
    std::cout << "Max int: " << max_int << std::endl;
    std::cout << "Max double: " << max_double << std::endl;
    std::cout << "Max string: " << max_string << std::endl;
}

int main() {
    std::cout << "=== Templates Fundamentals Demonstration ===" << std::endl;
    std::cout << "This program demonstrates function templates, class templates,\n"
              << "template instantiation, specialization, and metaprogramming basics.\n" << std::endl;
    
    // Demonstrate various template concepts
    demonstrateFunctionTemplates();
    demonstrateClassTemplates();
    demonstrateMetaprogramming();
    demonstrateSFINAE();
    demonstrateVariadicTemplates();
    demonstrateGenericContainers();
    demonstrateTemplateSpecialization();
    demonstrateTemplateConstraints();
    demonstrateTemplateInstantiation();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Templates enable generic programming in C++" << std::endl;
    std::cout << "2. Function templates provide generic algorithms" << std::endl;
    std::cout << "3. Class templates provide generic data structures" << std::endl;
    std::cout << "4. Template specialization allows custom behavior for specific types" << std::endl;
    std::cout << "5. Template metaprogramming enables compile-time computations" << std::endl;
    std::cout << "6. SFINAE provides compile-time type checking" << std::endl;
    std::cout << "7. Variadic templates support variable number of arguments" << std::endl;
    std::cout << "8. Template constraints ensure type requirements" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o templates_fundamentals 01_Templates_Fundamentals.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o templates_fundamentals 01_Templates_Fundamentals.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Templates_Fundamentals.cpp
 * 
 * Running:
 * ./templates_fundamentals (Linux/macOS)
 * templates_fundamentals.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for variadic templates and some features.
 * C++17 is recommended for best template support with if constexpr and fold expressions.
 * 
 * Template Notes:
 * - Templates enable generic programming
 * - Function templates provide generic algorithms
 * - Class templates provide generic data structures
 * - Template specialization allows custom behavior
 * - Template metaprogramming enables compile-time computations
 * - SFINAE provides compile-time type checking
 * - Variadic templates support variable arguments
 * - Template constraints ensure type requirements
 */"""
