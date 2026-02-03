/*
 * Lesson 17.3: Advanced Performance Optimization
 * 
 * This file demonstrates advanced performance optimization techniques
 * including profiling, benchmarking, cache optimization, branch prediction,
 * SIMD instructions, and compiler optimizations.
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
#include <numeric>
#include <cmath>

// Example 1: Profiling and Benchmarking
namespace ProfilingAndBenchmarking {
    
    // High-resolution timer for benchmarking
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
    };
    
    // Benchmark framework
    class Benchmark {
    private:
        std::string name_;
        std::vector<double> times_;
        
    public:
        Benchmark(const std::string& name) : name_(name) {}
        
        template<typename Func>
        void run(Func func, int iterations = 1000) {
            times_.clear();
            times_.reserve(iterations);
            
            for (int i = 0; i < iterations; ++i) {
                HighResolutionTimer timer;
                timer.start();
                func();
                times_.push_back(timer.elapsed_seconds());
            }
        }
        
        void print_results() {
            if (times_.empty()) {
                std::cout << "No benchmark data for " << name_ << std::endl;
                return;
            }
            
            std::sort(times_.begin(), times_.end());
            
            double min_time = times_.front();
            double max_time = times_.back();
            double avg_time = std::accumulate(times_.begin(), times_.end(), 0.0) / times_.size();
            double median_time = times_[times_.size() / 2];
            
            std::cout << "Benchmark: " << name_ << std::endl;
            std::cout << "  Min: " << min_time * 1e6 << " μs" << std::endl;
            std::cout << "  Max: " << max_time * 1e6 << " μs" << std::endl;
            std::cout << "  Avg: " << avg_time * 1e6 << " μs" << std::endl;
            std::cout << "  Median: " << median_time * 1e6 << " μs" << std::endl;
            std::cout << "  Samples: " << times_.size() << std::endl;
        }
        
        double get_average_time() const {
            if (times_.empty()) return 0.0;
            return std::accumulate(times_.begin(), times_.end(), 0.0) / times_.size();
        }
    };
    
    // Performance counter for measuring specific operations
    class PerformanceCounter {
    private:
        std::atomic<long long> count_{0};
        std::atomic<long long> total_time_{0};
        
    public:
        void add_measurement(long long time_ns) {
            count_.fetch_add(1);
            total_time_.fetch_add(time_ns);
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
        
        void reset() {
            count_.store(0);
            total_time_.store(0);
        }
    };
    
    void demonstrateProfilingAndBenchmarking() {
        std::cout << "=== Profiling and Benchmarking ===" << std::endl;
        
        // Benchmark vector operations
        Benchmark vector_benchmark("Vector Operations");
        std::vector<int> test_vector(1000);
        std::iota(test_vector.begin(), test_vector.end(), 0);
        
        vector_benchmark.run([&test_vector]() {
            std::sort(test_vector.begin(), test_vector.end());
        }, 100);
        
        vector_benchmark.print_results();
        
        // Benchmark string operations
        Benchmark string_benchmark("String Operations");
        std::string test_string = "Hello, World! This is a test string for benchmarking.";
        
        string_benchmark.run([&test_string]() {
            std::string copy = test_string;
            std::transform(copy.begin(), copy.end(), copy.begin(), ::toupper);
        }, 1000);
        
        string_benchmark.print_results();
        
        // Performance counter example
        PerformanceCounter counter;
        
        for (int i = 0; i < 100; ++i) {
            HighResolutionTimer timer;
            timer.start();
            
            // Simulate some work
            volatile int sum = 0;
            for (int j = 0; j < 1000; ++j) {
                sum += j;
            }
            
            counter.add_measurement(timer.elapsed_nanoseconds());
        }
        
        std::cout << "Performance Counter Results:" << std::endl;
        std::cout << "  Total operations: " << counter.get_total_count() << std::endl;
        std::cout << "  Average time: " << counter.get_average_time_ns() << " ns" << std::endl;
        std::cout << "  Total time: " << counter.get_total_time_ns() << " ns" << std::endl;
    }
}

// Example 2: Cache Optimization
namespace CacheOptimization {
    
    // Cache-friendly matrix multiplication
    class CacheOptimizedMatrix {
    private:
        std::vector<double> data_;
        size_t rows_, cols_;
        
    public:
        CacheOptimizedMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
            data_.resize(rows * cols);
        }
        
        double& operator()(size_t row, size_t col) {
            return data_[row * cols_ + col];
        }
        
        const double& operator()(size_t row, size_t col) const {
            return data_[row * cols_ + col];
        }
        
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }
        
        // Cache-optimized matrix multiplication with blocking
        static CacheOptimizedMatrix multiply_blocked(const CacheOptimizedMatrix& a, const CacheOptimizedMatrix& b, size_t block_size = 64) {
            assert(a.cols() == b.rows());
            
            CacheOptimizedMatrix result(a.rows(), b.cols());
            
            size_t n = a.rows();
            size_t m = a.cols();
            size_t p = b.cols();
            
            // Blocked matrix multiplication
            for (size_t ii = 0; ii < n; ii += block_size) {
                for (size_t jj = 0; jj < p; jj += block_size) {
                    for (size_t kk = 0; kk < m; kk += block_size) {
                        // Process block
                        size_t i_end = std::min(ii + block_size, n);
                        size_t j_end = std::min(jj + block_size, p);
                        size_t k_end = std::min(kk + block_size, m);
                        
                        for (size_t i = ii; i < i_end; ++i) {
                            for (size_t j = jj; j < j_end; ++j) {
                                double sum = 0.0;
                                for (size_t k = kk; k < k_end; ++k) {
                                    sum += a(i, k) * b(k, j);
                                }
                                result(i, j) += sum;
                            }
                        }
                    }
                }
            }
            
            return result;
        }
        
        // Naive matrix multiplication for comparison
        static CacheOptimizedMatrix multiply_naive(const CacheOptimizedMatrix& a, const CacheOptimizedMatrix& b) {
            assert(a.cols() == b.rows());
            
            CacheOptimizedMatrix result(a.rows(), b.cols());
            
            for (size_t i = 0; i < a.rows(); ++i) {
                for (size_t j = 0; j < b.cols(); ++j) {
                    double sum = 0.0;
                    for (size_t k = 0; k < a.cols(); ++k) {
                        sum += a(i, k) * b(k, j);
                    }
                    result(i, j) = sum;
                }
            }
            
            return result;
        }
        
        void fill_random() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(0.0, 1.0);
            
            for (auto& element : data_) {
                element = dis(gen);
            }
        }
    };
    
    // Cache-friendly data structure with padding
    struct alignas(64) CacheLineAligned {
        double value;
        char padding[64 - sizeof(double)];
    };
    
    // Array of structures vs structure of arrays
    struct ParticleAOS {
        double x, y, z;
        double vx, vy, vz;
        double mass;
    };
    
    struct ParticlesSOA {
        std::vector<double> x, y, z;
        std::vector<double> vx, vy, vz;
        std::vector<double> mass;
        
        ParticlesSOA(size_t count) : x(count), y(count), z(count), vx(count), vy(count), vz(count), mass(count) {}
        
        void update_positions(double dt) {
            for (size_t i = 0; i < x.size(); ++i) {
                x[i] += vx[i] * dt;
                y[i] += vy[i] * dt;
                z[i] += vz[i] * dt;
            }
        }
    };
    
    void demonstrateCacheOptimization() {
        std::cout << "\n=== Cache Optimization ===" << std::endl;
        
        // Matrix multiplication comparison
        const size_t matrix_size = 512;
        CacheOptimizedMatrix a(matrix_size, matrix_size);
        CacheOptimizedMatrix b(matrix_size, matrix_size);
        
        a.fill_random();
        b.fill_random();
        
        // Benchmark naive multiplication
        ProfilingAndBenchmarking::Benchmark naive_benchmark("Naive Matrix Multiplication");
        naive_benchmark.run([&a, &b]() {
            auto result = CacheOptimizedMatrix::multiply_naive(a, b);
        }, 1);
        
        naive_benchmark.print_results();
        
        // Benchmark blocked multiplication
        ProfilingAndBenchmarking::Benchmark blocked_benchmark("Blocked Matrix Multiplication");
        blocked_benchmark.run([&a, &b]() {
            auto result = CacheOptimizedMatrix::multiply_blocked(a, b);
        }, 1);
        
        blocked_benchmark.print_results();
        
        // AOS vs SOA comparison
        const size_t particle_count = 1000000;
        
        // AOS benchmark
        std::vector<ParticleAOS> particles_aos(particle_count);
        ProfilingAndBenchmarking::Benchmark aos_benchmark("Array of Structures");
        aos_benchmark.run([&particles_aos]() {
            for (auto& particle : particles_aos) {
                particle.x += particle.vx * 0.01;
                particle.y += particle.vy * 0.01;
                particle.z += particle.vz * 0.01;
            }
        }, 100);
        
        aos_benchmark.print_results();
        
        // SOA benchmark
        ParticlesSOA particles_soa(particle_count);
        ProfilingAndBenchmarking::Benchmark soa_benchmark("Structure of Arrays");
        soa_benchmark.run([&particles_soa]() {
            particles_soa.update_positions(0.01);
        }, 100);
        
        soa_benchmark.print_results();
        
        std::cout << "Cache optimization results:" << std::endl;
        std::cout << "  Blocked multiplication is " << (naive_benchmark.get_average_time() / blocked_benchmark.get_average_time()) << "x faster" << std::endl;
        std::cout << "  SOA is " << (aos_benchmark.get_average_time() / soa_benchmark.get_average_time()) << "x faster" << std::endl;
    }
}

// Example 3: Branch Prediction Optimization
namespace BranchPredictionOptimization {
    
    // Branch prediction friendly sorting
    void branch_friendly_sort(std::vector<int>& data) {
        // Separate positive and negative numbers to reduce branching
        std::vector<int> positive, negative;
        
        for (int value : data) {
            if (value >= 0) {
                positive.push_back(value);
            } else {
                negative.push_back(value);
            }
        }
        
        // Sort each partition
        std::sort(positive.begin(), positive.end());
        std::sort(negative.begin(), negative.end());
        
        // Merge back
        data.clear();
        data.insert(data.end(), negative.begin(), negative.end());
        data.insert(data.end(), positive.begin(), positive.end());
    }
    
    // Lookup table for expensive calculations
    class LookupTable {
    private:
        std::vector<double> table_;
        double min_value_, max_value_, step_;
        
    public:
        LookupTable(double min_val, double max_val, size_t size) 
            : min_value_(min_val), max_value_(max_val), step_((max_val - min_val) / (size - 1)) {
            table_.resize(size);
            
            // Precompute values
            for (size_t i = 0; i < size; ++i) {
                double x = min_val + i * step_;
                table_[i] = std::sin(x) * std::cos(x);  // Expensive calculation
            }
        }
        
        double lookup(double value) const {
            if (value < min_value_ || value > max_value_) {
                return std::sin(value) * std::cos(value);  // Fallback
            }
            
            size_t index = static_cast<size_t>((value - min_value_) / step_);
            return table_[index];
        }
    };
    
    // Branchless min/max functions
    inline int branchless_min(int a, int b) {
        return b ^ ((a ^ b) & -(a < b));
    }
    
    inline int branchless_max(int a, int b) {
        return a ^ ((a ^ b) & -(a < b));
    }
    
    // Branchless absolute value
    inline int branchless_abs(int value) {
        int mask = value >> (sizeof(int) * 8 - 1);
        return (value + mask) ^ mask;
    }
    
    // Conditional move optimization
    int conditional_move_example(int a, int b, int condition) {
        // Branch-based version (slower due to branch prediction)
        // return condition ? a : b;
        
        // Conditional move version (faster)
        int result = b;
        if (condition) {
            result = a;
        }
        return result;
    }
    
    void demonstrateBranchPredictionOptimization() {
        std::cout << "\n=== Branch Prediction Optimization ===" << std::endl;
        
        // Test branch-friendly sorting
        std::vector<int> test_data(1000000);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(-1000, 1000);
        
        std::generate(test_data.begin(), test_data.end(), [&]() { return dis(gen); });
        
        ProfilingAndBenchmarking::Benchmark std_sort_benchmark("std::sort");
        std_sort_benchmark.run([&test_data]() {
            std::vector<int> copy = test_data;
            std::sort(copy.begin(), copy.end());
        }, 10);
        
        std_sort_benchmark.print_results();
        
        ProfilingAndBenchmarking::Benchmark branch_friendly_benchmark("Branch-friendly sort");
        branch_friendly_benchmark.run([&test_data]() {
            std::vector<int> copy = test_data;
            branch_friendly_sort(copy);
        }, 10);
        
        branch_friendly_benchmark.print_results();
        
        // Test lookup table vs direct calculation
        LookupTable lookup_table(-3.14159, 3.14159, 1000);
        std::vector<double> test_values(100000);
        std::uniform_real_distribution<double> value_dis(-3.14159, 3.14159);
        
        std::generate(test_values.begin(), test_values.end(), [&]() { return value_dis(gen); });
        
        ProfilingAndBenchmarking::Benchmark direct_calc_benchmark("Direct calculation");
        direct_calc_benchmark.run([&test_values]() {
            double sum = 0.0;
            for (double value : test_values) {
                sum += std::sin(value) * std::cos(value);
            }
            volatile double result = sum;  // Prevent optimization
        }, 100);
        
        direct_calc_benchmark.print_results();
        
        ProfilingAndBenchmarking::Benchmark lookup_benchmark("Lookup table");
        lookup_benchmark.run([&test_values, &lookup_table]() {
            double sum = 0.0;
            for (double value : test_values) {
                sum += lookup_table.lookup(value);
            }
            volatile double result = sum;  // Prevent optimization
        }, 100);
        
        lookup_benchmark.print_results();
        
        // Test branchless functions
        std::vector<int> test_ints(1000000);
        std::uniform_int_distribution<int> int_dis(-1000, 1000);
        std::generate(test_ints.begin(), test_ints.end(), [&]() { return int_dis(gen); });
        
        ProfilingAndBenchmarking::Benchmark branchless_min_benchmark("Branchless min");
        branchless_min_benchmark.run([&test_ints]() {
            int sum = 0;
            for (size_t i = 0; i < test_ints.size() - 1; ++i) {
                sum += branchless_min(test_ints[i], test_ints[i + 1]);
            }
            volatile int result = sum;
        }, 100);
        
        branchless_min_benchmark.print_results();
        
        std::cout << "Branch prediction optimization results:" << std::endl;
        std::cout << "  Lookup table is " << (direct_calc_benchmark.get_average_time() / lookup_benchmark.get_average_time()) << "x faster" << std::endl;
    }
}

// Example 4: SIMD Optimization
namespace SIMDOptimization {
    
    // Simple SIMD-style vector operations (conceptual)
    class Vector4D {
    private:
        alignas(16) float data_[4];
        
    public:
        Vector4D(float x = 0, float y = 0, float z = 0, float w = 0) {
            data_[0] = x; data_[1] = y; data_[2] = z; data_[3] = w;
        }
        
        Vector4D& operator+=(const Vector4D& other) {
            for (int i = 0; i < 4; ++i) {
                data_[i] += other.data_[i];
            }
            return *this;
        }
        
        Vector4D operator+(const Vector4D& other) const {
            Vector4D result;
            for (int i = 0; i < 4; ++i) {
                result.data_[i] = data_[i] + other.data_[i];
            }
            return result;
        }
        
        Vector4D& operator*=(float scalar) {
            for (int i = 0; i < 4; ++i) {
                data_[i] *= scalar;
            }
            return *this;
        }
        
        float dot_product(const Vector4D& other) const {
            float result = 0.0f;
            for (int i = 0; i < 4; ++i) {
                result += data_[i] * other.data_[i];
            }
            return result;
        }
        
        float& operator[](int index) { return data_[index]; }
        const float& operator[](int index) const { return data_[index]; }
    };
    
    // SIMD-optimized matrix-vector multiplication
    class SIMDMatrix {
    private:
        std::vector<Vector4D> rows_;
        
    public:
        SIMDMatrix(size_t rows, size_t cols) : rows_(rows) {
            for (auto& row : rows_) {
                row = Vector4D();
            }
        }
        
        Vector4D multiply_vector(const Vector4D& vec) const {
            Vector4D result;
            for (const auto& row : rows_) {
                float dot = row.dot_product(vec);
                result += row * dot;
            }
            return result;
        }
        
        void set_row(size_t index, const Vector4D& row) {
            if (index < rows_.size()) {
                rows_[index] = row;
            }
        }
    };
    
    // Data parallel operations
    void vectorized_add(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& result) {
        assert(a.size() == b.size() && a.size() == result.size());
        
        // Process in chunks of 4 (SIMD width)
        size_t chunk_size = 4;
        size_t chunks = a.size() / chunk_size;
        
        for (size_t i = 0; i < chunks; ++i) {
            size_t base = i * chunk_size;
            for (size_t j = 0; j < chunk_size; ++j) {
                result[base + j] = a[base + j] + b[base + j];
            }
        }
        
        // Handle remaining elements
        for (size_t i = chunks * chunk_size; i < a.size(); ++i) {
            result[i] = a[i] + b[i];
        }
    }
    
    void demonstrateSIMDOptimization() {
        std::cout << "\n=== SIMD Optimization ===" << std::endl;
        
        // Test vector operations
        const size_t vector_count = 1000000;
        std::vector<Vector4D> vectors_a(vector_count);
        std::vector<Vector4D> vectors_b(vector_count);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
        
        for (size_t i = 0; i < vector_count; ++i) {
            vectors_a[i] = Vector4D(dis(gen), dis(gen), dis(gen), dis(gen));
            vectors_b[i] = Vector4D(dis(gen), dis(gen), dis(gen), dis(gen));
        }
        
        ProfilingAndBenchmarking::Benchmark vector_add_benchmark("Vector addition");
        vector_add_benchmark.run([&vectors_a, &vectors_b]() {
            for (size_t i = 0; i < vectors_a.size(); ++i) {
                vectors_a[i] += vectors_b[i];
            }
        }, 10);
        
        vector_add_benchmark.print_results();
        
        // Test vectorized operations
        const size_t array_size = 1000000;
        std::vector<float> array_a(array_size);
        std::vector<float> array_b(array_size);
        std::vector<float> result(array_size);
        
        std::generate(array_a.begin(), array_a.end(), [&]() { return dis(gen); });
        std::generate(array_b.begin(), array_b.end(), [&]() { return dis(gen); });
        
        ProfilingAndBenchmarking::Benchmark vectorized_add_benchmark("Vectorized addition");
        vectorized_add_benchmark.run([&array_a, &array_b, &result]() {
            vectorized_add(array_a, array_b, result);
        }, 100);
        
        vectorized_add_benchmark.print_results();
        
        // Test matrix-vector multiplication
        SIMDMatrix matrix(100, 4);
        for (size_t i = 0; i < 100; ++i) {
            matrix.set_row(i, Vector4D(dis(gen), dis(gen), dis(gen), dis(gen)));
        }
        
        Vector4D test_vector(dis(gen), dis(gen), dis(gen), dis(gen));
        
        ProfilingAndBenchmarking::Benchmark matrix_vector_benchmark("Matrix-vector multiplication");
        matrix_vector_benchmark.run([&matrix, &test_vector]() {
            auto result = matrix.multiply_vector(test_vector);
            volatile float sum = result[0] + result[1] + result[2] + result[3];
        }, 1000);
        
        matrix_vector_benchmark.print_results();
    }
}

// Example 5: Compiler Optimizations
namespace CompilerOptimizations {
    
    // Function inlining optimization
    inline int add_numbers(int a, int b) {
        return a + b;
    }
    
    // Loop unrolling
    void unrolled_loop_example(std::vector<int>& data) {
        size_t size = data.size();
        size_t unroll_factor = 4;
        
        // Unrolled loop
        for (size_t i = 0; i < size - unroll_factor; i += unroll_factor) {
            data[i] *= 2;
            data[i + 1] *= 2;
            data[i + 2] *= 2;
            data[i + 3] *= 2;
        }
        
        // Handle remaining elements
        for (size_t i = (size / unroll_factor) * unroll_factor; i < size; ++i) {
            data[i] *= 2;
        }
    }
    
    // Constant propagation
    constexpr int ARRAY_SIZE = 1000;
    constexpr double PI = 3.141592653589793;
    
    // Expression optimization
    double optimized_expression(double x, double y) {
        // Instead of: return (x * x) + (2 * x * y) + (y * y);
        // Use: return (x + y) * (x + y);
        return (x + y) * (x + y);
    }
    
    // Dead code elimination
    int dead_code_example(int value) {
        int unused = value * 2;  // This will be eliminated by compiler
        return value + 1;
    }
    
    // Strength reduction
    void strength_reduction_example(std::vector<int>& data) {
        // Instead of multiplication, use bit shifting where possible
        for (auto& value : data) {
            value *= 8;  // Compiler may optimize to: value << 3
        }
    }
    
    // Register allocation optimization
    void register_allocation_example(int a, int b, int c, int d) {
        // Local variables that can be kept in registers
        int temp1 = a + b;
        int temp2 = c + d;
        int result = temp1 * temp2;
        
        volatile int output = result;  // Prevent optimization
    }
    
    // Memory access optimization
    void memory_access_optimization(std::vector<int>& data) {
        // Sequential access is faster than random access
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] = i * i;
        }
    }
    
    // Template specialization for optimization
    template<typename T>
    T optimized_multiply(T a, T b) {
        return a * b;
    }
    
    template<>
    int optimized_multiply<int>(int a, int b) {
        // Specialized version for integers
        return a * b;
    }
    
    void demonstrateCompilerOptimizations() {
        std::cout << "\n=== Compiler Optimizations ===" << std::endl;
        
        // Test inlined functions
        ProfilingAndBenchmarking::Benchmark inline_benchmark("Inlined function");
        inline_benchmark.run([]() {
            int sum = 0;
            for (int i = 0; i < 1000000; ++i) {
                sum += add_numbers(i, i + 1);
            }
            volatile int result = sum;
        }, 100);
        
        inline_benchmark.print_results();
        
        // Test loop unrolling
        std::vector<int> test_data(1000000);
        std::iota(test_data.begin(), test_data.end(), 0);
        
        ProfilingAndBenchmarking::Benchmark unrolled_benchmark("Unrolled loop");
        unrolled_benchmark.run([&test_data]() {
            std::vector<int> copy = test_data;
            unrolled_loop_example(copy);
        }, 10);
        
        unrolled_benchmark.print_results();
        
        // Test expression optimization
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(-10.0, 10.0);
        
        ProfilingAndBenchmarking::Benchmark expression_benchmark("Optimized expression");
        expression_benchmark.run([&gen, &dis]() {
            double sum = 0.0;
            for (int i = 0; i < 1000000; ++i) {
                double x = dis(gen);
                double y = dis(gen);
                sum += optimized_expression(x, y);
            }
            volatile double result = sum;
        }, 100);
        
        expression_benchmark.print_results();
        
        // Test memory access patterns
        std::vector<int> memory_test_data(1000000);
        std::iota(memory_test_data.begin(), memory_test_data.end(), 0);
        
        ProfilingAndBenchmarking::Benchmark memory_benchmark("Memory access optimization");
        memory_benchmark.run([&memory_test_data]() {
            memory_access_optimization(memory_test_data);
        }, 10);
        
        memory_benchmark.print_results();
        
        std::cout << "Compiler optimization results:" << std::endl;
        std::cout << "  Inlined functions reduce function call overhead" << std::endl;
        std::cout << "  Loop unrolling reduces loop overhead" << std::endl;
        std::cout << "  Expression optimization reduces computation" << std::endl;
        std::cout << "  Memory access patterns affect cache performance" << std::endl;
    }
}

// Example 6: Advanced Optimization Techniques
namespace AdvancedOptimizationTechniques {
    
    // Memory pool for efficient allocation
    template<typename T>
    class MemoryPool {
    private:
        struct Block {
            alignas(T) char data[sizeof(T)];
            bool in_use;
        };
        
        std::vector<Block> blocks_;
        size_t next_free_;
        
    public:
        MemoryPool(size_t size) : blocks_(size), next_free_(0) {
            for (auto& block : blocks_) {
                block.in_use = false;
            }
        }
        
        T* allocate() {
            for (size_t i = 0; i < blocks_.size(); ++i) {
                size_t index = (next_free_ + i) % blocks_.size();
                if (!blocks_[index].in_use) {
                    blocks_[index].in_use = true;
                    next_free_ = (index + 1) % blocks_.size();
                    return reinterpret_cast<T*>(&blocks_[index].data);
                }
            }
            return nullptr;  // Pool is full
        }
        
        void deallocate(T* ptr) {
            for (auto& block : blocks_) {
                if (reinterpret_cast<T*>(&block.data) == ptr) {
                    block.in_use = false;
                    break;
                }
            }
        }
    };
    
    // Lock-free object pool
    template<typename T>
    class LockFreeObjectPool {
    private:
        struct Node {
            T data;
            std::atomic<Node*> next;
        };
        
        std::atomic<Node*> free_list_{nullptr};
        
    public:
        T* acquire() {
            Node* node = free_list_.load();
            while (node && !free_list_.compare_exchange_weak(node, node->next)) {
                // Retry
            }
            
            if (node) {
                return &node->data;
            }
            
            // Create new node
            return new T();
        }
        
        void release(T* obj) {
            Node* node = reinterpret_cast<Node*>(obj);
            Node* old_head = free_list_.load();
            
            do {
                node->next = old_head;
            } while (!free_list_.compare_exchange_weak(old_head, node));
        }
    };
    
    // Prefetch optimization
    void prefetch_optimized_sum(const std::vector<int>& data) {
        const size_t prefetch_distance = 8;
        
        for (size_t i = 0; i < data.size(); ++i) {
            // Prefetch next elements
            if (i + prefetch_distance < data.size()) {
                __builtin_prefetch(&data[i + prefetch_distance], 0, 3);
            }
            
            // Process current element
            volatile int sum = data[i];
        }
    }
    
    // NUMA-aware allocation
    class NumaAwareAllocator {
    public:
        static void* allocate(size_t size) {
            // In real implementation, this would use NUMA-aware allocation
            return std::aligned_alloc(64, size);  // Cache line aligned
        }
        
        static void deallocate(void* ptr) {
            std::free(ptr);
        }
    };
    
    void demonstrateAdvancedOptimizationTechniques() {
        std::cout << "\n=== Advanced Optimization Techniques ===" << std::endl;
        
        // Test memory pool
        MemoryPool<int> pool(1000);
        
        ProfilingAndBenchmarking::Benchmark pool_benchmark("Memory pool allocation");
        pool_benchmark.run([&pool]() {
            std::vector<int*> ptrs;
            for (int i = 0; i < 100; ++i) {
                int* ptr = pool.allocate();
                if (ptr) {
                    *ptr = i;
                    ptrs.push_back(ptr);
                }
            }
            
            for (int* ptr : ptrs) {
                pool.deallocate(ptr);
            }
        }, 1000);
        
        pool_benchmark.print_results();
        
        // Test prefetch optimization
        std::vector<int> prefetch_data(1000000);
        std::iota(prefetch_data.begin(), prefetch_data.end(), 0);
        
        ProfilingAndBenchmarking::Benchmark prefetch_benchmark("Prefetch optimization");
        prefetch_benchmark.run([&prefetch_data]() {
            prefetch_optimized_sum(prefetch_data);
        }, 100);
        
        prefetch_benchmark.print_results();
        
        // Test NUMA-aware allocation
        ProfilingAndBenchmarking::Benchmark numa_benchmark("NUMA-aware allocation");
        numa_benchmark.run([]() {
            void* ptr = NumaAwareAllocator::allocate(1024);
            NumaAwareAllocator::deallocate(ptr);
        }, 10000);
        
        numa_benchmark.print_results();
        
        std::cout << "Advanced optimization techniques:" << std::endl;
        std::cout << "  Memory pools reduce allocation overhead" << std::endl;
        std::cout << "  Prefetching improves cache performance" << std::endl;
        std::cout << "  NUMA-aware allocation improves memory access" << std::endl;
        std::cout << "  Lock-free data structures eliminate synchronization overhead" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Performance Optimization Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced performance optimization techniques including\n"
              << "profiling, benchmarking, cache optimization, branch prediction, SIMD instructions,\n"
              << "and compiler optimizations.\n" << std::endl;
    
    // Demonstrate various optimization techniques
    ProfilingAndBenchmarking::demonstrateProfilingAndBenchmarking();
    CacheOptimization::demonstrateCacheOptimization();
    BranchPredictionOptimization::demonstrateBranchPredictionOptimization();
    SIMDOptimization::demonstrateSIMDOptimization();
    CompilerOptimizations::demonstrateCompilerOptimizations();
    AdvancedOptimizationTechniques::demonstrateAdvancedOptimizationTechniques();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Profiling and benchmarking are essential for identifying performance bottlenecks" << std::endl;
    std::cout << "2. Cache optimization can provide significant performance improvements" << std::endl;
    std::cout << "3. Branch prediction optimization reduces pipeline stalls" << std::endl;
    std::cout << "4. SIMD instructions enable vectorized operations for better performance" << std::endl;
    std::cout << "5. Compiler optimizations can automatically improve code performance" << std::endl;
    std::cout << "6. Advanced techniques like memory pools and prefetching provide fine-grained control" << std::endl;
    std::cout << "7. Understanding hardware characteristics is crucial for optimization" << std::endl;
    std::cout << "8. Performance optimization should be data-driven and measured" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC with optimizations:
 * g++ -std=c++17 -Wall -Wextra -O3 -march=native -funroll-loops -ffast-math -o advanced_performance_optimization 03_Advanced_Performance_Optimization.cpp
 * 
 * Using Clang with optimizations:
 * clang++ -std=c++17 -Wall -Wextra -O3 -march=native -funroll-loops -ffast-math -o advanced_performance_optimization 03_Advanced_Performance_Optimization.cpp
 * 
 * Using MSVC with optimizations:
 * cl /std:c++17 /EHsc /O2 /Ox /Ot /GL /arch:AVX2 03_Advanced_Performance_Optimization.cpp
 * 
 * Running:
 * ./advanced_performance_optimization (Linux/macOS)
 * advanced_performance_optimization.exe (Windows)
 * 
 * Note: This lesson requires C++17 for some features.
 * Performance optimizations may vary based on compiler and hardware.
 * 
 * Advanced Performance Optimization Notes:
 * - Profiling and benchmarking are essential for identifying performance bottlenecks
 * - Cache optimization can provide significant performance improvements
 * - Branch prediction optimization reduces pipeline stalls
 * - SIMD instructions enable vectorized operations for better performance
 * - Compiler optimizations can automatically improve code performance
 * - Advanced techniques like memory pools and prefetching provide fine-grained control
 * - Understanding hardware characteristics is crucial for optimization
 * - Performance optimization should be data-driven and measured
 */"""
