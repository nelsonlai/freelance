#include <iostream>
#include <type_traits>
#include <vector>
#include <string>

// Template metaprogramming examples demonstrating compile-time computation

// 1. Basic template metaprogramming - compile-time factorial
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

// 2. Template metaprogramming with constexpr (C++11)
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// 3. Type traits and SFINAE (Substitution Failure Is Not An Error)
template<typename T>
struct IsPointer {
    static const bool value = false;
};

template<typename T>
struct IsPointer<T*> {
    static const bool value = true;
};

// 4. SFINAE example - enable_if
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
process_integer(T value) {
    std::cout << "Processing integer: " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
process_floating_point(T value) {
    std::cout << "Processing floating point: " << value << std::endl;
}

// 5. Variadic templates (C++11)
template<typename... Args>
struct TypeList {};

// 6. Template specialization for different argument counts
template<typename T>
struct TypeCount {
    static const int value = 1;
};

template<typename T, typename... Args>
struct TypeCount<TypeList<T, Args...>> {
    static const int value = 1 + TypeCount<TypeList<Args...>>::value;
};

// 7. Compile-time string manipulation
template<char... Chars>
struct String {
    static constexpr const char value[] = {Chars..., '\0'};
};

template<char... Chars>
constexpr const char String<Chars...>::value[];

// 8. Template metaprogramming for type manipulation
template<typename T>
struct RemovePointer {
    using type = T;
};

template<typename T>
struct RemovePointer<T*> {
    using type = T;
};

template<typename T>
struct RemovePointer<T**> {
    using type = T;
};

// 9. Compile-time loop unrolling
template<int N>
struct UnrollLoop {
    template<typename Func>
    static void execute(Func func) {
        func(N - 1);
        UnrollLoop<N - 1>::execute(func);
    }
};

template<>
struct UnrollLoop<0> {
    template<typename Func>
    static void execute(Func func) {
        // Base case - do nothing
    }
};

// 10. Template metaprogramming for container operations
template<typename Container>
struct ContainerTraits {
    using value_type = typename Container::value_type;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    
    static const bool is_sequential = false;
    static const bool is_associative = false;
};

template<typename T>
struct ContainerTraits<std::vector<T>> {
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    
    static const bool is_sequential = true;
    static const bool is_associative = false;
};

// 11. Compile-time conditionals
template<bool Condition, typename TrueType, typename FalseType>
struct Conditional {
    using type = TrueType;
};

template<typename TrueType, typename FalseType>
struct Conditional<false, TrueType, FalseType> {
    using type = FalseType;
};

// 12. Template metaprogramming for function overloading
template<typename T>
struct IsContainer {
    template<typename U>
    static auto test(int) -> decltype(std::declval<U>().begin(), std::declval<U>().end(), std::true_type{});
    
    template<typename U>
    static std::false_type test(...);
    
    static const bool value = decltype(test<T>(0))::value;
};

// 13. Compile-time type checking
template<typename T>
void print_type_info() {
    std::cout << "Type information for T:" << std::endl;
    std::cout << "  Is pointer: " << std::boolalpha << std::is_pointer<T>::value << std::endl;
    std::cout << "  Is reference: " << std::boolalpha << std::is_reference<T>::value << std::endl;
    std::cout << "  Is const: " << std::boolalpha << std::is_const<T>::value << std::endl;
    std::cout << "  Is integral: " << std::boolalpha << std::is_integral<T>::value << std::endl;
    std::cout << "  Is floating point: " << std::boolalpha << std::is_floating_point<T>::value << std::endl;
    std::cout << "  Size: " << sizeof(T) << " bytes" << std::endl;
}

// 14. Template metaprogramming for algorithm selection
template<typename Iterator>
struct IteratorCategory {
    using type = typename std::iterator_traits<Iterator>::iterator_category;
};

template<typename Iterator>
void select_algorithm(Iterator first, Iterator last) {
    using category = typename IteratorCategory<Iterator>::type;
    
    if (std::is_same<category, std::random_access_iterator_tag>::value) {
        std::cout << "Using random access algorithm" << std::endl;
    } else if (std::is_same<category, std::bidirectional_iterator_tag>::value) {
        std::cout << "Using bidirectional algorithm" << std::endl;
    } else {
        std::cout << "Using forward algorithm" << std::endl;
    }
}

// 15. Compile-time computation with constexpr
template<typename T>
constexpr T power(T base, int exponent) {
    return (exponent == 0) ? 1 : base * power(base, exponent - 1);
}

// 16. Template metaprogramming for type erasure
template<typename T>
class TypeEraser {
private:
    void* data;
    void (*destroy)(void*);
    void (*copy)(void*, const void*);
    
public:
    template<typename U>
    TypeEraser(U&& value) : data(new U(std::forward<U>(value))) {
        destroy = [](void* ptr) { delete static_cast<U*>(ptr); };
        copy = [](void* dest, const void* src) { 
            new(dest) U(*static_cast<const U*>(src)); 
        };
    }
    
    ~TypeEraser() {
        if (data) {
            destroy(data);
        }
    }
    
    TypeEraser(const TypeEraser& other) : data(nullptr) {
        if (other.data) {
            data = new char[sizeof(T)];
            copy(data, other.data);
            destroy = other.destroy;
            copy = other.copy;
        }
    }
    
    TypeEraser& operator=(const TypeEraser& other) {
        if (this != &other) {
            if (data) {
                destroy(data);
            }
            if (other.data) {
                data = new char[sizeof(T)];
                copy(data, other.data);
                destroy = other.destroy;
                copy = other.copy;
            } else {
                data = nullptr;
            }
        }
        return *this;
    }
};

int main() {
    std::cout << "Template Metaprogramming Examples" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // 1. Compile-time factorial
    std::cout << "\n1. Compile-time factorial:" << std::endl;
    std::cout << "Factorial<5>::value = " << Factorial<5>::value << std::endl;
    std::cout << "Factorial<10>::value = " << Factorial<10>::value << std::endl;
    
    // 2. constexpr factorial
    std::cout << "\n2. constexpr factorial:" << std::endl;
    constexpr int fact5 = factorial(5);
    constexpr int fact10 = factorial(10);
    std::cout << "factorial(5) = " << fact5 << std::endl;
    std::cout << "factorial(10) = " << fact10 << std::endl;
    
    // 3. Type traits
    std::cout << "\n3. Type traits:" << std::endl;
    std::cout << "IsPointer<int>::value = " << std::boolalpha << IsPointer<int>::value << std::endl;
    std::cout << "IsPointer<int*>::value = " << std::boolalpha << IsPointer<int*>::value << std::endl;
    std::cout << "IsPointer<int**>::value = " << std::boolalpha << IsPointer<int**>::value << std::endl;
    
    // 4. SFINAE with enable_if
    std::cout << "\n4. SFINAE with enable_if:" << std::endl;
    process_integer(42);
    process_floating_point(3.14);
    // process_integer(3.14);  // This would cause a compile error
    
    // 5. Variadic templates
    std::cout << "\n5. Variadic templates:" << std::endl;
    using MyTypeList = TypeList<int, double, std::string, char>;
    std::cout << "Type count: " << TypeCount<MyTypeList>::value << std::endl;
    
    // 6. Compile-time string
    std::cout << "\n6. Compile-time string:" << std::endl;
    using HelloString = String<'H', 'e', 'l', 'l', 'o'>;
    std::cout << "Compile-time string: " << HelloString::value << std::endl;
    
    // 7. Type manipulation
    std::cout << "\n7. Type manipulation:" << std::endl;
    using IntType = RemovePointer<int*>::type;
    using IntType2 = RemovePointer<int**>::type;
    std::cout << "RemovePointer<int*>::type is int: " << std::boolalpha 
              << std::is_same<IntType, int>::value << std::endl;
    std::cout << "RemovePointer<int**>::type is int: " << std::boolalpha 
              << std::is_same<IntType2, int>::value << std::endl;
    
    // 8. Loop unrolling
    std::cout << "\n8. Loop unrolling:" << std::endl;
    UnrollLoop<5>::execute([](int i) {
        std::cout << "Unrolled iteration: " << i << std::endl;
    });
    
    // 9. Container traits
    std::cout << "\n9. Container traits:" << std::endl;
    std::cout << "std::vector is sequential: " << std::boolalpha 
              << ContainerTraits<std::vector<int>>::is_sequential << std::endl;
    
    // 10. Compile-time conditionals
    std::cout << "\n10. Compile-time conditionals:" << std::endl;
    using TrueType = Conditional<true, int, double>::type;
    using FalseType = Conditional<false, int, double>::type;
    std::cout << "Conditional<true, int, double>::type is int: " << std::boolalpha 
              << std::is_same<TrueType, int>::value << std::endl;
    std::cout << "Conditional<false, int, double>::type is double: " << std::boolalpha 
              << std::is_same<FalseType, double>::value << std::endl;
    
    // 11. Container detection
    std::cout << "\n11. Container detection:" << std::endl;
    std::cout << "std::vector is container: " << std::boolalpha 
              << IsContainer<std::vector<int>>::value << std::endl;
    std::cout << "int is container: " << std::boolalpha 
              << IsContainer<int>::value << std::endl;
    
    // 12. Type information
    std::cout << "\n12. Type information:" << std::endl;
    print_type_info<int>();
    print_type_info<int*>();
    print_type_info<const int&>();
    
    // 13. Algorithm selection
    std::cout << "\n13. Algorithm selection:" << std::endl;
    std::vector<int> vec{1, 2, 3, 4, 5};
    select_algorithm(vec.begin(), vec.end());
    
    // 14. Compile-time power
    std::cout << "\n14. Compile-time power:" << std::endl;
    constexpr int pow2_5 = power(2, 5);
    constexpr int pow3_4 = power(3, 4);
    std::cout << "2^5 = " << pow2_5 << std::endl;
    std::cout << "3^4 = " << pow3_4 << std::endl;
    
    // 15. Type erasure
    std::cout << "\n15. Type erasure:" << std::endl;
    TypeEraser<int> eraser1(42);
    TypeEraser<std::string> eraser2("Hello");
    TypeEraser<double> eraser3(3.14);
    
    std::cout << "Type erasure examples created successfully" << std::endl;
    
    std::cout << "\nTemplate metaprogramming examples completed!" << std::endl;
    return 0;
}
