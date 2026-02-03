#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <random>
#include <chrono>

// Demonstrates STL algorithms and their usage
int main() {
    std::cout << "STL Algorithms Demonstration" << std::endl;
    std::cout << "============================" << std::endl;
    
    // 1. Non-modifying sequence operations
    std::cout << "\n1. NON-MODIFYING SEQUENCE OPERATIONS:" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 5, 7};
    
    // Find
    std::cout << "\nFind operations:" << std::endl;
    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Found 5 at position: " << (it - vec.begin()) << std::endl;
    }
    
    auto it2 = std::find_if(vec.begin(), vec.end(), [](int x) { return x > 8; });
    if (it2 != vec.end()) {
        std::cout << "Found first element > 8: " << *it2 << " at position: " << (it2 - vec.begin()) << std::endl;
    }
    
    // Count
    std::cout << "\nCount operations:" << std::endl;
    int count = std::count(vec.begin(), vec.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    int count_if = std::count_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    std::cout << "Count of even numbers: " << count_if << std::endl;
    
    // Search
    std::cout << "\nSearch operations:" << std::endl;
    std::vector<int> subseq = {3, 4, 5};
    auto search_it = std::search(vec.begin(), vec.end(), subseq.begin(), subseq.end());
    if (search_it != vec.end()) {
        std::cout << "Found subsequence {3, 4, 5} starting at position: " << (search_it - vec.begin()) << std::endl;
    }
    
    // Mismatch
    std::cout << "\nMismatch operations:" << std::endl;
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 5, 8};  // Different last element
    auto mismatch_pair = std::mismatch(vec.begin(), vec.end(), vec2.begin());
    if (mismatch_pair.first != vec.end()) {
        std::cout << "First mismatch at position: " << (mismatch_pair.first - vec.begin()) 
                  << ", values: " << *mismatch_pair.first << " vs " << *mismatch_pair.second << std::endl;
    }
    
    // Equal
    std::cout << "\nEqual operations:" << std::endl;
    std::vector<int> vec3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 5, 7};
    bool are_equal = std::equal(vec.begin(), vec.end(), vec3.begin());
    std::cout << "vec == vec3: " << std::boolalpha << are_equal << std::endl;
    
    // All_of, any_of, none_of
    std::cout << "\nPredicate operations:" << std::endl;
    bool all_positive = std::all_of(vec.begin(), vec.end(), [](int x) { return x > 0; });
    std::cout << "All positive: " << std::boolalpha << all_positive << std::endl;
    
    bool any_greater_than_8 = std::any_of(vec.begin(), vec.end(), [](int x) { return x > 8; });
    std::cout << "Any greater than 8: " << std::boolalpha << any_greater_than_8 << std::endl;
    
    bool none_negative = std::none_of(vec.begin(), vec.end(), [](int x) { return x < 0; });
    std::cout << "None negative: " << std::boolalpha << none_negative << std::endl;
    
    // 2. Modifying sequence operations
    std::cout << "\n2. MODIFYING SEQUENCE OPERATIONS:" << std::endl;
    
    std::vector<int> vec_mod = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> result(vec_mod.size());
    
    // Copy
    std::cout << "\nCopy operations:" << std::endl;
    std::copy(vec_mod.begin(), vec_mod.end(), result.begin());
    std::cout << "Copied vector: ";
    for (const auto& val : result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Copy_if
    std::vector<int> even_numbers;
    std::copy_if(vec_mod.begin(), vec_mod.end(), std::back_inserter(even_numbers),
                 [](int x) { return x % 2 == 0; });
    std::cout << "Even numbers: ";
    for (const auto& val : even_numbers) std::cout << val << " ";
    std::cout << std::endl;
    
    // Move
    std::cout << "\nMove operations:" << std::endl;
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(5);
    std::move(source.begin(), source.end(), destination.begin());
    
    std::cout << "Source after move: ";
    for (const auto& val : source) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Destination after move: ";
    for (const auto& val : destination) std::cout << val << " ";
    std::cout << std::endl;
    
    // Transform
    std::cout << "\nTransform operations:" << std::endl;
    std::vector<int> transform_result(vec_mod.size());
    std::transform(vec_mod.begin(), vec_mod.end(), transform_result.begin(),
                   [](int x) { return x * 2; });
    
    std::cout << "Transformed (doubled): ";
    for (const auto& val : transform_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Transform with two ranges
    std::vector<int> vec_a = {1, 2, 3, 4, 5};
    std::vector<int> vec_b = {2, 3, 4, 5, 6};
    std::vector<int> sum_result(vec_a.size());
    
    std::transform(vec_a.begin(), vec_a.end(), vec_b.begin(), sum_result.begin(),
                   std::plus<int>());
    
    std::cout << "Sum of two vectors: ";
    for (const auto& val : sum_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Replace
    std::cout << "\nReplace operations:" << std::endl;
    std::vector<int> replace_vec = {1, 2, 3, 2, 4, 2, 5};
    std::cout << "Before replace: ";
    for (const auto& val : replace_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::replace(replace_vec.begin(), replace_vec.end(), 2, 99);
    std::cout << "After replace 2 with 99: ";
    for (const auto& val : replace_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Replace_if
    std::vector<int> replace_if_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::replace_if(replace_if_vec.begin(), replace_if_vec.end(),
                    [](int x) { return x % 2 == 0; }, 0);
    
    std::cout << "After replace_if (even with 0): ";
    for (const auto& val : replace_if_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Fill
    std::cout << "\nFill operations:" << std::endl;
    std::vector<int> fill_vec(10);
    std::fill(fill_vec.begin(), fill_vec.end(), 42);
    
    std::cout << "Filled vector: ";
    for (const auto& val : fill_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Generate
    std::cout << "\nGenerate operations:" << std::endl;
    std::vector<int> generate_vec(10);
    int counter = 1;
    std::generate(generate_vec.begin(), generate_vec.end(), [&counter]() { return counter++; });
    
    std::cout << "Generated vector: ";
    for (const auto& val : generate_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // 3. Sorting and related operations
    std::cout << "\n3. SORTING AND RELATED OPERATIONS:" << std::endl;
    
    std::vector<int> sort_vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Sort
    std::cout << "\nSort operations:" << std::endl;
    std::cout << "Original: ";
    for (const auto& val : sort_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::sort(sort_vec.begin(), sort_vec.end());
    std::cout << "Sorted ascending: ";
    for (const auto& val : sort_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::sort(sort_vec.begin(), sort_vec.end(), std::greater<int>());
    std::cout << "Sorted descending: ";
    for (const auto& val : sort_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Partial sort
    std::cout << "\nPartial sort operations:" << std::endl;
    std::vector<int> partial_sort_vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::partial_sort(partial_sort_vec.begin(), partial_sort_vec.begin() + 3, partial_sort_vec.end());
    
    std::cout << "Partial sort (first 3): ";
    for (const auto& val : partial_sort_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Nth element
    std::cout << "\nNth element operations:" << std::endl;
    std::vector<int> nth_vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::nth_element(nth_vec.begin(), nth_vec.begin() + 4, nth_vec.end());
    
    std::cout << "Nth element (5th): ";
    for (const auto& val : nth_vec) std::cout << val << " ";
    std::cout << std::endl;
    std::cout << "5th element: " << nth_vec[4] << std::endl;
    
    // Binary search
    std::cout << "\nBinary search operations:" << std::endl;
    std::vector<int> binary_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool found = std::binary_search(binary_vec.begin(), binary_vec.end(), 5);
    std::cout << "Found 5: " << std::boolalpha << found << std::endl;
    
    auto lower = std::lower_bound(binary_vec.begin(), binary_vec.end(), 5);
    auto upper = std::upper_bound(binary_vec.begin(), binary_vec.end(), 5);
    
    std::cout << "Lower bound of 5: " << (lower - binary_vec.begin()) << std::endl;
    std::cout << "Upper bound of 5: " << (upper - binary_vec.begin()) << std::endl;
    
    // 4. Set operations
    std::cout << "\n4. SET OPERATIONS:" << std::endl;
    
    std::set<int> set1 = {1, 2, 3, 4, 5};
    std::set<int> set2 = {4, 5, 6, 7, 8};
    
    std::cout << "Set 1: ";
    for (const auto& val : set1) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Set 2: ";
    for (const auto& val : set2) std::cout << val << " ";
    std::cout << std::endl;
    
    // Union
    std::set<int> union_result;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
                   std::inserter(union_result, union_result.begin()));
    
    std::cout << "Union: ";
    for (const auto& val : union_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Intersection
    std::set<int> intersection_result;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                         std::inserter(intersection_result, intersection_result.begin()));
    
    std::cout << "Intersection: ";
    for (const auto& val : intersection_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Difference
    std::set<int> difference_result;
    std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                       std::inserter(difference_result, difference_result.begin()));
    
    std::cout << "Difference (set1 - set2): ";
    for (const auto& val : difference_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Symmetric difference
    std::set<int> sym_diff_result;
    std::set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                                 std::inserter(sym_diff_result, sym_diff_result.begin()));
    
    std::cout << "Symmetric difference: ";
    for (const auto& val : sym_diff_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // 5. Heap operations
    std::cout << "\n5. HEAP OPERATIONS:" << std::endl;
    
    std::vector<int> heap_vec = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Make heap
    std::cout << "\nHeap operations:" << std::endl;
    std::cout << "Original: ";
    for (const auto& val : heap_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::make_heap(heap_vec.begin(), heap_vec.end());
    std::cout << "Made heap: ";
    for (const auto& val : heap_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Push heap
    heap_vec.push_back(8);
    std::push_heap(heap_vec.begin(), heap_vec.end());
    std::cout << "After push 8: ";
    for (const auto& val : heap_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Pop heap
    std::pop_heap(heap_vec.begin(), heap_vec.end());
    int max_val = heap_vec.back();
    heap_vec.pop_back();
    std::cout << "After pop (max was " << max_val << "): ";
    for (const auto& val : heap_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Sort heap
    std::sort_heap(heap_vec.begin(), heap_vec.end());
    std::cout << "Sorted heap: ";
    for (const auto& val : heap_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // 6. Permutation operations
    std::cout << "\n6. PERMUTATION OPERATIONS:" << std::endl;
    
    std::vector<int> perm_vec = {1, 2, 3};
    
    std::cout << "Original: ";
    for (const auto& val : perm_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Next permutation
    std::cout << "Next permutations: ";
    do {
        for (const auto& val : perm_vec) std::cout << val << " ";
        std::cout << "  ";
    } while (std::next_permutation(perm_vec.begin(), perm_vec.end()));
    std::cout << std::endl;
    
    // 7. Numeric operations
    std::cout << "\n7. NUMERIC OPERATIONS:" << std::endl;
    
    std::vector<int> numeric_vec = {1, 2, 3, 4, 5};
    
    // Accumulate
    int sum = std::accumulate(numeric_vec.begin(), numeric_vec.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    int product = std::accumulate(numeric_vec.begin(), numeric_vec.end(), 1, std::multiplies<int>());
    std::cout << "Product: " << product << std::endl;
    
    // Inner product
    std::vector<int> vec_a = {1, 2, 3, 4, 5};
    std::vector<int> vec_b = {2, 3, 4, 5, 6};
    int inner_prod = std::inner_product(vec_a.begin(), vec_a.end(), vec_b.begin(), 0);
    std::cout << "Inner product: " << inner_prod << std::endl;
    
    // Partial sum
    std::vector<int> partial_sum_result(vec_a.size());
    std::partial_sum(vec_a.begin(), vec_a.end(), partial_sum_result.begin());
    
    std::cout << "Partial sums: ";
    for (const auto& val : partial_sum_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // Adjacent difference
    std::vector<int> adj_diff_result(vec_a.size());
    std::adjacent_difference(vec_a.begin(), vec_a.end(), adj_diff_result.begin());
    
    std::cout << "Adjacent differences: ";
    for (const auto& val : adj_diff_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // 8. Min/Max operations
    std::cout << "\n8. MIN/MAX OPERATIONS:" << std::endl;
    
    std::vector<int> minmax_vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    auto min_it = std::min_element(minmax_vec.begin(), minmax_vec.end());
    auto max_it = std::max_element(minmax_vec.begin(), minmax_vec.end());
    
    std::cout << "Min element: " << *min_it << " at position " << (min_it - minmax_vec.begin()) << std::endl;
    std::cout << "Max element: " << *max_it << " at position " << (max_it - minmax_vec.begin()) << std::endl;
    
    auto minmax_pair = std::minmax_element(minmax_vec.begin(), minmax_vec.end());
    std::cout << "Min: " << *minmax_pair.first << ", Max: " << *minmax_pair.second << std::endl;
    
    // 9. Remove operations
    std::cout << "\n9. REMOVE OPERATIONS:" << std::endl;
    
    std::vector<int> remove_vec = {1, 2, 3, 2, 4, 2, 5, 2, 6};
    std::cout << "Original: ";
    for (const auto& val : remove_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    auto remove_it = std::remove(remove_vec.begin(), remove_vec.end(), 2);
    remove_vec.erase(remove_it, remove_vec.end());
    
    std::cout << "After remove 2: ";
    for (const auto& val : remove_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Remove if
    std::vector<int> remove_if_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto remove_if_it = std::remove_if(remove_if_vec.begin(), remove_if_vec.end(),
                                       [](int x) { return x % 2 == 0; });
    remove_if_vec.erase(remove_if_it, remove_if_vec.end());
    
    std::cout << "After remove_if (even): ";
    for (const auto& val : remove_if_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // 10. Unique operations
    std::cout << "\n10. UNIQUE OPERATIONS:" << std::endl;
    
    std::vector<int> unique_vec = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5};
    std::cout << "Original: ";
    for (const auto& val : unique_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    auto unique_it = std::unique(unique_vec.begin(), unique_vec.end());
    unique_vec.erase(unique_it, unique_vec.end());
    
    std::cout << "After unique: ";
    for (const auto& val : unique_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "\nSTL algorithms demonstration completed!" << std::endl;
    return 0;
}
