# Lesson 7.2: Unions

## Learning Objectives
- Master union declaration and usage
- Understand union vs structure differences
- Learn union memory layout and alignment
- Practice with anonymous unions
- Explore union applications and best practices

## Prerequisites
- Completed Lesson 7.1 (Structures)
- Understanding of memory layout concepts
- Basic knowledge of data types

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Union Fundamentals

#### What are Unions?
- **Shared memory:** All members share the same memory location
- **Size:** Union size equals the size of its largest member
- **Access:** Only one member can be active at a time
- **Purpose:** Save memory when only one member is needed

#### Union Declaration
```cpp
union Data {
    int integer;
    double floating;
    char character;
};
```

### 2. Union vs Structure

#### Key Differences
| Feature | Union | Structure |
|---------|-------|-----------|
| Memory | Shared memory location | Separate memory locations |
| Size | Size of largest member | Sum of all members |
| Access | Only one member active | All members accessible |
| Purpose | Memory efficiency | Data grouping |

#### Memory Layout
```cpp
struct Point {
    int x, y;  // 8 bytes total
};

union Number {
    int i;
    double d;  // 8 bytes total (size of double)
};
```

### 3. Union Usage

#### Basic Usage
```cpp
union Data data;
data.integer = 42;
std::cout << data.integer << std::endl;

data.floating = 3.14;
std::cout << data.floating << std::endl;
// data.integer now contains garbage!
```

#### Tagged Unions
```cpp
struct TaggedData {
    enum Type { INTEGER, FLOATING, CHARACTER } type;
    union {
        int integer;
        double floating;
        char character;
    } value;
};
```

---

## Demonstration (25 minutes)

### Union Examples
```cpp
#include <iostream>

union Number {
    int integer;
    double floating;
    char character;
};

void demonstrateUnions() {
    std::cout << "=== Union Demonstration ===" << std::endl;
    
    union Number num;
    
    std::cout << "Union size: " << sizeof(union Number) << " bytes" << std::endl;
    
    // Use integer member
    num.integer = 42;
    std::cout << "Integer: " << num.integer << std::endl;
    
    // Use floating member (overwrites integer)
    num.floating = 3.14159;
    std::cout << "Floating: " << num.floating << std::endl;
    std::cout << "Integer (now garbage): " << num.integer << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Union Implementation
Implement and test unions:

**Tasks:**
1. Create basic unions with different types
2. Implement tagged unions
3. Test union memory layout
4. Compare union vs structure sizes

### Activity 2: Union Applications
Apply unions to real problems:

**Tasks:**
1. Implement a variant type
2. Create a flexible data container
3. Build a network packet structure
4. Design a graphics color system

### Activity 3: Union Safety
Practice union safety:

**Tasks:**
1. Implement safe union access
2. Use tagged unions correctly
3. Handle union lifetime
4. Avoid undefined behavior

---

## Key Concepts

### 1. Union Memory Layout
```cpp
union Example {
    char c;    // 1 byte
    int i;     // 4 bytes
    double d;  // 8 bytes
};
// Total size: 8 bytes (size of largest member)
```

### 2. Tagged Unions
```cpp
struct SafeUnion {
    enum { INT, DOUBLE, CHAR } tag;
    union {
        int i;
        double d;
        char c;
    };
};
```

### 3. Anonymous Unions
```cpp
struct Container {
    int type;
    union {  // Anonymous union
        int i;
        double d;
    };
};
```

---

## Best Practices

### 1. Union Design
- Use tagged unions for safety
- Document which member is active
- Keep unions simple and focused
- Consider alternatives like std::variant

### 2. Memory Management
- Be aware of memory layout
- Handle alignment issues
- Use appropriate member sizes
- Consider endianness

### 3. Safety
- Always use tagged unions when possible
- Don't access inactive members
- Initialize unions properly
- Use modern alternatives when available

---

## Common Pitfalls

### 1. Accessing Inactive Members
```cpp
// Wrong: accessing inactive member
union Data data;
data.integer = 42;
data.floating = 3.14;
std::cout << data.integer << std::endl;  // Undefined behavior!

// Correct: use tagged union
struct TaggedData {
    enum Type { INT, FLOAT } type;
    union {
        int i;
        float f;
    };
};
```

### 2. Memory Layout Assumptions
```cpp
// Wrong: assuming memory layout
union Data {
    char bytes[4];
    int value;
};
// Assumes specific byte order!

// Correct: use proper types
union Data {
    std::array<char, 4> bytes;
    int32_t value;
};
```

### 3. Lifetime Issues
```cpp
// Wrong: union with complex types
union BadUnion {
    std::string str;  // Dangerous!
    int value;
};

// Correct: use simple types or tagged union
union GoodUnion {
    char str[100];
    int value;
};
```

---

## Assessment

### Quiz Questions
1. What is the main difference between unions and structures?
2. How is union size determined?
3. Why are tagged unions safer than regular unions?
4. When should you use unions instead of structures?

### Practical Assessment
- Implement working union code
- Use unions safely and correctly
- Handle union memory layout
- Apply unions to solve problems

---

## Homework Assignment

### Task 1: Union Library
Implement:
1. A tagged union type system
2. A flexible data container using unions
3. A network packet structure
4. A graphics color representation

### Task 2: Union Applications
Create:
1. A variant type implementation
2. A memory-efficient data structure
3. A protocol message system
4. A configuration storage system

### Task 3: Union Analysis
Analyze:
1. Memory usage of unions vs structures
2. Performance implications of unions
3. Safety considerations with unions
4. Modern alternatives to unions

---

## Next Lesson Preview

In the next lesson, we'll learn about enumerations:
- Enum declaration and usage
- Scoped enumerations
- Enum class benefits
- Enum operators and conversions

Make sure you understand unions before moving on!