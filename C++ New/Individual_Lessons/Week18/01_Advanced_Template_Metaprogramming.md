# Week 18, Lesson 1: Advanced Template Metaprogramming

## 1. Learning Objectives

- Understand advanced template metaprogramming techniques and their applications.
- Learn SFINAE (Substitution Failure Is Not An Error) and its use cases.
- Explore type traits for compile-time type information and manipulation.
- Understand template specialization and partial specialization.
- Learn variadic templates and parameter pack expansion.
- Explore modern C++ metaprogramming with concepts and constexpr.
- Understand advanced template patterns like CRTP and type erasure.
- Learn best practices for template metaprogramming.

## 2. Prerequisites

- Strong understanding of C++ templates
- Knowledge of basic template metaprogramming
- Understanding of type deduction and SFINAE
- Familiarity with C++17 and C++20 features
- Knowledge of functional programming concepts

## 3. SFINAE (Substitution Failure Is Not An Error)

### 3.1 SFINAE Fundamentals

**SFINAE Concept:**
- Template substitution failures don't cause compilation errors
- Compiler silently discards failed template instantiations
- Enables conditional template instantiation
- Allows compile-time type introspection

**SFINAE Applications:**
- Type trait implementation
- Function overload resolution
- Template specialization selection
- Compile-time type checking

### 3.2 SFINAE with enable_if

```cpp
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
```

### 3.3 SFINAE with decltype

```cpp
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
```

### 3.4 SFINAE with void_t (C++17)

```cpp
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
```

### 3.5 SFINAE with Concepts (C++20)

```cpp
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
```

## 4. Type Traits

### 4.1 Custom Type Traits

**Type Trait Structure:**
```cpp
template<typename T>
struct trait_name {
    static constexpr bool value = /* compile-time boolean expression */;
    using type = /* type alias */;
};

template<typename T>
inline constexpr bool trait_name_v = trait_name<T>::value;

template<typename T>
using trait_name_t = typename trait_name<T>::type;
```

### 4.2 Type Trait Examples

```cpp
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
```

### 4.3 Complex Type Traits

```cpp
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
```

### 4.4 Type Trait Applications

```cpp
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
```

## 5. Template Specialization

### 5.1 Full Specialization

```cpp
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

// Full specialization for integers
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

// Full specialization for doubles
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
```

### 5.2 Partial Specialization

```cpp
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
```

### 5.3 Function Template Specialization

```cpp
// Function template with specialization
template<typename T>
void print_type_info(T&& value) {
    std::cout << "Type: " << TypeInfo<std::decay_t<T>>::name() << std::endl;
    std::cout << "Size: " << TypeInfo<std::decay_t<T>>::size() << " bytes" << std::endl;
    std::cout << "Is primitive: " << std::boolalpha << TypeInfo<std::decay_t<T>>::is_primitive() << std::endl;
}
```

### 5.4 Class Template Member Specialization

```cpp
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
```

## 6. Variadic Templates

### 6.1 Basic Variadic Templates

```cpp
// Basic variadic template
template<typename... Args>
void print_args(Args... args) {
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}
```

### 6.2 Fold Expressions (C++17)

```cpp
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
```

### 6.3 Parameter Pack Expansion

```cpp
// Variadic template with parameter pack expansion
template<typename T, typename... Args>
void print_with_type(T first, Args... args) {
    std::cout << "Type: " << typeid(T).name() << ", Value: " << first << std::endl;
    if constexpr (sizeof...(args) > 0) {
        print_with_type(args...);
    }
}
```

### 6.4 Perfect Forwarding with Variadic Templates

```cpp
// Variadic template with perfect forwarding
template<typename... Args>
auto make_tuple_forward(Args&&... args) {
    return std::make_tuple(std::forward<Args>(args)...);
}
```

### 6.5 SFINAE with Variadic Templates

```cpp
// Variadic template with SFINAE
template<typename... Args>
auto safe_sum(Args... args) -> std::enable_if_t<(std::is_arithmetic_v<Args> && ...), decltype((args + ...))> {
    return (args + ...);
}
```

### 6.6 Variadic Template Classes

```cpp
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
```

### 6.7 Variadic Templates with Concepts (C++20)

```cpp
// Variadic template with concepts (C++20)
template<typename... Args>
requires (std::integral<Args> && ...)
auto integral_sum(Args... args) {
    return (args + ...);
}
```

## 7. Modern C++ Metaprogramming

### 7.1 constexpr Functions

