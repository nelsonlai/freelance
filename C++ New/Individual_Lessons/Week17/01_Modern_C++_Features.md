# Week 17, Lesson 1: Modern C++ Features

## 1. Learning Objectives

- Understand the evolution of C++ and modern language features.
- Learn C++17 features including structured bindings, optional, variant, and any.
- Explore C++20 features including concepts, ranges, coroutines, and three-way comparison.
- Understand advanced template features like variable templates, CTAD, and fold expressions.
- Learn improvements in memory management with smart pointers and RAII.
- Understand the benefits and applications of modern C++ features.
- Learn best practices for using modern C++ features effectively.
- Understand compiler support and compatibility considerations.

## 2. Prerequisites

- Strong understanding of C++ fundamentals
- Knowledge of templates and generic programming
- Understanding of object-oriented programming
- Familiarity with STL containers and algorithms
- Knowledge of memory management concepts

## 3. C++ Evolution Overview

### 3.1 C++ Standards Timeline

**C++98/03:**
- First standardized version
- Basic templates and STL
- Exception handling
- RTTI (Run-Time Type Information)

**C++11:**
- Auto keyword and type deduction
- Range-based for loops
- Lambda expressions
- Smart pointers
- Move semantics
- Variadic templates

**C++14:**
- Auto return type deduction
- Generic lambdas
- make_unique
- Binary literals
- Digit separators

**C++17:**
- Structured bindings
- std::optional, std::variant, std::any
- std::string_view
- if constexpr
- std::filesystem
- Parallel algorithms

**C++20:**
- Concepts
- Ranges
- Coroutines
- Modules
- Three-way comparison (spaceship operator)
- std::format

**C++23:**
- std::expected
- std::mdspan
- std::print
- std::generator
- More ranges features

### 3.2 Modern C++ Philosophy

**Core Principles:**
- Type safety
- Performance
- Expressiveness
- Backward compatibility
- Zero-cost abstractions

**Design Goals:**
- Make simple things simple
- Make complex things possible
- Provide multiple ways to solve problems
- Maintain C compatibility where needed
- Enable modern programming paradigms

## 4. C++17 Features

### 4.1 Structured Bindings

Structured bindings allow you to unpack tuples, pairs, arrays, and structs into individual variables.

**Syntax:**
```cpp
auto [var1, var2, var3] = expression;
```

**Examples:**
```cpp
// Pair structured binding
std::pair<int, std::string> pair_data{42, "Hello"};
auto [number, text] = pair_data;

// Tuple structured binding
std::tuple<int, std::string, double> tuple_data{10, "World", 3.14};
auto [a, b, c] = tuple_data;

// Array structured binding
std::array<int, 3> array_data{1, 2, 3};
auto [first, second, third] = array_data;

// Map structured binding
std::map<std::string, int> map_data{{"apple", 5}, {"banana", 3}};
for (const auto& [key, value] : map_data) {
    std::cout << key << ": " << value << std::endl;
}
```

**Benefits:**
- Cleaner code
- Better readability
- Less boilerplate
- Type safety

### 4.2 std::optional

std::optional represents an optional value that may or may not be present.

**Declaration:**
```cpp
std::optional<T> optional_value;
```

**Examples:**
```cpp
std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // No value
    }
    return a / b;  // Has value
}

// Usage
auto result = divide(10, 2);
if (result.has_value()) {
    std::cout << "Result: " << result.value() << std::endl;
}

// Using value_or for default
auto result2 = divide(10, 0);
int final_result = result2.value_or(-1);  // -1 if no value
```

**Methods:**
- `has_value()`: Check if value exists
- `value()`: Get the value (throws if empty)
- `value_or(default)`: Get value or default
- `operator*`: Dereference (unsafe)
- `operator->`: Member access (unsafe)

### 4.3 std::variant

std::variant represents a type-safe union that can hold one of several types.

**Declaration:**
```cpp
std::variant<T1, T2, T3> variant_value;
```

