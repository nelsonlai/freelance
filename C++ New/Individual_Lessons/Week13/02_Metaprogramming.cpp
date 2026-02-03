/*
 * Lesson 13.2: Metaprogramming
 * 
 * This file demonstrates template metaprogramming, SFINAE, type traits,
 * constexpr functions, and compile-time computations.
 */

#include <iostream>
#include <type_traits>
#include <utility>
#include <string>
#include <vector>
#include <array>
#include <limits>

// Example 1: Basic Template Metaprogramming
namespace BasicMetaprogramming {
    
    // Template for compile-time factorial
    template<int N>
    struct factorial {
        static const int value = N * factorial<N - 1>::value;
    };
    
    template<>
    struct factorial<0> {
        static const int value = 1;
    };
    
    // Template for compile-time power
    template<int Base, int Exponent>
    struct power {
        static const int value = Base * power<Base, Exponent - 1>::value;
    };
    
    template<int Base>
    struct power<Base, 0> {
        static const int value = 1;
    };
    
    // Template for compile-time Fibonacci
    template<int N>
    struct fibonacci {
        static const int value = fibonacci<N - 1>::value + fibonacci<N - 2>::value;
    };
    
    template<>
    struct fibonacci<0> {
        static const int value = 0;
    };
    
    template<>
    struct fibonacci<1> {
        static const int value = 1;
    };
    
    // Template for compile-time greatest common divisor
    template<int A, int B>
    struct gcd {
        static const int value = gcd<B, A % B>::value;
    };
    
    template<int A>
    struct gcd<A, 0> {
        static const int value = A;
    };
    
    // Template for compile-time prime checking
    template<int N, int D>
    struct is_prime_helper {
        static const bool value = (N % D != 0) && is_prime_helper<N, D - 1>::value;
    };
    
    template<int N>
    struct is_prime_helper<N, 1> {
        static const bool value = true;
    };
    
    template<int N>
    struct is_prime {
        static const bool value = is_prime_helper<N, N - 1>::value;
    };
    
    template<>
    struct is_prime<1> {
        static const bool value = false;
    };
    
    template<>
    struct is_prime<2> {
        static const bool value = true;
    };
    
    // Template for compile-time array size
    template<typename T, size_t N>
    struct array_size {
        static const size_t value = N;
    };
    
    // Template for compile-time type selection
    template<bool Condition, typename TrueType, typename FalseType>
    struct conditional {
        using type = TrueType;
    };
    
    template<typename TrueType, typename FalseType>
    struct conditional<false, TrueType, FalseType> {
        using type = FalseType;
    };
    
    // Template for compile-time type removal
    template<typename T>
    struct remove_reference {
        using type = T;
    };
    
    template<typename T>
    struct remove_reference<T&> {
        using type = T;
    };
    
    template<typename T>
    struct remove_reference<T&&> {
        using type = T;
    };
    
    // Template for compile-time type addition
    template<typename T>
    struct add_reference {
        using type = T&;
    };
    
    template<typename T>
    struct add_reference<T&> {
        using type = T&;
    };
    
    template<typename T>
    struct add_reference<T&&> {
        using type = T&;
    };
}

// Example 2: SFINAE (Substitution Failure Is Not An Error)
namespace SFINAE {
    
    // SFINAE for detecting if type has size() method
    template<typename T>
    auto has_size_impl(int) -> decltype(std::declval<T>().size(), std::true_type{});
    
    template<typename T>
    auto has_size_impl(...) -> std::false_type;
    
    template<typename T>
    struct has_size : decltype(has_size_impl<T>(0)) {};
    
    // SFINAE for detecting if type has begin() method
    template<typename T>
    auto has_begin_impl(int) -> decltype(std::declval<T>().begin(), std::true_type{});
    
    template<typename T>
    auto has_begin_impl(...) -> std::false_type;
    
    template<typename T>
    struct has_begin : decltype(has_begin_impl<T>(0)) {};
    
