# Week 20, Lesson 1: Modern C++ Features

## 1. Learning Objectives
- Understand the evolution of C++ and the features introduced in C++17 and C++20.
- Learn about structured bindings, optional, variant, and parallel algorithms in C++17.
- Explore concepts, ranges, coroutines, and modules in C++20.
- Understand how modern C++ features improve code readability, performance, and safety.
- Learn about compile-time computation and advanced language features.
- Explore performance optimization techniques with modern C++.

## 2. Introduction to Modern C++

Modern C++ refers to the features and practices introduced in C++11 and later versions, particularly C++17 and C++20. These features significantly improve the language's expressiveness, safety, and performance.

### 2.1 C++ Evolution Timeline
- **C++98/03**: Original standard
- **C++11**: Major update with auto, lambda, smart pointers, move semantics
- **C++14**: Minor improvements and bug fixes
- **C++17**: Major update with structured bindings, optional, variant, parallel algorithms
- **C++20**: Major update with concepts, ranges, coroutines, modules

### 2.2 Benefits of Modern C++
- **Better Performance**: Compile-time computation, move semantics, parallel algorithms
- **Improved Safety**: Smart pointers, optional, variant, concepts
- **Enhanced Expressiveness**: Lambda expressions, structured bindings, ranges
- **Better Error Messages**: Concepts provide clearer template error messages
- **Functional Programming**: Ranges enable functional-style programming

## 3. C++17 Features

### 3.1 Structured Bindings
Structured bindings allow you to unpack tuples, pairs, arrays, and structs into individual variables.

```cpp
// Pair structured binding
auto [key, value] = std::make_pair(42, "Hello");

// Tuple structured binding
auto [a, b, c] = std::make_tuple(1, 2.5, std::string("Test"));

// Array structured binding
int arr[] = {1, 2, 3, 4, 5};
auto [first, second, third, fourth, fifth] = arr;

// Map structured binding
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
}
```

### 3.2 if constexpr
`if constexpr` allows compile-time conditional compilation, enabling template metaprogramming without SFINAE.

```cpp
template<typename T>
void process_value(T&& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Processing integer: " << value << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Processing floating point: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "Processing string: " << value << std::endl;
    } else {
        std::cout << "Processing unknown type" << std::endl;
    }
}
```

### 3.3 std::optional
`std::optional` represents an optional value that may or may not be present, eliminating the need for special sentinel values.

```cpp
std::optional<int> find_value(const std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        return *it;
    }
    return std::nullopt;
}

// Usage
auto result = find_value(numbers, 3);
if (result) {
    std::cout << "Found value: " << *result << std::endl;
} else {
    std::cout << "Value not found" << std::endl;
}

// Using value_or
int value = find_value(numbers, 10).value_or(-1);
```

### 3.4 std::variant
`std::variant` represents a type-safe union that can hold one of several alternative types.

```cpp
std::variant<int, std::string, double> get_value(int type) {
    switch (type) {
        case 0: return 42;
        case 1: return std::string("Hello");
        case 2: return 3.14;
        default: return 0;
    }
}

// Usage
auto value = get_value(1);
std::visit([](const auto& v) {
    std::cout << "Value: " << v << std::endl;
}, value);

// Type checking
if (std::holds_alternative<std::string>(value)) {
    std::cout << "String value: " << std::get<std::string>(value) << std::endl;
}
```

### 3.5 std::any
`std::any` can hold values of any type, providing runtime type erasure.

```cpp
std::any value;
value = 42;
std::cout << "Integer value: " << std::any_cast<int>(value) << std::endl;

value = std::string("Hello");
std::cout << "String value: " << std::any_cast<std::string>(value) << std::endl;

// Type checking
if (value.type() == typeid(double)) {
    std::cout << "Value is a double" << std::endl;
}
```

### 3.6 std::string_view
`std::string_view` provides a non-owning view of a string, avoiding unnecessary copies.

