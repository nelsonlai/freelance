#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <stdexcept>

// Demonstrates debugging and testing techniques
int main() {
    std::cout << "Debugging and Testing Demonstration" << std::endl;
    std::cout << "===================================" << std::endl;
    
    // 1. Unit Testing Framework
    std::cout << "\n1. UNIT TESTING FRAMEWORK:" << std::endl;
    
    // Simple test framework implementation
    class TestFramework {
    private:
        static int tests_run;
        static int tests_passed;
        static int tests_failed;
        
    public:
        static void run_test(const std::string& test_name, std::function<bool()> test_func) {
            tests_run++;
            std::cout << "  Running test: " << test_name << " ... ";
            
            try {
                if (test_func()) {
                    tests_passed++;
                    std::cout << "PASSED" << std::endl;
                } else {
                    tests_failed++;
                    std::cout << "FAILED" << std::endl;
                }
            } catch (const std::exception& e) {
                tests_failed++;
                std::cout << "FAILED (exception: " << e.what() << ")" << std::endl;
            }
        }
        
        static void print_summary() {
            std::cout << "\n  Test Summary:" << std::endl;
            std::cout << "    Total tests: " << tests_run << std::endl;
            std::cout << "    Passed: " << tests_passed << std::endl;
            std::cout << "    Failed: " << tests_failed << std::endl;
            std::cout << "    Success rate: " << (tests_passed * 100.0 / tests_run) << "%" << std::endl;
        }
    };
    
    int TestFramework::tests_run = 0;
    int TestFramework::tests_passed = 0;
    int TestFramework::tests_failed = 0;
    
    // Test cases
    TestFramework::run_test("Addition Test", []() {
        return (2 + 3) == 5;
    });
    
    TestFramework::run_test("String Test", []() {
        std::string str = "Hello";
        return str.length() == 5;
    });
    
    TestFramework::run_test("Vector Test", []() {
        std::vector<int> vec = {1, 2, 3};
        return vec.size() == 3;
    });
    
    TestFramework::run_test("Exception Test", []() {
        try {
            throw std::runtime_error("Test exception");
            return false;
        } catch (const std::exception&) {
            return true;
        }
    });
    
    TestFramework::print_summary();
    
    // 2. Assertions and Preconditions
    std::cout << "\n2. ASSERTIONS AND PRECONDITIONS:" << std::endl;
    
    // Custom assertion macro
    #define ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                std::cerr << "Assertion failed: " << message << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
                std::abort(); \
            } \
        } while(0)
    
    // Test assertions
    int value = 42;
    ASSERT(value > 0, "Value must be positive");
    ASSERT(value < 100, "Value must be less than 100");
    
    std::cout << "  Assertions passed" << std::endl;
    
    // Precondition checking
    auto safe_divide = [](double a, double b) -> double {
        ASSERT(b != 0, "Division by zero");
        return a / b;
    };
    
    try {
        double result = safe_divide(10.0, 2.0);
        std::cout << "  Safe division result: " << result << std::endl;
    } catch (...) {
        std::cout << "  Division failed" << std::endl;
    }
    
    // 3. Debugging Techniques
    std::cout << "\n3. DEBUGGING TECHNIQUES:" << std::endl;
    
    // Debug logging
    class DebugLogger {
    private:
        static bool debug_enabled;
        
    public:
        static void enable_debug(bool enable) {
            debug_enabled = enable;
        }
        
        static void log(const std::string& message) {
            if (debug_enabled) {
                std::cout << "  DEBUG: " << message << std::endl;
            }
        }
        
        static void log_variable(const std::string& name, const auto& value) {
            if (debug_enabled) {
                std::cout << "  DEBUG: " << name << " = " << value << std::endl;
            }
        }
    };
    
    bool DebugLogger::debug_enabled = true;
    
    DebugLogger::log("Starting debug session");
    DebugLogger::log_variable("value", 42);
    DebugLogger::log_variable("pi", 3.14159);
    
    // Conditional compilation for debug
    #ifdef DEBUG
    std::cout << "  Debug build - extra checks enabled" << std::endl;
    #else
    std::cout << "  Release build - optimizations enabled" << std::endl;
    #endif
    
    // 4. Memory Debugging
    std::cout << "\n4. MEMORY DEBUGGING:" << std::endl;
    
    // Memory leak detection
    class MemoryTracker {
    private:
        static std::atomic<int> allocations;
        static std::atomic<int> deallocations;
        
    public:
        static void track_allocation() {
            allocations.fetch_add(1);
        }
        
        static void track_deallocation() {
            deallocations.fetch_add(1);
        }
        
        static void print_status() {
            std::cout << "  Allocations: " << allocations.load() << std::endl;
            std::cout << "  Deallocations: " << deallocations.load() << std::endl;
            std::cout << "  Potential leaks: " << (allocations.load() - deallocations.load()) << std::endl;
        }
    };
    
    std::atomic<int> MemoryTracker::allocations{0};
    std::atomic<int> MemoryTracker::deallocations{0};
    
    // Track memory operations
    MemoryTracker::track_allocation();
    int* ptr = new int(42);
    MemoryTracker::track_deallocation();
    delete ptr;
    
    MemoryTracker::print_status();
    
    // 5. Performance Testing
    std::cout << "\n5. PERFORMANCE TESTING:" << std::endl;
    
    // Benchmarking utility
    class Benchmark {
    public:
        template<typename Func>
        static auto measure(Func func) {
            auto start = std::chrono::high_resolution_clock::now();
            auto result = func();
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "  Execution time: " << duration.count() << " microseconds" << std::endl;
            
            return result;
        }
    };
    
    // Benchmark different algorithms
    std::vector<int> test_data(10000);
    std::iota(test_data.begin(), test_data.end(), 0);
    
    auto result1 = Benchmark::measure([&]() {
        std::vector<int> copy = test_data;
        std::sort(copy.begin(), copy.end());
        return copy.size();
    });
    
    auto result2 = Benchmark::measure([&]() {
        std::vector<int> copy = test_data;
        std::stable_sort(copy.begin(), copy.end());
        return copy.size();
    });
    
    std::cout << "  Sort results: " << result1 << ", " << result2 << std::endl;
    
    // 6. Test-Driven Development
    std::cout << "\n6. TEST-DRIVEN DEVELOPMENT:" << std::endl;
    
    // Simple calculator class for TDD example
    class Calculator {
    public:
        int add(int a, int b) {
            return a + b;
        }
        
        int subtract(int a, int b) {
            return a - b;
        }
        
        int multiply(int a, int b) {
            return a * b;
        }
        
        double divide(double a, double b) {
            if (b == 0) {
                throw std::invalid_argument("Division by zero");
            }
            return a / b;
        }
    };
    
    Calculator calc;
    
    // Test cases for calculator
    TestFramework::run_test("Calculator Add", [&]() {
        return calc.add(2, 3) == 5;
    });
    
    TestFramework::run_test("Calculator Subtract", [&]() {
        return calc.subtract(5, 3) == 2;
    });
    
    TestFramework::run_test("Calculator Multiply", [&]() {
        return calc.multiply(4, 5) == 20;
    });
    
    TestFramework::run_test("Calculator Divide", [&]() {
        return calc.divide(10.0, 2.0) == 5.0;
    });
    
    TestFramework::run_test("Calculator Divide by Zero", [&]() {
        try {
            calc.divide(10.0, 0.0);
            return false;
        } catch (const std::invalid_argument&) {
            return true;
        }
    });
    
    // 7. Mock Objects
    std::cout << "\n7. MOCK OBJECTS:" << std::endl;
    
    // Interface for dependency injection
    class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual void log(const std::string& message) = 0;
    };
    
    // Mock logger for testing
    class MockLogger : public ILogger {
    private:
        std::vector<std::string> logged_messages;
        
    public:
        void log(const std::string& message) override {
            logged_messages.push_back(message);
        }
        
        const std::vector<std::string>& get_messages() const {
            return logged_messages;
        }
        
        void clear() {
            logged_messages.clear();
        }
    };
    
    // Service that uses logger
    class Service {
    private:
        std::shared_ptr<ILogger> logger;
        
    public:
        Service(std::shared_ptr<ILogger> logger) : logger(logger) {}
        
        void do_work() {
            logger->log("Starting work");
            logger->log("Work completed");
        }
    };
    
    // Test with mock
    auto mock_logger = std::make_shared<MockLogger>();
    Service service(mock_logger);
    
    service.do_work();
    
    const auto& messages = mock_logger->get_messages();
    std::cout << "  Logged messages: " << messages.size() << std::endl;
    for (const auto& msg : messages) {
        std::cout << "    " << msg << std::endl;
    }
    
    // 8. Integration Testing
    std::cout << "\n8. INTEGRATION TESTING:" << std::endl;
    
    // Database interface
    class IDatabase {
    public:
        virtual ~IDatabase() = default;
        virtual void save(const std::string& key, const std::string& value) = 0;
        virtual std::string load(const std::string& key) = 0;
    };
    
    // In-memory database for testing
    class InMemoryDatabase : public IDatabase {
    private:
        std::map<std::string, std::string> data;
        
    public:
        void save(const std::string& key, const std::string& value) override {
            data[key] = value;
        }
        
        std::string load(const std::string& key) override {
            auto it = data.find(key);
            if (it != data.end()) {
                return it->second;
            }
            throw std::runtime_error("Key not found");
        }
    };
    
    // Service that uses database
    class DataService {
    private:
        std::shared_ptr<IDatabase> database;
        
    public:
        DataService(std::shared_ptr<IDatabase> db) : database(db) {}
        
        void store_data(const std::string& key, const std::string& value) {
            database->save(key, value);
        }
        
        std::string retrieve_data(const std::string& key) {
            return database->load(key);
        }
    };
    
    // Integration test
    auto db = std::make_shared<InMemoryDatabase>();
    DataService data_service(db);
    
    data_service.store_data("test_key", "test_value");
    std::string retrieved = data_service.retrieve_data("test_key");
    
    TestFramework::run_test("Integration Test", [&]() {
        return retrieved == "test_value";
    });
    
    // 9. Error Handling Testing
    std::cout << "\n9. ERROR HANDLING TESTING:" << std::endl;
    
    // Function that can throw different exceptions
    auto risky_function = [](int input) -> int {
        if (input < 0) {
            throw std::invalid_argument("Input must be non-negative");
        }
        if (input > 100) {
            throw std::out_of_range("Input too large");
        }
        if (input == 42) {
            throw std::runtime_error("Special case");
        }
        return input * 2;
    };
    
    // Test different error conditions
    TestFramework::run_test("Negative Input Error", []() {
        try {
            risky_function(-1);
            return false;
        } catch (const std::invalid_argument&) {
            return true;
        }
    });
    
    TestFramework::run_test("Large Input Error", []() {
        try {
            risky_function(101);
            return false;
        } catch (const std::out_of_range&) {
            return true;
        }
    });
    
    TestFramework::run_test("Special Case Error", []() {
        try {
            risky_function(42);
            return false;
        } catch (const std::runtime_error&) {
            return true;
        }
    });
    
    TestFramework::run_test("Normal Operation", []() {
        try {
            int result = risky_function(10);
            return result == 20;
        } catch (...) {
            return false;
        }
    });
    
    // 10. Test Coverage
    std::cout << "\n10. TEST COVERAGE:" << std::endl;
    
    // Simple function with multiple branches
    auto coverage_function = [](int x, int y) -> int {
        if (x > 0 && y > 0) {
            return x + y;
        } else if (x < 0 && y < 0) {
            return x - y;
        } else if (x == 0 || y == 0) {
            return 0;
        } else {
            return x * y;
        }
    };
    
    // Test all branches
    TestFramework::run_test("Coverage - Both Positive", []() {
        return coverage_function(5, 3) == 8;
    });
    
    TestFramework::run_test("Coverage - Both Negative", []() {
        return coverage_function(-5, -3) == -2;
    });
    
    TestFramework::run_test("Coverage - One Zero", []() {
        return coverage_function(0, 5) == 0;
    });
    
    TestFramework::run_test("Coverage - Mixed Signs", []() {
        return coverage_function(5, -3) == -15;
    });
    
    // 11. Continuous Integration
    std::cout << "\n11. CONTINUOUS INTEGRATION:" << std::endl;
    
    // Simulate CI pipeline
    class CIPipeline {
    public:
        static bool run_tests() {
            std::cout << "  Running unit tests..." << std::endl;
            // Simulate test execution
            return true;
        }
        
        static bool run_integration_tests() {
            std::cout << "  Running integration tests..." << std::endl;
            // Simulate integration test execution
            return true;
        }
        
        static bool run_performance_tests() {
            std::cout << "  Running performance tests..." << std::endl;
            // Simulate performance test execution
            return true;
        }
        
        static bool build_project() {
            std::cout << "  Building project..." << std::endl;
            // Simulate build process
            return true;
        }
        
        static void run_pipeline() {
            std::cout << "  Starting CI pipeline..." << std::endl;
            
            if (!build_project()) {
                std::cout << "  Build failed!" << std::endl;
                return;
            }
            
            if (!run_tests()) {
                std::cout << "  Unit tests failed!" << std::endl;
                return;
            }
            
            if (!run_integration_tests()) {
                std::cout << "  Integration tests failed!" << std::endl;
                return;
            }
            
            if (!run_performance_tests()) {
                std::cout << "  Performance tests failed!" << std::endl;
                return;
            }
            
            std::cout << "  All tests passed! Pipeline successful." << std::endl;
        }
    };
    
    CIPipeline::run_pipeline();
    
    // 12. Best Practices
    std::cout << "\n12. BEST PRACTICES:" << std::endl;
    
    // Test naming conventions
    class TestNaming {
    public:
        static void test_addition_should_return_correct_sum() {
            Calculator calc;
            ASSERT(calc.add(2, 3) == 5, "Addition should return correct sum");
        }
        
        static void test_division_by_zero_should_throw_exception() {
            Calculator calc;
            try {
                calc.divide(10.0, 0.0);
                ASSERT(false, "Division by zero should throw exception");
            } catch (const std::invalid_argument&) {
                // Expected behavior
            }
        }
        
        static void test_empty_vector_should_have_zero_size() {
            std::vector<int> vec;
            ASSERT(vec.size() == 0, "Empty vector should have zero size");
        }
    };
    
    TestNaming::test_addition_should_return_correct_sum();
    TestNaming::test_division_by_zero_should_throw_exception();
    TestNaming::test_empty_vector_should_have_zero_size();
    
    std::cout << "  All naming convention tests passed" << std::endl;
    
    // 13. Test Automation
    std::cout << "\n13. TEST AUTOMATION:" << std::endl;
    
    // Automated test runner
    class TestRunner {
    public:
        static void run_all_tests() {
            std::cout << "  Running automated test suite..." << std::endl;
            
            // Collect all test functions
            std::vector<std::function<void()>> tests = {
                TestNaming::test_addition_should_return_correct_sum,
                TestNaming::test_division_by_zero_should_throw_exception,
                TestNaming::test_empty_vector_should_have_zero_size
            };
            
            int passed = 0;
            int failed = 0;
            
            for (auto& test : tests) {
                try {
                    test();
                    passed++;
                } catch (...) {
                    failed++;
                }
            }
            
            std::cout << "  Automated tests completed: " << passed << " passed, " << failed << " failed" << std::endl;
        }
    };
    
    TestRunner::run_all_tests();
    
    // 14. Debugging Tools Integration
    std::cout << "\n14. DEBUGGING TOOLS INTEGRATION:" << std::endl;
    
    // GDB integration example
    class GDBIntegration {
    public:
        static void breakpoint_example() {
            int value = 42;
            std::cout << "  Value before breakpoint: " << value << std::endl;
            
            // In GDB, you would set a breakpoint here
            // (gdb) break GDBIntegration::breakpoint_example
            // (gdb) run
            
            value *= 2;
            std::cout << "  Value after breakpoint: " << value << std::endl;
        }
        
        static void watchpoint_example() {
            int watched_value = 0;
            std::cout << "  Setting watchpoint on watched_value" << std::endl;
            
            // In GDB, you would set a watchpoint here
            // (gdb) watch watched_value
            // (gdb) continue
            
            for (int i = 0; i < 5; ++i) {
                watched_value = i;
                std::cout << "  watched_value changed to: " << watched_value << std::endl;
            }
        }
    };
    
    GDBIntegration::breakpoint_example();
    GDBIntegration::watchpoint_example();
    
    // 15. Test Documentation
    std::cout << "\n15. TEST DOCUMENTATION:" << std::endl;
    
    // Test documentation example
    /**
     * @brief Test suite for Calculator class
     * 
     * This test suite verifies the correctness of the Calculator class
     * implementation, including:
     * - Basic arithmetic operations
     * - Error handling for edge cases
     * - Boundary value testing
     * 
     * @test Test addition of positive numbers
     * @test Test subtraction with negative results
     * @test Test multiplication with zero
     * @test Test division by zero exception
     * 
     * @author Test Suite Generator
     * @version 1.0
     * @since 2024
     */
    class CalculatorTestSuite {
    public:
        static void run_all_tests() {
            std::cout << "  Running Calculator test suite..." << std::endl;
            
            Calculator calc;
            
            // Test addition
            ASSERT(calc.add(2, 3) == 5, "Addition test failed");
            
            // Test subtraction
            ASSERT(calc.subtract(5, 3) == 2, "Subtraction test failed");
            
            // Test multiplication
            ASSERT(calc.multiply(4, 5) == 20, "Multiplication test failed");
            
            // Test division
            ASSERT(calc.divide(10.0, 2.0) == 5.0, "Division test failed");
            
            std::cout << "  All Calculator tests passed" << std::endl;
        }
    };
    
    CalculatorTestSuite::run_all_tests();
    
    std::cout << "\nDebugging and testing demonstration completed!" << std::endl;
    return 0;
}
