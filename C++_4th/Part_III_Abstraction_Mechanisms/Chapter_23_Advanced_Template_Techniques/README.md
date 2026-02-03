# Chapter 23: Advanced Template Techniques

## 📘 Learning Objectives

After completing this chapter, you will:
- Master advanced template specialization techniques
- Understand template argument deduction and forwarding
- Learn about template instantiation and compilation
- Master template design patterns and idioms
- Understand template performance optimization

## 🎯 Key Concepts

### 1. Template Argument Deduction

- **Automatic type deduction**: Template parameter inference
- **Deduction guides**: C++17 deduction guide syntax
- **Perfect forwarding**: Forwarding template arguments
- **Universal references**: T&& template parameters
- **Reference collapsing**: Reference type collapsing rules

### 2. Template Instantiation

- **Implicit instantiation**: Automatic template instantiation
- **Explicit instantiation**: Manual template instantiation
- **Template specialization**: Specialized template versions
- **Template compilation**: Compile-time template processing
- **Template bloat**: Code size considerations

### 3. Template Design Patterns

- **CRTP**: Curiously Recurring Template Pattern
- **Type erasure**: Hiding concrete types
- **Policy-based design**: Template policy classes
- **Traits**: Type trait design patterns
- **Tag dispatch**: Runtime dispatch with tags

### 4. Template Optimization

- **Template specialization**: Performance optimization
- **Partial specialization**: Selective optimization
- **Template metafunctions**: Compile-time optimization
- **SFINAE optimization**: Conditional compilation
- **Template caching**: Compilation speed optimization

### 5. Advanced Template Features

- **Template templates**: Templates taking templates
- **Variable templates**: C++14 variable templates
- **Fold expressions**: C++17 fold syntax
- **If constexpr**: C++17 compile-time if
- **Concepts**: C++20 template constraints

## 🧩 Practice Exercises

### Exercise 23.1: Template Argument Deduction
Implement templates with automatic argument deduction.

### Exercise 23.2: Template Design Patterns
Use CRTP and policy-based design.

### Exercise 23.3: Template Optimization
Optimize template performance with specialization.

### Exercise 23.4: Advanced Template Features
Use modern C++ template features.

## 💻 Code Examples

### Template Argument Deduction
```cpp
#include <iostream>
#include <utility>

// Template with automatic deduction
template<typename T>
auto make_wrapper(T&& value) {
    return std::forward<T>(value);
}

// Deduction guide
template<typename T>
class Wrapper {
    T value;
public:
    Wrapper(T v) : value(v) {}
    T get() const { return value; }
};

// Deduction guide for Wrapper
template<typename T>
Wrapper(T) -> Wrapper<T>;

int main() {
    auto wrapper = make_wrapper(42);
    auto wrapper2 = Wrapper{3.14};  // Deduction guide
    
    std::cout << wrapper << std::endl;
    std::cout << wrapper2.get() << std::endl;
    
    return 0;
}
```

### CRTP Pattern
```cpp
#include <iostream>

// CRTP base class
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

// CRTP derived class
class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

int main() {
    Derived d;
    d.interface();  // Calls Derived::implementation
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Master template argument deduction** for cleaner code
2. **Use design patterns** for flexible template design
3. **Optimize templates** with specialization and metafunctions
4. **Understand instantiation** for compilation control
5. **Apply modern features** for better template code

## 🔗 Next Steps

After mastering advanced template techniques, proceed to Chapter 24 to learn about type traits and concepts.

## 📚 Additional Resources

- C++ Reference: Templates
- C++ Core Guidelines: Templates
- Practice with complex template patterns
