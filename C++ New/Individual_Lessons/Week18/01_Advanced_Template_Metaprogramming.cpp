/*
 * Lesson 18.1: Advanced Template Metaprogramming
 * 
 * This file demonstrates advanced template metaprogramming techniques
 * including SFINAE, type traits, template specialization, variadic templates,
 * and modern C++ metaprogramming with concepts and constexpr.
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
#include <concepts>

// Example 1: SFINAE (Substitution Failure Is Not An Error)
namespace SFINAE {
    
    // Basic SFINAE example
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    process_integral(T value) {
        std::cout << "Processing integral: " << value << std::endl;
        return value * 2;
    }
    
    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    process_floating_point(T value) {
        std::cout << "Processing floating point: " << value << std::endl;
        return value * 2.0;
    }
    
    template<typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value, void>::type
    process_other(T value) {
        std::cout << "Processing other type" << std::endl;
    }
    
    // SFINAE with decltype
    template<typename T>
    auto has_size_method(T&& t) -> decltype(t.size(), std::true_type{}) {
        return {};
    }
    
    std::false_type has_size_method(...) {
        return {};
    }
    
    template<typename T>
    void check_size_method(T&& t) {
        if constexpr (decltype(has_size_method(t))::value) {
            std::cout << "Has size method: " << t.size() << std::endl;
        } else {
            std::cout << "No size method" << std::endl;
        }
    }
    
    // SFINAE with void_t (C++17)
    template<typename, typename = std::void_t<>>
    struct has_begin_end : std::false_type {};
    
    template<typename T>
    struct has_begin_end<T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>> : std::true_type {};
    
    template<typename T>
    void check_container(T&& t) {
        if constexpr (has_begin_end<T>::value) {
            std::cout << "Is a container with begin/end" << std::endl;
        } else {
            std::cout << "Not a container" << std::endl;
        }
    }
    
    // SFINAE with concepts (C++20)
    template<typename T>
    concept HasSize = requires(T t) {
        t.size();
    };
    
    template<typename T>
    concept IsContainer = requires(T t) {
        t.begin();
        t.end();
        t.size();
    };
    
    template<HasSize T>
    void process_with_size(T&& t) {
        std::cout << "Processing with size: " << t.size() << std::endl;
    }
    
    template<IsContainer T>
    void process_container(T&& t) {
        std::cout << "Processing container with " << t.size() << " elements" << std::endl;
    }
    
    void demonstrateSFINAE() {
        std::cout << "=== SFINAE (Substitution Failure Is Not An Error) ===" << std::endl;
        
        // Test SFINAE with enable_if
        process_integral(42);
        process_floating_point(3.14);
        process_other(std::string("Hello"));
        
        // Test SFINAE with decltype
        std::vector<int> vec{1, 2, 3};
        std::string str = "Hello";
        int number = 42;
        
        check_size_method(vec);
        check_size_method(str);
        check_size_method(number);
        
        // Test SFINAE with void_t
        check_container(vec);
        check_container(str);
        check_container(number);
        
        // Test SFINAE with concepts
        process_with_size(vec);
        process_with_size(str);
        // process_with_size(number);  // This would cause a compilation error
        
        process_container(vec);
        process_container(str);
        // process_container(number);  // This would cause a compilation error
    }
}

// Example 2: Type Traits
namespace TypeTraits {
    
    // Custom type traits
    template<typename T>
    struct is_pointer_to_const {
        static constexpr bool value = std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>;
    };
    
    template<typename T>
    inline constexpr bool is_pointer_to_const_v = is_pointer_to_const<T>::value;
    
    // Type trait for checking if a type is a smart pointer
    template<typename T>
    struct is_smart_pointer : std::false_type {};
    
    template<typename T>
    struct is_smart_pointer<std::unique_ptr<T>> : std::true_type {};
    
    template<typename T>
    struct is_smart_pointer<std::shared_ptr<T>> : std::true_type {};
    
    template<typename T>
    struct is_smart_pointer<std::weak_ptr<T>> : std::true_type {};
    
    template<typename T>
    inline constexpr bool is_smart_pointer_v = is_smart_pointer<T>::value;
    
    // Type trait for checking if a type is callable
    template<typename T>
    struct is_callable {
        template<typename U>
        static auto test(U&& u) -> decltype(u(), std::true_type{});
        static std::false_type test(...);
        
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    
    template<typename T>
    inline constexpr bool is_callable_v = is_callable<T>::value;
    
    // Type trait for getting the underlying type of a smart pointer
    template<typename T>
    struct smart_pointer_element_type {
        using type = T;
    };
    
    template<typename T>
    struct smart_pointer_element_type<std::unique_ptr<T>> {
        using type = T;
    };
    
    template<typename T>
    struct smart_pointer_element_type<std::shared_ptr<T>> {
        using type = T;
    };
    
    template<typename T>
    using smart_pointer_element_type_t = typename smart_pointer_element_type<T>::type;
    
    // Type trait for checking if a type is a tuple-like
    template<typename T>
    struct is_tuple_like {
        template<typename U>
        static auto test(U&& u) -> decltype(std::get<0>(u), std::true_type{});
        static std::false_type test(...);
        
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    
    template<typename T>
    inline constexpr bool is_tuple_like_v = is_tuple_like<T>::value;
    
    void demonstrateTypeTraits() {
        std::cout << "\n=== Type Traits ===" << std::endl;
        
        // Test custom type traits
        std::cout << "is_pointer_to_const_v<const int*>: " << std::boolalpha << is_pointer_to_const_v<const int*> << std::endl;
        std::cout << "is_pointer_to_const_v<int*>: " << std::boolalpha << is_pointer_to_const_v<int*> << std::endl;
        
        std::cout << "is_smart_pointer_v<std::unique_ptr<int>>: " << std::boolalpha << is_smart_pointer_v<std::unique_ptr<int>> << std::endl;
        std::cout << "is_smart_pointer_v<int*>: " << std::boolalpha << is_smart_pointer_v<int*> << std::endl;
        
        // Test callable type trait
        auto lambda = []() { return 42; };
        std::cout << "is_callable_v<decltype(lambda)>: " << std::boolalpha << is_callable_v<decltype(lambda)> << std::endl;
        std::cout << "is_callable_v<int>: " << std::boolalpha << is_callable_v<int> << std::endl;
        
        // Test tuple-like type trait
        std::cout << "is_tuple_like_v<std::tuple<int, double>>: " << std::boolalpha << is_tuple_like_v<std::tuple<int, double>> << std::endl;
        std::cout << "is_tuple_like_v<std::pair<int, double>>: " << std::boolalpha << is_tuple_like_v<std::pair<int, double>> << std::endl;
        std::cout << "is_tuple_like_v<int>: " << std::boolalpha << is_tuple_like_v<int> << std::endl;
        
        // Test smart pointer element type
        using unique_ptr_type = smart_pointer_element_type_t<std::unique_ptr<int>>;
        std::cout << "smart_pointer_element_type_t<std::unique_ptr<int>> is int: " << std::boolalpha << std::is_same_v<unique_ptr_type, int> << std::endl;
    }
}

// Example 3: Template Specialization
namespace TemplateSpecialization {
    
    // Primary template
    template<typename T>
    struct TypeInfo {
        static constexpr const char* name() {
            return "Unknown";
        }
        
        static constexpr size_t size() {
            return sizeof(T);
        }
        
        static constexpr bool is_primitive() {
            return false;
        }
    };
    
    // Specialization for integers
    template<>
    struct TypeInfo<int> {
        static constexpr const char* name() {
            return "int";
        }
        
        static constexpr size_t size() {
            return sizeof(int);
        }
        
        static constexpr bool is_primitive() {
            return true;
        }
    };
    
    // Specialization for doubles
    template<>
    struct TypeInfo<double> {
        static constexpr const char* name() {
            return "double";
        }
        
        static constexpr size_t size() {
            return sizeof(double);
        }
        
        static constexpr bool is_primitive() {
            return true;
        }
    };
    
    // Specialization for strings
    template<>
    struct TypeInfo<std::string> {
        static constexpr const char* name() {
            return "std::string";
        }
        
        static constexpr size_t size() {
            return sizeof(std::string);
        }
        
        static constexpr bool is_primitive() {
            return false;
        }
    };
    
    // Partial specialization for pointers
    template<typename T>
    struct TypeInfo<T*> {
        static constexpr const char* name() {
            return "pointer";
        }
        
        static constexpr size_t size() {
            return sizeof(T*);
        }
        
        static constexpr bool is_primitive() {
            return false;
        }
    };
    
    // Partial specialization for arrays
    template<typename T, size_t N>
    struct TypeInfo<T[N]> {
        static constexpr const char* name() {
            return "array";
        }
        
        static constexpr size_t size() {
            return sizeof(T) * N;
        }
        
        static constexpr bool is_primitive() {
            return false;
        }
    };
    
    // Function template with specialization
    template<typename T>
    void print_type_info(T&& value) {
        std::cout << "Type: " << TypeInfo<std::decay_t<T>>::name() << std::endl;
        std::cout << "Size: " << TypeInfo<std::decay_t<T>>::size() << " bytes" << std::endl;
        std::cout << "Is primitive: " << std::boolalpha << TypeInfo<std::decay_t<T>>::is_primitive() << std::endl;
    }
    
    // Class template with member specialization
    template<typename T>
    class Container {
    public:
        void process() {
            process_impl<T>();
        }
        
    private:
        template<typename U>
        void process_impl() {
            std::cout << "Generic processing" << std::endl;
        }
        
        template<>
        void process_impl<int>() {
            std::cout << "Specialized processing for int" << std::endl;
        }
        
        template<>
        void process_impl<double>() {
            std::cout << "Specialized processing for double" << std::endl;
        }
    };
    
    void demonstrateTemplateSpecialization() {
        std::cout << "\n=== Template Specialization ===" << std::endl;
        
        // Test type info specializations
        print_type_info(42);
        print_type_info(3.14);
        print_type_info(std::string("Hello"));
        
        int* ptr = nullptr;
        print_type_info(ptr);
        
        int arr[10];
        print_type_info(arr);
        
        // Test class template specialization
        Container<int> int_container;
        Container<double> double_container;
        Container<std::string> string_container;
        
        int_container.process();
        double_container.process();
        string_container.process();
    }
}

// Example 4: Variadic Templates
namespace VariadicTemplates {
    
    // Basic variadic template
    template<typename... Args>
    void print_args(Args... args) {
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }
    
    // Variadic template with fold expressions
    template<typename... Args>
    auto sum(Args... args) {
        return (args + ...);
    }
    
    template<typename... Args>
    auto product(Args... args) {
        return (args * ...);
    }
    
    template<typename... Args>
    bool all_true(Args... args) {
        return (args && ...);
    }
    
    template<typename... Args>
    bool any_true(Args... args) {
        return (args || ...);
    }
    
    // Variadic template with parameter pack expansion
    template<typename T, typename... Args>
    void print_with_type(T first, Args... args) {
        std::cout << "Type: " << typeid(T).name() << ", Value: " << first << std::endl;
        if constexpr (sizeof...(args) > 0) {
            print_with_type(args...);
        }
    }
    
    // Variadic template with perfect forwarding
    template<typename... Args>
    auto make_tuple_forward(Args&&... args) {
        return std::make_tuple(std::forward<Args>(args)...);
    }
    
    // Variadic template with SFINAE
    template<typename... Args>
    auto safe_sum(Args... args) -> std::enable_if_t<(std::is_arithmetic_v<Args> && ...), decltype((args + ...))> {
        return (args + ...);
    }
    
    // Variadic template class
    template<typename... Types>
    class VariadicClass {
    public:
        VariadicClass(Types... args) : data_(args...) {}
        
        template<size_t Index>
        auto get() -> decltype(std::get<Index>(data_)) {
            return std::get<Index>(data_);
        }
        
        template<typename T>
        bool contains() const {
            return (std::is_same_v<T, Types> || ...);
        }
        
        static constexpr size_t size() {
            return sizeof...(Types);
        }
        
    private:
        std::tuple<Types...> data_;
    };
    
    // Variadic template with concepts (C++20)
    template<typename... Args>
    requires (std::integral<Args> && ...)
    auto integral_sum(Args... args) {
        return (args + ...);
    }
    
    void demonstrateVariadicTemplates() {
        std::cout << "\n=== Variadic Templates ===" << std::endl;
        
        // Test basic variadic template
        print_args(1, 2, 3, 4, 5);
        print_args("Hello", "World", 42, 3.14);
        
        // Test fold expressions
        std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl;
        std::cout << "Product: " << product(2, 3, 4) << std::endl;
        std::cout << "All true: " << std::boolalpha << all_true(true, true, true) << std::endl;
        std::cout << "Any true: " << std::boolalpha << any_true(false, false, true) << std::endl;
        
        // Test parameter pack expansion
        print_with_type(42, 3.14, "Hello", true);
        
        // Test perfect forwarding
        auto tuple = make_tuple_forward(1, 2.5, std::string("Hello"));
        std::cout << "Tuple size: " << std::tuple_size_v<decltype(tuple)> << std::endl;
        
        // Test SFINAE with variadic templates
        std::cout << "Safe sum: " << safe_sum(1, 2, 3, 4, 5) << std::endl;
        
        // Test variadic template class
        VariadicClass<int, double, std::string> vc(42, 3.14, "Hello");
        std::cout << "VC size: " << vc.size() << std::endl;
        std::cout << "VC contains int: " << std::boolalpha << vc.contains<int>() << std::endl;
        std::cout << "VC contains float: " << std::boolalpha << vc.contains<float>() << std::endl;
        
        // Test with concepts
        std::cout << "Integral sum: " << integral_sum(1, 2, 3, 4, 5) << std::endl;
    }
}

// Example 5: Modern C++ Metaprogramming
namespace ModernMetaprogramming {
    
    // constexpr functions for compile-time computation
    constexpr int factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
    
    constexpr int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // constexpr class for compile-time data structures
    template<size_t N>
    struct CompileTimeArray {
        int data[N];
        
        constexpr CompileTimeArray() : data{} {}
        
        constexpr int& operator[](size_t index) {
            return data[index];
        }
        
        constexpr const int& operator[](size_t index) const {
            return data[index];
        }
        
        constexpr size_t size() const {
            return N;
        }
        
        constexpr int sum() const {
            int result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += data[i];
            }
            return result;
        }
    };
    
    // Template metaprogramming with if constexpr
    template<typename T>
    void process_type(T&& value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Processing integral: " << value << std::endl;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "Processing floating point: " << value << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "Processing string: " << value << std::endl;
        } else {
            std::cout << "Processing unknown type" << std::endl;
        }
    }
    
    // Concepts for template constraints
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
    void print_container_info(const T& container) {
        std::cout << "Container size: " << container.size() << std::endl;
    }
    
    // Template metaprogramming with auto
    template<typename T>
    auto get_type_info() {
        if constexpr (std::is_integral_v<T>) {
            return "integral";
        } else if constexpr (std::is_floating_point_v<T>) {
            return "floating_point";
        } else {
            return "other";
        }
    }
    
    // Template metaprogramming with decltype
    template<typename T>
    auto get_value_type(T&& container) -> decltype(*container.begin()) {
        return *container.begin();
    }
    
    void demonstrateModernMetaprogramming() {
        std::cout << "\n=== Modern C++ Metaprogramming ===" << std::endl;
        
        // Test constexpr functions
        constexpr int fact_5 = factorial(5);
        constexpr int fib_10 = fibonacci(10);
        
        std::cout << "Factorial of 5: " << fact_5 << std::endl;
        std::cout << "Fibonacci of 10: " << fib_10 << std::endl;
        
        // Test constexpr class
        constexpr CompileTimeArray<5> array;
        constexpr int sum = array.sum();
        std::cout << "Compile-time array sum: " << sum << std::endl;
        
        // Test if constexpr
        process_type(42);
        process_type(3.14);
        process_type(std::string("Hello"));
        
        // Test concepts
        std::cout << "Square of 5: " << square(5) << std::endl;
        std::cout << "Square of 3.14: " << square(3.14) << std::endl;
        
        std::vector<int> vec{1, 2, 3, 4, 5};
        print_container_info(vec);
        
        // Test auto return type
        std::cout << "Type info for int: " << get_type_info<int>() << std::endl;
        std::cout << "Type info for double: " << get_type_info<double>() << std::endl;
        std::cout << "Type info for string: " << get_type_info<std::string>() << std::endl;
        
        // Test decltype
        std::cout << "First element type: " << typeid(get_value_type(vec)).name() << std::endl;
    }
}

// Example 6: Advanced Template Patterns
namespace AdvancedTemplatePatterns {
    
    // CRTP (Curiously Recurring Template Pattern)
    template<typename Derived>
    class Base {
    public:
        void interface() {
            static_cast<Derived*>(this)->implementation();
        }
        
        void common_operation() {
            std::cout << "Common operation in base" << std::endl;
        }
    };
    
    class Derived1 : public Base<Derived1> {
    public:
        void implementation() {
            std::cout << "Implementation in Derived1" << std::endl;
        }
    };
    
    class Derived2 : public Base<Derived2> {
    public:
        void implementation() {
            std::cout << "Implementation in Derived2" << std::endl;
        }
    };
    
    // Template Template Parameters
    template<template<typename> class Container, typename T>
    class Wrapper {
    private:
        Container<T> data_;
        
    public:
        Wrapper() = default;
        
        template<typename... Args>
        Wrapper(Args&&... args) : data_(std::forward<Args>(args)...) {}
        
        void add(const T& value) {
            data_.push_back(value);
        }
        
        size_t size() const {
            return data_.size();
        }
        
        void print() const {
            for (const auto& item : data_) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    };
    
    // Type Erasure Pattern
    class AnyType {
    private:
        struct Concept {
            virtual ~Concept() = default;
            virtual void print() const = 0;
            virtual std::unique_ptr<Concept> clone() const = 0;
        };
        
        template<typename T>
        struct Model : Concept {
            T data_;
            
            Model(T data) : data_(std::move(data)) {}
            
            void print() const override {
                std::cout << data_ << std::endl;
            }
            
            std::unique_ptr<Concept> clone() const override {
                return std::make_unique<Model<T>>(data_);
            }
        };
        
        std::unique_ptr<Concept> concept_;
        
    public:
        template<typename T>
        AnyType(T&& value) : concept_(std::make_unique<Model<std::decay_t<T>>>(std::forward<T>(value))) {}
        
        AnyType(const AnyType& other) : concept_(other.concept_->clone()) {}
        
        AnyType& operator=(const AnyType& other) {
            if (this != &other) {
                concept_ = other.concept_->clone();
            }
            return *this;
        }
        
        void print() const {
            concept_->print();
        }
    };
    
    // Expression Templates
    template<typename T>
    class Vector {
    private:
        std::vector<T> data_;
        
    public:
        Vector(size_t size) : data_(size) {}
        
        Vector(const std::vector<T>& data) : data_(data) {}
        
        T& operator[](size_t index) {
            return data_[index];
        }
        
        const T& operator[](size_t index) const {
            return data_[index];
        }
        
        size_t size() const {
            return data_.size();
        }
        
        template<typename Expr>
        Vector& operator=(const Expr& expr) {
            for (size_t i = 0; i < size(); ++i) {
                data_[i] = expr[i];
            }
            return *this;
        }
    };
    
    template<typename LHS, typename RHS>
    class VectorSum {
    private:
        const LHS& lhs_;
        const RHS& rhs_;
        
    public:
        VectorSum(const LHS& lhs, const RHS& rhs) : lhs_(lhs), rhs_(rhs) {}
        
        auto operator[](size_t index) const {
            return lhs_[index] + rhs_[index];
        }
        
        size_t size() const {
            return lhs_.size();
        }
    };
    
    template<typename LHS, typename RHS>
    auto operator+(const LHS& lhs, const RHS& rhs) {
        return VectorSum<LHS, RHS>(lhs, rhs);
    }
    
    void demonstrateAdvancedTemplatePatterns() {
        std::cout << "\n=== Advanced Template Patterns ===" << std::endl;
        
        // Test CRTP
        Derived1 d1;
        Derived2 d2;
        
        d1.interface();
        d2.interface();
        
        // Test Template Template Parameters
        Wrapper<std::vector, int> wrapper;
        wrapper.add(1);
        wrapper.add(2);
        wrapper.add(3);
        
        std::cout << "Wrapper size: " << wrapper.size() << std::endl;
        wrapper.print();
        
        // Test Type Erasure
        AnyType any1(42);
        AnyType any2(3.14);
        AnyType any3(std::string("Hello"));
        
        any1.print();
        any2.print();
        any3.print();
        
        // Test Expression Templates
        Vector<int> v1({1, 2, 3, 4, 5});
        Vector<int> v2({2, 3, 4, 5, 6});
        Vector<int> v3(5);
        
        v3 = v1 + v2;
        
        std::cout << "Expression template result: ";
        for (size_t i = 0; i < v3.size(); ++i) {
            std::cout << v3[i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Template Metaprogramming Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced template metaprogramming techniques including\n"
              << "SFINAE, type traits, template specialization, variadic templates, and modern C++\n"
              << "metaprogramming with concepts and constexpr.\n" << std::endl;
    
    // Demonstrate various template metaprogramming techniques
    SFINAE::demonstrateSFINAE();
    TypeTraits::demonstrateTypeTraits();
    TemplateSpecialization::demonstrateTemplateSpecialization();
    VariadicTemplates::demonstrateVariadicTemplates();
    ModernMetaprogramming::demonstrateModernMetaprogramming();
    AdvancedTemplatePatterns::demonstrateAdvancedTemplatePatterns();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. SFINAE enables conditional template instantiation based on type properties" << std::endl;
    std::cout << "2. Type traits provide compile-time type information and manipulation" << std::endl;
    std::cout << "3. Template specialization allows custom behavior for specific types" << std::endl;
    std::cout << "4. Variadic templates enable functions and classes with variable arguments" << std::endl;
    std::cout << "5. Modern C++ features like concepts and constexpr improve metaprogramming" << std::endl;
    std::cout << "6. Advanced patterns like CRTP and type erasure provide powerful abstractions" << std::endl;
    std::cout << "7. Template metaprogramming enables compile-time computation and optimization" << std::endl;
    std::cout << "8. Understanding template metaprogramming is essential for modern C++ development" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++20 -Wall -Wextra -O2 -o advanced_template_metaprogramming 01_Advanced_Template_Metaprogramming.cpp
 * 
 * Using Clang:
 * clang++ -std=c++20 -Wall -Wextra -O2 -o advanced_template_metaprogramming 01_Advanced_Template_Metaprogramming.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++20 /EHsc /O2 01_Advanced_Template_Metaprogramming.cpp
 * 
 * Running:
 * ./advanced_template_metaprogramming (Linux/macOS)
 * advanced_template_metaprogramming.exe (Windows)
 * 
 * Note: This lesson requires C++20 for some features.
 * C++17 is the minimum required version.
 * 
 * Advanced Template Metaprogramming Notes:
 * - SFINAE enables conditional template instantiation based on type properties
 * - Type traits provide compile-time type information and manipulation
 * - Template specialization allows custom behavior for specific types
 * - Variadic templates enable functions and classes with variable arguments
 * - Modern C++ features like concepts and constexpr improve metaprogramming
 * - Advanced patterns like CRTP and type erasure provide powerful abstractions
 * - Template metaprogramming enables compile-time computation and optimization
 * - Understanding template metaprogramming is essential for modern C++ development
 */"""