```cpp
std::string str = "Hello, World!";
std::string_view view(str);

std::cout << "String view: " << view << std::endl;
std::cout << "Length: " << view.length() << std::endl;
std::cout << "Substring: " << view.substr(0, 5) << std::endl;

// String view doesn't own the data
std::string_view literal_view = "Literal string";
```

### 3.7 Parallel Algorithms
C++17 introduced parallel execution policies for standard algorithms.

```cpp
std::vector<int> numbers(1000000);
std::iota(numbers.begin(), numbers.end(), 1);

// Parallel sort
std::sort(std::execution::par, numbers.begin(), numbers.end());

// Parallel transform
std::vector<int> squares(numbers.size());
std::transform(std::execution::par, numbers.begin(), numbers.end(), squares.begin(),
              [](int n) { return n * n; });
```

### 3.8 Filesystem
The `<filesystem>` library provides cross-platform file system operations.

```cpp
namespace fs = std::filesystem;

// Create directory
fs::create_directory("test_dir");

// Create file
std::ofstream file("test_dir/test_file.txt");
file << "Hello, World!" << std::endl;
file.close();

// Check if path exists
if (fs::exists("test_dir/test_file.txt")) {
    auto size = fs::file_size("test_dir/test_file.txt");
    std::cout << "File size: " << size << " bytes" << std::endl;
}

// Iterate directory
for (const auto& entry : fs::directory_iterator("test_dir")) {
    std::cout << "  " << entry.path().filename() << std::endl;
}
```

## 4. C++20 Features

### 4.1 Concepts
Concepts provide a way to specify requirements on template parameters, improving error messages and enabling better template constraints.

```cpp
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
void print_container(const T& container) {
    std::cout << "Container with " << container.size() << " elements:" << std::endl;
    for (const auto& element : container) {
        std::cout << "  " << element << std::endl;
    }
}
```

### 4.2 Ranges
Ranges provide a modern, functional approach to working with sequences of data.

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Filter and transform using ranges
auto even_squares = numbers 
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; });

std::cout << "Even squares: ";
for (int value : even_squares) {
    std::cout << value << " ";
}
std::cout << std::endl;

// Take first 5 elements
auto first_five = numbers | std::views::take(5);

// Drop first 3 elements
auto last_seven = numbers | std::views::drop(3);

// Reverse view
auto reversed = numbers | std::views::reverse;
```

### 4.3 Coroutines
Coroutines enable cooperative multitasking and can be used to implement generators, async operations, and state machines.

```cpp
template<typename T>
class Generator {
public:
    struct promise_type {
        T value;
        std::exception_ptr exception;
        
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        void unhandled_exception() {
            exception = std::current_exception();
        }
        
        std::suspend_always yield_value(T val) {
            value = val;
            return {};
        }
        
        void return_void() {}
    };
    
    // ... implementation details ...
};

// Fibonacci generator coroutine
Generator<int> fibonacci(int n) {
    int a = 0, b = 1;
    
    if (n >= 1) co_yield a;
    if (n >= 2) co_yield b;
    
    for (int i = 2; i < n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
        co_yield b;
    }
}

// Usage
auto fib_gen = fibonacci(10);
for (int value : fib_gen) {
    std::cout << value << " ";
}
```

### 4.4 Three-way Comparison (Spaceship Operator)
The spaceship operator (`<=>`) provides a unified way to implement all comparison operators.

```cpp
struct Point {
    int x, y;
    
    auto operator<=>(const Point& other) const = default;
};

// Usage
Point p1{1, 2};
Point p2{3, 4};

std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
std::cout << "p1 > p2: " << (p1 > p2) << std::endl;
std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
std::cout << "p1 != p2: " << (p1 != p2) << std::endl;
```

### 4.5 Designated Initializers
Designated initializers allow you to specify which members to initialize by name.

```cpp
struct Config {
    std::string name;
    int port;
    bool debug;
};

