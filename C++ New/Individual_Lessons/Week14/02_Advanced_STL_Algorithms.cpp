/*
 * Lesson 14.2: Advanced STL Algorithms
 * 
 * This file demonstrates advanced STL algorithms, custom comparators,
 * algorithm composition, and performance optimization techniques.
 */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>
#include <thread>
#include <future>

// Example 1: Advanced Search Algorithms
namespace AdvancedSearchAlgorithms {
    
    // Binary search with custom comparator
    template<typename Iterator, typename T, typename Compare>
    Iterator binary_search_custom(Iterator first, Iterator last, const T& value, Compare comp) {
        auto it = std::lower_bound(first, last, value, comp);
        if (it != last && !comp(value, *it)) {
            return it;
        }
        return last;
    }
    
    // Find if with multiple conditions
    template<typename Iterator, typename... Predicates>
    Iterator find_if_all(Iterator first, Iterator last, Predicates... preds) {
        return std::find_if(first, last, [&](const auto& value) {
            return (preds(value) && ...);
        });
    }
    
    // Find if with any condition
    template<typename Iterator, typename... Predicates>
    Iterator find_if_any(Iterator first, Iterator last, Predicates... preds) {
        return std::find_if(first, last, [&](const auto& value) {
            return (preds(value) || ...);
        });
    }
    
    // Adjacent find with custom predicate
    template<typename Iterator, typename Predicate>
    Iterator adjacent_find_custom(Iterator first, Iterator last, Predicate pred) {
        if (first == last) return last;
        
        Iterator next = first;
        ++next;
        
        while (next != last) {
            if (pred(*first, *next)) {
                return first;
            }
            ++first;
            ++next;
        }
        return last;
    }
    
    // Search for subsequence with custom comparator
    template<typename Iterator1, typename Iterator2, typename Compare>
    Iterator1 search_custom(Iterator1 first1, Iterator1 last1, 
                           Iterator2 first2, Iterator2 last2, Compare comp) {
        if (first2 == last2) return first1;
        
        while (first1 != last1) {
            Iterator1 it1 = first1;
            Iterator2 it2 = first2;
            
            while (comp(*it1, *it2)) {
                ++it1;
                ++it2;
                if (it2 == last2) return first1;
                if (it1 == last1) return last1;
            }
            ++first1;
        }
        return last1;
    }
    
    void demonstrateAdvancedSearch() {
        std::cout << "=== Advanced Search Algorithms ===" << std::endl;
        
        std::vector<int> vec = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        
        // Binary search with custom comparator
        auto it = binary_search_custom(vec.begin(), vec.end(), 7, std::less<int>{});
        if (it != vec.end()) {
            std::cout << "Found 7 at position: " << std::distance(vec.begin(), it) << std::endl;
        }
        
        // Find if with multiple conditions
        auto even_gt_5 = [](int x) { return x % 2 == 0 && x > 5; };
        auto odd_lt_10 = [](int x) { return x % 2 != 0 && x < 10; };
        
        auto it2 = find_if_all(vec.begin(), vec.end(), even_gt_5, odd_lt_10);
        if (it2 != vec.end()) {
            std::cout << "Found element satisfying all conditions: " << *it2 << std::endl;
        }
        
        // Adjacent find with custom predicate
        std::vector<int> vec2 = {1, 2, 4, 8, 16, 32, 64};
        auto it3 = adjacent_find_custom(vec2.begin(), vec2.end(), 
                                      [](int a, int b) { return b == a * 2; });
        if (it3 != vec2.end()) {
            std::cout << "Found adjacent elements where second is double of first: " 
                      << *it3 << " and " << *(it3 + 1) << std::endl;
        }
        
        // Search for subsequence
        std::vector<int> main_seq = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> sub_seq = {4, 5, 6};
        
        auto it4 = search_custom(main_seq.begin(), main_seq.end(),
                                sub_seq.begin(), sub_seq.end(),
                                std::equal_to<int>{});
        if (it4 != main_seq.end()) {
            std::cout << "Found subsequence at position: " << std::distance(main_seq.begin(), it4) << std::endl;
        }
    }
}

