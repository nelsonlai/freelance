# Chapter 14: Namespaces

## 📘 Learning Objectives

After completing this chapter, you will:
- Master namespace declaration and usage
- Understand namespace scope and visibility
- Learn about namespace aliases and using declarations
- Master nested and anonymous namespaces
- Understand namespace organization best practices

## 🎯 Key Concepts

### 1. Namespace Basics

- **Namespace declaration**: namespace name { ... }
- **Namespace scope**: Variables and functions within namespace
- **Global namespace**: Default namespace for global declarations
- **Namespace resolution**: How names are found

### 2. Using Declarations

- **using declaration**: using namespace::name;
- **using directive**: using namespace name;
- **Scope of using**: Where using declarations apply
- **Name conflicts**: Handling ambiguous names

### 3. Namespace Aliases

- **Namespace aliases**: namespace alias = namespace_name;
- **Long namespace names**: Simplifying access
- **Conditional aliases**: Using aliases conditionally

### 4. Nested Namespaces

- **Nested namespaces**: namespace outer { namespace inner { ... } }
- **Namespace scope**: Accessing nested namespaces
- **Namespace hierarchy**: Organizing related code

### 5. Anonymous Namespaces

- **Anonymous namespaces**: namespace { ... }
- **Internal linkage**: File-local names
- **Static alternative**: Replacing static with anonymous namespaces

### 6. Namespace Organization

- **Logical grouping**: Organizing related code
- **Header organization**: Namespace usage in headers
- **Implementation files**: Namespace usage in source files

## 🧩 Practice Exercises

### Exercise 14.1: Basic Namespaces
Create and use basic namespaces.

### Exercise 14.2: Using Declarations
Use using declarations and directives.

### Exercise 14.3: Namespace Aliases
Create and use namespace aliases.

### Exercise 14.4: Nested Namespaces
Implement nested namespace hierarchies.

## 💻 Code Examples

### Basic Namespaces
```cpp
#include <iostream>

namespace math {
    int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int a, int b) {
        return a * b;
    }
}

namespace string_utils {
    std::string to_upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
}

int main() {
    std::cout << "math::add(5, 3) = " << math::add(5, 3) << std::endl;
    std::cout << "string_utils::to_upper(\"hello\") = " 
              << string_utils::to_upper("hello") << std::endl;
    
    return 0;
}
```

### Using Declarations
```cpp
#include <iostream>

namespace math {
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
}

namespace string_utils {
    std::string to_lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}

int main() {
    using math::add;  // Using declaration
    using namespace string_utils;  // Using directive
    
    std::cout << "add(5, 3) = " << add(5, 3) << std::endl;
    std::cout << "to_lower(\"HELLO\") = " << to_lower("HELLO") << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use namespaces** to organize code logically
2. **Avoid using directives** in headers
3. **Use using declarations** sparingly
4. **Prefer namespace aliases** for long names
5. **Use anonymous namespaces** for internal linkage

## 🔗 Next Steps

After mastering namespaces, proceed to Chapter 15 to learn about source files and program organization.

## 📚 Additional Resources

- C++ Reference: Namespaces
- C++ Core Guidelines: Namespaces
- Practice with namespace organization
