/*
 * Lesson 20.3: Advanced Performance Engineering
 * 
 * This file demonstrates advanced performance engineering techniques including
 * profiling, benchmarking, optimization strategies, memory optimization,
 * cache optimization, and performance monitoring.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>
#include <random>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <array>
#include <tuple>
#include <type_traits>
#include <optional>
#include <variant>
#include <any>
#include <string_view>
#include <filesystem>
#include <execution>
#include <coroutine>
#include <concepts>
#include <ranges>
#include <barrier>
#include <latch>
#include <semaphore>
#include <stop_token>
#include <jthread>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <set>
#include <list>
#include <deque>

// Example 1: Profiling and Benchmarking
namespace ProfilingBenchmarking {
    
    // High-resolution timer for benchmarking
    class HighResolutionTimer {
    private:
        std::chrono::high_resolution_clock::time_point start_time_;
        std::chrono::high_resolution_clock::time_point end_time_;
        
    public:
        void start() {
            start_time_ = std::chrono::high_resolution_clock::now();
        }
        
        void stop() {
            end_time_ = std::chrono::high_resolution_clock::now();
        }
        
        template<typename Duration = std::chrono::microseconds>
        auto elapsed() const {
            return std::chrono::duration_cast<Duration>(end_time_ - start_time_).count();
        }
        
        double elapsed_seconds() const {
            return std::chrono::duration<double>(end_time_ - start_time_).count();
        }
    };
    
    // Benchmark runner
    class BenchmarkRunner {
    private:
        struct BenchmarkResult {
            std::string name;
            double min_time;
            double max_time;
            double avg_time;
            double median_time;
            double std_dev;
            size_t iterations;
        };
        
        std::vector<BenchmarkResult> results_;
        
    public:
        template<typename Func>
        void run_benchmark(const std::string& name, Func&& func, size_t iterations = 1000) {
            std::vector<double> times;
            times.reserve(iterations);
            
            // Warmup
            for (size_t i = 0; i < 10; ++i) {
                func();
            }
            
            // Benchmark
            HighResolutionTimer timer;
            for (size_t i = 0; i < iterations; ++i) {
                timer.start();
                func();
                timer.stop();
                times.push_back(timer.elapsed_seconds());
            }
            
            // Calculate statistics
            std::sort(times.begin(), times.end());
            
            double min_time = times.front();
            double max_time = times.back();
            double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
            double median_time = times[times.size() / 2];
            
            // Calculate standard deviation
            double variance = 0.0;
            for (double time : times) {
                variance += (time - avg_time) * (time - avg_time);
            }
            double std_dev = std::sqrt(variance / times.size());
            
            results_.push_back({name, min_time, max_time, avg_time, median_time, std_dev, iterations});
        }
        
        void print_results() {
            std::cout << "\n=== Benchmark Results ===" << std::endl;
            std::cout << std::setw(20) << "Name" 
                      << std::setw(15) << "Min (μs)" 
                      << std::setw(15) << "Max (μs)" 
                      << std::setw(15) << "Avg (μs)" 
                      << std::setw(15) << "Median (μs)" 
                      << std::setw(15) << "Std Dev" 
                      << std::setw(10) << "Iterations" << std::endl;
            std::cout << std::string(100, '-') << std::endl;
            
            for (const auto& result : results_) {
                std::cout << std::setw(20) << result.name
                          << std::setw(15) << std::fixed << std::setprecision(2) << result.min_time * 1e6
                          << std::setw(15) << std::fixed << std::setprecision(2) << result.max_time * 1e6
                          << std::setw(15) << std::fixed << std::setprecision(2) << result.avg_time * 1e6
                          << std::setw(15) << std::fixed << std::setprecision(2) << result.median_time * 1e6
                          << std::setw(15) << std::fixed << std::setprecision(2) << result.std_dev * 1e6
                          << std::setw(10) << result.iterations << std::endl;
            }
        }
        
        void save_results_to_file(const std::string& filename) {
            std::ofstream file(filename);
            if (file.is_open()) {
                file << "Name,Min (μs),Max (μs),Avg (μs),Median (μs),Std Dev,Iterations\n";
                for (const auto& result : results_) {
                    file << result.name << ","
                         << result.min_time * 1e6 << ","
                         << result.max_time * 1e6 << ","
                         << result.avg_time * 1e6 << ","
                         << result.median_time * 1e6 << ","
                         << result.std_dev * 1e6 << ","
                         << result.iterations << "\n";
                }
                file.close();
                std::cout << "Results saved to " << filename << std::endl;
            }
        }
    };
    
    // Memory usage profiler
    class MemoryProfiler {
    private:
        size_t initial_memory_;
        size_t peak_memory_;
        size_t current_memory_;
        
    public:
        MemoryProfiler() {
            initial_memory_ = get_current_memory_usage();
            peak_memory_ = initial_memory_;
            current_memory_ = initial_memory_;
        }
        
        void update() {
            current_memory_ = get_current_memory_usage();
            peak_memory_ = std::max(peak_memory_, current_memory_);
        }
        
        size_t get_peak_memory() const {
            return peak_memory_;
        }
        
        size_t get_current_memory() const {
            return current_memory_;
        }
        
        size_t get_memory_increase() const {
            return current_memory_ - initial_memory_;
        }
        
    private:
        size_t get_current_memory_usage() {
            // Simplified memory usage tracking
            // In real implementation, use system-specific APIs
            return 0; // Placeholder
        }
    };
    
    void demonstrateProfilingBenchmarking() {
        std::cout << "=== Profiling and Benchmarking ===" << std::endl;
        
        BenchmarkRunner runner;
        
        // Benchmark different sorting algorithms
        std::vector<int> data(10000);
        std::iota(data.begin(), data.end(), 1);
        std::random_device rd;
        std::mt19937 g(rd());
        
        // Benchmark std::sort
        runner.run_benchmark("std::sort", [&data, &g] {
            std::shuffle(data.begin(), data.end(), g);
            std::sort(data.begin(), data.end());
        }, 100);
        
        // Benchmark parallel sort
        runner.run_benchmark("parallel sort", [&data, &g] {
            std::shuffle(data.begin(), data.end(), g);
            std::sort(std::execution::par, data.begin(), data.end());
        }, 100);
        
        // Benchmark stable_sort
        runner.run_benchmark("stable_sort", [&data, &g] {
            std::shuffle(data.begin(), data.end(), g);
            std::stable_sort(data.begin(), data.end());
        }, 100);
        
        // Print results
        runner.print_results();
        
        // Save results to file
        runner.save_results_to_file("benchmark_results.csv");
    }
}

// Example 2: Optimization Strategies
namespace OptimizationStrategies {
    
    // Loop optimization examples
    class LoopOptimization {
    public:
        // Unoptimized version
        static double sum_squares_unoptimized(const std::vector<double>& values) {
            double sum = 0.0;
            for (size_t i = 0; i < values.size(); ++i) {
                sum += values[i] * values[i];
            }
            return sum;
        }
        
        // Optimized version with range-based for loop
        static double sum_squares_optimized(const std::vector<double>& values) {
            double sum = 0.0;
            for (const auto& value : values) {
                sum += value * value;
            }
            return sum;
        }
        
        // Optimized version with std::accumulate
        static double sum_squares_accumulate(const std::vector<double>& values) {
            return std::accumulate(values.begin(), values.end(), 0.0,
                [](double sum, double value) { return sum + value * value; });
        }
        
        // Optimized version with parallel execution
        static double sum_squares_parallel(const std::vector<double>& values) {
            return std::transform_reduce(std::execution::par,
                values.begin(), values.end(), 0.0, std::plus<>(),
                [](double value) { return value * value; });
        }
    };
    
    // Function inlining optimization
    class InlineOptimization {
    public:
        // Non-inlined function
        static inline double square(double x) {
            return x * x;
        }
        
        // Inlined function
        static constexpr double square_constexpr(double x) {
            return x * x;
        }
        
        // Template function (automatically inlined)
        template<typename T>
        static constexpr T square_template(T x) {
            return x * x;
        }
    };
    
    // Branch prediction optimization
    class BranchPrediction {
    public:
        // Unoptimized version with unpredictable branches
        static int count_even_unoptimized(const std::vector<int>& values) {
            int count = 0;
            for (int value : values) {
                if (value % 2 == 0) {
                    count++;
                }
            }
            return count;
        }
        
        // Optimized version with sorted data
        static int count_even_optimized(const std::vector<int>& values) {
            int count = 0;
            for (int value : values) {
                if (value % 2 == 0) {
                    count++;
                }
            }
            return count;
        }
        
        // Branchless version
        static int count_even_branchless(const std::vector<int>& values) {
            int count = 0;
            for (int value : values) {
                count += (value % 2 == 0);
            }
            return count;
        }
    };
    
    // Memory access optimization
    class MemoryAccessOptimization {
    public:
        // Unoptimized version with random memory access
        static double sum_matrix_unoptimized(const std::vector<std::vector<double>>& matrix) {
            double sum = 0.0;
            for (size_t i = 0; i < matrix.size(); ++i) {
                for (size_t j = 0; j < matrix[i].size(); ++j) {
                    sum += matrix[i][j];
                }
            }
            return sum;
        }
        
        // Optimized version with cache-friendly access
        static double sum_matrix_optimized(const std::vector<std::vector<double>>& matrix) {
            double sum = 0.0;
            for (const auto& row : matrix) {
                for (double value : row) {
                    sum += value;
                }
            }
            return sum;
        }
        
        // Optimized version with contiguous memory
        static double sum_matrix_contiguous(const std::vector<double>& matrix, size_t rows, size_t cols) {
            double sum = 0.0;
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    sum += matrix[i * cols + j];
                }
            }
            return sum;
        }
    };
    
    void demonstrateOptimizationStrategies() {
        std::cout << "\n=== Optimization Strategies ===" << std::endl;
        
        // Test loop optimization
        std::vector<double> values(1000000);
        std::iota(values.begin(), values.end(), 1.0);
        
        HighResolutionTimer timer;
        
        // Test sum_squares_unoptimized
        timer.start();
        double result1 = LoopOptimization::sum_squares_unoptimized(values);
        timer.stop();
        std::cout << "Sum squares unoptimized: " << result1 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        // Test sum_squares_optimized
        timer.start();
        double result2 = LoopOptimization::sum_squares_optimized(values);
        timer.stop();
        std::cout << "Sum squares optimized: " << result2 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        // Test sum_squares_accumulate
        timer.start();
        double result3 = LoopOptimization::sum_squares_accumulate(values);
        timer.stop();
        std::cout << "Sum squares accumulate: " << result3 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        // Test sum_squares_parallel
        timer.start();
        double result4 = LoopOptimization::sum_squares_parallel(values);
        timer.stop();
        std::cout << "Sum squares parallel: " << result4 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        // Test branch prediction
        std::vector<int> numbers(1000000);
        std::iota(numbers.begin(), numbers.end(), 1);
        
        // Test count_even_unoptimized
        timer.start();
        int count1 = BranchPrediction::count_even_unoptimized(numbers);
        timer.stop();
        std::cout << "Count even unoptimized: " << count1 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        // Test count_even_branchless
        timer.start();
        int count2 = BranchPrediction::count_even_branchless(numbers);
        timer.stop();
        std::cout << "Count even branchless: " << count2 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
    }
}

// Example 3: Memory Optimization
namespace MemoryOptimization {
    
    // Memory pool for efficient allocation
    template<typename T>
    class MemoryPool {
    private:
        struct Block {
            alignas(T) char data[sizeof(T)];
            Block* next;
        };
        
        std::vector<std::unique_ptr<Block[]>> blocks_;
        Block* free_list_;
        size_t block_size_;
        size_t current_block_;
        size_t current_offset_;
        
    public:
        MemoryPool(size_t block_size = 1024) 
            : free_list_(nullptr), block_size_(block_size), current_block_(0), current_offset_(0) {
            allocate_new_block();
        }
        
        ~MemoryPool() {
            // Clean up all blocks
            for (auto& block : blocks_) {
                // Destruct objects in block
                for (size_t i = 0; i < block_size_; ++i) {
                    T* obj = reinterpret_cast<T*>(&block[i]);
                    if (obj) {
                        obj->~T();
                    }
                }
            }
        }
        
        template<typename... Args>
        T* allocate(Args&&... args) {
            // Try to get from free list first
            if (free_list_) {
                Block* block = free_list_;
                free_list_ = free_list_->next;
                return new (block->data) T(std::forward<Args>(args)...);
            }
            
            // Allocate from current block
            if (current_offset_ < block_size_) {
                T* obj = new (blocks_[current_block_][current_offset_].data) T(std::forward<Args>(args)...);
                current_offset_++;
                return obj;
            }
            
            // Allocate new block if needed
            allocate_new_block();
            T* obj = new (blocks_[current_block_][current_offset_].data) T(std::forward<Args>(args)...);
            current_offset_++;
            return obj;
        }
        
        void deallocate(T* obj) {
            if (obj) {
                obj->~T();
                Block* block = reinterpret_cast<Block*>(obj);
                block->next = free_list_;
                free_list_ = block;
            }
        }
        
    private:
        void allocate_new_block() {
            blocks_.emplace_back(std::make_unique<Block[]>(block_size_));
            current_block_ = blocks_.size() - 1;
            current_offset_ = 0;
        }
    };
    
    // Custom allocator for STL containers
    template<typename T>
    class CustomAllocator {
    private:
        MemoryPool<T>* pool_;
        
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        
        CustomAllocator(MemoryPool<T>* pool) : pool_(pool) {}
        
        template<typename U>
        CustomAllocator(const CustomAllocator<U>& other) : pool_(other.pool_) {}
        
        pointer allocate(size_type n) {
            if (n == 1) {
                return pool_->allocate();
            }
            return static_cast<pointer>(std::aligned_alloc(alignof(T), n * sizeof(T)));
        }
        
        void deallocate(pointer p, size_type n) {
            if (n == 1) {
                pool_->deallocate(p);
            } else {
                std::free(p);
            }
        }
        
        template<typename U>
        bool operator==(const CustomAllocator<U>& other) const {
            return pool_ == other.pool_;
        }
        
        template<typename U>
        bool operator!=(const CustomAllocator<U>& other) const {
            return !(*this == other);
        }
    };
    
    // Cache-friendly data structure
    template<typename T>
    class CacheFriendlyVector {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;
        
    public:
        CacheFriendlyVector() : data_(nullptr), size_(0), capacity_(0) {}
        
        ~CacheFriendlyVector() {
            if (data_) {
                std::free(data_);
            }
        }
        
        void push_back(const T& value) {
            if (size_ >= capacity_) {
                resize(capacity_ * 2 + 1);
            }
            data_[size_++] = value;
        }
        
        void resize(size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = static_cast<T*>(std::aligned_alloc(alignof(T), new_capacity * sizeof(T)));
                if (data_) {
                    std::memcpy(new_data, data_, size_ * sizeof(T));
                    std::free(data_);
                }
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }
        
        T& operator[](size_t index) {
            return data_[index];
        }
        
        const T& operator[](size_t index) const {
            return data_[index];
        }
        
        size_t size() const {
            return size_;
        }
        
        T* data() {
            return data_;
        }
        
        const T* data() const {
            return data_;
        }
    };
    
    void demonstrateMemoryOptimization() {
        std::cout << "\n=== Memory Optimization ===" << std::endl;
        
        // Test memory pool
        MemoryPool<int> pool(100);
        
        std::vector<int*> pointers;
        
        // Allocate objects from pool
        for (int i = 0; i < 50; ++i) {
            int* ptr = pool.allocate(i);
            pointers.push_back(ptr);
        }
        
        std::cout << "Allocated " << pointers.size() << " objects from memory pool" << std::endl;
        
        // Deallocate some objects
        for (size_t i = 0; i < pointers.size(); i += 2) {
            pool.deallocate(pointers[i]);
        }
        
        std::cout << "Deallocated half of the objects" << std::endl;
        
        // Test custom allocator
        MemoryPool<std::string> string_pool(100);
        CustomAllocator<std::string> allocator(&string_pool);
        
        std::vector<std::string, CustomAllocator<std::string>> custom_vector(allocator);
        
        for (int i = 0; i < 10; ++i) {
            custom_vector.emplace_back("String " + std::to_string(i));
        }
        
        std::cout << "Created vector with custom allocator: " << custom_vector.size() << " elements" << std::endl;
        
        // Test cache-friendly vector
        CacheFriendlyVector<int> cache_vector;
        
        for (int i = 0; i < 1000; ++i) {
            cache_vector.push_back(i);
        }
        
        std::cout << "Cache-friendly vector size: " << cache_vector.size() << std::endl;
        
        // Test cache performance
        HighResolutionTimer timer;
        
        // Test cache-friendly access
        timer.start();
        int sum1 = 0;
        for (size_t i = 0; i < cache_vector.size(); ++i) {
            sum1 += cache_vector[i];
        }
        timer.stop();
        std::cout << "Cache-friendly access sum: " << sum1 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
    }
}

// Example 4: Cache Optimization
namespace CacheOptimization {
    
    // Cache line size (typically 64 bytes)
    constexpr size_t CACHE_LINE_SIZE = 64;
    
    // Cache-friendly matrix multiplication
    class CacheFriendlyMatrix {
    private:
        std::vector<double> data_;
        size_t rows_, cols_;
        
    public:
        CacheFriendlyMatrix(size_t rows, size_t cols) 
            : data_(rows * cols), rows_(rows), cols_(cols) {}
        
        double& operator()(size_t row, size_t col) {
            return data_[row * cols_ + col];
        }
        
        const double& operator()(size_t row, size_t col) const {
            return data_[row * cols_ + col];
        }
        
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }
        
        // Cache-friendly matrix multiplication
        CacheFriendlyMatrix multiply(const CacheFriendlyMatrix& other) const {
            assert(cols_ == other.rows_);
            
            CacheFriendlyMatrix result(rows_, other.cols_);
            
            // Block size for cache optimization
            constexpr size_t BLOCK_SIZE = 64;
            
            for (size_t i = 0; i < rows_; i += BLOCK_SIZE) {
                for (size_t j = 0; j < other.cols_; j += BLOCK_SIZE) {
                    for (size_t k = 0; k < cols_; k += BLOCK_SIZE) {
                        // Multiply block
                        for (size_t ii = i; ii < std::min(i + BLOCK_SIZE, rows_); ++ii) {
                            for (size_t jj = j; jj < std::min(j + BLOCK_SIZE, other.cols_); ++jj) {
                                double sum = 0.0;
                                for (size_t kk = k; kk < std::min(k + BLOCK_SIZE, cols_); ++kk) {
                                    sum += (*this)(ii, kk) * other(kk, jj);
                                }
                                result(ii, jj) += sum;
                            }
                        }
                    }
                }
            }
            
            return result;
        }
    };
    
    // Cache prefetching
    class CachePrefetch {
    public:
        static void prefetch_read(const void* addr) {
            __builtin_prefetch(addr, 0, 3); // Read, high temporal locality
        }
        
        static void prefetch_write(const void* addr) {
            __builtin_prefetch(addr, 1, 3); // Write, high temporal locality
        }
        
        // Optimized sum with prefetching
        static double sum_with_prefetch(const std::vector<double>& values) {
            double sum = 0.0;
            const size_t prefetch_distance = 8;
            
            for (size_t i = 0; i < values.size(); ++i) {
                // Prefetch future elements
                if (i + prefetch_distance < values.size()) {
                    prefetch_read(&values[i + prefetch_distance]);
                }
                
                sum += values[i];
            }
            
            return sum;
        }
    };
    
    // Data structure alignment
    struct alignas(CACHE_LINE_SIZE) CacheAlignedData {
        std::atomic<int> counter;
        char padding[CACHE_LINE_SIZE - sizeof(std::atomic<int>)];
    };
    
    // False sharing prevention
    class FalseSharingPrevention {
    private:
        std::array<CacheAlignedData, 4> data_;
        
    public:
        void increment_counter(size_t index) {
            data_[index].counter.fetch_add(1);
        }
        
        int get_counter(size_t index) const {
            return data_[index].counter.load();
        }
    };
    
    void demonstrateCacheOptimization() {
        std::cout << "\n=== Cache Optimization ===" << std::endl;
        
        // Test cache-friendly matrix multiplication
        constexpr size_t MATRIX_SIZE = 512;
        CacheFriendlyMatrix matrix1(MATRIX_SIZE, MATRIX_SIZE);
        CacheFriendlyMatrix matrix2(MATRIX_SIZE, MATRIX_SIZE);
        
        // Initialize matrices
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        
        for (size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (size_t j = 0; j < MATRIX_SIZE; ++j) {
                matrix1(i, j) = dis(gen);
                matrix2(i, j) = dis(gen);
            }
        }
        
        HighResolutionTimer timer;
        
        // Test matrix multiplication
        timer.start();
        auto result = matrix1.multiply(matrix2);
        timer.stop();
        
        std::cout << "Matrix multiplication (" << MATRIX_SIZE << "x" << MATRIX_SIZE 
                  << ") completed in " << timer.elapsed_seconds() << "s" << std::endl;
        
        // Test cache prefetching
        std::vector<double> values(1000000);
        std::iota(values.begin(), values.end(), 1.0);
        
        timer.start();
        double sum1 = std::accumulate(values.begin(), values.end(), 0.0);
        timer.stop();
        std::cout << "Standard sum: " << sum1 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        timer.start();
        double sum2 = CachePrefetch::sum_with_prefetch(values);
        timer.stop();
        std::cout << "Prefetch sum: " << sum2 
                  << " (Time: " << timer.elapsed_seconds() << "s)" << std::endl;
        
        // Test false sharing prevention
        FalseSharingPrevention prevention;
        
        std::vector<std::thread> threads;
        
        timer.start();
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&prevention, i] {
                for (int j = 0; j < 1000000; ++j) {
                    prevention.increment_counter(i);
                }
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        timer.stop();
        
        std::cout << "False sharing prevention test completed in " 
                  << timer.elapsed_seconds() << "s" << std::endl;
        
        for (int i = 0; i < 4; ++i) {
            std::cout << "Counter " << i << ": " << prevention.get_counter(i) << std::endl;
        }
    }
}

// Example 5: Performance Monitoring
namespace PerformanceMonitoring {
    
    // Performance metrics collector
    class PerformanceMetrics {
    private:
        struct Metric {
            std::string name;
            double value;
            std::chrono::steady_clock::time_point timestamp;
        };
        
        std::vector<Metric> metrics_;
        std::mutex metrics_mutex_;
        
    public:
        void record_metric(const std::string& name, double value) {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            metrics_.push_back({name, value, std::chrono::steady_clock::now()});
        }
        
        void print_metrics() {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            
            std::cout << "\n=== Performance Metrics ===" << std::endl;
            std::cout << std::setw(20) << "Metric" 
                      << std::setw(15) << "Value" 
                      << std::setw(25) << "Timestamp" << std::endl;
            std::cout << std::string(60, '-') << std::endl;
            
            for (const auto& metric : metrics_) {
                auto time_t = std::chrono::system_clock::to_time_t(
                    std::chrono::system_clock::now());
                std::cout << std::setw(20) << metric.name
                          << std::setw(15) << std::fixed << std::setprecision(2) << metric.value
                          << std::setw(25) << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S")
                          << std::endl;
            }
        }
        
        void save_metrics_to_file(const std::string& filename) {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            
            std::ofstream file(filename);
            if (file.is_open()) {
                file << "Metric,Value,Timestamp\n";
                for (const auto& metric : metrics_) {
                    file << metric.name << "," << metric.value << "," 
                         << std::chrono::duration_cast<std::chrono::milliseconds>(
                             metric.timestamp.time_since_epoch()).count() << "\n";
                }
                file.close();
                std::cout << "Metrics saved to " << filename << std::endl;
            }
        }
    };
    
    // Performance profiler
    class PerformanceProfiler {
    private:
        struct ProfileData {
            std::string function_name;
            double total_time;
            size_t call_count;
            double min_time;
            double max_time;
        };
        
        std::unordered_map<std::string, ProfileData> profiles_;
        std::mutex profiles_mutex_;
        
    public:
        class ScopedTimer {
        private:
            PerformanceProfiler* profiler_;
            std::string function_name_;
            std::chrono::high_resolution_clock::time_point start_time_;
            
        public:
            ScopedTimer(PerformanceProfiler* profiler, const std::string& function_name)
                : profiler_(profiler), function_name_(function_name) {
                start_time_ = std::chrono::high_resolution_clock::now();
            }
            
            ~ScopedTimer() {
                auto end_time = std::chrono::high_resolution_clock::now();
                double duration = std::chrono::duration<double>(end_time - start_time_).count();
                profiler_->record_function_call(function_name_, duration);
            }
        };
        
        void record_function_call(const std::string& function_name, double duration) {
            std::lock_guard<std::mutex> lock(profiles_mutex_);
            
            auto& profile = profiles_[function_name];
            profile.function_name = function_name;
            profile.total_time += duration;
            profile.call_count++;
            profile.min_time = std::min(profile.min_time, duration);
            profile.max_time = std::max(profile.max_time, duration);
        }
        
        void print_profiles() {
            std::lock_guard<std::mutex> lock(profiles_mutex_);
            
            std::cout << "\n=== Performance Profiles ===" << std::endl;
            std::cout << std::setw(20) << "Function" 
                      << std::setw(15) << "Total Time (s)" 
                      << std::setw(10) << "Calls" 
                      << std::setw(15) << "Avg Time (s)" 
                      << std::setw(15) << "Min Time (s)" 
                      << std::setw(15) << "Max Time (s)" << std::endl;
            std::cout << std::string(90, '-') << std::endl;
            
            for (const auto& [name, profile] : profiles_) {
                double avg_time = profile.total_time / profile.call_count;
                std::cout << std::setw(20) << profile.function_name
                          << std::setw(15) << std::fixed << std::setprecision(6) << profile.total_time
                          << std::setw(10) << profile.call_count
                          << std::setw(15) << std::fixed << std::setprecision(6) << avg_time
                          << std::setw(15) << std::fixed << std::setprecision(6) << profile.min_time
                          << std::setw(15) << std::fixed << std::setprecision(6) << profile.max_time
                          << std::endl;
            }
        }
    };
    
    // Global performance monitoring
    PerformanceMetrics g_metrics;
    PerformanceProfiler g_profiler;
    
    void demonstratePerformanceMonitoring() {
        std::cout << "\n=== Performance Monitoring ===" << std::endl;
        
        // Record some metrics
        g_metrics.record_metric("CPU Usage", 45.2);
        g_metrics.record_metric("Memory Usage", 128.5);
        g_metrics.record_metric("Network I/O", 1024.0);
        g_metrics.record_metric("Disk I/O", 512.0);
        
        // Profile some functions
        {
            PerformanceProfiler::ScopedTimer timer(&g_profiler, "function1");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        {
            PerformanceProfiler::ScopedTimer timer(&g_profiler, "function2");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        {
            PerformanceProfiler::ScopedTimer timer(&g_profiler, "function1");
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
        
        // Print results
        g_metrics.print_metrics();
        g_profiler.print_profiles();
        
        // Save to files
        g_metrics.save_metrics_to_file("performance_metrics.csv");
    }
}

int main() {
    std::cout << "=== Advanced Performance Engineering Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced performance engineering techniques including\n"
              << "profiling, benchmarking, optimization strategies, memory optimization,\n"
              << "cache optimization, and performance monitoring.\n" << std::endl;
    
    // Demonstrate various performance engineering techniques
    ProfilingBenchmarking::demonstrateProfilingBenchmarking();
    OptimizationStrategies::demonstrateOptimizationStrategies();
    MemoryOptimization::demonstrateMemoryOptimization();
    CacheOptimization::demonstrateCacheOptimization();
    PerformanceMonitoring::demonstratePerformanceMonitoring();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Profiling and benchmarking are essential for performance optimization" << std::endl;
    std::cout << "2. Optimization strategies include loop optimization and branch prediction" << std::endl;
    std::cout << "3. Memory optimization reduces allocation overhead and improves cache usage" << std::endl;
    std::cout << "4. Cache optimization improves memory access patterns and reduces cache misses" << std::endl;
    std::cout << "5. Performance monitoring enables continuous optimization and problem detection" << std::endl;
    std::cout << "6. Modern C++ provides tools for high-performance programming" << std::endl;
    std::cout << "7. Understanding hardware characteristics is crucial for optimization" << std::endl;
    std::cout << "8. Performance engineering is an iterative process of measurement and optimization" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC (C++20):
 * g++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_performance 03_Advanced_Performance_Engineering.cpp
 * 
 * Using Clang (C++20):
 * clang++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_performance 03_Advanced_Performance_Engineering.cpp
 * 
 * Using MSVC (Visual Studio 2019+):
 * cl /std:c++20 /EHsc /O2 03_Advanced_Performance_Engineering.cpp
 * 
 * Running:
 * ./advanced_performance (Linux/macOS)
 * advanced_performance.exe (Windows)
 * 
 * Note: This lesson requires C++20 for some features.
 * C++17 is the minimum required version for most features.
 * 
 * Advanced Performance Engineering Notes:
 * - Profiling and benchmarking are essential for performance optimization
 * - Optimization strategies include loop optimization and branch prediction
 * - Memory optimization reduces allocation overhead and improves cache usage
 * - Cache optimization improves memory access patterns and reduces cache misses
 * - Performance monitoring enables continuous optimization and problem detection
 * - Modern C++ provides tools for high-performance programming
 * - Understanding hardware characteristics is crucial for optimization
 * - Performance engineering is an iterative process of measurement and optimization
 */"""