// Usage
Config config{.name = "server", .port = 8080, .debug = true};
```

### 4.6 Modules
Modules provide a modern alternative to header files, offering better encapsulation and faster compilation.

```cpp
// Module interface file (example)
module math;

export int add(int a, int b) {
    return a + b;
}

export int multiply(int a, int b) {
    return a * b;
}

// Module usage
import math;

int result = add(5, 3);
```

## 5. Advanced Language Features

### 5.1 Template Metaprogramming with Concepts
Concepts enable more expressive template metaprogramming.

```cpp
template<typename T>
concept Arithmetic = requires(T a, T b) {
    a + b;
    a - b;
    a * b;
    a / b;
};

template<Arithmetic T>
class Calculator {
private:
    T value_;
    
public:
    Calculator(T initial = T{}) : value_(initial) {}
    
    T add(T other) { return value_ += other; }
    T subtract(T other) { return value_ -= other; }
    T multiply(T other) { return value_ *= other; }
    T divide(T other) { return value_ /= other; }
    
    T get_value() const { return value_; }
};
```

### 5.2 Advanced Lambda Expressions
Modern C++ provides powerful lambda expression features.

```cpp
int multiplier = 3;

// Lambda with capture by value
auto multiply_by = [multiplier](int value) { return value * multiplier; };

// Lambda with capture by reference
auto accumulate = [&multiplier](int value) { 
    multiplier += value; 
    return multiplier; 
};

// Lambda with generalized capture
auto create_adder = [](int x) {
    return [x](int y) { return x + y; };
};

// Usage
auto add_5 = create_adder(5);
std::cout << "Add 5 to 7: " << add_5(7) << std::endl;
```

### 5.3 Variadic Templates with Concepts
Concepts can be used with variadic templates for better type safety.

```cpp
template<typename... Args>
concept AllIntegral = (std::integral<Args> && ...);

template<AllIntegral... Args>
auto sum(Args... args) {
    return (args + ...);
}

template<typename... Args>
concept AllSame = (std::same_as<Args, std::tuple_element_t<0, std::tuple<Args...>>> && ...);

template<AllSame... Args>
auto concatenate(Args... args) {
    return (args + ...);
}
```

## 6. Performance and Optimization

### 6.1 Compile-time Computation
Modern C++ enables extensive compile-time computation.

```cpp
// constexpr functions
constexpr int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

constexpr int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// consteval functions (C++20)
consteval int compile_time_factorial(int n) {
    if (n <= 1) return 1;
    return n * compile_time_factorial(n - 1);
}

// Usage
constexpr int fact_5 = factorial(5);
constexpr int fib_10 = fibonacci(10);
constexpr int ct_fact = compile_time_factorial(6);
```

### 6.2 Memory Optimization
Modern C++ provides tools for memory optimization.

```cpp
// Cache line alignment
struct alignas(64) CacheLineAligned {
    int value;
    char padding[64 - sizeof(int)];
};

// Branch prediction optimization
template<typename T>
T branchless_max(T a, T b) {
    return a ^ ((a ^ b) & -(a < b));
}

template<typename T>
T branchless_min(T a, T b) {
    return b ^ ((a ^ b) & -(a < b));
}
```

## 7. Best Practices

### 7.1 Modern C++ Guidelines
1. **Use auto**: Let the compiler deduce types when appropriate
2. **Prefer smart pointers**: Use `std::unique_ptr` and `std::shared_ptr` over raw pointers
3. **Use constexpr**: Enable compile-time computation when possible
4. **Use concepts**: Provide better template constraints and error messages
5. **Use ranges**: Prefer functional-style programming with ranges
6. **Use structured bindings**: Improve code readability when unpacking data
7. **Use optional/variant**: Avoid special sentinel values and unsafe unions

### 7.2 Performance Considerations
1. **Compile-time computation**: Use `constexpr` and `consteval` for performance
2. **Move semantics**: Prefer move operations over copy operations
3. **Parallel algorithms**: Use parallel execution policies for large datasets
4. **Memory alignment**: Consider cache line alignment for performance-critical code
5. **Branch prediction**: Use branchless operations when appropriate

### 7.3 Safety Considerations
1. **Smart pointers**: Use smart pointers to prevent memory leaks
2. **Optional**: Use `std::optional` instead of special sentinel values
3. **Variant**: Use `std::variant` instead of unsafe unions
4. **Concepts**: Use concepts to provide better type safety
5. **Exception safety**: Ensure proper exception handling

## 8. Common Pitfalls and How to Avoid Them

### 8.1 Template Instantiation Issues
```cpp
// Problem: Template instantiation errors
template<typename T>
void process(T value) {
    value.non_existent_method(); // Error only when instantiated
}

