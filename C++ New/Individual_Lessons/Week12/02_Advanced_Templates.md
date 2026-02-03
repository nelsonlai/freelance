# Lesson 12.2: Advanced Templates

## Learning Objectives
- Master template metaprogramming techniques
- Understand template specialization and partial specialization
- Learn template argument deduction and forwarding
- Practice with modern template features
- Explore advanced template patterns and best practices

## Prerequisites
- Completed Lesson 12.1 (Templates Fundamentals)
- Understanding of basic templates
- Knowledge of template instantiation

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Template Metaprogramming

#### Type Traits and Type Checking
```cpp
#include <type_traits>

// Custom type traits
template<typename T>
struct is_pointer {
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

// Type checking with SFINAE
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
absolute_value(T value) {
    return value < 0 ? -value : value;
}

// Template metaprogramming for type manipulation
template<typename T>
struct remove_pointer {
    using type = T;
};

template<typename T>
struct remove_pointer<T*> {
    using type = T;
};

template<typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

// Compile-time type checking
template<typename T>
struct is_container {
    template<typename U>
    static auto test(int) -> decltype(
        std::declval<U>().begin(),
        std::declval<U>().end(),
        std::true_type{}
    );
    
    template<typename>
    static std::false_type test(...);
    
    static const bool value = decltype(test<T>(0))::value;
};
```

#### Template Metafunctions
```cpp
// Template metafunction for type selection
template<bool B, typename T, typename F>
struct conditional {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

// Template metafunction for type transformation
template<typename T>
struct add_const {
    using type = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

// Template metafunction for parameter pack manipulation
template<typename... Args>
struct count_types {
    static const size_t value = sizeof...(Args);
};

template<typename T, typename... Args>
struct count_occurrences {
    static const size_t value = (std::is_same_v<T, Args> + ...);
};
```

### 2. Template Specialization

#### Partial Specialization
```cpp
// Primary template
template<typename T, typename U>
class Pair {
private:
    T first_;
    U second_;
    
public:
    Pair(T first, U second) : first_(first), second_(second) {}
    
    void display() const {
        std::cout << "Pair(" << first_ << ", " << second_ << ")" << std::endl;
    }
};

// Partial specialization for same types
template<typename T>
class Pair<T, T> {
private:
    T first_;
    T second_;
    
public:
    Pair(T first, T second) : first_(first), second_(second) {}
    
    void display() const {
        std::cout << "SameTypePair(" << first_ << ", " << second_ << ")" << std::endl;
    }
    
    T difference() const {
        return first_ - second_;
    }
};

// Partial specialization for pointers
template<typename T, typename U>
class Pair<T*, U*> {
private:
    T* first_;
    U* second_;
    
public:
    Pair(T* first, U* second) : first_(first), second_(second) {}
    
    void display() const {
        std::cout << "PointerPair(" << *first_ << ", " << *second_ << ")" << std::endl;
    }
    
    bool both_null() const {
        return first_ == nullptr && second_ == nullptr;
    }
};
```

#### Template Specialization for Functions
```cpp
// Primary template
template<typename T>
void process(T value) {
    std::cout << "Generic processing: " << value << std::endl;
}

// Specialization for pointers
template<typename T>
void process(T* value) {
    if (value) {
        std::cout << "Pointer processing: " << *value << std::endl;
    } else {
        std::cout << "Null pointer" << std::endl;
    }
}

// Specialization for containers
template<typename T>
void process(const std::vector<T>& container) {
    std::cout << "Vector processing: ";
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
```

### 3. Template Argument Deduction

#### Automatic Type Deduction
```cpp
// Function template with automatic deduction
template<typename T>
void print_type(T value) {
    std::cout << "Type: " << typeid(T).name() << ", Value: " << value << std::endl;
}

// Class template argument deduction (C++17)
template<typename T>
class Container {
private:
    std::vector<T> data_;
    
public:
    Container(std::initializer_list<T> init) : data_(init) {}
    
    void display() const {
        std::cout << "Container: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Deduction guides
template<typename T>
Container(T) -> Container<T>;

template<typename T>
Container(std::initializer_list<T>) -> Container<T>;
```

#### Perfect Forwarding
```cpp
// Perfect forwarding with universal references
template<typename T>
void forward_value(T&& value) {
    process_value(std::forward<T>(value));
}

template<typename T>
void process_value(T&& value) {
    std::cout << "Processing: " << value << std::endl;
}

// Variadic perfect forwarding
template<typename... Args>
void forward_all(Args&&... args) {
    process_all(std::forward<Args>(args)...);
}

template<typename... Args>
void process_all(Args&&... args) {
    (std::cout << ... << args) << std::endl;
}
```

