# Lesson 9.2: Namespaces

## Learning Objectives
- Master namespace declaration and definition
- Understand namespace aliases and using declarations
- Learn anonymous namespaces and their uses
- Practice with namespace organization
- Explore namespace best practices and modern features

## Prerequisites
- Completed Lesson 9.1 (Exception Handling)
- Understanding of basic C++ syntax
- Knowledge of scope and visibility

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Namespace Fundamentals

#### What are Namespaces?
- **Name organization:** Namespaces organize code into logical groups
- **Name collision prevention:** Avoid naming conflicts between different libraries
- **Scope management:** Control the visibility of names
- **Code organization:** Group related functionality together

#### Namespace Declaration
```cpp
namespace MyNamespace {
    int value = 42;
    void function() {
        std::cout << "Hello from namespace" << std::endl;
    }
    
    class MyClass {
        // Class definition
    };
}

// Accessing namespace members
MyNamespace::value = 100;
MyNamespace::function();
```

### 2. Namespace Usage

#### Using Declarations
```cpp
// Using declaration for specific names
using std::cout;
using std::endl;

// Using directive for entire namespace
using namespace std;

// Selective using declarations
using MyNamespace::value;
using MyNamespace::function;
```

#### Namespace Aliases
```cpp
// Create shorter aliases for long namespace names
namespace fs = std::filesystem;
namespace chrono = std::chrono;

// Use aliases
fs::path file_path = "example.txt";
auto now = chrono::system_clock::now();
```

### 3. Nested and Anonymous Namespaces

#### Nested Namespaces
```cpp
namespace Outer {
    namespace Inner {
        void function() {
            std::cout << "Nested namespace" << std::endl;
        }
    }
}

// Access nested namespace
Outer::Inner::function();

// C++17 nested namespace syntax
namespace Outer::Inner {
    void another_function() {
        std::cout << "Another nested function" << std::endl;
    }
}
```

#### Anonymous Namespaces
```cpp
namespace {
    int internal_value = 42;
    void internal_function() {
        std::cout << "Internal function" << std::endl;
    }
}
// Equivalent to: static int internal_value = 42;
// static void internal_function() { ... }
```

---

## Demonstration (25 minutes)

### Namespace Examples
```cpp
#include <iostream>
#include <string>

namespace Math {
    const double PI = 3.14159;
    
    double circle_area(double radius) {
        return PI * radius * radius;
    }
    
    double circle_circumference(double radius) {
        return 2 * PI * radius;
    }
}

namespace StringUtils {
    std::string to_upper(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = std::toupper(c);
        }
        return result;
    }
    
    std::string to_lower(const std::string& str) {
        std::string result = str;
        for (char& c : result) {
            c = std::tolower(c);
        }
        return result;
    }
}

void demonstrateNamespaces() {
    std::cout << "=== Namespace Demonstration ===" << std::endl;
    
    // Using qualified names
    std::cout << "PI = " << Math::PI << std::endl;
    std::cout << "Circle area (radius 5): " << Math::circle_area(5) << std::endl;
    
    std::string text = "Hello World";
    std::cout << "Original: " << text << std::endl;
    std::cout << "Upper: " << StringUtils::to_upper(text) << std::endl;
    std::cout << "Lower: " << StringUtils::to_lower(text) << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Namespace Implementation
Implement namespaces:

**Tasks:**
1. Create custom namespaces for different modules
2. Implement nested namespaces
3. Use anonymous namespaces for internal functions
4. Practice namespace aliases

### Activity 2: Namespace Organization
Organize code with namespaces:

**Tasks:**
1. Design namespace hierarchy
2. Separate public and private interfaces
3. Use namespace aliases effectively
4. Implement namespace-based libraries

### Activity 3: Namespace Best Practices
Apply namespace best practices:

**Tasks:**
1. Avoid using directives in headers
2. Use selective using declarations
3. Organize related functionality
4. Handle namespace conflicts

---

## Key Concepts

### 1. Namespace Scope
```cpp
namespace MyNamespace {
    int global_var = 42;  // Namespace-scoped variable
    
    void function() {
        int local_var = 10;  // Function-scoped variable
        // Can access both global_var and local_var
    }
}

// global_var is not accessible here without qualification
```

### 2. Namespace Lookup
```cpp
namespace A {
    void function() { std::cout << "A::function" << std::endl; }
}

namespace B {
    void function() { std::cout << "B::function" << std::endl; }
    void test() {
        function();  // Calls B::function
        A::function();  // Calls A::function
    }
}
```

### 3. Namespace Composition
```cpp
namespace Library {
    namespace Core {
        class Base { /* ... */ };
    }
    
    namespace Graphics {
        class Window { /* ... */ };
    }
    
    namespace Audio {
        class Sound { /* ... */ };
    }
}
```

---

## Best Practices

### 1. Namespace Design
- Use descriptive namespace names
- Keep namespaces focused and cohesive
- Avoid overly deep nesting
- Use consistent naming conventions

### 2. Using Declarations
- Prefer using declarations over using directives
- Use using declarations in implementation files, not headers
- Be selective with using declarations
- Avoid using directives in global scope

### 3. Code Organization
- Group related functionality in namespaces
- Use anonymous namespaces for internal implementation
- Create namespace aliases for convenience
- Document namespace purposes

---

## Common Pitfalls

### 1. Using Directives in Headers
```cpp
// Wrong: using directive in header
// myheader.h
using namespace std;  // Pollutes global namespace for all users

// Correct: qualified names or selective using declarations
// myheader.h
#include <iostream>
// Use std::cout, std::endl, etc.
```

### 2. Namespace Pollution
```cpp
// Wrong: too many using declarations
using std::cout;
using std::endl;
using std::string;
using std::vector;
// ... many more

// Correct: selective using declarations
using std::cout;
using std::endl;
// Or use qualified names where appropriate
```

### 3. Namespace Conflicts
```cpp
// Wrong: conflicting names
namespace A {
    void function() { /* ... */ }
}

namespace B {
    void function() { /* ... */ }
}

using namespace A;
using namespace B;
function();  // Ambiguous!

// Correct: qualified names or selective using
A::function();
B::function();
```

---

## Assessment

### Quiz Questions
1. What is the purpose of namespaces in C++?
2. What is the difference between using declarations and using directives?
3. When should you use anonymous namespaces?
4. Why should you avoid using directives in header files?

### Practical Assessment
- Implement working namespace code
- Use namespaces correctly and safely
- Organize code with appropriate namespaces
- Handle namespace conflicts properly

---

## Homework Assignment

### Task 1: Namespace Library
Implement:
1. A library organized with multiple namespaces
2. Namespace aliases for convenience
3. Nested namespaces for logical grouping
4. Anonymous namespaces for internal implementation

### Task 2: Namespace Applications
Apply namespaces to:
1. Large project organization
2. Library design and implementation
3. Code modularity and separation
4. Interface design patterns

### Task 3: Namespace Analysis
Analyze:
1. Namespace design patterns
2. Namespace organization strategies
3. Performance implications of namespaces
4. Modern namespace features and best practices

---

## Next Lesson Preview

In the next lesson, we'll learn about source files and programs:
- Source file organization
- Header files and include guards
- Compilation and linking
- Program structure and build systems

Make sure you understand namespaces before moving on!
