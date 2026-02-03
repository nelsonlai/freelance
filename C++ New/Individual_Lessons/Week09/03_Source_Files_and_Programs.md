# Lesson 9.3: Source Files and Programs

## Learning Objectives
- Master source file organization and structure
- Understand header files and include guards
- Learn compilation and linking process
- Practice with program structure and build systems
- Explore modern build tools and project organization

## Prerequisites
- Completed Lesson 9.2 (Namespaces)
- Understanding of basic C++ syntax
- Knowledge of functions and classes

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Source File Organization

#### File Types
- **Header files (.h/.hpp):** Declarations and interface definitions
- **Source files (.cpp/.cc):** Implementation and executable code
- **Inline files (.inl):** Template implementations
- **Module files (.cppm):** C++20 modules (future)

#### Basic File Structure
```cpp
// header.h
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

class MyClass {
public:
    MyClass(const std::string& name);
    void display() const;
private:
    std::string name_;
};

#endif // HEADER_H

// source.cpp
#include "header.h"

MyClass::MyClass(const std::string& name) : name_(name) {}

void MyClass::display() const {
    std::cout << "Name: " << name_ << std::endl;
}
```

### 2. Header Files and Include Guards

#### Include Guards
```cpp
#ifndef MY_HEADER_H
#define MY_HEADER_H
// Header content
#endif // MY_HEADER_H
```

#### Modern Include Guards (C++11)
```cpp
#pragma once
// Header content
```

#### Header File Best Practices
- Include only what you need
- Use forward declarations when possible
- Avoid including headers in other headers unnecessarily
- Use include guards or #pragma once

### 3. Compilation and Linking

#### Compilation Process
1. **Preprocessing:** Expand macros and includes
2. **Compilation:** Convert source to object files
3. **Linking:** Combine object files into executable

#### Compiler Commands
```bash
# Compile single file
g++ -c source.cpp -o source.o

# Compile and link
g++ source.cpp -o program

# Compile multiple files
g++ main.cpp utils.cpp -o program

# With optimization and warnings
g++ -Wall -Wextra -O2 main.cpp utils.cpp -o program
```

---

## Demonstration (25 minutes)

### File Organization Examples
```cpp
// math_utils.h
#pragma once
#include <vector>

namespace MathUtils {
    double average(const std::vector<double>& numbers);
    double standard_deviation(const std::vector<double>& numbers);
    int factorial(int n);
}

// math_utils.cpp
#include "math_utils.h"
#include <numeric>
#include <cmath>

namespace MathUtils {
    double average(const std::vector<double>& numbers) {
        if (numbers.empty()) return 0.0;
        double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
        return sum / numbers.size();
    }
    
    double standard_deviation(const std::vector<double>& numbers) {
        if (numbers.size() < 2) return 0.0;
        double avg = average(numbers);
        double sum_sq_diff = 0.0;
        for (double num : numbers) {
            double diff = num - avg;
            sum_sq_diff += diff * diff;
        }
        return std::sqrt(sum_sq_diff / (numbers.size() - 1));
    }
    
    int factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
}

// main.cpp
#include "math_utils.h"
#include <iostream>

int main() {
    std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    std::cout << "Numbers: ";
    for (double num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Average: " << MathUtils::average(numbers) << std::endl;
    std::cout << "Standard deviation: " << MathUtils::standard_deviation(numbers) << std::endl;
    std::cout << "Factorial of 5: " << MathUtils::factorial(5) << std::endl;
    
    return 0;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: File Organization
Organize code into multiple files:

**Tasks:**
1. Create header files with proper include guards
2. Implement source files with corresponding headers
3. Organize classes and functions into logical files
4. Practice forward declarations

### Activity 2: Build System
Set up build systems:

**Tasks:**
1. Create Makefiles for compilation
2. Use CMake for cross-platform builds
3. Set up project structure
4. Configure compiler flags and options

### Activity 3: Program Structure
Design program architecture:

**Tasks:**
1. Separate interface from implementation
2. Create modular program structure
3. Handle dependencies between modules
4. Implement proper error handling

---

## Key Concepts

### 1. Separate Compilation
```cpp
// Each source file is compiled independently
// Object files are linked together to form executable

// file1.cpp
int add(int a, int b) { return a + b; }

// file2.cpp
int multiply(int a, int b) { return a * b; }

// main.cpp
#include "file1.h"
#include "file2.h"
int main() {
    int result = add(multiply(2, 3), 4);
    return 0;
}
```

### 2. Linkage
```cpp
// External linkage (default for non-static functions)
int global_function() { return 42; }

// Internal linkage (static functions)
static int internal_function() { return 24; }

// No linkage (local variables)
void function() {
    int local_var = 10;  // No linkage
}
```

### 3. Forward Declarations
```cpp
// Forward declaration (no implementation needed)
class MyClass;
void my_function(MyClass& obj);

// Use forward declarations to reduce dependencies
class AnotherClass {
    MyClass* ptr;  // Only needs pointer, not full definition
};
```

---

## Best Practices

### 1. File Organization
- One class per header file
- Group related functions together
- Use consistent naming conventions
- Keep files focused and cohesive

### 2. Include Management
- Include only what you need
- Use forward declarations when possible
- Avoid circular dependencies
- Order includes consistently

### 3. Build System
- Use modern build tools (CMake, Meson)
- Configure appropriate compiler flags
- Set up proper dependency management
- Enable warnings and optimizations

---

## Common Pitfalls

### 1. Circular Dependencies
```cpp
// Wrong: circular dependency
// file1.h
#include "file2.h"
class Class1 { Class2* ptr; };

// file2.h
#include "file1.h"
class Class2 { Class1* ptr; };

// Correct: forward declarations
// file1.h
class Class2;  // Forward declaration
class Class1 { Class2* ptr; };

// file2.h
class Class1;  // Forward declaration
class Class2 { Class1* ptr; };
```

### 2. Missing Include Guards
```cpp
// Wrong: no include guards
// myheader.h
class MyClass { /* ... */ };

// Correct: include guards
#ifndef MY_HEADER_H
#define MY_HEADER_H
class MyClass { /* ... */ };
#endif
```

### 3. Implementation in Headers
```cpp
// Wrong: implementation in header
// myheader.h
class MyClass {
public:
    void function() {
        // Implementation here causes recompilation of all users
    }
};

// Correct: declaration in header, implementation in source
// myheader.h
class MyClass {
public:
    void function();
};

// mysource.cpp
void MyClass::function() {
    // Implementation here
}
```

---

## Assessment

### Quiz Questions
1. What is the difference between header and source files?
2. Why are include guards necessary?
3. What is the purpose of forward declarations?
4. How does the compilation and linking process work?

### Practical Assessment
- Organize code into multiple files correctly
- Use proper include guards and forward declarations
- Set up build systems appropriately
- Handle dependencies between modules

---

## Homework Assignment

### Task 1: File Organization
Implement:
1. A multi-file C++ project with proper organization
2. Header files with include guards
3. Source files with implementations
4. Forward declarations where appropriate

### Task 2: Build System
Create:
1. Makefiles for compilation
2. CMake configuration files
3. Project structure documentation
4. Build scripts and automation

### Task 3: Program Architecture
Design:
1. Modular program structure
2. Clear separation of concerns
3. Proper dependency management
4. Error handling and logging

---

## Next Lesson Preview

In the next lesson, we'll learn about classes in depth:
- Class design and encapsulation
- Access specifiers and member functions
- Static members and nested classes
- Class relationships and inheritance

Make sure you understand source file organization before moving on!