// Example 2: Advanced Sorting Algorithms
namespace AdvancedSortingAlgorithms {
    
    // Merge sort with custom comparator
    template<typename Iterator, typename Compare>
    void merge_sort_custom(Iterator first, Iterator last, Compare comp) {
        if (std::distance(first, last) <= 1) return;
        
        Iterator middle = first + std::distance(first, last) / 2;
        merge_sort_custom(first, middle, comp);
        merge_sort_custom(middle, last, comp);
        
        std::inplace_merge(first, middle, last, comp);
    }
    
    // Quick sort with custom comparator
    template<typename Iterator, typename Compare>
    void quick_sort_custom(Iterator first, Iterator last, Compare comp) {
        if (std::distance(first, last) <= 1) return;
        
        Iterator pivot = std::partition(first, last, [&](const auto& value) {
            return comp(value, *std::prev(last));
        });
        
        quick_sort_custom(first, pivot, comp);
        quick_sort_custom(pivot, last, comp);
    }
    
    // Heap sort with custom comparator
    template<typename Iterator, typename Compare>
    void heap_sort_custom(Iterator first, Iterator last, Compare comp) {
        std::make_heap(first, last, comp);
        std::sort_heap(first, last, comp);
    }
    
    // Counting sort for integers
    template<typename Iterator>
    void counting_sort(Iterator first, Iterator last, int min_val, int max_val) {
        std::vector<int> count(max_val - min_val + 1, 0);
        
        // Count occurrences
        for (auto it = first; it != last; ++it) {
            count[*it - min_val]++;
        }
        
        // Reconstruct sorted sequence
        auto it = first;
        for (int i = 0; i < count.size(); ++i) {
            for (int j = 0; j < count[i]; ++j) {
                *it++ = i + min_val;
            }
        }
    }
    
    // Radix sort for integers
    template<typename Iterator>
    void radix_sort(Iterator first, Iterator last) {
        if (first == last) return;
        
        // Find maximum element
        auto max_elem = *std::max_element(first, last);
        
        // Sort by each digit
        for (int exp = 1; max_elem / exp > 0; exp *= 10) {
            std::vector<int> count(10, 0);
            std::vector<typename std::iterator_traits<Iterator>::value_type> output(
                std::distance(first, last));
            
            // Count occurrences of each digit
            for (auto it = first; it != last; ++it) {
                count[(*it / exp) % 10]++;
            }
            
            // Change count to position
            for (int i = 1; i < 10; ++i) {
                count[i] += count[i - 1];
            }
            
            // Build output array
            for (auto it = last; it != first; --it) {
                output[count[(*std::prev(it) / exp) % 10] - 1] = *std::prev(it);
                count[(*std::prev(it) / exp) % 10]--;
            }
            
            // Copy output back
            std::copy(output.begin(), output.end(), first);
        }
    }
    
