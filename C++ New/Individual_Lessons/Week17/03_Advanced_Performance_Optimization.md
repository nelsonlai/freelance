# Week 17, Lesson 3: Advanced Performance Optimization

## 1. Learning Objectives

- Understand advanced performance optimization techniques and their applications.
- Learn profiling and benchmarking methodologies for identifying bottlenecks.
- Explore cache optimization strategies and data layout techniques.
- Understand branch prediction optimization and its impact on performance.
- Learn SIMD instructions and vectorized operations.
- Understand compiler optimizations and how to leverage them.
- Learn advanced optimization techniques like memory pools and prefetching.
- Understand the principles of performance measurement and analysis.

## 2. Prerequisites

- Understanding of C++ fundamentals and data structures
- Knowledge of computer architecture basics
- Familiarity with memory management concepts
- Understanding of algorithmic complexity
- Basic knowledge of compiler behavior

## 3. Profiling and Benchmarking

### 3.1 Performance Measurement Fundamentals

**Why Measure Performance:**
- Identify bottlenecks in code
- Validate optimization efforts
- Compare different implementations
- Set performance baselines
- Track performance regressions

**Measurement Principles:**
- Measure what matters to users
- Use representative workloads
- Account for system variability
- Measure multiple metrics
- Consider both average and worst-case performance

### 3.2 High-Resolution Timing

```cpp
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
```

### 3.3 Benchmarking Framework

```cpp
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
};
```

### 3.4 Performance Counters

```cpp
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
```

## 4. Cache Optimization

### 4.1 Cache Hierarchy and Locality

**Cache Levels:**
- L1 Cache: Fastest, smallest (32KB-64KB)
- L2 Cache: Medium speed, medium size (256KB-1MB)
- L3 Cache: Slower, larger (8MB-32MB)
- Main Memory: Slowest, largest (GBs)

**Types of Locality:**
- **Temporal Locality**: Recently accessed data is likely to be accessed again
- **Spatial Locality**: Data near recently accessed data is likely to be accessed

### 4.2 Cache-Friendly Data Structures

**Array of Structures vs Structure of Arrays:**
```cpp
// Array of Structures (AOS) - Cache-unfriendly
struct ParticleAOS {
    double x, y, z;
    double vx, vy, vz;
    double mass;
};

// Structure of Arrays (SOA) - Cache-friendly
struct ParticlesSOA {
    std::vector<double> x, y, z;
    std::vector<double> vx, vy, vz;
    std::vector<double> mass;
    
    void update_positions(double dt) {
        for (size_t i = 0; i < x.size(); ++i) {
            x[i] += vx[i] * dt;
            y[i] += vy[i] * dt;
            z[i] += vz[i] * dt;
        }
    }
};
```

### 4.3 Cache-Optimized Matrix Multiplication

```cpp
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
};
```

### 4.4 Cache Line Alignment

```cpp
struct alignas(64) CacheLineAligned {
    double value;
    char padding[64 - sizeof(double)];
};

// Avoid false sharing
class FalseSharingExample {
private:
    struct alignas(64) Counter {
        std::atomic<int> value{0};
        char padding[64 - sizeof(std::atomic<int>)];
    };
    
    std::array<Counter, 4> counters_;
    
public:
    void increment_counter(int index) {
        counters_[index].value.fetch_add(1);
    }
};
```

## 5. Branch Prediction Optimization

### 5.1 Branch Prediction Fundamentals

**Branch Prediction Types:**
- **Static Prediction**: Compiler makes predictions based on heuristics
- **Dynamic Prediction**: CPU learns from execution history
- **Branch Target Buffer (BTB)**: Caches branch targets

**Branch Prediction Accuracy:**
- Predictable branches: >95% accuracy
- Random branches: ~50% accuracy
- Mispredicted branches: 10-20 cycle penalty

### 5.2 Branch Prediction Optimization Techniques

**Reduce Branching:**
```cpp
// Branch-heavy version
int max_value(const std::vector<int>& data) {
    int max_val = data[0];
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] > max_val) {  // Branch here
            max_val = data[i];
        }
    }
    return max_val;
}

// Branch-reduced version
int max_value_optimized(const std::vector<int>& data) {
    int max_val = data[0];
    for (size_t i = 1; i < data.size(); ++i) {
        max_val = std::max(max_val, data[i]);  // No explicit branch
    }
    return max_val;
}
```

**Branchless Operations:**
```cpp
// Branchless min/max
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
```