**Examples:**
```cpp
using ShapeVariant = std::variant<int, double, std::string>;

ShapeVariant v1 = 42;
ShapeVariant v2 = 3.14159;
ShapeVariant v3 = std::string("Hello");

// Type-safe access with std::visit
std::visit([](const auto& value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "Integer: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << "Double: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: " << value << std::endl;
    }
}, v1);

// Check which type is held
if (std::holds_alternative<int>(v1)) {
    std::cout << "v1 holds an integer" << std::endl;
}

// Safe access
try {
    int value = std::get<int>(v1);
    std::cout << "Value: " << value << std::endl;
} catch (const std::bad_variant_access& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

### 4.4 std::any

std::any can hold any type and provides type-safe access.

**Declaration:**
```cpp
std::any any_value;
```

**Examples:**
```cpp
std::any value1 = 42;
std::any value2 = std::string("Hello");
std::any value3 = 3.14;

// Type-safe access
if (value1.type() == typeid(int)) {
    int int_value = std::any_cast<int>(value1);
    std::cout << "Integer value: " << int_value << std::endl;
}

// Safe any_cast
try {
    std::string str_value = std::any_cast<std::string>(value2);
    std::cout << "String value: " << str_value << std::endl;
} catch (const std::bad_any_cast& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

### 4.5 std::string_view

std::string_view provides a non-owning view of a string.

**Declaration:**
```cpp
std::string_view view;
```

**Examples:**
```cpp
std::string str = "Hello, World!";
std::string_view sv = str;

// No copying, just viewing
std::cout << "Size: " << sv.size() << std::endl;
std::cout << "First character: " << sv[0] << std::endl;
std::cout << "Substring: " << sv.substr(0, 5) << std::endl;

// String view from C-string
const char* cstr = "C-style string";
std::string_view sv2(cstr);

// String view from literal
std::string_view sv3("String literal");
```

**Benefits:**
- No memory allocation
- No copying
- Can view any string-like data
- Efficient substring operations

### 4.6 if constexpr

if constexpr allows compile-time conditional compilation.

**Syntax:**
```cpp
if constexpr (condition) {
    // Compile-time branch
}
```

**Examples:**
```cpp
template<typename T>
void process_value(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Processing integer: " << value << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Processing float: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "Processing string: " << value << std::endl;
    } else {
        std::cout << "Processing unknown type" << std::endl;
    }
}
```

### 4.7 std::filesystem

std::filesystem provides portable file system operations.

**Examples:**
```cpp
namespace fs = std::filesystem;

// Get current directory
std::cout << "Current directory: " << fs::current_path() << std::endl;

// Check if path exists
fs::path current_path = fs::current_path();
std::cout << "Exists: " << std::boolalpha << fs::exists(current_path) << std::endl;

// List directory contents
for (const auto& entry : fs::directory_iterator(current_path)) {
    std::cout << entry.path().filename() << std::endl;
}

// File operations
if (fs::is_regular_file("file.txt")) {
    std::cout << "File size: " << fs::file_size("file.txt") << " bytes" << std::endl;
}
```

## 5. C++20 Features

### 5.1 Concepts

Concepts provide a way to specify requirements on template parameters.

**Syntax:**
```cpp
template<typename T>
concept ConceptName = requires(T t) {
    // requirements
};
```

**Examples:**
```cpp
template<typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

template<typename T>
concept Container = requires(T t) {
    t.begin();
    t.end();
    t.size();
};

template<Addable T>
T add_values(T a, T b) {
    return a + b;
}

template<Container T>
void print_container_info(const T& container) {
    std::cout << "Container size: " << container.size() << std::endl;
}
```

**Benefits:**
- Better error messages
- Type safety
- Documentation
- Code clarity

### 5.2 Ranges

Ranges provide a modern way to work with sequences of data.

**Examples:**
```cpp
std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Filter even numbers and square them
auto even_squares = numbers | 
    std::views::filter([](int n) { return n % 2 == 0; }) |
    std::views::transform([](int n) { return n * n; });

// Take first 5 elements and double them
auto first_five_doubled = numbers |
    std::views::take(5) |
    std::views::transform([](int n) { return n * 2; });

// Reverse view
auto reversed = numbers | std::views::reverse;
```

**Benefits:**
- Lazy evaluation
- Composable operations
- Readable code
- Performance optimization

### 5.3 Coroutines

Coroutines enable cooperative multitasking and generators.

**Example Generator:**
```cpp
struct Generator {
    struct promise_type {
        int current_value;
        
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
    
    ~Generator() {
        if (coro) coro.destroy();
    }
    
    struct iterator {
        std::coroutine_handle<promise_type> coro;
        
        iterator(std::coroutine_handle<promise_type> h) : coro(h) {}
        
        iterator& operator++() {
            coro.resume();
            return *this;
        }
        
        int operator*() const {
            return coro.promise().current_value;
        }
        
        bool operator!=(const iterator& other) const {
            return coro != other.coro;
        }
    };
    
    iterator begin() {
        coro.resume();
        return iterator{coro};
    }
    
    iterator end() {
        return iterator{};
    }
};

Generator fibonacci(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        co_yield a;
        int temp = a + b;
        a = b;
        b = temp;
    }
}
```

### 5.4 Three-way Comparison (Spaceship Operator)

The spaceship operator (<=>) provides a unified way to implement all comparison operators.

**Examples:**
```cpp
struct Person {
    std::string name;
    int age;
    
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    // Default three-way comparison
    auto operator<=>(const Person& other) const = default;
    
    // Custom three-way comparison
    // auto operator<=>(const Person& other) const {
    //     if (auto cmp = name <=> other.name; cmp != 0) return cmp;
    //     return age <=> other.age;
    // }
};

Person alice("Alice", 30);
Person bob("Bob", 25);

std::cout << "Alice < Bob: " << std::boolalpha << (alice < bob) << std::endl;
std::cout << "Alice > Bob: " << std::boolalpha << (alice > bob) << std::endl;
std::cout << "Alice == Bob: " << std::boolalpha << (alice == bob) << std::endl;
```

### 5.5 std::format

std::format provides type-safe string formatting.

**Examples:**
```cpp
// Note: Requires C++20 and may not be available in all compilers
std::string name = "Alice";
int age = 30;
double height = 5.6;

// Basic formatting
std::string formatted = std::format("Hello {}, you are {} years old", name, age);

// Format specifiers
std::string formatted2 = std::format("Height: {:.2f} feet", height);

// Positional arguments
std::string formatted3 = std::format("Hello {1}, you are {0} years old", age, name);
```

## 6. Advanced Template Features

### 6.1 Variable Templates

Variable templates allow you to define template variables.

**Examples:**
```cpp
template<typename T>
constexpr T pi = T(3.1415926535897932385L);

template<typename T>
constexpr T e = T(2.7182818284590452354L);

// Usage
double pi_double = pi<double>;
float pi_float = pi<float>;
long double pi_long = pi<long double>;
```

### 6.2 Class Template Argument Deduction (CTAD)

CTAD allows the compiler to deduce template arguments from constructor arguments.

**Examples:**
```cpp
template<typename T>
class Point {
private:
    T x_, y_;
    
public:
    Point(T x, T y) : x_(x), y_(y) {}
    
    T get_x() const { return x_; }
    T get_y() const { return y_; }
};

// CTAD deduces template arguments
Point p1(10, 20);        // Point<int>
Point p2(3.14, 2.71);    // Point<double>
Point p3(10.5f, 20.5f);  // Point<float>

// Explicit template arguments still work
Point<double> p4(10, 20);
```

### 6.3 Fold Expressions

Fold expressions allow you to apply binary operators to parameter packs.

**Examples:**
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Binary right fold
}

