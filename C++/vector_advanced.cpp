/*
 * VECTOR ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced vector concepts including custom allocators, move semantics, and performance optimization:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced VECTOR concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic VECTOR concepts
 * - Familiarity with intermediate C++ features
 * - Understanding of memory management
 * - Knowledge of STL containers and algorithms
 * 
 * Key Topics Covered:
 * - Advanced syntax and features
 * - Performance optimization
 * - Error handling and safety
 * - Modern C++ practices
 * - Real-world applications
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <random>
using namespace std;

// Advanced vector with custom allocator
template<typename T, typename Allocator = allocator<T>>
class AdvancedVector {
private:
    vector<T, Allocator> data;
    mutex dataMutex;
    atomic<size_t> accessCount{0};
    
public:
    void push_back(const T& value) {
        lock_guard<mutex> lock(dataMutex);
        data.push_back(value);
        accessCount.fetch_add(1);
    }
    
    void push_back(T&& value) {
        lock_guard<mutex> lock(dataMutex);
        data.push_back(move(value));
        accessCount.fetch_add(1);
    }
    
    T& operator[](size_t index) {
        accessCount.fetch_add(1);
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        accessCount.fetch_add(1);
        return data[index];
    }
    
    size_t size() const { return data.size(); }
    size_t getAccessCount() const { return accessCount.load(); }
    
    void printStats() const {
        cout << "Size: " << size() << ", Access count: " << getAccessCount() << endl;
    }
};

// Vector with move semantics
class MoveableVector {
private:
    vector<int> data;
    
public:
    MoveableVector(vector<int>&& vec) : data(move(vec)) {}
    
    MoveableVector(MoveableVector&& other) noexcept : data(move(other.data)) {}
    
    MoveableVector& operator=(MoveableVector&& other) noexcept {
        if (this != &other) {
            data = move(other.data);
        }
        return *this;
    }
    
    void print() const {
        for (int val : data) cout << val << " ";
        cout << endl;
    }
};

// Vector with performance monitoring
class MonitoredVector {
private:
    vector<int> data;
    atomic<size_t> operations{0};
    
public:
    void push_back(int value) {
        data.push_back(value);
        operations.fetch_add(1);
    }
    
    int& operator[](size_t index) {
        operations.fetch_add(1);
        return data[index];
    }
    
    size_t getOperationCount() const { return operations.load(); }
    size_t size() const { return data.size(); }
};

int main() {
    cout << "=== VECTOR ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: Custom allocator
    cout << "1. Custom Allocator:" << endl;
    AdvancedVector<int> av;
    for (int i = 0; i < 5; ++i) {
        av.push_back(i * 10);
    }
    av.printStats();
    cout << endl;
    
    // Example 2: Move semantics
    cout << "2. Move Semantics:" << endl;
    vector<int> original = {1, 2, 3, 4, 5};
    MoveableVector mv(move(original));
    mv.print();
    cout << "Original size after move: " << original.size() << endl;
    cout << endl;
    
    // Example 3: Performance monitoring
    cout << "3. Performance Monitoring:" << endl;
    MonitoredVector mv2;
    for (int i = 0; i < 10; ++i) {
        mv2.push_back(i);
    }
    cout << "Operations: " << mv2.getOperationCount() << endl;
    cout << endl;
    
    // Example 4: Thread safety
    cout << "4. Thread Safety:" << endl;
    AdvancedVector<int> threadSafe;
    vector<thread> threads;
    
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&threadSafe, i]() {
            for (int j = 0; j < 10; ++j) {
                threadSafe.push_back(i * 10 + j);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    threadSafe.printStats();
    cout << endl;
    
    // Example 5: Memory optimization
    cout << "5. Memory Optimization:" << endl;
    vector<int> optimized;
    optimized.reserve(1000);  // Pre-allocate memory
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        optimized.push_back(i);
    }
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time with reserve: " << duration.count() << " microseconds" << endl;
    cout << "Capacity: " << optimized.capacity() << endl;
    cout << "Size: " << optimized.size() << endl;
    
    return 0;
}