    // SFINAE for detecting if type has end() method
    template<typename T>
    auto has_end_impl(int) -> decltype(std::declval<T>().end(), std::true_type{});
    
    template<typename T>
    auto has_end_impl(...) -> std::false_type;
    
    template<typename T>
    struct has_end : decltype(has_end_impl<T>(0)) {};
    
    // SFINAE for detecting if type is iterable
    template<typename T>
    struct is_iterable {
        static const bool value = has_begin<T>::value && has_end<T>::value;
    };
    
    // SFINAE for detecting if type has operator[]
    template<typename T>
    auto has_subscript_impl(int) -> decltype(std::declval<T>()[0], std::true_type{});
    
    template<typename T>
    auto has_subscript_impl(...) -> std::false_type;
    
    template<typename T>
    struct has_subscript : decltype(has_subscript_impl<T>(0)) {};
    
    // SFINAE for detecting if type is indexable
    template<typename T>
    struct is_indexable {
        static const bool value = has_subscript<T>::value;
    };
    
    // SFINAE for detecting if type has push_back method
    template<typename T>
    auto has_push_back_impl(int) -> decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()), std::true_type{});
    
    template<typename T>
    auto has_push_back_impl(...) -> std::false_type;
    
    template<typename T>
    struct has_push_back : decltype(has_push_back_impl<T>(0)) {};
    
    // SFINAE for detecting if type is container-like
    template<typename T>
    struct is_container_like {
        static const bool value = has_size<T>::value && has_push_back<T>::value;
    };
}

// Example 3: Type Traits
namespace TypeTraits {
    
    // Custom type traits
    template<typename T>
    struct is_pointer {
        static const bool value = false;
    };
    
    template<typename T>
    struct is_pointer<T*> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_reference {
        static const bool value = false;
    };
    
    template<typename T>
    struct is_reference<T&> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_reference<T&&> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_const {
        static const bool value = false;
    };
    
    template<typename T>
    struct is_const<const T> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_volatile {
        static const bool value = false;
    };
    
    template<typename T>
    struct is_volatile<volatile T> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_array {
        static const bool value = false;
    };
    
    template<typename T, size_t N>
    struct is_array<T[N]> {
        static const bool value = true;
    };
    
    template<typename T>
    struct is_array<T[]> {
        static const bool value = true;
    };
    
    // Type manipulation traits
    template<typename T>
    struct remove_pointer {
        using type = T;
    };
    
    template<typename T>
    struct remove_pointer<T*> {
        using type = T;
    };
    
    template<typename T>
    struct remove_const {
        using type = T;
    };
    
    template<typename T>
    struct remove_const<const T> {
        using type = T;
    };
    
    template<typename T>
    struct remove_volatile {
        using type = T;
    };
    
    template<typename T>
    struct remove_volatile<volatile T> {
        using type = T;
    };
    
    template<typename T>
    struct remove_cv {
        using type = typename remove_const<typename remove_volatile<T>::type>::type;
    };
    
    // Type relationship traits
    template<typename T, typename U>
    struct is_same {
        static const bool value = false;
    };
    
    template<typename T>
    struct is_same<T, T> {
        static const bool value = true;
    };
    
    template<typename T, typename U>
    struct is_base_of {
        static const bool value = std::is_base_of<T, U>::value;
    };
    
    // Type size traits
    template<typename T>
    struct type_size {
        static const size_t value = sizeof(T);
    };
    
    template<typename T>
    struct type_alignment {
        static const size_t value = alignof(T);
    };
}

// Example 4: Constexpr Functions
namespace ConstexprFunctions {
    
