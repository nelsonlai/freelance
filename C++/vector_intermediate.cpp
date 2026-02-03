/*
 * VECTOR INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate vector concepts including iterators, algorithms, and performance optimization:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced VECTOR concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic VECTOR concepts
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
#include <algorithm>
#include <iterator>
#include <numeric>
#include <random>
#include <chrono>
using namespace std;

// Custom class for vector operations
class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    Student(const string& n, int a, double g) : name(n), age(a), gpa(g) {}
    
    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    double getGpa() const { return gpa; }
    
    // For sorting
    bool operator<(const Student& other) const {
        return gpa > other.gpa;  // Sort by GPA descending
    }
    
    // For output
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.name << " (Age: " << s.age << ", GPA: " << s.gpa << ")";
        return os;
    }
};

// Function to demonstrate vector operations
void demonstrateVectorOperations() {
    cout << "=== VECTOR INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Vector with custom objects
    cout << "1. Vector with Custom Objects:" << endl;
    vector<Student> students = {
        {"Alice", 20, 3.8},
        {"Bob", 21, 3.5},
        {"Charlie", 19, 3.9},
        {"Diana", 22, 3.7},
        {"Eve", 20, 3.6}
    };
    
    cout << "Original students:" << endl;
    for (const auto& student : students) {
        cout << "  " << student << endl;
    }
    cout << endl;
    
    // Example 2: Sorting and searching
    cout << "2. Sorting and Searching:" << endl;
    sort(students.begin(), students.end());
    cout << "Students sorted by GPA (descending):" << endl;
    for (const auto& student : students) {
        cout << "  " << student << endl;
    }
    
    // Find student with specific GPA
    auto it = find_if(students.begin(), students.end(), 
        [](const Student& s) { return s.getGpa() == 3.7; });
    if (it != students.end()) {
        cout << "Found student with GPA 3.7: " << *it << endl;
    }
    cout << endl;
    
    // Example 3: Vector algorithms
    cout << "3. Vector Algorithms:" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "Original numbers: ";
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    // Transform: square all numbers
    vector<int> squared;
    transform(numbers.begin(), numbers.end(), back_inserter(squared),
        [](int x) { return x * x; });
    
    cout << "Squared numbers: ";
    copy(squared.begin(), squared.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    // Filter: get even numbers
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evens),
        [](int x) { return x % 2 == 0; });
    
    cout << "Even numbers: ";
    copy(evens.begin(), evens.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    // Accumulate: sum of numbers
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    cout << "Sum of numbers: " << sum << endl;
    
    // Count: count even numbers
    int evenCount = count_if(numbers.begin(), numbers.end(),
        [](int x) { return x % 2 == 0; });
    cout << "Count of even numbers: " << evenCount << endl;
    cout << endl;
    
    // Example 4: Vector capacity and memory management
    cout << "4. Vector Capacity and Memory Management:" << endl;
    vector<int> capacityTest;
    
    cout << "Initial capacity: " << capacityTest.capacity() << endl;
    cout << "Initial size: " << capacityTest.size() << endl;
    
    for (int i = 0; i < 10; i++) {
        capacityTest.push_back(i);
        cout << "After adding " << i << ": size=" << capacityTest.size() 
             << ", capacity=" << capacityTest.capacity() << endl;
    }
    cout << endl;
    
    // Example 5: Vector of vectors (2D matrix)
    cout << "5. Vector of Vectors (2D Matrix):" << endl;
    vector<vector<int>> matrix(3, vector<int>(4, 0));
    
    // Initialize matrix
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = i * matrix[i].size() + j + 1;
        }
    }
    
    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Example 6: Vector with iterators
    cout << "6. Vector with Iterators:" << endl;
    vector<string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    cout << "Words using iterators:" << endl;
    for (auto it = words.begin(); it != words.end(); ++it) {
        cout << "  " << *it << " (length: " << it->length() << ")" << endl;
    }
    
    // Reverse iteration
    cout << "Words in reverse:" << endl;
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        cout << "  " << *it << endl;
    }
    cout << endl;
    
    // Example 7: Vector with custom allocator (simplified)
    cout << "7. Vector Performance:" << endl;
    vector<int> performanceTest;
    
    auto start = chrono::high_resolution_clock::now();
    
    // Add 100000 elements
    for (int i = 0; i < 100000; i++) {
        performanceTest.push_back(i);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Time to add 100,000 elements: " << duration.count() << " microseconds" << endl;
    cout << "Final size: " << performanceTest.size() << endl;
    cout << "Final capacity: " << performanceTest.capacity() << endl;
    cout << endl;
    
    // Example 8: Vector with move semantics
    cout << "8. Vector with Move Semantics:" << endl;
    vector<string> source = {"move", "these", "strings"};
    vector<string> destination;
    
    cout << "Source before move: ";
    for (const auto& s : source) {
        cout << s << " ";
    }
    cout << endl;
    
    // Move elements
    destination = move(source);
    
    cout << "Destination after move: ";
    for (const auto& s : destination) {
        cout << s << " ";
    }
    cout << endl;
    
    cout << "Source after move (should be empty): " << source.size() << " elements" << endl;
    cout << endl;
    
    // Example 9: Vector with custom comparison
    cout << "9. Vector with Custom Comparison:" << endl;
    vector<pair<string, int>> nameAge = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"Diana", 35}
    };
    
    cout << "Original name-age pairs:" << endl;
    for (const auto& pair : nameAge) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }
    
    // Sort by age
    sort(nameAge.begin(), nameAge.end(), 
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });
    
    cout << "Sorted by age:" << endl;
    for (const auto& pair : nameAge) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    demonstrateVectorOperations();
    return 0;
}
