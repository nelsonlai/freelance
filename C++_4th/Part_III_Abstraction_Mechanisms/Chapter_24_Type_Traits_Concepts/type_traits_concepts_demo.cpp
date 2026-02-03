#include <iostream>
#include <type_traits>
#include <concepts>
#include <vector>
#include <string>
#include <memory>

// Demonstrates type traits and concepts
int main() {
    std::cout << "Type Traits and Concepts Demonstration" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // 1. Basic Type Traits
    std::cout << "\n1. BASIC TYPE TRAITS:" << std::endl;
    
    // Primary type categories
    std::cout << "  Primary type categories:" << std::endl;
    std::cout << "    is_void<void>: " << std::is_void_v<void> << std::endl;
    std::cout << "    is_integral<int>: " << std::is_integral_v<int> << std::endl;
    std::cout << "    is_floating_point<double>: " << std::is_floating_point_v<double> << std::endl;
    std::cout << "    is_array<int[5]>: " << std::is_array_v<int[5]> << std::endl;
    std::cout << "    is_pointer<int*>: " << std::is_pointer_v<int*> << std::endl;
    std::cout << "    is_reference<int&>: " << std::is_reference_v<int&> << std::endl;
    std::cout << "    is_function<void()>: " << std::is_function_v<void()> << std::endl;
    
    // Composite type categories
    std::cout << "  Composite type categories:" << std::endl;
    std::cout << "    is_arithmetic<int>: " << std::is_arithmetic_v<int> << std::endl;
    std::cout << "    is_arithmetic<double>: " << std::is_arithmetic_v<double> << std::endl;
    std::cout << "    is_arithmetic<std::string>: " << std::is_arithmetic_v<std::string> << std::endl;
    std::cout << "    is_fundamental<int>: " << std::is_fundamental_v<int> << std::endl;
    std::cout << "    is_fundamental<std::string>: " << std::is_fundamental_v<std::string> << std::endl;
    
    // 2. Type Properties
    std::cout << "\n2. TYPE PROPERTIES:" << std::endl;
    
    // Const and volatile
    std::cout << "  Const and volatile:" << std::endl;
    std::cout << "    is_const<const int>: " << std::is_const_v<const int> << std::endl;
    std::cout << "    is_const<int>: " << std::is_const_v<int> << std::endl;
    std::cout << "    is_volatile<volatile int>: " << std::is_volatile_v<volatile int> << std::endl;
    std::cout << "    is_volatile<int>: " << std::is_volatile_v<int> << std::endl;
    
    // Signed and unsigned
    std::cout << "  Signed and unsigned:" << std::endl;
    std::cout << "    is_signed<int>: " << std::is_signed_v<int> << std::endl;
    std::cout << "    is_signed<unsigned int>: " << std::is_signed_v<unsigned int> << std::endl;
    std::cout << "    is_unsigned<unsigned int>: " << std::is_unsigned_v<unsigned int> << std::endl;
    std::cout << "    is_unsigned<int>: " << std::is_unsigned_v<int> << std::endl;
    
    // 3. Type Relationships
    std::cout << "\n3. TYPE RELATIONSHIPS:" << std::endl;
    
    // Type identity
    std::cout << "  Type identity:" << std::endl;
    std::cout << "    is_same<int, int>: " << std::is_same_v<int, int> << std::endl;
    std::cout << "    is_same<int, double>: " << std::is_same_v<int, double> << std::endl;
    std::cout << "    is_same<int, const int>: " << std::is_same_v<int, const int> << std::endl;
    
    // Base and derived
    class Base {};
    class Derived : public Base {};
    
    std::cout << "  Base and derived:" << std::endl;
    std::cout << "    is_base_of<Base, Derived>: " << std::is_base_of_v<Base, Derived> << std::endl;
    std::cout << "    is_base_of<Derived, Base>: " << std::is_base_of_v<Derived, Base> << std::endl;
    std::cout << "    is_base_of<Base, Base>: " << std::is_base_of_v<Base, Base> << std::endl;
    
    // Convertible
    std::cout << "  Convertible:" << std::endl;
    std::cout << "    is_convertible<int, double>: " << std::is_convertible_v<int, double> << std::endl;
    std::cout << "    is_convertible<double, int>: " << std::is_convertible_v<double, int> << std::endl;
    std::cout << "    is_convertible<Derived, Base>: " << std::is_convertible_v<Derived, Base> << std::endl;
    
    // 4. Type Modifications
    std::cout << "\n4. TYPE MODIFICATIONS:" << std::endl;
    
    // Remove qualifiers
    std::cout << "  Remove qualifiers:" << std::endl;
    std::cout << "    remove_const<const int>: " << typeid(std::remove_const_t<const int>).name() << std::endl;
    std::cout << "    remove_volatile<volatile int>: " << typeid(std::remove_volatile_t<volatile int>).name() << std::endl;
    std::cout << "    remove_cv<const volatile int>: " << typeid(std::remove_cv_t<const volatile int>).name() << std::endl;
    
    // Remove references and pointers
    std::cout << "  Remove references and pointers:" << std::endl;
    std::cout << "    remove_reference<int&>: " << typeid(std::remove_reference_t<int&>).name() << std::endl;
    std::cout << "    remove_pointer<int*>: " << typeid(std::remove_pointer_t<int*>).name() << std::endl;
    
    // Add qualifiers
    std::cout << "  Add qualifiers:" << std::endl;
    std::cout << "    add_const<int>: " << typeid(std::add_const_t<int>).name() << std::endl;
    std::cout << "    add_volatile<int>: " << typeid(std::add_volatile_t<int>).name() << std::endl;
    std::cout << "    add_cv<int>: " << typeid(std::add_cv_t<int>).name() << std::endl;
    
    // 5. enable_if and SFINAE
    std::cout << "\n5. ENABLE_IF AND SFINAE:" << std::endl;
    
    // Using enable_if
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
    
    // Using enable_if with void
    template<typename T>
    typename std::enable_if<std::is_pointer<T>::value>::type
    process_pointer(T ptr) {
        std::cout << "  Processing pointer: " << *ptr << std::endl;
    }
    
    int value = 42;
    process_pointer(&value);
    
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
    
    template<typename T>
    concept HasSize = requires(T t) {
        t.size();
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
    
    template<HasSize T>
    void print_size(T container) {
        std::cout << "  Size: " << container.size() << std::endl;
    }
    
    std::cout << "  Add values: " << add_values(5, 3) << std::endl;
    std::cout << "  Add values: " << add_values(2.5, 3.7) << std::endl;
    print_value(42);
    print_value(std::string("Hello"));
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    print_size(vec);
    
    // 7. Custom Type Traits
    std::cout << "\n7. CUSTOM TYPE TRAITS:" << std::endl;
    
    // Custom type trait for checking if type has operator+
    template<typename T>
    struct has_plus_operator {
    private:
        template<typename U>
        static auto test(int) -> decltype(std::declval<U>() + std::declval<U>(), std::true_type{});
        
        template<typename>
        static std::false_type test(...);
        
    public:
        static const bool value = decltype(test<T>(0))::value;
    };
    
    std::cout << "  has_plus_operator<int>: " << has_plus_operator<int>::value << std::endl;
    std::cout << "  has_plus_operator<std::string>: " << has_plus_operator<std::string>::value << std::endl;
    
    // Custom type trait for checking if type is container
    template<typename T>
    struct is_container {
    private:
        template<typename U>
        static auto test(int) -> decltype(
            std::declval<U>().begin(),
            std::declval<U>().end(),
            std::declval<U>().size(),
            std::true_type{}
        );
        
        template<typename>
        static std::false_type test(...);
        
    public:
        static const bool value = decltype(test<T>(0))::value;
    };
    
    std::cout << "  is_container<std::vector<int>>: " << is_container<std::vector<int>>::value << std::endl;
    std::cout << "  is_container<int>: " << is_container<int>::value << std::endl;
    
    // 8. Type Traits with Variadic Templates
    std::cout << "\n8. TYPE TRAITS WITH VARIADIC TEMPLATES:" << std::endl;
    
    // Check if all types are the same
    template<typename... Types>
    struct all_same;
    
    template<typename T>
    struct all_same<T> : std::true_type {};
    
    template<typename T, typename U, typename... Rest>
    struct all_same<T, U, Rest...> : std::false_type {};
    
    template<typename T, typename... Rest>
    struct all_same<T, T, Rest...> : all_same<T, Rest...> {};
    
    std::cout << "  all_same<int, int, int>: " << all_same<int, int, int>::value << std::endl;
    std::cout << "  all_same<int, double, int>: " << all_same<int, double, int>::value << std::endl;
    
    // Check if all types are integral
    template<typename... Types>
    struct all_integral : std::conjunction<std::is_integral<Types>...> {};
    
    std::cout << "  all_integral<int, long, short>: " << all_integral<int, long, short>::value << std::endl;
    std::cout << "  all_integral<int, double, long>: " << all_integral<int, double, long>::value << std::endl;
    
    // 9. Type Traits for Template Metaprogramming
    std::cout << "\n9. TYPE TRAITS FOR TEMPLATE METAPROGRAMMING:" << std::endl;
    
    // Conditional type selection
    template<bool B, typename T, typename F>
    struct conditional {
        using type = T;
    };
    
    template<typename T, typename F>
    struct conditional<false, T, F> {
        using type = F;
    };
    
    using int_or_double = std::conditional_t<true, int, double>;
    using float_or_string = std::conditional_t<false, float, std::string>;
    
    std::cout << "  int_or_double: " << typeid(int_or_double).name() << std::endl;
    std::cout << "  float_or_string: " << typeid(float_or_string).name() << std::endl;
    
    // Type transformation
    template<typename T>
    struct add_pointer {
        using type = T*;
    };
    
    template<typename T>
    struct add_reference {
        using type = T&;
    };
    
    using int_ptr = add_pointer<int>::type;
    using int_ref = add_reference<int>::type;
    
    std::cout << "  int_ptr: " << typeid(int_ptr).name() << std::endl;
    std::cout << "  int_ref: " << typeid(int_ref).name() << std::endl;
    
    // 10. Advanced Concepts
    std::cout << "\n10. ADVANCED CONCEPTS:" << std::endl;
    
    // Concept with multiple requirements
    template<typename T>
    concept Iterable = requires(T t) {
        t.begin();
        t.end();
        typename T::value_type;
    };
    
    template<typename T>
    concept Sortable = requires(T t) {
        t.begin();
        t.end();
        std::sort(t.begin(), t.end());
    };
    
    // Use advanced concepts
    template<Iterable T>
    void print_iterable(T container) {
        std::cout << "  Iterable contents: ";
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    template<Sortable T>
    void sort_and_print(T container) {
        std::sort(container.begin(), container.end());
        std::cout << "  Sorted contents: ";
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<int> numbers = {3, 1, 4, 1, 5};
    print_iterable(numbers);
    sort_and_print(numbers);
    
    // 11. Type Traits for Error Handling
    std::cout << "\n11. TYPE TRAITS FOR ERROR HANDLING:" << std::endl;
    
    // Check if type can throw
    template<typename T>
    struct is_nothrow_constructible {
        static const bool value = std::is_nothrow_constructible_v<T>;
    };
    
    std::cout << "  is_nothrow_constructible<int>: " << is_nothrow_constructible<int>::value << std::endl;
    std::cout << "  is_nothrow_constructible<std::string>: " << is_nothrow_constructible<std::string>::value << std::endl;
    
    // Check if type is trivially copyable
    template<typename T>
    struct is_trivially_copyable {
        static const bool value = std::is_trivially_copyable_v<T>;
    };
    
    std::cout << "  is_trivially_copyable<int>: " << is_trivially_copyable<int>::value << std::endl;
    std::cout << "  is_trivially_copyable<std::string>: " << is_trivially_copyable<std::string>::value << std::endl;
    
    // 12. Performance Considerations
    std::cout << "\n12. PERFORMANCE CONSIDERATIONS:" << std::endl;
    
    // Compile-time vs runtime type checking
    const int num_iterations = 1000000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_iterations; ++i) {
        if constexpr (std::is_integral_v<int>) {
            // Compile-time check
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto compile_time_check = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_iterations; ++i) {
        if (std::is_integral_v<int>) {
            // Runtime check
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto runtime_check = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "  Compile-time check time: " << compile_time_check.count() << " ns" << std::endl;
    std::cout << "  Runtime check time: " << runtime_check.count() << " ns" << std::endl;
    std::cout << "  Compile-time speedup: " << (double)runtime_check.count() / compile_time_check.count() << "x" << std::endl;
    
    // 13. Best Practices
    std::cout << "\n13. BEST PRACTICES:" << std::endl;
    
    // Use type traits for template specialization
    template<typename T>
    void process_type(T value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "  Processing integral: " << value << std::endl;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "  Processing floating point: " << value << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "  Processing string: " << value << std::endl;
        } else {
            std::cout << "  Processing unknown type" << std::endl;
        }
    }
    
    process_type(42);
    process_type(3.14);
    process_type(std::string("Hello"));
    
    // Use concepts for better error messages
    template<typename T>
    requires std::integral<T>
    void process_integral_concept(T value) {
        std::cout << "  Processing integral with concept: " << value << std::endl;
    }
    
    process_integral_concept(42);
    
    // 14. Real-world Examples
    std::cout << "\n14. REAL-WORLD EXAMPLES:" << std::endl;
    
    // Smart pointer type traits
    template<typename T>
    struct is_smart_pointer {
        static const bool value = false;
    };
    
    template<typename T>
    struct is_smart_pointer<std::unique_ptr<T>> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_smart_pointer<std::shared_ptr<T>> {
        static const bool value = true;
    };
    
    std::cout << "  is_smart_pointer<std::unique_ptr<int>>: " << is_smart_pointer<std::unique_ptr<int>>::value << std::endl;
    std::cout << "  is_smart_pointer<int*>: " << is_smart_pointer<int*>::value << std::endl;
    
    // Container type traits
    template<typename T>
    struct is_std_container {
        static const bool value = false;
    };
    
    template<typename T, typename Alloc>
    struct is_std_container<std::vector<T, Alloc>> {
        static const bool value = true;
    };
    
    template<typename T, typename Alloc>
    struct is_std_container<std::list<T, Alloc>> {
        static const bool value = true;
    };
    
    std::cout << "  is_std_container<std::vector<int>>: " << is_std_container<std::vector<int>>::value << std::endl;
    std::cout << "  is_std_container<std::string>: " << is_std_container<std::string>::value << std::endl;
    
    std::cout << "\nType traits and concepts demonstration completed!" << std::endl;
    return 0;
}