    // Constexpr factorial
    constexpr int factorial(int n) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }
    
    // Constexpr power
    constexpr int power(int base, int exponent) {
        return (exponent == 0) ? 1 : base * power(base, exponent - 1);
    }
    
    // Constexpr Fibonacci
    constexpr int fibonacci(int n) {
        return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // Constexpr greatest common divisor
    constexpr int gcd(int a, int b) {
        return (b == 0) ? a : gcd(b, a % b);
    }
    
    // Constexpr least common multiple
    constexpr int lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }
    
    // Constexpr prime checking
    constexpr bool is_prime(int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    // Constexpr string length
    constexpr size_t string_length(const char* str) {
        size_t len = 0;
        while (str[len] != '\0') {
            ++len;
        }
        return len;
    }
    
    // Constexpr string comparison
    constexpr bool string_equal(const char* a, const char* b) {
        while (*a && *b) {
            if (*a != *b) return false;
            ++a;
            ++b;
        }
        return *a == *b;
    }
    
    // Constexpr array sum
    template<size_t N>
    constexpr int array_sum(const std::array<int, N>& arr) {
        int sum = 0;
        for (size_t i = 0; i < N; ++i) {
            sum += arr[i];
        }
        return sum;
    }
    
    // Constexpr array maximum
    template<size_t N>
    constexpr int array_max(const std::array<int, N>& arr) {
        int max_val = arr[0];
        for (size_t i = 1; i < N; ++i) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
        return max_val;
    }
    
    // Constexpr array minimum
    template<size_t N>
    constexpr int array_min(const std::array<int, N>& arr) {
        int min_val = arr[0];
        for (size_t i = 1; i < N; ++i) {
            if (arr[i] < min_val) {
                min_val = arr[i];
            }
        }
        return min_val;
    }
}

// Example 5: Compile-time Computations
namespace CompileTimeComputations {
    
    // Compile-time string hashing
    constexpr size_t hash_string(const char* str) {
        size_t hash = 5381;
        int c;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }
    
    // Compile-time CRC32
    constexpr uint32_t crc32_table[256] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
        0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
        0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
        0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
        0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
        0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
        0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
        0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
        0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
        0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
        0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
        0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
        0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
        0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
        0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
        0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
        0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
        0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
        0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
        0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
        0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
        0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
    };
    
    constexpr uint32_t crc32(const char* data, size_t length) {
        uint32_t crc = 0xffffffff;
        for (size_t i = 0; i < length; ++i) {
            crc = crc32_table[(crc ^ data[i]) & 0xff] ^ (crc >> 8);
        }
        return crc ^ 0xffffffff;
    }
    
    // Compile-time string to integer conversion
    constexpr int string_to_int(const char* str, int base = 10) {
        int result = 0;
        int sign = 1;
        size_t i = 0;
        
        // Handle sign
        if (str[0] == '-') {
            sign = -1;
            i = 1;
        } else if (str[0] == '+') {
            i = 1;
        }
        
        // Convert digits
        while (str[i] != '\0') {
            char c = str[i];
            int digit = 0;
            
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'A' && c <= 'Z') {
                digit = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'z') {
                digit = c - 'a' + 10;
            }
            
            if (digit >= base) break;
            
            result = result * base + digit;
            ++i;
        }
        
        return result * sign;
    }
    
    // Compile-time integer to string conversion
    constexpr size_t int_to_string(char* buffer, int value, int base = 10) {
        if (value == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return 1;
        }
        
        char temp[32];
        size_t i = 0;
        bool negative = value < 0;
        
        if (negative) value = -value;
        
        while (value > 0) {
            int digit = value % base;
            temp[i++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
            value /= base;
        }
        
        size_t j = 0;
        if (negative) buffer[j++] = '-';
        
        while (i > 0) {
            buffer[j++] = temp[--i];
        }
        
        buffer[j] = '\0';
        return j;
    }
}