    void demonstrateAdvancedSorting() {
        std::cout << "\n=== Advanced Sorting Algorithms ===" << std::endl;
        
        std::vector<int> vec = {64, 34, 25, 12, 22, 11, 90, 5};
        
        // Merge sort
        std::vector<int> vec1 = vec;
        merge_sort_custom(vec1.begin(), vec1.end(), std::less<int>{});
        std::cout << "Merge sort result: ";
        for (const auto& elem : vec1) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Quick sort
        std::vector<int> vec2 = vec;
        quick_sort_custom(vec2.begin(), vec2.end(), std::less<int>{});
        std::cout << "Quick sort result: ";
        for (const auto& elem : vec2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Heap sort
        std::vector<int> vec3 = vec;
        heap_sort_custom(vec3.begin(), vec3.end(), std::less<int>{});
        std::cout << "Heap sort result: ";
        for (const auto& elem : vec3) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Counting sort
        std::vector<int> vec4 = vec;
        counting_sort(vec4.begin(), vec4.end(), 5, 90);
        std::cout << "Counting sort result: ";
        for (const auto& elem : vec4) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Radix sort
        std::vector<int> vec5 = vec;
        radix_sort(vec5.begin(), vec5.end());
        std::cout << "Radix sort result: ";
        for (const auto& elem : vec5) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 3: Advanced Transform Algorithms
namespace AdvancedTransformAlgorithms {
    
    // Transform with multiple input ranges
    template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOp>
    OutputIterator transform_two_ranges(InputIterator1 first1, InputIterator1 last1,
                                       InputIterator2 first2, InputIterator2 last2,
                                       OutputIterator result, BinaryOp op) {
        while (first1 != last1 && first2 != last2) {
            *result = op(*first1, *first2);
            ++first1;
            ++first2;
            ++result;
        }
        return result;
    }
    
    // Transform with index
    template<typename InputIterator, typename OutputIterator, typename UnaryOp>
    OutputIterator transform_with_index(InputIterator first, InputIterator last,
                                       OutputIterator result, UnaryOp op) {
        size_t index = 0;
        while (first != last) {
            *result = op(*first, index);
            ++first;
            ++result;
            ++index;
        }
        return result;
    }
    
    // Transform with state
    template<typename InputIterator, typename OutputIterator, typename UnaryOp, typename State>
    OutputIterator transform_with_state(InputIterator first, InputIterator last,
                                       OutputIterator result, UnaryOp op, State& state) {
        while (first != last) {
            *result = op(*first, state);
            ++first;
            ++result;
        }
        return result;
    }
    
    // Transform with predicate
    template<typename InputIterator, typename OutputIterator, typename UnaryOp, typename Predicate>
    OutputIterator transform_if(InputIterator first, InputIterator last,
                               OutputIterator result, UnaryOp op, Predicate pred) {
        while (first != last) {
            if (pred(*first)) {
                *result = op(*first);
                ++result;
            }
            ++first;
        }
        return result;
    }
    
    // Transform with multiple outputs
    template<typename InputIterator, typename OutputIterator1, typename OutputIterator2, typename BinaryOp>
    std::pair<OutputIterator1, OutputIterator2> transform_to_two_outputs(
        InputIterator first, InputIterator last,
        OutputIterator1 result1, OutputIterator2 result2, BinaryOp op) {
        while (first != last) {
            auto result = op(*first);
            *result1 = result.first;
            *result2 = result.second;
            ++first;
            ++result1;
            ++result2;
        }
        return {result1, result2};
    }
    
    void demonstrateAdvancedTransform() {
        std::cout << "\n=== Advanced Transform Algorithms ===" << std::endl;
        
        std::vector<int> vec1 = {1, 2, 3, 4, 5};
        std::vector<int> vec2 = {10, 20, 30, 40, 50};
        std::vector<int> result(5);
        
        // Transform with two input ranges
        transform_two_ranges(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                           result.begin(), std::plus<int>{});
        std::cout << "Transform two ranges (addition): ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Transform with index
        std::vector<int> result2(5);
        transform_with_index(vec1.begin(), vec1.end(), result2.begin(),
                           [](int value, size_t index) { return value * index; });
        std::cout << "Transform with index: ";
        for (const auto& elem : result2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Transform with state
        int multiplier = 2;
        std::vector<int> result3(5);
        transform_with_state(vec1.begin(), vec1.end(), result3.begin(),
                           [](int value, int& mult) { return value * mult++; }, multiplier);
        std::cout << "Transform with state: ";
        for (const auto& elem : result3) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Transform with predicate
        std::vector<int> result4;
        transform_if(vec1.begin(), vec1.end(), std::back_inserter(result4),
                    [](int x) { return x * x; },
                    [](int x) { return x % 2 == 0; });
        std::cout << "Transform if (even numbers squared): ";
        for (const auto& elem : result4) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Transform to two outputs
        std::vector<int> result5(5), result6(5);
        transform_to_two_outputs(vec1.begin(), vec1.end(), result5.begin(), result6.begin(),
                               [](int x) { return std::make_pair(x * 2, x * 3); });
        std::cout << "Transform to two outputs (x*2, x*3): ";
        for (size_t i = 0; i < result5.size(); ++i) {
            std::cout << "{" << result5[i] << ", " << result6[i] << "} ";
        }
        std::cout << std::endl;
    }
}

// Example 4: Advanced Partition Algorithms
namespace AdvancedPartitionAlgorithms {
    
    // Partition with custom predicate
    template<typename Iterator, typename Predicate>
    Iterator partition_custom(Iterator first, Iterator last, Predicate pred) {
        while (first != last) {
            while (pred(*first)) {
                ++first;
                if (first == last) return first;
            }
            do {
                --last;
                if (first == last) return first;
            } while (!pred(*last));
            std::iter_swap(first, last);
            ++first;
        }
        return first;
    }
    
    // Stable partition with custom predicate
    template<typename Iterator, typename Predicate>
    Iterator stable_partition_custom(Iterator first, Iterator last, Predicate pred) {
        if (first == last) return first;
        
        auto middle = first + std::distance(first, last) / 2;
        auto left = stable_partition_custom(first, middle, pred);
        auto right = stable_partition_custom(middle, last, pred);
        
        return std::rotate(left, middle, right);
    }
    
    // Partition point with custom predicate
    template<typename Iterator, typename Predicate>
    Iterator partition_point_custom(Iterator first, Iterator last, Predicate pred) {
        while (first != last) {
            auto middle = first + std::distance(first, last) / 2;
            if (pred(*middle)) {
                first = middle + 1;
            } else {
                last = middle;
            }
        }
        return first;
    }
    
    // Three-way partition (Dutch flag)
    template<typename Iterator, typename T>
    std::pair<Iterator, Iterator> three_way_partition(Iterator first, Iterator last, const T& pivot) {
        auto low = first;
        auto mid = first;
        auto high = last - 1;
        
        while (mid <= high) {
            if (*mid < pivot) {
                std::iter_swap(low, mid);
                ++low;
                ++mid;
            } else if (*mid > pivot) {
                std::iter_swap(mid, high);
                --high;
            } else {
                ++mid;
            }
        }
        
        return {low, mid};
    }
    
    void demonstrateAdvancedPartition() {
        std::cout << "\n=== Advanced Partition Algorithms ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Partition with custom predicate
        auto it = partition_custom(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
        std::cout << "Partition (even numbers first): ";
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << "Partition point: " << std::distance(vec.begin(), it) << std::endl;
        
        // Three-way partition
        std::vector<int> vec2 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        auto pivot = 5;
        auto [low, high] = three_way_partition(vec2.begin(), vec2.end(), pivot);
        
        std::cout << "Three-way partition (pivot = 5): ";
        for (const auto& elem : vec2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << "Partition points: " << std::distance(vec2.begin(), low) 
                  << " and " << std::distance(vec2.begin(), high) << std::endl;
    }
}

// Example 5: Advanced Accumulate Algorithms
namespace AdvancedAccumulateAlgorithms {
    
    // Accumulate with custom binary operation
    template<typename Iterator, typename T, typename BinaryOp>
    T accumulate_custom(Iterator first, Iterator last, T init, BinaryOp op) {
        while (first != last) {
            init = op(init, *first);
            ++first;
        }
        return init;
    }
    
    // Accumulate with index
    template<typename Iterator, typename T, typename BinaryOp>
    T accumulate_with_index(Iterator first, Iterator last, T init, BinaryOp op) {
        size_t index = 0;
        while (first != last) {
            init = op(init, *first, index);
            ++first;
            ++index;
        }
        return init;
    }
    
    // Accumulate with state
    template<typename Iterator, typename T, typename BinaryOp, typename State>
    T accumulate_with_state(Iterator first, Iterator last, T init, BinaryOp op, State& state) {
        while (first != last) {
            init = op(init, *first, state);
            ++first;
        }
        return init;
    }
    
    // Accumulate with predicate
    template<typename Iterator, typename T, typename BinaryOp, typename Predicate>
    T accumulate_if(Iterator first, Iterator last, T init, BinaryOp op, Predicate pred) {
        while (first != last) {
            if (pred(*first)) {
                init = op(init, *first);
            }
            ++first;
        }
        return init;
    }
    
    // Partial sum with custom operation
    template<typename Iterator, typename OutputIterator, typename BinaryOp>
    OutputIterator partial_sum_custom(Iterator first, Iterator last, OutputIterator result, BinaryOp op) {
        if (first == last) return result;
        
        typename std::iterator_traits<Iterator>::value_type sum = *first;
        *result = sum;
        ++result;
        ++first;
        
        while (first != last) {
            sum = op(sum, *first);
            *result = sum;
            ++result;
            ++first;
        }
        return result;
    }
    
    // Adjacent difference with custom operation
    template<typename Iterator, typename OutputIterator, typename BinaryOp>
    OutputIterator adjacent_difference_custom(Iterator first, Iterator last, OutputIterator result, BinaryOp op) {
        if (first == last) return result;
        
        typename std::iterator_traits<Iterator>::value_type prev = *first;
        *result = prev;
        ++result;
        ++first;
        
        while (first != last) {
            typename std::iterator_traits<Iterator>::value_type curr = *first;
            *result = op(curr, prev);
            prev = curr;
            ++result;
            ++first;
        }
        return result;
    }
    
    void demonstrateAdvancedAccumulate() {
        std::cout << "\n=== Advanced Accumulate Algorithms ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        // Accumulate with custom operation
        int product = accumulate_custom(vec.begin(), vec.end(), 1, std::multiplies<int>{});
        std::cout << "Product of elements: " << product << std::endl;
        
        // Accumulate with index
        int weighted_sum = accumulate_with_index(vec.begin(), vec.end(), 0,
                                                [](int acc, int value, size_t index) {
                                                    return acc + value * index;
                                                });
        std::cout << "Weighted sum: " << weighted_sum << std::endl;
        
        // Accumulate with state
        int counter = 0;
        int sum_with_counter = accumulate_with_state(vec.begin(), vec.end(), 0,
                                                    [](int acc, int value, int& count) {
                                                        count++;
                                                        return acc + value * count;
                                                    }, counter);
        std::cout << "Sum with counter: " << sum_with_counter << std::endl;
        
        // Accumulate with predicate
        int sum_even = accumulate_if(vec.begin(), vec.end(), 0, std::plus<int>{},
                                    [](int x) { return x % 2 == 0; });
        std::cout << "Sum of even elements: " << sum_even << std::endl;
        
        // Partial sum
        std::vector<int> partial_sums(5);
        partial_sum_custom(vec.begin(), vec.end(), partial_sums.begin(), std::plus<int>{});
        std::cout << "Partial sums: ";
        for (const auto& elem : partial_sums) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Adjacent difference
        std::vector<int> adjacent_diffs(5);
        adjacent_difference_custom(vec.begin(), vec.end(), adjacent_diffs.begin(), std::minus<int>{});
        std::cout << "Adjacent differences: ";
        for (const auto& elem : adjacent_diffs) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 6: Algorithm Composition
namespace AlgorithmComposition {
    
    // Compose multiple algorithms
    template<typename Container, typename... Algorithms>
    auto compose_algorithms(Container& container, Algorithms... algos) {
        return [&](auto... args) {
            (algos(container, args), ...);
        };
    }
    
    // Pipeline algorithms
    template<typename Container, typename... Algorithms>
    auto pipeline_algorithms(Container& container, Algorithms... algos) {
        return [&](auto... args) {
            auto result = container;
            ((result = algos(result, args)), ...);
            return result;
        };
    }
    
    // Conditional algorithm execution
    template<typename Container, typename Algorithm, typename Condition>
    auto conditional_algorithm(Container& container, Algorithm algo, Condition cond) {
        return [&](auto... args) {
            if (cond(container)) {
                return algo(container, args...);
            }
            return container;
        };
    }
    
    // Algorithm with error handling
    template<typename Container, typename Algorithm, typename ErrorHandler>
    auto safe_algorithm(Container& container, Algorithm algo, ErrorHandler handler) {
        return [&](auto... args) {
            try {
                return algo(container, args...);
            } catch (...) {
                return handler(container, args...);
            }
        };
    }
    
    void demonstrateAlgorithmComposition() {
        std::cout << "\n=== Algorithm Composition ===" << std::endl;
        
        std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        
        // Compose algorithms
        auto sort_and_unique = compose_algorithms(vec,
            [](auto& container) { std::sort(container.begin(), container.end()); },
            [](auto& container) { container.erase(std::unique(container.begin(), container.end()), container.end()); }
        );
        
        std::cout << "Original vector: ";
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        sort_and_unique();
        
        std::cout << "After sort and unique: ";
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Pipeline algorithms
        auto transform_and_filter = pipeline_algorithms(vec,
            [](const auto& container, auto op) {
                std::vector<int> result;
                std::transform(container.begin(), container.end(), std::back_inserter(result), op);
                return result;
            },
            [](const auto& container, auto pred) {
                std::vector<int> result;
                std::copy_if(container.begin(), container.end(), std::back_inserter(result), pred);
                return result;
            }
        );
        
        auto result = transform_and_filter([](int x) { return x * 2; }, [](int x) { return x > 10; });
        
        std::cout << "Transform (x*2) and filter (>10): ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Conditional algorithm
        auto conditional_sort = conditional_algorithm(vec,
            [](auto& container) { std::sort(container.begin(), container.end()); },
            [](const auto& container) { return container.size() > 5; }
        );
        
        std::vector<int> small_vec = {3, 1, 2};
        conditional_sort();
        std::cout << "Conditional sort (size > 5): ";
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Safe algorithm
        auto safe_divide = safe_algorithm(vec,
            [](auto& container, int divisor) {
                std::transform(container.begin(), container.end(), container.begin(),
                              [divisor](int x) { return x / divisor; });
                return container;
            },
            [](auto& container, int divisor) {
                std::cout << "Error: Division by " << divisor << std::endl;
                return container;
            }
        );
        
        safe_divide(2);
        std::cout << "Safe divide by 2: ";
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 7: Performance Optimization
namespace PerformanceOptimization {
    
    // Parallel algorithm execution
    template<typename Iterator, typename Algorithm>
    void parallel_algorithm(Iterator first, Iterator last, Algorithm algo) {
        const size_t num_threads = std::thread::hardware_concurrency();
        const size_t chunk_size = std::distance(first, last) / num_threads;
        
        std::vector<std::future<void>> futures;
        
        for (size_t i = 0; i < num_threads; ++i) {
            auto chunk_first = first + i * chunk_size;
            auto chunk_last = (i == num_threads - 1) ? last : chunk_first + chunk_size;
            
            futures.emplace_back(std::async(std::launch::async, [=]() {
                algo(chunk_first, chunk_last);
            }));
        }
        
        for (auto& future : futures) {
            future.wait();
        }
    }
    
    // Cache-friendly algorithm
    template<typename Iterator, typename Algorithm>
    void cache_friendly_algorithm(Iterator first, Iterator last, Algorithm algo) {
        const size_t cache_line_size = 64;
        const size_t element_size = sizeof(typename std::iterator_traits<Iterator>::value_type);
        const size_t elements_per_cache_line = cache_line_size / element_size;
        
        for (auto it = first; it < last; it += elements_per_cache_line) {
            auto chunk_end = std::min(it + elements_per_cache_line, last);
            algo(it, chunk_end);
        }
    }
    
    // SIMD-friendly algorithm
    template<typename Iterator, typename Algorithm>
    void simd_friendly_algorithm(Iterator first, Iterator last, Algorithm algo) {
        const size_t simd_width = 4; // Assume 4 elements per SIMD instruction
        
        // Process SIMD-width chunks
        for (auto it = first; it < last; it += simd_width) {
            auto chunk_end = std::min(it + simd_width, last);
            algo(it, chunk_end);
        }
    }
    
    // Memory pool algorithm
    template<typename Iterator, typename Algorithm>
    void memory_pool_algorithm(Iterator first, Iterator last, Algorithm algo) {
        const size_t pool_size = 1024;
        std::vector<char> memory_pool(pool_size);
        
        // Use memory pool for temporary storage
        algo(first, last);
    }
    
    void demonstratePerformanceOptimization() {
        std::cout << "\n=== Performance Optimization ===" << std::endl;
        
        const size_t size = 1000000;
        std::vector<int> vec(size);
        
        // Fill with random values
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        for (auto& elem : vec) {
            elem = dis(gen);
        }
        
        // Measure standard sort
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(vec.begin(), vec.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto standard_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Standard sort time: " << standard_time.count() << " microseconds" << std::endl;
        
        // Measure parallel sort
        std::vector<int> vec2 = vec;
        start = std::chrono::high_resolution_clock::now();
        parallel_algorithm(vec2.begin(), vec2.end(), [](auto first, auto last) {
            std::sort(first, last);
        });
        end = std::chrono::high_resolution_clock::now();
        auto parallel_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Parallel sort time: " << parallel_time.count() << " microseconds" << std::endl;
        
        // Measure cache-friendly algorithm
        std::vector<int> vec3 = vec;
        start = std::chrono::high_resolution_clock::now();
        cache_friendly_algorithm(vec3.begin(), vec3.end(), [](auto first, auto last) {
            std::sort(first, last);
        });
        end = std::chrono::high_resolution_clock::now();
        auto cache_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Cache-friendly sort time: " << cache_time.count() << " microseconds" << std::endl;
        
        // Performance comparison
        std::cout << "Performance improvement:" << std::endl;
        std::cout << "  Parallel vs Standard: " << (double)standard_time.count() / parallel_time.count() << "x" << std::endl;
        std::cout << "  Cache-friendly vs Standard: " << (double)standard_time.count() / cache_time.count() << "x" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced STL Algorithms Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced STL algorithms, custom comparators,\n"
              << "algorithm composition, and performance optimization techniques.\n" << std::endl;
    
    // Demonstrate various advanced algorithm concepts
    AdvancedSearchAlgorithms::demonstrateAdvancedSearch();
    AdvancedSortingAlgorithms::demonstrateAdvancedSorting();
    AdvancedTransformAlgorithms::demonstrateAdvancedTransform();
    AdvancedPartitionAlgorithms::demonstrateAdvancedPartition();
    AdvancedAccumulateAlgorithms::demonstrateAdvancedAccumulate();
    AlgorithmComposition::demonstrateAlgorithmComposition();
    PerformanceOptimization::demonstratePerformanceOptimization();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Advanced search algorithms provide flexible and efficient searching" << std::endl;
    std::cout << "2. Custom sorting algorithms can be optimized for specific use cases" << std::endl;
    std::cout << "3. Transform algorithms can handle complex transformations and conditions" << std::endl;
    std::cout << "4. Partition algorithms enable efficient data organization" << std::endl;
    std::cout << "5. Accumulate algorithms support complex aggregation operations" << std::endl;
    std::cout << "6. Algorithm composition enables reusable and modular code" << std::endl;
    std::cout << "7. Performance optimization techniques can significantly improve execution speed" << std::endl;
    std::cout << "8. Custom algorithms can be tailored to specific requirements and constraints" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_stl_algorithms 02_Advanced_STL_Algorithms.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_stl_algorithms 02_Advanced_STL_Algorithms.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Advanced_STL_Algorithms.cpp
 * 
 * Running:
 * ./advanced_stl_algorithms (Linux/macOS)
 * advanced_stl_algorithms.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best algorithm support.
 * 
 * Advanced STL Algorithms Notes:
 * - Advanced search algorithms provide flexible and efficient searching
 * - Custom sorting algorithms can be optimized for specific use cases
 * - Transform algorithms can handle complex transformations and conditions
 * - Partition algorithms enable efficient data organization
 * - Accumulate algorithms support complex aggregation operations
 * - Algorithm composition enables reusable and modular code
 * - Performance optimization techniques can significantly improve execution speed
 * - Custom algorithms can be tailored to specific requirements and constraints
 */"""
