/*
 * Lesson 17.1: Modern C++ Features
 * 
 * This file demonstrates modern C++ features including
 * C++17 features, C++20 features, concepts, modules,
 * coroutines, and other advanced language features.
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
#include <optional>
#include <variant>
#include <any>
#include <string_view>
#include <filesystem>
#include <array>
#include <tuple>
#include <type_traits>
#include <concepts>

// Example 1: C++17 Features
namespace Cpp17Features {
    
    // Structured Bindings
    void demonstrateStructuredBindings() {
        std::cout << "=== C++17 Structured Bindings ===" << std::endl;
        
        // Pair structured binding
        std::pair<int, std::string> pair_data{42, "Hello"};
        auto [number, text] = pair_data;
        std::cout << "Number: " << number << ", Text: " << text << std::endl;
        
        // Tuple structured binding
        std::tuple<int, std::string, double> tuple_data{10, "World", 3.14};
        auto [a, b, c] = tuple_data;
        std::cout << "A: " << a << ", B: " << b << ", C: " << c << std::endl;
        
        // Array structured binding
        std::array<int, 3> array_data{1, 2, 3};
        auto [first, second, third] = array_data;
        std::cout << "First: " << first << ", Second: " << second << ", Third: " << third << std::endl;
        
        // Map structured binding
        std::map<std::string, int> map_data{{"apple", 5}, {"banana", 3}, {"cherry", 8}};
        for (const auto& [key, value] : map_data) {
            std::cout << key << ": " << value << std::endl;
        }
    }
    
    // std::optional
    std::optional<int> divide(int a, int b) {
        if (b == 0) {
            return std::nullopt;
        }
        return a / b;
    }
    
    std::optional<std::string> find_user(const std::string& id) {
        std::map<std::string, std::string> users{
            {"user1", "John Doe"},
            {"user2", "Jane Smith"},
            {"user3", "Bob Johnson"}
        };
        
        auto it = users.find(id);
        if (it != users.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    void demonstrateOptional() {
        std::cout << "\n=== C++17 std::optional ===" << std::endl;
        
        // Safe division
        auto result1 = divide(10, 2);
        if (result1.has_value()) {
            std::cout << "10 / 2 = " << result1.value() << std::endl;
        }
        
        auto result2 = divide(10, 0);
        if (!result2.has_value()) {
            std::cout << "Division by zero returned nullopt" << std::endl;
        }
        
        // Using value_or for default values
        auto result3 = divide(15, 3);
        std::cout << "15 / 3 = " << result3.value_or(-1) << std::endl;
        
        // User lookup
        auto user1 = find_user("user1");
        if (user1) {
            std::cout << "Found user: " << *user1 << std::endl;
        }
        
        auto user4 = find_user("user4");
        std::cout << "User4: " << (user4 ? *user4 : "Not found") << std::endl;
    }
    
    // std::variant
    using ShapeVariant = std::variant<int, double, std::string>;
    
    void print_variant(const ShapeVariant& v) {
        std::visit([](const auto& value) {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, int>) {
                std::cout << "Integer: " << value << std::endl;
            } else if constexpr (std::is_same_v<T, double>) {
                std::cout << "Double: " << value << std::endl;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "String: " << value << std::endl;
            }
        }, v);
    }
    
    void demonstrateVariant() {
        std::cout << "\n=== C++17 std::variant ===" << std::endl;
        
        ShapeVariant v1 = 42;
        ShapeVariant v2 = 3.14159;
        ShapeVariant v3 = std::string("Hello, World!");
        
        print_variant(v1);
        print_variant(v2);
        print_variant(v3);
        
        // Check which type is currently held
        if (std::holds_alternative<int>(v1)) {
            std::cout << "v1 holds an integer: " << std::get<int>(v1) << std::endl;
        }
        
        // Safe get with index
        try {
            std::cout << "v2 as double: " << std::get<double>(v2) << std::endl;
        } catch (const std::bad_variant_access& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    // std::any
    void demonstrateAny() {
        std::cout << "\n=== C++17 std::any ===" << std::endl;
        
        std::any value1 = 42;
        std::any value2 = std::string("Hello");
        std::any value3 = 3.14;
        std::any value4 = std::vector<int>{1, 2, 3, 4, 5};
        
        // Type-safe access
        if (value1.type() == typeid(int)) {
            std::cout << "value1 is int: " << std::any_cast<int>(value1) << std::endl;
        }
        
        if (value2.type() == typeid(std::string)) {
            std::cout << "value2 is string: " << std::any_cast<std::string>(value2) << std::endl;
        }
        
        if (value4.type() == typeid(std::vector<int>)) {
            auto vec = std::any_cast<std::vector<int>>(value4);
            std::cout << "value4 is vector with size: " << vec.size() << std::endl;
        }
        
        // Safe any_cast
        try {
            std::cout << "value3 as double: " << std::any_cast<double>(value3) << std::endl;
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    // std::string_view
    void demonstrateStringView() {
        std::cout << "\n=== C++17 std::string_view ===" << std::endl;
        
        std::string str = "Hello, World!";
        std::string_view sv = str;
        
        std::cout << "String view: " << sv << std::endl;
        std::cout << "Size: " << sv.size() << std::endl;
        std::cout << "First character: " << sv[0] << std::endl;
        std::cout << "Substring: " << sv.substr(0, 5) << std::endl;
        
        // String view from C-string
        const char* cstr = "C-style string";
        std::string_view sv2(cstr);
        std::cout << "C-string view: " << sv2 << std::endl;
        
        // String view from literal
        std::string_view sv3("String literal");
        std::cout << "Literal view: " << sv3 << std::endl;
        
        // No copying, just viewing
        std::string long_string = "This is a very long string that we don't want to copy";
        std::string_view view_of_long = long_string;
        std::cout << "View of long string (no copy): " << view_of_long.substr(0, 20) << "..." << std::endl;
    }
    
    // if constexpr
    template<typename T>
    void process_value(T value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Processing integer: " << value << std::endl;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "Processing float: " << value << std::endl;
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
        process_value(true);
    }
    
    // std::filesystem
    void demonstrateFilesystem() {
        std::cout << "\n=== C++17 std::filesystem ===" << std::endl;
        
        namespace fs = std::filesystem;
        
        // Get current directory
        std::cout << "Current directory: " << fs::current_path() << std::endl;
        
        // Check if path exists
        fs::path current_path = fs::current_path();
        std::cout << "Current path exists: " << std::boolalpha << fs::exists(current_path) << std::endl;
        
        // Check if it's a directory
        std::cout << "Is directory: " << std::boolalpha << fs::is_directory(current_path) << std::endl;
        
        // Get file size (if it's a file)
        if (fs::is_regular_file(current_path)) {
            std::cout << "File size: " << fs::file_size(current_path) << " bytes" << std::endl;
        }
        
        // List directory contents
        try {
            std::cout << "Directory contents:" << std::endl;
            for (const auto& entry : fs::directory_iterator(current_path)) {
                std::cout << "  " << entry.path().filename() << " (";
                if (entry.is_directory()) {
                    std::cout << "directory";
                } else if (entry.is_regular_file()) {
                    std::cout << "file";
                } else {
                    std::cout << "other";
                }
                std::cout << ")" << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cout << "Filesystem error: " << e.what() << std::endl;
        }
    }
    
    void demonstrateAllFeatures() {
        demonstrateStructuredBindings();
        demonstrateOptional();
        demonstrateVariant();
        demonstrateAny();
        demonstrateStringView();
        demonstrateIfConstexpr();
        demonstrateFilesystem();
    }
}

// Example 2: C++20 Features
namespace Cpp20Features {
    
    // Concepts (C++20)
    template<typename T>
    concept Addable = requires(T a, T b) {
        a + b;
    };
    
    template<typename T>
    concept Printable = requires(T a) {
        std::cout << a;
    };
    
    template<typename T>
    concept Container = requires(T t) {
        t.begin();
        t.end();
        t.size();
    };
    
    template<Addable T>
    T add_values(T a, T b) {
        return a + b;
    }
    
    template<Printable T>
    void print_value(T value) {
        std::cout << "Value: " << value << std::endl;
    }
    
    template<Container T>
    void print_container_info(const T& container) {
        std::cout << "Container size: " << container.size() << std::endl;
    }
    
    void demonstrateConcepts() {
        std::cout << "\n=== C++20 Concepts ===" << std::endl;
        
        // Addable concept
        std::cout << "Adding integers: " << add_values(5, 3) << std::endl;
        std::cout << "Adding doubles: " << add_values(2.5, 3.7) << std::endl;
        
        // Printable concept
        print_value(42);
        print_value("Hello, World!");
        print_value(3.14159);
        
        // Container concept
        std::vector<int> vec{1, 2, 3, 4, 5};
        std::array<int, 3> arr{10, 20, 30};
        std::string str = "Hello";
        
        print_container_info(vec);
        print_container_info(arr);
        print_container_info(str);
    }
    
    // Ranges (C++20)
    void demonstrateRanges() {
        std::cout << "\n=== C++20 Ranges ===" << std::endl;
        
        std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Filter even numbers and square them
        auto even_squares = numbers | 
            std::views::filter([](int n) { return n % 2 == 0; }) |
            std::views::transform([](int n) { return n * n; });
        
        std::cout << "Even squares: ";
        for (int value : even_squares) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Take first 5 elements and double them
        auto first_five_doubled = numbers |
            std::views::take(5) |
            std::views::transform([](int n) { return n * 2; });
        
        std::cout << "First 5 doubled: ";
        for (int value : first_five_doubled) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Reverse view
        auto reversed = numbers | std::views::reverse;
        std::cout << "Reversed: ";
        for (int value : reversed | std::views::take(5)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    
    // Modules (C++20) - Note: This is a simplified example
    // In real C++20, modules would be in separate .cppm files
    void demonstrateModules() {
        std::cout << "\n=== C++20 Modules (Conceptual) ===" << std::endl;
        std::cout << "Note: Full module support requires separate .cppm files" << std::endl;
        std::cout << "Modules provide:" << std::endl;
        std::cout << "- Faster compilation" << std::endl;
        std::cout << "- Better encapsulation" << std::endl;
        std::cout << "- Reduced header dependencies" << std::endl;
        std::cout << "- Cleaner interfaces" << std::endl;
    }
    
    // Coroutines (C++20)
    #include <coroutine>
    
    // Simple generator coroutine
    struct Generator {
        struct promise_type {
            int current_value;
            
            Generator get_return_object() {
                return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
            }
            
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            
            std::suspend_always yield_value(int value) {
                current_value = value;
                return {};
            }
            
            void return_void() {}
            void unhandled_exception() {}
        };
        
        std::coroutine_handle<promise_type> coro;
        
        Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
        
        ~Generator() {
            if (coro) coro.destroy();
        }
        
        // Non-copyable
        Generator(const Generator&) = delete;
        Generator& operator=(const Generator&) = delete;
        
        // Move-only
        Generator(Generator&& other) noexcept : coro(other.coro) {
            other.coro = {};
        }
        
        Generator& operator=(Generator&& other) noexcept {
            if (this != &other) {
                if (coro) coro.destroy();
                coro = other.coro;
                other.coro = {};
            }
            return *this;
        }
        
        struct iterator {
            std::coroutine_handle<promise_type> coro;
            
            iterator(std::coroutine_handle<promise_type> h) : coro(h) {}
            
            iterator& operator++() {
                coro.resume();
                return *this;
            }
            
            int operator*() const {
                return coro.promise().current_value;
            }
            
            bool operator!=(const iterator& other) const {
                return coro != other.coro;
            }
        };
        
        iterator begin() {
            coro.resume();
            return iterator{coro};
        }
        
        iterator end() {
            return iterator{};
        }
    };
    
    Generator fibonacci(int n) {
        int a = 0, b = 1;
        for (int i = 0; i < n; ++i) {
            co_yield a;
            int temp = a + b;
            a = b;
            b = temp;
        }
    }
    
    void demonstrateCoroutines() {
        std::cout << "\n=== C++20 Coroutines ===" << std::endl;
        
        std::cout << "Fibonacci sequence (first 10 numbers): ";
        for (int value : fibonacci(10)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    
    // Three-way comparison (spaceship operator)
    struct Person {
        std::string name;
        int age;
        
        Person(const std::string& n, int a) : name(n), age(a) {}
        
        auto operator<=>(const Person& other) const = default;
    };
    
    void demonstrateThreeWayComparison() {
        std::cout << "\n=== C++20 Three-way Comparison ===" << std::endl;
        
        Person alice("Alice", 30);
        Person bob("Bob", 25);
        Person charlie("Charlie", 30);
        
        std::cout << "Alice < Bob: " << std::boolalpha << (alice < bob) << std::endl;
        std::cout << "Alice > Bob: " << std::boolalpha << (alice > bob) << std::endl;
        std::cout << "Alice == Charlie: " << std::boolalpha << (alice == charlie) << std::endl;
        std::cout << "Alice != Bob: " << std::boolalpha << (alice != bob) << std::endl;
    }
    
    // std::format (C++20)
    void demonstrateFormat() {
        std::cout << "\n=== C++20 std::format ===" << std::endl;
        
        // Note: std::format requires C++20 and may not be available in all compilers
        std::cout << "std::format provides:" << std::endl;
        std::cout << "- Type-safe string formatting" << std::endl;
        std::cout << "- Python-style format strings" << std::endl;
        std::cout << "- Better performance than printf/iostream" << std::endl;
        std::cout << "- Locale support" << std::endl;
        
        // Example usage (conceptual)
        std::cout << "Example: std::format(\"Hello {}, you are {} years old\", name, age)" << std::endl;
    }
    
    void demonstrateAllFeatures() {
        demonstrateConcepts();
        demonstrateRanges();
        demonstrateModules();
        demonstrateCoroutines();
        demonstrateThreeWayComparison();
        demonstrateFormat();
    }
}

// Example 3: Advanced Template Features
namespace AdvancedTemplates {
    
    // Variable templates
    template<typename T>
    constexpr T pi = T(3.1415926535897932385L);
    
    template<typename T>
    constexpr T e = T(2.7182818284590452354L);
    
    void demonstrateVariableTemplates() {
        std::cout << "\n=== Variable Templates ===" << std::endl;
        
        std::cout << "Pi as float: " << pi<float> << std::endl;
        std::cout << "Pi as double: " << pi<double> << std::endl;
        std::cout << "Pi as long double: " << pi<long double> << std::endl;
        
        std::cout << "E as float: " << e<float> << std::endl;
        std::cout << "E as double: " << e<double> << std::endl;
    }
    
    // Class template argument deduction (CTAD)
    template<typename T>
    class Point {
    private:
        T x_, y_;
        
    public:
        Point(T x, T y) : x_(x), y_(y) {}
        
        T get_x() const { return x_; }
        T get_y() const { return y_; }
        
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            return os << "(" << p.x_ << ", " << p.y_ << ")";
        }
    };
    
    void demonstrateCTAD() {
        std::cout << "\n=== Class Template Argument Deduction ===" << std::endl;
        
        // CTAD deduces template arguments from constructor
        Point p1(10, 20);        // Point<int>
        Point p2(3.14, 2.71);    // Point<double>
        Point p3(10.5f, 20.5f);  // Point<float>
        
        std::cout << "Point 1: " << p1 << std::endl;
        std::cout << "Point 2: " << p2 << std::endl;
        std::cout << "Point 3: " << p3 << std::endl;
        
        // Explicit template arguments still work
        Point<double> p4(10, 20);
        std::cout << "Point 4: " << p4 << std::endl;
    }
    
    // Fold expressions
    template<typename... Args>
    auto sum(Args... args) {
        return (args + ...);
    }
    
    template<typename... Args>
    auto product(Args... args) {
        return (args * ...);
    }
    
    template<typename... Args>
    void print_all(Args... args) {
        (std::cout << ... << args) << std::endl;
    }
    
    template<typename T, typename... Args>
    bool all_equal(const T& first, const Args&... rest) {
        return ((first == rest) && ...);
    }
    
    void demonstrateFoldExpressions() {
        std::cout << "\n=== Fold Expressions ===" << std::endl;
        
        std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl;
        std::cout << "Product: " << product(2, 3, 4) << std::endl;
        
        std::cout << "Print all: ";
        print_all("Hello", " ", "World", "!", " ", 42);
        
        std::cout << "All equal (5, 5, 5): " << std::boolalpha << all_equal(5, 5, 5) << std::endl;
        std::cout << "All equal (5, 5, 6): " << std::boolalpha << all_equal(5, 5, 6) << std::endl;
    }
    
    // SFINAE and type traits
    template<typename T>
    std::enable_if_t<std::is_integral_v<T>, void> process_integer(T value) {
        std::cout << "Processing integer: " << value << std::endl;
    }
    
    template<typename T>
    std::enable_if_t<std::is_floating_point_v<T>, void> process_float(T value) {
        std::cout << "Processing float: " << value << std::endl;
    }
    
    template<typename T>
    std::enable_if_t<!std::is_arithmetic_v<T>, void> process_other(T value) {
        std::cout << "Processing other type" << std::endl;
    }
    
    void demonstrateSFINAE() {
        std::cout << "\n=== SFINAE and Type Traits ===" << std::endl;
        
        process_integer(42);
        process_float(3.14);
        process_other(std::string("Hello"));
        
        // Type traits
        std::cout << "Is int integral: " << std::boolalpha << std::is_integral_v<int> << std::endl;
        std::cout << "Is double floating point: " << std::boolalpha << std::is_floating_point_v<double> << std::endl;
        std::cout << "Is string arithmetic: " << std::boolalpha << std::is_arithmetic_v<std::string> << std::endl;
    }
    
    void demonstrateAllFeatures() {
        demonstrateVariableTemplates();
        demonstrateCTAD();
        demonstrateFoldExpressions();
        demonstrateSFINAE();
    }
}

// Example 4: Memory Management Improvements
namespace MemoryManagement {
    
    // Smart pointers improvements
    void demonstrateSmartPointers() {
        std::cout << "\n=== Modern Smart Pointers ===" << std::endl;
        
        // make_unique (C++14)
        auto unique_ptr = std::make_unique<std::vector<int>>(10, 42);
        std::cout << "Unique pointer vector size: " << unique_ptr->size() << std::endl;
        
        // make_shared (C++11)
        auto shared_ptr = std::make_shared<std::string>("Hello, World!");
        std::cout << "Shared pointer string: " << *shared_ptr << std::endl;
        std::cout << "Reference count: " << shared_ptr.use_count() << std::endl;
        
        // weak_ptr
        std::weak_ptr<std::string> weak_ptr = shared_ptr;
        std::cout << "Weak pointer expired: " << std::boolalpha << weak_ptr.expired() << std::endl;
        
        if (auto locked = weak_ptr.lock()) {
            std::cout << "Weak pointer locked: " << *locked << std::endl;
        }
        
        // Custom deleter
        auto custom_deleter = [](std::string* ptr) {
            std::cout << "Custom deleter called for: " << *ptr << std::endl;
            delete ptr;
        };
        
        std::unique_ptr<std::string, decltype(custom_deleter)> custom_ptr(
            new std::string("Custom deletion"), custom_deleter);
    }
    
    // RAII improvements
    class ResourceManager {
    private:
        std::unique_ptr<int[]> data_;
        size_t size_;
        
    public:
        ResourceManager(size_t size) : size_(size) {
            data_ = std::make_unique<int[]>(size);
            std::cout << "Resource allocated: " << size << " integers" << std::endl;
        }
        
        ~ResourceManager() {
            std::cout << "Resource deallocated: " << size_ << " integers" << std::endl;
        }
        
        // Move constructor
        ResourceManager(ResourceManager&& other) noexcept 
            : data_(std::move(other.data_)), size_(other.size_) {
            other.size_ = 0;
            std::cout << "Resource moved" << std::endl;
        }
        
        // Move assignment
        ResourceManager& operator=(ResourceManager&& other) noexcept {
            if (this != &other) {
                data_ = std::move(other.data_);
                size_ = other.size_;
                other.size_ = 0;
                std::cout << "Resource move assigned" << std::endl;
            }
            return *this;
        }
        
        // Non-copyable
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        
        int& operator[](size_t index) {
            return data_[index];
        }
        
        const int& operator[](size_t index) const {
            return data_[index];
        }
        
        size_t size() const {
            return size_;
        }
    };
    
    void demonstrateRAII() {
        std::cout << "\n=== RAII Improvements ===" << std::endl;
        
        {
            ResourceManager manager(100);
            manager[0] = 42;
            manager[1] = 84;
            
            std::cout << "First element: " << manager[0] << std::endl;
            std::cout << "Second element: " << manager[1] << std::endl;
            
            // Move semantics
            ResourceManager moved_manager = std::move(manager);
            std::cout << "Moved manager size: " << moved_manager.size() << std::endl;
            
            // manager is now in moved-from state
            std::cout << "Original manager size: " << manager.size() << std::endl;
        } // Automatic cleanup when leaving scope
    }
    
    void demonstrateAllFeatures() {
        demonstrateSmartPointers();
        demonstrateRAII();
    }
}

int main() {
    std::cout << "=== Modern C++ Features Demonstration ===" << std::endl;
    std::cout << "This program demonstrates modern C++ features including\n"
              << "C++17 features, C++20 features, advanced templates,\n"
              << "and improved memory management.\n" << std::endl;
    
    // Demonstrate various modern C++ features
    Cpp17Features::demonstrateAllFeatures();
    Cpp20Features::demonstrateAllFeatures();
    AdvancedTemplates::demonstrateAllFeatures();
    MemoryManagement::demonstrateAllFeatures();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. C++17 introduced structured bindings, optional, variant, and any" << std::endl;
    std::cout << "2. C++20 added concepts, ranges, coroutines, and three-way comparison" << std::endl;
    std::cout << "3. Modern templates support variable templates, CTAD, and fold expressions" << std::endl;
    std::cout << "4. Smart pointers and RAII provide better memory management" << std::endl;
    std::cout << "5. Modern C++ features improve type safety and performance" << std::endl;
    std::cout << "6. New language features enable more expressive and efficient code" << std::endl;
    std::cout << "7. Backward compatibility is maintained while adding new capabilities" << std::endl;
    std::cout << "8. Modern C++ continues to evolve with each standard release" << std::endl;
    
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
 * Note: This lesson requires C++20 for full functionality.
 * Some features may require specific compiler versions.
 * 
 * Modern C++ Features Notes:
 * - C++17 introduced structured bindings, optional, variant, and any
 * - C++20 added concepts, ranges, coroutines, and three-way comparison
 * - Modern templates support variable templates, CTAD, and fold expressions
 * - Smart pointers and RAII provide better memory management
 * - Modern C++ features improve type safety and performance
 * - New language features enable more expressive and efficient code
 * - Backward compatibility is maintained while adding new capabilities
 * - Modern C++ continues to evolve with each standard release
 */"""
