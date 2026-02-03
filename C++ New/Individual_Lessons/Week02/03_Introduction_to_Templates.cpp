/*
 * Lesson 2.3: Introduction to Templates
 * 
 * This file demonstrates function templates, class templates,
 * template instantiation, and generic programming concepts.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

// Function template for finding maximum of two values
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Function template with multiple parameters
template<typename T, typename U>
void printPair(T first, U second) {
    std::cout << "Pair: (" << first << ", " << second << ")" << std::endl;
}

// Function template for array operations
template<typename T, int SIZE>
void printArray(T (&arr)[SIZE]) {
    std::cout << "Array contents: ";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Function template for finding minimum
template<typename T>
T minimum(T a, T b) {
    return (a < b) ? a : b;
}

// Function template for swapping values
template<typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Function template for calculating average
template<typename T>
double calculateAverage(const T* arr, size_t size) {
    if (size == 0) {
        return 0.0;
    }
    
    T sum = T{};  // Initialize with default value
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return static_cast<double>(sum) / size;
}

// Function to demonstrate function templates
void demonstrateFunctionTemplates() {
    std::cout << "=== Function Templates Demo ===" << std::endl;
    
    // Using maximum with different types
    std::cout << "Maximum of 10 and 20: " << maximum(10, 20) << std::endl;
    std::cout << "Maximum of 3.5 and 2.1: " << maximum(3.5, 2.1) << std::endl;
    std::cout << "Maximum of 'a' and 'z': " << maximum('a', 'z') << std::endl;
    std::cout << "Maximum of 'Hello' and 'World': " << maximum(std::string("Hello"), std::string("World")) << std::endl;
    
    // Using minimum
    std::cout << "\nMinimum of 15 and 25: " << minimum(15, 25) << std::endl;
    std::cout << "Minimum of 4.2 and 1.7: " << minimum(4.2, 1.7) << std::endl;
    
    // Using swapValues
    int x = 10, y = 20;
    std::cout << "\nBefore swap: x = " << x << ", y = " << y << std::endl;
    swapValues(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    // Using printPair with different types
    std::cout << "\nMixed type pairs:" << std::endl;
    printPair(42, "Hello");
    printPair(3.14, true);
    printPair('A', 65);
    
    // Using array template
    int numbers[] = {1, 2, 3, 4, 5};
    printArray(numbers);
    
    double decimals[] = {1.1, 2.2, 3.3};
    printArray(decimals);
    
    // Using calculateAverage
    int intArray[] = {10, 20, 30, 40, 50};
    double avg = calculateAverage(intArray, 5);
    std::cout << "Average of integers: " << avg << std::endl;
    
    double doubleArray[] = {1.5, 2.5, 3.5, 4.5};
    double avg2 = calculateAverage(doubleArray, 4);
    std::cout << "Average of doubles: " << avg2 << std::endl;
}

// Generic Stack class template
template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    // Constructor
    Stack() = default;
    
    // Push element onto stack
    void push(const T& item) {
        data.push_back(item);
        std::cout << "Pushed: " << item << std::endl;
    }
    
    // Pop element from stack
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty!");
        }
        T item = data.back();
        data.pop_back();
        std::cout << "Popped: " << item << std::endl;
        return item;
    }
    
    // Check if stack is empty
    bool isEmpty() const {
        return data.empty();
    }
    
    // Get current size
    size_t size() const {
        return data.size();
    }
    
    // Display stack contents
    void display() const {
        if (isEmpty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack contents (top to bottom): ";
        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // Peek at top element without removing
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty!");
        }
        return data.back();
    }
};

// Generic Queue class template
template<typename T>
class Queue {
private:
    std::vector<T> data;
    
public:
    // Constructor
    Queue() = default;
    
    // Enqueue element
    void enqueue(const T& item) {
        data.push_back(item);
        std::cout << "Enqueued: " << item << std::endl;
    }
    
    // Dequeue element
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        T item = data.front();
        data.erase(data.begin());
        std::cout << "Dequeued: " << item << std::endl;
        return item;
    }
    
    // Check if queue is empty
    bool isEmpty() const {
        return data.empty();
    }
    
    // Get current size
    size_t size() const {
        return data.size();
    }
    
    // Display queue contents
    void display() const {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue contents (front to back): ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Generic Pair class template
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;
    
public:
    // Constructor
    Pair(const T& f, const U& s) : first(f), second(s) {}
    
    // Getters
    const T& getFirst() const { return first; }
    const U& getSecond() const { return second; }
    
    // Setters
    void setFirst(const T& f) { first = f; }
    void setSecond(const U& s) { second = s; }
    
    // Display
    void display() const {
        std::cout << "Pair: (" << first << ", " << second << ")" << std::endl;
    }
};

// Function to demonstrate class templates
void demonstrateClassTemplates() {
    std::cout << "\n=== Class Templates Demo ===" << std::endl;
    
    // Integer Stack
    std::cout << "\n--- Integer Stack ---" << std::endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    
    std::cout << "Top element: " << intStack.peek() << std::endl;
    intStack.pop();
    intStack.display();
    
    // String Stack
    std::cout << "\n--- String Stack ---" << std::endl;
    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("C++");
    stringStack.display();
    
    // Integer Queue
    std::cout << "\n--- Integer Queue ---" << std::endl;
    Queue<int> intQueue;
    intQueue.enqueue(100);
    intQueue.enqueue(200);
    intQueue.enqueue(300);
    intQueue.display();
    
    intQueue.dequeue();
    intQueue.display();
    
    // Double Stack
    std::cout << "\n--- Double Stack ---" << std::endl;
    Stack<double> doubleStack;
    doubleStack.push(1.5);
    doubleStack.push(2.5);
    doubleStack.push(3.5);
    doubleStack.display();
    
    // Pair examples
    std::cout << "\n--- Pair Examples ---" << std::endl;
    Pair<int, std::string> pair1(42, "Answer");
    pair1.display();
    
    Pair<std::string, double> pair2("Pi", 3.14159);
    pair2.display();
    
    Pair<char, int> pair3('A', 65);
    pair3.display();
}

// Template specialization example
template<typename T>
void printInfo(T value) {
    std::cout << "Generic: " << value << std::endl;
}

// Specialization for strings
template<>
void printInfo<std::string>(std::string value) {
    std::cout << "String: \"" << value << "\" (length: " << value.length() << ")" << std::endl;
}

// Specialization for integers
template<>
void printInfo<int>(int value) {
    std::cout << "Integer: " << value << " (hex: 0x" << std::hex << value << std::dec << ")" << std::endl;
}

// Function to demonstrate template specialization
void demonstrateTemplateSpecialization() {
    std::cout << "\n=== Template Specialization Demo ===" << std::endl;
    
    printInfo(42);
    printInfo(3.14);
    printInfo(std::string("Hello"));
    printInfo('A');
    printInfo(true);
}

// Non-type template parameter example
template<typename T, int SIZE>
class FixedArray {
private:
    T data[SIZE];
    
public:
    // Constructor
    FixedArray() {
        for (int i = 0; i < SIZE; ++i) {
            data[i] = T{};  // Initialize with default value
        }
    }
    
    // Constructor with initial value
    FixedArray(const T& initialValue) {
        for (int i = 0; i < SIZE; ++i) {
            data[i] = initialValue;
        }
    }
    
    // Access operator
    T& operator[](int index) {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }
    
    // Size function
    int size() const { return SIZE; }
    
    // Display function
    void display() const {
        std::cout << "FixedArray<" << SIZE << ">: ";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Function to demonstrate non-type template parameters
void demonstrateNonTypeTemplateParameters() {
    std::cout << "\n=== Non-Type Template Parameters Demo ===" << std::endl;
    
    // Different sized arrays
    FixedArray<int, 5> intArray5;
    FixedArray<int, 10> intArray10(42);  // Initialize with 42
    FixedArray<double, 3> doubleArray3(3.14);
    
    // Fill arrays with values
    for (int i = 0; i < intArray5.size(); ++i) {
        intArray5[i] = i * 10;
    }
    
    for (int i = 0; i < intArray10.size(); ++i) {
        intArray10[i] = i;
    }
    
    for (int i = 0; i < doubleArray3.size(); ++i) {
        doubleArray3[i] = i * 1.5;
    }
    
    // Display arrays
    intArray5.display();
    intArray10.display();
    doubleArray3.display();
    
    // Access individual elements
    std::cout << "intArray5[2] = " << intArray5[2] << std::endl;
    std::cout << "intArray10[5] = " << intArray10[5] << std::endl;
    std::cout << "doubleArray3[1] = " << doubleArray3[1] << std::endl;
}

// Advanced template example with iterators
template<typename Iterator>
auto findMaxElement(Iterator begin, Iterator end) -> decltype(*begin) {
    if (begin == end) {
        throw std::runtime_error("Empty range!");
    }
    
    auto maxElement = begin;
    for (auto it = begin + 1; it != end; ++it) {
        if (*it > *maxElement) {
            maxElement = it;
        }
    }
    return *maxElement;
}

// Function to demonstrate advanced template features
void demonstrateAdvancedTemplates() {
    std::cout << "\n=== Advanced Templates Demo ===" << std::endl;
    
    // Using with different containers
    std::vector<int> intVector = {10, 5, 20, 15, 25};
    std::vector<double> doubleVector = {1.5, 2.7, 0.8, 3.2, 1.1};
    std::vector<std::string> stringVector = {"apple", "banana", "cherry", "date"};
    
    // Find maximum elements
    std::cout << "Max in int vector: " << findMaxElement(intVector.begin(), intVector.end()) << std::endl;
    std::cout << "Max in double vector: " << findMaxElement(doubleVector.begin(), doubleVector.end()) << std::endl;
    std::cout << "Max in string vector: " << findMaxElement(stringVector.begin(), stringVector.end()) << std::endl;
    
    // Using with arrays
    int intArray[] = {30, 10, 50, 20, 40};
    int maxInt = findMaxElement(std::begin(intArray), std::end(intArray));
    std::cout << "Max in int array: " << maxInt << std::endl;
}

int main() {
    std::cout << "=== C++ Templates Introduction Demo ===" << std::endl;
    std::cout << "This program demonstrates function templates, class templates, and advanced template features.\n" << std::endl;
    
    // Demonstrate various template concepts
    demonstrateFunctionTemplates();
    demonstrateClassTemplates();
    demonstrateTemplateSpecialization();
    demonstrateNonTypeTemplateParameters();
    demonstrateAdvancedTemplates();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Templates enable generic programming with type safety" << std::endl;
    std::cout << "2. Function templates work with any compatible type" << std::endl;
    std::cout << "3. Class templates create generic containers and classes" << std::endl;
    std::cout << "4. Template specialization allows custom behavior for specific types" << std::endl;
    std::cout << "5. Non-type template parameters enable compile-time constants" << std::endl;
    std::cout << "6. Templates provide zero-cost abstractions" << std::endl;
    std::cout << "7. Template instantiation happens at compile time" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o templates_intro 03_Introduction_to_Templates.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o templates_intro 03_Introduction_to_Templates.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 03_Introduction_to_Templates.cpp
 * 
 * Running:
 * ./templates_intro (Linux/macOS)
 * templates_intro.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for auto keyword and decltype.
 * C++17 is recommended for best template support.
 */