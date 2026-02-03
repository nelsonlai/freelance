#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <thread>
#include <execution>

// Demonstrates performance optimization techniques
int main() {
    std::cout << "Performance Optimization Demonstration" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // 1. Compiler Optimizations
    std::cout << "\n1. COMPILER OPTIMIZATIONS:" << std::endl;
    
    // Function inlining
    inline int add_inline(int a, int b) {
        return a + b;
    }
    
    int result = add_inline(5, 3);
    std::cout << "  Inline function result: " << result << std::endl;
    
    // Loop unrolling simulation
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Regular loop
    int sum1 = 0;
    for (int num : numbers) {
        sum1 += num;
    }
    std::cout << "  Regular loop sum: " << sum1 << std::endl;
    
    // Unrolled loop (manual)
    int sum2 = 0;
    for (size_t i = 0; i < numbers.size(); i += 2) {
        sum2 += numbers[i];
        if (i + 1 < numbers.size()) {
            sum2 += numbers[i + 1];
        }
    }
    std::cout << "  Unrolled loop sum: " << sum2 << std::endl;
    
    // 2. Profiling and Benchmarking
    std::cout << "\n2. PROFILING AND BENCHMARKING:" << std::endl;
    
    const int size = 1000000;
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 0);
    
    // Benchmark sorting
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Sorting " << size << " elements took: " << sort_time.count() << " microseconds" << std::endl;
    
    // Benchmark searching
    start = std::chrono::high_resolution_clock::now();
    auto it = std::find(data.begin(), data.end(), size / 2);
    end = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Linear search took: " << search_time.count() << " microseconds" << std::endl;
    
    // Binary search
    start = std::chrono::high_resolution_clock::now();
    bool found = std::binary_search(data.begin(), data.end(), size / 2);
    end = std::chrono::high_resolution_clock::now();
    auto binary_search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Binary search took: " << binary_search_time.count() << " microseconds" << std::endl;
    std::cout << "  Binary search speedup: " << (double)search_time.count() / binary_search_time.count() << "x" << std::endl;
    
    // 3. Cache Optimization
    std::cout << "\n3. CACHE OPTIMIZATION:" << std::endl;
    
    const int matrix_size = 1000;
    std::vector<std::vector<int>> matrix(matrix_size, std::vector<int>(matrix_size));
    
    // Initialize matrix
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    
    // Cache-friendly: row-major access
    start = std::chrono::high_resolution_clock::now();
    int sum_row_major = 0;
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            sum_row_major += matrix[i][j];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto row_major_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Cache-unfriendly: column-major access
    start = std::chrono::high_resolution_clock::now();
    int sum_col_major = 0;
    for (int j = 0; j < matrix_size; ++j) {
        for (int i = 0; i < matrix_size; ++i) {
            sum_col_major += matrix[i][j];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto col_major_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Row-major access time: " << row_major_time.count() << " microseconds" << std::endl;
    std::cout << "  Column-major access time: " << col_major_time.count() << " microseconds" << std::endl;
    std::cout << "  Row-major speedup: " << (double)col_major_time.count() / row_major_time.count() << "x" << std::endl;
    
    // 4. Algorithmic Optimization
    std::cout << "\n4. ALGORITHMIC OPTIMIZATION:" << std::endl;
    
    // Naive Fibonacci
    auto naive_fib = [](int n) -> long long {
        if (n <= 1) return n;
        return naive_fib(n - 1) + naive_fib(n - 2);
    };
    
    // Optimized Fibonacci with memoization
    std::unordered_map<int, long long> memo;
    auto optimized_fib = [&memo](int n) -> long long {
        if (n <= 1) return n;
        if (memo.find(n) != memo.end()) return memo[n];
        memo[n] = optimized_fib(n - 1) + optimized_fib(n - 2);
        return memo[n];
    };
    
    // Iterative Fibonacci
    auto iterative_fib = [](int n) -> long long {
        if (n <= 1) return n;
        long long a = 0, b = 1;
        for (int i = 2; i <= n; ++i) {
            long long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    };
    
    int fib_n = 30;
    
    start = std::chrono::high_resolution_clock::now();
    long long result1 = optimized_fib(fib_n);
    end = std::chrono::high_resolution_clock::now();
    auto optimized_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    long long result2 = iterative_fib(fib_n);
    end = std::chrono::high_resolution_clock::now();
    auto iterative_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Fibonacci(" << fib_n << ") = " << result1 << std::endl;
    std::cout << "  Optimized (memoized) time: " << optimized_time.count() << " microseconds" << std::endl;
    std::cout << "  Iterative time: " << iterative_time.count() << " microseconds" << std::endl;
    
    // 5. Parallel Algorithms
    std::cout << "\n5. PARALLEL ALGORITHMS:" << std::endl;
    
    std::vector<int> parallel_data(1000000);
    std::iota(parallel_data.begin(), parallel_data.end(), 0);
    
    // Sequential transform
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> sequential_result(parallel_data.size());
    std::transform(parallel_data.begin(), parallel_data.end(), sequential_result.begin(),
                   [](int x) { return x * x; });
    end = std::chrono::high_resolution_clock::now();
    auto sequential_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Parallel transform
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> parallel_result(parallel_data.size());
    std::transform(std::execution::par, parallel_data.begin(), parallel_data.end(), 
                   parallel_result.begin(), [](int x) { return x * x; });
    end = std::chrono::high_resolution_clock::now();
    auto parallel_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Sequential transform time: " << sequential_time.count() << " microseconds" << std::endl;
    std::cout << "  Parallel transform time: " << parallel_time.count() << " microseconds" << std::endl;
    std::cout << "  Parallel speedup: " << (double)sequential_time.count() / parallel_time.count() << "x" << std::endl;
    
    // 6. Memory Access Patterns
    std::cout << "\n6. MEMORY ACCESS PATTERNS:" << std::endl;
    
    const int array_size = 1000000;
    std::vector<int> array(array_size);
    std::iota(array.begin(), array.end(), 0);
    
    // Sequential access
    start = std::chrono::high_resolution_clock::now();
    int sequential_sum = 0;
    for (int i = 0; i < array_size; ++i) {
        sequential_sum += array[i];
    }
    end = std::chrono::high_resolution_clock::now();
    auto sequential_access_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Random access
    std::vector<int> random_indices(array_size);
    std::iota(random_indices.begin(), random_indices.end(), 0);
    std::shuffle(random_indices.begin(), random_indices.end(), gen);
    
    start = std::chrono::high_resolution_clock::now();
    int random_sum = 0;
    for (int idx : random_indices) {
        random_sum += array[idx];
    }
    end = std::chrono::high_resolution_clock::now();
    auto random_access_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Sequential access time: " << sequential_access_time.count() << " microseconds" << std::endl;
    std::cout << "  Random access time: " << random_access_time.count() << " microseconds" << std::endl;
    std::cout << "  Sequential access speedup: " << (double)random_access_time.count() / sequential_access_time.count() << "x" << std::endl;
    
    // 7. Branch Prediction Optimization
    std::cout << "\n7. BRANCH PREDICTION OPTIMIZATION:" << std::endl;
    
    std::vector<int> unsorted_data(100000);
    std::iota(unsorted_data.begin(), unsorted_data.end(), 0);
    std::shuffle(unsorted_data.begin(), unsorted_data.end(), gen);
    
    // Unsorted data (poor branch prediction)
    start = std::chrono::high_resolution_clock::now();
    int unsorted_count = 0;
    for (int value : unsorted_data) {
        if (value < 50000) {  // Random branch
            unsorted_count++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto unsorted_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Sorted data (good branch prediction)
    std::sort(unsorted_data.begin(), unsorted_data.end());
    
    start = std::chrono::high_resolution_clock::now();
    int sorted_count = 0;
    for (int value : unsorted_data) {
        if (value < 50000) {  // Predictable branch
            sorted_count++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto sorted_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Unsorted data time: " << unsorted_time.count() << " microseconds" << std::endl;
    std::cout << "  Sorted data time: " << sorted_time.count() << " microseconds" << std::endl;
    std::cout << "  Branch prediction speedup: " << (double)unsorted_time.count() / sorted_time.count() << "x" << std::endl;
    
    // 8. Template Metaprogramming for Performance
    std::cout << "\n8. TEMPLATE METAPROGRAMMING FOR PERFORMANCE:" << std::endl;
    
    // Compile-time power calculation
    template<int Base, int Exponent>
    struct Power {
        static const int value = Base * Power<Base, Exponent-1>::value;
    };
    
    template<int Base>
    struct Power<Base, 0> {
        static const int value = 1;
    };
    
    // Runtime power calculation
    auto runtime_power = [](int base, int exp) -> int {
        int result = 1;
        for (int i = 0; i < exp; ++i) {
            result *= base;
        }
        return result;
    };
    
    const int base = 2;
    const int exp = 10;
    
    start = std::chrono::high_resolution_clock::now();
    int compile_time_result = Power<base, exp>::value;
    end = std::chrono::high_resolution_clock::now();
    auto compile_time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int runtime_result = runtime_power(base, exp);
    end = std::chrono::high_resolution_clock::now();
    auto runtime_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "  Compile-time result: " << compile_time_result << " (time: " << compile_time_duration.count() << " ns)" << std::endl;
    std::cout << "  Runtime result: " << runtime_result << " (time: " << runtime_duration.count() << " ns)" << std::endl;
    
    // 9. Data Structure Optimization
    std::cout << "\n9. DATA STRUCTURE OPTIMIZATION:" << std::endl;
    
    const int num_elements = 100000;
    
    // Vector vs List performance
    std::vector<int> vec;
    std::list<int> lst;
    
    // Insertion performance
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        vec.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto vec_insert_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        lst.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto lst_insert_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Vector insertion time: " << vec_insert_time.count() << " microseconds" << std::endl;
    std::cout << "  List insertion time: " << lst_insert_time.count() << " microseconds" << std::endl;
    
    // Search performance
    start = std::chrono::high_resolution_clock::now();
    auto vec_it = std::find(vec.begin(), vec.end(), num_elements / 2);
    end = std::chrono::high_resolution_clock::now();
    auto vec_search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto lst_it = std::find(lst.begin(), lst.end(), num_elements / 2);
    end = std::chrono::high_resolution_clock::now();
    auto lst_search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Vector search time: " << vec_search_time.count() << " microseconds" << std::endl;
    std::cout << "  List search time: " << lst_search_time.count() << " microseconds" << std::endl;
    
    // 10. Optimization Best Practices
    std::cout << "\n10. OPTIMIZATION BEST PRACTICES:" << std::endl;
    
    // Use const where possible
    const std::vector<int> const_data = {1, 2, 3, 4, 5};
    
    // Use references to avoid copying
    auto process_by_reference = [](const std::vector<int>& data) -> int {
        return std::accumulate(data.begin(), data.end(), 0);
    };
    
    // Use move semantics
    auto process_by_move = [](std::vector<int>&& data) -> int {
        return std::accumulate(data.begin(), data.end(), 0);
    };
    
    std::vector<int> large_data(1000000, 42);
    
    start = std::chrono::high_resolution_clock::now();
    int ref_result = process_by_reference(large_data);
    end = std::chrono::high_resolution_clock::now();
    auto ref_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int move_result = process_by_move(std::move(large_data));
    end = std::chrono::high_resolution_clock::now();
    auto move_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Reference processing time: " << ref_time.count() << " microseconds" << std::endl;
    std::cout << "  Move processing time: " << move_time.count() << " microseconds" << std::endl;
    std::cout << "  Results: ref=" << ref_result << ", move=" << move_result << std::endl;
    
    std::cout << "\nPerformance optimization demonstration completed!" << std::endl;
    return 0;
}
