/*
 * Lesson 13.3: Variadic Templates
 * 
 * This file demonstrates variadic templates, parameter packs,
 * fold expressions, and advanced template patterns.
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <type_traits>
#include <utility>
#include <functional>

// Example 1: Basic Variadic Templates
namespace BasicVariadicTemplates {
    
    // Variadic template for printing arguments
    template<typename... Args>
    void print_args(Args... args) {
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }
    
    // Variadic template for counting arguments
    template<typename... Args>
    constexpr size_t count_args(Args... args) {
        return sizeof...(args);
    }
    
    // Variadic template for summing arguments
    template<typename... Args>
    constexpr auto sum_args(Args... args) {
        return (args + ...);
    }
    
    // Variadic template for multiplying arguments
    template<typename... Args>
    constexpr auto multiply_args(Args... args) {
        return (args * ...);
    }
    
    // Variadic template for finding maximum
    template<typename T, typename... Args>
    constexpr T max_args(T first, Args... args) {
        if constexpr (sizeof...(args) == 0) {
            return first;
        } else {
            return std::max(first, max_args(args...));
        }
    }
    
    // Variadic template for finding minimum
    template<typename T, typename... Args>
    constexpr T min_args(T first, Args... args) {
        if constexpr (sizeof...(args) == 0) {
            return first;
        } else {
            return std::min(first, min_args(args...));
        }
    }
    
    // Variadic template for checking if all arguments are true
    template<typename... Args>
    constexpr bool all_true(Args... args) {
        return (args && ...);
    }
    
    // Variadic template for checking if any argument is true
    template<typename... Args>
    constexpr bool any_true(Args... args) {
        return (args || ...);
    }
    
    // Variadic template for concatenating strings
    template<typename... Args>
    std::string concatenate_strings(Args... args) {
        return (std::string(args) + ...);
    }
    
    // Variadic template for creating tuple
    template<typename... Args>
    auto make_tuple(Args... args) {
        return std::make_tuple(args...);
    }
    
    // Variadic template for creating array
    template<typename T, typename... Args>
    std::array<T, sizeof...(Args) + 1> make_array(T first, Args... args) {
        return {first, args...};
    }
}

// Example 2: Parameter Pack Manipulation
namespace ParameterPackManipulation {
    
    // Get first argument
    template<typename First, typename... Rest>
    First get_first(First first, Rest... rest) {
        return first;
    }
    
    // Get last argument
    template<typename Last>
    Last get_last(Last last) {
        return last;
    }
    
    template<typename First, typename... Rest>
    auto get_last(First first, Rest... rest) {
        return get_last(rest...);
    }
    
    // Get argument at specific index
    template<size_t Index, typename First, typename... Rest>
    auto get_at_index(First first, Rest... rest) {
        if constexpr (Index == 0) {
            return first;
        } else {
            return get_at_index<Index - 1>(rest...);
        }
    }
    
    // Reverse parameter pack
    template<typename... Args>
    auto reverse_pack(Args... args) {
        return std::make_tuple(args...);
    }
    
    // Count specific type in parameter pack
    template<typename T, typename... Args>
    constexpr size_t count_type(Args... args) {
        return (std::is_same_v<T, Args> + ...);
    }
    
    // Check if all types are same
    template<typename T, typename... Args>
    constexpr bool all_same_type(Args... args) {
        return (std::is_same_v<T, Args> && ...);
    }
    
    // Check if any type is same
    template<typename T, typename... Args>
    constexpr bool any_same_type(Args... args) {
        return (std::is_same_v<T, Args> || ...);
    }
    
    // Filter parameter pack by type
    template<typename T, typename... Args>
    auto filter_by_type(Args... args) {
        std::vector<T> result;
        (..., (std::is_same_v<T, Args> ? (void)result.push_back(args) : (void)0));
        return result;
    }
    
    // Transform parameter pack
    template<typename Func, typename... Args>
    auto transform_pack(Func func, Args... args) {
        return std::make_tuple(func(args)...);
    }
    
    // Apply function to each argument
    template<typename Func, typename... Args>
    void for_each_arg(Func func, Args... args) {
        (func(args), ...);
    }
    
    // Apply function with index to each argument
    template<typename Func, typename... Args>
    void for_each_arg_with_index(Func func, Args... args) {
        size_t index = 0;
        (func(index++, args), ...);
    }
}

// Example 3: Advanced Variadic Patterns
namespace AdvancedVariadicPatterns {
    
    // Variadic template class
    template<typename... Types>
    class VariadicClass {
    public:
        static constexpr size_t count = sizeof...(Types);
        
        template<size_t Index>
        using type_at = std::tuple_element_t<Index, std::tuple<Types...>>;
        
        static void print_types() {
            ((std::cout << typeid(Types).name() << " "), ...);
            std::cout << std::endl;
        }
        
        template<typename T>
        static constexpr bool contains_type() {
            return (std::is_same_v<T, Types> || ...);
        }
        
        template<typename T>
        static constexpr size_t index_of_type() {
            size_t index = 0;
            bool found = false;
            ((!found && std::is_same_v<T, Types> ? (found = true) : (++index)), ...);
            return found ? index : static_cast<size_t>(-1);
        }
    };
    
    // Variadic template function with perfect forwarding
    template<typename Func, typename... Args>
    auto perfect_forward(Func&& func, Args&&... args) {
        return func(std::forward<Args>(args)...);
    }
    
    // Variadic template for function composition
    template<typename Func1, typename Func2>
    auto compose(Func1&& f1, Func2&& f2) {
        return [f1 = std::forward<Func1>(f1), f2 = std::forward<Func2>(f2)]
               (auto&&... args) {
                   return f1(f2(std::forward<decltype(args)>(args)...));
               };
    }
    
    // Variadic template for function composition with multiple functions
    template<typename Func1, typename... Funcs>
    auto compose_multiple(Func1&& f1, Funcs&&... funcs) {
        if constexpr (sizeof...(funcs) == 0) {
            return std::forward<Func1>(f1);
        } else {
            return compose(std::forward<Func1>(f1), 
                          compose_multiple(std::forward<Funcs>(funcs)...));
        }
    }
    
    // Variadic template for function overloading
    template<typename... Funcs>
    struct overload_set : Funcs... {
        using Funcs::operator()...;
        
        overload_set(Funcs... funcs) : Funcs(std::forward<Funcs>(funcs))... {}
    };
    
    template<typename... Funcs>
    auto make_overload_set(Funcs&&... funcs) {
        return overload_set<std::decay_t<Funcs>...>(std::forward<Funcs>(funcs)...);
    }
    
    // Variadic template for type list
    template<typename... Types>
    struct type_list {
        static constexpr size_t size = sizeof...(Types);
        
        template<size_t Index>
        using type_at = std::tuple_element_t<Index, std::tuple<Types...>>;
        
        template<typename T>
        static constexpr bool contains() {
            return (std::is_same_v<T, Types> || ...);
        }
        
        template<typename T>
        static constexpr size_t index_of() {
            size_t index = 0;
            bool found = false;
            ((!found && std::is_same_v<T, Types> ? (found = true) : (++index)), ...);
            return found ? index : static_cast<size_t>(-1);
        }
        
        template<template<typename> class Predicate>
        static constexpr bool all_satisfy() {
            return (Predicate<Types>::value && ...);
        }
        
        template<template<typename> class Predicate>
        static constexpr bool any_satisfy() {
            return (Predicate<Types>::value || ...);
        }
    };
    
    // Variadic template for value list
    template<auto... Values>
    struct value_list {
        static constexpr size_t size = sizeof...(Values);
        
        template<size_t Index>
        static constexpr auto value_at = std::get<Index>(std::make_tuple(Values...));
        
        template<auto Value>
        static constexpr bool contains() {
            return ((Values == Value) || ...);
        }
        
        template<auto Value>
        static constexpr size_t index_of() {
            size_t index = 0;
            bool found = false;
            ((!found && (Values == Value) ? (found = true) : (++index)), ...);
            return found ? index : static_cast<size_t>(-1);
        }
    };
}

// Example 4: Variadic Templates with SFINAE
namespace VariadicSFINAE {
    
    // Check if all types are integral
    template<typename... Types>
    struct all_integral {
        static constexpr bool value = (std::is_integral_v<Types> && ...);
    };
    
    // Check if all types are floating point
    template<typename... Types>
    struct all_floating_point {
        static constexpr bool value = (std::is_floating_point_v<Types> && ...);
    };
    
    // Check if all types are same
    template<typename T, typename... Types>
    struct all_same {
        static constexpr bool value = (std::is_same_v<T, Types> && ...);
    };
    
    // Check if all types are different
    template<typename... Types>
    struct all_different {
        static constexpr bool value = true;
    };
    
    template<typename T, typename... Types>
    struct all_different<T, Types...> {
        static constexpr bool value = (!std::is_same_v<T, Types> && ...) && 
                                      all_different<Types...>::value;
    };
    
    // Check if all types are constructible
    template<typename T, typename... Types>
    struct all_constructible {
        static constexpr bool value = (std::is_constructible_v<T, Types> && ...);
    };
    
    // Check if all types are convertible
    template<typename T, typename... Types>
    struct all_convertible {
        static constexpr bool value = (std::is_convertible_v<Types, T> && ...);
    };
    
    // Variadic template function with SFINAE
    template<typename... Types>
    typename std::enable_if_t<all_integral<Types...>::value, int>
    sum_integrals(Types... values) {
        return (values + ...);
    }
    
    template<typename... Types>
    typename std::enable_if_t<all_floating_point<Types...>::value, double>
    sum_floating_points(Types... values) {
        return (values + ...);
    }
    
    // Variadic template function with concepts (C++20 style)
    template<typename... Types>
    requires (std::is_integral_v<Types> && ...)
    auto sum_integrals_concept(Types... values) {
        return (values + ...);
    }
    
    template<typename... Types>
    requires (std::is_floating_point_v<Types> && ...)
    auto sum_floating_points_concept(Types... values) {
        return (values + ...);
    }
}

// Example 5: Variadic Templates with Fold Expressions
namespace FoldExpressions {
    
    // Unary fold expressions
    template<typename... Args>
    constexpr bool all_true_unary(Args... args) {
        return (... && args);
    }
    
    template<typename... Args>
    constexpr bool any_true_unary(Args... args) {
        return (... || args);
    }
    
    template<typename... Args>
    constexpr auto sum_unary(Args... args) {
        return (... + args);
    }
    
    template<typename... Args>
    constexpr auto multiply_unary(Args... args) {
        return (... * args);
    }
    
    // Binary fold expressions
    template<typename... Args>
    constexpr bool all_true_binary(Args... args) {
        return (args && ... && true);
    }
    
    template<typename... Args>
    constexpr bool any_true_binary(Args... args) {
        return (args || ... || false);
    }
    
    template<typename... Args>
    constexpr auto sum_binary(Args... args) {
        return (args + ... + 0);
    }
    
    template<typename... Args>
    constexpr auto multiply_binary(Args... args) {
        return (args * ... * 1);
    }
    
    // Fold expressions with custom operators
    template<typename... Args>
    constexpr auto concatenate_strings_fold(Args... args) {
        return (std::string(args) + ... + std::string(""));
    }
    
    template<typename... Args>
    constexpr auto max_fold(Args... args) {
        return (args + ... + std::numeric_limits<std::common_type_t<Args...>>::min());
    }
    
    template<typename... Args>
    constexpr auto min_fold(Args... args) {
        return (args + ... + std::numeric_limits<std::common_type_t<Args...>>::max());
    }
    
    // Fold expressions with function calls
    template<typename Func, typename... Args>
    void call_function_fold(Func func, Args... args) {
        (func(args), ...);
    }
    
    template<typename Func, typename... Args>
    auto transform_fold(Func func, Args... args) {
        return std::make_tuple(func(args)...);
    }
    
    // Fold expressions with conditional logic
    template<typename... Args>
    constexpr size_t count_non_zero(Args... args) {
        return (static_cast<size_t>(args != 0) + ...);
    }
    
    template<typename... Args>
    constexpr size_t count_even(Args... args) {
        return (static_cast<size_t>(args % 2 == 0) + ...);
    }
    
    template<typename... Args>
    constexpr size_t count_odd(Args... args) {
        return (static_cast<size_t>(args % 2 != 0) + ...);
    }
    
    // Fold expressions with type checking
    template<typename T, typename... Args>
    constexpr size_t count_type_instances(Args... args) {
        return (static_cast<size_t>(std::is_same_v<T, Args>) + ...);
    }
    
    template<typename... Args>
    constexpr size_t count_integral_types(Args... args) {
        return (static_cast<size_t>(std::is_integral_v<Args>) + ...);
    }
    
    template<typename... Args>
    constexpr size_t count_floating_point_types(Args... args) {
        return (static_cast<size_t>(std::is_floating_point_v<Args>) + ...);
    }
}

// Function to demonstrate basic variadic templates
void demonstrateBasicVariadicTemplates() {
    std::cout << "=== Basic Variadic Templates Demonstration ===" << std::endl;
    
    // Print arguments
    BasicVariadicTemplates::print_args(1, 2, 3, 4, 5);
    BasicVariadicTemplates::print_args("Hello", "World", 42, 3.14);
    BasicVariadicTemplates::print_args('A', 'B', 'C');
    
    // Count arguments
    std::cout << "Count of (1, 2, 3, 4, 5): " << BasicVariadicTemplates::count_args(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Count of (\"Hello\", \"World\", 42): " << BasicVariadicTemplates::count_args("Hello", "World", 42) << std::endl;
    
    // Sum arguments
    std::cout << "Sum of (1, 2, 3, 4, 5): " << BasicVariadicTemplates::sum_args(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Sum of (10.5, 20.5, 30.5): " << BasicVariadicTemplates::sum_args(10.5, 20.5, 30.5) << std::endl;
    
    // Multiply arguments
    std::cout << "Product of (2, 3, 4): " << BasicVariadicTemplates::multiply_args(2, 3, 4) << std::endl;
    std::cout << "Product of (1.5, 2.5, 3.5): " << BasicVariadicTemplates::multiply_args(1.5, 2.5, 3.5) << std::endl;
    
    // Find maximum
    std::cout << "Max of (1, 5, 3, 9, 2): " << BasicVariadicTemplates::max_args(1, 5, 3, 9, 2) << std::endl;
    std::cout << "Max of (10.5, 20.5, 15.5): " << BasicVariadicTemplates::max_args(10.5, 20.5, 15.5) << std::endl;
    
    // Find minimum
    std::cout << "Min of (1, 5, 3, 9, 2): " << BasicVariadicTemplates::min_args(1, 5, 3, 9, 2) << std::endl;
    std::cout << "Min of (10.5, 20.5, 15.5): " << BasicVariadicTemplates::min_args(10.5, 20.5, 15.5) << std::endl;
    
    // Boolean operations
    std::cout << "All true (true, true, true): " << BasicVariadicTemplates::all_true(true, true, true) << std::endl;
    std::cout << "All true (true, false, true): " << BasicVariadicTemplates::all_true(true, false, true) << std::endl;
    std::cout << "Any true (false, false, true): " << BasicVariadicTemplates::any_true(false, false, true) << std::endl;
    std::cout << "Any true (false, false, false): " << BasicVariadicTemplates::any_true(false, false, false) << std::endl;
    
    // String concatenation
    std::cout << "Concatenated: " << BasicVariadicTemplates::concatenate_strings("Hello", " ", "World", "!") << std::endl;
    
    // Make tuple
    auto tuple = BasicVariadicTemplates::make_tuple(1, 2.5, "Hello", 'A');
    std::cout << "Tuple: (" << std::get<0>(tuple) << ", " << std::get<1>(tuple) 
              << ", " << std::get<2>(tuple) << ", " << std::get<3>(tuple) << ")" << std::endl;
    
    // Make array
    auto array = BasicVariadicTemplates::make_array(1, 2, 3, 4, 5);
    std::cout << "Array: ";
    for (const auto& elem : array) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate parameter pack manipulation
void demonstrateParameterPackManipulation() {
    std::cout << "\n=== Parameter Pack Manipulation Demonstration ===" << std::endl;
    
    // Get first argument
    std::cout << "First of (1, 2, 3, 4, 5): " << ParameterPackManipulation::get_first(1, 2, 3, 4, 5) << std::endl;
    std::cout << "First of (\"Hello\", \"World\", 42): " << ParameterPackManipulation::get_first("Hello", "World", 42) << std::endl;
    
    // Get last argument
    std::cout << "Last of (1, 2, 3, 4, 5): " << ParameterPackManipulation::get_last(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Last of (\"Hello\", \"World\", 42): " << ParameterPackManipulation::get_last("Hello", "World", 42) << std::endl;
    
    // Get argument at specific index
    std::cout << "At index 2 of (1, 2, 3, 4, 5): " << ParameterPackManipulation::get_at_index<2>(1, 2, 3, 4, 5) << std::endl;
    std::cout << "At index 0 of (\"Hello\", \"World\", 42): " << ParameterPackManipulation::get_at_index<0>("Hello", "World", 42) << std::endl;
    
    // Count specific type
    std::cout << "Count of int in (1, 2.5, 3, 4.5, 5): " << ParameterPackManipulation::count_type<int>(1, 2.5, 3, 4.5, 5) << std::endl;
    std::cout << "Count of double in (1, 2.5, 3, 4.5, 5): " << ParameterPackManipulation::count_type<double>(1, 2.5, 3, 4.5, 5) << std::endl;
    
    // Check if all types are same
    std::cout << "All int in (1, 2, 3, 4, 5): " << ParameterPackManipulation::all_same_type<int>(1, 2, 3, 4, 5) << std::endl;
    std::cout << "All int in (1, 2.5, 3, 4.5, 5): " << ParameterPackManipulation::all_same_type<int>(1, 2.5, 3, 4.5, 5) << std::endl;
    
    // Check if any type is same
    std::cout << "Any int in (1, 2.5, 3, 4.5, 5): " << ParameterPackManipulation::any_same_type<int>(1, 2.5, 3, 4.5, 5) << std::endl;
    std::cout << "Any double in (1, 2.5, 3, 4.5, 5): " << ParameterPackManipulation::any_same_type<double>(1, 2.5, 3, 4.5, 5) << std::endl;
    
    // Filter by type
    auto ints = ParameterPackManipulation::filter_by_type<int>(1, 2.5, 3, 4.5, 5);
    std::cout << "Filtered ints: ";
    for (const auto& i : ints) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Transform parameter pack
    auto transformed = ParameterPackManipulation::transform_pack([](int x) { return x * x; }, 1, 2, 3, 4, 5);
    std::cout << "Transformed (squares): ";
    std::apply([](auto... args) { ((std::cout << args << " "), ...); }, transformed);
    std::cout << std::endl;
    
    // For each argument
    std::cout << "For each argument: ";
    ParameterPackManipulation::for_each_arg([](auto arg) { std::cout << arg << " "; }, 1, 2, 3, 4, 5);
    std::cout << std::endl;
    
    // For each argument with index
    std::cout << "For each argument with index: ";
    ParameterPackManipulation::for_each_arg_with_index([](size_t index, auto arg) { 
        std::cout << "[" << index << "]=" << arg << " "; 
    }, "Hello", "World", 42);
    std::cout << std::endl;
}

// Function to demonstrate advanced variadic patterns
void demonstrateAdvancedVariadicPatterns() {
    std::cout << "\n=== Advanced Variadic Patterns Demonstration ===" << std::endl;
    
    // Variadic template class
    using MyVariadicClass = AdvancedVariadicPatterns::VariadicClass<int, double, std::string, char>;
    std::cout << "VariadicClass count: " << MyVariadicClass::count << std::endl;
    std::cout << "VariadicClass types: ";
    MyVariadicClass::print_types();
    
    std::cout << "Contains int: " << MyVariadicClass::contains_type<int>() << std::endl;
    std::cout << "Contains float: " << MyVariadicClass::contains_type<float>() << std::endl;
    std::cout << "Index of int: " << MyVariadicClass::index_of_type<int>() << std::endl;
    std::cout << "Index of double: " << MyVariadicClass::index_of_type<double>() << std::endl;
    
    // Perfect forwarding
    auto result = AdvancedVariadicPatterns::perfect_forward([](int a, double b, const std::string& c) {
        return std::to_string(a) + " " + std::to_string(b) + " " + c;
    }, 42, 3.14, "Hello");
    std::cout << "Perfect forwarding result: " << result << std::endl;
    
    // Function composition
    auto square = [](int x) { return x * x; };
    auto add_one = [](int x) { return x + 1; };
    auto composed = AdvancedVariadicPatterns::compose(square, add_one);
    std::cout << "Composed function (square(add_one(5))): " << composed(5) << std::endl;
    
    // Multiple function composition
    auto double_val = [](int x) { return x * 2; };
    auto composed_multiple = AdvancedVariadicPatterns::compose_multiple(square, add_one, double_val);
    std::cout << "Multiple composed function (square(add_one(double(5)))): " << composed_multiple(5) << std::endl;
    
    // Overload set
    auto overloaded = AdvancedVariadicPatterns::make_overload_set(
        [](int x) { return x * 2; },
        [](double x) { return x * 3.0; },
        [](const std::string& x) { return x + x; }
    );
    
    std::cout << "Overloaded with int: " << overloaded(5) << std::endl;
    std::cout << "Overloaded with double: " << overloaded(3.14) << std::endl;
    std::cout << "Overloaded with string: " << overloaded(std::string("Hello")) << std::endl;
    
    // Type list
    using MyTypeList = AdvancedVariadicPatterns::type_list<int, double, std::string, char>;
    std::cout << "TypeList size: " << MyTypeList::size << std::endl;
    std::cout << "TypeList contains int: " << MyTypeList::contains<int>() << std::endl;
    std::cout << "TypeList index of double: " << MyTypeList::index_of<double>() << std::endl;
    std::cout << "All types are integral: " << MyTypeList::all_satisfy<std::is_integral>() << std::endl;
    std::cout << "Any type is integral: " << MyTypeList::any_satisfy<std::is_integral>() << std::endl;
    
    // Value list
    using MyValueList = AdvancedVariadicPatterns::value_list<1, 2, 3, 4, 5>;
    std::cout << "ValueList size: " << MyValueList::size << std::endl;
    std::cout << "ValueList contains 3: " << MyValueList::contains<3>() << std::endl;
    std::cout << "ValueList index of 4: " << MyValueList::index_of<4>() << std::endl;
    std::cout << "ValueList value at index 2: " << MyValueList::value_at<2> << std::endl;
}

// Function to demonstrate variadic templates with SFINAE
void demonstrateVariadicSFINAE() {
    std::cout << "\n=== Variadic Templates with SFINAE Demonstration ===" << std::endl;
    
    // Type checking
    std::cout << "All integral (int, long, short): " << VariadicSFINAE::all_integral<int, long, short>::value << std::endl;
    std::cout << "All integral (int, double, short): " << VariadicSFINAE::all_integral<int, double, short>::value << std::endl;
    
    std::cout << "All floating point (float, double): " << VariadicSFINAE::all_floating_point<float, double>::value << std::endl;
    std::cout << "All floating point (float, int, double): " << VariadicSFINAE::all_floating_point<float, int, double>::value << std::endl;
    
    std::cout << "All same (int, int, int): " << VariadicSFINAE::all_same<int, int, int>::value << std::endl;
    std::cout << "All same (int, double, int): " << VariadicSFINAE::all_same<int, double, int>::value << std::endl;
    
    std::cout << "All different (int, double, char): " << VariadicSFINAE::all_different<int, double, char>::value << std::endl;
    std::cout << "All different (int, int, char): " << VariadicSFINAE::all_different<int, int, char>::value << std::endl;
    
    // SFINAE functions
    std::cout << "Sum integrals (1, 2, 3, 4, 5): " << VariadicSFINAE::sum_integrals(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Sum floating points (1.5, 2.5, 3.5): " << VariadicSFINAE::sum_floating_points(1.5, 2.5, 3.5) << std::endl;
    
    // Concepts style (if supported)
    // std::cout << "Sum integrals concept (1, 2, 3, 4, 5): " << VariadicSFINAE::sum_integrals_concept(1, 2, 3, 4, 5) << std::endl;
    // std::cout << "Sum floating points concept (1.5, 2.5, 3.5): " << VariadicSFINAE::sum_floating_points_concept(1.5, 2.5, 3.5) << std::endl;
}

// Function to demonstrate fold expressions
void demonstrateFoldExpressions() {
    std::cout << "\n=== Fold Expressions Demonstration ===" << std::endl;
    
    // Unary fold expressions
    std::cout << "All true unary (true, true, true): " << FoldExpressions::all_true_unary(true, true, true) << std::endl;
    std::cout << "All true unary (true, false, true): " << FoldExpressions::all_true_unary(true, false, true) << std::endl;
    
    std::cout << "Any true unary (false, false, true): " << FoldExpressions::any_true_unary(false, false, true) << std::endl;
    std::cout << "Any true unary (false, false, false): " << FoldExpressions::any_true_unary(false, false, false) << std::endl;
    
    std::cout << "Sum unary (1, 2, 3, 4, 5): " << FoldExpressions::sum_unary(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Multiply unary (2, 3, 4): " << FoldExpressions::multiply_unary(2, 3, 4) << std::endl;
    
    // Binary fold expressions
    std::cout << "All true binary (true, true, true): " << FoldExpressions::all_true_binary(true, true, true) << std::endl;
    std::cout << "All true binary (true, false, true): " << FoldExpressions::all_true_binary(true, false, true) << std::endl;
    
    std::cout << "Any true binary (false, false, true): " << FoldExpressions::any_true_binary(false, false, true) << std::endl;
    std::cout << "Any true binary (false, false, false): " << FoldExpressions::any_true_binary(false, false, false) << std::endl;
    
    std::cout << "Sum binary (1, 2, 3, 4, 5): " << FoldExpressions::sum_binary(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Multiply binary (2, 3, 4): " << FoldExpressions::multiply_binary(2, 3, 4) << std::endl;
    
    // Custom operators
    std::cout << "Concatenate strings fold: " << FoldExpressions::concatenate_strings_fold("Hello", " ", "World", "!") << std::endl;
    
    // Function calls
    std::cout << "Call function fold: ";
    FoldExpressions::call_function_fold([](auto arg) { std::cout << arg << " "; }, 1, 2, 3, 4, 5);
    std::cout << std::endl;
    
    // Transform
    auto transformed = FoldExpressions::transform_fold([](int x) { return x * x; }, 1, 2, 3, 4, 5);
    std::cout << "Transform fold (squares): ";
    std::apply([](auto... args) { ((std::cout << args << " "), ...); }, transformed);
    std::cout << std::endl;
    
    // Conditional logic
    std::cout << "Count non-zero (0, 1, 0, 2, 0): " << FoldExpressions::count_non_zero(0, 1, 0, 2, 0) << std::endl;
    std::cout << "Count even (1, 2, 3, 4, 5): " << FoldExpressions::count_even(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Count odd (1, 2, 3, 4, 5): " << FoldExpressions::count_odd(1, 2, 3, 4, 5) << std::endl;
    
    // Type checking
    std::cout << "Count int types (1, 2.5, 3, 4.5, 5): " << FoldExpressions::count_type_instances<int>(1, 2.5, 3, 4.5, 5) << std::endl;
    std::cout << "Count integral types (1, 2.5, 3, 4.5, 5): " << FoldExpressions::count_integral_types(1, 2.5, 3, 4.5, 5) << std::endl;
    std::cout << "Count floating point types (1, 2.5, 3, 4.5, 5): " << FoldExpressions::count_floating_point_types(1, 2.5, 3, 4.5, 5) << std::endl;
}

int main() {
    std::cout << "=== Variadic Templates Demonstration ===" << std::endl;
    std::cout << "This program demonstrates variadic templates, parameter packs,\n"
              << "fold expressions, and advanced template patterns.\n" << std::endl;
    
    // Demonstrate various variadic template concepts
    demonstrateBasicVariadicTemplates();
    demonstrateParameterPackManipulation();
    demonstrateAdvancedVariadicPatterns();
    demonstrateVariadicSFINAE();
    demonstrateFoldExpressions();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Variadic templates enable functions and classes to accept variable numbers of arguments" << std::endl;
    std::cout << "2. Parameter packs can be manipulated using recursive templates and fold expressions" << std::endl;
    std::cout << "3. Fold expressions provide concise syntax for operations on parameter packs" << std::endl;
    std::cout << "4. SFINAE can be used with variadic templates for conditional instantiation" << std::endl;
    std::cout << "5. Perfect forwarding preserves value categories of arguments" << std::endl;
    std::cout << "6. Function composition and overload sets are powerful patterns" << std::endl;
    std::cout << "7. Type lists and value lists enable compile-time type and value manipulation" << std::endl;
    std::cout << "8. Variadic templates are essential for modern C++ generic programming" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o variadic_templates 03_Variadic_Templates.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o variadic_templates 03_Variadic_Templates.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Variadic_Templates.cpp
 * 
 * Running:
 * ./variadic_templates (Linux/macOS)
 * variadic_templates.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for fold expressions.
 * Some features may require C++20 for concepts.
 * 
 * Variadic Templates Notes:
 * - Variadic templates enable functions and classes to accept variable numbers of arguments
 * - Parameter packs can be manipulated using recursive templates and fold expressions
 * - Fold expressions provide concise syntax for operations on parameter packs
 * - SFINAE can be used with variadic templates for conditional instantiation
 * - Perfect forwarding preserves value categories of arguments
 * - Function composition and overload sets are powerful patterns
 * - Type lists and value lists enable compile-time type and value manipulation
 * - Variadic templates are essential for modern C++ generic programming
 */"""