```cpp
// constexpr functions for compile-time computation
constexpr int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

constexpr int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### 7.2 constexpr Classes

```cpp
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
```

### 7.3 if constexpr (C++17)

```cpp
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
```

### 7.4 Concepts (C++20)

```cpp
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
```

### 7.5 Auto Return Type

```cpp
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
```

### 7.6 decltype in Metaprogramming

```cpp
// Template metaprogramming with decltype
template<typename T>
auto get_value_type(T&& container) -> decltype(*container.begin()) {
    return *container.begin();
}
```

## 8. Advanced Template Patterns

### 8.1 CRTP (Curiously Recurring Template Pattern)

```cpp
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
```

### 8.2 Template Template Parameters

```cpp
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
```

### 8.3 Type Erasure Pattern

```cpp
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
```

### 8.4 Expression Templates

```cpp
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
```

## 9. Best Practices

### 9.1 Template Metaprogramming Guidelines

**Design Principles:**
- Keep metaprogramming code simple and readable
- Use meaningful names for type traits and concepts
- Document complex metaprogramming constructs
- Prefer concepts over SFINAE when possible

**Performance Considerations:**
- Use constexpr for compile-time computation
- Avoid deep template instantiation
- Consider compilation time impact
- Use if constexpr to reduce template instantiation

### 9.2 Error Handling

**Compile-Time Errors:**
- Use static_assert for meaningful error messages
- Provide clear error messages for template failures
- Use concepts to improve error messages
- Consider using requires clauses

**Example:**
```cpp
template<typename T>
void process_type(T&& value) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
    // Process value
}
```

### 9.3 Debugging Template Code

**Debugging Techniques:**
- Use typeid to inspect types at runtime
- Use static_assert to verify assumptions
- Use compiler-specific debugging features
- Consider using external tools for template analysis

**Example:**
```cpp
template<typename T>
void debug_type(T&& value) {
    std::cout << "Type: " << typeid(T).name() << std::endl;
    std::cout << "Decayed type: " << typeid(std::decay_t<T>).name() << std::endl;
}
```

## 10. Common Pitfalls and Solutions

### 10.1 Template Instantiation Issues

**Problem**: Infinite template instantiation
**Solution**: Use proper termination conditions and SFINAE

**Problem**: Template instantiation explosion
**Solution**: Use if constexpr and concepts to reduce instantiation

**Problem**: Compilation time issues
**Solution**: Optimize template code and use precompiled headers

### 10.2 Type Deduction Issues

**Problem**: Unexpected type deduction
**Solution**: Use explicit template parameters and std::decay_t

**Problem**: Reference collapsing issues
**Solution**: Understand perfect forwarding and reference collapsing rules

**Problem**: Template argument deduction failures
**Solution**: Use SFINAE and concepts to guide deduction

### 10.3 SFINAE Complexity

**Problem**: Complex SFINAE expressions
**Solution**: Use concepts (C++20) or simplify SFINAE logic

**Problem**: SFINAE not working as expected
**Solution**: Understand substitution vs instantiation and use proper SFINAE patterns

## 11. Advanced Topics

### 11.1 Template Metaprogramming Libraries

**Boost.MPL:**
- Meta-programming library
- Type sequences and algorithms
- Compile-time data structures

**Boost.Hana:**
- Modern metaprogramming library
- Runtime and compile-time computation
- Type-level computations

**std::experimental::meta:**
- Standard library metaprogramming
- Reflection and introspection
- Type manipulation utilities

### 11.2 Future Directions

**C++23 and Beyond:**
- Enhanced reflection capabilities
- Improved metaprogramming features
- Better template debugging tools
- Standardized metaprogramming libraries

## 12. Summary

Advanced template metaprogramming provides powerful tools for compile-time computation and type manipulation. Key takeaways include:

1. **SFINAE** enables conditional template instantiation based on type properties
2. **Type traits** provide compile-time type information and manipulation
3. **Template specialization** allows custom behavior for specific types
4. **Variadic templates** enable functions and classes with variable arguments
5. **Modern C++ features** like concepts and constexpr improve metaprogramming
6. **Advanced patterns** like CRTP and type erasure provide powerful abstractions
7. **Template metaprogramming** enables compile-time computation and optimization
8. **Understanding template metaprogramming** is essential for modern C++ development

Effective use of template metaprogramming requires understanding both the language features and the underlying principles of compile-time computation.

## 13. Exercises

### Exercise 1: SFINAE Implementation
Implement a type trait that checks if a type has a specific member function using SFINAE.

### Exercise 2: Type Traits
Create custom type traits for checking if a type is a container, if it's callable, and if it's a smart pointer.

### Exercise 3: Template Specialization
Implement a template class with specializations for different types, including partial specializations for pointers and arrays.

### Exercise 4: Variadic Templates
Create a variadic template function that can sum, multiply, or concatenate arguments based on their types.

### Exercise 5: Advanced Patterns
Implement a type erasure container that can hold any type and provide a common interface.

## 14. Further Reading

- "C++ Templates: The Complete Guide" by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor
- "Modern C++ Design" by Andrei Alexandrescu
- "C++ Template Metaprogramming" by David Abrahams and Aleksey Gurtovoy
- "Effective Modern C++" by Scott Meyers
- "The C++ Programming Language" by Bjarne Stroustrup
- "C++ Core Guidelines" by Bjarne Stroustrup and Herb Sutter
- "Template Metaprogramming with C++" by Marius Bancila
