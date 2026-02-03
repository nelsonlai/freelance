# Chapter 12: Function Objects

## 📘 Learning Objectives

After completing this chapter, you will:
- Master function objects (functors) and their uses
- Understand lambda expressions and closures
- Learn about function adapters and binders
- Master STL function objects and predicates
- Understand modern C++ function programming

## 🎯 Key Concepts

### 1. Function Objects (Functors)

- **Function objects**: Classes with operator()
- **Callable objects**: Any object that can be called like a function
- **Stateful functions**: Function objects can maintain state
- **Template compatibility**: Work with STL algorithms

### 2. Lambda Expressions

- **Lambda syntax**: [capture](parameters) -> return_type { body }
- **Capture clauses**: Capture variables from enclosing scope
- **Capture by value**: [=] or [variable]
- **Capture by reference**: [&] or [&variable]
- **Generic lambdas**: [](auto param) { ... }

### 3. Function Adapters

- **std::bind**: Bind arguments to functions
- **std::function**: Type-erased function wrapper
- **Function composition**: Combine multiple functions
- **Partial application**: Fix some arguments

### 4. STL Function Objects

- **Arithmetic**: plus, minus, multiplies, divides, modulus
- **Logical**: logical_and, logical_or, logical_not
- **Comparison**: equal_to, not_equal_to, greater, less
- **Bitwise**: bit_and, bit_or, bit_xor

### 5. Predicates and Comparators

- **Predicates**: Functions returning bool
- **Unary predicates**: Take one argument
- **Binary predicates**: Take two arguments
- **Comparators**: For ordering and sorting

## 🧩 Practice Exercises

### Exercise 12.1: Function Objects
Create custom function objects for different operations.

### Exercise 12.2: Lambda Expressions
Use lambdas with STL algorithms.

### Exercise 12.3: Function Adapters
Use std::bind and std::function effectively.

### Exercise 12.4: STL Function Objects
Apply STL function objects in algorithms.

## 💻 Code Examples

### Function Objects
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Custom function object
class MultiplyBy {
private:
    int factor;
    
public:
    MultiplyBy(int f) : factor(f) {}
    
    int operator()(int x) const {
        return x * factor;
    }
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Use function object
    MultiplyBy multiply_by_3(3);
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), multiply_by_3);
    
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Lambda Expressions
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Lambda with capture
    int threshold = 5;
    auto is_greater_than = [threshold](int x) {
        return x > threshold;
    };
    
    // Use lambda with algorithm
    auto it = std::find_if(numbers.begin(), numbers.end(), is_greater_than);
    if (it != numbers.end()) {
        std::cout << "First number greater than " << threshold << ": " << *it << std::endl;
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use function objects** for stateful operations
2. **Prefer lambdas** for simple, one-off functions
3. **Use std::bind** for partial application
4. **Use std::function** for type erasure
5. **Understand capture semantics** in lambdas

## 🔗 Next Steps

After mastering function objects, proceed to Chapter 13 to learn about exception handling.

## 📚 Additional Resources

- C++ Reference: Function Objects
- C++ Core Guidelines: Function Objects
- Practice with STL algorithms and function objects
