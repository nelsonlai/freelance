#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>

// Demonstrates compatibility and migration strategies
int main() {
    std::cout << "Compatibility and Migration Demonstration" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // 1. C++ Standard Evolution
    std::cout << "\n1. C++ STANDARD EVOLUTION:" << std::endl;
    
    // C++98/03 features
    std::cout << "  C++98/03 features:" << std::endl;
    std::vector<int> old_vector;
    old_vector.push_back(1);
    old_vector.push_back(2);
    old_vector.push_back(3);
    
    for (std::vector<int>::iterator it = old_vector.begin(); it != old_vector.end(); ++it) {
        std::cout << "    " << *it << " ";
    }
    std::cout << std::endl;
    
    // C++11 features
    std::cout << "  C++11 features:" << std::endl;
    auto cpp11_vector = std::vector<int>{4, 5, 6};
    for (const auto& item : cpp11_vector) {
        std::cout << "    " << item << " ";
    }
    std::cout << std::endl;
    
    // C++14 features
    std::cout << "  C++14 features:" << std::endl;
    auto cpp14_lambda = [](auto x) { return x * 2; };
    std::cout << "    Auto lambda result: " << cpp14_lambda(21) << std::endl;
    
    // C++17 features
    std::cout << "  C++17 features:" << std::endl;
    if (auto [a, b] = std::make_pair(10, 20); a < b) {
        std::cout << "    Structured binding: " << a << " < " << b << std::endl;
    }
    
    // C++20 features (if available)
    std::cout << "  C++20 features:" << std::endl;
    std::cout << "    Concepts and ranges (if supported)" << std::endl;
    
    // 2. Legacy Code Migration
    std::cout << "\n2. LEGACY CODE MIGRATION:" << std::endl;
    
    // Old C-style array
    int old_array[5] = {1, 2, 3, 4, 5};
    std::cout << "  Old C-style array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << old_array[i] << " ";
    }
    std::cout << std::endl;
    
    // Migrate to modern C++
    std::array<int, 5> modern_array = {1, 2, 3, 4, 5};
    std::cout << "  Modern std::array: ";
    for (const auto& item : modern_array) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // Old C-style string
    char old_string[100] = "Hello, World!";
    std::cout << "  Old C-style string: " << old_string << std::endl;
    
    // Migrate to modern C++
    std::string modern_string = "Hello, World!";
    std::cout << "  Modern std::string: " << modern_string << std::endl;
    
    // 3. Memory Management Migration
    std::cout << "\n3. MEMORY MANAGEMENT MIGRATION:" << std::endl;
    
    // Old C-style memory management
    int* old_ptr = new int(42);
    std::cout << "  Old C++ memory management: " << *old_ptr << std::endl;
    delete old_ptr;
    
    // Migrate to smart pointers
    auto smart_ptr = std::make_unique<int>(42);
    std::cout << "  Modern smart pointer: " << *smart_ptr << std::endl;
    
    // Old C-style array allocation
    int* old_array_ptr = new int[5];
    for (int i = 0; i < 5; ++i) {
        old_array_ptr[i] = i * 2;
    }
    std::cout << "  Old array allocation: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << old_array_ptr[i] << " ";
    }
    std::cout << std::endl;
    delete[] old_array_ptr;
    
    // Migrate to modern containers
    std::vector<int> modern_vector(5);
    std::iota(modern_vector.begin(), modern_vector.end(), 0);
    std::transform(modern_vector.begin(), modern_vector.end(), modern_vector.begin(),
                   [](int x) { return x * 2; });
    std::cout << "  Modern vector: ";
    for (const auto& item : modern_vector) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 4. Function Style Migration
    std::cout << "\n4. FUNCTION STYLE MIGRATION:" << std::endl;
    
    // Old function style
    int old_add(int a, int b) {
        return a + b;
    }
    std::cout << "  Old function style: " << old_add(5, 3) << std::endl;
    
    // Modern function style
    auto modern_add = [](int a, int b) { return a + b; };
    std::cout << "  Modern lambda: " << modern_add(5, 3) << std::endl;
    
    // Function objects
    struct AddFunctor {
        int operator()(int a, int b) const {
            return a + b;
        }
    };
    AddFunctor add_functor;
    std::cout << "  Function object: " << add_functor(5, 3) << std::endl;
    
    // 5. Error Handling Migration
    std::cout << "\n5. ERROR HANDLING MIGRATION:" << std::endl;
    
    // Old error handling
    int old_divide(int a, int b, int* result) {
        if (b == 0) {
            return -1;  // Error code
        }
        *result = a / b;
        return 0;  // Success
    }
    
    int old_result;
    int old_error = old_divide(10, 2, &old_result);
    if (old_error == 0) {
        std::cout << "  Old error handling: " << old_result << std::endl;
    }
    
    // Modern error handling
    std::optional<int> modern_divide(int a, int b) {
        if (b == 0) {
            return std::nullopt;
        }
        return a / b;
    }
    
    auto modern_result = modern_divide(10, 2);
    if (modern_result) {
        std::cout << "  Modern error handling: " << *modern_result << std::endl;
    }
    
    // Exception-based error handling
    int exception_divide(int a, int b) {
        if (b == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }
    
    try {
        int exception_result = exception_divide(10, 2);
        std::cout << "  Exception-based: " << exception_result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Exception caught: " << e.what() << std::endl;
    }
    
    // 6. Template Migration
    std::cout << "\n6. TEMPLATE MIGRATION:" << std::endl;
    
    // Old template style
    template<typename T>
    T old_max(T a, T b) {
        return (a > b) ? a : b;
    }
    std::cout << "  Old template: " << old_max(10, 20) << std::endl;
    
    // Modern template style
    template<typename T>
    constexpr T modern_max(T a, T b) {
        return (a > b) ? a : b;
    }
    std::cout << "  Modern template: " << modern_max(10, 20) << std::endl;
    
    // C++20 concepts (if available)
    template<typename T>
    requires std::totally_ordered<T>
    T concept_max(T a, T b) {
        return (a > b) ? a : b;
    }
    
    // 7. Container Migration
    std::cout << "\n7. CONTAINER MIGRATION:" << std::endl;
    
    // Old container usage
    std::vector<int> old_container;
    old_container.push_back(1);
    old_container.push_back(2);
    old_container.push_back(3);
    
    // Modern container usage
    std::vector<int> modern_container = {1, 2, 3};
    
    // Old iteration
    std::cout << "  Old iteration: ";
    for (std::vector<int>::iterator it = old_container.begin(); it != old_container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Modern iteration
    std::cout << "  Modern iteration: ";
    for (const auto& item : modern_container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 8. Algorithm Migration
    std::cout << "\n8. ALGORITHM MIGRATION:" << std::endl;
    
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // Old algorithm usage
    std::sort(numbers.begin(), numbers.end());
    std::cout << "  Sorted numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Modern algorithm usage (C++20 ranges if available)
    std::vector<int> modern_numbers = {5, 2, 8, 1, 9, 3};
    std::ranges::sort(modern_numbers);
    std::cout << "  Modern sorted numbers: ";
    for (const auto& num : modern_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 9. Performance Migration
    std::cout << "\n9. PERFORMANCE MIGRATION:" << std::endl;
    
    const int num_elements = 1000000;
    
    // Old performance patterns
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> old_perf_vector;
    for (int i = 0; i < num_elements; ++i) {
        old_perf_vector.push_back(i);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto old_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Modern performance patterns
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> modern_perf_vector;
    modern_perf_vector.reserve(num_elements);
    for (int i = 0; i < num_elements; ++i) {
        modern_perf_vector.push_back(i);
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto modern_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Old vector time: " << old_time.count() << " microseconds" << std::endl;
    std::cout << "  Modern vector time: " << modern_time.count() << " microseconds" << std::endl;
    std::cout << "  Modern speedup: " << (double)old_time.count() / modern_time.count() << "x" << std::endl;
    
    // 10. Compatibility Wrappers
    std::cout << "\n10. COMPATIBILITY WRAPPERS:" << std::endl;
    
    // Legacy C function wrapper
    class LegacyWrapper {
    private:
        std::unique_ptr<int[]> data;
        size_t size;
        
    public:
        LegacyWrapper(size_t s) : size(s) {
            data = std::make_unique<int[]>(s);
        }
        
        // Provide C-style interface
        int* get_data() { return data.get(); }
        size_t get_size() const { return size; }
        
        // Provide modern C++ interface
        std::span<int> get_span() { return std::span<int>(data.get(), size); }
        
        // Iterator support
        int* begin() { return data.get(); }
        int* end() { return data.get() + size; }
    };
    
    LegacyWrapper wrapper(5);
    std::iota(wrapper.begin(), wrapper.end(), 1);
    
    std::cout << "  Legacy wrapper: ";
    for (const auto& item : wrapper) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 11. Migration Tools and Techniques
    std::cout << "\n11. MIGRATION TOOLS AND TECHNIQUES:" << std::endl;
    
    // Compile-time checks
    static_assert(sizeof(int) == 4, "int must be 4 bytes");
    static_assert(std::is_same_v<int, int>, "Type check");
    
    // Runtime checks
    if constexpr (std::is_same_v<int, int>) {
        std::cout << "  Compile-time type check passed" << std::endl;
    }
    
    // Feature detection
    if constexpr (__cpp_lib_ranges >= 201911L) {
        std::cout << "  C++20 ranges available" << std::endl;
    } else {
        std::cout << "  C++20 ranges not available" << std::endl;
    }
    
    // 12. Best Practices for Migration
    std::cout << "\n12. BEST PRACTICES FOR MIGRATION:" << std::endl;
    
    // Gradual migration
    class GradualMigration {
    private:
        std::vector<int> modern_data;
        
    public:
        // Keep old interface for compatibility
        void add_item(int item) {
            modern_data.push_back(item);
        }
        
        // Add modern interface
        void add_items(std::initializer_list<int> items) {
            modern_data.insert(modern_data.end(), items.begin(), items.end());
        }
        
        // Modern iteration
        auto begin() { return modern_data.begin(); }
        auto end() { return modern_data.end(); }
        
        // Old-style access
        int get_item(size_t index) const {
            return modern_data[index];
        }
        
        // Modern access
        int& operator[](size_t index) {
            return modern_data[index];
        }
    };
    
    GradualMigration migration;
    migration.add_item(1);
    migration.add_items({2, 3, 4, 5});
    
    std::cout << "  Gradual migration: ";
    for (const auto& item : migration) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 13. Testing Migration
    std::cout << "\n13. TESTING MIGRATION:" << std::endl;
    
    // Unit test framework compatibility
    auto test_function = [](int input) -> int {
        return input * 2;
    };
    
    // Test cases
    assert(test_function(5) == 10);
    assert(test_function(0) == 0);
    assert(test_function(-3) == -6);
    
    std::cout << "  All tests passed" << std::endl;
    
    // 14. Documentation Migration
    std::cout << "\n14. DOCUMENTATION MIGRATION:" << std::endl;
    
    // Modern documentation style
    /**
     * @brief Modern function with comprehensive documentation
     * @param input The input value to process
     * @return The processed result
     * @throws std::invalid_argument if input is negative
     * @since C++17
     */
    auto documented_function = [](int input) -> int {
        if (input < 0) {
            throw std::invalid_argument("Input must be non-negative");
        }
        return input * 2;
    };
    
    try {
        int result = documented_function(5);
        std::cout << "  Documented function result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
    }
    
    // 15. Future-Proofing
    std::cout << "\n15. FUTURE-PROOFING:" << std::endl;
    
    // Use standard library features
    std::cout << "  Using standard library features:" << std::endl;
    
    // std::optional for nullable types
    std::optional<int> maybe_value = 42;
    if (maybe_value) {
        std::cout << "    Optional value: " << *maybe_value << std::endl;
    }
    
    // std::variant for type-safe unions
    std::variant<int, std::string, double> variant_value = 42;
    std::visit([](const auto& value) {
        std::cout << "    Variant value: " << value << std::endl;
    }, variant_value);
    
    // std::any for type-erased values
    std::any any_value = std::string("Hello, Future!");
    std::cout << "    Any value: " << std::any_cast<std::string>(any_value) << std::endl;
    
    std::cout << "\nCompatibility and migration demonstration completed!" << std::endl;
    return 0;
}
