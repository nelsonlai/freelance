# Lesson 5.2: Types and Declarations Deep Dive

## Learning Objectives
- Master fundamental C++ types and their characteristics
- Understand type conversions and promotions
- Learn about type aliases and typedef
- Practice with const and volatile qualifiers
- Explore type deduction with auto and decltype

## Prerequisites
- Completed Lesson 5.1 (Smart Pointers)
- Understanding of basic C++ types
- Familiarity with variable declarations

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Fundamental Types

#### Built-in Types
- **Integer types:** int, short, long, long long
- **Floating-point types:** float, double, long double
- **Character types:** char, wchar_t, char16_t, char32_t
- **Boolean type:** bool
- **Void type:** void

#### Type Characteristics
```cpp
#include <iostream>
#include <limits>

void demonstrateTypes() {
    std::cout << "Integer types:" << std::endl;
    std::cout << "int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "short: " << sizeof(short) << " bytes" << std::endl;
    std::cout << "long: " << sizeof(long) << " bytes" << std::endl;
    std::cout << "long long: " << sizeof(long long) << " bytes" << std::endl;
    
    std::cout << "
Floating-point types:" << std::endl;
    std::cout << "float: " << sizeof(float) << " bytes" << std::endl;
    std::cout << "double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "long double: " << sizeof(long double) << " bytes" << std::endl;
    
    std::cout << "
Range limits:" << std::endl;
    std::cout << "int range: " << std::numeric_limits<int>::min() 
              << " to " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "double range: " << std::numeric_limits<double>::min() 
              << " to " << std::numeric_limits<double>::max() << std::endl;
}
```

### 2. Type Conversions

#### Implicit Conversions
- **Promotions:** char to int, float to double
- **Narrowing conversions:** double to int
- **Boolean conversions:** Any type to bool

#### Explicit Conversions
```cpp
// C-style cast
int x = (int)3.14;

// Static cast
int y = static_cast<int>(3.14);

// Dynamic cast (for polymorphic types)
// Base* ptr = dynamic_cast<Derived*>(base_ptr);

// Const cast
const int* const_ptr = &x;
int* mutable_ptr = const_cast<int*>(const_ptr);

// Reinterpret cast
int* int_ptr = &x;
char* char_ptr = reinterpret_cast<char*>(int_ptr);
```

### 3. Type Aliases and Typedef

#### Traditional Typedef
```cpp
typedef std::vector<int> IntVector;
typedef int (*FunctionPtr)(int, int);
```

#### Modern Type Aliases
```cpp
using IntVector = std::vector<int>;
using FunctionPtr = int (*)(int, int);
using StringMap = std::map<std::string, std::string>;
```

### 4. Const and Volatile Qualifiers

#### Const Qualifier
```cpp
const int x = 42;           // Immutable value
const int* ptr = &x;        // Pointer to const
int* const const_ptr = &y;  // Const pointer
const int* const both = &x; // Const pointer to const
```

#### Volatile Qualifier
```cpp
volatile int counter = 0;   // May change unexpectedly
volatile int* vol_ptr = &counter;
```

### 5. Auto and Decltype

#### Auto Type Deduction
```cpp
auto x = 42;              // int
auto y = 3.14;            // double
auto z = std::string("hello"); // std::string
auto vec = std::vector<int>{1, 2, 3}; // std::vector<int>
```

#### Decltype
```cpp
int x = 42;
decltype(x) y = x;        // y is int
decltype(x + 3.14) z;     // z is double
```

---

## Demonstration (25 minutes)

### Type System Examples
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>

