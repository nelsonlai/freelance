#include <iostream>
#include <cmath>
#include <string>

// Complex number class demonstrating operator overloading
class Complex {
private:
    double real;
    double imaginary;
    
public:
    // Constructors
    Complex(double real = 0.0, double imaginary = 0.0) 
        : real(real), imaginary(imaginary) {}
    
    // Copy constructor
    Complex(const Complex& other) : real(other.real), imaginary(other.imaginary) {}
    
    // Getters
    double get_real() const { return real; }
    double get_imaginary() const { return imaginary; }
    
    // Setters
    void set_real(double real) { this->real = real; }
    void set_imaginary(double imaginary) { this->imaginary = imaginary; }
    
    // Member functions
    double magnitude() const {
        return std::sqrt(real * real + imaginary * imaginary);
    }
    
    double phase() const {
        return std::atan2(imaginary, real);
    }
    
    Complex conjugate() const {
        return Complex(real, -imaginary);
    }
    
    std::string to_string() const {
        std::string result = std::to_string(real);
        if (imaginary >= 0) {
            result += " + " + std::to_string(imaginary) + "i";
        } else {
            result += " - " + std::to_string(-imaginary) + "i";
        }
        return result;
    }
    
    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    Complex operator*(const Complex& other) const {
        double new_real = real * other.real - imaginary * other.imaginary;
        double new_imaginary = real * other.imaginary + imaginary * other.real;
        return Complex(new_real, new_imaginary);
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        if (denominator == 0) {
            throw std::runtime_error("Division by zero");
        }
        
        double new_real = (real * other.real + imaginary * other.imaginary) / denominator;
        double new_imaginary = (imaginary * other.real - real * other.imaginary) / denominator;
        return Complex(new_real, new_imaginary);
    }
    
    // Assignment operators
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imaginary = other.imaginary;
        }
        return *this;
    }
    
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imaginary += other.imaginary;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imaginary -= other.imaginary;
        return *this;
    }
    
    Complex& operator*=(const Complex& other) {
        double new_real = real * other.real - imaginary * other.imaginary;
        double new_imaginary = real * other.imaginary + imaginary * other.real;
        real = new_real;
        imaginary = new_imaginary;
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Complex& other) const {
        const double epsilon = 1e-9;
        return std::abs(real - other.real) < epsilon && 
               std::abs(imaginary - other.imaginary) < epsilon;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Unary operators
    Complex operator-() const {
        return Complex(-real, -imaginary);
    }
    
    Complex operator+() const {
        return *this;
    }
    
    // Increment and decrement operators
    Complex& operator++() {  // Pre-increment
        real += 1.0;
        return *this;
    }
    
    Complex operator++(int) {  // Post-increment
        Complex temp = *this;
        real += 1.0;
        return temp;
    }
    
    Complex& operator--() {  // Pre-decrement
        real -= 1.0;
        return *this;
    }
    
    Complex operator--(int) {  // Post-decrement
        Complex temp = *this;
        real -= 1.0;
        return temp;
    }
    
    // Friend function for stream output
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

// Friend function implementation
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.to_string();
    return os;
}

int main() {
    std::cout << "Complex Number Class with Operator Overloading" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // 1. Creating complex numbers
    std::cout << "\n1. CREATING COMPLEX NUMBERS:" << std::endl;
    
    Complex c1(3.0, 4.0);  // 3 + 4i
    Complex c2(1.0, 2.0);  // 1 + 2i
    Complex c3(5.0, -2.0); // 5 - 2i
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c3 = " << c3 << std::endl;
    
    // 2. Basic arithmetic operations
    std::cout << "\n2. ARITHMETIC OPERATIONS:" << std::endl;
    
    Complex sum = c1 + c2;
    std::cout << "c1 + c2 = " << sum << std::endl;
    
    Complex difference = c1 - c2;
    std::cout << "c1 - c2 = " << difference << std::endl;
    
    Complex product = c1 * c2;
    std::cout << "c1 * c2 = " << product << std::endl;
    
    Complex quotient = c1 / c2;
    std::cout << "c1 / c2 = " << quotient << std::endl;
    
    // 3. Assignment operators
    std::cout << "\n3. ASSIGNMENT OPERATORS:" << std::endl;
    
    Complex c4 = c1;
    std::cout << "c4 = c1: " << c4 << std::endl;
    
    c4 += c2;
    std::cout << "c4 += c2: " << c4 << std::endl;
    
    c4 -= c2;
    std::cout << "c4 -= c2: " << c4 << std::endl;
    
    c4 *= c2;
    std::cout << "c4 *= c2: " << c4 << std::endl;
    
    // 4. Comparison operators
    std::cout << "\n4. COMPARISON OPERATORS:" << std::endl;
    
    Complex c5(3.0, 4.0);
    std::cout << "c1 == c5: " << std::boolalpha << (c1 == c5) << std::endl;
    std::cout << "c1 != c2: " << std::boolalpha << (c1 != c2) << std::endl;
    
    // 5. Unary operators
    std::cout << "\n5. UNARY OPERATORS:" << std::endl;
    
    std::cout << "-c1 = " << (-c1) << std::endl;
    std::cout << "+c1 = " << (+c1) << std::endl;
    
    // 6. Increment and decrement operators
    std::cout << "\n6. INCREMENT/DECREMENT OPERATORS:" << std::endl;
    
    Complex c6(5.0, 3.0);
    std::cout << "Original c6: " << c6 << std::endl;
    
    std::cout << "++c6: " << (++c6) << std::endl;
    std::cout << "c6 after pre-increment: " << c6 << std::endl;
    
    std::cout << "c6++: " << (c6++) << std::endl;
    std::cout << "c6 after post-increment: " << c6 << std::endl;
    
    // 7. Mathematical properties
    std::cout << "\n7. MATHEMATICAL PROPERTIES:" << std::endl;
    
    std::cout << "c1 magnitude: " << c1.magnitude() << std::endl;
    std::cout << "c1 phase: " << c1.phase() << " radians" << std::endl;
    std::cout << "c1 conjugate: " << c1.conjugate() << std::endl;
    
    // 8. Error handling
    std::cout << "\n8. ERROR HANDLING:" << std::endl;
    
    Complex zero(0.0, 0.0);
    try {
        Complex result = c1 / zero;
    } catch (const std::runtime_error& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
    
    // 9. Chaining operations
    std::cout << "\n9. OPERATION CHAINING:" << std::endl;
    
    Complex result = (c1 + c2) * c3;
    std::cout << "(c1 + c2) * c3 = " << result << std::endl;
    
    // 10. Using with standard algorithms (if we had a container)
    std::cout << "\n10. COMPLEX NUMBER PROPERTIES:" << std::endl;
    
    std::cout << "Real part of c1: " << c1.get_real() << std::endl;
    std::cout << "Imaginary part of c1: " << c1.get_imaginary() << std::endl;
    
    return 0;
}
