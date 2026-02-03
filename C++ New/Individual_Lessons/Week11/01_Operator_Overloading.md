# Lesson 11.1: Operator Overloading

## Learning Objectives
- Master arithmetic and assignment operator overloading
- Understand comparison and logical operator overloading
- Learn function call and subscript operators
- Practice with type conversion operators
- Explore advanced operator overloading patterns

## Prerequisites
- Completed Lesson 10.3 (Copy and Move Semantics)
- Understanding of basic classes and objects
- Knowledge of constructors and destructors

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Arithmetic Operators

#### Basic Arithmetic Operators
```cpp
class Complex {
private:
    double real_;
    double imaginary_;
    
public:
    Complex(double real = 0.0, double imaginary = 0.0)
        : real_(real), imaginary_(imaginary) {}
    
    // Addition operator
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imaginary_ + other.imaginary_);
    }
    
    // Subtraction operator
    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imaginary_ - other.imaginary_);
    }
    
    // Multiplication operator
    Complex operator*(const Complex& other) const {
        return Complex(
            real_ * other.real_ - imaginary_ * other.imaginary_,
            real_ * other.imaginary_ + imaginary_ * other.real_
        );
    }
    
    // Division operator
    Complex operator/(const Complex& other) const {
        double denominator = other.real_ * other.real_ + other.imaginary_ * other.imaginary_;
        return Complex(
            (real_ * other.real_ + imaginary_ * other.imaginary_) / denominator,
            (imaginary_ * other.real_ - real_ * other.imaginary_) / denominator
        );
    }
    
    // Unary minus operator
    Complex operator-() const {
        return Complex(-real_, -imaginary_);
    }
    
    // Unary plus operator
    Complex operator+() const {
        return *this;
    }
    
    // Display
    void display() const {
        std::cout << real_ << " + " << imaginary_ << "i" << std::endl;
    }
};
```

### 2. Assignment Operators

#### Compound Assignment Operators
```cpp
class Vector {
private:
    double* data_;
    size_t size_;
    
public:
    Vector(size_t size) : size_(size) {
        data_ = new double[size_];
        std::fill(data_, data_ + size_, 0.0);
    }
    
    ~Vector() {
        delete[] data_;
    }
    
    // Copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new double[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
    
    // Addition assignment
    Vector& operator+=(const Vector& other) {
        if (size_ == other.size_) {
            for (size_t i = 0; i < size_; ++i) {
                data_[i] += other.data_[i];
            }
        }
        return *this;
    }
    
    // Subtraction assignment
    Vector& operator-=(const Vector& other) {
        if (size_ == other.size_) {
            for (size_t i = 0; i < size_; ++i) {
                data_[i] -= other.data_[i];
            }
        }
        return *this;
    }
    
    // Scalar multiplication assignment
    Vector& operator*=(double scalar) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] *= scalar;
        }
        return *this;
    }
    
    // Scalar division assignment
    Vector& operator/=(double scalar) {
        if (scalar != 0.0) {
            for (size_t i = 0; i < size_; ++i) {
                data_[i] /= scalar;
            }
        }
        return *this;
    }
};
```

### 3. Comparison Operators

#### Relational Operators
```cpp
class Fraction {
private:
    int numerator_;
    int denominator_;
    
    int gcd(int a, int b) const {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    void simplify() {
        int common_divisor = gcd(std::abs(numerator_), std::abs(denominator_));
        numerator_ /= common_divisor;
        denominator_ /= common_divisor;
    }
    
public:
    Fraction(int num, int denom) : numerator_(num), denominator_(denom) {
        if (denominator_ == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }
    
    // Equality operator
    bool operator==(const Fraction& other) const {
        return numerator_ * other.denominator_ == other.numerator_ * denominator_;
    }
    
    // Inequality operator
    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
    
    // Less than operator
    bool operator<(const Fraction& other) const {
        return numerator_ * other.denominator_ < other.numerator_ * denominator_;
    }
    
    // Greater than operator
    bool operator>(const Fraction& other) const {
        return other < *this;
    }
    
    // Less than or equal operator
    bool operator<=(const Fraction& other) const {
        return !(other < *this);
    }
    
    // Greater than or equal operator
    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
    
    // Display
    void display() const {
        std::cout << numerator_ << "/" << denominator_ << std::endl;
    }
};
```

### 4. Function Call and Subscript Operators

