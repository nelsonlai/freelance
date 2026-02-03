#include <iostream>
#include <string>
#include <algorithm>
#include "mini_stl/vector.h"

using namespace mini_stl;

// Demonstrate vector functionality
void demonstrate_vector_basics() {
    std::cout << "=== Vector Basics ===" << std::endl;
    
    // Create vectors
    vector<int> v1;
    vector<int> v2(5, 10);  // 5 elements with value 10
    vector<int> v3{1, 2, 3, 4, 5};  // Initializer list
    
    std::cout << "v1 size: " << v1.size() << ", capacity: " << v1.capacity() << std::endl;
    std::cout << "v2 size: " << v2.size() << ", capacity: " << v2.capacity() << std::endl;
    std::cout << "v3 size: " << v3.size() << ", capacity: " << v3.capacity() << std::endl;
    
    // Display v2 and v3
    std::cout << "v2: ";
    for (int val : v2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "v3: ";
    for (int val : v3) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void demonstrate_vector_operations() {
    std::cout << "\n=== Vector Operations ===" << std::endl;
    
    vector<int> v;
    
    // Add elements
    for (int i = 1; i <= 10; ++i) {
        v.push_back(i);
    }
    
    std::cout << "After adding 1-10: ";
    for (int val : v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << std::endl;
    
    // Access elements
    std::cout << "First element: " << v.front() << std::endl;
    std::cout << "Last element: " << v.back() << std::endl;
    std::cout << "Element at index 5: " << v[5] << std::endl;
    
    // Insert elements
    v.insert(v.begin() + 2, 99);
    std::cout << "After inserting 99 at position 2: ";
    for (int val : v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Erase elements
    v.erase(v.begin() + 2);
    std::cout << "After erasing element at position 2: ";
    for (int val : v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void demonstrate_vector_iterators() {
    std::cout << "\n=== Vector Iterators ===" << std::endl;
    
    vector<std::string> words{"hello", "world", "cpp", "programming"};
    
    // Forward iteration
    std::cout << "Forward iteration: ";
    for (auto it = words.begin(); it != words.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Reverse iteration
    std::cout << "Reverse iteration: ";
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop
    std::cout << "Range-based for loop: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // Iterator arithmetic
    auto it = words.begin();
    std::cout << "Element at begin(): " << *it << std::endl;
    std::cout << "Element at begin() + 2: " << *(it + 2) << std::endl;
    std::cout << "Element at end() - 1: " << *(words.end() - 1) << std::endl;
}

void demonstrate_vector_copy_move() {
    std::cout << "\n=== Vector Copy and Move ===" << std::endl;
    
    vector<int> original{1, 2, 3, 4, 5};
    std::cout << "Original: ";
    for (int val : original) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Copy constructor
    vector<int> copied(original);
    std::cout << "Copied: ";
    for (int val : copied) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Move constructor
    vector<int> moved(std::move(original));
    std::cout << "Moved: ";
    for (int val : moved) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Original after move (should be empty): ";
    for (int val : original) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Original size after move: " << original.size() << std::endl;
}

void demonstrate_vector_exceptions() {
    std::cout << "\n=== Vector Exception Handling ===" << std::endl;
    
    vector<int> v{1, 2, 3, 4, 5};
    
    try {
        std::cout << "Accessing valid index: " << v.at(2) << std::endl;
        std::cout << "Accessing invalid index: " << v.at(10) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "Reserving valid capacity: ";
        v.reserve(100);
        std::cout << "Success! New capacity: " << v.capacity() << std::endl;
        
        std::cout << "Reserving invalid capacity: ";
        v.reserve(2);  // Less than current size
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

void demonstrate_vector_algorithms() {
    std::cout << "\n=== Vector with Algorithms ===" << std::endl;
    
    vector<int> numbers{5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Original: ";
    for (int val : numbers) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Sort
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted: ";
    for (int val : numbers) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Find
    auto it = std::find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        std::cout << "Found 7 at position: " << (it - numbers.begin()) << std::endl;
    }
    
    // Count
    int count = std::count(numbers.begin(), numbers.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    // Transform
    vector<int> doubled(numbers.size());
    std::transform(numbers.begin(), numbers.end(), doubled.begin(),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled: ";
    for (int val : doubled) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void demonstrate_vector_performance() {
    std::cout << "\n=== Vector Performance ===" << std::endl;
    
    vector<int> v;
    
    std::cout << "Adding 100,000 elements..." << std::endl;
    for (int i = 0; i < 100000; ++i) {
        v.push_back(i);
    }
    
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Capacity: " << v.capacity() << std::endl;
    
    std::cout << "Shrinking to fit..." << std::endl;
    v.shrink_to_fit();
    std::cout << "Capacity after shrink: " << v.capacity() << std::endl;
    
    std::cout << "Clearing vector..." << std::endl;
    v.clear();
    std::cout << "Size after clear: " << v.size() << std::endl;
    std::cout << "Capacity after clear: " << v.capacity() << std::endl;
}

int main() {
    std::cout << "Mini STL Vector Example" << std::endl;
    std::cout << "=======================" << std::endl;
    
    demonstrate_vector_basics();
    demonstrate_vector_operations();
    demonstrate_vector_iterators();
    demonstrate_vector_copy_move();
    demonstrate_vector_exceptions();
    demonstrate_vector_algorithms();
    demonstrate_vector_performance();
    
    std::cout << "\nVector example completed successfully!" << std::endl;
    return 0;
}
