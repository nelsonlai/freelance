/*
 * Lesson 15.3: Advanced Performance Optimization
 * 
 * This file demonstrates advanced performance optimization techniques,
 * profiling, benchmarking, and optimization strategies.
 */

#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <numeric>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

// Example 1: Cache Optimization
namespace CacheOptimization {
    
    // Cache-friendly matrix multiplication
    template<size_t N>
    class CacheFriendlyMatrix {
    private:
        std::array<std::array<double, N>, N> data_;
        
    public:
        CacheFriendlyMatrix() {
            std::fill(&data_[0][0], &data_[0][0] + N * N, 0.0);
        }
        
        double& operator()(size_t row, size_t col) { return data_[row][col]; }
        const double& operator()(size_t row, size_t col) const { return data_[row][col]; }
        
        // Cache-friendly matrix multiplication
        CacheFriendlyMatrix operator*(const CacheFriendlyMatrix& other) const {
            CacheFriendlyMatrix result;
            
            const size_t block_size = 64; // Cache line size
            
            for (size_t ii = 0; ii < N; ii += block_size) {
                for (size_t jj = 0; jj < N; jj += block_size) {
                    for (size_t kk = 0; kk < N; kk += block_size) {
                        for (size_t i = ii; i < std::min(ii + block_size, N); ++i) {
                            for (size_t j = jj; j < std::min(jj + block_size, N); ++j) {
                                double sum = 0.0;
                                for (size_t k = kk; k < std::min(kk + block_size, N); ++k) {
                                    sum += data_[i][k] * other.data_[k][j];
                                }
                                result.data_[i][j] += sum;
                            }
                        }
                    }
                }
            }
            
            return result;
        }
        
        void fill_random() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            
            for (auto& row : data_) {
                for (auto& elem : row) {
                    elem = dis(gen);
                }
            }
        }
    };
    
    // Cache-unfriendly matrix (for comparison)
    template<size_t N>
    class CacheUnfriendlyMatrix {
    private:
        std::array<std::array<double, N>, N> data_;
        
    public:
        CacheUnfriendlyMatrix() {
            std::fill(&data_[0][0], &data_[0][0] + N * N, 0.0);
        }
        
        double& operator()(size_t row, size_t col) { return data_[row][col]; }
        const double& operator()(size_t row, size_t col) const { return data_[row][col]; }
        
        // Cache-unfriendly matrix multiplication
        CacheUnfriendlyMatrix operator*(const CacheUnfriendlyMatrix& other) const {
            CacheUnfriendlyMatrix result;
            
            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    for (size_t k = 0; k < N; ++k) {
                        result.data_[i][j] += data_[i][k] * other.data_[k][j];
                    }
                }
            }
            
            return result;
        }
        
        void fill_random() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            
            for (auto& row : data_) {
                for (auto& elem : row) {
                    elem = dis(gen);
                }
            }
        }
    };
    
    // Data structure with good cache locality
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
        
        void push_back(const T& value) {
            if (size_ >= capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            data_[size_++] = value;
        }
        
        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = new T[new_capacity];
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }
        
        T& operator[](size_t index) { return data_[index]; }
        const T& operator[](size_t index) const { return data_[index]; }
        
        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }
        
        // Cache-friendly iteration
        template<typename Func>
        void for_each(Func func) {
            for (size_t i = 0; i < size_; ++i) {
                func(data_[i]);
            }
        }
        
        // Cache-friendly sum
        T sum() const {
            T result = T{};
            for (size_t i = 0; i < size_; ++i) {
                result += data_[i];
            }
            return result;
        }
    };
    
    void demonstrateCacheOptimization() {
        std::cout << "=== Cache Optimization ===" << std::endl;
        
        const size_t matrix_size = 512;
        
        // Cache-friendly matrix multiplication
        CacheFriendlyMatrix<matrix_size> matrix1, matrix2;
        matrix1.fill_random();
        matrix2.fill_random();
        
        auto start = std::chrono::high_resolution_clock::now();
        auto result1 = matrix1 * matrix2;
        auto end = std::chrono::high_resolution_clock::now();
        auto cache_friendly_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Cache-friendly matrix multiplication time: " << cache_friendly_time.count() << " ms" << std::endl;
        
        // Cache-unfriendly matrix multiplication
        CacheUnfriendlyMatrix<matrix_size> matrix3, matrix4;
        matrix3.fill_random();
        matrix4.fill_random();
        
        start = std::chrono::high_resolution_clock::now();
        auto result2 = matrix3 * matrix4;
        end = std::chrono::high_resolution_clock::now();
        auto cache_unfriendly_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Cache-unfriendly matrix multiplication time: " << cache_unfriendly_time.count() << " ms" << std::endl;
        std::cout << "Cache optimization speedup: " << (double)cache_unfriendly_time.count() / cache_friendly_time.count() << "x" << std::endl;
        
        // Cache-friendly vector
        const size_t vector_size = 1000000;
        
        CacheFriendlyVector<int> cache_vec;
        std::vector<int> std_vec;
        
        for (size_t i = 0; i < vector_size; ++i) {
            cache_vec.push_back(i);
            std_vec.push_back(i);
        }
        
        // Sum comparison
        start = std::chrono::high_resolution_clock::now();
        int cache_sum = cache_vec.sum();
        end = std::chrono::high_resolution_clock::now();
        auto cache_sum_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        start = std::chrono::high_resolution_clock::now();
        int std_sum = std::accumulate(std_vec.begin(), std_vec.end(), 0);
        end = std::chrono::high_resolution_clock::now();
        auto std_sum_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Cache-friendly sum time: " << cache_sum_time.count() << " microseconds" << std::endl;
        std::cout << "Standard sum time: " << std_sum_time.count() << " microseconds" << std::endl;
        std::cout << "Sum results match: " << (cache_sum == std_sum ? "Yes" : "No") << std::endl;
    }
}