// Solution: Use concepts
template<typename T>
concept HasMethod = requires(T t) {
    t.non_existent_method();
};

template<HasMethod T>
void process(T value) {
    value.non_existent_method(); // Error at concept check
}
```

### 8.2 Memory Management Issues
```cpp
// Problem: Raw pointer management
int* ptr = new int(42);
// ... use ptr ...
delete ptr; // Easy to forget or double-delete

// Solution: Use smart pointers
auto ptr = std::make_unique<int>(42);
// Automatic cleanup
```

### 8.3 Exception Safety Issues
```cpp
// Problem: Exception unsafe code
void unsafe_function() {
    int* ptr = new int(42);
    risky_operation(); // May throw
    delete ptr; // May not execute
}

// Solution: RAII with smart pointers
void safe_function() {
    auto ptr = std::make_unique<int>(42);
    risky_operation(); // May throw, but ptr is automatically cleaned up
}
```

## 9. Exercises

### 9.1 Basic Exercises
1. **Structured Bindings**: Create a function that returns a tuple and use structured bindings to unpack it.
2. **Optional**: Implement a function that searches for an element in a vector and returns an optional.
3. **Variant**: Create a variant that can hold different types and demonstrate type-safe access.
4. **String View**: Implement a function that takes a string_view parameter and processes it.

### 9.2 Intermediate Exercises
1. **Concepts**: Define concepts for different types of containers and implement generic algorithms.
2. **Ranges**: Use ranges to filter, transform, and process data in functional style.
3. **Coroutines**: Implement a generator that produces a sequence of values.
4. **Parallel Algorithms**: Compare performance of sequential and parallel algorithms.

### 9.3 Advanced Exercises
1. **Template Metaprogramming**: Use concepts and variadic templates to implement advanced algorithms.
2. **Compile-time Computation**: Implement compile-time sorting and searching algorithms.
3. **Memory Optimization**: Implement cache-friendly data structures with proper alignment.
4. **Performance Analysis**: Profile and optimize code using modern C++ features.

## 10. Summary

Modern C++ features introduced in C++17 and C++20 significantly improve the language's expressiveness, safety, and performance. Key features include:

- **C++17**: Structured bindings, optional, variant, parallel algorithms, filesystem
- **C++20**: Concepts, ranges, coroutines, modules, three-way comparison
- **Performance**: Compile-time computation, move semantics, parallel algorithms
- **Safety**: Smart pointers, optional, variant, concepts
- **Expressiveness**: Lambda expressions, structured bindings, ranges

These features enable more readable, maintainable, and efficient C++ code while providing better type safety and error messages. Understanding and applying these features is essential for modern C++ development.

## 11. Additional Resources

- [C++17 Standard](https://en.cppreference.com/w/cpp/17)
- [C++20 Standard](https://en.cppreference.com/w/cpp/20)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)
- [C++ Reference](https://en.cppreference.com/)

## 12. Next Steps

After completing this lesson, you should:
1. Practice using C++17 and C++20 features in your projects
2. Explore advanced template metaprogramming techniques
3. Learn about performance optimization with modern C++
4. Study design patterns and their modern C++ implementations
5. Explore advanced concurrency and parallel programming techniques
