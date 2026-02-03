#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <array>
#include <tuple>
#include <functional>

// Demonstrates C++ templates and advanced features
int main() {
    std::cout << "C++ Templates Demonstration" << std::endl;
    std::cout << "===========================" << std::endl;
    
    // 1. Function templates
    std::cout << "\n1. FUNCTION TEMPLATES:" << std::endl;
    
    template<typename T>
    T maximum(T a, T b) {
        return (a > b) ? a : b;
    }
    
    template<typename T>
    T minimum(T a, T b) {
        return (a < b) ? a : b;
    }
    
    template<typename T>
    void swap_values(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
    
    int int_a = 10, int_b = 20;
    double double_a = 3.14, double_b = 2.71;
    std::string str_a = "hello", str_b = "world";
    
    std::cout << "maximum(10, 20) = " << maximum(int_a, int_b) << std::endl;
    std::cout << "maximum(3.14, 2.71) = " << maximum(double_a, double_b) << std::endl;
    std::cout << "maximum(\"hello\", \"world\") = " << maximum(str_a, str_b) << std::endl;
    
    std::cout << "Before swap: a = " << int_a << ", b = " << int_b << std::endl;
    swap_values(int_a, int_b);
    std::cout << "After swap: a = " << int_a << ", b = " << int_b << std::endl;
    
    // 2. Class templates
    std::cout << "\n2. CLASS TEMPLATES:" << std::endl;
    
    template<typename T>
    class Stack {
    private:
        std::vector<T> data;
        
    public:
        void push(const T& item) {
            data.push_back(item);
        }
        
        void pop() {
            if (!data.empty()) {
                data.pop_back();
            }
        }
        
        T& top() {
            if (data.empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return data.back();
        }
        
        const T& top() const {
            if (data.empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return data.back();
        }
        
        bool empty() const {
            return data.empty();
        }
        
        size_t size() const {
            return data.size();
        }
        
        void display() const {
            std::cout << "Stack contents: ";
            for (const auto& item : data) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    };
    
    Stack<int> int_stack;
    Stack<std::string> str_stack;
    
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    int_stack.display();
    
    str_stack.push("first");
    str_stack.push("second");
    str_stack.push("third");
    str_stack.display();
    
    // 3. Template specialization
    std::cout << "\n3. TEMPLATE SPECIALIZATION:" << std::endl;
    
    template<typename T>
    class Container {
    public:
        void add(const T& item) {
            std::cout << "Generic container adding: " << item << std::endl;
        }
    };
    
    // Specialization for strings
    template<>
    class Container<std::string> {
    public:
        void add(const std::string& item) {
            std::cout << "String container adding: \"" << item << "\"" << std::endl;
        }
    };
    
    Container<int> int_container;
    Container<std::string> str_container;
    
    int_container.add(42);
    str_container.add("hello");
    
    // 4. Template metaprogramming
    std::cout << "\n4. TEMPLATE METAPROGRAMMING:" << std::endl;
    
    // Factorial at compile time
    template<int N>
    struct Factorial {
        static constexpr int value = N * Factorial<N - 1>::value;
    };
    
    template<>
    struct Factorial<0> {
        static constexpr int value = 1;
    };
    
    // Fibonacci at compile time
    template<int N>
    struct Fibonacci {
        static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
    };
    
    template<>
    struct Fibonacci<0> {
        static constexpr int value = 0;
    };
    
    template<>
    struct Fibonacci<1> {
        static constexpr int value = 1;
    };
    
    std::cout << "Factorial<5> = " << Factorial<5>::value << std::endl;
    std::cout << "Factorial<10> = " << Factorial<10>::value << std::endl;
    
    std::cout << "Fibonacci<10> = " << Fibonacci<10>::value << std::endl;
    std::cout << "Fibonacci<15> = " << Fibonacci<15>::value << std::endl;
    
    // 5. Type traits
    std::cout << "\n5. TYPE TRAITS:" << std::endl;
    
    template<typename T>
    void print_type_info() {
        std::cout << "Type: " << typeid(T).name() << std::endl;
        std::cout << "  Is integral: " << std::boolalpha << std::is_integral_v<T> << std::endl;
        std::cout << "  Is floating point: " << std::boolalpha << std::is_floating_point_v<T> << std::endl;
        std::cout << "  Is pointer: " << std::boolalpha << std::is_pointer_v<T> << std::endl;
        std::cout << "  Is reference: " << std::boolalpha << std::is_reference_v<T> << std::endl;
        std::cout << "  Size: " << sizeof(T) << " bytes" << std::endl;
    }
    
    print_type_info<int>();
    print_type_info<double>();
    print_type_info<std::string>();
    
    // 6. Variadic templates
    std::cout << "\n6. VARIADIC TEMPLATES:" << std::endl;
    
    template<typename... Args>
    void print_all(Args... args) {
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }
    
    template<typename... Args>
    auto sum_all(Args... args) {
        return (args + ...);
    }
    
    template<typename... Args>
    auto multiply_all(Args... args) {
        return (args * ...);
    }
    
    print_all(1, 2, 3, 4, 5);
    print_all("Hello", "World", "C++", "Templates");
    
    std::cout << "Sum of 1, 2, 3, 4, 5: " << sum_all(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Product of 2, 3, 4: " << multiply_all(2, 3, 4) << std::endl;
    
    // 7. Template with multiple parameters
    std::cout << "\n7. TEMPLATE WITH MULTIPLE PARAMETERS:" << std::endl;
    
    template<typename T, typename U>
    class Pair {
    private:
        T first;
        U second;
        
    public:
        Pair(const T& first, const U& second) : first(first), second(second) {}
        
        T get_first() const { return first; }
        U get_second() const { return second; }
        
        void set_first(const T& value) { first = value; }
        void set_second(const U& value) { second = value; }
        
        void display() const {
            std::cout << "Pair(" << first << ", " << second << ")" << std::endl;
        }
    };
    
    Pair<int, std::string> pair1(42, "hello");
    Pair<double, double> pair2(3.14, 2.71);
    
    pair1.display();
    pair2.display();
    
    // 8. Template template parameters
    std::cout << "\n8. TEMPLATE TEMPLATE PARAMETERS:" << std::endl;
    
    template<template<typename> class Container, typename T>
    class ContainerWrapper {
    private:
        Container<T> container;
        
    public:
        void add(const T& item) {
            container.push_back(item);
        }
        
        void display() const {
            std::cout << "Container contents: ";
            for (const auto& item : container) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    };
    
    ContainerWrapper<std::vector, int> wrapper;
    wrapper.add(1);
    wrapper.add(2);
    wrapper.add(3);
    wrapper.display();
    
    // 9. SFINAE (Substitution Failure Is Not An Error)
    std::cout << "\n9. SFINAE:" << std::endl;
    
    template<typename T>
    typename std::enable_if<std::is_integral_v<T>, void>::type
    process_integral(T value) {
        std::cout << "Processing integral value: " << value << std::endl;
    }
    
    template<typename T>
    typename std::enable_if<std::is_floating_point_v<T>, void>::type
    process_floating_point(T value) {
        std::cout << "Processing floating point value: " << value << std::endl;
    }
    
    template<typename T>
    typename std::enable_if<std::is_same_v<T, std::string>, void>::type
    process_string(T value) {
        std::cout << "Processing string value: \"" << value << "\"" << std::endl;
    }
    
    process_integral(42);
    process_floating_point(3.14);
    process_string(std::string("hello"));
    
    // 10. Template aliases
    std::cout << "\n10. TEMPLATE ALIASES:" << std::endl;
    
    template<typename T>
    using Vector = std::vector<T>;
    
    template<typename T>
    using Pair = std::pair<T, T>;
    
    template<typename T>
    using Function = std::function<T()>;
    
    Vector<int> int_vector = {1, 2, 3, 4, 5};
    Pair<double> double_pair = {3.14, 2.71};
    Function<int> int_function = []() { return 42; };
    
    std::cout << "Vector size: " << int_vector.size() << std::endl;
    std::cout << "Pair: (" << double_pair.first << ", " << double_pair.second << ")" << std::endl;
    std::cout << "Function result: " << int_function() << std::endl;
    
    // 11. Template with constexpr
    std::cout << "\n11. TEMPLATE WITH CONSTEXPR:" << std::endl;
    
    template<typename T>
    constexpr T power(T base, int exponent) {
        T result = 1;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }
    
    constexpr int result1 = power(2, 10);
    constexpr double result2 = power(2.0, 5);
    
    std::cout << "2^10 = " << result1 << std::endl;
    std::cout << "2.0^5 = " << result2 << std::endl;
    
    // 12. Template with concepts (C++20 style simulation)
    std::cout << "\n12. TEMPLATE WITH CONCEPTS:" << std::endl;
    
    template<typename T>
    void print_if_printable(const T& value) {
        if constexpr (std::is_same_v<T, std::string> || std::is_arithmetic_v<T>) {
            std::cout << "Printable value: " << value << std::endl;
        } else {
            std::cout << "Non-printable type" << std::endl;
        }
    }
    
    print_if_printable(42);
    print_if_printable(3.14);
    print_if_printable(std::string("hello"));
    print_if_printable(std::vector<int>{1, 2, 3});
    
    // 13. Template with perfect forwarding
    std::cout << "\n13. TEMPLATE WITH PERFECT FORWARDING:" << std::endl;
    
    template<typename T>
    class Wrapper {
    private:
        T value;
        
    public:
        template<typename U>
        Wrapper(U&& u) : value(std::forward<U>(u)) {}
        
        const T& get() const { return value; }
        T& get() { return value; }
        
        void display() const {
            std::cout << "Wrapper value: " << value << std::endl;
        }
    };
    
    Wrapper<std::string> wrapper1("hello");
    Wrapper<int> wrapper2(42);
    
    wrapper1.display();
    wrapper2.display();
    
    // 14. Template with tuple
    std::cout << "\n14. TEMPLATE WITH TUPLE:" << std::endl;
    
    template<typename... Args>
    void print_tuple(const std::tuple<Args...>& t) {
        std::cout << "Tuple: ";
        std::apply([](const auto&... args) {
            ((std::cout << args << " "), ...);
        }, t);
        std::cout << std::endl;
    }
    
    auto tuple1 = std::make_tuple(1, 2.5, std::string("hello"));
    auto tuple2 = std::make_tuple(std::string("world"), 42, 3.14);
    
    print_tuple(tuple1);
    print_tuple(tuple2);
    
    // 15. Template with array
    std::cout << "\n15. TEMPLATE WITH ARRAY:" << std::endl;
    
    template<typename T, size_t N>
    class ArrayWrapper {
    private:
        std::array<T, N> data;
        
    public:
        ArrayWrapper(std::initializer_list<T> init) {
            size_t i = 0;
            for (const auto& item : init) {
                if (i < N) {
                    data[i++] = item;
                }
            }
        }
        
        T& operator[](size_t index) {
            return data[index];
        }
        
        const T& operator[](size_t index) const {
            return data[index];
        }
        
        size_t size() const { return N; }
        
        void display() const {
            std::cout << "Array: ";
            for (size_t i = 0; i < N; ++i) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
    };
    
    ArrayWrapper<int, 5> array1 = {1, 2, 3, 4, 5};
    ArrayWrapper<std::string, 3> array2 = {"hello", "world", "cpp"};
    
    array1.display();
    array2.display();
    
    std::cout << "\nTemplates demonstration completed!" << std::endl;
    return 0;
}