// Function to demonstrate basic metaprogramming
void demonstrateBasicMetaprogramming() {
    std::cout << "=== Basic Metaprogramming Demonstration ===" << std::endl;
    
    // Compile-time factorial
    std::cout << "Factorial of 5: " << BasicMetaprogramming::factorial<5>::value << std::endl;
    std::cout << "Factorial of 10: " << BasicMetaprogramming::factorial<10>::value << std::endl;
    
    // Compile-time power
    std::cout << "2^8: " << BasicMetaprogramming::power<2, 8>::value << std::endl;
    std::cout << "3^4: " << BasicMetaprogramming::power<3, 4>::value << std::endl;
    
    // Compile-time Fibonacci
    std::cout << "Fibonacci(10): " << BasicMetaprogramming::fibonacci<10>::value << std::endl;
    std::cout << "Fibonacci(15): " << BasicMetaprogramming::fibonacci<15>::value << std::endl;
    
    // Compile-time GCD
    std::cout << "GCD(48, 18): " << BasicMetaprogramming::gcd<48, 18>::value << std::endl;
    std::cout << "GCD(100, 25): " << BasicMetaprogramming::gcd<100, 25>::value << std::endl;
    
    // Compile-time prime checking
    std::cout << "Is 17 prime? " << (BasicMetaprogramming::is_prime<17>::value ? "Yes" : "No") << std::endl;
    std::cout << "Is 25 prime? " << (BasicMetaprogramming::is_prime<25>::value ? "Yes" : "No") << std::endl;
    std::cout << "Is 29 prime? " << (BasicMetaprogramming::is_prime<29>::value ? "Yes" : "No") << std::endl;
    
    // Compile-time array size
    std::array<int, 10> arr;
    std::cout << "Array size: " << BasicMetaprogramming::array_size<decltype(arr), 10>::value << std::endl;
    
    // Compile-time type selection
    using IntType = typename BasicMetaprogramming::conditional<true, int, double>::type;
    using DoubleType = typename BasicMetaprogramming::conditional<false, int, double>::type;
    
    std::cout << "IntType is int: " << std::is_same<IntType, int>::value << std::endl;
    std::cout << "DoubleType is double: " << std::is_same<DoubleType, double>::value << std::endl;
}

// Function to demonstrate SFINAE
void demonstrateSFINAE() {
    std::cout << "\n=== SFINAE Demonstration ===" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    int value = 42;
    
    // Test has_size trait
    std::cout << "vector has size(): " << SFINAE::has_size<std::vector<int>>::value << std::endl;
    std::cout << "array has size(): " << SFINAE::has_size<std::array<int, 5>>::value << std::endl;
    std::cout << "int has size(): " << SFINAE::has_size<int>::value << std::endl;
    
    // Test has_begin trait
    std::cout << "vector has begin(): " << SFINAE::has_begin<std::vector<int>>::value << std::endl;
    std::cout << "array has begin(): " << SFINAE::has_begin<std::array<int, 5>>::value << std::endl;
    std::cout << "int has begin(): " << SFINAE::has_begin<int>::value << std::endl;
    
    // Test is_iterable trait
    std::cout << "vector is iterable: " << SFINAE::is_iterable<std::vector<int>>::value << std::endl;
    std::cout << "array is iterable: " << SFINAE::is_iterable<std::array<int, 5>>::value << std::endl;
    std::cout << "int is iterable: " << SFINAE::is_iterable<int>::value << std::endl;
    
    // Test has_subscript trait
    std::cout << "vector has subscript: " << SFINAE::has_subscript<std::vector<int>>::value << std::endl;
    std::cout << "array has subscript: " << SFINAE::has_subscript<std::array<int, 5>>::value << std::endl;
    std::cout << "int has subscript: " << SFINAE::has_subscript<int>::value << std::endl;
    
    // Test is_indexable trait
    std::cout << "vector is indexable: " << SFINAE::is_indexable<std::vector<int>>::value << std::endl;
    std::cout << "array is indexable: " << SFINAE::is_indexable<std::array<int, 5>>::value << std::endl;
    std::cout << "int is indexable: " << SFINAE::is_indexable<int>::value << std::endl;
    
    // Test has_push_back trait
    std::cout << "vector has push_back(): " << SFINAE::has_push_back<std::vector<int>>::value << std::endl;
    std::cout << "array has push_back(): " << SFINAE::has_push_back<std::array<int, 5>>::value << std::endl;
    std::cout << "int has push_back(): " << SFINAE::has_push_back<int>::value << std::endl;
    
    // Test is_container_like trait
    std::cout << "vector is container-like: " << SFINAE::is_container_like<std::vector<int>>::value << std::endl;
    std::cout << "array is container-like: " << SFINAE::is_container_like<std::array<int, 5>>::value << std::endl;
    std::cout << "int is container-like: " << SFINAE::is_container_like<int>::value << std::endl;
}

