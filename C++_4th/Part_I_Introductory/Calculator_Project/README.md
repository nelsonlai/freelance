# 🧮 Calculator Project - Part I Capstone

## 📘 Project Overview

This calculator project demonstrates all concepts learned in Part I of the C++ curriculum:
- User-defined classes and objects
- Exception handling
- STL containers and algorithms
- Basic threading concepts
- Clean, modular code structure

## 🎯 Learning Objectives

After completing this project, you will:
- Apply object-oriented programming principles
- Implement robust error handling with exceptions
- Use STL containers for data management
- Implement basic threading for complex calculations
- Design clean, maintainable code architecture

## 🏗️ Project Architecture

### Core Classes

1. **Calculator**: Main calculator class with basic operations
2. **Operation**: Base class for all operations
3. **ArithmeticOperation**: Handles basic arithmetic
4. **ScientificOperation**: Handles scientific calculations
5. **OperationHistory**: Manages calculation history
6. **CalculatorException**: Custom exception class

### Features

- **Basic Operations**: Addition, subtraction, multiplication, division
- **Scientific Operations**: Square root, power, logarithm, trigonometric functions
- **History Management**: Store and retrieve calculation history
- **Error Handling**: Comprehensive exception handling
- **Threading**: Background calculation for complex operations
- **Memory Management**: RAII principles throughout

## 🧩 Implementation Requirements

### 1. Exception Handling
- Custom exception classes
- Input validation
- Division by zero protection
- Overflow/underflow detection

### 2. STL Usage
- `std::vector` for operation history
- `std::string` for input/output
- `std::map` for operation lookup
- `std::thread` for background calculations

### 3. Class Design
- Proper encapsulation
- Constructor/destructor implementation
- Operator overloading where appropriate
- Const correctness

### 4. Threading
- Background calculation for expensive operations
- Thread-safe history management
- Proper thread cleanup

## 💻 Code Structure

```
Calculator_Project/
├── README.md
├── calculator.h
├── calculator.cpp
├── operation.h
├── operation.cpp
├── operation_history.h
├── operation_history.cpp
├── calculator_exception.h
├── calculator_exception.cpp
├── main.cpp
├── Makefile
└── tests/
    ├── test_calculator.cpp
    └── test_operations.cpp
```

## 🚀 Getting Started

1. **Compile the project**:
   ```bash
   make
   ```

2. **Run the calculator**:
   ```bash
   ./calculator
   ```

3. **Run tests**:
   ```bash
   make test
   ```

## 🎮 Usage Examples

### Basic Operations
```
Enter expression: 2 + 3
Result: 5

Enter expression: 10 / 2
Result: 5

Enter expression: sqrt(16)
Result: 4
```

### History Management
```
Command: history
1. 2 + 3 = 5
2. 10 / 2 = 5
3. sqrt(16) = 4

Command: clear
History cleared.
```

### Error Handling
```
Enter expression: 5 / 0
Error: Division by zero

Enter expression: sqrt(-4)
Error: Square root of negative number
```

## 🧪 Testing

The project includes comprehensive tests for:
- Basic arithmetic operations
- Scientific operations
- Error handling
- History management
- Threading functionality

## 📚 Key Learning Points

1. **RAII**: Resource management through object lifetime
2. **Exception Safety**: Proper error handling without resource leaks
3. **STL Integration**: Effective use of standard containers and algorithms
4. **Thread Safety**: Proper synchronization and thread management
5. **Code Organization**: Clean separation of concerns

## 🔗 Next Steps

After completing this project, you'll be ready for Part II of the curriculum, which covers advanced language features, memory management, and more complex programming patterns.

## 🏆 Success Criteria

- [ ] All basic operations work correctly
- [ ] Scientific operations function properly
- [ ] Exception handling works for all error cases
- [ ] History management is thread-safe
- [ ] Code follows C++ best practices
- [ ] All tests pass
- [ ] Memory management is correct (no leaks)
