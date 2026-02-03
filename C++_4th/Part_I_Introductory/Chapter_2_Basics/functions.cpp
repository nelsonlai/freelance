#include <iostream>
#include <string>
#include <vector>

// Function declarations
int add(int a, int b);
double multiply(double a, double b);
void print_message(const std::string& message);
void print_numbers(const std::vector<int>& numbers);
int factorial(int n);
bool is_prime(int n);
void swap_values(int& a, int& b);
int get_max_value(const std::vector<int>& numbers);

// Function definitions
int add(int a, int b) {

    return a + b;
}

double multiply(double a, double b) {
    return a * b;
}

void print_message(const std::string& message) {
    std::cout << "Message: " << message << std::endl;
}

void print_numbers(const std::vector<int>& numbers) {
    std::cout << "Numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Recursive function
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Function with complex logic
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function with reference parameters
void swap_values(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function with const reference parameter
int get_max_value(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        return 0;
    }
    
    int max_val = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
    }
    return max_val;
}

// Function overloading examples
void display(int value) {
    std::cout << "Integer: " << value << std::endl;
}

void display(double value) {
    std::cout << "Double: " << value << std::endl;
}

void display(const std::string& value) {
    std::cout << "String: " << value << std::endl;
}

// Function with default parameters
void greet(const std::string& name, const std::string& greeting = "Hello") {
    std::cout << greeting << ", " << name << "!" << std::endl;
}

// Function returning multiple values (using references)
void divide(int a, int b, int& quotient, int& remainder) {
    quotient = a / b;
    remainder = a % b;
}

int main() {
    std::cout << "C++ Functions Demonstration" << std::endl;
    std::cout << "===========================" << std::endl;
    
    // 1. Basic functions
    std::cout << "\n1. BASIC FUNCTIONS:" << std::endl;
    
    int sum = add(10, 20);
    std::cout << "10 + 20 = " << sum << std::endl;
    
    double product = multiply(3.14, 2.0);
    std::cout << "3.14 * 2.0 = " << product << std::endl;
    
    // 2. Functions with no return value
    std::cout << "\n2. VOID FUNCTIONS:" << std::endl;
    
    print_message("Welcome to C++ functions!");
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    print_numbers(numbers);
    
    // 3. Recursive functions
    std::cout << "\n3. RECURSIVE FUNCTIONS:" << std::endl;
    
    int n = 5;
    std::cout << "Factorial of " << n << " = " << factorial(n) << std::endl;
    
    // 4. Functions with complex logic
    std::cout << "\n4. COMPLEX LOGIC FUNCTIONS:" << std::endl;
    
    std::cout << "Prime numbers from 2 to 20: ";
    for (int i = 2; i <= 20; ++i) {
        if (is_prime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    
    // 5. Functions with reference parameters
    std::cout << "\n5. REFERENCE PARAMETERS:" << std::endl;
    
    int x = 10, y = 20;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap_values(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    // 6. Functions with const reference parameters
    std::cout << "\n6. CONST REFERENCE PARAMETERS:" << std::endl;
    
    std::vector<int> test_numbers = {15, 3, 8, 22, 7};
    print_numbers(test_numbers);
    std::cout << "Maximum value: " << get_max_value(test_numbers) << std::endl;
    
    // 7. Function overloading
    std::cout << "\n7. FUNCTION OVERLOADING:" << std::endl;
    
    display(42);
    display(3.14);
    display(std::string("Hello"));
    
    // 8. Default parameters
    std::cout << "\n8. DEFAULT PARAMETERS:" << std::endl;
    
    greet("Alice");
    greet("Bob", "Good morning");
    
    // 9. Functions returning multiple values
    std::cout << "\n9. MULTIPLE RETURN VALUES:" << std::endl;
    
    int dividend = 17, divisor = 5;
    int quotient, remainder;
    divide(dividend, divisor, quotient, remainder);
    
    std::cout << dividend << " ÷ " << divisor << " = " << quotient 
              << " remainder " << remainder << std::endl;
    
    return 0;
}