// Example 2: SIMD Optimization
namespace SIMDOptimization {
    
    // SIMD-friendly vector operations
    class SIMDVector {
    private:
        std::vector<float> data_;
        
    public:
        SIMDVector(size_t size) : data_(size) {}
        
        void fill_random() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0f, 1.0f);
            
            for (auto& elem : data_) {
                elem = dis(gen);
            }
        }
        
        // SIMD-friendly addition
        SIMDVector operator+(const SIMDVector& other) const {
            SIMDVector result(data_.size());
            
            const size_t simd_width = 4; // Assume 4 floats per SIMD instruction
            
            for (size_t i = 0; i < data_.size(); i += simd_width) {
                size_t end = std::min(i + simd_width, data_.size());
                for (size_t j = i; j < end; ++j) {
                    result.data_[j] = data_[j] + other.data_[j];
                }
            }
            
            return result;
        }
        
        // SIMD-friendly multiplication
        SIMDVector operator*(const SIMDVector& other) const {
            SIMDVector result(data_.size());
            
            const size_t simd_width = 4;
            
            for (size_t i = 0; i < data_.size(); i += simd_width) {
                size_t end = std::min(i + simd_width, data_.size());
                for (size_t j = i; j < end; ++j) {
                    result.data_[j] = data_[j] * other.data_[j];
                }
            }
            
            return result;
        }
        
        // SIMD-friendly dot product
        float dot_product(const SIMDVector& other) const {
            float result = 0.0f;
            
            const size_t simd_width = 4;
            
            for (size_t i = 0; i < data_.size(); i += simd_width) {
                size_t end = std::min(i + simd_width, data_.size());
                for (size_t j = i; j < end; ++j) {
                    result += data_[j] * other.data_[j];
                }
            }
            
            return result;
        }
        
        // SIMD-friendly magnitude
        float magnitude() const {
            float result = 0.0f;
            
            const size_t simd_width = 4;
            
            for (size_t i = 0; i < data_.size(); i += simd_width) {
                size_t end = std::min(i + simd_width, data_.size());
                for (size_t j = i; j < end; ++j) {
                    result += data_[j] * data_[j];
                }
            }
            
            return std::sqrt(result);
        }
        
        size_t size() const { return data_.size(); }
        float& operator[](size_t index) { return data_[index]; }
        const float& operator[](size_t index) const { return data_[index]; }
    };
    
    // Standard vector for comparison
    class StandardVector {
    private:
        std::vector<float> data_;
        
    public:
        StandardVector(size_t size) : data_(size) {}
        
        void fill_random() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0f, 1.0f);
            
            for (auto& elem : data_) {
                elem = dis(gen);
            }
        }
        
        StandardVector operator+(const StandardVector& other) const {
            StandardVector result(data_.size());
            
            for (size_t i = 0; i < data_.size(); ++i) {
                result.data_[i] = data_[i] + other.data_[i];
            }
            
            return result;
        }
        
        StandardVector operator*(const StandardVector& other) const {
            StandardVector result(data_.size());
            
            for (size_t i = 0; i < data_.size(); ++i) {
                result.data_[i] = data_[i] * other.data_[i];
            }
            
            return result;
        }
        
        float dot_product(const StandardVector& other) const {
            float result = 0.0f;
            
            for (size_t i = 0; i < data_.size(); ++i) {
                result += data_[i] * other.data_[i];
            }
            
            return result;
        }
        
        float magnitude() const {
            float result = 0.0f;
            
            for (size_t i = 0; i < data_.size(); ++i) {
                result += data_[i] * data_[i];
            }
            
            return std::sqrt(result);
        }
        
        size_t size() const { return data_.size(); }
        float& operator[](size_t index) { return data_[index]; }
        const float& operator[](size_t index) const { return data_[index]; }
    };
    
    void demonstrateSIMDOptimization() {
        std::cout << "\n=== SIMD Optimization ===" << std::endl;
        
        const size_t vector_size = 1000000;
        
        // SIMD vector operations
        SIMDVector simd_vec1(vector_size), simd_vec2(vector_size);
        simd_vec1.fill_random();
        simd_vec2.fill_random();
        
        auto start = std::chrono::high_resolution_clock::now();
        auto simd_result = simd_vec1 + simd_vec2;
        auto end = std::chrono::high_resolution_clock::now();
        auto simd_add_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        start = std::chrono::high_resolution_clock::now();
        auto simd_mult_result = simd_vec1 * simd_vec2;
        end = std::chrono::high_resolution_clock::now();
        auto simd_mult_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        start = std::chrono::high_resolution_clock::now();
        float simd_dot = simd_vec1.dot_product(simd_vec2);
        end = std::chrono::high_resolution_clock::now();
        auto simd_dot_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Standard vector operations
        StandardVector std_vec1(vector_size), std_vec2(vector_size);
        std_vec1.fill_random();
        std_vec2.fill_random();
        
        start = std::chrono::high_resolution_clock::now();
        auto std_result = std_vec1 + std_vec2;
        end = std::chrono::high_resolution_clock::now();
        auto std_add_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        start = std::chrono::high_resolution_clock::now();
        auto std_mult_result = std_vec1 * std_vec2;
        end = std::chrono::high_resolution_clock::now();
        auto std_mult_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        start = std::chrono::high_resolution_clock::now();
        float std_dot = std_vec1.dot_product(std_vec2);
        end = std::chrono::high_resolution_clock::now();
        auto std_dot_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "SIMD addition time: " << simd_add_time.count() << " microseconds" << std::endl;
        std::cout << "Standard addition time: " << std_add_time.count() << " microseconds" << std::endl;
        std::cout << "Addition speedup: " << (double)std_add_time.count() / simd_add_time.count() << "x" << std::endl;
        
        std::cout << "SIMD multiplication time: " << simd_mult_time.count() << " microseconds" << std::endl;
        std::cout << "Standard multiplication time: " << std_mult_time.count() << " microseconds" << std::endl;
        std::cout << "Multiplication speedup: " << (double)std_mult_time.count() / simd_mult_time.count() << "x" << std::endl;
        
        std::cout << "SIMD dot product time: " << simd_dot_time.count() << " microseconds" << std::endl;
        std::cout << "Standard dot product time: " << std_dot_time.count() << " microseconds" << std::endl;
        std::cout << "Dot product speedup: " << (double)std_dot_time.count() / simd_dot_time.count() << "x" << std::endl;
        
        std::cout << "Dot product results match: " << (std::abs(simd_dot - std_dot) < 1e-6 ? "Yes" : "No") << std::endl;
    }
}

