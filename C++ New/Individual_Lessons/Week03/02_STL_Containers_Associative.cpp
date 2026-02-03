/*
 * Lesson 3.2: STL Containers - Associative
 * 
 * This file demonstrates set, multiset, map, and multimap containers,
 * their operations, performance characteristics, and best practices.
 */

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to demonstrate set operations
void demonstrateSet() {
    std::cout << "=== Set Demonstration ===" << std::endl;
    
    std::set<int> s;
    
    // Insert elements
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(30);  // Duplicate - won't be added
    
    std::cout << "Set contents: ";
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Search operations
    auto it = s.find(20);
    if (it != s.end()) {
        std::cout << "Found 20 in set" << std::endl;
    }
    
    // Count occurrences
    std::cout << "Count of 20: " << s.count(20) << std::endl;
    std::cout << "Count of 25: " << s.count(25) << std::endl;
    
    // Range operations
    auto lower = s.lower_bound(15);
    auto upper = s.upper_bound(25);
    
    std::cout << "Elements in range [15, 25]: ";
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Set operations
    std::set<int> s2 = {20, 30, 40, 50};
    std::cout << "Second set: ";
    for (const auto& elem : s2) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Union
    std::set<int> union_set;
    std::set_union(s.begin(), s.end(), s2.begin(), s2.end(),
                   std::inserter(union_set, union_set.begin()));
    std::cout << "Union: ";
    for (const auto& elem : union_set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Intersection
    std::set<int> intersection_set;
    std::set_intersection(s.begin(), s.end(), s2.begin(), s2.end(),
                          std::inserter(intersection_set, intersection_set.begin()));
    std::cout << "Intersection: ";
    for (const auto& elem : intersection_set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate multiset operations
void demonstrateMultiset() {
    std::cout << "
=== Multiset Demonstration ===" << std::endl;
    
    std::multiset<int> ms;
    
    // Insert elements (duplicates allowed)
    ms.insert(30);
    ms.insert(10);
    ms.insert(20);
    ms.insert(30);  // Duplicate - will be added
    
    std::cout << "Multiset contents: ";
    for (const auto& elem : ms) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Count occurrences
    std::cout << "Count of 30: " << ms.count(30) << std::endl;
    std::cout << "Count of 10: " << ms.count(10) << std::endl;
    
    // Find all occurrences
    auto range = ms.equal_range(30);
    std::cout << "All occurrences of 30: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Remove one occurrence
    ms.erase(ms.find(30));
    std::cout << "After removing one 30: ";
    for (const auto& elem : ms) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate map operations
void demonstrateMap() {
    std::cout << "
=== Map Demonstration ===" << std::endl;
    
    std::map<std::string, int> ages;
    
    // Insert key-value pairs
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    
    // Access elements
    std::cout << "Alice's age: " << ages["Alice"] << std::endl;
    std::cout << "Bob's age: " << ages["Bob"] << std::endl;
    
    // Iterate through map
    std::cout << "All ages: ";
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
    
    // Search operations
    auto it = ages.find("Charlie");
    if (it != ages.end()) {
        std::cout << "Found Charlie: " << it->second << std::endl;
    }
    
    // Update value
    ages["Alice"] = 26;
    std::cout << "Updated Alice's age: " << ages["Alice"] << std::endl;
    
    // Insert with hint
    auto hint = ages.find("Bob");
    ages.insert(hint, {"David", 28});
    
    std::cout << "After inserting David: ";
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
    
    // Range operations
    auto lower = ages.lower_bound("B");
    auto upper = ages.upper_bound("C");
    
    std::cout << "Names starting with B or C: ";
    for (auto it = lower; it != upper; ++it) {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate multimap operations
void demonstrateMultimap() {
    std::cout << "
=== Multimap Demonstration ===" << std::endl;
    
    std::multimap<std::string, int> grades;
    
    // Insert key-value pairs (duplicates allowed)
    grades.insert({"Alice", 85});
    grades.insert({"Bob", 90});
    grades.insert({"Alice", 92});
    grades.insert({"Charlie", 88});
    
    std::cout << "All grades: ";
    for (const auto& pair : grades) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
    
    // Find all grades for Alice
    auto range = grades.equal_range("Alice");
    std::cout << "Alice's grades: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << std::endl;
    
    // Count occurrences
    std::cout << "Number of Alice's grades: " << grades.count("Alice") << std::endl;
    
    // Remove one occurrence
    grades.erase(grades.find("Alice"));
    std::cout << "After removing one Alice grade: ";
    for (const auto& pair : grades) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate custom comparison
void demonstrateCustomComparison() {
    std::cout << "
=== Custom Comparison Demonstration ===" << std::endl;
    
    // Set with custom comparison (descending order)
    std::set<int, std::greater<int>> descending_set;
    descending_set.insert(30);
    descending_set.insert(10);
    descending_set.insert(20);
    
    std::cout << "Descending set: ";
    for (const auto& elem : descending_set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // Map with custom comparison
    std::map<std::string, int, std::greater<std::string>> descending_map;
    descending_map["Alice"] = 25;
    descending_map["Bob"] = 30;
    descending_map["Charlie"] = 35;
    
    std::cout << "Descending map: ";
    for (const auto& pair : descending_map) {
        std::cout << pair.first << ": " << pair.second << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate performance characteristics
void demonstratePerformance() {
    std::cout << "
=== Performance Demonstration ===" << std::endl;
    
    const int SIZE = 100000;
    
    // Set performance
    {
        std::set<int> s;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < SIZE; ++i) {
            s.insert(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Set insertion time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // Map performance
    {
        std::map<int, int> m;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < SIZE; ++i) {
            m[i] = i * 2;
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Map insertion time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // Search performance
    {
        std::set<int> s;
        for (int i = 0; i < SIZE; ++i) {
            s.insert(i);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < 10000; ++i) {
            auto it = s.find(i % SIZE);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Set search time: " << duration.count() << " microseconds" << std::endl;
    }
}

// Function to demonstrate real-world applications
void demonstrateRealWorldApplications() {
    std::cout << "
=== Real-World Applications ===" << std::endl;
    
    // Student database
    std::map<std::string, std::vector<int>> student_grades;
    student_grades["Alice"] = {85, 90, 88};
    student_grades["Bob"] = {92, 87, 95};
    student_grades["Charlie"] = {78, 82, 80};
    
    std::cout << "Student grades:" << std::endl;
    for (const auto& pair : student_grades) {
        std::cout << pair.first << ": ";
        for (int grade : pair.second) {
            std::cout << grade << " ";
        }
        std::cout << std::endl;
    }
    
    // Word frequency counter
    std::map<std::string, int> word_count;
    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    
    for (const auto& word : words) {
        word_count[word]++;
    }
    
    std::cout << "
Word frequencies:" << std::endl;
    for (const auto& pair : word_count) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Phone directory
    std::map<std::string, std::string> phone_directory;
    phone_directory["Alice"] = "555-1234";
    phone_directory["Bob"] = "555-5678";
    phone_directory["Charlie"] = "555-9012";
    
    std::cout << "
Phone directory:" << std::endl;
    for (const auto& pair : phone_directory) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    std::cout << "=== STL Associative Containers Demonstration ===" << std::endl;
    std::cout << "This program demonstrates set, multiset, map, and multimap containers,
"
              << "their operations, performance characteristics, and real-world applications.
" << std::endl;
    
    // Demonstrate various associative container operations
    demonstrateSet();
    demonstrateMultiset();
    demonstrateMap();
    demonstrateMultimap();
    demonstrateCustomComparison();
    demonstratePerformance();
    demonstrateRealWorldApplications();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. Set: Unique elements with fast search" << std::endl;
    std::cout << "2. Multiset: Duplicate elements allowed" << std::endl;
    std::cout << "3. Map: Key-value pairs with unique keys" << std::endl;
    std::cout << "4. Multimap: Key-value pairs with duplicate keys" << std::endl;
    std::cout << "5. All associative containers maintain sorted order" << std::endl;
    std::cout << "6. Use appropriate container based on key uniqueness requirements" << std::endl;
    std::cout << "7. Range operations are efficient for finding elements in ranges" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o stl_associative 02_STL_Containers_Associative.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o stl_associative 02_STL_Containers_Associative.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_STL_Containers_Associative.cpp
 * 
 * Running:
 * ./stl_associative (Linux/macOS)
 * stl_associative.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for range-based for loops and auto.
 * C++17 is recommended for best STL support.
 * 
 * Performance Notes:
 * - Associative containers provide O(log n) search time
 * - Insertion and deletion are also O(log n)
 * - Memory overhead is higher than sequential containers
 * - Consider unordered containers for better performance when order isn't needed
 */