void demonstrateTypeSystem() {
    // Fundamental types
    int integer = 42;
    double floating = 3.14159;
    char character = 'A';
    bool boolean = true;
    
    std::cout << "Types:" << std::endl;
    std::cout << "int: " << typeid(integer).name() << std::endl;
    std::cout << "double: " << typeid(floating).name() << std::endl;
    std::cout << "char: " << typeid(character).name() << std::endl;
    std::cout << "bool: " << typeid(boolean).name() << std::endl;
    
    // Auto type deduction
    auto auto_int = 42;
    auto auto_double = 3.14;
    auto auto_string = std::string("Hello");
    
    std::cout << "
Auto deduction:" << std::endl;
    std::cout << "auto_int: " << typeid(auto_int).name() << std::endl;
    std::cout << "auto_double: " << typeid(auto_double).name() << std::endl;
    std::cout << "auto_string: " << typeid(auto_string).name() << std::endl;
    
    // Type aliases
    using IntVector = std::vector<int>;
    using StringMap = std::map<std::string, std::string>;
    
    IntVector numbers = {1, 2, 3, 4, 5};
    StringMap dictionary = {{"hello", "world"}, {"cpp", "programming"}};
    
    std::cout << "
Type aliases:" << std::endl;
    std::cout << "IntVector: " << typeid(numbers).name() << std::endl;
    std::cout << "StringMap: " << typeid(dictionary).name() << std::endl;
}
```

### Const Examples
```cpp
void demonstrateConst() {
    const int immutable = 42;
    // immutable = 50;  // Error: cannot modify const
    
    int mutable_var = 100;
    const int* ptr_to_const = &mutable_var;
    // *ptr_to_const = 200;  // Error: cannot modify through const pointer
    
    int* const const_ptr = &mutable_var;
    *const_ptr = 200;  // OK: can modify value
    // const_ptr = &immutable;  // Error: cannot modify const pointer
    
    const int* const both_const = &mutable_var;
    // *both_const = 300;  // Error: cannot modify value
    // both_const = &immutable;  // Error: cannot modify pointer
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Type System Exploration
Explore the type system:

**Tasks:**
1. Investigate size and range of all fundamental types
2. Experiment with type conversions
3. Create custom type aliases
4. Test const and volatile qualifiers

### Activity 2: Auto and Decltype
Practice type deduction:

**Tasks:**
1. Use auto for variable declarations
2. Apply decltype for type queries
3. Combine auto with containers
4. Test type deduction edge cases

### Activity 3: Type Safety
Implement type-safe code:

**Tasks:**
1. Use explicit casts appropriately
2. Implement const-correct functions
3. Create type-safe wrappers
4. Handle type conversions safely

---

## Key Concepts

### 1. Type Safety
```cpp
// Type-safe function
void processNumber(const int& num) {
    std::cout << "Processing: " << num << std::endl;
}

// Type-safe container
std::vector<int> numbers;
numbers.push_back(42);  // Type-safe insertion
```

### 2. Const Correctness
```cpp
class Container {
private:
    std::vector<int> data_;
    
public:
    void add(int value) {
        data_.push_back(value);
    }
    
    int get(size_t index) const {
        return data_[index];  // Const method
    }
    
    size_t size() const {
        return data_.size();
    }
};
```

### 3. Type Aliases for Readability
```cpp
// Complex type made readable
using DatabaseConnection = std::unique_ptr<sqlite3, decltype(&sqlite3_close)>;
using UserMap = std::map<std::string, std::shared_ptr<User>>;
using EventCallback = std::function<void(const Event&)>;
```

---

## Best Practices

### 1. Type Selection
- Use appropriate types for the domain
- Prefer signed integers for most cases
- Use double for floating-point calculations
- Choose types based on required range and precision

### 2. Type Safety
- Avoid C-style casts
- Use explicit casts when necessary
- Prefer const correctness
- Use auto judiciously for complex types

### 3. Type Aliases
- Use type aliases for complex types
- Prefer using over typedef
- Make aliases descriptive and meaningful
- Group related aliases together

---

## Common Pitfalls

### 1. Implicit Conversions
```cpp
// Dangerous implicit conversion
void function(int x) { /* ... */ }
function(3.14);  // Implicit double to int conversion

// Better: explicit conversion
function(static_cast<int>(3.14));
```

### 2. Const Correctness
```cpp
// Wrong: non-const method accessing const object
class BadClass {
public:
    void modify() { /* ... */ }
};

const BadClass obj;
// obj.modify();  // Error: cannot call non-const method

// Correct: const method
class GoodClass {
public:
    void modify() const { /* ... */ }
};
```

### 3. Type Aliases
```cpp
// Wrong: confusing alias
using T = int;  // What is T?

// Correct: descriptive alias
using UserId = int;
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
```

---

## Assessment

### Quiz Questions
1. What are the differences between fundamental types?
2. When should you use explicit type conversions?
3. What is the difference between const and volatile?
4. How does auto type deduction work?

### Practical Assessment
- Implement type-safe code
- Use appropriate type conversions
- Apply const correctness
- Create meaningful type aliases

---

## Homework Assignment

### Task 1: Type System Investigation
Investigate:
1. Size and range of all fundamental types
2. Type conversion behaviors
3. Performance implications of different types
4. Platform-specific type variations

### Task 2: Type-Safe Library
Create:
1. A type-safe container library
2. Type-safe function wrappers
3. Const-correct utility classes
4. Type alias definitions

### Task 3: Type Deduction
Practice:
1. Auto type deduction in various contexts
2. Decltype for type queries
3. Template type deduction
4. Lambda type deduction

---

## Next Lesson Preview

In the next lesson, we'll learn about fundamental type characteristics:
- Integer types and their ranges
- Floating-point precision and representation
- Character encoding and Unicode
- Boolean logic and operations

Make sure you understand type declarations before moving on!