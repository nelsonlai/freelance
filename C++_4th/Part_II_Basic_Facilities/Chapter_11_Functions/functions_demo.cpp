#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

// Demonstrates C++ functions and advanced features
int main() {
    std::cout << "C++ Functions Demonstration" << std::endl;
    std::cout << "===========================" << std::endl;
    
    // 1. Basic function declaration and definition
    std::cout << "\n1. BASIC FUNCTIONS:" << std::endl;
    
    auto basic_add = [](int a, int b) -> int {
        return a + b;
    };
    
    auto basic_multiply = [](int a, int b) -> int {
        return a * b;
    };
    
    std::cout << "basic_add(5, 3) = " << basic_add(5, 3) << std::endl;
    std::cout << "basic_multiply(4, 6) = " << basic_multiply(4, 6) << std::endl;
    
    // 2. Function with different parameter types
    std::cout << "\n2. FUNCTIONS WITH DIFFERENT PARAMETER TYPES:" << std::endl;
    
    auto print_value = [](const std::string& name, int value) {
        std::cout << name << " = " << value << std::endl;
    };
    
    auto print_double = [](const std::string& name, double value) {
        std::cout << name << " = " << value << std::endl;
    };
    
    auto print_string = [](const std::string& name, const std::string& value) {
        std::cout << name << " = " << value << std::endl;
    };
    
    print_value("Integer", 42);
    print_double("Double", 3.14159);
    print_string("String", "Hello, World!");
    
    // 3. Function overloading (using lambdas with different types)
    std::cout << "\n3. FUNCTION OVERLOADING:" << std::endl;
    
    auto add_int = [](int a, int b) { return a + b; };
    auto add_double = [](double a, double b) { return a + b; };
    auto add_string = [](const std::string& a, const std::string& b) { return a + b; };
    
    std::cout << "add_int(5, 3) = " << add_int(5, 3) << std::endl;
    std::cout << "add_double(3.5, 2.7) = " << add_double(3.5, 2.7) << std::endl;
    std::cout << "add_string(\"Hello\", \" World\") = " << add_string("Hello", " World") << std::endl;
    
    // 4. Default arguments
    std::cout << "\n4. DEFAULT ARGUMENTS:" << std::endl;
    
    auto power = [](int base, int exponent = 2) {
        int result = 1;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    };
    
    std::cout << "power(5) = " << power(5) << " (default exponent 2)" << std::endl;
    std::cout << "power(5, 3) = " << power(5, 3) << std::endl;
    std::cout << "power(2, 8) = " << power(2, 8) << std::endl;
    
    // 5. Function templates (using lambda templates)
    std::cout << "\n5. FUNCTION TEMPLATES:" << std::endl;
    
    auto template_max = [](auto a, auto b) {
        return (a > b) ? a : b;
    };
    
    std::cout << "template_max(10, 20) = " << template_max(10, 20) << std::endl;
    std::cout << "template_max(3.14, 2.71) = " << template_max(3.14, 2.71) << std::endl;
    std::cout << "template_max('z', 'a') = " << template_max('z', 'a') << std::endl;
    
    // 6. Constexpr functions
    std::cout << "\n6. CONSTEXPR FUNCTIONS:" << std::endl;
    
    constexpr auto constexpr_factorial = [](int n) constexpr {
        int result = 1;
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
        return result;
    };
    
    constexpr int fact_5 = constexpr_factorial(5);
    std::cout << "constexpr_factorial(5) = " << fact_5 << std::endl;
    std::cout << "constexpr_factorial(3) = " << constexpr_factorial(3) << std::endl;
    
    // 7. Inline functions
    std::cout << "\n7. INLINE FUNCTIONS:" << std::endl;
    
    auto inline_square = [](int x) {
        return x * x;
    };
    
    std::cout << "inline_square(7) = " << inline_square(7) << std::endl;
    std::cout << "inline_square(12) = " << inline_square(12) << std::endl;
    
    // 8. Function pointers
    std::cout << "\n8. FUNCTION POINTERS:" << std::endl;
    
    auto operation_add = [](int a, int b) { return a + b; };
    auto operation_multiply = [](int a, int b) { return a * b; };
    auto operation_subtract = [](int a, int b) { return a - b; };
    
    std::function<int(int, int)> operations[] = {
        operation_add,
        operation_multiply,
        operation_subtract
    };
    
    const char* operation_names[] = {"Add", "Multiply", "Subtract"};
    
    int a = 10, b = 5;
    for (int i = 0; i < 3; ++i) {
        std::cout << operation_names[i] << "(" << a << ", " << b << ") = " 
                  << operations[i](a, b) << std::endl;
    }
    
    // 9. Lambda functions
    std::cout << "\n9. LAMBDA FUNCTIONS:" << std::endl;
    
    // Simple lambda
    auto simple_lambda = [](int x) { return x * 2; };
    std::cout << "simple_lambda(5) = " << simple_lambda(5) << std::endl;
    
    // Lambda with capture
    int multiplier = 3;
    auto capture_lambda = [multiplier](int x) { return x * multiplier; };
    std::cout << "capture_lambda(4) = " << capture_lambda(4) << std::endl;
    
    // Lambda with reference capture
    int counter = 0;
    auto counter_lambda = [&counter](int x) { 
        counter += x; 
        return counter; 
    };
    std::cout << "counter_lambda(5) = " << counter_lambda(5) << std::endl;
    std::cout << "counter_lambda(3) = " << counter_lambda(3) << std::endl;
    std::cout << "counter = " << counter << std::endl;
    
    // 10. Higher-order functions
    std::cout << "\n10. HIGHER-ORDER FUNCTIONS:" << std::endl;
    
    auto apply_function = [](const std::vector<int>& vec, std::function<int(int)> func) {
        std::vector<int> result;
        for (int val : vec) {
            result.push_back(func(val));
        }
        return result;
    };
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Apply square function
    auto square_func = [](int x) { return x * x; };
    auto squared = apply_function(numbers, square_func);
    
    std::cout << "Original: ";
    for (int val : numbers) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Squared: ";
    for (int val : squared) std::cout << val << " ";
    std::cout << std::endl;
    
    // 11. Variadic functions (using lambda with variadic templates)
    std::cout << "\n11. VARIADIC FUNCTIONS:" << std::endl;
    
    auto variadic_sum = [](auto... args) {
        return (args + ...);  // C++17 fold expression
    };
    
    std::cout << "variadic_sum(1, 2, 3, 4, 5) = " << variadic_sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << "variadic_sum(10, 20, 30) = " << variadic_sum(10, 20, 30) << std::endl;
    
    // 12. Recursive functions
    std::cout << "\n12. RECURSIVE FUNCTIONS:" << std::endl;
    
    auto recursive_factorial = [](int n) -> int {
        if (n <= 1) return 1;
        return n * recursive_factorial(n - 1);
    };
    
    std::cout << "recursive_factorial(5) = " << recursive_factorial(5) << std::endl;
    std::cout << "recursive_factorial(6) = " << recursive_factorial(6) << std::endl;
    
    // 13. Function composition
    std::cout << "\n13. FUNCTION COMPOSITION:" << std::endl;
    
    auto compose = [](auto f, auto g) {
        return [f, g](auto x) { return f(g(x)); };
    };
    
    auto add_one = [](int x) { return x + 1; };
    auto multiply_by_two = [](int x) { return x * 2; };
    
    auto composed = compose(add_one, multiply_by_two);
    std::cout << "composed(5) = add_one(multiply_by_two(5)) = " << composed(5) << std::endl;
    
    // 14. Function with multiple return values (using pair)
    std::cout << "\n14. FUNCTIONS WITH MULTIPLE RETURN VALUES:" << std::endl;
    
    auto divide_with_remainder = [](int dividend, int divisor) {
        return std::make_pair(dividend / divisor, dividend % divisor);
    };
    
    auto [quotient, remainder] = divide_with_remainder(17, 5);
    std::cout << "17 / 5 = " << quotient << " remainder " << remainder << std::endl;
    
    // 15. Function with array parameters
    std::cout << "\n15. FUNCTIONS WITH ARRAY PARAMETERS:" << std::endl;
    
    auto array_sum = [](const int arr[], size_t size) {
        int sum = 0;
        for (size_t i = 0; i < size; ++i) {
            sum += arr[i];
        }
        return sum;
    };
    
    auto array_max = [](const int arr[], size_t size) {
        int max_val = arr[0];
        for (size_t i = 1; i < size; ++i) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
        return max_val;
    };
    
    int test_array[] = {3, 7, 2, 9, 1, 5};
    size_t array_size = sizeof(test_array) / sizeof(test_array[0]);
    
    std::cout << "Array: ";
    for (size_t i = 0; i < array_size; ++i) {
        std::cout << test_array[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Array sum: " << array_sum(test_array, array_size) << std::endl;
    std::cout << "Array max: " << array_max(test_array, array_size) << std::endl;
    
    // 16. Function with vector parameters
    std::cout << "\n16. FUNCTIONS WITH VECTOR PARAMETERS:" << std::endl;
    
    auto vector_average = [](const std::vector<double>& vec) {
        if (vec.empty()) return 0.0;
        
        double sum = 0.0;
        for (double val : vec) {
            sum += val;
        }
        return sum / vec.size();
    };
    
    std::vector<double> values = {1.5, 2.7, 3.9, 4.1, 5.3};
    std::cout << "Vector: ";
    for (double val : values) std::cout << val << " ";
    std::cout << std::endl;
    std::cout << "Average: " << vector_average(values) << std::endl;
    
    // 17. Function with string parameters
    std::cout << "\n17. FUNCTIONS WITH STRING PARAMETERS:" << std::endl;
    
    auto string_reverse = [](const std::string& str) {
        std::string reversed = str;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    };
    
    auto string_to_upper = [](const std::string& str) {
        std::string upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    };
    
    std::string test_string = "Hello, World!";
    std::cout << "Original: " << test_string << std::endl;
    std::cout << "Reversed: " << string_reverse(test_string) << std::endl;
    std::cout << "Uppercase: " << string_to_upper(test_string) << std::endl;
    
    // 18. Function with reference parameters
    std::cout << "\n18. FUNCTIONS WITH REFERENCE PARAMETERS:" << std::endl;
    
    auto swap_values = [](int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    };
    
    int x = 10, y = 20;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap_values(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    // 19. Function with const reference parameters
    std::cout << "\n19. FUNCTIONS WITH CONST REFERENCE PARAMETERS:" << std::endl;
    
    auto print_large_object = [](const std::vector<int>& large_vec) {
        std::cout << "Large object size: " << large_vec.size() << std::endl;
        std::cout << "First few elements: ";
        for (size_t i = 0; i < std::min(large_vec.size(), size_t(5)); ++i) {
            std::cout << large_vec[i] << " ";
        }
        std::cout << std::endl;
    };
    
    std::vector<int> large_vector(1000);
    std::iota(large_vector.begin(), large_vector.end(), 1);
    print_large_object(large_vector);
    
    // 20. Function with pointer parameters
    std::cout << "\n20. FUNCTIONS WITH POINTER PARAMETERS:" << std::endl;
    
    auto modify_pointer = [](int* ptr, int new_value) {
        if (ptr != nullptr) {
            *ptr = new_value;
        }
    };
    
    int pointer_var = 42;
    std::cout << "Before modification: " << pointer_var << std::endl;
    modify_pointer(&pointer_var, 100);
    std::cout << "After modification: " << pointer_var << std::endl;
    
    std::cout << "\nFunctions demonstration completed!" << std::endl;
    return 0;
}
