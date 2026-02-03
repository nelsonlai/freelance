# Chapter 38: Utilities

## 📘 Learning Objectives

After completing this chapter, you will:
- Master utility classes and functions
- Understand std::pair and std::tuple
- Learn about std::optional and std::variant
- Master std::any and type erasure
- Understand utility algorithms and functions

## 🎯 Key Concepts

### 1. Pair and Tuple

- **std::pair**: Two-element tuple
- **std::tuple**: Multi-element tuple
- **Structured bindings**: C++17 tuple unpacking
- **Tuple operations**: Comparison and manipulation
- **Tuple algorithms**: Tuple-based algorithms

### 2. Optional and Variant

- **std::optional**: Optional value container
- **std::variant**: Type-safe union
- **std::any**: Type-erased container
- **Monadic operations**: Optional and variant operations
- **Error handling**: Error handling patterns

### 3. Utility Functions

- **std::move**: Move semantics
- **std::forward**: Perfect forwarding
- **std::swap**: Value swapping
- **std::exchange**: Value exchange
- **std::invoke**: Function invocation

### 4. Type Traits

- **Type information**: Compile-time type introspection
- **Type transformations**: Type manipulation
- **Type queries**: Type property queries
- **Custom traits**: User-defined type traits
- **Trait composition**: Combining traits

### 5. Utility Algorithms

- **std::min/max**: Min/max operations
- **std::clamp**: Value clamping
- **std::gcd/lcm**: Mathematical utilities
- **std::sample**: Random sampling
- **std::shuffle**: Random shuffling

## 🧩 Practice Exercises

### Exercise 38.1: Pair and Tuple
Use pairs and tuples for data organization.

### Exercise 38.2: Optional and Variant
Implement optional and variant patterns.

### Exercise 38.3: Utility Functions
Use utility functions for common operations.

### Exercise 38.4: Type Traits
Create and use custom type traits.

## 💻 Code Examples

### Pair and Tuple
```cpp
#include <iostream>
#include <tuple>
#include <string>

int main() {
    // Pair usage
    std::pair<std::string, int> person("John", 30);
    std::cout << "Name: " << person.first << ", Age: " << person.second << std::endl;
    
    // Tuple usage
    std::tuple<std::string, int, double> data("Alice", 25, 65.5);
    std::cout << "Name: " << std::get<0>(data) << std::endl;
    std::cout << "Age: " << std::get<1>(data) << std::endl;
    std::cout << "Weight: " << std::get<2>(data) << std::endl;
    
    // Structured bindings (C++17)
    auto [name, age, weight] = data;
    std::cout << "Name: " << name << ", Age: " << age << ", Weight: " << weight << std::endl;
    
    return 0;
}
```

### Optional and Variant
```cpp
#include <iostream>
#include <optional>
#include <variant>
#include <string>

int main() {
    // Optional usage
    std::optional<int> maybe_number = 42;
    if (maybe_number) {
        std::cout << "Number: " << *maybe_number << std::endl;
    }
    
    std::optional<int> empty_number;
    std::cout << "Empty optional: " << (empty_number ? "has value" : "no value") << std::endl;
    
    // Variant usage
    std::variant<int, std::string, double> value = "Hello";
    std::visit([](const auto& v) {
        std::cout << "Value: " << v << std::endl;
    }, value);
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use pairs and tuples** for structured data
2. **Apply optional and variant** for type-safe alternatives
3. **Master utility functions** for common operations
4. **Use type traits** for compile-time type introspection
5. **Apply utility algorithms** for efficient operations

## 🔗 Next Steps

After mastering utilities, proceed to Chapter 39 to learn about strings and string views.

## 📚 Additional Resources

- C++ Reference: Utilities
- C++ Core Guidelines: Utilities
- Practice with utility classes and functions