### 5.3 Lookup Tables

```cpp
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
```

### 5.4 Conditional Moves

```cpp
// Branch-based version (slower due to branch prediction)
int conditional_branch(int a, int b, int condition) {
    return condition ? a : b;
}

// Conditional move version (faster)
int conditional_move(int a, int b, int condition) {
    int result = b;
    if (condition) {
        result = a;
    }
    return result;
}
```

## 6. SIMD Optimization

### 6.1 SIMD Concepts

**SIMD (Single Instruction, Multiple Data):**
- Process multiple data elements with one instruction
- Modern CPUs support 128-bit, 256-bit, and 512-bit SIMD
- Common instruction sets: SSE, AVX, AVX-512

**SIMD Benefits:**
- 2x to 8x speedup for vectorizable operations
- Reduced instruction count
- Better cache utilization
- Parallel data processing

### 6.2 SIMD-Friendly Data Structures

```cpp
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
    
    float dot_product(const Vector4D& other) const {
        float result = 0.0f;
        for (int i = 0; i < 4; ++i) {
            result += data_[i] * other.data_[i];
        }
        return result;
    }
};
```

### 6.3 Vectorized Operations

```cpp
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
```

### 6.4 SIMD Matrix Operations

```cpp
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
```

## 7. Compiler Optimizations

### 7.1 Function Inlining

```cpp
// Inline functions for better performance
inline int add_numbers(int a, int b) {
    return a + b;
}

// Template functions are implicitly inline
template<typename T>
T multiply(T a, T b) {
    return a * b;
}
```

### 7.2 Loop Optimizations

**Loop Unrolling:**
```cpp
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
```

**Loop Vectorization:**
```cpp
// Compiler can vectorize this loop
void vectorizable_loop(std::vector<float>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = data[i] * 2.0f + 1.0f;
    }
}
```

### 7.3 Expression Optimization

```cpp
// Instead of: return (x * x) + (2 * x * y) + (y * y);
// Use: return (x + y) * (x + y);
double optimized_expression(double x, double y) {
    return (x + y) * (x + y);
}

// Strength reduction
void strength_reduction_example(std::vector<int>& data) {
    // Instead of multiplication, use bit shifting where possible
    for (auto& value : data) {
        value *= 8;  // Compiler may optimize to: value << 3
    }
}
```

### 7.4 Constant Propagation and Dead Code Elimination

```cpp
constexpr int ARRAY_SIZE = 1000;
constexpr double PI = 3.141592653589793;

// Dead code elimination
int dead_code_example(int value) {
    int unused = value * 2;  // This will be eliminated by compiler
    return value + 1;
}

// Constant propagation
double circle_area(double radius) {
    return PI * radius * radius;  // PI is known at compile time
}
```

## 8. Advanced Optimization Techniques

### 8.1 Memory Pools

```cpp
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
```

### 8.2 Prefetching

```cpp
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
```

### 8.3 NUMA-Aware Allocation

```cpp
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
```

### 8.4 Lock-Free Object Pools

```cpp
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
```

## 9. Performance Analysis Tools

### 9.1 Profiling Tools

**CPU Profilers:**
- **gprof**: GNU profiler for function-level profiling
- **perf**: Linux performance analysis tool
- **Intel VTune**: Advanced performance profiler
- **Valgrind Callgrind**: Call graph profiler

**Memory Profilers:**
- **Valgrind Massif**: Heap profiler
- **Intel Inspector**: Memory and thread error detector
- **AddressSanitizer**: Memory error detector

### 9.2 Benchmarking Tools

**Micro-benchmarking:**
- **Google Benchmark**: C++ benchmarking framework
- **Catch2**: Testing framework with benchmarking
- **Nonius**: Statistical benchmarking library

**System-level Tools:**
- **htop**: System resource monitor
- **iostat**: I/O statistics
- **vmstat**: Virtual memory statistics

### 9.3 Compiler Analysis

**Compiler Flags for Analysis:**
```bash
# GCC optimization flags
g++ -O3 -march=native -funroll-loops -ffast-math

# Clang optimization flags
clang++ -O3 -march=native -funroll-loops -ffast-math

# MSVC optimization flags
cl /O2 /Ox /Ot /GL /arch:AVX2
```

**Compiler Analysis Options:**
```bash
# Generate assembly output
g++ -S -O3 source.cpp

# Generate optimization report
g++ -fopt-info-vec-optimized source.cpp

# Profile-guided optimization
g++ -fprofile-generate source.cpp
./program
g++ -fprofile-use source.cpp
```

