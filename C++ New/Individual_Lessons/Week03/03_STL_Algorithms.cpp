/*
 * Lesson 3.3: STL Algorithms
 * 
 * This file demonstrates STL algorithms, their categories,
 * usage patterns, and performance characteristics.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <chrono>

// Function to demonstrate non-modifying algorithms
void demonstrateNonModifyingAlgorithms() {
    std::cout << "=== Non-Modifying Algorithms ===" << std::endl;
    
    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7, 4, 6, 5};
    
    std::cout << "Original vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Find operations
    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Found 5 at position: " << std::distance(vec.begin(), it) << std::endl;
    }
    
    // Count operations
    int count = std::count(vec.begin(), vec.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    // Count if with predicate
    int even_count = std::count_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    std::cout << "Count of even numbers: " << even_count << std::endl;
    
    // Find if with predicate
    auto even_it = std::find_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    if (even_it != vec.end()) {
        std::cout << "First even number: " << *even_it << std::endl;
    }
    
    // Search for subsequence
    std::vector<int> pattern = {3, 7};
    auto search_it = std::search(vec.begin(), vec.end(), pattern.begin(), pattern.end());
    if (search_it != vec.end()) {
        std::cout << "Found pattern {3, 7} at position: " << std::distance(vec.begin(), search_it) << std::endl;
    }
    
    // Adjacent find
    auto adjacent_it = std::adjacent_find(vec.begin(), vec.end());
    if (adjacent_it != vec.end()) {
        std::cout << "Found adjacent equal elements: " << *adjacent_it << std::endl;
    }
    
    // Min and max elements
    auto min_it = std::min_element(vec.begin(), vec.end());
    auto max_it = std::max_element(vec.begin(), vec.end());
    std::cout << "Min element: " << *min_it << ", Max element: " << *max_it << std::endl;
    
    // Min and max values
    int min_val = std::min(10, 20);
    int max_val = std::max(10, 20);
    std::cout << "Min(10, 20): " << min_val << ", Max(10, 20): " << max_val << std::endl;
}

// Function to demonstrate modifying algorithms
void demonstrateModifyingAlgorithms() {
    std::cout << "
=== Modifying Algorithms ===" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Transform
    std::vector<int> doubled;
    std::transform(vec.begin(), vec.end(), std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled vector: ";
    for (int x : doubled) std::cout << x << " ";
    std::cout << std::endl;
    
    // Transform in place
    std::transform(vec.begin(), vec.end(), vec.begin(),
                   [](int x) { return x * x; });
    
    std::cout << "Squared vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Replace
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 3, 6, 3, 7};
    std::cout << "Before replace: ";
    for (int x : vec2) std::cout << x << " ";
    std::cout << std::endl;
    
    std::replace(vec2.begin(), vec2.end(), 3, 30);
    std::cout << "After replacing 3 with 30: ";
    for (int x : vec2) std::cout << x << " ";
    std::cout << std::endl;
    
    // Replace if
    std::vector<int> vec3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "Before replace_if: ";
    for (int x : vec3) std::cout << x << " ";
    std::cout << std::endl;
    
    std::replace_if(vec3.begin(), vec3.end(), [](int x) { return x % 2 == 0; }, 0);
    std::cout << "After replacing even numbers with 0: ";
    for (int x : vec3) std::cout << x << " ";
    std::cout << std::endl;
    
    // Fill
    std::vector<int> vec4(10);
    std::fill(vec4.begin(), vec4.end(), 42);
    std::cout << "Filled vector: ";
    for (int x : vec4) std::cout << x << " ";
    std::cout << std::endl;
    
    // Generate
    std::vector<int> vec5(10);
    int counter = 1;
    std::generate(vec5.begin(), vec5.end(), [&counter]() { return counter++; });
    std::cout << "Generated vector: ";
    for (int x : vec5) std::cout << x << " ";
    std::cout << std::endl;
}

// Function to demonstrate sorting algorithms
void demonstrateSortingAlgorithms() {
    std::cout << "
=== Sorting Algorithms ===" << std::endl;
    
    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Original vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Sort
    std::vector<int> sorted_vec = vec;
    std::sort(sorted_vec.begin(), sorted_vec.end());
    std::cout << "Sorted vector: ";
    for (int x : sorted_vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Sort with custom comparator
    std::vector<int> reverse_sorted = vec;
    std::sort(reverse_sorted.begin(), reverse_sorted.end(), std::greater<int>());
    std::cout << "Reverse sorted vector: ";
    for (int x : reverse_sorted) std::cout << x << " ";
    std::cout << std::endl;
    
    // Partial sort
    std::vector<int> partial_sorted = vec;
    std::partial_sort(partial_sorted.begin(), partial_sorted.begin() + 3, partial_sorted.end());
    std::cout << "Partially sorted (first 3): ";
    for (int x : partial_sorted) std::cout << x << " ";
    std::cout << std::endl;
    
    // Nth element
    std::vector<int> nth_vec = vec;
    std::nth_element(nth_vec.begin(), nth_vec.begin() + 3, nth_vec.end());
    std::cout << "Nth element (4th): " << nth_vec[3] << std::endl;
    std::cout << "Vector after nth_element: ";
    for (int x : nth_vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Binary search (requires sorted data)
    bool found = std::binary_search(sorted_vec.begin(), sorted_vec.end(), 5);
    std::cout << "5 found in sorted vector: " << (found ? "Yes" : "No") << std::endl;
    
    // Lower bound
    auto lower = std::lower_bound(sorted_vec.begin(), sorted_vec.end(), 5);
    std::cout << "Lower bound of 5: " << *lower << std::endl;
    
    // Upper bound
    auto upper = std::upper_bound(sorted_vec.begin(), sorted_vec.end(), 5);
    std::cout << "Upper bound of 5: " << *upper << std::endl;
}

// Function to demonstrate removal algorithms
void demonstrateRemovalAlgorithms() {
    std::cout << "
=== Removal Algorithms ===" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5, 3, 6, 3, 7, 8};
    
    std::cout << "Original vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Remove (doesn't actually remove, just moves elements)
    auto new_end = std::remove(vec.begin(), vec.end(), 3);
    std::cout << "After remove(3): ";
    for (auto it = vec.begin(); it != new_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Actually erase removed elements
    vec.erase(new_end, vec.end());
    std::cout << "After erase: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Remove if
    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "Original vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    auto new_end2 = std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    vec.erase(new_end2, vec.end());
    std::cout << "After removing even numbers: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Unique
    std::vector<int> vec2 = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    std::cout << "Original vector: ";
    for (int x : vec2) std::cout << x << " ";
    std::cout << std::endl;
    
    auto unique_end = std::unique(vec2.begin(), vec2.end());
    vec2.erase(unique_end, vec2.end());
    std::cout << "After removing duplicates: ";
    for (int x : vec2) std::cout << x << " ";
    std::cout << std::endl;
}

// Function to demonstrate set algorithms
void demonstrateSetAlgorithms() {
    std::cout << "
=== Set Algorithms ===" << std::endl;
    
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {3, 4, 5, 6, 7};
    
    std::cout << "Vector 1: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Vector 2: ";
    for (int x : vec2) std::cout << x << " ";
    std::cout << std::endl;
    
    // Union
    std::vector<int> union_result;
    std::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                   std::back_inserter(union_result));
    std::cout << "Union: ";
    for (int x : union_result) std::cout << x << " ";
    std::cout << std::endl;
    
    // Intersection
    std::vector<int> intersection_result;
    std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                          std::back_inserter(intersection_result));
    std::cout << "Intersection: ";
    for (int x : intersection_result) std::cout << x << " ";
    std::cout << std::endl;
    
    // Difference
    std::vector<int> difference_result;
    std::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                        std::back_inserter(difference_result));
    std::cout << "Difference (vec1 - vec2): ";
    for (int x : difference_result) std::cout << x << " ";
    std::cout << std::endl;
    
    // Symmetric difference
    std::vector<int> symmetric_diff_result;
    std::set_symmetric_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                                  std::back_inserter(symmetric_diff_result));
    std::cout << "Symmetric difference: ";
    for (int x : symmetric_diff_result) std::cout << x << " ";
    std::cout << std::endl;
}

// Function to demonstrate numeric algorithms
void demonstrateNumericAlgorithms() {
    std::cout << "
=== Numeric Algorithms ===" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Vector: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // Accumulate
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
    std::cout << "Product: " << product << std::endl;
    
    // Inner product
    std::vector<int> vec2 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    int inner_prod = std::inner_product(vec.begin(), vec.end(), vec2.begin(), 0);
    std::cout << "Inner product: " << inner_prod << std::endl;
    
    // Partial sum
    std::vector<int> partial_sums;
    std::partial_sum(vec.begin(), vec.end(), std::back_inserter(partial_sums));
    std::cout << "Partial sums: ";
    for (int x : partial_sums) std::cout << x << " ";
    std::cout << std::endl;
    
    // Adjacent difference
    std::vector<int> adjacent_diffs;
    std::adjacent_difference(vec.begin(), vec.end(), std::back_inserter(adjacent_diffs));
    std::cout << "Adjacent differences: ";
    for (int x : adjacent_diffs) std::cout << x << " ";
    std::cout << std::endl;
}

// Function to demonstrate performance characteristics
void demonstratePerformance() {
    std::cout << "
=== Performance Demonstration ===" << std::endl;
    
    const int SIZE = 100000;
    
    // Generate random data
    std::vector<int> vec(SIZE);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    for (int i = 0; i < SIZE; ++i) {
        vec[i] = dis(gen);
    }
    
    // Measure sorting performance
    {
        std::vector<int> sorted_vec = vec;
        auto start = std::chrono::high_resolution_clock::now();
        
        std::sort(sorted_vec.begin(), sorted_vec.end());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Sorting time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // Measure search performance
    {
        std::vector<int> sorted_vec = vec;
        std::sort(sorted_vec.begin(), sorted_vec.end());
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < 1000; ++i) {
            auto it = std::binary_search(sorted_vec.begin(), sorted_vec.end(), dis(gen));
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Binary search time (1000 searches): " << duration.count() << " microseconds" << std::endl;
    }
    
    // Measure transformation performance
    {
        std::vector<int> result(SIZE);
        auto start = std::chrono::high_resolution_clock::now();
        
        std::transform(vec.begin(), vec.end(), result.begin(),
                       [](int x) { return x * 2; });
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Transformation time: " << duration.count() << " microseconds" << std::endl;
    }
}

int main() {
    std::cout << "=== STL Algorithms Demonstration ===" << std::endl;
    std::cout << "This program demonstrates STL algorithms, their categories,
"
              << "usage patterns, and performance characteristics.
" << std::endl;
    
    // Demonstrate various algorithm categories
    demonstrateNonModifyingAlgorithms();
    demonstrateModifyingAlgorithms();
    demonstrateSortingAlgorithms();
    demonstrateRemovalAlgorithms();
    demonstrateSetAlgorithms();
    demonstrateNumericAlgorithms();
    demonstratePerformance();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. STL algorithms work with any container through iterators" << std::endl;
    std::cout << "2. Non-modifying algorithms don't change the container" << std::endl;
    std::cout << "3. Modifying algorithms change the container contents" << std::endl;
    std::cout << "4. Sorting algorithms require random access iterators" << std::endl;
    std::cout << "5. Set algorithms work with sorted ranges" << std::endl;
    std::cout << "6. Numeric algorithms provide mathematical operations" << std::endl;
    std::cout << "7. Performance varies significantly between algorithms" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o stl_algorithms 03_STL_Algorithms.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o stl_algorithms 03_STL_Algorithms.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_STL_Algorithms.cpp
 * 
 * Running:
 * ./stl_algorithms (Linux/macOS)
 * stl_algorithms.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for lambdas and auto.
 * C++17 is recommended for best STL support.
 * 
 * Performance Notes:
 * - Sorting algorithms have O(n log n) complexity
 * - Binary search has O(log n) complexity
 * - Linear algorithms have O(n) complexity
 * - Always measure performance for your specific use case
 */