### 4. Modern Template Features

#### Concepts and Constraints (C++20)
```cpp
#include <concepts>

// Concept definition
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<typename T>
concept Container = requires(T t) {
    t.begin();
    t.end();
    t.size();
};

// Constrained templates
template<Numeric T>
T square(T value) {
    return value * value;
}

template<Container T>
void print_container(const T& container) {
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// Concept with requirements
template<typename T>
concept Printable = requires(T t) {
    std::cout << t;
};

template<Printable T>
void print_value(T value) {
    std::cout << "Value: " << value << std::endl;
}
```

#### Template Parameter Packs
```cpp
// Parameter pack expansion
template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << std::endl;
}

// Parameter pack with different operations
template<typename... Args>
auto sum_all(Args... args) {
    return (args + ...);
}

template<typename... Args>
auto max_all(Args... args) {
    return (args, ...);
}

// Parameter pack with templates
template<template<typename> class... Templates>
struct combine_templates {};

template<typename T, template<typename> class... Templates>
void apply_templates(T value, Templates<T>... templates) {
    // Apply each template to the value
}
```

---

## Demonstration (25 minutes)

### Advanced Template Examples
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>
#include <memory>

// Template metaprogramming example
template<int N>
struct compile_time_array {
    int data_[N];
    
    constexpr int& operator[](int index) {
        return data_[index];
    }
    
    constexpr const int& operator[](int index) const {
        return data_[index];
    }
    
    constexpr int size() const {
        return N;
    }
};

// Template specialization for different sizes
template<>
struct compile_time_array<1> {
    int data_;
    
    constexpr int& operator[](int index) {
        return data_;
    }
    
    constexpr const int& operator[](int index) const {
        return data_;
    }
    
    constexpr int size() const {
        return 1;
    }
};

// Advanced template with SFINAE
template<typename T>
class advanced_container {
private:
    std::vector<T> data_;
    
public:
    void add(const T& item) {
        data_.push_back(item);
    }
    
    // SFINAE for sorting
    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, void>::type
    sort() {
        std::sort(data_.begin(), data_.end());
    }
    
    // SFINAE for string operations
    template<typename U = T>
    typename std::enable_if<std::is_same<U, std::string>::value, void>::type
    sort() {
        std::sort(data_.begin(), data_.end());
    }
    
