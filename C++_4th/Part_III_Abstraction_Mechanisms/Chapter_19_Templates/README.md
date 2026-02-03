# Chapter 19: Templates

## 📘 Learning Objectives

After completing this chapter, you will:
- Master function templates and class templates
- Understand template instantiation and specialization
- Learn about template metaprogramming
- Master variadic templates and parameter packs
- Understand SFINAE and type traits

## 🎯 Key Concepts

### 1. Function Templates

- **Template syntax**: template<typename T> or template<class T>
- **Template parameters**: Type and non-type parameters
- **Template instantiation**: Compiler generates code
- **Template specialization**: Custom implementations
- **Template overloading**: Multiple template functions

### 2. Class Templates

- **Template classes**: Generic classes
- **Member function templates**: Generic member functions
- **Template specialization**: Partial and explicit specialization
- **Template inheritance**: Inheriting from template classes
- **Template friends**: Friend functions in templates

### 3. Template Metaprogramming

- **Compile-time computation**: Calculations at compile time
- **Type traits**: Compile-time type information
- **Template recursion**: Recursive template definitions
- **SFINAE**: Substitution Failure Is Not An Error
- **constexpr**: Compile-time evaluation

### 4. Variadic Templates

- **Parameter packs**: Variable number of template parameters
- **Pack expansion**: Expanding parameter packs
- **Fold expressions**: C++17 fold operations
- **Perfect forwarding**: Forwarding arguments efficiently

### 5. Advanced Template Features

- **Template aliases**: using declarations for templates
- **Template template parameters**: Templates as parameters
- **Dependent names**: Names dependent on template parameters
- **Two-phase lookup**: Template name resolution

## 🧩 Practice Exercises

### Exercise 19.1: Function Templates
Create generic functions using templates.

### Exercise 19.2: Class Templates
Implement generic classes and containers.

### Exercise 19.3: Template Specialization
Specialize templates for specific types.

### Exercise 19.4: Template Metaprogramming
Use templates for compile-time computation.

## 💻 Code Examples

### Function Templates
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Function template
template<typename T>
T find_max(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("Vector is empty");
    }
    
    T max_val = vec[0];
    for (const auto& item : vec) {
        if (item > max_val) {
            max_val = item;
        }
    }
    return max_val;
}

// Template specialization
template<>
std::string find_max<std::string>(const std::vector<std::string>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("Vector is empty");
    }
    
    std::string max_val = vec[0];
    for (const auto& item : vec) {
        if (item.length() > max_val.length()) {
            max_val = item;
        }
    }
    return max_val;
}

int main() {
    std::vector<int> int_vec = {1, 5, 3, 9, 2};
    std::vector<std::string> str_vec = {"hello", "world", "cpp"};
    
    std::cout << "Max int: " << find_max(int_vec) << std::endl;
    std::cout << "Max string: " << find_max(str_vec) << std::endl;
    
    return 0;
}
```

### Class Templates
```cpp
#include <iostream>
#include <vector>

// Class template
template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    void push(const T& item) {
        data.push_back(item);
    }
    
    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }
    
    T& top() {
        if (data.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data.back();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
};

int main() {
    Stack<int> int_stack;
    Stack<std::string> str_stack;
    
    int_stack.push(42);
    int_stack.push(84);
    
    str_stack.push("hello");
    str_stack.push("world");
    
    std::cout << "Int stack top: " << int_stack.top() << std::endl;
    std::cout << "String stack top: " << str_stack.top() << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use templates for generic code**: Avoid code duplication
2. **Understand template instantiation**: Know when code is generated
3. **Use specialization carefully**: Only when necessary
4. **Prefer constexpr**: For compile-time computation
5. **Use SFINAE judiciously**: For type-based selection

## 🔗 Next Steps

After mastering templates, proceed to Chapter 20 to learn about generic programming.

## 📚 Additional Resources

- C++ Reference: Templates
- C++ Core Guidelines: Templates
- Practice with template metaprogramming