// Example 3: Branch Prediction Optimization
namespace BranchPredictionOptimization {
    
    // Branch prediction friendly sorting
    template<typename T>
    void branch_friendly_sort(std::vector<T>& data) {
        // Use a sorting algorithm that minimizes branch mispredictions
        std::sort(data.begin(), data.end());
    }
    
    // Branch prediction friendly search
    template<typename T>
    size_t branch_friendly_search(const std::vector<T>& data, const T& value) {
        // Use binary search which has predictable branches
        auto it = std::lower_bound(data.begin(), data.end(), value);
        return std::distance(data.begin(), it);
    }
    
    // Branch prediction friendly conditional
    template<typename T>
    T branch_friendly_conditional(bool condition, const T& true_value, const T& false_value) {
        // Use conditional move instead of branch
        return condition ? true_value : false_value;
    }
    
    // Branch prediction friendly loop
    template<typename T>
    T branch_friendly_sum(const std::vector<T>& data) {
        T sum = T{};
        
        // Unroll loop to reduce branch overhead
        const size_t unroll_factor = 4;
        size_t i = 0;
        
        for (; i + unroll_factor <= data.size(); i += unroll_factor) {
            sum += data[i] + data[i + 1] + data[i + 2] + data[i + 3];
        }
        
        for (; i < data.size(); ++i) {
            sum += data[i];
        }
        
        return sum;
    }
    