    void display() const {
        std::cout << "Container: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Template with perfect forwarding
template<typename T>
class forwarding_container {
private:
    std::vector<T> data_;
    
public:
    template<typename U>
    void add(U&& item) {
        data_.emplace_back(std::forward<U>(item));
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        data_.emplace_back(std::forward<Args>(args)...);
    }
    
    void display() const {
        std::cout << "Forwarding Container: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Template with variadic parameters
template<typename... Args>
class variadic_container {
private:
    std::tuple<Args...> data_;
    
public:
    variadic_container(Args... args) : data_(args...) {}
    
    template<size_t N>
    auto get() -> decltype(std::get<N>(data_)) {
        return std::get<N>(data_);
    }
    
    void display() const {
        std::cout << "Variadic Container: ";
        display_impl(std::index_sequence_for<Args...>{});
    }
    
private:
    template<size_t... Is>
    void display_impl(std::index_sequence<Is...>) const {
        ((std::cout << std::get<Is>(data_) << " "), ...);
        std::cout << std::endl;
    }
};

void demonstrateAdvancedTemplates() {
    std::cout << "=== Advanced Templates Demonstration ===" << std::endl;
    
    // Compile-time array
    constexpr compile_time_array<5> arr;
    std::cout << "Compile-time array size: " << arr.size() << std::endl;
    
    // Advanced container with SFINAE
    advanced_container<int> int_container;
    advanced_container<std::string> string_container;
    
    int_container.add(3);
    int_container.add(1);
    int_container.add(4);
    int_container.add(1);
    int_container.add(5);
    
    string_container.add("banana");
    string_container.add("apple");
    string_container.add("cherry");
    
    std::cout << "\nBefore sorting:" << std::endl;
    int_container.display();
    string_container.display();
    
    int_container.sort();
    string_container.sort();
    
    std::cout << "\nAfter sorting:" << std::endl;
    int_container.display();
    string_container.display();
    
    // Forwarding container
    forwarding_container<std::string> forwarding_cont;
    forwarding_cont.add("Hello");
    forwarding_cont.emplace("World");
    forwarding_cont.add(std::string("Template"));
    forwarding_cont.display();
    
    // Variadic container
    variadic_container<int, double, std::string> variadic_cont(42, 3.14, "Hello");
    variadic_cont.display();
    
    std::cout << "First element: " << variadic_cont.get<0>() << std::endl;
    std::cout << "Second element: " << variadic_cont.get<1>() << std::endl;
    std::cout << "Third element: " << variadic_cont.get<2>() << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Template Metaprogramming
Implement template metaprogramming:

**Tasks:**
1. Create custom type traits
2. Implement template metafunctions
3. Use SFINAE for type checking
4. Build compile-time computations

### Activity 2: Template Specialization
Apply template specialization:

**Tasks:**
1. Implement partial specialization
2. Create function template specializations
3. Handle different type categories
4. Optimize for specific types

### Activity 3: Modern Template Features
Use modern template features:

**Tasks:**
1. Implement perfect forwarding
2. Use variadic templates
3. Apply template constraints
4. Create deduction guides

---

## Key Concepts

### 1. Template Metaprogramming
```cpp
// Compile-time computation
template<int N>
struct power_of_two {
    static const int value = 2 * power_of_two<N - 1>::value;
};

template<>
struct power_of_two<0> {
    static const int value = 1;
};

// Type manipulation
template<typename T>
struct add_reference {
    using type = T&;
};

template<typename T>
using add_reference_t = typename add_reference<T>::type;
```

### 2. SFINAE Techniques
```cpp
// SFINAE for function selection
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
process_integer(T value) {
    std::cout << "Integer: " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
process_floating(T value) {
    std::cout << "Floating: " << value << std::endl;
}
```

### 3. Perfect Forwarding
```cpp
template<typename T>
void perfect_forward(T&& value) {
    process(std::forward<T>(value));
}

template<typename T>
void process(T& value) {
    std::cout << "Lvalue: " << value << std::endl;
}

template<typename T>
void process(T&& value) {
    std::cout << "Rvalue: " << value << std::endl;
}
```

---

## Best Practices

### 1. Template Metaprogramming
- Use template metaprogramming for compile-time computations
- Prefer constexpr functions when possible
- Document template requirements clearly
- Use type traits for type checking

### 2. Template Specialization
- Use specialization for type-specific optimizations
- Prefer partial specialization over full specialization
- Maintain consistent interface across specializations
- Document specialization behavior

### 3. Modern Template Features
- Use perfect forwarding for generic functions
- Apply variadic templates for flexible interfaces
- Use template constraints for type safety
- Leverage automatic deduction when appropriate

---

## Common Pitfalls

### 1. Template Instantiation Issues
```cpp
// Wrong: incomplete type in template
template<typename T>
class Container {
    T data_;  // T might be incomplete
};

// Correct: use pointers or references
template<typename T>
class Container {
    T* data_;  // T can be incomplete
};
```

### 2. SFINAE Complexity
```cpp
// Wrong: overly complex SFINAE
template<typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && 
    std::is_same<T, int>::value, 
    void
>::type
complex_function(T value);

// Correct: use concepts or simpler SFINAE
template<typename T>
requires std::is_arithmetic_v<T>
void simple_function(T value);
```

### 3. Template Specialization Order
```cpp
// Wrong: specialization before primary template
template<>
class Vector<bool> {};  // Error!

template<typename T>
class Vector {};

// Correct: specialization after primary template
template<typename T>
class Vector {};

template<>
class Vector<bool> {};
```

---

## Assessment

### Quiz Questions
1. What is template metaprogramming and when should you use it?
2. How does partial specialization differ from full specialization?
3. What is perfect forwarding and why is it useful?
4. How do template constraints improve code safety?

### Practical Assessment
- Implement template metaprogramming techniques
- Use template specialization appropriately
- Apply perfect forwarding correctly
- Handle modern template features

---

## Homework Assignment

### Task 1: Template Metaprogramming Library
Implement:
1. Custom type traits for common operations
2. Template metafunctions for type manipulation
3. Compile-time algorithms and data structures
4. SFINAE-based function selection

### Task 2: Advanced Template Specialization
Create:
1. A generic container with multiple specializations
2. Function templates with type-specific optimizations
3. Partial specialization for different type categories
4. Performance comparison of specializations

### Task 3: Modern Template Features
Apply:
1. Perfect forwarding in generic functions
2. Variadic templates for flexible interfaces
3. Template constraints and concepts
4. Automatic deduction and forwarding

---

## Next Lesson Preview

In the next lesson, we'll learn about generic programming:
- Generic algorithms and data structures
- Iterator concepts and ranges
- Function objects and adapters
- Modern generic programming patterns

Make sure you understand advanced templates before moving on!
