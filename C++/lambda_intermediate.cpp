/*
 * LAMBDA INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate lambda concepts including advanced capture modes, generic lambdas, and STL integration:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced LAMBDA concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic LAMBDA concepts
 * - Familiarity with intermediate C++ features
 * - Understanding of memory management
 * - Knowledge of STL containers and algorithms
 * 
 * Key Topics Covered:
 * - Advanced syntax and features
 * - Performance optimization
 * - Error handling and safety
 * - Modern C++ practices
 * - Real-world applications
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <map>
using namespace std;

// Function that takes lambda as parameter
void processVector(vector<int>& vec, function<void(int&)> processor) {
    for (auto& element : vec) {
        processor(element);
    }
}

// Function that returns lambda
function<int(int)> createMultiplier(int factor) {
    return [factor](int x) { return x * factor; };
}

// Template function with lambda
template<typename Container, typename Predicate>
void printIf(const Container& container, Predicate pred) {
    for (const auto& element : container) {
        if (pred(element)) {
            cout << element << " ";
        }
    }
    cout << endl;
}

// Class with lambda member
class Calculator {
private:
    function<double(double, double)> operation;
    
public:
    Calculator(function<double(double, double)> op) : operation(op) {}
    
    double calculate(double a, double b) {
        return operation(a, b);
    }
    
    void setOperation(function<double(double, double)> op) {
        operation = op;
    }
};

// Lambda with complex capture
class LambdaCaptureDemo {
private:
    int value;
    string name;
    
public:
    LambdaCaptureDemo(int v, const string& n) : value(v), name(n) {}
    
    function<void()> createGreeting() {
        // Capture by value
        return [value = this->value, name = this->name]() {
            cout << "Hello from " << name << " with value " << value << endl;
        };
    }
    
    function<void()> createCounter() {
        // Capture by reference with mutable
        return [this]() mutable {
            value++;
            cout << "Counter: " << value << endl;
        };
    }
};

// Lambda with move semantics
class MoveDemo {
private:
    unique_ptr<string> data;
    
public:
    MoveDemo(const string& s) : data(make_unique<string>(s)) {}
    
    function<string()> createGetter() {
        // Move capture
        return [data = move(data)]() {
            return *data;
        };
    }
};

// Lambda with variadic capture
template<typename... Args>
auto createVariadicLambda(Args... args) {
    return [args...](int multiplier) {
        return ((args * multiplier) + ...);
    };
}

// Lambda with perfect forwarding
template<typename T>
auto createForwardingLambda(T&& value) {
    return [value = forward<T>(value)]() {
        cout << "Forwarded value: " << value << endl;
    };
}

// Lambda with exception handling
auto createSafeLambda() {
    return []() {
        try {
            throw runtime_error("Test exception");
        } catch (const exception& e) {
            cout << "Caught exception: " << e.what() << endl;
        }
    };
}

// Lambda with recursion
function<int(int)> createFactorial() {
    function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    return factorial;
}

// Lambda with state
auto createStatefulLambda() {
    int count = 0;
    return [count]() mutable {
        return ++count;
    };
}

// Lambda with complex return type
auto createComplexLambda() {
    return [](int x) -> pair<int, string> {
        return {x * 2, "Result: " + to_string(x * 2)};
    };
}

int main() {
    cout << "=== LAMBDA INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Lambda with different capture modes
    cout << "1. Lambda with Different Capture Modes:" << endl;
    int x = 10, y = 20;
    
    // Capture by value
    auto addX = [x](int a) { return a + x; };
    cout << "addX(5) = " << addX(5) << endl;
    
    // Capture by reference
    auto modifyY = [&y](int a) { y += a; };
    modifyY(5);
    cout << "After modifyY(5), y = " << y << endl;
    
    // Capture all by value
    auto addAll = [=](int a) { return a + x + y; };
    cout << "addAll(5) = " << addAll(5) << endl;
    
    // Capture all by reference
    auto modifyAll = [&](int a) { x += a; y += a; };
    modifyAll(3);
    cout << "After modifyAll(3), x = " << x << ", y = " << y << endl;
    cout << endl;
    
    // Example 2: Lambda with STL algorithms
    cout << "2. Lambda with STL Algorithms:" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "Original numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Transform with lambda
    vector<int> doubled;
    transform(numbers.begin(), numbers.end(), back_inserter(doubled),
        [](int x) { return x * 2; });
    
    cout << "Doubled numbers: ";
    for (int n : doubled) cout << n << " ";
    cout << endl;
    
    // Filter with lambda
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evens),
        [](int x) { return x % 2 == 0; });
    
    cout << "Even numbers: ";
    for (int n : evens) cout << n << " ";
    cout << endl;
    
    // Sort with lambda
    vector<string> words = {"apple", "banana", "cherry", "date"};
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });
    
    cout << "Words sorted by length: ";
    for (const string& w : words) cout << w << " ";
    cout << endl;
    cout << endl;
    
    // Example 3: Lambda with function parameters
    cout << "3. Lambda with Function Parameters:" << endl;
    vector<int> data = {1, 2, 3, 4, 5};
    
    cout << "Original data: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // Process with lambda
    processVector(data, [](int& x) { x *= 3; });
    
    cout << "After multiplying by 3: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    cout << endl;
    
    // Example 4: Lambda returning functions
    cout << "4. Lambda Returning Functions:" << endl;
    auto doubler = createMultiplier(2);
    auto tripler = createMultiplier(3);
    
    cout << "doubler(5) = " << doubler(5) << endl;
    cout << "tripler(5) = " << tripler(5) << endl;
    cout << endl;
    
    // Example 5: Template with lambda
    cout << "5. Template with Lambda:" << endl;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "Numbers greater than 5: ";
    printIf(nums, [](int x) { return x > 5; });
    
    cout << "Even numbers: ";
    printIf(nums, [](int x) { return x % 2 == 0; });
    cout << endl;
    
    // Example 6: Lambda with class members
    cout << "6. Lambda with Class Members:" << endl;
    Calculator calc([](double a, double b) { return a + b; });
    cout << "Addition: " << calc.calculate(5, 3) << endl;
    
    calc.setOperation([](double a, double b) { return a * b; });
    cout << "Multiplication: " << calc.calculate(5, 3) << endl;
    cout << endl;
    
    // Example 7: Complex capture
    cout << "7. Complex Capture:" << endl;
    LambdaCaptureDemo demo(42, "Test");
    
    auto greeting = demo.createGreeting();
    greeting();
    
    auto counter = demo.createCounter();
    counter();
    counter();
    counter();
    cout << endl;
    
    // Example 8: Move semantics with lambda
    cout << "8. Move Semantics with Lambda:" << endl;
    MoveDemo moveDemo("Hello World");
    auto getter = moveDemo.createGetter();
    cout << "Data from lambda: " << getter() << endl;
    cout << endl;
    
    // Example 9: Variadic lambda
    cout << "9. Variadic Lambda:" << endl;
    auto variadicLambda = createVariadicLambda(1, 2, 3, 4, 5);
    cout << "Variadic lambda result: " << variadicLambda(2) << endl;
    cout << endl;
    
    // Example 10: Perfect forwarding with lambda
    cout << "10. Perfect Forwarding with Lambda:" << endl;
    auto forwardingLambda = createForwardingLambda(string("Forwarded"));
    forwardingLambda();
    cout << endl;
    
    // Example 11: Exception handling with lambda
    cout << "11. Exception Handling with Lambda:" << endl;
    auto safeLambda = createSafeLambda();
    safeLambda();
    cout << endl;
    
    // Example 12: Recursive lambda
    cout << "12. Recursive Lambda:" << endl;
    auto factorial = createFactorial();
    cout << "Factorial of 5: " << factorial(5) << endl;
    cout << "Factorial of 7: " << factorial(7) << endl;
    cout << endl;
    
    // Example 13: Stateful lambda
    cout << "13. Stateful Lambda:" << endl;
    auto counter = createStatefulLambda();
    cout << "Counter calls: " << counter() << " " << counter() << " " << counter() << endl;
    cout << endl;
    
    // Example 14: Complex return type
    cout << "14. Complex Return Type:" << endl;
    auto complexLambda = createComplexLambda();
    auto result = complexLambda(21);
    cout << "Result: " << result.first << ", " << result.second << endl;
    cout << endl;
    
    // Example 15: Lambda with containers
    cout << "15. Lambda with Containers:" << endl;
    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
    
    cout << "High scores (>= 90): ";
    for (const auto& pair : scores) {
        if (pair.second >= 90) {
            cout << pair.first << "(" << pair.second << ") ";
        }
    }
    cout << endl;
    
    // Lambda with map operations
    vector<pair<string, int>> highScores;
    copy_if(scores.begin(), scores.end(), back_inserter(highScores),
        [](const pair<string, int>& p) { return p.second >= 90; });
    
    cout << "High scores using lambda: ";
    for (const auto& pair : highScores) {
        cout << pair.first << "(" << pair.second << ") ";
    }
    cout << endl;
    
    return 0;
}
