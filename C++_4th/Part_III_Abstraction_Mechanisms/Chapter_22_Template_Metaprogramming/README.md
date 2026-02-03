# Chapter 22: Template Metaprogramming

## 📘 Learning Objectives

After completing this chapter, you will:
- Master template metaprogramming fundamentals
- Understand SFINAE (Substitution Failure Is Not An Error)
- Learn about type traits and template specialization
- Master variadic templates and parameter packs
- Understand compile-time computation and optimization

## 🎯 Key Concepts

### 1. Template Metaprogramming Basics

- **Template instantiation**: Compile-time code generation
- **Template recursion**: Recursive template definitions
- **Template specialization**: Specialized template implementations
- **Partial specialization**: Partial template specialization
- **Template aliases**: Type aliases with templates

### 2. SFINAE (Substitution Failure Is Not An Error)

- **SFINAE principle**: Template substitution rules
- **enable_if**: Conditional template instantiation
- **decltype**: Type deduction from expressions
- **void_t**: SFINAE helper template
- **Concept emulation**: Pre-C++20 concept simulation

### 3. Type Traits

- **Built-in type traits**: Standard library type traits
- **Custom type traits**: User-defined type traits
- **Type categories**: Fundamental type categories
- **Type transformations**: Type manipulation traits
- **Type queries**: Type information queries

### 4. Variadic Templates

- **Parameter packs**: Variable template arguments
- **Pack expansion**: Expanding parameter packs
- **Fold expressions**: C++17 fold syntax
- **Perfect forwarding**: Forwarding parameter packs
- **Template argument deduction**: Automatic type deduction

### 5. Compile-time Computation

- **Constexpr functions**: Compile-time function evaluation
- **Template recursion**: Recursive compile-time computation
- **Template specialization**: Compile-time branching
- **Integer sequences**: Compile-time integer sequences
- **Performance optimization**: Zero-cost abstractions

## 🧩 Practice Exercises

### Exercise 22.1: Basic Template Metaprogramming
Implement basic template metaprogramming patterns.

### Exercise 22.2: SFINAE and Type Traits
Use SFINAE to create type-safe templates.

### Exercise 22.3: Variadic Templates
Implement variadic template functions and classes.

### Exercise 22.4: Compile-time Computation
Create compile-time algorithms and data structures.

## 💻 Code Examples

### Template Metaprogramming Basics
```cpp
#include <iostream>
#include <type_traits>

// Basic template metaprogramming
template<int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

// SFINAE example
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add_one(T value) {
    return value + 1;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
add_one(T value) {
    return value + 1.0;
}

int main() {
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;
    std::cout << "Add one to 5: " << add_one(5) << std::endl;
    std::cout << "Add one to 3.14: " << add_one(3.14) << std::endl;
    return 0;
}
```

### Variadic Templates
```cpp
#include <iostream>
#include <string>

// Variadic template function
template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << std::endl;  // C++17 fold expression
}

// Variadic template class
template<typename... Types>
struct TypeList {};

template<typename T, typename... Types>
struct TypeList<T, Types...> {
    using head = T;
    using tail = TypeList<Types...>;
};

int main() {
    print_all("Hello", " ", "World", " ", 42);
    return 0;
}
```

## 🎓 Key Takeaways

1. **Understand SFINAE** for type-safe template programming
2. **Use type traits** for compile-time type introspection
3. **Master variadic templates** for flexible function and class design
4. **Leverage compile-time computation** for performance optimization
5. **Combine patterns** for powerful template metaprogramming

## 🔗 Next Steps

After mastering template metaprogramming, proceed to Chapter 23 to learn about advanced template techniques.

## 📚 Additional Resources

- C++ Reference: Templates
- C++ Core Guidelines: Templates
- Practice with complex template metaprogramming
