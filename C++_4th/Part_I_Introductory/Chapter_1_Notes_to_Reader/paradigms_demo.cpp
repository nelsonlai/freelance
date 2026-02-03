#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Demonstrates different programming paradigms in C++

// 1. PROCEDURAL PARADIGM - Functions and structured programming
int add(int a, int b) {
    return a + b;
}

void print_numbers(const std::vector<int>& numbers) {
    std::cout << "Numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 2. OBJECT-ORIENTED PARADIGM - Classes and encapsulation
class Calculator {
private:
    double last_result;
    
public:
    Calculator() : last_result(0.0) {}
    
    double multiply(double a, double b) {
        last_result = a * b;
        return last_result;
    }
    
    double get_last_result() const {
        return last_result;
    }
    
    void reset() {
        last_result = 0.0;
    }
};

// 3. GENERIC PARADIGM - Templates and compile-time polymorphism
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
void print_container(const T& container) {
    std::cout << "Container contents: ";
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 4. FUNCTIONAL PARADIGM - Higher-order functions and lambdas
void demonstrate_functional_paradigm() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Lambda function (anonymous function)
    auto square = [](int x) { return x * x; };
    
    // Higher-order function (transform)
    std::vector<int> squared_numbers;
    std::transform(numbers.begin(), numbers.end(), 
                   std::back_inserter(squared_numbers), square);
    
    std::cout << "Original numbers: ";
    print_container(numbers);
    
    std::cout << "Squared numbers: ";
    print_container(squared_numbers);
    
    // Function object
    auto is_even = [](int x) { return x % 2 == 0; };
    
    // Count even numbers using functional approach
    int even_count = std::count_if(numbers.begin(), numbers.end(), is_even);
    std::cout << "Even numbers count: " << even_count << std::endl;
}

int main() {
    std::cout << "C++ Programming Paradigms Demonstration" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    // 1. Procedural paradigm
    std::cout << "\n1. PROCEDURAL PARADIGM:" << std::endl;
    std::vector<int> nums = {10, 20, 30, 40, 50};
    print_numbers(nums);
    std::cout << "Sum of first two: " << add(nums[0], nums[1]) << std::endl;
    
    // 2. Object-oriented paradigm
    std::cout << "\n2. OBJECT-ORIENTED PARADIGM:" << std::endl;
    Calculator calc;
    double result = calc.multiply(15.5, 2.0);
    std::cout << "15.5 * 2.0 = " << result << std::endl;
    std::cout << "Last result: " << calc.get_last_result() << std::endl;
    
    // 3. Generic paradigm
    std::cout << "\n3. GENERIC PARADIGM:" << std::endl;
    std::cout << "Maximum of 10 and 25: " << maximum(10, 25) << std::endl;
    std::cout << "Maximum of 3.14 and 2.71: " << maximum(3.14, 2.71) << std::endl;
    std::cout << "Maximum of 'a' and 'z': " << maximum('a', 'z') << std::endl;
    
    // 4. Functional paradigm
    std::cout << "\n4. FUNCTIONAL PARADIGM:" << std::endl;
    demonstrate_functional_paradigm();
    
    std::cout << "\nThis demonstrates how C++ supports multiple programming paradigms!" << std::endl;
    return 0;
}