template<typename... Args>
auto product(Args... args) {
    return (args * ...);  // Binary right fold
}

template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << std::endl;  // Binary left fold
}

template<typename T, typename... Args>
bool all_equal(const T& first, const Args&... rest) {
    return ((first == rest) && ...);  // Binary right fold
}

// Usage
int total = sum(1, 2, 3, 4, 5);  // 15
int product_result = product(2, 3, 4);  // 24
print_all("Hello", " ", "World", "!", " ", 42);
bool all_same = all_equal(5, 5, 5, 5);  // true
```

**Fold Expression Types:**
- `(pack op ...)`: Binary right fold
- `(... op pack)`: Binary left fold
- `(pack op ... op init)`: Binary right fold with initial value
- `(init op ... op pack)`: Binary left fold with initial value

### 6.4 SFINAE and Type Traits

SFINAE (Substitution Failure Is Not An Error) allows template specialization based on type properties.

**Examples:**
```cpp
template<typename T>
std::enable_if_t<std::is_integral_v<T>, void> process_integer(T value) {
    std::cout << "Processing integer: " << value << std::endl;
}

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void> process_float(T value) {
    std::cout << "Processing float: " << value << std::endl;
}

template<typename T>
std::enable_if_t<!std::is_arithmetic_v<T>, void> process_other(T value) {
    std::cout << "Processing other type" << std::endl;
}

