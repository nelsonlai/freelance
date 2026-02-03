# Lesson 1.1: C++ Philosophy and Modern Programming

## Learning Objectives
- Understand C++ as a systems programming language
- Learn about modern C++ (C++11/14/17/20) features
- Set up development environment
- Understand zero-cost abstractions principle

## Prerequisites
- Basic programming knowledge (any language)
- Access to a computer with internet connection

## Duration
90 minutes

## Materials Needed
- Computer with C++ compiler (GCC, Clang, or MSVC)
- IDE (Visual Studio, CLion, VS Code, or Code::Blocks)
- Text editor

---

## Lecture Content (30 minutes)

### 1. C++ History and Evolution
C++ was created by Bjarne Stroustrup in 1979 as "C with Classes". It has evolved through several standards:

- **C++98/C++03:** First standardized version
- **C++11:** Major update with modern features
- **C++14:** Small improvements and bug fixes
- **C++17:** Additional features and improvements
- **C++20:** Latest major update with concepts and modules

### 2. Modern C++ Philosophy
- **Zero-cost abstractions:** High-level constructs don't incur runtime overhead
- **RAII (Resource Acquisition Is Initialization):** Automatic resource management
- **Type safety:** Compile-time error detection
- **Performance:** Close to hardware performance when needed
- **Expressiveness:** Clear and concise code

### 3. C++ vs Other Languages
- **vs C:** Object-oriented, templates, exceptions, RAII
- **vs Java:** No garbage collector, direct memory control, multiple inheritance
- **vs Python:** Compiled, static typing, better performance
- **vs Rust:** More mature ecosystem, easier learning curve

---

## Hands-on Activity (30 minutes)

### Environment Setup
1. **Install Compiler:**
   - Windows: Visual Studio Community or MinGW
   - macOS: Xcode Command Line Tools
   - Linux: GCC or Clang via package manager

2. **Choose IDE:**
   - Visual Studio (Windows)
   - CLion (Cross-platform)
   - VS Code with C++ extension
   - Code::Blocks

3. **Verify Installation:**
   ```bash
   g++ --version
   # or
   clang++ --version
   ```

### Test Compilation
Create and compile your first C++ program to verify everything works.

---

## Practice Session (30 minutes)

### Activity 1: Hello World Variations
Students will create variations of the classic "Hello World" program to get familiar with:
- Basic program structure
- Compilation process
- Different output methods

### Activity 2: Environment Exploration
- Navigate IDE features
- Understand compilation process
- Learn about build configurations

---

## Key Concepts

### 1. Zero-Cost Abstractions
```cpp
// High-level code with no runtime overhead
std::vector<int> vec = {1, 2, 3, 4, 5};
for (const auto& item : vec) {
    // This loop is as efficient as a C-style loop
}
```

### 2. RAII Principle
```cpp
// Resources are automatically managed
{
    std::ifstream file("data.txt");  // File opened
    // Use file...
}  // File automatically closed when going out of scope
```

### 3. Modern C++ Features Preview
- `auto` keyword for type deduction
- Range-based for loops
- Smart pointers for memory management
- Lambda expressions for functional programming

---

## Assessment

### Quiz Questions
1. What does RAII stand for and why is it important?
2. Name three advantages of modern C++ over C.
3. What is meant by "zero-cost abstractions"?

### Practical Assessment
- Successfully compile and run a C++ program
- Demonstrate understanding of IDE features
- Explain the compilation process

---

## Homework Assignment

### Task 1: Research
Research and write a short paragraph about:
- One modern C++ feature introduced in C++11
- How C++ differs from another programming language you know

### Task 2: Practice
Create a simple program that:
- Prints your name and student ID
- Calculates and displays the area of a rectangle
- Uses at least one modern C++ feature (like `auto`)

---

## Additional Resources

### Online References
- [cppreference.com](https://cppreference.com) - Comprehensive C++ reference
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/) - Best practices
- [Bjarne Stroustrup's FAQ](http://www.stroustrup.com/bs_faq.html)

### Books
- "The C++ Programming Language, 4th Edition" by Bjarne Stroustrup
- "Effective Modern C++" by Scott Meyers
- "C++ Primer" by Stanley Lippman

---

## Next Lesson Preview

In the next lesson, we'll dive into basic program structure and variables. We'll learn about:
- C++ program anatomy
- Fundamental data types
- Variable declaration and initialization
- The `auto` keyword and type deduction

Make sure you have your development environment set up and working before the next class!
