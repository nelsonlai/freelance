# Lesson 7.3: Enumerations

## Learning Objectives
- Master enum declaration and usage
- Understand scoped enumerations (enum class)
- Learn enum operators and conversions
- Practice with enum applications
- Explore enum best practices and modern features

## Prerequisites
- Completed Lesson 7.2 (Unions)
- Understanding of basic data types
- Knowledge of constants and literals

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Enumeration Fundamentals

#### What are Enumerations?
- **Named constants:** Define a set of named integer constants
- **Type safety:** Create a distinct type for a set of values
- **Readability:** Make code more self-documenting
- **Maintainability:** Easy to add or modify values

#### Traditional Enum Declaration
```cpp
enum Color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};

enum Status {
    PENDING = 10,
    RUNNING = 20,
    COMPLETED = 30
};
```

### 2. Scoped Enumerations (enum class)

#### Benefits of enum class
- **Scope:** Values are scoped to the enum name
- **Type safety:** No implicit conversions
- **Namespace:** Avoids name conflicts
- **Strong typing:** Prevents accidental comparisons

#### enum class Declaration
```cpp
enum class Color {
    RED,
    GREEN,
    BLUE
};

enum class Status {
    PENDING = 10,
    RUNNING = 20,
    COMPLETED = 30
};
```

### 3. Enum Usage

#### Basic Usage
```cpp
Color color = Color::RED;
if (color == Color::RED) {
    std::cout << "Color is red" << std::endl;
}

Status status = Status::RUNNING;
std::cout << "Status value: " << static_cast<int>(status) << std::endl;
```

#### Enum Operations
```cpp
enum class Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

Direction turnRight(Direction dir) {
    return static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
}
```

---

## Demonstration (25 minutes)

### Enum Examples
```cpp
#include <iostream>

enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4
};

void demonstrateEnums() {
    std::cout << "=== Enum Demonstration ===" << std::endl;
    
    Priority priority = Priority::HIGH;
    
    switch (priority) {
        case Priority::LOW:
            std::cout << "Low priority task" << std::endl;
            break;
        case Priority::MEDIUM:
            std::cout << "Medium priority task" << std::endl;
            break;
        case Priority::HIGH:
            std::cout << "High priority task" << std::endl;
            break;
        case Priority::CRITICAL:
            std::cout << "Critical priority task" << std::endl;
            break;
    }
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Enum Implementation
Implement and test enums:

**Tasks:**
1. Create basic enums with custom values
2. Implement enum class with scoped values
3. Build enum utility functions
4. Test enum conversions and operations

### Activity 2: Enum Applications
Apply enums to real problems:

**Tasks:**
1. Implement a state machine
2. Create a configuration system
3. Build a game object system
4. Design a logging system

### Activity 3: Enum Best Practices
Practice enum best practices:

**Tasks:**
1. Use enum class for type safety
2. Implement enum operators
3. Handle enum conversions safely
4. Apply modern enum features

---

## Key Concepts

### 1. Enum Values
```cpp
enum class Size {
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 4,
    XLARGE = 8
};

// Bitwise operations
Size combined = static_cast<Size>(static_cast<int>(Size::SMALL) | static_cast<int>(Size::LARGE));
```

### 2. Enum Conversions
```cpp
enum class Color { RED, GREEN, BLUE };

Color color = Color::RED;
int value = static_cast<int>(color);        // Convert to int
Color newColor = static_cast<Color>(1);     // Convert from int
```

### 3. Enum Iteration
```cpp
enum class Direction { NORTH, EAST, SOUTH, WEST };

Direction directions[] = {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
for (auto dir : directions) {
    std::cout << static_cast<int>(dir) << std::endl;
}
```

---

## Best Practices

### 1. Enum Design
- Use enum class for new code
- Provide meaningful names
- Use appropriate underlying types
- Document enum purpose

### 2. Type Safety
- Prefer enum class over enum
- Use explicit conversions
- Avoid implicit comparisons
- Handle enum values safely

### 3. Code Organization
- Group related enums
- Use consistent naming
- Provide utility functions
- Consider enum operators

---

## Common Pitfalls

### 1. Implicit Conversions
```cpp
// Wrong: traditional enum allows implicit conversion
enum Color { RED, GREEN, BLUE };
Color color = RED;
int value = color;  // Implicit conversion!

// Correct: enum class prevents implicit conversion
enum class Color { RED, GREEN, BLUE };
Color color = Color::RED;
int value = static_cast<int>(color);  // Explicit conversion required
```

### 2. Scope Issues
```cpp
// Wrong: traditional enum pollutes global scope
enum Color { RED, GREEN, BLUE };
enum TrafficLight { RED, YELLOW, GREEN };  // Error: RED redefined!

// Correct: enum class provides scoping
enum class Color { RED, GREEN, BLUE };
enum class TrafficLight { RED, YELLOW, GREEN };  // OK: scoped
```

### 3. Uninitialized Enums
```cpp
// Wrong: uninitialized enum
enum class Status { PENDING, RUNNING, COMPLETED };
Status status;  // Uninitialized!

// Correct: initialize enum
Status status = Status::PENDING;
```

---

## Assessment

### Quiz Questions
1. What is the difference between enum and enum class?
2. How do you convert between enum and integer values?
3. Why are scoped enumerations safer?
4. When should you use enums instead of constants?

### Practical Assessment
- Implement working enum code
- Use enums safely and correctly
- Apply enums to solve problems
- Handle enum operations properly

---

## Homework Assignment

### Task 1: Enum Library
Implement:
1. A comprehensive enum utility library
2. Enum operators and conversions
3. Enum iteration and range functions
4. Type-safe enum wrappers

### Task 2: Enum Applications
Apply enums to:
1. State machine implementations
2. Configuration management systems
3. Game object state systems
4. Logging and debugging systems

### Task 3: Enum Analysis
Analyze:
1. Performance implications of enums
2. Memory usage of different enum types
3. Type safety benefits of enum class
4. Modern enum features and alternatives

---

## Next Lesson Preview

In the next lesson, we'll learn about statements:
- Expression statements and declarations
- Compound statements and blocks
- Selection statements (if, switch)
- Iteration statements (for, while, do-while)

Make sure you understand enumerations before moving on!