/*
 * TEMPLATE BEGINNER EXAMPLES
 * 
 * This file demonstrates basic template concepts including function templates, class templates, and type parameters:
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

/*
 * TEMPLATE BEGINNER EXAMPLES
 * 
 * This file demonstrates basic template concepts in C++:
 * - Basic function templates
 * - Class templates with type and non-type parameters
 * - Template instantiation and type deduction
 * - Template specialization
 * - Templates with different data types
 * 
 * Learning Objectives:
 * - Understand what templates are and why they're useful
 * - Learn how to declare and use function templates
 * - Master basic class template syntax
 * - Understand template instantiation
 * - Learn about template parameters and specialization
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
#include <vector>    // For vector container
using namespace std; // Using standard namespace (for beginners)

/*
 * BASIC FUNCTION TEMPLATE
 * 
 * A function template is a blueprint for creating functions that work with
 * different data types. The compiler generates specific functions based on
 * the types used when the template is called.
 * 
 * Key Points:
 * - 'template<typename T>' declares a template with type parameter T
 * - T can be any type (int, double, string, etc.)
 * - The compiler generates a separate function for each type used
 * - This avoids code duplication for similar functions
 * 
 * @param a First value to compare
 * @param b Second value to compare
 * @return The larger of the two values
 */
template<typename T>
T getMax(T a, T b) {
    // Compare the values and return the larger one
    // override: operator> must be defined for type T
    return (a > b) ? a : b;  // Return the larger value using ternary operator
}


// Function template with multiple types
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

// Function template with explicit return type
template<typename T>
T square(T value) {
    return value * value;
}

// Function template with default parameter
template<typename T = int>
T multiply(T a, T b) {
    return a * b;
}

// Basic class template
template<typename T>
class Box {
private:
    T content;
    
public:
    Box(T value) : content(value) {}
    
    T getContent() const {
        return content;
    }
    
    void setContent(T value) {
        content = value;
    }
    
    void display() const {
        cout << "Box contains: " << content << endl;
    }
};

// Class template with multiple parameters
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;
    
public:
    Pair(T f, U s) : first(f), second(s) {}
    
    T getFirst() const { return first; }
    U getSecond() const { return second; }
    
    void setFirst(T f) { first = f; }
    void setSecond(U s) { second = s; }
    
    void display() const {
        cout << "Pair: (" << first << ", " << second << ")" << endl;
    }
};

// Class template with non-type parameter
template<typename T, int SIZE>
class Array {
private:
    T data[SIZE];
    
public:
    void set(int index, T value) {
        if (index >= 0 && index < SIZE) {
            data[index] = value;
        }
    }
    
    T get(int index) const {
        if (index >= 0 && index < SIZE) {
            return data[index];
        }
        return T{};
    }
    
    int size() const { return SIZE; }
    
    void display() const {
        cout << "Array[" << SIZE << "]: ";
        for (int i = 0; i < SIZE; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// Template with vector
template<typename T>
class VectorWrapper {
private:
    vector<T> data;
    
public:
    void add(T value) {
        data.push_back(value);
    }
    
    T get(int index) const {
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        return T{};
    }
    
    int size() const { return data.size(); }
    
    void display() const {
        cout << "Vector contents: ";
        for (const auto& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
};

// Template function with string
template<typename T>
string toString(T value) {
    return to_string(value);
}

// Specialization for string
template<>
string toString<string>(string value) {
    return value;
}

int main() {
    cout << "=== TEMPLATE BEGINNER EXAMPLES ===" << endl << endl;
    
    // Example 1: Basic function templates
    cout << "1. Basic Function Templates:" << endl;
    cout << "Max of 5 and 10: " << getMax(5, 10) << endl;
    cout << "Max of 3.14 and 2.71: " << getMax(3.14, 2.71) << endl;
    cout << "Max of 'a' and 'z': " << getMax('a', 'z') << endl;
    cout << endl;
    
    // Example 2: Function templates with multiple types
    cout << "2. Function Templates with Multiple Types:" << endl;
    cout << "Add int and double: " << add(5, 3.14) << endl;
    cout << "Add string and int: " << add(string("Hello"), 5) << endl;
    cout << "Square of 5: " << square(5) << endl;
    cout << "Square of 3.14: " << square(3.14) << endl;
    cout << endl;
    
    // Example 3: Function templates with default parameters
    cout << "3. Function Templates with Default Parameters:" << endl;
    cout << "Multiply ints: " << multiply(5, 3) << endl;
    cout << "Multiply doubles: " << multiply<double>(2.5, 4.0) << endl;
    cout << "Multiply with default type: " << multiply(10, 20) << endl;
    cout << endl;
    
    // Example 4: Basic class templates
    cout << "4. Basic Class Templates:" << endl;
    Box<int> intBox(42);
    Box<string> stringBox("Hello World");
    Box<double> doubleBox(3.14159);
    
    intBox.display();
    stringBox.display();
    doubleBox.display();
    cout << endl;
    
    // Example 5: Class templates with multiple parameters
    cout << "5. Class Templates with Multiple Parameters:" << endl;
    Pair<int, string> pair1(1, "First");
    Pair<string, double> pair2("Pi", 3.14159);
    Pair<char, int> pair3('A', 65);
    
    pair1.display();
    pair2.display();
    pair3.display();
    cout << endl;
    
    // Example 6: Class templates with non-type parameters
    cout << "6. Class Templates with Non-type Parameters:" << endl;
    Array<int, 5> intArray;
    Array<string, 3> stringArray;
    
    // Fill int array
    for (int i = 0; i < 5; i++) {
        intArray.set(i, i * 10);
    }
    
    // Fill string array
    stringArray.set(0, "Hello");
    stringArray.set(1, "World");
    stringArray.set(2, "C++");
    
    intArray.display();
    stringArray.display();
    cout << endl;
    
    // Example 7: Template with vector
    cout << "7. Template with Vector:" << endl;
    VectorWrapper<int> intVector;
    VectorWrapper<string> stringVector;
    
    intVector.add(10);
    intVector.add(20);
    intVector.add(30);
    
    stringVector.add("Template");
    stringVector.add("Programming");
    stringVector.add("C++");
    
    intVector.display();
    stringVector.display();
    cout << endl;
    
    // Example 8: Template specialization
    cout << "8. Template Specialization:" << endl;
    cout << "toString(42): " << toString(42) << endl;
    cout << "toString(3.14): " << toString(3.14) << endl;
    cout << "toString(string): " << toString(string("Hello")) << endl;
    cout << endl;
    
    // Example 9: Template with different data types
    cout << "9. Template with Different Data Types:" << endl;
    Box<bool> boolBox(true);
    Box<char> charBox('X');
    Box<float> floatBox(2.718f);
    
    boolBox.display();
    charBox.display();
    floatBox.display();
    cout << endl;
    
    // Example 10: Template with calculations
    cout << "10. Template with Calculations:" << endl;
    cout << "Square of 7: " << square(7) << endl;
    cout << "Square of 2.5: " << square(2.5) << endl;
    cout << "Square of 100: " << square(100) << endl;
    
    // Template with different operations
    auto subtract = [](auto a, auto b) { return a - b; };
    cout << "Subtract 10 - 3: " << subtract(10, 3) << endl;
    cout << "Subtract 5.5 - 2.3: " << subtract(5.5, 2.3) << endl;
    
    return 0;
}
