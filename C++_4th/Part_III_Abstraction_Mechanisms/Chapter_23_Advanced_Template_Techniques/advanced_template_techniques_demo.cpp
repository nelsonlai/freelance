#include <iostream>
#include <type_traits>
#include <concepts>
#include <vector>
#include <string>

// Demonstrates advanced template techniques
int main() {
    std::cout << "Advanced Template Techniques Demonstration" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // 1. Variadic Templates
    std::cout << "\n1. VARIADIC TEMPLATES:" << std::endl;
    
    // Basic variadic template
    template<typename... Args>
    void print_all(Args... args) {
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }
    
    print_all(1, 2.5, "hello", 'c');
    
    // Variadic template with fold expressions
    template<typename... Args>
    auto sum_all(Args... args) {
        return (args + ...);
    }
    
    std::cout << "  Sum: " << sum_all(1, 2, 3, 4, 5) << std::endl;
    
    // Variadic template with perfect forwarding
    template<typename... Args>
    auto make_tuple_forward(Args&&... args) {
        return std::make_tuple(std::forward<Args>(args)...);
    }
    
    auto t = make_tuple_forward(1, 2.5, std::string("hello"));
    std::cout << "  Tuple: " << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << std::endl;
    
    // 2. Template Specialization
    std::cout << "\n2. TEMPLATE SPECIALIZATION:" << std::endl;
    
    // Primary template
    template<typename T>
    struct TypeInfo {
        static const char* name() { return "unknown"; }
    };
    
    // Specialization for int
    template<>
    struct TypeInfo<int> {
        static const char* name() { return "int"; }
    };
    
    // Specialization for double
    template<>
    struct TypeInfo<double> {
        static const char* name() { return "double"; }
    };
    
    // Specialization for string
    template<>
    struct TypeInfo<std::string> {
        static const char* name() { return "string"; }
    };
    
    std::cout << "  Type info for int: " << TypeInfo<int>::name() << std::endl;
    std::cout << "  Type info for double: " << TypeInfo<double>::name() << std::endl;
    std::cout << "  Type info for string: " << TypeInfo<std::string>::name() << std::endl;
    
    // Partial specialization
    template<typename T>
    struct ContainerInfo {
        static const char* name() { return "container"; }
    };
    
    template<typename T>
    struct ContainerInfo<std::vector<T>> {
        static const char* name() { return "vector"; }
    };
    
    std::cout << "  Container info for vector<int>: " << ContainerInfo<std::vector<int>>::name() << std::endl;
    
    // 3. SFINAE (Substitution Failure Is Not An Error)
    std::cout << "\n3. SFINAE:" << std::endl;
    
    // SFINAE with enable_if
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    process_integral(T value) {
        return value * 2;
    }
    
    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    process_floating(T value) {
        return value * 3.14;
    }
    
    std::cout << "  Process integral: " << process_integral(5) << std::endl;
    std::cout << "  Process floating: " << process_floating(2.5) << std::endl;
    
    // SFINAE with decltype
    template<typename T>
    auto has_size_method(T&& t) -> decltype(t.size(), std::true_type{}) {
        return std::true_type{};
    }
    
    std::false_type has_size_method(...) {
        return std::false_type{};
    }
    
    std::vector<int> vec = {1, 2, 3};
    std::cout << "  Vector has size method: " << has_size_method(vec) << std::endl;
    std::cout << "  Int has size method: " << has_size_method(42) << std::endl;
    
    // 4. Type Traits
    std::cout << "\n4. TYPE TRAITS:" << std::endl;
    
    // Basic type traits
    std::cout << "  is_integral<int>: " << std::is_integral_v<int> << std::endl;
    std::cout << "  is_floating_point<double>: " << std::is_floating_point_v<double> << std::endl;
    std::cout << "  is_pointer<int*>: " << std::is_pointer_v<int*> << std::endl;
    std::cout << "  is_reference<int&>: " << std::is_reference_v<int&> << std::endl;
    
    // Composite type traits
    std::cout << "  is_arithmetic<int>: " << std::is_arithmetic_v<int> << std::endl;
    std::cout << "  is_arithmetic<std::string>: " << std::is_arithmetic_v<std::string> << std::endl;
    
    // Type relationships
    std::cout << "  is_same<int, int>: " << std::is_same_v<int, int> << std::endl;
    std::cout << "  is_same<int, double>: " << std::is_same_v<int, double> << std::endl;
    std::cout << "  is_base_of<std::string, std::string>: " << std::is_base_of_v<std::string, std::string> << std::endl;
    
    // 5. Template Metaprogramming
    std::cout << "\n5. TEMPLATE METAPROGRAMMING:" << std::endl;
    
    // Compile-time factorial
    template<int N>
    struct Factorial {
        static const int value = N * Factorial<N-1>::value;
    };
    
    template<>
    struct Factorial<0> {
        static const int value = 1;
    };
    
    std::cout << "  Factorial<5>: " << Factorial<5>::value << std::endl;
    std::cout << "  Factorial<10>: " << Factorial<10>::value << std::endl;
    
    // Compile-time Fibonacci
    template<int N>
    struct Fibonacci {
        static const int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
    };
    
    template<>
    struct Fibonacci<0> {
        static const int value = 0;
    };
    
    template<>
    struct Fibonacci<1> {
        static const int value = 1;
    };
    
    std::cout << "  Fibonacci<10>: " << Fibonacci<10>::value << std::endl;
    
    // 6. Concepts (C++20)
    std::cout << "\n6. CONCEPTS (C++20):" << std::endl;
    
    // Define concepts
    template<typename T>
    concept Addable = requires(T a, T b) {
        a + b;
    };
    
    template<typename T>
    concept Printable = requires(T t) {
        std::cout << t;
    };
    
    // Use concepts
    template<Addable T>
    T add_values(T a, T b) {
        return a + b;
    }
    
    template<Printable T>
    void print_value(T value) {
        std::cout << "  Value: " << value << std::endl;
    }
    
    std::cout << "  Add values: " << add_values(5, 3) << std::endl;
    std::cout << "  Add values: " << add_values(2.5, 3.7) << std::endl;
    print_value(42);
    print_value(std::string("Hello"));
    
    // 7. Template Aliases
    std::cout << "\n7. TEMPLATE ALIASES:" << std::endl;
    
    // Type alias
    template<typename T>
    using Vector = std::vector<T>;
    
    // Alias template
    template<typename T>
    using Ptr = T*;
    
    Vector<int> int_vector = {1, 2, 3, 4, 5};
    Ptr<int> int_ptr = new int(42);
    
    std::cout << "  Vector size: " << int_vector.size() << std::endl;
    std::cout << "  Pointer value: " << *int_ptr << std::endl;
    
    delete int_ptr;
    
    // 8. Template Template Parameters
    std::cout << "\n8. TEMPLATE TEMPLATE PARAMETERS:" << std::endl;
    
    template<template<typename> class Container, typename T>
    void print_container(const Container<T>& container) {
        std::cout << "  Container contents: ";
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<int> vec_int = {1, 2, 3};
    std::vector<double> vec_double = {1.1, 2.2, 3.3};
    
    print_container(vec_int);
    print_container(vec_double);
    
    // 9. CRTP (Curiously Recurring Template Pattern)
    std::cout << "\n9. CRTP (CURIOUSLY RECURRING TEMPLATE PATTERN):" << std::endl;
    
    template<typename Derived>
    class Base {
    public:
        void interface() {
            static_cast<Derived*>(this)->implementation();
        }
        
        void common_operation() {
            std::cout << "  Common operation in base" << std::endl;
        }
    };
    
    class Derived1 : public Base<Derived1> {
    public:
        void implementation() {
            std::cout << "  Implementation in Derived1" << std::endl;
        }
    };
    
    class Derived2 : public Base<Derived2> {
    public:
        void implementation() {
            std::cout << "  Implementation in Derived2" << std::endl;
        }
    };
    
    Derived1 d1;
    Derived2 d2;
    
    d1.interface();
    d2.interface();
    
    // 10. Template Argument Deduction
    std::cout << "\n10. TEMPLATE ARGUMENT DEDUCTION:" << std::endl;
    
    // Class template argument deduction (CTAD)
    std::vector vec_deduced = {1, 2, 3, 4, 5};  // C++17
    std::cout << "  Deduced vector size: " << vec_deduced.size() << std::endl;
    
    std::pair pair_deduced = {42, std::string("hello")};  // C++17
    std::cout << "  Deduced pair: " << pair_deduced.first << ", " << pair_deduced.second << std::endl;
    
    // Function template argument deduction
    auto max_val = std::max(10, 20);
    std::cout << "  Max value: " << max_val << std::endl;
    
    // 11. Template Constraints
    std::cout << "\n11. TEMPLATE CONSTRAINTS:" << std::endl;
    
    // Using requires clause
    template<typename T>
    requires std::integral<T>
    void process_integral_only(T value) {
        std::cout << "  Processing integral: " << value << std::endl;
    }
    
    template<typename T>
    requires std::floating_point<T>
    void process_floating_only(T value) {
        std::cout << "  Processing floating: " << value << std::endl;
    }
    
    process_integral_only(42);
    process_floating_only(3.14);
    
    // 12. Template Specialization with Concepts
    std::cout << "\n12. TEMPLATE SPECIALIZATION WITH CONCEPTS:" << std::endl;
    
    template<typename T>
    struct TypeCategory {
        static const char* name() { return "unknown"; }
    };
    
    template<std::integral T>
    struct TypeCategory<T> {
        static const char* name() { return "integral"; }
    };
    
    template<std::floating_point T>
    struct TypeCategory<T> {
        static const char* name() { return "floating_point"; }
    };
    
    std::cout << "  Type category for int: " << TypeCategory<int>::name() << std::endl;
    std::cout << "  Type category for double: " << TypeCategory<double>::name() << std::endl;
    
    // 13. Advanced Template Patterns
    std::cout << "\n13. ADVANCED TEMPLATE PATTERNS:" << std::endl;
    
    // Policy-based design
    template<typename T, template<typename> class Allocator = std::allocator>
    class Container {
    private:
        Allocator<T> allocator;
        T* data;
        size_t size;
        
    public:
        Container(size_t s) : size(s) {
            data = allocator.allocate(size);
        }
        
        ~Container() {
            allocator.deallocate(data, size);
        }
        
        T& operator[](size_t index) {
            return data[index];
        }
        
        size_t get_size() const { return size; }
    };
    
    Container<int> int_container(5);
    for (size_t i = 0; i < int_container.get_size(); ++i) {
        int_container[i] = static_cast<int>(i * 2);
    }
    
    std::cout << "  Container values: ";
    for (size_t i = 0; i < int_container.get_size(); ++i) {
        std::cout << int_container[i] << " ";
    }
    std::cout << std::endl;
    
    // 14. Template Metaprogramming Utilities
    std::cout << "\n14. TEMPLATE METAPROGRAMMING UTILITIES:" << std::endl;
    
    // Type list
    template<typename... Types>
    struct TypeList {};
    
    using IntList = TypeList<int, double, std::string>;
    
    // Size of type list
    template<typename List>
    struct Size;
    
    template<typename... Types>
    struct Size<TypeList<Types...>> {
        static const size_t value = sizeof...(Types);
    };
    
    std::cout << "  Type list size: " << Size<IntList>::value << std::endl;
    
    // 15. Performance Considerations
    std::cout << "\n15. PERFORMANCE CONSIDERATIONS:" << std::endl;
    
    // Template instantiation cost
    const int num_instantiations = 1000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_instantiations; ++i) {
        auto result = Factorial<10>::value;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto template_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_instantiations; ++i) {
        int result = 1;
        for (int j = 1; j <= 10; ++j) {
            result *= j;
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto runtime_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "  Template metaprogramming time: " << template_time.count() << " ns" << std::endl;
    std::cout << "  Runtime computation time: " << runtime_time.count() << " ns" << std::endl;
    std::cout << "  Template speedup: " << (double)runtime_time.count() / template_time.count() << "x" << std::endl;
    
    std::cout << "\nAdvanced template techniques demonstration completed!" << std::endl;
    return 0;
}