// Function to demonstrate type traits
void demonstrateTypeTraits() {
    std::cout << "\n=== Type Traits Demonstration ===" << std::endl;
    
    // Test is_pointer trait
    std::cout << "int is pointer: " << TypeTraits::is_pointer<int>::value << std::endl;
    std::cout << "int* is pointer: " << TypeTraits::is_pointer<int*>::value << std::endl;
    std::cout << "int** is pointer: " << TypeTraits::is_pointer<int**>::value << std::endl;
    
    // Test is_reference trait
    std::cout << "int is reference: " << TypeTraits::is_reference<int>::value << std::endl;
    std::cout << "int& is reference: " << TypeTraits::is_reference<int&>::value << std::endl;
    std::cout << "int&& is reference: " << TypeTraits::is_reference<int&&>::value << std::endl;
    
    // Test is_const trait
    std::cout << "int is const: " << TypeTraits::is_const<int>::value << std::endl;
    std::cout << "const int is const: " << TypeTraits::is_const<const int>::value << std::endl;
    std::cout << "const int* is const: " << TypeTraits::is_const<const int*>::value << std::endl;
    std::cout << "int* const is const: " << TypeTraits::is_const<int* const>::value << std::endl;
    
    // Test is_volatile trait
    std::cout << "int is volatile: " << TypeTraits::is_volatile<int>::value << std::endl;
    std::cout << "volatile int is volatile: " << TypeTraits::is_volatile<volatile int>::value << std::endl;
    
    // Test is_array trait
    std::cout << "int is array: " << TypeTraits::is_array<int>::value << std::endl;
    std::cout << "int[5] is array: " << TypeTraits::is_array<int[5]>::value << std::endl;
    std::cout << "int[] is array: " << TypeTraits::is_array<int[]>::value << std::endl;
    
    // Test type manipulation traits
    using IntType = TypeTraits::remove_pointer<int*>::type;
    std::cout << "remove_pointer<int*>::type is int: " << std::is_same<IntType, int>::value << std::endl;
    
    using NonConstType = TypeTraits::remove_const<const int>::type;
    std::cout << "remove_const<const int>::type is int: " << std::is_same<NonConstType, int>::value << std::endl;
    
    using NonVolatileType = TypeTraits::remove_volatile<volatile int>::type;
    std::cout << "remove_volatile<volatile int>::type is int: " << std::is_same<NonVolatileType, int>::value << std::endl;
    
    using NonCVType = TypeTraits::remove_cv<const volatile int>::type;
    std::cout << "remove_cv<const volatile int>::type is int: " << std::is_same<NonCVType, int>::value << std::endl;
    
    // Test type relationship traits
    std::cout << "int is same as int: " << TypeTraits::is_same<int, int>::value << std::endl;
    std::cout << "int is same as double: " << TypeTraits::is_same<int, double>::value << std::endl;
    
    // Test type size traits
    std::cout << "sizeof(int): " << TypeTraits::type_size<int>::value << std::endl;
    std::cout << "sizeof(double): " << TypeTraits::type_size<double>::value << std::endl;
    std::cout << "alignof(int): " << TypeTraits::type_alignment<int>::value << std::endl;
    std::cout << "alignof(double): " << TypeTraits::type_alignment<double>::value << std::endl;
}

