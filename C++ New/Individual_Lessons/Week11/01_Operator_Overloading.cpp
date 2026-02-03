/*
 * Lesson 11.1: Operator Overloading
 * 
 * This file demonstrates arithmetic and assignment operator overloading,
 * comparison and logical operators, function call and subscript operators,
 * and type conversion operators.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <sstream>

// Example 1: Complex Number Class with Arithmetic Operators
class Complex {
private:
    double real_;
    double imaginary_;
    
public:
    Complex(double real = 0.0, double imaginary = 0.0)
        : real_(real), imaginary_(imaginary) {}
    
    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imaginary_ + other.imaginary_);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imaginary_ - other.imaginary_);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(
            real_ * other.real_ - imaginary_ * other.imaginary_,
            real_ * other.imaginary_ + imaginary_ * other.real_
        );
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real_ * other.real_ + other.imaginary_ * other.imaginary_;
        if (denominator == 0) {
            throw std::invalid_argument("Division by zero complex number");
        }
        return Complex(
            (real_ * other.real_ + imaginary_ * other.imaginary_) / denominator,
            (imaginary_ * other.real_ - real_ * other.imaginary_) / denominator
        );
    }
    
    // Unary operators
    Complex operator-() const {
        return Complex(-real_, -imaginary_);
    }
    
    Complex operator+() const {
        return *this;
    }
    
    // Assignment operators
    Complex& operator+=(const Complex& other) {
        real_ += other.real_;
        imaginary_ += other.imaginary_;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real_ -= other.real_;
        imaginary_ -= other.imaginary_;
        return *this;
    }
    
    Complex& operator*=(const Complex& other) {
        double new_real = real_ * other.real_ - imaginary_ * other.imaginary_;
        double new_imaginary = real_ * other.imaginary_ + imaginary_ * other.real_;
        real_ = new_real;
        imaginary_ = new_imaginary;
        return *this;
    }
    
    Complex& operator/=(const Complex& other) {
        return *this = *this / other;
    }
    
    // Comparison operators
    bool operator==(const Complex& other) const {
        return real_ == other.real_ && imaginary_ == other.imaginary_;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Type conversion operators
    explicit operator double() const {
        return std::sqrt(real_ * real_ + imaginary_ * imaginary_);
    }
    
    explicit operator bool() const {
        return real_ != 0.0 || imaginary_ != 0.0;
    }
    
    // Getters
    double getReal() const { return real_; }
    double getImaginary() const { return imaginary_; }
    
    // Display
    void display() const {
        if (imaginary_ >= 0) {
            std::cout << real_ << " + " << imaginary_ << "i";
        } else {
            std::cout << real_ << " - " << std::abs(imaginary_) << "i";
        }
    }
    
    // Friend functions for symmetric operators
    friend Complex operator*(double scalar, const Complex& complex) {
        return Complex(scalar * complex.real_, scalar * complex.imaginary_);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& complex) {
        complex.display();
        return os;
    }
};

// Example 2: Vector Class with Assignment Operators
class Vector {
private:
    double* data_;
    size_t size_;
    
public:
    Vector(size_t size) : size_(size) {
        data_ = new double[size_];
        std::fill(data_, data_ + size_, 0.0);
    }
    
    Vector(const Vector& other) : size_(other.size_) {
        data_ = new double[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    ~Vector() {
        delete[] data_;
    }
    
    // Assignment operators
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new double[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
    
    Vector& operator+=(const Vector& other) {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vector sizes must match for addition");
        }
        for (size_t i = 0; i < size_; ++i) {
            data_[i] += other.data_[i];
        }
        return *this;
    }
    
    Vector& operator-=(const Vector& other) {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vector sizes must match for subtraction");
        }
        for (size_t i = 0; i < size_; ++i) {
            data_[i] -= other.data_[i];
        }
        return *this;
    }
    
    Vector& operator*=(double scalar) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] *= scalar;
        }
        return *this;
    }
    
    Vector& operator/=(double scalar) {
        if (scalar == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        for (size_t i = 0; i < size_; ++i) {
            data_[i] /= scalar;
        }
        return *this;
    }
    
    // Arithmetic operators
    Vector operator+(const Vector& other) const {
        Vector result = *this;
        return result += other;
    }
    
    Vector operator-(const Vector& other) const {
        Vector result = *this;
        return result -= other;
    }
    
    Vector operator*(double scalar) const {
        Vector result = *this;
        return result *= scalar;
    }
    
    Vector operator/(double scalar) const {
        Vector result = *this;
        return result /= scalar;
    }
    
    // Subscript operator
    double& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const double& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    // Comparison operators
    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }
    
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    
    // Utility methods
    size_t size() const { return size_; }
    
    double magnitude() const {
        double sum = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            sum += data_[i] * data_[i];
        }
        return std::sqrt(sum);
    }
    
    void display() const {
        std::cout << "[";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
    
    // Friend functions
    friend Vector operator*(double scalar, const Vector& vec) {
        return vec * scalar;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        vec.display();
        return os;
    }
};

// Example 3: Fraction Class with Comparison Operators
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
        
        // Ensure denominator is positive
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }
    
public:
    Fraction(int num = 0, int denom = 1) : numerator_(num), denominator_(denom) {
        if (denominator_ == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }
    
    // Arithmetic operators
    Fraction operator+(const Fraction& other) const {
        int new_num = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        int new_denom = denominator_ * other.denominator_;
        return Fraction(new_num, new_denom);
    }
    
    Fraction operator-(const Fraction& other) const {
        int new_num = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        int new_denom = denominator_ * other.denominator_;
        return Fraction(new_num, new_denom);
    }
    
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
    }
    
    Fraction operator/(const Fraction& other) const {
        if (other.numerator_ == 0) {
            throw std::invalid_argument("Division by zero fraction");
        }
        return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
    }
    
    // Unary operators
    Fraction operator-() const {
        return Fraction(-numerator_, denominator_);
    }
    
    Fraction operator+() const {
        return *this;
    }
    
    // Assignment operators
    Fraction& operator+=(const Fraction& other) {
        return *this = *this + other;
    }
    
    Fraction& operator-=(const Fraction& other) {
        return *this = *this - other;
    }
    
    Fraction& operator*=(const Fraction& other) {
        return *this = *this * other;
    }
    
    Fraction& operator/=(const Fraction& other) {
        return *this = *this / other;
    }
    
    // Comparison operators
    bool operator==(const Fraction& other) const {
        return numerator_ * other.denominator_ == other.numerator_ * denominator_;
    }
    
    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Fraction& other) const {
        return numerator_ * other.denominator_ < other.numerator_ * denominator_;
    }
    
    bool operator>(const Fraction& other) const {
        return other < *this;
    }
    
    bool operator<=(const Fraction& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
    
    // Type conversion operators
    explicit operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }
    
    explicit operator int() const {
        return numerator_ / denominator_;
    }
    
    explicit operator bool() const {
        return numerator_ != 0;
    }
    
    // Getters
    int getNumerator() const { return numerator_; }
    int getDenominator() const { return denominator_; }
    
    // Display
    void display() const {
        std::cout << numerator_ << "/" << denominator_;
    }
    
    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        frac.display();
        return os;
    }
};

// Example 4: Function Call Operator
class FunctionObject {
private:
    double multiplier_;
    std::string name_;
    
public:
    FunctionObject(double mult = 1.0, const std::string& name = "Function")
        : multiplier_(mult), name_(name) {}
    
    // Function call operator with single parameter
    double operator()(double x) const {
        std::cout << name_ << "(" << x << ") = ";
        return x * multiplier_;
    }
    
    // Function call operator with multiple parameters
    double operator()(double x, double y) const {
        std::cout << name_ << "(" << x << ", " << y << ") = ";
        return (x + y) * multiplier_;
    }
    
    // Function call operator for arrays
    void operator()(double* array, size_t size) const {
        std::cout << name_ << " applied to array of size " << size << std::endl;
        for (size_t i = 0; i < size; ++i) {
            array[i] *= multiplier_;
        }
    }
    
    // Function call operator for vectors
    void operator()(std::vector<double>& vec) const {
        std::cout << name_ << " applied to vector of size " << vec.size() << std::endl;
        for (double& value : vec) {
            value *= multiplier_;
        }
    }
    
    const std::string& getName() const { return name_; }
};

// Example 5: Safe Array with Subscript Operator
class SafeArray {
private:
    double* data_;
    size_t size_;
    std::string name_;
    
public:
    SafeArray(size_t size, const std::string& name = "SafeArray")
        : size_(size), name_(name) {
        data_ = new double[size_];
        std::fill(data_, data_ + size_, 0.0);
    }
    
    SafeArray(const SafeArray& other) : size_(other.size_), name_(other.name_ + "_Copy") {
        data_ = new double[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    ~SafeArray() {
        delete[] data_;
    }
    
    SafeArray& operator=(const SafeArray& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            name_ = other.name_ + "_Assigned";
            data_ = new double[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
    
    // Subscript operator (non-const version)
    double& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                   " out of range for array of size " + std::to_string(size_));
        }
        return data_[index];
    }
    
    // Subscript operator (const version)
    const double& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                   " out of range for array of size " + std::to_string(size_));
        }
        return data_[index];
    }
    
    // Arithmetic operators
    SafeArray& operator+=(const SafeArray& other) {
        if (size_ != other.size_) {
            throw std::invalid_argument("Array sizes must match for addition");
        }
        for (size_t i = 0; i < size_; ++i) {
            data_[i] += other.data_[i];
        }
        return *this;
    }
    
    SafeArray operator+(const SafeArray& other) const {
        SafeArray result = *this;
        return result += other;
    }
    
    SafeArray& operator*=(double scalar) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] *= scalar;
        }
        return *this;
    }
    
    SafeArray operator*(double scalar) const {
        SafeArray result = *this;
        return result *= scalar;
    }
    
    // Comparison operators
    bool operator==(const SafeArray& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }
    
    bool operator!=(const SafeArray& other) const {
        return !(*this == other);
    }
    
    // Utility methods
    size_t size() const { return size_; }
    const std::string& getName() const { return name_; }
    
    void fill(double value) {
        std::fill(data_, data_ + size_, value);
    }
    
    double sum() const {
        double total = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            total += data_[i];
        }
        return total;
    }
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
    
    // Friend functions
    friend SafeArray operator*(double scalar, const SafeArray& arr) {
        return arr * scalar;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const SafeArray& arr) {
        arr.display();
        return os;
    }
};

// Function to demonstrate complex number operations
void demonstrateComplexNumbers() {
    std::cout << "=== Complex Number Operations ===" << std::endl;
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    
    std::cout << "\nArithmetic operations:" << std::endl;
    std::cout << "c1 + c2 = " << (c1 + c2) << std::endl;
    std::cout << "c1 - c2 = " << (c1 - c2) << std::endl;
    std::cout << "c1 * c2 = " << (c1 * c2) << std::endl;
    std::cout << "c1 / c2 = " << (c1 / c2) << std::endl;
    
    std::cout << "\nUnary operations:" << std::endl;
    std::cout << "-c1 = " << (-c1) << std::endl;
    std::cout << "+c2 = " << (+c2) << std::endl;
    
    std::cout << "\nAssignment operations:" << std::endl;
    Complex c3 = c1;
    std::cout << "c3 = c1: " << c3 << std::endl;
    c3 += c2;
    std::cout << "c3 += c2: " << c3 << std::endl;
    c3 *= c2;
    std::cout << "c3 *= c2: " << c3 << std::endl;
    
    std::cout << "\nComparison operations:" << std::endl;
    std::cout << "c1 == c2: " << (c1 == c2 ? "true" : "false") << std::endl;
    std::cout << "c1 != c2: " << (c1 != c2 ? "true" : "false") << std::endl;
    
    std::cout << "\nType conversions:" << std::endl;
    std::cout << "Magnitude of c1: " << static_cast<double>(c1) << std::endl;
    std::cout << "c1 as bool: " << (static_cast<bool>(c1) ? "true" : "false") << std::endl;
    
    std::cout << "\nScalar multiplication:" << std::endl;
    std::cout << "2.5 * c1 = " << (2.5 * c1) << std::endl;
}

// Function to demonstrate vector operations
void demonstrateVectorOperations() {
    std::cout << "\n=== Vector Operations ===" << std::endl;
    
    Vector v1(3);
    Vector v2(3);
    
    // Initialize vectors
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    
    std::cout << "\nArithmetic operations:" << std::endl;
    std::cout << "v1 + v2 = " << (v1 + v2) << std::endl;
    std::cout << "v1 - v2 = " << (v1 - v2) << std::endl;
    std::cout << "v1 * 2.5 = " << (v1 * 2.5) << std::endl;
    std::cout << "3.0 * v2 = " << (3.0 * v2) << std::endl;
    
    std::cout << "\nAssignment operations:" << std::endl;
    Vector v3 = v1;
    std::cout << "v3 = v1: " << v3 << std::endl;
    v3 += v2;
    std::cout << "v3 += v2: " << v3 << std::endl;
    v3 *= 0.5;
    std::cout << "v3 *= 0.5: " << v3 << std::endl;
    
    std::cout << "\nComparison operations:" << std::endl;
    std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
    std::cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << std::endl;
    
    std::cout << "\nVector properties:" << std::endl;
    std::cout << "Magnitude of v1: " << v1.magnitude() << std::endl;
    std::cout << "Magnitude of v2: " << v2.magnitude() << std::endl;
}

// Function to demonstrate fraction operations
void demonstrateFractionOperations() {
    std::cout << "\n=== Fraction Operations ===" << std::endl;
    
    Fraction f1(3, 4);
    Fraction f2(2, 5);
    
    std::cout << "f1 = " << f1 << std::endl;
    std::cout << "f2 = " << f2 << std::endl;
    
    std::cout << "\nArithmetic operations:" << std::endl;
    std::cout << "f1 + f2 = " << (f1 + f2) << std::endl;
    std::cout << "f1 - f2 = " << (f1 - f2) << std::endl;
    std::cout << "f1 * f2 = " << (f1 * f2) << std::endl;
    std::cout << "f1 / f2 = " << (f1 / f2) << std::endl;
    
    std::cout << "\nComparison operations:" << std::endl;
    std::cout << "f1 == f2: " << (f1 == f2 ? "true" : "false") << std::endl;
    std::cout << "f1 != f2: " << (f1 != f2 ? "true" : "false") << std::endl;
    std::cout << "f1 < f2: " << (f1 < f2 ? "true" : "false") << std::endl;
    std::cout << "f1 > f2: " << (f1 > f2 ? "true" : "false") << std::endl;
    std::cout << "f1 <= f2: " << (f1 <= f2 ? "true" : "false") << std::endl;
    std::cout << "f1 >= f2: " << (f1 >= f2 ? "true" : "false") << std::endl;
    
    std::cout << "\nType conversions:" << std::endl;
    std::cout << "f1 as double: " << static_cast<double>(f1) << std::endl;
    std::cout << "f2 as double: " << static_cast<double>(f2) << std::endl;
    std::cout << "f1 as int: " << static_cast<int>(f1) << std::endl;
    std::cout << "f1 as bool: " << (static_cast<bool>(f1) ? "true" : "false") << std::endl;
}

// Function to demonstrate function call operator
void demonstrateFunctionCallOperator() {
    std::cout << "\n=== Function Call Operator ===" << std::endl;
    
    FunctionObject doubler(2.0, "Doubler");
    FunctionObject tripler(3.0, "Tripler");
    FunctionObject adder(1.0, "Adder");
    
    std::cout << "Single parameter function calls:" << std::endl;
    std::cout << doubler(5.0) << std::endl;
    std::cout << tripler(4.0) << std::endl;
    std::cout << adder(7.0) << std::endl;
    
    std::cout << "\nMultiple parameter function calls:" << std::endl;
    std::cout << doubler(3.0, 4.0) << std::endl;
    std::cout << tripler(2.0, 1.0) << std::endl;
    
    std::cout << "\nFunction call with arrays:" << std::endl;
    double array[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::cout << "Original array: [1.0, 2.0, 3.0, 4.0, 5.0]" << std::endl;
    doubler(array, 5);
    std::cout << "After doubler: [";
    for (int i = 0; i < 5; ++i) {
        std::cout << array[i];
        if (i < 4) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    
    std::cout << "\nFunction call with vectors:" << std::endl;
    std::vector<double> vec = {10.0, 20.0, 30.0};
    std::cout << "Original vector: [10.0, 20.0, 30.0]" << std::endl;
    tripler(vec);
    std::cout << "After tripler: [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Function to demonstrate subscript operator
void demonstrateSubscriptOperator() {
    std::cout << "\n=== Subscript Operator ===" << std::endl;
    
    SafeArray arr1(5, "Array1");
    SafeArray arr2(5, "Array2");
    
    // Initialize arrays
    for (size_t i = 0; i < 5; ++i) {
        arr1[i] = i + 1;
        arr2[i] = (i + 1) * 2;
    }
    
    std::cout << arr1 << std::endl;
    std::cout << arr2 << std::endl;
    
    std::cout << "\nAccessing elements:" << std::endl;
    for (size_t i = 0; i < arr1.size(); ++i) {
        std::cout << "arr1[" << i << "] = " << arr1[i] << std::endl;
    }
    
    std::cout << "\nModifying elements:" << std::endl;
    arr1[0] = 100;
    arr1[4] = 200;
    std::cout << "After modification: " << arr1 << std::endl;
    
    std::cout << "\nArithmetic operations:" << std::endl;
    std::cout << "arr1 + arr2 = " << (arr1 + arr2) << std::endl;
    std::cout << "arr1 * 2.5 = " << (arr1 * 2.5) << std::endl;
    std::cout << "3.0 * arr2 = " << (3.0 * arr2) << std::endl;
    
    std::cout << "\nArray properties:" << std::endl;
    std::cout << "arr1 sum: " << arr1.sum() << std::endl;
    std::cout << "arr2 sum: " << arr2.sum() << std::endl;
    
    std::cout << "\nComparison operations:" << std::endl;
    std::cout << "arr1 == arr2: " << (arr1 == arr2 ? "true" : "false") << std::endl;
    
    // Test bounds checking
    std::cout << "\nBounds checking:" << std::endl;
    try {
        std::cout << "arr1[10] = " << arr1[10] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Function to demonstrate operator overloading best practices
void demonstrateBestPractices() {
    std::cout << "\n=== Operator Overloading Best Practices ===" << std::endl;
    
    std::cout << "1. Maintain operator precedence and associativity" << std::endl;
    std::cout << "2. Use const member functions when appropriate" << std::endl;
    std::cout << "3. Return appropriate types (references vs values)" << std::endl;
    std::cout << "4. Implement related operators in terms of each other" << std::endl;
    std::cout << "5. Use friend functions for symmetric operators" << std::endl;
    std::cout << "6. Provide meaningful error messages" << std::endl;
    std::cout << "7. Handle edge cases and exceptions properly" << std::endl;
    std::cout << "8. Use explicit conversion operators when appropriate" << std::endl;
    std::cout << "9. Follow consistent naming and behavior patterns" << std::endl;
    std::cout << "10. Document operator behavior and semantics" << std::endl;
}

int main() {
    std::cout << "=== Operator Overloading Demonstration ===" << std::endl;
    std::cout << "This program demonstrates arithmetic and assignment operator overloading,\n"
              << "comparison and logical operators, function call and subscript operators,\n"
              << "and type conversion operators.\n" << std::endl;
    
    // Demonstrate various operator overloading concepts
    demonstrateComplexNumbers();
    demonstrateVectorOperations();
    demonstrateFractionOperations();
    demonstrateFunctionCallOperator();
    demonstrateSubscriptOperator();
    demonstrateBestPractices();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Operator overloading allows custom behavior for operators" << std::endl;
    std::cout << "2. Maintain operator precedence and associativity" << std::endl;
    std::cout << "3. Use const-correctness in operator implementations" << std::endl;
    std::cout << "4. Return appropriate types for different operators" << std::endl;
    std::cout << "5. Implement related operators consistently" << std::endl;
    std::cout << "6. Use friend functions for symmetric operations" << std::endl;
    std::cout << "7. Provide meaningful error handling" << std::endl;
    std::cout << "8. Use explicit conversion operators for clarity" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o operator_overloading 01_Operator_Overloading.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o operator_overloading 01_Operator_Overloading.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Operator_Overloading.cpp
 * 
 * Running:
 * ./operator_overloading (Linux/macOS)
 * operator_overloading.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best operator overloading support.
 * 
 * Operator Overloading Notes:
 * - Maintain operator precedence and associativity
 * - Use const-correctness appropriately
 * - Return references for assignment operators
 * - Return values for arithmetic operators
 * - Implement related operators consistently
 * - Use friend functions for symmetric operators
 * - Handle exceptions and edge cases
 * - Provide meaningful error messages
 * - Use explicit conversion operators when appropriate
 */"""
