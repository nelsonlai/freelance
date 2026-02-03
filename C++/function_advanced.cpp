/*
 * FUNCTION ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced function concepts including perfect forwarding, caching, and exception safety:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced FUNCTION concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic FUNCTION concepts
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
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <type_traits>
using namespace std;

// Advanced function with perfect forwarding
template<typename F>
class PerfectFunction {
private:
    function<F> func;
    
public:
    template<typename U>
    PerfectFunction(U&& f) : func(forward<U>(f)) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(func(forward<Args>(args)...)) {
        return func(forward<Args>(args)...);
    }
};

// Function with caching
template<typename F>
class CachedFunction {
private:
    function<F> func;
    map<tuple<>, decltype(func())> cache;
    mutex cacheMutex;
    
public:
    CachedFunction(F f) : func(f) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(func(forward<Args>(args)...)) {
        auto key = make_tuple(args...);
        
        {
            lock_guard<mutex> lock(cacheMutex);
            auto it = cache.find(key);
            if (it != cache.end()) {
                return it->second;
            }
        }
        
        auto result = func(forward<Args>(args)...);
        
        {
            lock_guard<mutex> lock(cacheMutex);
            cache[key] = result;
        }
        
        return result;
    }
};

// Function with performance monitoring
template<typename F>
class MonitoredFunction {
private:
    function<F> func;
    atomic<size_t> callCount{0};
    atomic<size_t> totalTime{0};
    
public:
    MonitoredFunction(F f) : func(f) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(func(forward<Args>(args)...)) {
        auto start = chrono::high_resolution_clock::now();
        auto result = func(forward<Args>(args)...);
        auto end = chrono::high_resolution_clock::now();
        
        callCount.fetch_add(1);
        totalTime.fetch_add(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
        
        return result;
    }
    
    void printStats() const {
        cout << "Calls: " << callCount.load() << endl;
        cout << "Total time: " << totalTime.load() << " ns" << endl;
        cout << "Average time: " << (callCount.load() > 0 ? totalTime.load() / callCount.load() : 0) << " ns" << endl;
    }
};

// Function with exception handling
template<typename F>
class SafeFunction {
private:
    function<F> func;
    
public:
    SafeFunction(F f) : func(f) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> optional<decltype(func(forward<Args>(args)...))> {
        try {
            return func(forward<Args>(args)...);
        } catch (...) {
            return nullopt;
        }
    }
};

// Function with retry logic
template<typename F>
class RetryFunction {
private:
    function<F> func;
    size_t maxRetries;
    
public:
    RetryFunction(F f, size_t retries = 3) : func(f), maxRetries(retries) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(func(forward<Args>(args)...)) {
        for (size_t i = 0; i < maxRetries; ++i) {
            try {
                return func(forward<Args>(args)...);
            } catch (...) {
                if (i == maxRetries - 1) throw;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
        throw runtime_error("Max retries exceeded");
    }
};

int main() {
    cout << "=== FUNCTION ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: Perfect forwarding
    cout << "1. Perfect Forwarding:" << endl;
    PerfectFunction<int(int)> pf([](int x) { return x * 2; });
    cout << "Result: " << pf(21) << endl;
    cout << endl;
    
    // Example 2: Caching
    cout << "2. Caching:" << endl;
    CachedFunction<int(int)> cf([](int x) { 
        cout << "Computing..." << endl;
        return x * x; 
    });
    
    cout << "First call: " << cf(5) << endl;
    cout << "Second call: " << cf(5) << endl;
    cout << endl;
    
    // Example 3: Performance monitoring
    cout << "3. Performance Monitoring:" << endl;
    MonitoredFunction<int(int)> mf([](int x) { 
        this_thread::sleep_for(chrono::milliseconds(1));
        return x * 3; 
    });
    
    for (int i = 0; i < 5; ++i) {
        mf(i);
    }
    mf.printStats();
    cout << endl;
    
    // Example 4: Exception handling
    cout << "4. Exception Handling:" << endl;
    SafeFunction<int(int)> sf([](int x) {
        if (x < 0) throw invalid_argument("Negative value");
        return x * 2;
    });
    
    auto result1 = sf(5);
    auto result2 = sf(-5);
    
    cout << "Result 1: " << (result1 ? to_string(*result1) : "Error") << endl;
    cout << "Result 2: " << (result2 ? to_string(*result2) : "Error") << endl;
    cout << endl;
    
    // Example 5: Retry logic
    cout << "5. Retry Logic:" << endl;
    RetryFunction<int(int)> rf([](int x) {
        static int attempts = 0;
        attempts++;
        if (attempts < 3) throw runtime_error("Temporary failure");
        return x * 4;
    });
    
    try {
        cout << "Result: " << rf(10) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}