## 10. Performance Optimization Best Practices

### 10.1 Optimization Methodology

**Optimization Process:**
1. **Measure**: Profile and benchmark current performance
2. **Identify**: Find bottlenecks and hotspots
3. **Optimize**: Apply targeted optimizations
4. **Validate**: Verify improvements and correctness
5. **Iterate**: Repeat until performance goals are met

**Performance Goals:**
- Define measurable performance targets
- Consider both throughput and latency
- Account for different workload scenarios
- Set realistic expectations

### 10.2 Common Optimization Patterns

**Data Structure Optimization:**
- Choose appropriate data structures
- Optimize memory layout
- Minimize indirection
- Use cache-friendly access patterns

**Algorithm Optimization:**
- Choose optimal algorithms
- Reduce algorithmic complexity
- Use specialized algorithms for specific cases
- Consider approximation algorithms

**System Optimization:**
- Optimize I/O operations
- Minimize system calls
- Use efficient synchronization primitives
- Consider NUMA awareness

### 10.3 Optimization Pitfalls

**Premature Optimization:**
- Don't optimize without measuring
- Focus on bottlenecks first
- Consider maintainability
- Measure the impact

**Micro-optimizations:**
- Avoid optimizing rarely executed code
- Consider compiler optimizations
- Focus on algorithmic improvements
- Measure before and after

**Over-optimization:**
- Balance performance and readability
- Consider code maintainability
- Document optimization decisions
- Use profiling to guide optimization

## 11. Performance Measurement and Analysis

### 11.1 Measurement Techniques

**Statistical Analysis:**
- Collect multiple samples
- Calculate confidence intervals
- Identify outliers
- Use appropriate statistical tests

**Workload Characterization:**
- Use representative data
- Test different scenarios
- Consider edge cases
- Account for system variability

**Performance Regression Testing:**
- Establish baselines
- Automate performance testing
- Track performance trends
- Set performance budgets

### 11.2 Performance Metrics

**Throughput Metrics:**
- Operations per second
- Data processed per unit time
- Requests handled per second
- Transactions per second

**Latency Metrics:**
- Response time
- End-to-end latency
- Queueing time
- Processing time

**Resource Utilization:**
- CPU utilization
- Memory usage
- Cache hit rates
- I/O throughput

## 12. Summary

Advanced performance optimization requires a systematic approach combining measurement, analysis, and targeted improvements. Key takeaways include:

1. **Profiling and benchmarking** are essential for identifying performance bottlenecks
2. **Cache optimization** can provide significant performance improvements
3. **Branch prediction optimization** reduces pipeline stalls
4. **SIMD instructions** enable vectorized operations for better performance
5. **Compiler optimizations** can automatically improve code performance
6. **Advanced techniques** like memory pools and prefetching provide fine-grained control
7. **Understanding hardware characteristics** is crucial for optimization
8. **Performance optimization** should be data-driven and measured

Effective performance optimization requires understanding both the application requirements and the underlying hardware characteristics, combined with systematic measurement and analysis.

## 13. Exercises

### Exercise 1: Profiling and Benchmarking
Create a benchmarking framework to compare the performance of different sorting algorithms on various data sizes and distributions.

### Exercise 2: Cache Optimization
Implement and compare cache-friendly vs cache-unfriendly versions of matrix multiplication, measuring the performance difference.

### Exercise 3: Branch Prediction Optimization
Optimize a function with many conditional branches using lookup tables and branchless operations, measuring the performance improvement.

### Exercise 4: SIMD Optimization
Implement vectorized operations for common mathematical functions and compare performance with scalar implementations.

### Exercise 5: Advanced Optimization
Implement a memory pool allocator and compare its performance with standard heap allocation for a high-frequency allocation scenario.

## 14. Further Reading

- "Computer Systems: A Programmer's Perspective" by Randal E. Bryant and David R. O'Hallaron
- "Systems Performance: Enterprise and the Cloud" by Brendan Gregg
- "The Art of Computer Programming" by Donald E. Knuth
- "High Performance Computing" by Charles Severance and Kevin Dowd
- "Optimizing C++" by Steve Heller
- "Performance Analysis and Tuning on Modern CPUs" by Agner Fog
- "Intel 64 and IA-32 Architectures Optimization Reference Manual"