// Function to demonstrate constexpr functions
void demonstrateConstexprFunctions() {
    std::cout << "\n=== Constexpr Functions Demonstration ===" << std::endl;
    
    // Constexpr factorial
    std::cout << "Factorial of 5: " << ConstexprFunctions::factorial(5) << std::endl;
    std::cout << "Factorial of 10: " << ConstexprFunctions::factorial(10) << std::endl;
    
    // Constexpr power
    std::cout << "2^8: " << ConstexprFunctions::power(2, 8) << std::endl;
    std::cout << "3^4: " << ConstexprFunctions::power(3, 4) << std::endl;
    
    // Constexpr Fibonacci
    std::cout << "Fibonacci(10): " << ConstexprFunctions::fibonacci(10) << std::endl;
    std::cout << "Fibonacci(15): " << ConstexprFunctions::fibonacci(15) << std::endl;
    
    // Constexpr GCD
    std::cout << "GCD(48, 18): " << ConstexprFunctions::gcd(48, 18) << std::endl;
    std::cout << "GCD(100, 25): " << ConstexprFunctions::gcd(100, 25) << std::endl;
    
    // Constexpr LCM
    std::cout << "LCM(12, 18): " << ConstexprFunctions::lcm(12, 18) << std::endl;
    std::cout << "LCM(15, 25): " << ConstexprFunctions::lcm(15, 25) << std::endl;
    
    // Constexpr prime checking
    std::cout << "Is 17 prime? " << (ConstexprFunctions::is_prime(17) ? "Yes" : "No") << std::endl;
    std::cout << "Is 25 prime? " << (ConstexprFunctions::is_prime(25) ? "Yes" : "No") << std::endl;
    std::cout << "Is 29 prime? " << (ConstexprFunctions::is_prime(29) ? "Yes" : "No") << std::endl;
    
    // Constexpr string operations
    constexpr size_t len = ConstexprFunctions::string_length("Hello, World!");
    std::cout << "String length of 'Hello, World!': " << len << std::endl;
    
    constexpr bool equal = ConstexprFunctions::string_equal("Hello", "Hello");
    std::cout << "Strings 'Hello' and 'Hello' are equal: " << (equal ? "Yes" : "No") << std::endl;
    
    constexpr bool not_equal = ConstexprFunctions::string_equal("Hello", "World");
    std::cout << "Strings 'Hello' and 'World' are equal: " << (not_equal ? "Yes" : "No") << std::endl;
    
    // Constexpr array operations
    constexpr std::array<int, 5> arr = {1, 2, 3, 4, 5};
    constexpr int sum = ConstexprFunctions::array_sum(arr);
    constexpr int max_val = ConstexprFunctions::array_max(arr);
    constexpr int min_val = ConstexprFunctions::array_min(arr);
    
    std::cout << "Array sum: " << sum << std::endl;
    std::cout << "Array max: " << max_val << std::endl;
    std::cout << "Array min: " << min_val << std::endl;
}