// Type traits
std::cout << "Is int integral: " << std::boolalpha << std::is_integral_v<int> << std::endl;
std::cout << "Is double floating point: " << std::boolalpha << std::is_floating_point_v<double> << std::endl;
std::cout << "Is string arithmetic: " << std::boolalpha << std::is_arithmetic_v<std::string> << std::endl;
```

## 7. Memory Management Improvements

### 7.1 Smart Pointers

Modern C++ provides improved smart pointer functionality.

**std::unique_ptr:**
```cpp
// make_unique (C++14)
auto unique_ptr = std::make_unique<std::vector<int>>(10, 42);

// Custom deleter
auto custom_deleter = [](std::string* ptr) {
    std::cout << "Custom deleter called for: " << *ptr << std::endl;
    delete ptr;
};

std::unique_ptr<std::string, decltype(custom_deleter)> custom_ptr(
    new std::string("Custom deletion"), custom_deleter);
```

**std::shared_ptr:**
```cpp
// make_shared (C++11)
auto shared_ptr = std::make_shared<std::string>("Hello, World!");
std::cout << "Reference count: " << shared_ptr.use_count() << std::endl;

// weak_ptr
std::weak_ptr<std::string> weak_ptr = shared_ptr;
std::cout << "Weak pointer expired: " << std::boolalpha << weak_ptr.expired() << std::endl;

if (auto locked = weak_ptr.lock()) {
    std::cout << "Weak pointer locked: " << *locked << std::endl;
}
```

### 7.2 RAII Improvements

RAII (Resource Acquisition Is Initialization) is enhanced with move semantics.

**Example:**
```cpp
class ResourceManager {
private:
    std::unique_ptr<int[]> data_;
    size_t size_;
    
public:
    ResourceManager(size_t size) : size_(size) {
        data_ = std::make_unique<int[]>(size);
        std::cout << "Resource allocated: " << size << " integers" << std::endl;
    }
    
    ~ResourceManager() {
        std::cout << "Resource deallocated: " << size_ << " integers" << std::endl;
    }
    
    // Move constructor
    ResourceManager(ResourceManager&& other) noexcept 
        : data_(std::move(other.data_)), size_(other.size_) {
        other.size_ = 0;
        std::cout << "Resource moved" << std::endl;
    }
    
    // Move assignment
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
            std::cout << "Resource move assigned" << std::endl;
        }
        return *this;
    }
    
    // Non-copyable
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    int& operator[](size_t index) {
        return data_[index];
    }
    
    const int& operator[](size_t index) const {
        return data_[index];
    }
    
    size_t size() const {
        return size_;
    }
};
```

## 8. Best Practices

### 8.1 Modern C++ Guidelines

**Use Modern Features:**
- Prefer `auto` for type deduction
- Use smart pointers instead of raw pointers
- Use range-based for loops
- Use structured bindings for unpacking
- Use `std::optional` for optional values

**Avoid Deprecated Features:**
- Avoid raw pointers for ownership
- Avoid `new` and `delete`
- Avoid C-style casts
- Avoid macros where possible
- Avoid `std::endl` in favor of `'\n'`

### 8.2 Performance Considerations

**Zero-Cost Abstractions:**
- Modern C++ features often have zero runtime cost
- Compile-time optimizations
- Template instantiation overhead
- Move semantics for performance

**Memory Management:**
- Use smart pointers for automatic cleanup
- Prefer stack allocation
- Use move semantics to avoid copying
- Consider memory pools for frequent allocations

### 8.3 Compatibility and Migration

**Compiler Support:**
- Check compiler feature support
- Use feature test macros
- Consider polyfills for older compilers
- Gradual migration strategy

**Feature Test Macros:**
```cpp
#if __cpp_structured_bindings >= 201606L
    // Use structured bindings
    auto [key, value] = pair;