    // Branch prediction friendly comparison
    template<typename T>
    bool branch_friendly_compare(const std::vector<T>& data, const T& threshold) {
        // Use SIMD-like operations to reduce branches
        bool result = true;
        
        for (const auto& elem : data) {
            result &= (elem > threshold);
        }
        
        return result;
    }
    
    void demonstrateBranchPredictionOptimization() {
        std::cout << "\n=== Branch Prediction Optimization ===" << std::endl;
        
        const size_t data_size = 1000000;
        std::vector<int> data(data_size);
        
        // Fill with random data
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        for (auto& elem : data) {
            elem = dis(gen);
        }
        
        // Branch-friendly sorting
        auto start = std::chrono::high_resolution_clock::now();
        branch_friendly_sort(data);
        auto end = std::chrono::high_resolution_clock::now();
        auto sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Branch-friendly sort time: " << sort_time.count() << " microseconds" << std::endl;
        
        // Branch-friendly search
        const int search_value = 500;
        
        start = std::chrono::high_resolution_clock::now();
        size_t search_result = branch_friendly_search(data, search_value);
        end = std::chrono::high_resolution_clock::now();
        auto search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Branch-friendly search time: " << search_time.count() << " microseconds" << std::endl;
        std::cout << "Search result: " << search_result << std::endl;
        
        // Branch-friendly sum
        start = std::chrono::high_resolution_clock::now();
        int sum_result = branch_friendly_sum(data);
        end = std::chrono::high_resolution_clock::now();
        auto sum_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Branch-friendly sum time: " << sum_time.count() << " microseconds" << std::endl;
        std::cout << "Sum result: " << sum_result << std::endl;
        
        // Branch-friendly comparison
        const int threshold = 100;
        
        start = std::chrono::high_resolution_clock::now();
        bool compare_result = branch_friendly_compare(data, threshold);
        end = std::chrono::high_resolution_clock::now();
        auto compare_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Branch-friendly compare time: " << compare_time.count() << " microseconds" << std::endl;
        std::cout << "Compare result: " << (compare_result ? "All elements > threshold" : "Some elements <= threshold") << std::endl;
    }
}

// Example 4: Memory Access Optimization
namespace MemoryAccessOptimization {
    
    // Memory access pattern optimization
    template<typename T>
    class MemoryOptimizedVector {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;
        
    public:
        MemoryOptimizedVector() : data_(nullptr), size_(0), capacity_(0) {}
        
        ~MemoryOptimizedVector() {
            delete[] data_;
        }
        
        void push_back(const T& value) {
            if (size_ >= capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            data_[size_++] = value;
        }
        
        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = new T[new_capacity];
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }
        
        T& operator[](size_t index) { return data_[index]; }
        const T& operator[](size_t index) const { return data_[index]; }
        
        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }
        