#### Function Call Operator
```cpp
class FunctionObject {
private:
    double multiplier_;
    
public:
    FunctionObject(double mult = 1.0) : multiplier_(mult) {}
    
    // Function call operator
    double operator()(double x) const {
        return x * multiplier_;
    }
    
    // Function call operator with multiple parameters
    double operator()(double x, double y) const {
        return (x + y) * multiplier_;
    }
    
    // Function call operator for arrays
    void operator()(double* array, size_t size) const {
        for (size_t i = 0; i < size; ++i) {
            array[i] *= multiplier_;
        }
    }
};

// Usage examples
void demonstrateFunctionCallOperator() {
    FunctionObject doubler(2.0);
    FunctionObject tripler(3.0);
    
    double result1 = doubler(5.0);        // 10.0
    double result2 = tripler(4.0, 6.0);   // 30.0
    
    double array[] = {1.0, 2.0, 3.0, 4.0};
    doubler(array, 4);  // array becomes [2.0, 4.0, 6.0, 8.0]
}
```

#### Subscript Operator
```cpp
class SafeArray {
private:
    double* data_;
    size_t size_;
    
public:
    SafeArray(size_t size) : size_(size) {
        data_ = new double[size_];
        std::fill(data_, data_ + size_, 0.0);
    }
    
    ~SafeArray() {
        delete[] data_;
    }
    
    // Subscript operator (non-const version)
    double& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    // Subscript operator (const version)
    const double& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const { return size_; }
};
```

---

## Demonstration (25 minutes)

### Operator Overloading Examples
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<double>> data_;
    size_t rows_;
    size_t cols_;
    