#else
    // Fallback for older compilers
    auto key = pair.first;
    auto value = pair.second;
#endif
```

## 9. Common Pitfalls and Solutions

### 9.1 Modern C++ Pitfalls

**Problem**: Overusing `auto` keyword
**Solution**: Use `auto` when the type is obvious or when dealing with complex types

**Problem**: Misunderstanding move semantics
**Solution**: Understand when moves happen and when they don't

**Problem**: Incorrect use of smart pointers
**Solution**: Understand the difference between `unique_ptr`, `shared_ptr`, and `weak_ptr`

**Problem**: Performance issues with modern features
**Solution**: Profile code and understand the costs of abstractions

### 9.2 Template Pitfalls

**Problem**: Template instantiation errors
**Solution**: Use concepts (C++20) or SFINAE for better error messages

**Problem**: Template bloat
**Solution**: Use explicit instantiation and template specialization

**Problem**: Compilation time issues
**Solution**: Use forward declarations and reduce template dependencies

### 9.3 Memory Management Pitfalls

**Problem**: Circular references with `shared_ptr`
**Solution**: Use `weak_ptr` to break cycles

**Problem**: Exception safety issues
**Solution**: Use RAII and smart pointers

**Problem**: Move semantics confusion
**Solution**: Understand when objects are moved and when they're copied

## 10. Advanced Topics

### 10.1 Modules (C++20)

Modules provide a new way to organize and compile C++ code.

**Benefits:**
- Faster compilation
- Better encapsulation
- Reduced header dependencies
- Cleaner interfaces

**Example Module:**
```cpp
// math.cppm
export module math;

export int add(int a, int b) {
    return a + b;
}

export double multiply(double a, double b) {
    return a * b;
}
```

**Using Modules:**
```cpp
// main.cpp
import math;

int main() {
    int result = add(5, 3);
    double product = multiply(2.5, 4.0);
    return 0;
}
```

### 10.2 Reflection (Future C++)

Reflection will allow runtime inspection of types.

**Proposed Features:**
- Type information
- Member access
- Function invocation
- Template metaprogramming

### 10.3 Networking (Future C++)

Standard networking library for C++.

**Proposed Features:**
- Sockets
- HTTP client/server
- WebSocket support
- Asynchronous operations

## 11. Summary

Modern C++ features significantly improve the language's expressiveness, type safety, and performance. Key takeaways include:

1. **C++17** introduced structured bindings, optional, variant, and any for better type safety
2. **C++20** added concepts, ranges, coroutines, and three-way comparison for modern programming
3. **Advanced templates** support variable templates, CTAD, and fold expressions for more expressive code
4. **Smart pointers and RAII** provide better memory management and exception safety
5. **Modern C++ features** improve type safety and performance with zero-cost abstractions
6. **New language features** enable more expressive and efficient code
7. **Backward compatibility** is maintained while adding new capabilities
8. **Modern C++** continues to evolve with each standard release

Understanding and using these modern features will make your C++ code more maintainable, efficient, and expressive.

## 12. Exercises

### Exercise 1: C++17 Features
Implement a function that returns an `std::optional<std::string>` for finding a user by ID, and use structured bindings to unpack the result.

### Exercise 2: C++20 Concepts
Create concepts for `Comparable`, `Printable`, and `Container`, and implement functions that use these concepts.

### Exercise 3: Advanced Templates
Implement a variable template for mathematical constants and use fold expressions to create a variadic function that calculates the sum of squares.

### Exercise 4: Smart Pointers
Implement a resource manager class using `std::unique_ptr` with custom deleters and move semantics.

### Exercise 5: Modern C++ Design
Design a modern C++ class that uses C++17 and C++20 features for a configuration system with type-safe value storage.

## 13. Further Reading

- "C++17 - The Complete Guide" by Nicolai M. Josuttis
- "C++20 - The Complete Guide" by Nicolai M. Josuttis
- "Effective Modern C++" by Scott Meyers
- "C++ Templates: The Complete Guide" by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor
- "C++ Concurrency in Action" by Anthony Williams
- "The C++ Programming Language" by Bjarne Stroustrup
- "C++ Core Guidelines" by Bjarne Stroustrup and Herb Sutter
