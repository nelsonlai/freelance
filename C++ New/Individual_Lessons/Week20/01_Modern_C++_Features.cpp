/*
 * Lesson 20.1: Modern C++ Features
 * 
 * This file demonstrates modern C++ features including
 * C++17 and C++20 features, concepts, modules, coroutines,
 * and advanced language features.
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

// Example 1: C++17 Features
namespace Cpp17Features {
    
    // Structured bindings
    void demonstrateStructuredBindings() {
        std::cout << "=== C++17 Structured Bindings ===" << std::endl;
        
        // Pair structured binding
        auto [key, value] = std::make_pair(42, "Hello");
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
        
        // Tuple structured binding
        auto [a, b, c] = std::make_tuple(1, 2.5, std::string("Test"));
        std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
        
        // Array structured binding
        int arr[] = {1, 2, 3, 4, 5};
        auto [first, second, third, fourth, fifth] = arr;
        std::cout << "Array elements: " << first << ", " << second << ", " << third << ", " << fourth << ", " << fifth << std::endl;
        
        // Map structured binding
        std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
        for (const auto& [name, score] : scores) {
            std::cout << name << ": " << score << std::endl;
        }
    }
    
    // if constexpr
    template<typename T>
    void process_value(T&& value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Processing integer: " << value << std::endl;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "Processing floating point: " << value << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "Processing string: " << value << std::endl;
        } else {
            std::cout << "Processing unknown type" << std::endl;
        }
    }
    
    void demonstrateIfConstexpr() {
        std::cout << "\n=== C++17 if constexpr ===" << std::endl;
        
        process_value(42);
        process_value(3.14);
        process_value(std::string("Hello"));
        process_value(std::vector<int>{1, 2, 3});
    }
    
    // std::optional
    std::optional<int> find_value(const std::vector<int>& vec, int target) {
        auto it = std::find(vec.begin(), vec.end(), target);
        if (it != vec.end()) {
            return *it;
        }
        return std::nullopt;
    }
    
    void demonstrateOptional() {
        std::cout << "\n=== C++17 std::optional ===" << std::endl;
        
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        
        auto result1 = find_value(numbers, 3);
        if (result1) {
            std::cout << "Found value: " << *result1 << std::endl;
        } else {
            std::cout << "Value not found" << std::endl;
        }
        
        auto result2 = find_value(numbers, 10);
        if (result2) {
            std::cout << "Found value: " << *result2 << std::endl;
        } else {
            std::cout << "Value not found" << std::endl;
        }
        
        // Using value_or
        int value = find_value(numbers, 10).value_or(-1);
        std::cout << "Value or default: " << value << std::endl;
    }
    
    // std::variant
    std::variant<int, std::string, double> get_value(int type) {
        switch (type) {
            case 0: return 42;
            case 1: return std::string("Hello");
            case 2: return 3.14;
            default: return 0;
        }
    }
    
    void demonstrateVariant() {
        std::cout << "\n=== C++17 std::variant ===" << std::endl;
        
        auto value1 = get_value(0);
        std::visit([](const auto& v) {
            std::cout << "Value: " << v << std::endl;
        }, value1);
        
        auto value2 = get_value(1);
        if (std::holds_alternative<std::string>(value2)) {
            std::cout << "String value: " << std::get<std::string>(value2) << std::endl;
        }
        
        auto value3 = get_value(2);
        if (std::holds_alternative<double>(value3)) {
            std::cout << "Double value: " << std::get<double>(value3) << std::endl;
        }
    }
    
    // std::any
    void demonstrateAny() {
        std::cout << "\n=== C++17 std::any ===" << std::endl;
        
        std::any value;
        
        value = 42;
        std::cout << "Integer value: " << std::any_cast<int>(value) << std::endl;
        
        value = std::string("Hello");
        std::cout << "String value: " << std::any_cast<std::string>(value) << std::endl;
        
        value = 3.14;
        std::cout << "Double value: " << std::any_cast<double>(value) << std::endl;
        
        // Check type
        if (value.type() == typeid(double)) {
            std::cout << "Value is a double" << std::endl;
        }
    }
    
    // std::string_view
    void demonstrateStringView() {
        std::cout << "\n=== C++17 std::string_view ===" << std::endl;
        
        std::string str = "Hello, World!";
        std::string_view view(str);
        
        std::cout << "String view: " << view << std::endl;
        std::cout << "Length: " << view.length() << std::endl;
        std::cout << "Substring: " << view.substr(0, 5) << std::endl;
        
        // String view doesn't own the data
        std::string_view literal_view = "Literal string";
        std::cout << "Literal view: " << literal_view << std::endl;
    }
    
    // Parallel algorithms
    void demonstrateParallelAlgorithms() {
        std::cout << "\n=== C++17 Parallel Algorithms ===" << std::endl;
        
        std::vector<int> numbers(1000000);
        std::iota(numbers.begin(), numbers.end(), 1);
        
        // Sequential sort
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(numbers.begin(), numbers.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto sequential_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        // Shuffle for parallel test
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(numbers.begin(), numbers.end(), g);
        
        // Parallel sort
        start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, numbers.begin(), numbers.end());
        end = std::chrono::high_resolution_clock::now();
        auto parallel_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Sequential sort time: " << sequential_time.count() << " ms" << std::endl;
        std::cout << "Parallel sort time: " << parallel_time.count() << " ms" << std::endl;
        
        // Parallel transform
        std::vector<int> squares(numbers.size());
        std::transform(std::execution::par, numbers.begin(), numbers.end(), squares.begin(),
                      [](int n) { return n * n; });
        
        std::cout << "First 10 squares: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << squares[i] << " ";
        }
        std::cout << std::endl;
    }
    
    // Filesystem
    void demonstrateFilesystem() {
        std::cout << "\n=== C++17 Filesystem ===" << std::endl;
        
        namespace fs = std::filesystem;
        
        try {
            // Create directory
            fs::create_directory("test_dir");
            std::cout << "Created directory: test_dir" << std::endl;
            
            // Create file
            std::ofstream file("test_dir/test_file.txt");
            file << "Hello, World!" << std::endl;
            file.close();
            std::cout << "Created file: test_dir/test_file.txt" << std::endl;
            
            // Check if path exists
            if (fs::exists("test_dir/test_file.txt")) {
                std::cout << "File exists" << std::endl;
                
                // Get file size
                auto size = fs::file_size("test_dir/test_file.txt");
                std::cout << "File size: " << size << " bytes" << std::endl;
                
                // Get file permissions
                auto perms = fs::status("test_dir/test_file.txt").permissions();
                std::cout << "File permissions: " << std::oct << static_cast<int>(perms) << std::endl;
            }
            
            // Iterate directory
            std::cout << "Directory contents:" << std::endl;
            for (const auto& entry : fs::directory_iterator("test_dir")) {
                std::cout << "  " << entry.path().filename() << std::endl;
            }
            
            // Clean up
            fs::remove_all("test_dir");
            std::cout << "Cleaned up test directory" << std::endl;
            
        } catch (const fs::filesystem_error& e) {
            std::cout << "Filesystem error: " << e.what() << std::endl;
        }
    }
    
    void demonstrateCpp17Features() {
        std::cout << "=== C++17 Features Demonstration ===" << std::endl;
        
        demonstrateStructuredBindings();
        demonstrateIfConstexpr();
        demonstrateOptional();
        demonstrateVariant();
        demonstrateAny();
        demonstrateStringView();
        demonstrateParallelAlgorithms();
        demonstrateFilesystem();
    }
}

// Example 2: C++20 Features
namespace Cpp20Features {
    
    // Concepts
    template<typename T>
    concept Numeric = std::integral<T> || std::floating_point<T>;
    
    template<typename T>
    concept Container = requires(T t) {
        t.begin();
        t.end();
        t.size();
    };
    
    template<Numeric T>
    T square(T value) {
        return value * value;
    }
    
    template<Container T>
    void print_container(const T& container) {
        std::cout << "Container with " << container.size() << " elements:" << std::endl;
        for (const auto& element : container) {
            std::cout << "  " << element << std::endl;
        }
    }
    
    void demonstrateConcepts() {
        std::cout << "\n=== C++20 Concepts ===" << std::endl;
        
        std::cout << "Square of 5: " << square(5) << std::endl;
        std::cout << "Square of 3.14: " << square(3.14) << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        print_container(vec);
        
        std::array<std::string, 3> arr = {"Hello", "World", "C++20"};
        print_container(arr);
    }
    
    // Ranges
    void demonstrateRanges() {
        std::cout << "\n=== C++20 Ranges ===" << std::endl;
        
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Filter and transform using ranges
        auto even_squares = numbers 
            | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * n; });
        
        std::cout << "Even squares: ";
        for (int value : even_squares) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Take first 5 elements
        auto first_five = numbers | std::views::take(5);
        std::cout << "First 5 elements: ";
        for (int value : first_five) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Drop first 3 elements
        auto last_seven = numbers | std::views::drop(3);
        std::cout << "Last 7 elements: ";
        for (int value : last_seven) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Reverse view
        auto reversed = numbers | std::views::reverse;
        std::cout << "Reversed: ";
        for (int value : reversed) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    
    // Coroutines
    template<typename T>
    class Generator {
    public:
        struct promise_type {
            T value;
            std::exception_ptr exception;
            
            Generator get_return_object() {
                return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
            }
            
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            
            void unhandled_exception() {
                exception = std::current_exception();
            }
            
            std::suspend_always yield_value(T val) {
                value = val;
                return {};
            }
            
            void return_void() {}
        };
        
        using handle_type = std::coroutine_handle<promise_type>;
        
    private:
        handle_type coro_;
        
    public:
        Generator(handle_type h) : coro_(h) {}
        
        ~Generator() {
            if (coro_) {
                coro_.destroy();
            }
        }
        
        // Non-copyable
        Generator(const Generator&) = delete;
        Generator& operator=(const Generator&) = delete;
        
        // Movable
        Generator(Generator&& other) noexcept : coro_(other.coro_) {
            other.coro_ = {};
        }
        
        Generator& operator=(Generator&& other) noexcept {
            if (this != &other) {
                if (coro_) {
                    coro_.destroy();
                }
                coro_ = other.coro_;
                other.coro_ = {};
            }
            return *this;
        }
        
        // Iterator interface
        struct iterator {
            Generator* gen;
            
            iterator(Generator* g) : gen(g) {
                if (gen && !gen->done()) {
                    gen->resume();
                }
            }
            
            iterator& operator++() {
                if (gen && !gen->done()) {
                    gen->resume();
                }
                return *this;
            }
            
            bool operator!=(const iterator& other) const {
                return gen != other.gen || (gen && !gen->done());
            }
            
            T operator*() const {
                return gen ? gen->get_value() : T{};
            }
        };
        
        iterator begin() {
            return iterator(this);
        }
        
        iterator end() {
            return iterator(nullptr);
        }
        
        // Resume coroutine
        bool resume() {
            if (!coro_ || coro_.done()) {
                return false;
            }
            
            coro_.resume();
            return !coro_.done();
        }
        
        // Check if coroutine is done
        bool done() const {
            return !coro_ || coro_.done();
        }
        
        // Get current value
        T get_value() const {
            if (coro_ && !coro_.done()) {
                return coro_.promise().value;
            }
            return {};
        }
    };
    
    // Fibonacci generator coroutine
    Generator<int> fibonacci(int n) {
        int a = 0, b = 1;
        
        if (n >= 1) co_yield a;
        if (n >= 2) co_yield b;
        
        for (int i = 2; i < n; ++i) {
            int temp = a + b;
            a = b;
            b = temp;
            co_yield b;
        }
    }
    
    void demonstrateCoroutines() {
        std::cout << "\n=== C++20 Coroutines ===" << std::endl;
        
        auto fib_gen = fibonacci(10);
        
        std::cout << "Fibonacci sequence (first 10): ";
        for (int value : fib_gen) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    
    // Modules (simplified example - full modules require separate compilation)
    void demonstrateModules() {
        std::cout << "\n=== C++20 Modules ===" << std::endl;
        std::cout << "Modules require separate compilation and are not fully demonstrated here." << std::endl;
        std::cout << "Modules provide better encapsulation and faster compilation than headers." << std::endl;
    }
    
    // Three-way comparison (spaceship operator)
    struct Point {
        int x, y;
        
        auto operator<=>(const Point& other) const = default;
    };
    
    void demonstrateThreeWayComparison() {
        std::cout << "\n=== C++20 Three-way Comparison ===" << std::endl;
        
        Point p1{1, 2};
        Point p2{3, 4};
        Point p3{1, 2};
        
        std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
        std::cout << "p1 > p2: " << (p1 > p2) << std::endl;
        std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
        std::cout << "p1 != p2: " << (p1 != p2) << std::endl;
    }
    
    // Designated initializers
    struct Config {
        std::string name;
        int port;
        bool debug;
    };
    
    void demonstrateDesignatedInitializers() {
        std::cout << "\n=== C++20 Designated Initializers ===" << std::endl;
        
        Config config{.name = "server", .port = 8080, .debug = true};
        
        std::cout << "Config: " << config.name << ":" << config.port 
                  << " (debug: " << config.debug << ")" << std::endl;
    }
    
    void demonstrateCpp20Features() {
        std::cout << "\n=== C++20 Features Demonstration ===" << std::endl;
        
        demonstrateConcepts();
        demonstrateRanges();
        demonstrateCoroutines();
        demonstrateModules();
        demonstrateThreeWayComparison();
        demonstrateDesignatedInitializers();
    }
}

// Example 3: Advanced Language Features
namespace AdvancedLanguageFeatures {
    
    // Template metaprogramming with concepts
    template<typename T>
    concept Arithmetic = requires(T a, T b) {
        a + b;
        a - b;
        a * b;
        a / b;
    };
    
    template<Arithmetic T>
    class Calculator {
    private:
        T value_;
        
    public:
        Calculator(T initial = T{}) : value_(initial) {}
        
        T add(T other) { return value_ += other; }
        T subtract(T other) { return value_ -= other; }
        T multiply(T other) { return value_ *= other; }
        T divide(T other) { return value_ /= other; }
        
        T get_value() const { return value_; }
    };
    
    void demonstrateAdvancedTemplates() {
        std::cout << "\n=== Advanced Template Features ===" << std::endl;
        
        Calculator<int> int_calc(10);
        std::cout << "Integer calculator: " << int_calc.add(5) << std::endl;
        
        Calculator<double> double_calc(10.5);
        std::cout << "Double calculator: " << double_calc.multiply(2.0) << std::endl;
    }
    
    // Lambda expressions with captures
    void demonstrateAdvancedLambdas() {
        std::cout << "\n=== Advanced Lambda Features ===" << std::endl;
        
        int multiplier = 3;
        
        // Lambda with capture by value
        auto multiply_by = [multiplier](int value) { return value * multiplier; };
        
        // Lambda with capture by reference
        auto accumulate = [&multiplier](int value) { 
            multiplier += value; 
            return multiplier; 
        };
        
        // Lambda with generalized capture
        auto create_adder = [](int x) {
            return [x](int y) { return x + y; };
        };
        
        std::cout << "Multiply 5 by " << multiplier << ": " << multiply_by(5) << std::endl;
        std::cout << "Accumulate 10: " << accumulate(10) << std::endl;
        std::cout << "Multiplier is now: " << multiplier << std::endl;
        
        auto add_5 = create_adder(5);
        std::cout << "Add 5 to 7: " << add_5(7) << std::endl;
    }
    
    // SFINAE with concepts
    template<typename T>
    concept HasSize = requires(T t) {
        t.size();
    };
    
    template<typename T>
    concept HasBeginEnd = requires(T t) {
        t.begin();
        t.end();
    };
    
    template<HasSize T>
    void print_size(const T& container) {
        std::cout << "Container size: " << container.size() << std::endl;
    }
    
    template<HasBeginEnd T>
    void print_elements(const T& container) {
        std::cout << "Container elements: ";
        for (const auto& element : container) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    
    void demonstrateConceptsWithSFINAE() {
        std::cout << "\n=== Concepts with SFINAE ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        print_size(vec);
        print_elements(vec);
        
        std::array<std::string, 3> arr = {"Hello", "World", "C++"};
        print_size(arr);
        print_elements(arr);
    }
    
    // Variadic templates with concepts
    template<typename... Args>
    concept AllIntegral = (std::integral<Args> && ...);
    
    template<AllIntegral... Args>
    auto sum(Args... args) {
        return (args + ...);
    }
    
    template<typename... Args>
    concept AllSame = (std::same_as<Args, std::tuple_element_t<0, std::tuple<Args...>>> && ...);
    
    template<AllSame... Args>
    auto concatenate(Args... args) {
        return (args + ...);
    }
    
    void demonstrateVariadicConcepts() {
        std::cout << "\n=== Variadic Templates with Concepts ===" << std::endl;
        
        std::cout << "Sum of integers: " << sum(1, 2, 3, 4, 5) << std::endl;
        
        std::cout << "Concatenate strings: " << concatenate(std::string("Hello"), std::string(" "), std::string("World")) << std::endl;
    }
    
    void demonstrateAdvancedLanguageFeatures() {
        std::cout << "\n=== Advanced Language Features Demonstration ===" << std::endl;
        
        demonstrateAdvancedTemplates();
        demonstrateAdvancedLambdas();
        demonstrateConceptsWithSFINAE();
        demonstrateVariadicConcepts();
    }
}

// Example 4: Performance and Optimization
namespace PerformanceOptimization {
    
    // constexpr functions
    constexpr int factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
    
    constexpr int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // consteval functions (C++20)
    consteval int compile_time_factorial(int n) {
        if (n <= 1) return 1;
        return n * compile_time_factorial(n - 1);
    }
    
    void demonstrateCompileTimeComputation() {
        std::cout << "\n=== Compile-time Computation ===" << std::endl;
        
        constexpr int fact_5 = factorial(5);
        constexpr int fib_10 = fibonacci(10);
        
        std::cout << "Factorial of 5: " << fact_5 << std::endl;
        std::cout << "Fibonacci of 10: " << fib_10 << std::endl;
        
        // Compile-time computation
        constexpr int ct_fact = compile_time_factorial(6);
        std::cout << "Compile-time factorial of 6: " << ct_fact << std::endl;
    }
    
    // Memory optimization with alignas
    struct alignas(64) CacheLineAligned {
        int value;
        char padding[64 - sizeof(int)];
    };
    
    // Branch prediction optimization
    template<typename T>
    T branchless_max(T a, T b) {
        return a ^ ((a ^ b) & -(a < b));
    }
    
    template<typename T>
    T branchless_min(T a, T b) {
        return b ^ ((a ^ b) & -(a < b));
    }
    
    void demonstratePerformanceOptimization() {
        std::cout << "\n=== Performance Optimization ===" << std::endl;
        
        // Test branchless operations
        std::cout << "Branchless max(10, 20): " << branchless_max(10, 20) << std::endl;
        std::cout << "Branchless min(10, 20): " << branchless_min(10, 20) << std::endl;
        
        // Test cache alignment
        CacheLineAligned aligned_data;
        aligned_data.value = 42;
        std::cout << "Cache-aligned data: " << aligned_data.value << std::endl;
        
        // Test constexpr performance
        demonstrateCompileTimeComputation();
    }
}

int main() {
    std::cout << "=== Modern C++ Features Demonstration ===" << std::endl;
    std::cout << "This program demonstrates modern C++ features including\n"
              << "C++17 and C++20 features, concepts, coroutines, and advanced language features.\n" << std::endl;
    
    // Demonstrate various modern C++ features
    Cpp17Features::demonstrateCpp17Features();
    Cpp20Features::demonstrateCpp20Features();
    AdvancedLanguageFeatures::demonstrateAdvancedLanguageFeatures();
    PerformanceOptimization::demonstratePerformanceOptimization();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. C++17 introduced structured bindings, optional, variant, and parallel algorithms" << std::endl;
    std::cout << "2. C++20 introduced concepts, ranges, coroutines, and modules" << std::endl;
    std::cout << "3. Concepts provide better template constraints and error messages" << std::endl;
    std::cout << "4. Ranges enable functional-style programming with lazy evaluation" << std::endl;
    std::cout << "5. Coroutines enable cooperative multitasking and generators" << std::endl;
    std::cout << "6. Modern C++ features improve code readability, performance, and safety" << std::endl;
    std::cout << "7. Compile-time computation enables better performance and type safety" << std::endl;
    std::cout << "8. Advanced language features enable more expressive and efficient code" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC (C++20):
 * g++ -std=c++20 -Wall -Wextra -O2 -pthread -o modern_cpp_features 01_Modern_C++_Features.cpp
 * 
 * Using Clang (C++20):
 * clang++ -std=c++20 -Wall -Wextra -O2 -pthread -o modern_cpp_features 01_Modern_C++_Features.cpp
 * 
 * Using MSVC (Visual Studio 2019+):
 * cl /std:c++20 /EHsc /O2 01_Modern_C++_Features.cpp
 * 
 * Running:
 * ./modern_cpp_features (Linux/macOS)
 * modern_cpp_features.exe (Windows)
 * 
 * Note: This lesson requires C++20 for some features.
 * C++17 is the minimum required version for most features.
 * 
 * Modern C++ Features Notes:
 * - C++17 introduced structured bindings, optional, variant, and parallel algorithms
 * - C++20 introduced concepts, ranges, coroutines, and modules
 * - Concepts provide better template constraints and error messages
 * - Ranges enable functional-style programming with lazy evaluation
 * - Coroutines enable cooperative multitasking and generators
 * - Modern C++ features improve code readability, performance, and safety
 * - Compile-time computation enables better performance and type safety
 * - Advanced language features enable more expressive and efficient code
 */"""