// Function to demonstrate compile-time computations
void demonstrateCompileTimeComputations() {
    std::cout << "\n=== Compile-time Computations Demonstration ===" << std::endl;
    
    // Compile-time string hashing
    constexpr size_t hash1 = CompileTimeComputations::hash_string("Hello, World!");
    constexpr size_t hash2 = CompileTimeComputations::hash_string("Hello, World!");
    constexpr size_t hash3 = CompileTimeComputations::hash_string("Hello, Universe!");
    
    std::cout << "Hash of 'Hello, World!': " << hash1 << std::endl;
    std::cout << "Hash of 'Hello, World!' (again): " << hash2 << std::endl;
    std::cout << "Hash of 'Hello, Universe!': " << hash3 << std::endl;
    std::cout << "Hashes are consistent: " << (hash1 == hash2 ? "Yes" : "No") << std::endl;
    std::cout << "Hashes are different: " << (hash1 != hash3 ? "Yes" : "No") << std::endl;
    
    // Compile-time CRC32
    constexpr uint32_t crc1 = CompileTimeComputations::crc32("Hello, World!", 13);
    constexpr uint32_t crc2 = CompileTimeComputations::crc32("Hello, World!", 13);
    constexpr uint32_t crc3 = CompileTimeComputations::crc32("Hello, Universe!", 16);
    
    std::cout << "CRC32 of 'Hello, World!': " << std::hex << crc1 << std::dec << std::endl;
    std::cout << "CRC32 of 'Hello, World!' (again): " << std::hex << crc2 << std::dec << std::endl;
    std::cout << "CRC32 of 'Hello, Universe!': " << std::hex << crc3 << std::dec << std::endl;
    
    // Compile-time string to integer conversion
    constexpr int num1 = CompileTimeComputations::string_to_int("12345");
    constexpr int num2 = CompileTimeComputations::string_to_int("-67890");
    constexpr int num3 = CompileTimeComputations::string_to_int("FF", 16);
    
    std::cout << "String '12345' to int: " << num1 << std::endl;
    std::cout << "String '-67890' to int: " << num2 << std::endl;
    std::cout << "String 'FF' (hex) to int: " << num3 << std::endl;
    
    // Compile-time integer to string conversion
    char buffer1[32], buffer2[32], buffer3[32];
    constexpr size_t len1 = CompileTimeComputations::int_to_string(buffer1, 12345);
    constexpr size_t len2 = CompileTimeComputations::int_to_string(buffer2, -67890);
    constexpr size_t len3 = CompileTimeComputations::int_to_string(buffer3, 255, 16);
    
    std::cout << "Int 12345 to string: " << buffer1 << " (length: " << len1 << ")" << std::endl;
    std::cout << "Int -67890 to string: " << buffer2 << " (length: " << len2 << ")" << std::endl;
    std::cout << "Int 255 (hex) to string: " << buffer3 << " (length: " << len3 << ")" << std::endl;
}

int main() {
    std::cout << "=== Metaprogramming Demonstration ===" << std::endl;
    std::cout << "This program demonstrates template metaprogramming, SFINAE,\n"
              << "type traits, constexpr functions, and compile-time computations.\n" << std::endl;
    
    // Demonstrate various metaprogramming concepts
    demonstrateBasicMetaprogramming();
    demonstrateSFINAE();
    demonstrateTypeTraits();
    demonstrateConstexprFunctions();
    demonstrateCompileTimeComputations();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Template metaprogramming enables compile-time computations" << std::endl;
    std::cout << "2. SFINAE allows conditional template instantiation" << std::endl;
    std::cout << "3. Type traits provide compile-time type information" << std::endl;
    std::cout << "4. Constexpr functions enable compile-time evaluation" << std::endl;
    std::cout << "5. Compile-time computations improve runtime performance" << std::endl;
    std::cout << "6. Metaprogramming enables advanced generic programming" << std::endl;
    std::cout << "7. Template specialization provides custom behavior" << std::endl;
    std::cout << "8. Modern C++ provides powerful metaprogramming tools" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o metaprogramming 02_Metaprogramming.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o metaprogramming 02_Metaprogramming.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Metaprogramming.cpp
 * 
 * Running:
 * ./metaprogramming (Linux/macOS)
 * metaprogramming.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best metaprogramming support.
 * 
 * Metaprogramming Notes:
 * - Template metaprogramming enables compile-time computations
 * - SFINAE allows conditional template instantiation
 * - Type traits provide compile-time type information
 * - Constexpr functions enable compile-time evaluation
 * - Compile-time computations improve runtime performance
 * - Metaprogramming enables advanced generic programming
 * - Template specialization provides custom behavior
 * - Modern C++ provides powerful metaprogramming tools
 */"""