        // Memory-optimized iteration
        template<typename Func>
        void for_each(Func func) {
            const size_t cache_line_size = 64;
            const size_t elements_per_cache_line = cache_line_size / sizeof(T);
            
            for (size_t i = 0; i < size_; i += elements_per_cache_line) {
                size_t end = std::min(i + elements_per_cache_line, size_);
                for (size_t j = i; j < end; ++j) {
                    func(data_[j]);
                }
            }
        }
        
        // Memory-optimized sum
        T sum() const {
            T result = T{};
            
            const size_t cache_line_size = 64;
            const size_t elements_per_cache_line = cache_line_size / sizeof(T);
            
            for (size_t i = 0; i < size_; i += elements_per_cache_line) {
                size_t end = std::min(i + elements_per_cache_line, size_);
                for (size_t j = i; j < end; ++j) {
                    result += data_[j];
                }
            }
            
            return result;
        }
    };
    
    // Memory access pattern analysis
    template<typename T>
    class MemoryAccessAnalyzer {
    private:
        std::vector<T> data_;
        std::vector<size_t> access_pattern_;
        
    public:
        MemoryAccessAnalyzer(size_t size) : data_(size), access_pattern_() {
            access_pattern_.reserve(size);
        }
        
        void fill_random() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 1000);
            
            for (auto& elem : data_) {
                elem = dis(gen);
            }
        }
        
        // Sequential access (good cache locality)
        T sequential_sum() {
            access_pattern_.clear();
            T result = T{};
            
            for (size_t i = 0; i < data_.size(); ++i) {
                access_pattern_.push_back(i);
                result += data_[i];
            }
            
            return result;
        }
        
        // Random access (poor cache locality)
        T random_sum() {
            access_pattern_.clear();
            T result = T{};
            
            std::vector<size_t> indices(data_.size());
            std::iota(indices.begin(), indices.end(), 0);
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(indices.begin(), indices.end(), gen);
            
            for (size_t index : indices) {
                access_pattern_.push_back(index);
                result += data_[index];
            }
            
            return result;
        }
        
        // Strided access (moderate cache locality)
        T strided_sum(size_t stride) {
            access_pattern_.clear();
            T result = T{};
            
            for (size_t i = 0; i < data_.size(); i += stride) {
                access_pattern_.push_back(i);
                result += data_[i];
            }
            
            return result;
        }
        
        const std::vector<size_t>& get_access_pattern() const {
            return access_pattern_;
        }
    };
    
    void demonstrateMemoryAccessOptimization() {
        std::cout << "\n=== Memory Access Optimization ===" << std::endl;
        
        const size_t vector_size = 1000000;
        
        // Memory-optimized vector
        MemoryOptimizedVector<int> mem_vec;
        std::vector<int> std_vec;
        
        for (size_t i = 0; i < vector_size; ++i) {
            mem_vec.push_back(i);
            std_vec.push_back(i);
        }
        
        // Sum comparison
        auto start = std::chrono::high_resolution_clock::now();
        int mem_sum = mem_vec.sum();
        auto end = std::chrono::high_resolution_clock::now();
        auto mem_sum_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        start = std::chrono::high_resolution_clock::now();
        int std_sum = std::accumulate(std_vec.begin(), std_vec.end(), 0);
        end = std::chrono::high_resolution_clock::now();
        auto std_sum_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Memory-optimized sum time: " << mem_sum_time.count() << " microseconds" << std::endl;
        std::cout << "Standard sum time: " << std_sum_time.count() << " microseconds" << std::endl;
        std::cout << "Memory optimization speedup: " << (double)std_sum_time.count() / mem_sum_time.count() << "x" << std::endl;
        std::cout << "Sum results match: " << (mem_sum == std_sum ? "Yes" : "No") << std::endl;
        
        // Memory access pattern analysis
        const size_t analysis_size = 100000;
        MemoryAccessAnalyzer<int> analyzer(analysis_size);
        analyzer.fill_random();
        
        // Sequential access
        start = std::chrono::high_resolution_clock::now();
        int seq_sum = analyzer.sequential_sum();
        end = std::chrono::high_resolution_clock::now();
        auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Random access
        start = std::chrono::high_resolution_clock::now();
        int rand_sum = analyzer.random_sum();
        end = std::chrono::high_resolution_clock::now();
        auto rand_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Strided access
        start = std::chrono::high_resolution_clock::now();
        int strided_sum = analyzer.strided_sum(10);
        end = std::chrono::high_resolution_clock::now();
        auto strided_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Sequential access time: " << seq_time.count() << " microseconds" << std::endl;
        std::cout << "Random access time: " << rand_time.count() << " microseconds" << std::endl;
        std::cout << "Strided access time: " << strided_time.count() << " microseconds" << std::endl;
        std::cout << "Sequential vs Random speedup: " << (double)rand_time.count() / seq_time.count() << "x" << std::endl;
        std::cout << "Sequential vs Strided speedup: " << (double)strided_time.count() / seq_time.count() << "x" << std::endl;
    }
}

