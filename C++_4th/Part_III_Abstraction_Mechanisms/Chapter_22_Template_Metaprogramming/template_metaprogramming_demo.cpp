#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <tuple>

// Demonstrates template metaprogramming concepts
int main() {
    std::cout << "Template Metaprogramming Demonstration" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // 1. Basic Template Metaprogramming
    std::cout << "\n1. BASIC TEMPLATE METAPROGRAMMING:" << std::endl;
    
    // Compile-time factorial calculation
    template<int N>
    struct Factorial {
        static const int value = N * Factorial<N-1>::value;
    };
    
    template<>
    struct Factorial<0> {
        static const int value = 1;
    };
    
    // Compile-time power calculation
    template<int Base, int Exponent>
    struct Power {
        static const int value = Base * Power<Base, Exponent-1>::value;
    };
    
    template<int Base>
    struct Power<Base, 0> {
        static const int value = 1;
    };
    
    // Compile-time Fibonacci calculation
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
    
    std::cout << "Compile-time calculations:" << std::endl;
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;
    std::cout << "2^8: " << Power<2, 8>::value << std::endl;
    std::cout << "Fibonacci(10): " << Fibonacci<10>::value << std::endl;
    
    // 2. SFINAE (Substitution Failure Is Not An Error)
    std::cout << "\n2. SFINAE (SUBSTITUTION FAILURE IS NOT AN ERROR):" << std::endl;
    
    // SFINAE with enable_if
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    add_one(T value) {
        std::cout << "Integer version: ";
        return value + 1;
    }
    
    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    add_one(T value) {
        std::cout << "Floating point version: ";
        return value + 1.0;
    }
    
    template<typename T>
    typename std::enable_if<std::is_pointer<T>::value, T>::type
    add_one(T value) {
        std::cout << "Pointer version: ";
        return value + 1;
    }
    
    std::cout << "SFINAE examples:" << std::endl;
    std::cout << add_one(5) << std::endl;
    std::cout << add_one(3.14) << std::endl;
    int x = 10;
    std::cout << add_one(&x) << std::endl;
    
    // SFINAE with decltype
    template<typename T>
    auto has_size_method(T&& t) -> decltype(t.size(), std::true_type{}) {
        return std::true_type{};
    }
    
    std::false_type has_size_method(...) {
        return std::false_type{};
    }
    
    std::cout << "\nSFINAE with decltype:" << std::endl;
    std::vector<int> vec = {1, 2, 3};
    std::cout << "Vector has size method: " << has_size_method(vec) << std::endl;
    std::cout << "Int has size method: " << has_size_method(42) << std::endl;
    
    // 3. Type Traits
    std::cout << "\n3. TYPE TRAITS:" << std::endl;
    
    // Custom type traits
    template<typename T>
    struct is_container {
        template<typename U>
        static auto test(int) -> decltype(
            std::declval<U>().begin(),
            std::declval<U>().end(),
            std::declval<U>().size(),
            std::true_type{}
        );
        
        template<typename>
        static std::false_type test(...);
        
        static const bool value = decltype(test<T>(0))::value;
    };
    
    // Type transformation traits
    template<typename T>
    struct remove_reference_and_const {
        using type = std::remove_const_t<std::remove_reference_t<T>>;
    };
    
    template<typename T>
    using remove_reference_and_const_t = typename remove_reference_and_const<T>::type;
    
    std::cout << "Type traits examples:" << std::endl;
    std::cout << "is_container<vector<int>>: " << is_container<std::vector<int>>::value << std::endl;
    std::cout << "is_container<int>: " << is_container<int>::value << std::endl;
    std::cout << "is_container<string>: " << is_container<std::string>::value << std::endl;
    
    // 4. Variadic Templates
    std::cout << "\n4. VARIADIC TEMPLATES:" << std::endl;
    
    // Variadic template function
    template<typename... Args>
    void print_all(Args... args) {
        (std::cout << ... << args) << std::endl;  // C++17 fold expression
    }
    
    // Variadic template class
    template<typename... Types>
    struct TypeList {
        static const size_t size = sizeof...(Types);
    };
    
    template<typename T, typename... Types>
    struct TypeList<T, Types...> {
        using head = T;
        using tail = TypeList<Types...>;
        static const size_t size = sizeof...(Types) + 1;
    };
    
    // Variadic template with perfect forwarding
    template<typename... Args>
    auto make_tuple_forward(Args&&... args) {
        return std::make_tuple(std::forward<Args>(args)...);
    }
    
    std::cout << "Variadic template examples:" << std::endl;
    print_all("Hello", " ", "World", " ", 42, " ", 3.14);
    
    using MyTypeList = TypeList<int, double, std::string>;
    std::cout << "TypeList size: " << MyTypeList::size << std::endl;
    
    auto tup = make_tuple_forward(1, 2.0, "hello");
    std::cout << "Tuple created with perfect forwarding" << std::endl;
    
    // 5. Template Specialization
    std::cout << "\n5. TEMPLATE SPECIALIZATION:" << std::endl;
    
    // Primary template
    template<typename T>
    struct TypeInfo {
        static const char* name() { return "Unknown type"; }
        static const size_t size = sizeof(T);
    };
    
    // Specialization for int
    template<>
    struct TypeInfo<int> {
        static const char* name() { return "int"; }
        static const size_t size = sizeof(int);
    };
    
    // Specialization for double
    template<>
    struct TypeInfo<double> {
        static const char* name() { return "double"; }
        static const size_t size = sizeof(double);
    };
    
    // Specialization for std::string
    template<>
    struct TypeInfo<std::string> {
        static const char* name() { return "std::string"; }
        static const size_t size = sizeof(std::string);
    };
    
    std::cout << "Template specialization examples:" << std::endl;
    std::cout << "TypeInfo<int>::name(): " << TypeInfo<int>::name() << std::endl;
    std::cout << "TypeInfo<double>::name(): " << TypeInfo<double>::name() << std::endl;
    std::cout << "TypeInfo<std::string>::name(): " << TypeInfo<std::string>::name() << std::endl;
    std::cout << "TypeInfo<char>::name(): " << TypeInfo<char>::name() << std::endl;
    
    // 6. Partial Specialization
    std::cout << "\n6. PARTIAL SPECIALIZATION:" << std::endl;
    
    // Primary template
    template<typename T, typename U>
    struct IsSame {
        static const bool value = false;
    };
    
    // Partial specialization for same types
    template<typename T>
    struct IsSame<T, T> {
        static const bool value = true;
    };
    
    // Template for pointer types
    template<typename T>
    struct IsPointer {
        static const bool value = false;
    };
    
    template<typename T>
    struct IsPointer<T*> {
        static const bool value = true;
    };
    
    std::cout << "Partial specialization examples:" << std::endl;
    std::cout << "IsSame<int, int>::value: " << IsSame<int, int>::value << std::endl;
    std::cout << "IsSame<int, double>::value: " << IsSame<int, double>::value << std::endl;
    std::cout << "IsPointer<int>::value: " << IsPointer<int>::value << std::endl;
    std::cout << "IsPointer<int*>::value: " << IsPointer<int*>::value << std::endl;
    
    // 7. Compile-time Computation
    std::cout << "\n7. COMPILE-TIME COMPUTATION:" << std::endl;
    
    // Compile-time string length
    template<size_t N>
    struct StringLength {
        static const size_t value = N - 1;  // Excluding null terminator
    };
    
    // Compile-time array sum
    template<typename T, size_t N>
    struct ArraySum {
        static const T value = ArraySum<T, N-1>::value + T{};
    };
    
    template<typename T>
    struct ArraySum<T, 0> {
        static const T value = T{};
    };
    
    // Compile-time prime checking
    template<int N, int D>
    struct IsPrimeHelper {
        static const bool value = (N % D != 0) && IsPrimeHelper<N, D-1>::value;
    };
    
    template<int N>
    struct IsPrimeHelper<N, 1> {
        static const bool value = true;
    };
    
    template<int N>
    struct IsPrime {
        static const bool value = IsPrimeHelper<N, N-1>::value;
    };
    
    template<>
    struct IsPrime<2> {
        static const bool value = true;
    };
    
    template<>
    struct IsPrime<1> {
        static const bool value = false;
    };
    
    std::cout << "Compile-time computation examples:" << std::endl;
    std::cout << "String length of 'Hello': " << StringLength<6>::value << std::endl;
    std::cout << "Is 17 prime: " << IsPrime<17>::value << std::endl;
    std::cout << "Is 15 prime: " << IsPrime<15>::value << std::endl;
    std::cout << "Is 2 prime: " << IsPrime<2>::value << std::endl;
    
    // 8. Template Aliases
    std::cout << "\n8. TEMPLATE ALIASES:" << std::endl;
    
    // Template alias for function pointers
    template<typename T>
    using FunctionPtr = T(*)();
    
    // Template alias for containers
    template<typename T>
    using Vector = std::vector<T>;
    
    // Template alias for pairs
    template<typename T, typename U>
    using Pair = std::pair<T, U>;
    
    std::cout << "Template alias examples:" << std::endl;
    
    // Function pointer alias
    FunctionPtr<int> int_func = []() { return 42; };
    std::cout << "Function pointer result: " << int_func() << std::endl;
    
    // Container alias
    Vector<int> int_vector = {1, 2, 3, 4, 5};
    std::cout << "Vector size: " << int_vector.size() << std::endl;
    
    // Pair alias
    Pair<int, std::string> my_pair = {42, "hello"};
    std::cout << "Pair: " << my_pair.first << ", " << my_pair.second << std::endl;
    
    // 9. Advanced Template Patterns
    std::cout << "\n9. ADVANCED TEMPLATE PATTERNS:" << std::endl;
    
    // CRTP (Curiously Recurring Template Pattern)
    template<typename Derived>
    class BaseCRTP {
    public:
        void interface() {
            static_cast<Derived*>(this)->implementation();
        }
    };
    
    class DerivedCRTP : public BaseCRTP<DerivedCRTP> {
    public:
        void implementation() {
            std::cout << "CRTP implementation called" << std::endl;
        }
    };
    
    // Template method pattern
    template<typename T>
    class TemplateMethod {
    public:
        void algorithm() {
            step1();
            step2();
            step3();
        }
    private:
        virtual void step1() = 0;
        virtual void step2() = 0;
        virtual void step3() = 0;
    };
    
    class ConcreteTemplate : public TemplateMethod<ConcreteTemplate> {
    private:
        void step1() override { std::cout << "Step 1" << std::endl; }
        void step2() override { std::cout << "Step 2" << std::endl; }
        void step3() override { std::cout << "Step 3" << std::endl; }
    };
    
    std::cout << "Advanced template patterns:" << std::endl;
    DerivedCRTP crtp;
    crtp.interface();
    
    ConcreteTemplate concrete;
    concrete.algorithm();
    
    // 10. Template Metaprogramming Performance
    std::cout << "\n10. TEMPLATE METAPROGRAMMING PERFORMANCE:" << std::endl;
    
    // Compile-time vs runtime computation
    constexpr int compile_time_factorial(int n) {
        return (n <= 1) ? 1 : n * compile_time_factorial(n - 1);
    }
    
    int runtime_factorial(int n) {
        return (n <= 1) ? 1 : n * runtime_factorial(n - 1);
    }
    
    std::cout << "Compile-time factorial(10): " << compile_time_factorial(10) << std::endl;
    std::cout << "Runtime factorial(10): " << runtime_factorial(10) << std::endl;
    
    // Template vs function performance
    template<int N>
    struct TemplateFactorial {
        static const int value = N * TemplateFactorial<N-1>::value;
    };
    
    template<>
    struct TemplateFactorial<0> {
        static const int value = 1;
    };
    
    std::cout << "Template factorial(10): " << TemplateFactorial<10>::value << std::endl;
    
    std::cout << "\nTemplate metaprogramming demonstration completed!" << std::endl;
    return 0;
}
