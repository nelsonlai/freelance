/*
 * LAMBDA ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced lambda concepts including templates, perfect forwarding, and complex capture patterns:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced LAMBDA concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic LAMBDA concepts
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
#include <variant>
using namespace std;

// Advanced lambda with perfect forwarding
template<typename... Args>
auto createPerfectLambda(Args&&... args) {
    return [args...](auto&&... params) {
        return (args + ... + params);
    };
}

// Lambda with caching
template<typename F>
class CachedLambda {
private:
    F func;
    map<tuple<>, decltype(func())> cache;
    mutex cacheMutex;
    
public:
    CachedLambda(F f) : func(f) {}
    
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

// Lambda with performance monitoring
template<typename F>
class MonitoredLambda {
private:
    F func;
    atomic<size_t> callCount{0};
    atomic<size_t> totalTime{0};
    
public:
    MonitoredLambda(F f) : func(f) {}
    
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

// Lambda with exception handling
template<typename F>
class SafeLambda {
private:
    F func;
    
public:
    SafeLambda(F f) : func(f) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> optional<decltype(func(forward<Args>(args)...))> {
        try {
            return func(forward<Args>(args)...);
        } catch (...) {
            return nullopt;
        }
    }
};

// Lambda with retry logic
template<typename F>
class RetryLambda {
private:
    F func;
    size_t maxRetries;
    
public:
    RetryLambda(F f, size_t retries = 3) : func(f), maxRetries(retries) {}
    
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

// Lambda with state
template<typename F>
class StatefulLambda {
private:
    F func;
    atomic<size_t> state{0};
    
public:
    StatefulLambda(F f) : func(f) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(func(forward<Args>(args)...)) {
        state.fetch_add(1);
        return func(forward<Args>(args)...);
    }
    
    size_t getState() const { return state.load(); }
};

// Lambda with move semantics
template<typename F>
class MoveableLambda {
private:
    F func;
    
public:
    MoveableLambda(F f) : func(move(f)) {}
    
    MoveableLambda(MoveableLambda&& other) noexcept : func(move(other.func)) {}
    
    MoveableLambda& operator=(MoveableLambda&& other) noexcept {
        if (this != &other) {
            func = move(other.func);
        }
        return *this;
    }
    
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(func(forward<Args>(args)...)) {
        return func(forward<Args>(args)...);
    }
};

int main() {
    cout << "=== LAMBDA ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: Perfect forwarding
    cout << "1. Perfect Forwarding:" << endl;
    auto perfectLambda = createPerfectLambda(10, 20, 30);
    cout << "Result: " << perfectLambda(5, 15) << endl;
    cout << endl;
    
    // Example 2: Caching
    cout << "2. Caching:" << endl;
    CachedLambda cachedLambda([](int x) {
        cout << "Computing..." << endl;
        return x * x;
    });
    
    cout << "First call: " << cachedLambda(5) << endl;
    cout << "Second call: " << cachedLambda(5) << endl;
    cout << endl;
    
    // Example 3: Performance monitoring
    cout << "3. Performance Monitoring:" << endl;
    MonitoredLambda monitoredLambda([](int x) {
        this_thread::sleep_for(chrono::milliseconds(1));
        return x * 3;
    });
    
    for (int i = 0; i < 5; ++i) {
        monitoredLambda(i);
    }
    monitoredLambda.printStats();
    cout << endl;
    
    // Example 4: Exception handling
    cout << "4. Exception Handling:" << endl;
    SafeLambda safeLambda([](int x) {
        if (x < 0) throw invalid_argument("Negative value");
        return x * 2;
    });
    
    auto result1 = safeLambda(5);
    auto result2 = safeLambda(-5);
    
    cout << "Result 1: " << (result1 ? to_string(*result1) : "Error") << endl;
    cout << "Result 2: " << (result2 ? to_string(*result2) : "Error") << endl;
    cout << endl;
    
    // Example 5: Retry logic
    cout << "5. Retry Logic:" << endl;
    RetryLambda retryLambda([](int x) {
        static int attempts = 0;
        attempts++;
        if (attempts < 3) throw runtime_error("Temporary failure");
        return x * 4;
    });
    
    try {
        cout << "Result: " << retryLambda(10) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 6: Stateful lambda
    cout << "6. Stateful Lambda:" << endl;
    StatefulLambda statefulLambda([](int x) { return x * 2; });
    
    for (int i = 0; i < 5; ++i) {
        cout << "Call " << (i + 1) << ": " << statefulLambda(i) << endl;
    }
    cout << "State: " << statefulLambda.getState() << endl;
    cout << endl;
    
    // Example 7: Move semantics
    cout << "7. Move Semantics:" << endl;
    MoveableLambda moveableLambda([](int x) { return x * 3; });
    MoveableLambda movedLambda = move(moveableLambda);
    
    cout << "Moved lambda result: " << movedLambda(7) << endl;
    cout << endl;
    
    // Example 8: Complex lambda composition
    cout << "8. Complex Lambda Composition:" << endl;
    auto compose = [](auto f, auto g) {
        return [f, g](auto x) { return f(g(x)); };
    };
    
    auto square = [](int x) { return x * x; };
    auto addOne = [](int x) { return x + 1; };
    
    auto composed = compose(square, addOne);
    cout << "Composed result: " << composed(5) << endl;
    cout << endl;
    
    // Example 9: Lambda with variant
    cout << "9. Lambda with Variant:" << endl;
    variant<int, string, double> v = 42;
    
    auto visitor = [](const auto& value) {
        cout << "Value: " << value << " (type: " << typeid(value).name() << ")" << endl;
    };
    
    visit(visitor, v);
    cout << endl;
    
    // Example 10: Lambda with thread safety
    cout << "10. Lambda with Thread Safety:" << endl;
    atomic<int> counter{0};
    mutex printMutex;
    
    auto threadSafeLambda = [&counter, &printMutex](int id) {
        for (int i = 0; i < 5; ++i) {
            counter.fetch_add(1);
            {
                lock_guard<mutex> lock(printMutex);
                cout << "Thread " << id << ": " << counter.load() << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    };
    
    vector<thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(threadSafeLambda, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "Final counter: " << counter.load() << endl;
    
    return 0;
}