// Example 5: Algorithm Optimization
namespace AlgorithmOptimization {
    
    // Optimized sorting algorithms
    template<typename T>
    void optimized_quicksort(std::vector<T>& data, size_t low, size_t high) {
        if (low < high) {
            // Use insertion sort for small arrays
            if (high - low < 10) {
                for (size_t i = low + 1; i <= high; ++i) {
                    T key = data[i];
                    size_t j = i;
                    while (j > low && data[j - 1] > key) {
                        data[j] = data[j - 1];
                        --j;
                    }
                    data[j] = key;
                }
                return;
            }
            
            // Use median-of-three for pivot selection
            size_t mid = low + (high - low) / 2;
            if (data[mid] < data[low]) std::swap(data[low], data[mid]);
            if (data[high] < data[low]) std::swap(data[low], data[high]);
            if (data[high] < data[mid]) std::swap(data[mid], data[high]);
            
            T pivot = data[mid];
            size_t i = low, j = high;
            
            while (i <= j) {
                while (data[i] < pivot) ++i;
                while (data[j] > pivot) --j;
                if (i <= j) {
                    std::swap(data[i], data[j]);
                    ++i;
                    --j;
                }
            }
            
            optimized_quicksort(data, low, j);
            optimized_quicksort(data, i, high);
        }
    }
    
