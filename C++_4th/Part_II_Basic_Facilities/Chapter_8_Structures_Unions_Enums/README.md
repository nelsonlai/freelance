# Chapter 8: Structures, Unions, and Enumerations

## 📘 Learning Objectives

After completing this chapter, you will:
- Master user-defined types (struct, enum, union)
- Understand type-safe enums (enum class)
- Learn when to use each type
- Master initialization and member access
- Understand memory layout and alignment

## 🎯 Key Concepts

### 1. Structures (struct)

- **Purpose**: Group related data together
- **Default access**: Public members
- **Initialization**: Multiple initialization methods
- **Member functions**: Can have methods
- **Memory layout**: Contiguous memory allocation

### 2. Enumerations (enum)

- **Traditional enum**: Implicit conversion to int
- **Scoped enum (enum class)**: Type-safe, no implicit conversion
- **Underlying type**: Can specify underlying integer type
- **Forward declaration**: Can be forward declared

### 3. Unions

- **Purpose**: Share memory between different types
- **Size**: Size of largest member
- **Active member**: Only one member is active at a time
- **Type safety**: No built-in type safety

### 4. Type Safety

- **enum class**: Provides type safety
- **Strong typing**: Prevents accidental conversions
- **Namespace**: Scoped to prevent name conflicts

## 🧩 Practice Exercises

### Exercise 8.1: Structure Design
Create structures for different data types (Person, Point, Rectangle).

### Exercise 8.2: Enumeration Usage
Use both traditional and scoped enums effectively.

### Exercise 8.3: Union Implementation
Implement type-safe unions with tagged unions.

### Exercise 8.4: Memory Layout
Study memory layout and alignment of structures.

## 💻 Code Examples

### Structure Examples
```cpp
#include <iostream>
#include <string>

// Basic structure
struct Point {
    double x, y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    void display() const {
        std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }
    
    double distance_from_origin() const {
        return std::sqrt(x * x + y * y);
    }
};

// Structure with different data types
struct Person {
    std::string name;
    int age;
    double height;
    bool is_student;
    
    Person(const std::string& name, int age, double height, bool is_student)
        : name(name), age(age), height(height), is_student(is_student) {}
    
    void display_info() const {
        std::cout << "Name: " << name << ", Age: " << age 
                  << ", Height: " << height << ", Student: " 
                  << std::boolalpha << is_student << std::endl;
    }
};

int main() {
    Point p1(3.0, 4.0);
    p1.display();
    std::cout << "Distance from origin: " << p1.distance_from_origin() << std::endl;
    
    Person person("Alice", 25, 5.6, true);
    person.display_info();
    
    return 0;
}
```

### Enumeration Examples
```cpp
#include <iostream>

// Traditional enum
enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW
};

// Scoped enum (enum class)
enum class Size {
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

// Enum with specified underlying type
enum class Status : unsigned char {
    PENDING = 0,
    ACTIVE = 1,
    COMPLETED = 2,
    CANCELLED = 3
};

int main() {
    // Traditional enum usage
    Color color = RED;
    std::cout << "Color: " << color << std::endl;  // Implicit conversion to int
    
    // Scoped enum usage
    Size size = Size::MEDIUM;
    // std::cout << "Size: " << size << std::endl;  // Compile error - no implicit conversion
    
    // Type-safe comparison
    if (size == Size::MEDIUM) {
        std::cout << "Size is medium" << std::endl;
    }
    
    // Status enum
    Status status = Status::ACTIVE;
    std::cout << "Status value: " << static_cast<int>(status) << std::endl;
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Structures**: Use for grouping related data
2. **Enums**: Use enum class for type safety
3. **Unions**: Use carefully, consider type safety
4. **Initialization**: Use modern initialization methods
5. **Memory layout**: Understand alignment and padding

## 🔗 Next Steps

After mastering structures, unions, and enums, proceed to Chapter 9 to learn about statements and control flow.

## 📚 Additional Resources

- C++ Reference: Structures, Unions, Enumerations
- C++ Core Guidelines: Enums
- Memory Layout Documentation