public:
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data_.resize(rows_, std::vector<double>(cols_, 0.0));
    }
    
    // Subscript operator for matrix access
    std::vector<double>& operator[](size_t row) {
        return data_[row];
    }
    
    const std::vector<double>& operator[](size_t row) const {
        return data_[row];
    }
    
    // Addition operator
    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }
    
    // Scalar multiplication
    Matrix operator*(double scalar) const {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result[i][j] = data_[i][j] * scalar;
            }
        }
        return result;
    }
    
    // Equality operator
    bool operator==(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            return false;
        }
        
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                if (data_[i][j] != other.data_[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    // Display matrix
    void display() const {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

void demonstrateOperatorOverloading() {
    std::cout << "=== Operator Overloading Demonstration ===" << std::endl;
    
    Matrix m1(2, 3);
    m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
    m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
    
    Matrix m2(2, 3);
    m2[0][0] = 7; m2[0][1] = 8; m2[0][2] = 9;
    m2[1][0] = 10; m2[1][1] = 11; m2[1][2] = 12;
    
    std::cout << "Matrix 1:" << std::endl;
    m1.display();
    
    std::cout << "\nMatrix 2:" << std::endl;
    m2.display();
    
    std::cout << "\nMatrix 1 + Matrix 2:" << std::endl;
    Matrix m3 = m1 + m2;
    m3.display();
    
    std::cout << "\nMatrix 1 * 2.5:" << std::endl;
    Matrix m4 = m1 * 2.5;
    m4.display();
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Arithmetic Operator Overloading
Implement arithmetic operators:

**Tasks:**
1. Create a class with arithmetic operators
2. Implement compound assignment operators
3. Handle operator precedence and associativity
4. Test with various data types

### Activity 2: Comparison Operator Overloading
Implement comparison operators:

**Tasks:**
1. Create a class with comparison operators
2. Implement logical operators
3. Handle edge cases and error conditions
4. Test comparison functionality

### Activity 3: Special Operators
Implement special operators:

**Tasks:**
1. Create function call operator for custom behavior
2. Implement subscript operator for array-like access
3. Design type conversion operators
4. Apply operator overloading best practices

---

## Key Concepts

### 1. Operator Precedence and Associativity
```cpp
class CustomNumber {
private:
    double value_;
    
public:
    CustomNumber(double val = 0.0) : value_(val) {}
    
    // Operators must respect precedence and associativity
    CustomNumber operator+(const CustomNumber& other) const {
        return CustomNumber(value_ + other.value_);
    }
    
    CustomNumber operator*(const CustomNumber& other) const {
        return CustomNumber(value_ * other.value_);
    }
    
    // Left-to-right associativity for addition
    // Higher precedence for multiplication
    // a + b * c should be evaluated as a + (b * c)
};
```

### 2. Type Conversion Operators
```cpp
class SmartString {
private:
    std::string data_;
    
public:
    SmartString(const std::string& str) : data_(str) {}
    
    // Conversion to std::string
    operator std::string() const {
        return data_;
    }
    
    // Conversion to const char*
    operator const char*() const {
        return data_.c_str();
    }
    
    // Conversion to bool (for truthiness)
    operator bool() const {
        return !data_.empty();
    }
    
    // Explicit conversion to int
    explicit operator int() const {
        try {
            return std::stoi(data_);
        } catch (...) {
            return 0;
        }
    }
};
```

### 3. Operator Overloading Best Practices
```cpp
class BestPracticeExample {
private:
    double value_;
    
public:
    BestPracticeExample(double val = 0.0) : value_(val) {}
    
    // 1. Use const member functions when possible
    double getValue() const { return value_; }
    
    // 2. Return references for assignment operators
    BestPracticeExample& operator+=(const BestPracticeExample& other) {
        value_ += other.value_;
        return *this;
    }
    
    // 3. Return values for arithmetic operators
    BestPracticeExample operator+(const BestPracticeExample& other) const {
        return BestPracticeExample(value_ + other.value_);
    }
    
    // 4. Implement related operators in terms of each other
    BestPracticeExample& operator-=(const BestPracticeExample& other) {
        return *this += (-other);
    }
    
    BestPracticeExample operator-() const {
        return BestPracticeExample(-value_);
    }
    
    // 5. Use friend functions for symmetric operators
    friend BestPracticeExample operator+(double lhs, const BestPracticeExample& rhs) {
        return BestPracticeExample(lhs) + rhs;
    }
};
```

---

## Best Practices

### 1. Operator Design
- Maintain operator precedence and associativity
- Use const member functions when appropriate
- Return appropriate types (references vs values)
- Implement related operators in terms of each other

### 2. Symmetric Operators
- Use friend functions for symmetric operators
- Allow mixed-type operations when sensible
- Provide both member and non-member versions
- Maintain consistency with built-in operators

### 3. Type Conversion
- Use explicit conversion operators when appropriate
- Avoid ambiguous conversions
- Provide meaningful conversion semantics
- Consider performance implications

---

## Common Pitfalls

### 1. Incorrect Return Types
```cpp
// Wrong: returning value instead of reference
class BadAssignment {
public:
    BadAssignment operator+=(const BadAssignment& other) {
        // ... implementation
        return *this;  // Should return reference
    }
};

// Correct: returning reference
class GoodAssignment {
public:
    GoodAssignment& operator+=(const GoodAssignment& other) {
        // ... implementation
        return *this;  // Returns reference
    }
};
```

### 2. Missing Const Correctness
```cpp
// Wrong: non-const member function
class BadConst {
public:
    bool operator==(const BadConst& other) {  // Should be const
        return value_ == other.value_;
    }
};

// Correct: const member function
class GoodConst {
public:
    bool operator==(const GoodConst& other) const {  // Const
        return value_ == other.value_;
    }
};
```

### 3. Inconsistent Operator Behavior
```cpp
// Wrong: inconsistent behavior
class Inconsistent {
public:
    bool operator==(const Inconsistent& other) const {
        return value_ == other.value_;
    }
    
    bool operator!=(const Inconsistent& other) const {
        return value_ != other.value_;  // Should use !(*this == other)
    }
};

// Correct: consistent behavior
class Consistent {
public:
    bool operator==(const Consistent& other) const {
        return value_ == other.value_;
    }
    
    bool operator!=(const Consistent& other) const {
        return !(*this == other);  // Consistent with ==
    }
};
```

---

## Assessment

### Quiz Questions
1. What is the difference between member and non-member operator overloading?
2. When should you return a reference vs a value from an operator?
3. What are the benefits of using const member functions?
4. How do you implement symmetric operators?

### Practical Assessment
- Implement arithmetic and assignment operators correctly
- Create comparison operators with proper semantics
- Design function call and subscript operators
- Apply operator overloading best practices

---

## Homework Assignment

### Task 1: Custom Number Class
Implement:
1. A custom number class with arithmetic operators
2. Comparison operators for ordering
3. Type conversion operators
4. Assignment operators

### Task 2: Container Class
Create:
1. A container class with subscript operator
2. Function call operator for operations
3. Iterator support
4. Memory management

### Task 3: Mathematical Vector
Design:
1. A mathematical vector class
2. Vector arithmetic operations
3. Scalar operations
4. Comparison and utility operators

---

## Next Lesson Preview

In the next lesson, we'll learn about inheritance:
- Base and derived classes
- Virtual functions and polymorphism
- Abstract classes and interfaces
- Multiple inheritance and virtual inheritance

Make sure you understand operator overloading before moving on!
