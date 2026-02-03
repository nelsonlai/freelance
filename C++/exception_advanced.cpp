/*
 * EXCEPTION HANDLING ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced exception handling concepts:
 * - Exception_ptr and cross-thread exceptions
 * - Function try blocks
 * - Exception translation
 * - Performance considerations
 * - Custom exception handlers
 * - std::current_exception and std::rethrow_exception
 * - Exception-safe algorithms
 * - Advanced RAII patterns
 * - Exception specifications in templates
 * - Best practices for production code
 * 
 * Learning Objectives:
 * - Master advanced exception handling techniques
 * - Understand performance implications
 * - Handle exceptions across thread boundaries
 * - Write production-quality exception-safe code
 * - Implement advanced error handling patterns
 * 
 * Prerequisites:
 * - Completed exception_beginner.cpp and exception_intermediate.cpp
 * - Understanding of C++ templates
 * - Familiarity with move semantics
 * - Understanding of threading basics
 * 
 * Key Topics Covered:
 * - std::exception_ptr
 * - Function try blocks
 * - Exception translation patterns
 * - Performance optimization
 * - Advanced RAII
 * - Production best practices
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>
#include <memory>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <chrono>
#include <mutex>
using namespace std;

// ==============================================================================
// SECTION 1: std::exception_ptr
// ==============================================================================
/*
 * STD::EXCEPTION_PTR (C++11):
 * 
 * Type-erased pointer to exception object.
 * 
 * Uses:
 * - Store exceptions for later handling
 * - Transfer exceptions between threads
 * - Implement deferred exception handling
 * - Store multiple exceptions
 * 
 * Key functions:
 * - std::current_exception() - capture current exception
 * - std::rethrow_exception() - rethrow stored exception
 * - std::make_exception_ptr() - create exception_ptr without throwing
 */

