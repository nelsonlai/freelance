/*
 * Lesson 8.3: Functions
 * 
 * This file demonstrates function declaration, definition,
 * parameters, overloading, and lambda expressions.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <optional>
#include <cmath>

// Function declarations
int add(int a, int b);
double add(double a, double b);
std::string add(const std::string& a, const std::string& b);
void print_info(const std::string& name, int age = 0);
int factorial(int n);
void demonstrate_parameters(int value, int& reference, const int& const_ref, int* pointer);

// Function templates
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate basic functions
void demonstrateBasicFunctions() {
    std::cout << "=== Basic Functions ===" << std::endl;
    
    // Function calls
    int result1 = add(5, 3);
    std::cout << "add(5, 3) = " << result1 << std::endl;
    
    double result2 = add(3.14, 2.71);
    std::cout << "add(3.14, 2.71) = " << result2 << std::endl;
    
    std::string result3 = add("Hello", "World");
    std::cout << "add(\"Hello\", \"World\") = " << result3 << std::endl;
    
    // Function with default parameters
    print_info("Alice");
    print_info("Bob", 25);
    print_info("Charlie", 30);
}

// Function to demonstrate parameter passing
void demonstrateParameters() {
    std::cout << "\n=== Parameter Passing ===" << std::endl;
    
    int value = 10;
    int reference = 20;
    int const_ref = 30;
    int pointer_val = 40;
    
    std::cout << "Before function call:" << std::endl;
    std::cout << "value = " << value << std::endl;
    std::cout << "reference = " << reference << std::endl;
    std::cout << "const_ref = " << const_ref << std::endl;
    std::cout << "pointer_val = " << pointer_val << std::endl;
    
    demonstrate_parameters(value, reference, const_ref, &pointer_val);
    
    std::cout << "\nAfter function call:" << std::endl;
    std::cout << "value = " << value << " (unchanged - passed by value)" << std::endl;
    std::cout << "reference = " << reference << " (changed - passed by reference)" << std::endl;
    std::cout << "const_ref = " << const_ref << " (unchanged - const reference)" << std::endl;
    std::cout << "pointer_val = " << pointer_val << " (changed - passed by pointer)" << std::endl;
}

// Function to demonstrate function overloading
void demonstrateFunctionOverloading() {
    std::cout << "\n=== Function Overloading ===" << std::endl;
    
    // Different parameter types
    std::cout << "add(int, int): " << add(5, 3) << std::endl;
    std::cout << "add(double, double): " << add(3.14, 2.71) << std::endl;
    std::cout << "add(string, string): " << add("Hello", "World") << std::endl;
    
    // Template function
    std::cout << "\nTemplate functions:" << std::endl;
    std::cout << "maximum(int, int): " << maximum(10, 20) << std::endl;
    std::cout << "maximum(double, double): " << maximum(3.14, 2.71) << std::endl;
    std::cout << "maximum(string, string): " << maximum(std::string("apple"), std::string("banana")) << std::endl;
}

// Function to demonstrate recursion
void demonstrateRecursion() {
    std::cout << "\n=== Recursion ===" << std::endl;
    
    // Factorial function
    std::cout << "Factorial of 5: " << factorial(5) << std::endl;
    std::cout << "Factorial of 10: " << factorial(10) << std::endl;
    
    // Fibonacci function
    auto fibonacci = [](int n) -> int {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    };
    
    std::cout << "\nFibonacci sequence:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << fibonacci(i) << " ";
    }
    std::cout << std::endl;
    
    // Recursive binary search
    auto binary_search = [](const std::vector<int>& arr, int target, int left, int right) -> int {
        if (left > right) return -1;
        
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] > target) return binary_search(arr, target, left, mid - 1);
        return binary_search(arr, target, mid + 1, right);
    };
    
    std::vector<int> sorted_array = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int target = 7;
    int index = binary_search(sorted_array, target, 0, sorted_array.size() - 1);
    std::cout << "\nBinary search for " << target << " in sorted array: index " << index << std::endl;
}

// Function to demonstrate lambda expressions
void demonstrateLambdaExpressions() {
    std::cout << "\n=== Lambda Expressions ===" << std::endl;
    
    // Basic lambda
    auto square = [](int x) -> int {
        return x * x;
    };
    
    std::cout << "square(5) = " << square(5) << std::endl;
    
    // Lambda with capture
    int multiplier = 3;
    auto multiply = [multiplier](int x) -> int {
        return x * multiplier;
    };
    
    std::cout << "multiply(4) = " << multiply(4) << std::endl;
    
    // Lambda with reference capture
    int counter = 0;
    auto increment = [&counter]() -> int {
        return ++counter;
    };
    
    std::cout << "increment() = " << increment() << std::endl;
    std::cout << "increment() = " << increment() << std::endl;
    std::cout << "counter = " << counter << std::endl;
    
    // Lambda with STL algorithms
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Count even numbers
    int even_count = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "Even numbers count: " << even_count << std::endl;
    
    // Transform numbers to squares
    std::vector<int> squares;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares), [](int n) {
        return n * n;
    });
    
    std::cout << "Squares: ";
    print_vector(squares);
    
    // Sort by absolute value
    std::vector<int> mixed = {-5, 3, -1, 4, -2};
    std::sort(mixed.begin(), mixed.end(), [](int a, int b) {
        return std::abs(a) < std::abs(b);
    });
    
    std::cout << "Sorted by absolute value: ";
    print_vector(mixed);
}

// Function to demonstrate function objects
void demonstrateFunctionObjects() {
    std::cout << "\n=== Function Objects ===" << std::endl;
    
    // Function object class
    class Multiplier {
    private:
        int factor_;
    public:
        Multiplier(int factor) : factor_(factor) {}
        int operator()(int x) const {
            return x * factor_;
        }
    };
    
    Multiplier multiply_by_5(5);
    std::cout << "multiply_by_5(3) = " << multiply_by_5(3) << std::endl;
    
    // Using with STL algorithms
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result;
    
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(result), multiply_by_5);
    
    std::cout << "Original numbers: ";
    print_vector(numbers);
    std::cout << "Multiplied by 5: ";
    print_vector(result);
    
    // Function object with state
    class Counter {
    private:
        int count_;
    public:
        Counter() : count_(0) {}
        int operator()() {
            return ++count_;
        }
        int get_count() const { return count_; }
    };
    
    Counter counter;
    std::cout << "counter() = " << counter() << std::endl;
    std::cout << "counter() = " << counter() << std::endl;
    std::cout << "counter() = " << counter() << std::endl;
    std::cout << "Total count: " << counter.get_count() << std::endl;
}

// Function to demonstrate higher-order functions
void demonstrateHigherOrderFunctions() {
    std::cout << "\n=== Higher-Order Functions ===" << std::endl;
    
    // Function that takes a function as parameter
    auto apply_operation = [](const std::vector<int>& vec, std::function<int(int)> op) {
        std::vector<int> result;
        for (const auto& element : vec) {
            result.push_back(op(element));
        }
        return result;
    };
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Apply square function
    auto square = [](int x) { return x * x; };
    auto squares = apply_operation(numbers, square);
    
    std::cout << "Original: ";
    print_vector(numbers);
    std::cout << "Squared: ";
    print_vector(squares);
    
    // Apply cube function
    auto cube = [](int x) { return x * x * x; };
    auto cubes = apply_operation(numbers, cube);
    
    std::cout << "Cubed: ";
    print_vector(cubes);
    
    // Function that returns a function
    auto create_multiplier = [](int factor) {
        return [factor](int x) { return x * factor; };
    };
    
    auto multiply_by_3 = create_multiplier(3);
    auto multiply_by_7 = create_multiplier(7);
    
    std::cout << "multiply_by_3(4) = " << multiply_by_3(4) << std::endl;
    std::cout << "multiply_by_7(4) = " << multiply_by_7(4) << std::endl;
}

// Function to demonstrate optional return values
void demonstrateOptionalReturns() {
    std::cout << "\n=== Optional Return Values ===" << std::endl;
    
    // Function that might not return a value
    auto safe_divide = [](double a, double b) -> std::optional<double> {
        if (b == 0) {
            return std::nullopt;  // No value
        }
        return a / b;
    };
    
    auto result1 = safe_divide(10.0, 2.0);
    if (result1) {
        std::cout << "10.0 / 2.0 = " << *result1 << std::endl;
    } else {
        std::cout << "Division by zero!" << std::endl;
    }
    
    auto result2 = safe_divide(10.0, 0.0);
    if (result2) {
        std::cout << "10.0 / 0.0 = " << *result2 << std::endl;
    } else {
        std::cout << "Division by zero!" << std::endl;
    }
    
    // Function that finds element in vector
    auto find_element = [](const std::vector<int>& vec, int target) -> std::optional<int> {
        auto it = std::find(vec.begin(), vec.end(), target);
        if (it != vec.end()) {
            return std::distance(vec.begin(), it);
        }
        return std::nullopt;
    };
    
    std::vector<int> numbers = {1, 3, 5, 7, 9};
    auto index1 = find_element(numbers, 5);
    if (index1) {
        std::cout << "Found 5 at index " << *index1 << std::endl;
    } else {
        std::cout << "5 not found" << std::endl;
    }
    
    auto index2 = find_element(numbers, 4);
    if (index2) {
        std::cout << "Found 4 at index " << *index2 << std::endl;
    } else {
        std::cout << "4 not found" << std::endl;
    }
}

// Function to demonstrate function pointers
void demonstrateFunctionPointers() {
    std::cout << "\n=== Function Pointers ===" << std::endl;
    
    // Function pointer type
    using MathFunction = int(*)(int, int);
    
    // Function pointer assignments
    MathFunction func1 = add;
    MathFunction func2 = [](int a, int b) { return a - b; };
    
    std::cout << "func1(5, 3) = " << func1(5, 3) << std::endl;
    std::cout << "func2(5, 3) = " << func2(5, 3) << std::endl;
    
    // Function pointer array
    MathFunction operations[] = {
        [](int a, int b) { return a + b; },
        [](int a, int b) { return a - b; },
        [](int a, int b) { return a * b; },
        [](int a, int b) { return (b != 0) ? a / b : 0; }
    };
    
    const char* operation_names[] = {"Addition", "Subtraction", "Multiplication", "Division"};
    
    int a = 10, b = 3;
    for (int i = 0; i < 4; ++i) {
        std::cout << operation_names[i] << ": " << operations[i](a, b) << std::endl;
    }
}

// Function implementations
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

std::string add(const std::string& a, const std::string& b) {
    return a + b;
}

void print_info(const std::string& name, int age) {
    std::cout << "Name: " << name;
    if (age > 0) {
        std::cout << ", Age: " << age;
    }
    std::cout << std::endl;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

void demonstrate_parameters(int value, int& reference, const int& const_ref, int* pointer) {
    std::cout << "\nInside function:" << std::endl;
    std::cout << "value = " << value << std::endl;
    std::cout << "reference = " << reference << std::endl;
    std::cout << "const_ref = " << const_ref << std::endl;
    std::cout << "*pointer = " << *pointer << std::endl;
    
    // Modify parameters
    value = 100;        // Modifies local copy
    reference = 200;    // Modifies original variable
    // const_ref = 300; // Error: cannot modify const reference
    *pointer = 400;     // Modifies value pointed to
    
    std::cout << "\nAfter modifications:" << std::endl;
    std::cout << "value = " << value << std::endl;
    std::cout << "reference = " << reference << std::endl;
    std::cout << "const_ref = " << const_ref << std::endl;
    std::cout << "*pointer = " << *pointer << std::endl;
}

int main() {
    std::cout << "=== Functions Demonstration ===" << std::endl;
    std::cout << "This program demonstrates function declaration, definition,\n"
              << "parameters, overloading, and lambda expressions.\n" << std::endl;
    
    // Demonstrate various function concepts
    demonstrateBasicFunctions();
    demonstrateParameters();
    demonstrateFunctionOverloading();
    demonstrateRecursion();
    demonstrateLambdaExpressions();
    demonstrateFunctionObjects();
    demonstrateHigherOrderFunctions();
    demonstrateOptionalReturns();
    demonstrateFunctionPointers();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Functions encapsulate reusable code blocks" << std::endl;
    std::cout << "2. Parameters can be passed by value, reference, or pointer" << std::endl;
    std::cout << "3. Function overloading allows multiple functions with the same name" << std::endl;
    std::cout << "4. Lambda expressions provide inline function definitions" << std::endl;
    std::cout << "5. Function objects allow stateful functions" << std::endl;
    std::cout << "6. Higher-order functions take or return other functions" << std::endl;
    std::cout << "7. std::optional provides safe optional return values" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o functions 03_Functions.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o functions 03_Functions.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Functions.cpp
 * 
 * Running:
 * ./functions (Linux/macOS)
 * functions.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for lambda expressions.
 * C++17 is recommended for best function support.
 * 
 * Function Notes:
 * - Use const references for large parameters
 * - Prefer return by value for small objects
 * - Use std::optional for optional return values
 * - Lambda expressions are useful for inline functions
 * - Function objects can maintain state
 * - Higher-order functions provide flexibility
 */"""
