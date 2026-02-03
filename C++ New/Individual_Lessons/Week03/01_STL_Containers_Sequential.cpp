/*
 * Lesson 3.1: STL Containers - Sequential
 * 
 * This file demonstrates vector, list, and deque containers,
 * their operations, performance characteristics, and best practices.
 */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>

// Function to demonstrate vector operations
void demonstrateVector() {
    std::cout << "=== Vector Demonstration ===" << std::endl;
    
    // Create and populate vector
    std::vector<int> vec;
    std::cout << "Initial size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    
    // Add elements and observe capacity growth
    for (int i = 1; i <= 10; ++i) {
        vec.push_back(i * 10);
        std::cout << "Added " << (i * 10) << " - size: " << vec.size() 
                  << ", capacity: " << vec.capacity() << std::endl;
    }
    
    // Access elements using different methods
    std::cout << "\nVector contents using []: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Vector contents using at(): ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Vector contents using iterators: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Vector contents using range-based for: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Insert in middle
    vec.insert(vec.begin() + 5, 999);
    std::cout << "\nAfter inserting 999 at position 5: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Remove element
    vec.erase(vec.begin() + 3);
    std::cout << "After removing element at position 3: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Demonstrate bounds checking
    try {
        std::cout << "Accessing element at index 100: " << vec.at(100) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // Reserve capacity
    std::vector<int> vec2;
    vec2.reserve(1000);
    std::cout << "\nVector with reserved capacity - size: " << vec2.size() 
              << ", capacity: " << vec2.capacity() << std::endl;
}

// Function to demonstrate list operations
void demonstrateList() {
    std::cout << "\n=== List Demonstration ===" << std::endl;
    
    std::list<int> lst;
    
    // Add elements at both ends
    lst.push_back(100);
    lst.push_front(50);
    lst.push_back(200);
    lst.push_front(25);
    lst.push_back(300);
    
    std::cout << "List contents: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Insert in middle
    auto it = lst.begin();
    std::advance(it, 2);  // Move iterator to position 2
    lst.insert(it, 999);
    
    std::cout << "After inserting 999 at position 2: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Remove elements
    lst.remove(200);  // Remove all occurrences of 200
    std::cout << "After removing 200: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Sort list
    lst.sort();
    std::cout << "After sorting: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Demonstrate list-specific operations
    std::list<int> lst2 = {400, 500, 600};
    std::cout << "\nSecond list: ";
    for (const auto& elem : lst2) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Merge lists
    lst.merge(lst2);
    std::cout << "After merging: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Reverse list
    lst.reverse();
    std::cout << "After reversing: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Remove duplicates
    lst.unique();
    std::cout << "After removing duplicates: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate deque operations
void demonstrateDeque() {
    std::cout << "\n=== Deque Demonstration ===" << std::endl;
    
    std::deque<int> dq;
    
    // Add elements at both ends
    dq.push_back(10);
    dq.push_front(5);
    dq.push_back(20);
    dq.push_front(1);
    dq.push_back(30);
    
    std::cout << "Deque contents: ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Random access
    std::cout << "Element at index 2: " << dq[2] << std::endl;
    std::cout << "Element at index 4: " << dq[4] << std::endl;
    std::cout << "Front element: " << dq.front() << std::endl;
    std::cout << "Back element: " << dq.back() << std::endl;
    
    // Remove from both ends
    std::cout << "Removed from front: " << dq.front() << std::endl;
    dq.pop_front();
    
    std::cout << "Removed from back: " << dq.back() << std::endl;
    dq.pop_back();
    
    std::cout << "After removals: ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Insert in middle
    dq.insert(dq.begin() + 1, 999);
    std::cout << "After inserting 999 at position 1: ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Erase from middle
    dq.erase(dq.begin() + 2);
    std::cout << "After erasing element at position 2: ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate iterator usage
void demonstrateIterators() {
    std::cout << "\n=== Iterator Demonstration ===" << std::endl;
    
    std::vector<int> vec = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    // Forward iterator
    std::cout << "Forward iteration: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Reverse iterator
    std::cout << "Reverse iteration: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Const iterator
    std::cout << "Const iterator: ";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Iterator arithmetic
    auto it = vec.begin();
    std::cout << "Element at begin(): " << *it << std::endl;
    std::cout << "Element at begin() + 3: " << *(it + 3) << std::endl;
    std::cout << "Element at begin() + 7: " << *(it + 7) << std::endl;
    
    // Iterator distance
    std::cout << "Distance from begin to end: " << std::distance(vec.begin(), vec.end()) << std::endl;
    std::cout << "Distance from begin to begin+5: " << std::distance(vec.begin(), vec.begin() + 5) << std::endl;
    
    // Iterator invalidation demonstration
    std::cout << "\nIterator invalidation demo:" << std::endl;
    auto it2 = vec.begin() + 3;
    std::cout << "Iterator points to: " << *it2 << std::endl;
    
    vec.insert(vec.begin() + 1, 999);  // This invalidates it2
    std::cout << "After insertion, iterator is invalidated" << std::endl;
    std::cout << "New vector: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate container algorithms
void demonstrateContainerAlgorithms() {
    std::cout << "\n=== Container Algorithms Demonstration ===" << std::endl;
    
    std::vector<int> vec = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    
    std::cout << "Original vector: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Sort
    std::sort(vec.begin(), vec.end());
    std::cout << "After sorting: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Reverse
    std::reverse(vec.begin(), vec.end());
    std::cout << "After reversing: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Find
    auto it = std::find(vec.begin(), vec.end(), 25);
    if (it != vec.end()) {
        std::cout << "Found 25 at position: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "25 not found" << std::endl;
    }
    
    // Count
    int count = std::count(vec.begin(), vec.end(), 30);
    std::cout << "Number of 30s: " << count << std::endl;
    
    // Max element
    auto maxIt = std::max_element(vec.begin(), vec.end());
    std::cout << "Maximum element: " << *maxIt << std::endl;
    
    // Min element
    auto minIt = std::min_element(vec.begin(), vec.end());
    std::cout << "Minimum element: " << *minIt << std::endl;
    
    // Accumulate
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum of all elements: " << sum << std::endl;
}

// Function to demonstrate performance characteristics
void demonstratePerformance() {
    std::cout << "\n=== Performance Demonstration ===" << std::endl;
    
    const int SIZE = 100000;
    
    // Vector performance
    {
        std::vector<int> vec;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < SIZE; ++i) {
            vec.push_back(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Vector push_back time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // List performance
    {
        std::list<int> lst;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < SIZE; ++i) {
            lst.push_back(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "List push_back time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // Deque performance
    {
        std::deque<int> dq;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < SIZE; ++i) {
            dq.push_back(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Deque push_back time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // Random access performance
    {
        std::vector<int> vec(SIZE);
        std::list<int> lst(SIZE);
        std::deque<int> dq(SIZE);
        
        // Fill containers
        for (int i = 0; i < SIZE; ++i) {
            vec[i] = i;
            dq[i] = i;
        }
        
        auto it = lst.begin();
        for (int i = 0; i < SIZE; ++i) {
            *it = i;
            ++it;
        }
        
        // Measure random access
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, SIZE - 1);
        
        // Vector random access
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10000; ++i) {
                int index = dis(gen);
                volatile int val = vec[index];  // Prevent optimization
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Vector random access time: " << duration.count() << " microseconds" << std::endl;
        }
        
        // Deque random access
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10000; ++i) {
                int index = dis(gen);
                volatile int val = dq[index];  // Prevent optimization
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Deque random access time: " << duration.count() << " microseconds" << std::endl;
        }
    }
}

// Function to demonstrate container selection guidelines
void demonstrateContainerSelection() {
    std::cout << "\n=== Container Selection Guidelines ===" << std::endl;
    
    // Scenario 1: Frequent random access - use vector
    std::cout << "Scenario 1: Random access (use vector)" << std::endl;
    std::vector<int> scores = {85, 92, 78, 96, 88, 91, 83, 89, 94, 87};
    
    // Random access is O(1)
    std::cout << "Student 5's score: " << scores[4] << std::endl;
    std::cout << "Student 8's score: " << scores[7] << std::endl;
    
    // Scenario 2: Frequent insertions in middle - use list
    std::cout << "\nScenario 2: Frequent middle insertions (use list)" << std::endl;
    std::list<std::string> playlist = {"Song A", "Song B", "Song C", "Song D"};
    
    std::cout << "Original playlist: ";
    for (const auto& song : playlist) {
        std::cout << song << " ";
    }
    std::cout << std::endl;
    
    // Insert in middle is O(1) for list
    auto it = playlist.begin();
    std::advance(it, 2);
    playlist.insert(it, "New Song");
    
    std::cout << "After inserting 'New Song' at position 2: ";
    for (const auto& song : playlist) {
        std::cout << song << " ";
    }
    std::cout << std::endl;
    
    // Scenario 3: Frequent operations at both ends - use deque
    std::cout << "\nScenario 3: Both-end operations (use deque)" << std::endl;
    std::deque<int> sliding_window;
    
    // Add elements at both ends
    sliding_window.push_back(10);
    sliding_window.push_front(5);
    sliding_window.push_back(15);
    sliding_window.push_front(1);
    
    std::cout << "Sliding window: ";
    for (const auto& elem : sliding_window) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Remove from both ends
    sliding_window.pop_front();
    sliding_window.pop_back();
    
    std::cout << "After removing from both ends: ";
    for (const auto& elem : sliding_window) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== STL Sequential Containers Demonstration ===" << std::endl;
    std::cout << "This program demonstrates vector, list, and deque containers,\n"
              << "their operations, performance characteristics, and best practices.\n" << std::endl;
    
    // Demonstrate various container operations
    demonstrateVector();
    demonstrateList();
    demonstrateDeque();
    demonstrateIterators();
    demonstrateContainerAlgorithms();
    demonstratePerformance();
    demonstrateContainerSelection();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Vector: Best for random access and end operations" << std::endl;
    std::cout << "2. List: Best for frequent insertions/deletions in middle" << std::endl;
    std::cout << "3. Deque: Best for operations at both ends with random access" << std::endl;
    std::cout << "4. Iterators provide uniform access to container elements" << std::endl;
    std::cout << "5. Choose container based on your specific use case" << std::endl;
    std::cout << "6. Performance characteristics matter for large datasets" << std::endl;
    std::cout << "7. Iterator invalidation can cause undefined behavior" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o stl_containers 01_STL_Containers_Sequential.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o stl_containers 01_STL_Containers_Sequential.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_STL_Containers_Sequential.cpp
 * 
 * Running:
 * ./stl_containers (Linux/macOS)
 * stl_containers.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for range-based for loops and auto.
 * C++17 is recommended for best STL support.
 * 
 * Performance Notes:
 * - Vector typically has best cache locality
 * - List has worst cache locality but best insertion performance
 * - Deque provides a balance between vector and list
 * - Always measure performance for your specific use case
 */