    // Optimized binary search
    template<typename T>
    size_t optimized_binary_search(const std::vector<T>& data, const T& value) {
        size_t left = 0, right = data.size();
        
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            
            if (data[mid] < value) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    // Optimized matrix multiplication
    template<size_t N>
    void optimized_matrix_multiply(const std::array<std::array<double, N>, N>& a,
                                  const std::array<std::array<double, N>, N>& b,
                                  std::array<std::array<double, N>, N>& c) {
        const size_t block_size = 64;
        
        for (size_t ii = 0; ii < N; ii += block_size) {
            for (size_t jj = 0; jj < N; jj += block_size) {
                for (size_t kk = 0; kk < N; kk += block_size) {
                    for (size_t i = ii; i < std::min(ii + block_size, N); ++i) {
                        for (size_t j = jj; j < std::min(jj + block_size, N); ++j) {
                            double sum = 0.0;
                            for (size_t k = kk; k < std::min(kk + block_size, N); ++k) {
                                sum += a[i][k] * b[k][j];
                            }
                            c[i][j] += sum;
                        }
                    }
                }
            }
        }
    }
    
    void demonstrateAlgorithmOptimization() {
        std::cout << "\n=== Algorithm Optimization ===" << std::endl;
        
        const size_t data_size = 100000;
        std::vector<int> data(data_size);
        
        // Fill with random data
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        for (auto& elem : data) {
            elem = dis(gen);
        }
        
        // Optimized quicksort
        std::vector<int> sort_data = data;
        
        auto start = std::chrono::high_resolution_clock::now();
        optimized_quicksort(sort_data, 0, sort_data.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto optimized_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Standard sort
        std::vector<int> std_sort_data = data;
        
        start = std::chrono::high_resolution_clock::now();
        std::sort(std_sort_data.begin(), std_sort_data.end());
        end = std::chrono::high_resolution_clock::now();
        auto std_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Optimized quicksort time: " << optimized_sort_time.count() << " microseconds" << std::endl;
        std::cout << "Standard sort time: " << std_sort_time.count() << " microseconds" << std::endl;
        std::cout << "Sort optimization speedup: " << (double)std_sort_time.count() / optimized_sort_time.count() << "x" << std::endl;
        
        // Optimized binary search
        const int search_value = 500;
        
        start = std::chrono::high_resolution_clock::now();
        size_t optimized_search_result = optimized_binary_search(sort_data, search_value);
        end = std::chrono::high_resolution_clock::now();
        auto optimized_search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Standard binary search
        start = std::chrono::high_resolution_clock::now();
        auto std_search_result = std::lower_bound(sort_data.begin(), sort_data.end(), search_value);
        end = std::chrono::high_resolution_clock::now();
        auto std_search_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Optimized binary search time: " << optimized_search_time.count() << " microseconds" << std::endl;
        std::cout << "Standard binary search time: " << std_search_time.count() << " microseconds" << std::endl;
        std::cout << "Search optimization speedup: " << (double)std_search_time.count() / optimized_search_time.count() << "x" << std::endl;
        std::cout << "Search results match: " << (optimized_search_result == std::distance(sort_data.begin(), std_search_result) ? "Yes" : "No") << std::endl;
        
        // Optimized matrix multiplication
        const size_t matrix_size = 256;
        std::array<std::array<double, matrix_size>, matrix_size> matrix_a, matrix_b, matrix_c;
        
        // Fill matrices with random data
        std::uniform_real_distribution<> dis_real(0.0, 1.0);
        for (auto& row : matrix_a) {
            for (auto& elem : row) {
                elem = dis_real(gen);
            }
        }
        for (auto& row : matrix_b) {
            for (auto& elem : row) {
                elem = dis_real(gen);
            }
        }
        
        // Initialize result matrix
        for (auto& row : matrix_c) {
            std::fill(row.begin(), row.end(), 0.0);
        }
        
        start = std::chrono::high_resolution_clock::now();
        optimized_matrix_multiply(matrix_a, matrix_b, matrix_c);
        end = std::chrono::high_resolution_clock::now();
        auto optimized_matrix_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Optimized matrix multiplication time: " << optimized_matrix_time.count() << " ms" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Performance Optimization Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced performance optimization techniques,\n"
              << "profiling, benchmarking, and optimization strategies.\n" << std::endl;
    
    // Demonstrate various advanced performance optimization concepts
    CacheOptimization::demonstrateCacheOptimization();
    SIMDOptimization::demonstrateSIMDOptimization();
    BranchPredictionOptimization::demonstrateBranchPredictionOptimization();
    MemoryAccessOptimization::demonstrateMemoryAccessOptimization();
    AlgorithmOptimization::demonstrateAlgorithmOptimization();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Cache optimization significantly improves memory access performance" << std::endl;
    std::cout << "2. SIMD optimization enables vectorized operations for better throughput" << std::endl;
    std::cout << "3. Branch prediction optimization reduces pipeline stalls" << std::endl;
    std::cout << "4. Memory access patterns greatly affect performance" << std::endl;
    std::cout << "5. Algorithm optimization can provide substantial performance improvements" << std::endl;
    std::cout << "6. Profiling and benchmarking are essential for identifying bottlenecks" << std::endl;
    std::cout << "7. Modern CPUs have complex performance characteristics that require careful optimization" << std::endl;
    std::cout << "8. Performance optimization should be data-driven and measured" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -march=native -o advanced_performance_optimization 03_Advanced_Performance_Optimization.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -march=native -o advanced_performance_optimization 03_Advanced_Performance_Optimization.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 /arch:AVX2 03_Advanced_Performance_Optimization.cpp
 * 
 * Running:
 * ./advanced_performance_optimization (Linux/macOS)
 * advanced_performance_optimization.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for some features.
 * The -march=native flag enables CPU-specific optimizations.
 * 
 * Advanced Performance Optimization Notes:
 * - Cache optimization significantly improves memory access performance
 * - SIMD optimization enables vectorized operations for better throughput
 * - Branch prediction optimization reduces pipeline stalls
 * - Memory access patterns greatly affect performance
 * - Algorithm optimization can provide substantial performance improvements
 * - Profiling and benchmarking are essential for identifying bottlenecks
 * - Modern CPUs have complex performance characteristics that require careful optimization
 * - Performance optimization should be data-driven and measured
 */"""
