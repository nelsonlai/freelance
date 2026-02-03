/*
 * FUNCTION INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate function concepts including overloading, templates, and advanced techniques:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced FUNCTION concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic FUNCTION concepts
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
#include <functional>
#include <algorithm>
#include <memory>
using namespace std;

// Function overloading
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

string add(const string& a, const string& b) {
    return a + b;
}

// Function with default parameters
void printInfo(const string& name, int age = 18, const string& city = "Unknown") {
    cout << "Name: " << name << ", Age: " << age << ", City: " << city << endl;
}

// Inline function
inline int square(int x) {
    return x * x;
}

// Function with reference parameters
void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function with const reference
void printVector(const vector<int>& vec) {
    cout << "Vector contents: ";
    for (const auto& element : vec) {
        cout << element << " ";
    }
    cout << endl;
}

// Function returning reference
int& getElement(vector<int>& vec, size_t index) {
    return vec[index];
}

// Function with function pointer parameter
void applyOperation(vector<int>& vec, int (*operation)(int)) {
    for (auto& element : vec) {
        element = operation(element);
    }
}

// Function with lambda parameter
void processNumbers(vector<int>& numbers, function<int(int)> processor) {
    for (auto& num : numbers) {
        num = processor(num);
    }
}

// Recursive function
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Template function with multiple types
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// Function with variadic templates
template<typename... Args>
void printAll(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

// Function with std::function
function<int(int)> createMultiplier(int factor) {
    return [factor](int x) { return x * factor; };
}

// Function returning lambda
auto createAdder(int value) {
    return [value](int x) { return x + value; };
}

// Function with exception handling
double safeDivide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("Division by zero");
    }
    return a / b;
}

// Function with RAII
class ResourceManager {
private:
    string resource;
    
public:
    ResourceManager(const string& res) : resource(res) {
        cout << "Acquired resource: " << resource << endl;
    }
    
    ~ResourceManager() {
        cout << "Released resource: " << resource << endl;
    }
    
    void useResource() {
        cout << "Using resource: " << resource << endl;
    }
};

void useResource(const string& resourceName) {
    ResourceManager rm(resourceName);
    rm.useResource();
    // Resource automatically released when function exits
}

// Function with move semantics
vector<int> createLargeVector(size_t size) {
    vector<int> result;
    result.reserve(size);
    
    for (size_t i = 0; i < size; i++) {
        result.push_back(static_cast<int>(i));
    }
    
    return result;  // Move semantics will be used
}

// Function with perfect forwarding
template<typename T>
void forwardValue(T&& value) {
    cout << "Forwarded value: " << value << endl;
}

int main() {
    cout << "=== FUNCTION INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Function overloading
    cout << "1. Function Overloading:" << endl;
    cout << "add(5, 3) = " << add(5, 3) << endl;
    cout << "add(3.14, 2.86) = " << add(3.14, 2.86) << endl;
    cout << "add(\"Hello\", \" World\") = " << add(string("Hello"), string(" World")) << endl;
    cout << endl;
    
    // Example 2: Default parameters
    cout << "2. Default Parameters:" << endl;
    printInfo("Alice");
    printInfo("Bob", 25);
    printInfo("Charlie", 30, "New York");
    cout << endl;
    
    // Example 3: Inline functions
    cout << "3. Inline Functions:" << endl;
    cout << "square(5) = " << square(5) << endl;
    cout << "square(7) = " << square(7) << endl;
    cout << endl;
    
    // Example 4: Reference parameters
    cout << "4. Reference Parameters:" << endl;
    int x = 10, y = 20;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swapValues(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    cout << endl;
    
    // Example 5: Const reference
    cout << "5. Const Reference:" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5};
    printVector(numbers);
    cout << endl;
    
    // Example 6: Function returning reference
    cout << "6. Function Returning Reference:" << endl;
    vector<int> vec = {10, 20, 30, 40, 50};
    cout << "Original vector: ";
    printVector(vec);
    
    getElement(vec, 2) = 99;  // Modify element through reference
    cout << "After modifying element 2: ";
    printVector(vec);
    cout << endl;
    
    // Example 7: Function pointers
    cout << "7. Function Pointers:" << endl;
    vector<int> data = {1, 2, 3, 4, 5};
    cout << "Original data: ";
    printVector(data);
    
    applyOperation(data, [](int x) { return x * x; });
    cout << "After squaring: ";
    printVector(data);
    cout << endl;
    
    // Example 8: Function with std::function
    cout << "8. Function with std::function:" << endl;
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << "Original numbers: ";
    printVector(nums);
    
    processNumbers(nums, [](int x) { return x + 10; });
    cout << "After adding 10: ";
    printVector(nums);
    cout << endl;
    
    // Example 9: Recursive functions
    cout << "9. Recursive Functions:" << endl;
    cout << "Factorial of 5: " << factorial(5) << endl;
    cout << "Factorial of 7: " << factorial(7) << endl;
    cout << endl;
    
    // Example 10: Template functions
    cout << "10. Template Functions:" << endl;
    cout << "maximum(10, 20) = " << maximum(10, 20) << endl;
    cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << endl;
    cout << "multiply(5, 3.14) = " << multiply(5, 3.14) << endl;
    cout << endl;
    
    // Example 11: Variadic templates
    cout << "11. Variadic Templates:" << endl;
    printAll(1, 2, 3, "hello", 4.5);
    printAll("A", "B", "C");
    cout << endl;
    
    // Example 12: Function returning function
    cout << "12. Function Returning Function:" << endl;
    auto doubler = createMultiplier(2);
    auto tripler = createMultiplier(3);
    
    cout << "doubler(5) = " << doubler(5) << endl;
    cout << "tripler(5) = " << tripler(5) << endl;
    
    auto addFive = createAdder(5);
    cout << "addFive(10) = " << addFive(10) << endl;
    cout << endl;
    
    // Example 13: Exception handling
    cout << "13. Exception Handling:" << endl;
    try {
        cout << "10 / 2 = " << safeDivide(10, 2) << endl;
        cout << "10 / 0 = " << safeDivide(10, 0) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 14: RAII
    cout << "14. RAII (Resource Acquisition Is Initialization):" << endl;
    useResource("Database Connection");
    cout << "Resource automatically released" << endl;
    cout << endl;
    
    // Example 15: Move semantics
    cout << "15. Move Semantics:" << endl;
    auto largeVec = createLargeVector(1000);
    cout << "Created vector with " << largeVec.size() << " elements" << endl;
    cout << "First few elements: ";
    for (size_t i = 0; i < min(size_t(5), largeVec.size()); i++) {
        cout << largeVec[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    // Example 16: Perfect forwarding
    cout << "16. Perfect Forwarding:" << endl;
    forwardValue(42);
    forwardValue(string("Hello"));
    forwardValue(3.14);
    
    return 0;
}
