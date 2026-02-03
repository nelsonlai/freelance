/*
 * Lesson 19.2: Advanced Performance Engineering
 * 
 * This file demonstrates advanced performance engineering techniques including
 * profiling, benchmarking, performance analysis, optimization strategies,
 * and performance monitoring.
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
#include <fstream>
#include <iomanip>
#include <cmath>

// Example 1: High-Resolution Timing and Profiling
namespace Profiling {
    
    // High-resolution timer
    class HighResolutionTimer {
    private:
        std::chrono::high_resolution_clock::time_point start_time_;
        
    public:
        void start() {
            start_time_ = std::chrono::high_resolution_clock::now();
        }
        
        double elapsed_seconds() const {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time_);
            return duration.count() / 1e9;
        }
        
        long long elapsed_nanoseconds() const {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time_);
            return duration.count();
        }
        
        double elapsed_microseconds() const {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_);
            return duration.count();
        }
        
        double elapsed_milliseconds() const {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_);
            return duration.count();
        }
    };
    
    // RAII profiler
    class Profiler {
    private:
        std::string name_;
        HighResolutionTimer timer_;
        bool active_;
        
    public:
        Profiler(const std::string& name) : name_(name), active_(false) {
            start();
        }
        
        ~Profiler() {
            if (active_) {
                stop();
            }
        }
        
        void start() {
            if (!active_) {
                timer_.start();
                active_ = true;
            }
        }
        
        void stop() {
            if (active_) {
                double elapsed = timer_.elapsed_seconds();
                std::cout << "[" << name_ << "] Elapsed: " << elapsed << " seconds" << std::endl;
                active_ = false;
            }
        }
        
        double get_elapsed() const {
            return timer_.elapsed_seconds();
        }
        
        bool is_active() const {
            return active_;
        }
    };
    
    // Performance counter
    class PerformanceCounter {
    private:
        std::string name_;
        std::atomic<long long> count_;
        std::atomic<long long> total_time_;
        std::atomic<long long> min_time_;
        std::atomic<long long> max_time_;
        
    public:
        PerformanceCounter(const std::string& name) 
            : name_(name), count_(0), total_time_(0), min_time_(LLONG_MAX), max_time_(0) {}
        
        void add_measurement(long long time_ns) {
            count_.fetch_add(1);
            total_time_.fetch_add(time_ns);
            
            long long current_min = min_time_.load();
            while (time_ns < current_min && !min_time_.compare_exchange_weak(current_min, time_ns)) {
                // Retry
            }
            
            long long current_max = max_time_.load();
            while (time_ns > current_max && !max_time_.compare_exchange_weak(current_max, time_ns)) {
                // Retry
            }
        }
        
        double get_average_time_ns() const {
            long long count = count_.load();
            if (count == 0) return 0.0;
            return static_cast<double>(total_time_.load()) / count;
        }
        
        long long get_total_count() const {
            return count_.load();
        }
        
        long long get_total_time_ns() const {
            return total_time_.load();
        }
        
        long long get_min_time_ns() const {
            long long min = min_time_.load();
            return min == LLONG_MAX ? 0 : min;
        }
        
        long long get_max_time_ns() const {
            return max_time_.load();
        }
        
        void reset() {
            count_.store(0);
            total_time_.store(0);
            min_time_.store(LLONG_MAX);
            max_time_.store(0);
        }
        
        void print_stats() const {
            long long count = count_.load();
            if (count == 0) {
                std::cout << "[" << name_ << "] No measurements" << std::endl;
                return;
            }
            
            double avg_ns = get_average_time_ns();
            long long min_ns = get_min_time_ns();
            long long max_ns = get_max_time_ns();
            long long total_ns = get_total_time_ns();
            
            std::cout << "[" << name_ << "] Statistics:" << std::endl;
            std::cout << "  Count: " << count << std::endl;
            std::cout << "  Total time: " << total_ns / 1e9 << " seconds" << std::endl;
            std::cout << "  Average time: " << avg_ns / 1e6 << " ms" << std::endl;
            std::cout << "  Min time: " << min_ns / 1e6 << " ms" << std::endl;
            std::cout << "  Max time: " << max_ns / 1e6 << " ms" << std::endl;
        }
    };
    
    // Global performance counter registry
    class PerformanceCounterRegistry {
    private:
        std::map<std::string, std::unique_ptr<PerformanceCounter>> counters_;
        std::mutex mutex_;
        
    public:
        static PerformanceCounterRegistry& get_instance() {
            static PerformanceCounterRegistry instance;
            return instance;
        }
        
        PerformanceCounter& get_counter(const std::string& name) {
            std::lock_guard<std::mutex> lock(mutex_);
            
            auto it = counters_.find(name);
            if (it == counters_.end()) {
                counters_[name] = std::make_unique<PerformanceCounter>(name);
                return *counters_[name];
            }
            
            return *it->second;
        }
        
        void print_all_stats() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            std::cout << "\n=== Performance Counter Statistics ===" << std::endl;
            for (const auto& [name, counter] : counters_) {
                counter->print_stats();
                std::cout << std::endl;
            }
        }
        
        void reset_all() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            for (const auto& [name, counter] : counters_) {
                counter->reset();
            }
        }
    };
    
    // RAII performance measurement
    class PerformanceMeasurement {
    private:
        PerformanceCounter& counter_;
        HighResolutionTimer timer_;
        
    public:
        PerformanceMeasurement(const std::string& counter_name) 
            : counter_(PerformanceCounterRegistry::get_instance().get_counter(counter_name)) {
            timer_.start();
        }
        
        ~PerformanceMeasurement() {
            long long elapsed_ns = timer_.elapsed_nanoseconds();
            counter_.add_measurement(elapsed_ns);
        }
    };
    
    void demonstrateProfiling() {
        std::cout << "=== Profiling ===" << std::endl;
        
        // Test high-resolution timer
        HighResolutionTimer timer;
        timer.start();
        
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::cout << "Elapsed time: " << timer.elapsed_milliseconds() << " ms" << std::endl;
        
        // Test profiler
        {
            Profiler profiler("Test Operation");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        // Test performance counter
        PerformanceCounter counter("Test Counter");
        
        for (int i = 0; i < 10; ++i) {
            {
                PerformanceMeasurement measurement("Test Counter");
                std::this_thread::sleep_for(std::chrono::milliseconds(10 + i));
            }
        }
        
        counter.print_stats();
        
        // Test global registry
        PerformanceCounterRegistry::get_instance().print_all_stats();
    }
}

// Example 2: Benchmarking Framework
namespace Benchmarking {
    
    // Benchmark result
    struct BenchmarkResult {
        std::string name;
        double min_time;
        double max_time;
        double avg_time;
        double median_time;
        double std_dev;
        size_t iterations;
        bool success;
        
        BenchmarkResult(const std::string& name, size_t iterations, bool success)
            : name(name), min_time(0), max_time(0), avg_time(0), median_time(0), std_dev(0), 
              iterations(iterations), success(success) {}
    };
    
    // Benchmark framework
    class BenchmarkFramework {
    private:
        std::vector<BenchmarkResult> results_;
        
    public:
        // Run benchmark
        template<typename Func>
        BenchmarkResult run_benchmark(const std::string& name, Func func, size_t iterations = 1000) {
            std::cout << "Running benchmark: " << name << " (" << iterations << " iterations)" << std::endl;
            
            std::vector<double> times;
            times.reserve(iterations);
            
            bool success = true;
            
            try {
                for (size_t i = 0; i < iterations; ++i) {
                    Profiling::HighResolutionTimer timer;
                    timer.start();
                    
                    func();
                    
                    double elapsed = timer.elapsed_seconds();
                    times.push_back(elapsed);
                }
            } catch (const std::exception& e) {
                std::cout << "Benchmark failed: " << e.what() << std::endl;
                success = false;
            }
            
            if (!success || times.empty()) {
                return BenchmarkResult(name, iterations, false);
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
            variance /= times.size();
            double std_dev = std::sqrt(variance);
            
            BenchmarkResult result(name, iterations, true);
            result.min_time = min_time;
            result.max_time = max_time;
            result.avg_time = avg_time;
            result.median_time = median_time;
            result.std_dev = std_dev;
            
            results_.push_back(result);
            return result;
        }
        
        // Print all results
        void print_results() {
            std::cout << "\n=== Benchmark Results ===" << std::endl;
            
            for (const auto& result : results_) {
                if (!result.success) {
                    std::cout << "[" << result.name << "] FAILED" << std::endl;
                    continue;
                }
                
                std::cout << "[" << result.name << "] Results:" << std::endl;
                std::cout << "  Iterations: " << result.iterations << std::endl;
                std::cout << "  Min time: " << result.min_time * 1e6 << " μs" << std::endl;
                std::cout << "  Max time: " << result.max_time * 1e6 << " μs" << std::endl;
                std::cout << "  Avg time: " << result.avg_time * 1e6 << " μs" << std::endl;
                std::cout << "  Median time: " << result.median_time * 1e6 << " μs" << std::endl;
                std::cout << "  Std dev: " << result.std_dev * 1e6 << " μs" << std::endl;
                std::cout << std::endl;
            }
        }
        
        // Export results to CSV
        void export_csv(const std::string& filename) {
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cout << "Failed to open file: " << filename << std::endl;
                return;
            }
            
            file << "Name,Iterations,Min Time (μs),Max Time (μs),Avg Time (μs),Median Time (μs),Std Dev (μs)" << std::endl;
            
            for (const auto& result : results_) {
                if (result.success) {
                    file << result.name << "," << result.iterations << ","
                         << result.min_time * 1e6 << "," << result.max_time * 1e6 << ","
                         << result.avg_time * 1e6 << "," << result.median_time * 1e6 << ","
                         << result.std_dev * 1e6 << std::endl;
                }
            }
            
            file.close();
            std::cout << "Results exported to: " << filename << std::endl;
        }
        
        // Clear results
        void clear_results() {
            results_.clear();
        }
    };
    
    void demonstrateBenchmarking() {
        std::cout << "\n=== Benchmarking ===" << std::endl;
        
        BenchmarkFramework framework;
        
        // Benchmark vector operations
        framework.run_benchmark("Vector Push Back", []() {
            std::vector<int> vec;
            for (int i = 0; i < 1000; ++i) {
                vec.push_back(i);
            }
        }, 1000);
        
        framework.run_benchmark("Vector Reserve Push Back", []() {
            std::vector<int> vec;
            vec.reserve(1000);
            for (int i = 0; i < 1000; ++i) {
                vec.push_back(i);
            }
        }, 1000);
        
        // Benchmark map operations
        framework.run_benchmark("Map Insert", []() {
            std::map<int, int> map;
            for (int i = 0; i < 1000; ++i) {
                map[i] = i * 2;
            }
        }, 100);
        
        framework.run_benchmark("Unordered Map Insert", []() {
            std::unordered_map<int, int> map;
            for (int i = 0; i < 1000; ++i) {
                map[i] = i * 2;
            }
        }, 100);
        
        // Benchmark string operations
        framework.run_benchmark("String Concatenation", []() {
            std::string str;
            for (int i = 0; i < 100; ++i) {
                str += "test";
            }
        }, 1000);
        
        framework.run_benchmark("String Stream", []() {
            std::stringstream ss;
            for (int i = 0; i < 100; ++i) {
                ss << "test";
            }
            std::string str = ss.str();
        }, 1000);
        
        // Print results
        framework.print_results();
        
        // Export to CSV
        framework.export_csv("benchmark_results.csv");
    }
}

// Example 3: Performance Analysis
namespace PerformanceAnalysis {
    
    // Performance analyzer
    class PerformanceAnalyzer {
    private:
        struct Measurement {
            std::string name;
            double time;
            std::chrono::steady_clock::time_point timestamp;
            
            Measurement(const std::string& name, double time) 
                : name(name), time(time), timestamp(std::chrono::steady_clock::now()) {}
        };
        
        std::vector<Measurement> measurements_;
        std::mutex measurements_mutex_;
        
    public:
        // Add measurement
        void add_measurement(const std::string& name, double time) {
            std::lock_guard<std::mutex> lock(measurements_mutex_);
            measurements_.emplace_back(name, time);
        }
        
        // Analyze measurements
        void analyze() {
            std::lock_guard<std::mutex> lock(measurements_mutex_);
            
            if (measurements_.empty()) {
                std::cout << "No measurements to analyze" << std::endl;
                return;
            }
            
            // Group measurements by name
            std::map<std::string, std::vector<double>> grouped_measurements;
            for (const auto& measurement : measurements_) {
                grouped_measurements[measurement.name].push_back(measurement.time);
            }
            
            std::cout << "\n=== Performance Analysis ===" << std::endl;
            
            for (const auto& [name, times] : grouped_measurements) {
                analyze_function(name, times);
            }
        }
        
        // Clear measurements
        void clear() {
            std::lock_guard<std::mutex> lock(measurements_mutex_);
            measurements_.clear();
        }
        
    private:
        void analyze_function(const std::string& name, const std::vector<double>& times) {
            if (times.empty()) return;
            
            std::vector<double> sorted_times = times;
            std::sort(sorted_times.begin(), sorted_times.end());
            
            double min_time = sorted_times.front();
            double max_time = sorted_times.back();
            double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
            double median_time = sorted_times[sorted_times.size() / 2];
            
            // Calculate percentiles
            double p90 = sorted_times[static_cast<size_t>(times.size() * 0.9)];
            double p95 = sorted_times[static_cast<size_t>(times.size() * 0.95)];
            double p99 = sorted_times[static_cast<size_t>(times.size() * 0.99)];
            
            // Calculate standard deviation
            double variance = 0.0;
            for (double time : times) {
                variance += (time - avg_time) * (time - avg_time);
            }
            variance /= times.size();
            double std_dev = std::sqrt(variance);
            
            std::cout << "[" << name << "] Analysis:" << std::endl;
            std::cout << "  Samples: " << times.size() << std::endl;
            std::cout << "  Min: " << min_time * 1e6 << " μs" << std::endl;
            std::cout << "  Max: " << max_time * 1e6 << " μs" << std::endl;
            std::cout << "  Avg: " << avg_time * 1e6 << " μs" << std::endl;
            std::cout << "  Median: " << median_time * 1e6 << " μs" << std::endl;
            std::cout << "  P90: " << p90 * 1e6 << " μs" << std::endl;
            std::cout << "  P95: " << p95 * 1e6 << " μs" << std::endl;
            std::cout << "  P99: " << p99 * 1e6 << " μs" << std::endl;
            std::cout << "  Std Dev: " << std_dev * 1e6 << " μs" << std::endl;
            std::cout << std::endl;
        }
    };
    
    // Global performance analyzer
    class GlobalPerformanceAnalyzer {
    private:
        static PerformanceAnalyzer instance_;
        
    public:
        static PerformanceAnalyzer& get_instance() {
            return instance_;
        }
    };
    
    PerformanceAnalyzer GlobalPerformanceAnalyzer::instance_;
    
    // RAII performance measurement
    class PerformanceMeasurement {
    private:
        std::string name_;
        Profiling::HighResolutionTimer timer_;
        
    public:
        PerformanceMeasurement(const std::string& name) : name_(name) {
            timer_.start();
        }
        
        ~PerformanceMeasurement() {
            double elapsed = timer_.elapsed_seconds();
            GlobalPerformanceAnalyzer::get_instance().add_measurement(name_, elapsed);
        }
    };
    
    void demonstratePerformanceAnalysis() {
        std::cout << "\n=== Performance Analysis ===" << std::endl;
        
        // Simulate some operations with measurements
        for (int i = 0; i < 100; ++i) {
            {
                PerformanceMeasurement measurement("Fast Operation");
                std::this_thread::sleep_for(std::chrono::microseconds(100));
            }
            
            {
                PerformanceMeasurement measurement("Slow Operation");
                std::this_thread::sleep_for(std::chrono::microseconds(500));
            }
        }
        
        // Analyze measurements
        GlobalPerformanceAnalyzer::get_instance().analyze();
    }
}

// Example 4: Optimization Strategies
namespace OptimizationStrategies {
    
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
            delete[] data_;
        }
        
        // Non-copyable
        CacheFriendlyVector(const CacheFriendlyVector&) = delete;
        CacheFriendlyVector& operator=(const CacheFriendlyVector&) = delete;
        
        // Movable
        CacheFriendlyVector(CacheFriendlyVector&& other) noexcept 
            : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        
        CacheFriendlyVector& operator=(CacheFriendlyVector&& other) noexcept {
            if (this != &other) {
                delete[] data_;
                data_ = other.data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                other.data_ = nullptr;
                other.size_ = 0;
                other.capacity_ = 0;
            }
            return *this;
        }
        
        void push_back(const T& value) {
            if (size_ >= capacity_) {
                reserve(capacity_ * 2 + 1);
            }
            data_[size_++] = value;
        }
        
        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = new T[new_capacity];
                for (size_t i = 0; i < size_; ++i) {
                    new_data[i] = std::move(data_[i]);
                }
                delete[] data_;
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
        
        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }
        
        T* data() { return data_; }
        const T* data() const { return data_; }
    };
    
    // Optimized matrix multiplication
    template<typename T>
    class OptimizedMatrix {
    private:
        std::vector<T> data_;
        size_t rows_, cols_;
        
    public:
        OptimizedMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
            data_.resize(rows * cols);
        }
        
        T& operator()(size_t row, size_t col) {
            return data_[row * cols_ + col];
        }
        
        const T& operator()(size_t row, size_t col) const {
            return data_[row * cols_ + col];
        }
        
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }
        
        // Cache-optimized matrix multiplication
        OptimizedMatrix multiply(const OptimizedMatrix& other, size_t block_size = 64) const {
            assert(cols_ == other.rows());
            
            OptimizedMatrix result(rows_, other.cols());
            
            size_t n = rows_;
            size_t m = cols_;
            size_t p = other.cols();
            
            // Blocked matrix multiplication for cache optimization
            for (size_t ii = 0; ii < n; ii += block_size) {
                for (size_t jj = 0; jj < p; jj += block_size) {
                    for (size_t kk = 0; kk < m; kk += block_size) {
                        // Process block
                        size_t i_end = std::min(ii + block_size, n);
                        size_t j_end = std::min(jj + block_size, p);
                        size_t k_end = std::min(kk + block_size, m);
                        
                        for (size_t i = ii; i < i_end; ++i) {
                            for (size_t j = jj; j < j_end; ++j) {
                                T sum = T{};
                                for (size_t k = kk; k < k_end; ++k) {
                                    sum += (*this)(i, k) * other(k, j);
                                }
                                result(i, j) += sum;
                            }
                        }
                    }
                }
            }
            
            return result;
        }
    };
    
    // Memory pool for frequent allocations
    template<typename T>
    class MemoryPool {
    private:
        struct Block {
            alignas(T) char data[sizeof(T)];
            Block* next;
        };
        
        Block* free_list_;
        std::vector<std::unique_ptr<Block[]>> blocks_;
        size_t block_size_;
        size_t current_block_;
        size_t current_offset_;
        
    public:
        MemoryPool(size_t block_size = 1024) 
            : free_list_(nullptr), block_size_(block_size), current_block_(0), current_offset_(0) {
            allocate_block();
        }
        
        T* allocate() {
            if (free_list_) {
                Block* block = free_list_;
                free_list_ = block->next;
                return reinterpret_cast<T*>(block->data);
            }
            
            if (current_offset_ >= block_size_) {
                allocate_block();
            }
            
            Block* block = &blocks_[current_block_][current_offset_];
            ++current_offset_;
            return reinterpret_cast<T*>(block->data);
        }
        
        void deallocate(T* ptr) {
            if (!ptr) return;
            
            Block* block = reinterpret_cast<Block*>(ptr);
            block->next = free_list_;
            free_list_ = block;
        }
        
    private:
        void allocate_block() {
            blocks_.emplace_back(std::make_unique<Block[]>(block_size_));
            current_block_ = blocks_.size() - 1;
            current_offset_ = 0;
        }
    };
    
    // RAII wrapper for pool-allocated objects
    template<typename T>
    class PoolPtr {
    private:
        T* ptr_;
        MemoryPool<T>* pool_;
        
    public:
        PoolPtr() : ptr_(nullptr), pool_(nullptr) {}
        
        explicit PoolPtr(T* ptr, MemoryPool<T>* pool) : ptr_(ptr), pool_(pool) {}
        
        ~PoolPtr() {
            if (ptr_ && pool_) {
                ptr_->~T();
                pool_->deallocate(ptr_);
            }
        }
        
        // Non-copyable
        PoolPtr(const PoolPtr&) = delete;
        PoolPtr& operator=(const PoolPtr&) = delete;
        
        // Movable
        PoolPtr(PoolPtr&& other) noexcept : ptr_(other.ptr_), pool_(other.pool_) {
            other.ptr_ = nullptr;
            other.pool_ = nullptr;
        }
        
        PoolPtr& operator=(PoolPtr&& other) noexcept {
            if (this != &other) {
                if (ptr_ && pool_) {
                    ptr_->~T();
                    pool_->deallocate(ptr_);
                }
                ptr_ = other.ptr_;
                pool_ = other.pool_;
                other.ptr_ = nullptr;
                other.pool_ = nullptr;
            }
            return *this;
        }
        
        T* get() const { return ptr_; }
        T& operator*() const { return *ptr_; }
        T* operator->() const { return ptr_; }
        
        explicit operator bool() const { return ptr_ != nullptr; }
    };
    
    template<typename T, typename... Args>
    PoolPtr<T> make_pool_ptr(MemoryPool<T>& pool, Args&&... args) {
        T* ptr = pool.allocate();
        new(ptr) T(std::forward<Args>(args)...);
        return PoolPtr<T>(ptr, &pool);
    }
    
    void demonstrateOptimizationStrategies() {
        std::cout << "\n=== Optimization Strategies ===" << std::endl;
        
        // Test cache-friendly vector
        CacheFriendlyVector<int> cache_friendly_vec;
        for (int i = 0; i < 1000; ++i) {
            cache_friendly_vec.push_back(i);
        }
        
        std::cout << "Cache-friendly vector size: " << cache_friendly_vec.size() << std::endl;
        std::cout << "Cache-friendly vector capacity: " << cache_friendly_vec.capacity() << std::endl;
        
        // Test optimized matrix multiplication
        OptimizedMatrix<double> matrix1(100, 100);
        OptimizedMatrix<double> matrix2(100, 100);
        
        // Initialize matrices
        for (size_t i = 0; i < 100; ++i) {
            for (size_t j = 0; j < 100; ++j) {
                matrix1(i, j) = i + j;
                matrix2(i, j) = i - j;
            }
        }
        
        // Test matrix multiplication
        auto result = matrix1.multiply(matrix2);
        std::cout << "Matrix multiplication result size: " << result.rows() << "x" << result.cols() << std::endl;
        
        // Test memory pool
        MemoryPool<int> int_pool;
        
        std::vector<PoolPtr<int>> ptrs;
        for (int i = 0; i < 100; ++i) {
            ptrs.push_back(make_pool_ptr(int_pool, i));
        }
        
        std::cout << "Memory pool allocated " << ptrs.size() << " integers" << std::endl;
        
        // Test performance with and without optimizations
        Benchmarking::BenchmarkFramework framework;
        
        framework.run_benchmark("Standard Vector", []() {
            std::vector<int> vec;
            for (int i = 0; i < 1000; ++i) {
                vec.push_back(i);
            }
        }, 1000);
        
        framework.run_benchmark("Cache-Friendly Vector", []() {
            CacheFriendlyVector<int> vec;
            for (int i = 0; i < 1000; ++i) {
                vec.push_back(i);
            }
        }, 1000);
        
        framework.print_results();
    }
}

// Example 5: Performance Monitoring
namespace PerformanceMonitoring {
    
    // Performance monitor
    class PerformanceMonitor {
    private:
        struct Metric {
            std::string name;
            double value;
            std::chrono::steady_clock::time_point timestamp;
            
            Metric(const std::string& name, double value) 
                : name(name), value(value), timestamp(std::chrono::steady_clock::now()) {}
        };
        
        std::vector<Metric> metrics_;
        std::mutex metrics_mutex_;
        std::atomic<bool> monitoring_;
        std::thread monitoring_thread_;
        
    public:
        PerformanceMonitor() : monitoring_(false) {}
        
        ~PerformanceMonitor() {
            stop_monitoring();
        }
        
        // Start monitoring
        void start_monitoring() {
            if (monitoring_) {
                return;
            }
            
            monitoring_ = true;
            monitoring_thread_ = std::thread(&PerformanceMonitor::monitoring_loop, this);
        }
        
        // Stop monitoring
        void stop_monitoring() {
            if (monitoring_) {
                monitoring_ = false;
                if (monitoring_thread_.joinable()) {
                    monitoring_thread_.join();
                }
            }
        }
        
        // Add metric
        void add_metric(const std::string& name, double value) {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            metrics_.emplace_back(name, value);
        }
        
        // Get metrics
        std::vector<Metric> get_metrics() const {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            return metrics_;
        }
        
        // Clear metrics
        void clear_metrics() {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            metrics_.clear();
        }
        
        // Export metrics to CSV
        void export_metrics(const std::string& filename) {
            std::lock_guard<std::mutex> lock(metrics_mutex_);
            
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cout << "Failed to open file: " << filename << std::endl;
                return;
            }
            
            file << "Name,Value,Timestamp" << std::endl;
            
            for (const auto& metric : metrics_) {
                auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                    metric.timestamp.time_since_epoch()).count();
                file << metric.name << "," << metric.value << "," << timestamp << std::endl;
            }
            
            file.close();
            std::cout << "Metrics exported to: " << filename << std::endl;
        }
        
    private:
        void monitoring_loop() {
            while (monitoring_) {
                // Collect system metrics (simplified)
                add_metric("cpu_usage", get_cpu_usage());
                add_metric("memory_usage", get_memory_usage());
                add_metric("thread_count", get_thread_count());
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        
        double get_cpu_usage() {
            // Simplified CPU usage calculation
            static auto last_time = std::chrono::steady_clock::now();
            static auto last_idle = std::chrono::steady_clock::now();
            
            auto now = std::chrono::steady_clock::now();
            auto idle = now - last_idle;
            auto total = now - last_time;
            
            last_time = now;
            last_idle = now;
            
            if (total.count() > 0) {
                return (1.0 - static_cast<double>(idle.count()) / total.count()) * 100.0;
            }
            return 0.0;
        }
        
        double get_memory_usage() {
            // Simplified memory usage calculation
            return 50.0 + (rand() % 50);  // Simulated memory usage
        }
        
        double get_thread_count() {
            return std::thread::hardware_concurrency();
        }
    };
    
    // Global performance monitor
    class GlobalPerformanceMonitor {
    private:
        static PerformanceMonitor instance_;
        
    public:
        static PerformanceMonitor& get_instance() {
            return instance_;
        }
    };
    
    PerformanceMonitor GlobalPerformanceMonitor::instance_;
    
    // RAII performance monitoring
    class PerformanceMonitoring {
    private:
        std::string operation_name_;
        Profiling::HighResolutionTimer timer_;
        
    public:
        PerformanceMonitoring(const std::string& operation_name) : operation_name_(operation_name) {
            timer_.start();
        }
        
        ~PerformanceMonitoring() {
            double elapsed = timer_.elapsed_seconds();
            GlobalPerformanceMonitor::get_instance().add_metric(operation_name_ + "_duration", elapsed);
        }
    };
    
    void demonstratePerformanceMonitoring() {
        std::cout << "\n=== Performance Monitoring ===" << std::endl;
        
        // Start monitoring
        GlobalPerformanceMonitor::get_instance().start_monitoring();
        
        // Simulate some operations
        for (int i = 0; i < 10; ++i) {
            {
                PerformanceMonitoring monitoring("test_operation");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            
            // Add some metrics
            GlobalPerformanceMonitor::get_instance().add_metric("custom_metric", i * 10.0);
        }
        
        // Wait a bit for monitoring to collect data
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Stop monitoring
        GlobalPerformanceMonitor::get_instance().stop_monitoring();
        
        // Export metrics
        GlobalPerformanceMonitor::get_instance().export_metrics("performance_metrics.csv");
        
        std::cout << "Performance monitoring completed" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Performance Engineering Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced performance engineering techniques including\n"
              << "profiling, benchmarking, performance analysis, optimization strategies,\n"
              << "and performance monitoring.\n" << std::endl;
    
    // Demonstrate various performance engineering techniques
    Profiling::demonstrateProfiling();
    Benchmarking::demonstrateBenchmarking();
    PerformanceAnalysis::demonstratePerformanceAnalysis();
    OptimizationStrategies::demonstrateOptimizationStrategies();
    PerformanceMonitoring::demonstratePerformanceMonitoring();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Profiling provides detailed timing information for code sections" << std::endl;
    std::cout << "2. Benchmarking enables systematic performance comparison" << std::endl;
    std::cout << "3. Performance analysis identifies bottlenecks and optimization opportunities" << std::endl;
    std::cout << "4. Optimization strategies improve cache utilization and memory access patterns" << std::endl;
    std::cout << "5. Performance monitoring enables real-time system health tracking" << std::endl;
    std::cout << "6. Cache-friendly data structures improve memory access performance" << std::endl;
    std::cout << "7. Memory pools reduce allocation overhead for frequent allocations" << std::endl;
    std::cout << "8. Systematic performance engineering leads to better software quality" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_performance_engineering 02_Advanced_Performance_Engineering.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_performance_engineering 02_Advanced_Performance_Engineering.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Advanced_Performance_Engineering.cpp
 * 
 * Running:
 * ./advanced_performance_engineering (Linux/macOS)
 * advanced_performance_engineering.exe (Windows)
 * 
 * Note: This lesson requires C++17 for some features.
 * 
 * Advanced Performance Engineering Notes:
 * - Profiling provides detailed timing information for code sections
 * - Benchmarking enables systematic performance comparison
 * - Performance analysis identifies bottlenecks and optimization opportunities
 * - Optimization strategies improve cache utilization and memory access patterns
 * - Performance monitoring enables real-time system health tracking
 * - Cache-friendly data structures improve memory access performance
 * - Memory pools reduce allocation overhead for frequent allocations
 * - Systematic performance engineering leads to better software quality
 */"""