void exceptionPtrBasics() {
    cout << "=== STD::EXCEPTION_PTR ===" << endl << endl;
    
    // Example 1: Capturing and rethrowing
    cout << "1. Capturing and Rethrowing:" << endl;
    exception_ptr eptr;
    
    try {
        throw runtime_error("Original error");
    } catch (...) {
        eptr = current_exception();  // Capture exception
        cout << "   Exception captured" << endl;
    }
    
    // Rethrow later
    try {
        if (eptr) {
            rethrow_exception(eptr);
        }
    } catch (runtime_error& e) {
        cout << "   Rethrown and caught: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 2: make_exception_ptr
    cout << "2. make_exception_ptr (no throw):" << endl;
    exception_ptr eptr2 = make_exception_ptr(logic_error("Logic error"));
    
    try {
        rethrow_exception(eptr2);
    } catch (logic_error& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 3: Storing multiple exceptions
    cout << "3. Storing Multiple Exceptions:" << endl;
    vector<exception_ptr> exceptions;
    
    for (int i = 0; i < 3; i++) {
        try {
            if (i == 0) throw runtime_error("Error 0");
            if (i == 1) throw logic_error("Error 1");
            if (i == 2) throw invalid_argument("Error 2");
        } catch (...) {
            exceptions.push_back(current_exception());
        }
    }
    
    cout << "   Processing stored exceptions:" << endl;
    for (size_t i = 0; i < exceptions.size(); i++) {
        try {
            rethrow_exception(exceptions[i]);
        } catch (exception& e) {
            cout << "   Exception " << i << ": " << e.what() << endl;
        }
    }
    cout << endl;
}

// ==============================================================================
// SECTION 2: CROSS-THREAD EXCEPTION HANDLING
// ==============================================================================
/*
 * EXCEPTIONS AND THREADS:
 * 
 * Problem: Exceptions can't cross thread boundaries
 * Solution: Use exception_ptr to transfer exceptions
 * 
 * Patterns:
 * - Capture in worker thread
 * - Store in shared location
 * - Rethrow in main thread
 * 
 * std::future automatically handles this!
 */

void workerFunction(exception_ptr& eptr, int value) {
    try {
        if (value < 0) {
            throw invalid_argument("Value must be non-negative");
        }
        cout << "   Worker: Processing value " << value << endl;
    } catch (...) {
        eptr = current_exception();
    }
}

int taskWithException(int value) {
    if (value < 0) {
        throw runtime_error("Negative value in task");
    }
    return value * 2;
}

void crossThreadExceptions() {
    cout << "=== CROSS-THREAD EXCEPTION HANDLING ===" << endl << endl;
    
    // Example 1: Manual exception transfer
    cout << "1. Manual Exception Transfer:" << endl;
    exception_ptr eptr;
    thread worker(workerFunction, ref(eptr), -5);
    worker.join();
    
    if (eptr) {
        try {
            rethrow_exception(eptr);
        } catch (exception& e) {
            cout << "   Main thread caught: " << e.what() << endl;
        }
    }
    cout << endl;
    
    // Example 2: Using std::future (automatic)
    cout << "2. Using std::future (automatic):" << endl;
    auto future = async(launch::async, taskWithException, -10);
    
    try {
        int result = future.get();  // Exception rethrown here!
        cout << "   Result: " << result << endl;
    } catch (runtime_error& e) {
        cout << "   Caught from future: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 3: Multiple threads with exceptions
    cout << "3. Multiple Threads:" << endl;
    vector<future<int>> futures;
    
    for (int i = -2; i <= 2; i++) {
        futures.push_back(async(launch::async, [i]() {
            if (i < 0) throw runtime_error("Negative: " + to_string(i));
            return i * i;
        }));
    }
    
    for (size_t i = 0; i < futures.size(); i++) {
        try {
            int result = futures[i].get();
            cout << "   Task " << i << " result: " << result << endl;
        } catch (exception& e) {
            cout << "   Task " << i << " failed: " << e.what() << endl;
        }
    }
    cout << endl;
}

// ==============================================================================
// SECTION 3: FUNCTION TRY BLOCKS
// ==============================================================================
/*
 * FUNCTION TRY BLOCKS:
 * 
 * Special syntax to catch exceptions from:
 * - Constructor initialization list
 * - Constructor body
 * - Member initialization
 * 
 * Syntax:
 * Constructor::Constructor() try : members() {
 *     // body
 * } catch (...) {
 *     // handle
 * }
 * 
 * Main use: Catching exceptions during member initialization
 */

class Resource {
public:
    Resource(int id) {
        if (id < 0) {
            throw invalid_argument("Invalid resource ID");
        }
        cout << "   Resource " << id << " created" << endl;
    }
};

class Container {
private:
    Resource resource1;
    Resource resource2;
    
public:
    // Function try block for constructor
    Container(int id1, int id2)
    try : resource1(id1), resource2(id2) {
        cout << "   Container body executing" << endl;
        // Constructor body
    } catch (invalid_argument& e) {
        cout << "   Caught in function try block: " << e.what() << endl;
        // Note: Exception is automatically rethrown!
        // throw;  // Implicit
    }
    
    // Can't prevent exception from propagating in constructor try blocks
};

class NormalClass {
private:
    Resource resource;
    
public:
    // Regular constructor (for comparison)
    NormalClass(int id) : resource(id) {
        // Can't catch exceptions from initialization list here
    }
};

void functionTryBlocks() {
    cout << "=== FUNCTION TRY BLOCKS ===" << endl << endl;
    
    // Example 1: Catching initialization exceptions
    cout << "1. Function Try Block:" << endl;
    try {
        Container c(10, -5);  // Second resource will throw
    } catch (invalid_argument& e) {
        cout << "   Main caught: " << e.what() << endl;
    }
    cout << endl;
    
    cout << "Note: Function try blocks automatically rethrow" << endl;
    cout << "Main use: Logging or cleanup during construction" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 4: EXCEPTION TRANSLATION
// ==============================================================================
/*
 * EXCEPTION TRANSLATION:
 * 
 * Converting one exception type to another.
 * 
 * Uses:
 * - Hide implementation details
 * - Provide domain-specific exceptions
 * - Cross library boundaries
 * - Unify error handling
 */

// Low-level library exception
class LowLevelError : public exception {
public:
    const char* what() const noexcept override {
        return "Low-level internal error";
    }
};

// High-level domain exception
class DomainError : public runtime_error {
public:
    DomainError(const string& msg) : runtime_error(msg) {}
};

// Low-level function
void lowLevelOperation() {
    throw LowLevelError();
}

// Translation layer
void domainOperation() {
    try {
        lowLevelOperation();
    } catch (LowLevelError& e) {
        // Translate to domain exception
        throw DomainError("Domain operation failed: " + string(e.what()));
    }
}

// Translation wrapper template
template<typename DomainException, typename F>
auto translateExceptions(F func) -> decltype(func()) {
    try {
        return func();
    } catch (exception& e) {
        throw DomainException("Translated: " + string(e.what()));
    }
}

void exceptionTranslation() {
    cout << "=== EXCEPTION TRANSLATION ===" << endl << endl;
    
    // Example 1: Manual translation
    cout << "1. Manual Translation:" << endl;
    try {
        domainOperation();
    } catch (DomainError& e) {
        cout << "   Caught domain error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 2: Generic translation wrapper
    cout << "2. Generic Translation Wrapper:" << endl;
    try {
        auto result = translateExceptions<DomainError>([]() {
            throw logic_error("Original error");
            return 42;
        });
    } catch (DomainError& e) {
        cout << "   Caught translated: " << e.what() << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 5: PERFORMANCE CONSIDERATIONS
// ==============================================================================
/*
 * EXCEPTION PERFORMANCE:
 * 
 * Modern implementations (zero-cost exceptions):
 * - No overhead when exception NOT thrown
 * - Significant overhead when exception IS thrown
 * 
 * Guidelines:
 * - Use for exceptional cases only
 * - Don't use in performance-critical hot paths
 * - Consider return codes for frequent errors
 * - Measure actual performance impact
 */

// Return code approach
int divideReturnCode(int a, int b, int& result) {
    if (b == 0) {
        return -1;  // Error code
    }
    result = a / b;
    return 0;  // Success
}

// Exception approach
int divideException(int a, int b) {
    if (b == 0) {
        throw invalid_argument("Division by zero");
    }
    return a / b;
}

void performanceConsiderations() {
    cout << "=== PERFORMANCE CONSIDERATIONS ===" << endl << endl;
    
    cout << "Exception Performance Characteristics:" << endl;
    cout << "   - Zero overhead when NOT thrown (modern compilers)" << endl;
    cout << "   - Significant overhead when thrown" << endl;
    cout << "   - Stack unwinding takes time" << endl;
    cout << "   - Constructor/destructor calls during unwinding" << endl;
    cout << endl;
    
    cout << "When to use return codes vs exceptions:" << endl;
    cout << endl;
    
    cout << "Use RETURN CODES for:" << endl;
    cout << "   ✓ Frequent errors (expected conditions)" << endl;
    cout << "   ✓ Performance-critical hot paths" << endl;
    cout << "   ✓ Simple validation" << endl;
    cout << "   ✓ Optional results" << endl;
    cout << endl;
    
    cout << "Use EXCEPTIONS for:" << endl;
    cout << "   ✓ Rare, exceptional conditions" << endl;
    cout << "   ✓ Errors that can't be handled locally" << endl;
    cout << "   ✓ Constructor failures" << endl;
    cout << "   ✓ Deeply nested call stacks" << endl;
    cout << endl;
    
    // Demonstrate both approaches
    cout << "Example - Return code approach:" << endl;
    int result;
    if (divideReturnCode(10, 2, result) == 0) {
        cout << "   Result: " << result << endl;
    }
    cout << endl;
    
    cout << "Example - Exception approach:" << endl;
    try {
        int res = divideException(10, 2);
        cout << "   Result: " << res << endl;
    } catch (...) {
        cout << "   Error occurred" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 6: EXCEPTION-SAFE ALGORITHMS
// ==============================================================================
/*
 * EXCEPTION-SAFE ALGORITHMS:
 * 
 * Techniques for writing algorithms that are exception-safe:
 * - Copy-and-swap idiom
 * - Two-phase operations
 * - Commit-or-rollback pattern
 * - Transactional semantics
 */

template<typename T>
class ExceptionSafeVector {
private:
    T* data;
    size_t capacity;
    size_t count;
    
public:
    ExceptionSafeVector() : data(nullptr), capacity(0), count(0) {}
    
    ~ExceptionSafeVector() {
        delete[] data;
    }
    
    // Copy constructor (strong guarantee)
    ExceptionSafeVector(const ExceptionSafeVector& other)
        : data(nullptr), capacity(0), count(0) {
        if (other.count > 0) {
            data = new T[other.capacity];  // May throw
            capacity = other.capacity;
            // If copy throws, destructor cleans up data
            for (size_t i = 0; i < other.count; i++) {
                data[i] = other.data[i];
            }
            count = other.count;
        }
    }
    
    // Copy assignment (strong guarantee using copy-and-swap)
    ExceptionSafeVector& operator=(const ExceptionSafeVector& other) {
        if (this != &other) {
            ExceptionSafeVector temp(other);  // May throw, but this unchanged
            swap(temp);                        // No-throw swap
        }
        return *this;
    }
    
    // No-throw swap
    void swap(ExceptionSafeVector& other) noexcept {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(count, other.count);
    }
    
    // Strong guarantee push_back
    void push_back(const T& value) {
        if (count == capacity) {
            // Need to grow
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCapacity];  // May throw, original unchanged
            
            // Copy existing elements
            for (size_t i = 0; i < count; i++) {
                newData[i] = data[i];  // May throw, but newData will be cleaned up
            }
            
            // Add new element
            newData[count] = value;  // May throw, but newData will be cleaned up
            
            // Commit (no-throw operations from here)
            delete[] data;
            data = newData;
            capacity = newCapacity;
            count++;
        } else {
            data[count++] = value;
        }
    }
    
    size_t size() const noexcept { return count; }
    
    const T& operator[](size_t index) const {
        if (index >= count) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

void exceptionSafeAlgorithms() {
    cout << "=== EXCEPTION-SAFE ALGORITHMS ===" << endl << endl;
    
    cout << "1. Copy-and-Swap Idiom:" << endl;
    ExceptionSafeVector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    
    ExceptionSafeVector<int> vec2;
    vec2 = vec1;  // Uses copy-and-swap (strong guarantee)
    
    cout << "   Vector copied successfully" << endl;
    cout << "   Size: " << vec2.size() << endl;
    cout << endl;
    
    cout << "Key Techniques:" << endl;
    cout << "   ✓ Copy-and-swap for assignment" << endl;
    cout << "   ✓ Two-phase: prepare, then commit" << endl;
    cout << "   ✓ No-throw operations for commit phase" << endl;
    cout << "   ✓ RAII for automatic cleanup" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 7: ADVANCED RAII PATTERNS
// ==============================================================================
/*
 * ADVANCED RAII PATTERNS:
 * 
 * - Scope guards
 * - Scope exit handlers
 * - Transaction-like semantics
 * - Generic resource management
 */

// Simple scope guard
template<typename F>
class ScopeGuard {
private:
    F func;
    bool active;
    
public:
    ScopeGuard(F f) : func(std::move(f)), active(true) {}
    
    ~ScopeGuard() {
        if (active) {
            try {
                func();
            } catch (...) {
                // Don't let exceptions escape destructor
            }
        }
    }
    
    void dismiss() { active = false; }
    
    // Prevent copying
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
};

// Helper function to create scope guards
template<typename F>
ScopeGuard<F> makeScopeGuard(F f) {
    return ScopeGuard<F>(std::move(f));
}

// Transaction-like class
template<typename T>
class Transaction {
private:
    T& resource;
    T backup;
    bool committed;
    
public:
    Transaction(T& res) : resource(res), backup(res), committed(false) {}
    
    ~Transaction() {
        if (!committed) {
            // Rollback on exception
            resource = backup;
            cout << "   Transaction rolled back" << endl;
        }
    }
    
    void commit() {
        committed = true;
        cout << "   Transaction committed" << endl;
    }
};

void advancedRaiiPatterns() {
    cout << "=== ADVANCED RAII PATTERNS ===" << endl << endl;
    
    // Example 1: Scope guard
    cout << "1. Scope Guard:" << endl;
    {
        bool resourceAcquired = false;
        auto guard = makeScopeGuard([&]() {
            if (resourceAcquired) {
                cout << "   Scope guard: Cleaning up resource" << endl;
            }
        });
        
        cout << "   Acquiring resource..." << endl;
        resourceAcquired = true;
        
        // Resource automatically cleaned up when guard destroyed
    }
    cout << endl;
    
    // Example 2: Dismissed scope guard
    cout << "2. Dismissed Scope Guard:" << endl;
    {
        auto guard = makeScopeGuard([]() {
            cout << "   This won't print (dismissed)" << endl;
        });
        
        cout << "   Operation successful" << endl;
        guard.dismiss();  // Don't execute cleanup
    }
    cout << endl;
    
    // Example 3: Transaction pattern
    cout << "3. Transaction Pattern:" << endl;
    int value = 100;
    cout << "   Initial value: " << value << endl;
    
    try {
        Transaction<int> trans(value);
        value = 200;
        cout << "   Modified value: " << value << endl;
        throw runtime_error("Simulated error");
        trans.commit();  // Won't reach here
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << "   Final value: " << value << " (rolled back)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 8: EXCEPTION SPECIFICATIONS IN TEMPLATES
// ==============================================================================
/*
 * CONDITIONAL NOEXCEPT:
 * 
 * noexcept can depend on template parameters:
 * - noexcept(expression)
 * - noexcept(noexcept(expression))
 * 
 * Enables perfect exception propagation in templates.
 */

template<typename T>
class Container {
private:
    T value;
    
public:
    // Constructor noexcept if T's constructor is noexcept
    Container(const T& v) noexcept(noexcept(T(v))) : value(v) {}
    
    // Swap noexcept if T's swap is noexcept
    void swap(Container& other) noexcept(noexcept(std::swap(value, other.value))) {
        std::swap(value, other.value);
    }
    
    // Move constructor noexcept if T's move is noexcept
    Container(Container&& other) noexcept(noexcept(T(std::move(other.value))))
        : value(std::move(other.value)) {}
    
    T getValue() const noexcept { return value; }
};

void templateExceptionSpecs() {
    cout << "=== EXCEPTION SPECIFICATIONS IN TEMPLATES ===" << endl << endl;
    
    cout << "Conditional noexcept:" << endl;
    cout << "   template<typename T>" << endl;
    cout << "   void func() noexcept(noexcept(T::operation())) {" << endl;
    cout << "       // noexcept if T::operation() is noexcept" << endl;
    cout << "   }" << endl;
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Propagates exception guarantees" << endl;
    cout << "   ✓ Enables optimizations" << endl;
    cout << "   ✓ Works with any type" << endl;
    cout << endl;
    
    Container<int> c1(42);
    Container<string> c2("test");
    cout << "   Containers created with proper noexcept guarantees" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 9: PRODUCTION BEST PRACTICES
// ==============================================================================
/*
 * PRODUCTION-QUALITY EXCEPTION HANDLING:
 * 
 * 1. Logging and diagnostics
 * 2. Error recovery strategies
 * 3. Exception hierarchy design
 * 4. Documentation
 * 5. Testing
 */

class Logger {
public:
    static void logError(const string& msg) {
        cout << "   [ERROR] " << msg << endl;
    }
    
    static void logException(const exception& e) {
        cout << "   [EXCEPTION] " << e.what() << endl;
    }
};

// Production-quality function with comprehensive error handling
class ProductionService {
public:
    void processRequest(int requestId) {
        try {
            validateRequest(requestId);
            executeRequest(requestId);
            commitResults(requestId);
            
        } catch (const invalid_argument& e) {
            Logger::logException(e);
            // Handle validation error
            handleValidationError(e);
            throw;  // Rethrow for caller
            
        } catch (const runtime_error& e) {
            Logger::logException(e);
            // Attempt recovery
            if (!attemptRecovery()) {
                throw;  // Rethrow if recovery failed
            }
            
        } catch (const exception& e) {
            Logger::logException(e);
            // Unknown exception - cleanup and rethrow
            cleanup();
            throw;
            
        } catch (...) {
            Logger::logError("Unknown exception type");
            cleanup();
            throw;
        }
    }
    
private:
    void validateRequest(int id) {
        if (id <= 0) {
            throw invalid_argument("Invalid request ID");
        }
    }
    
    void executeRequest(int id) {
        cout << "   Executing request " << id << endl;
    }
    
    void commitResults(int id) {
        cout << "   Committing results for request " << id << endl;
    }
    
    void handleValidationError(const exception& e) {
        cout << "   Handling validation error..." << endl;
    }
    
    bool attemptRecovery() {
        cout << "   Attempting recovery..." << endl;
        return false;  // Simulate failed recovery
    }
    
    void cleanup() {
        cout << "   Performing cleanup..." << endl;
    }
};

void productionBestPractices() {
    cout << "=== PRODUCTION BEST PRACTICES ===" << endl << endl;
    
    cout << "1. Comprehensive Error Handling:" << endl;
    ProductionService service;
    try {
        service.processRequest(-1);
    } catch (invalid_argument& e) {
        cout << "   Client handled: " << e.what() << endl;
    }
    cout << endl;
    
    cout << "Best Practices Summary:" << endl;
    cout << endl;
    
    cout << "1. Logging:" << endl;
    cout << "   ✓ Log all exceptions" << endl;
    cout << "   ✓ Include context (timestamp, request ID, etc.)" << endl;
    cout << "   ✓ Use structured logging" << endl;
    cout << endl;
    
    cout << "2. Recovery:" << endl;
    cout << "   ✓ Attempt recovery when possible" << endl;
    cout << "   ✓ Have fallback strategies" << endl;
    cout << "   ✓ Document recovery behavior" << endl;
    cout << endl;
    
    cout << "3. Documentation:" << endl;
    cout << "   ✓ Document what exceptions can be thrown" << endl;
    cout << "   ✓ Document exception safety guarantees" << endl;
    cout << "   ✓ Provide usage examples" << endl;
    cout << endl;
    
    cout << "4. Testing:" << endl;
    cout << "   ✓ Test exception paths" << endl;
    cout << "   ✓ Test resource cleanup" << endl;
    cout << "   ✓ Test recovery mechanisms" << endl;
    cout << "   ✓ Use fault injection" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: COMPREHENSIVE BEST PRACTICES
// ==============================================================================

void comprehensiveBestPractices() {
    cout << "=== COMPREHENSIVE BEST PRACTICES ===" << endl << endl;
    
    cout << "Exception Design:" << endl;
    cout << "   ✓ Create exception hierarchy for your domain" << endl;
    cout << "   ✓ Derive from std::exception" << endl;
    cout << "   ✓ Include relevant context in exceptions" << endl;
    cout << "   ✓ Use descriptive names" << endl;
    cout << endl;
    
    cout << "Exception Safety:" << endl;
    cout << "   ✓ Use RAII for all resources" << endl;
    cout << "   ✓ Aim for strong guarantee" << endl;
    cout << "   ✓ At minimum, provide basic guarantee" << endl;
    cout << "   ✓ Mark non-throwing operations noexcept" << endl;
    cout << "   ✓ NEVER throw from destructors" << endl;
    cout << endl;
    
    cout << "Performance:" << endl;
    cout << "   ✓ Use exceptions for exceptional cases only" << endl;
    cout << "   ✓ Use return codes for frequent errors" << endl;
    cout << "   ✓ Minimize exception throwing in hot paths" << endl;
    cout << "   ✓ Profile actual performance impact" << endl;
    cout << endl;
    
    cout << "Error Handling:" << endl;
    cout << "   ✓ Catch specific exceptions first" << endl;
    cout << "   ✓ Catch by reference (const if possible)" << endl;
    cout << "   ✓ Log before rethrowing" << endl;
    cout << "   ✓ Don't catch and ignore" << endl;
    cout << "   ✓ Use exception translation at boundaries" << endl;
    cout << endl;
    
    cout << "Threading:" << endl;
    cout << "   ✓ Use exception_ptr for cross-thread exceptions" << endl;
    cout << "   ✓ Prefer std::future for async exceptions" << endl;
    cout << "   ✓ Document thread safety" << endl;
    cout << endl;
    
    cout << "Modern C++ Features:" << endl;
    cout << "   ✓ Use noexcept specification" << endl;
    cout << "   ✓ Use smart pointers (RAII)" << endl;
    cout << "   ✓ Use exception_ptr when needed" << endl;
    cout << "   ✓ Use nested exceptions for context" << endl;
    cout << "   ✓ Use scope guards for cleanup" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║      EXCEPTION HANDLING ADVANCED TUTORIAL - C++            ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Master production-level exception handling techniques    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    exceptionPtrBasics();
    crossThreadExceptions();
    functionTryBlocks();
    exceptionTranslation();
    performanceConsiderations();
    exceptionSafeAlgorithms();
    advancedRaiiPatterns();
    templateExceptionSpecs();
    productionBestPractices();
    comprehensiveBestPractices();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of Exception Handling Advanced Tutorial               ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  You now have mastery of C++ exception handling!           ║" << endl;
    cout << "║  Apply these techniques in production code.                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

