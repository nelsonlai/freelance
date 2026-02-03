/*
 * TEMPLATE INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate template concepts including specialization, SFINAE, and advanced patterns:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced TEMPLATE concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic TEMPLATE concepts
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
#include <string>
#include <vector>
#include <type_traits>
#include <memory>
#include <algorithm>
using namespace std;

// Template specialization
template<typename T>
class TypeInfo {
public:
    static string getName() {
        return "Unknown type";
    }
    
    static bool isNumeric() {
        return false;
    }
};

// Specialization for int
template<>
class TypeInfo<int> {
public:
    static string getName() {
        return "int";
    }
    
    static bool isNumeric() {
        return true;
    }
};

// Specialization for double
template<>
class TypeInfo<double> {
public:
    static string getName() {
        return "double";
    }
    
    static bool isNumeric() {
        return true;
    }
};

// Specialization for string
template<>
class TypeInfo<string> {
public:
    static string getName() {
        return "string";
    }
    
    static bool isNumeric() {
        return false;
    }
};

// Variadic templates
template<typename... Args>
void printAll(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename... Args>
auto sumAll(Args... args) -> decltype((args + ...)) {
    return (args + ...);
}

// Template with SFINAE
template<typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
safeDivide(T a, T b) {
    if (b == 0) {
        throw invalid_argument("Division by zero");
    }
    return a / b;
}

// Template with concepts (C++20 style simulation)
template<typename T>
concept Numeric = is_arithmetic_v<T>;

template<Numeric T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// CRTP (Curiously Recurring Template Pattern)
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void commonFunction() {
        cout << "Common functionality" << endl;
    }
};

class Concrete : public Base<Concrete> {
public:
    void implementation() {
        cout << "Concrete implementation" << endl;
    }
};

// Template metaprogramming
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

// Template with type traits
template<typename T>
class TypeChecker {
public:
    static void check() {
        cout << "Type: " << typeid(T).name() << endl;
        cout << "Is pointer: " << is_pointer_v<T> << endl;
        cout << "Is reference: " << is_reference_v<T> << endl;
        cout << "Is arithmetic: " << is_arithmetic_v<T> << endl;
        cout << "Is class: " << is_class_v<T> << endl;
    }
};

// Template with perfect forwarding
template<typename T>
class PerfectWrapper {
private:
    T value;
    
public:
    template<typename U>
    PerfectWrapper(U&& val) : value(forward<U>(val)) {}
    
    T getValue() const { return value; }
    
    template<typename U>
    void setValue(U&& val) {
        value = forward<U>(val);
    }
};

// Template with variadic class
template<typename... Types>
class VariadicClass {
public:
    void printTypes() {
        ((cout << "Type: " << typeid(Types).name() << endl), ...);
    }
    
    template<typename T>
    bool contains() {
        return (is_same_v<T, Types> || ...);
    }
};

// Template with lambda
template<typename T>
auto createProcessor(T&& processor) {
    return [processor = forward<T>(processor)](auto&&... args) {
        return processor(forward<decltype(args)>(args)...);
    };
}

// Template with memory management
template<typename T>
class SmartArray {
private:
    unique_ptr<T[]> data;
    size_t size;
    
public:
    SmartArray(size_t s) : size(s), data(make_unique<T[]>(s)) {}
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    size_t getSize() const { return size; }
    
    void fill(T value) {
        fill(data.get(), data.get() + size, value);
    }
    
    void display() const {
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// Template with function objects
template<typename T>
class Comparator {
public:
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template<typename T, typename Compare = Comparator<T>>
class SortedVector {
private:
    vector<T> data;
    Compare comp;
    
public:
    void insert(T value) {
        data.insert(
            lower_bound(data.begin(), data.end(), value, comp),
            value
        );
    }
    
    void display() const {
        for (const auto& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
    
    size_t size() const { return data.size(); }
};

// Template with exception handling
template<typename T>
class SafeContainer {
private:
    vector<T> data;
    
public:
    void add(T value) {
        try {
            data.push_back(value);
        } catch (const exception& e) {
            cout << "Error adding value: " << e.what() << endl;
        }
    }
    
    T get(size_t index) const {
        if (index >= data.size()) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t size() const { return data.size(); }
};

int main() {
    cout << "=== TEMPLATE INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Template specialization
    cout << "1. Template Specialization:" << endl;
    cout << "int: " << TypeInfo<int>::getName() << " (numeric: " << TypeInfo<int>::isNumeric() << ")" << endl;
    cout << "double: " << TypeInfo<double>::getName() << " (numeric: " << TypeInfo<double>::isNumeric() << ")" << endl;
    cout << "string: " << TypeInfo<string>::getName() << " (numeric: " << TypeInfo<string>::isNumeric() << ")" << endl;
    cout << endl;
    
    // Example 2: Variadic templates
    cout << "2. Variadic Templates:" << endl;
    printAll(1, 2, 3, "hello", 4.5);
    printAll("Template", "Programming", "C++");
    
    cout << "Sum of 1, 2, 3, 4, 5: " << sumAll(1, 2, 3, 4, 5) << endl;
    cout << "Sum of 1.1, 2.2, 3.3: " << sumAll(1.1, 2.2, 3.3) << endl;
    cout << endl;
    
    // Example 3: SFINAE
    cout << "3. SFINAE (Substitution Failure Is Not An Error):" << endl;
    try {
        cout << "10 / 2 = " << safeDivide(10, 2) << endl;
        cout << "15.0 / 3.0 = " << safeDivide(15.0, 3.0) << endl;
        cout << "10 / 0 = " << safeDivide(10, 0) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 4: Concepts (C++20 style)
    cout << "4. Concepts (C++20 style):" << endl;
    cout << "Max of 5 and 10: " << maximum(5, 10) << endl;
    cout << "Max of 3.14 and 2.71: " << maximum(3.14, 2.71) << endl;
    cout << endl;
    
    // Example 5: CRTP
    cout << "5. CRTP (Curiously Recurring Template Pattern):" << endl;
    Concrete concrete;
    concrete.interface();
    concrete.commonFunction();
    cout << endl;
    
    // Example 6: Template metaprogramming
    cout << "6. Template Metaprogramming:" << endl;
    cout << "Factorial of 5: " << Factorial<5>::value << endl;
    cout << "Factorial of 7: " << Factorial<7>::value << endl;
    cout << "Factorial of 10: " << Factorial<10>::value << endl;
    cout << endl;
    
    // Example 7: Type traits
    cout << "7. Type Traits:" << endl;
    TypeChecker<int>::check();
    cout << endl;
    TypeChecker<string>::check();
    cout << endl;
    
    // Example 8: Perfect forwarding
    cout << "8. Perfect Forwarding:" << endl;
    PerfectWrapper<string> wrapper1("Hello");
    PerfectWrapper<string> wrapper2(string("World"));
    
    cout << "Wrapper 1: " << wrapper1.getValue() << endl;
    cout << "Wrapper 2: " << wrapper2.getValue() << endl;
    cout << endl;
    
    // Example 9: Variadic class
    cout << "9. Variadic Class:" << endl;
    VariadicClass<int, string, double> vc;
    vc.printTypes();
    cout << "Contains int: " << vc.contains<int>() << endl;
    cout << "Contains float: " << vc.contains<float>() << endl;
    cout << endl;
    
    // Example 10: Template with lambda
    cout << "10. Template with Lambda:" << endl;
    auto processor = createProcessor([](int x) { return x * 2; });
    cout << "Process 5: " << processor(5) << endl;
    
    auto stringProcessor = createProcessor([](const string& s) { return s + " processed"; });
    cout << "Process string: " << stringProcessor(string("Hello")) << endl;
    cout << endl;
    
    // Example 11: Memory management
    cout << "11. Memory Management:" << endl;
    SmartArray<int> smartArray(5);
    smartArray.fill(42);
    smartArray.display();
    
    for (size_t i = 0; i < smartArray.getSize(); i++) {
        smartArray[i] = i * 10;
    }
    smartArray.display();
    cout << endl;
    
    // Example 12: Function objects
    cout << "12. Function Objects:" << endl;
    SortedVector<int> sortedVec;
    sortedVec.insert(30);
    sortedVec.insert(10);
    sortedVec.insert(50);
    sortedVec.insert(20);
    sortedVec.insert(40);
    
    cout << "Sorted vector: ";
    sortedVec.display();
    cout << endl;
    
    // Example 13: Exception handling
    cout << "13. Exception Handling:" << endl;
    SafeContainer<int> safeContainer;
    safeContainer.add(10);
    safeContainer.add(20);
    safeContainer.add(30);
    
    try {
        cout << "Element 0: " << safeContainer.get(0) << endl;
        cout << "Element 1: " << safeContainer.get(1) << endl;
        cout << "Element 5: " << safeContainer.get(5) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 14: Template with algorithms
    cout << "14. Template with Algorithms:" << endl;
    vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    auto findMax = [](const vector<int>& vec) {
        return *max_element(vec.begin(), vec.end());
    };
    
    auto findMin = [](const vector<int>& vec) {
        return *min_element(vec.begin(), vec.end());
    };
    
    cout << "Numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    cout << "Max: " << findMax(numbers) << endl;
    cout << "Min: " << findMin(numbers) << endl;
    
    return 0;
}
