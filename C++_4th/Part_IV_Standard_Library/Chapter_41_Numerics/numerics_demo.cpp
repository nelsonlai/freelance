#include <iostream>
#include <random>
#include <complex>
#include <numeric>
#include <vector>
#include <cmath>
#include <iomanip>

// Demonstrates numerics library features
int main() {
    std::cout << "Numerics Demonstration" << std::endl;
    std::cout << "======================" << std::endl;
    
    // 1. Random Number Generation
    std::cout << "\n1. RANDOM NUMBER GENERATION:" << std::endl;
    
    // Random number engines
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> int_dist(1, 100);
    std::uniform_real_distribution<> real_dist(0.0, 1.0);
    
    std::cout << "  Random integers (1-100): ";
    for (int i = 0; i < 5; ++i) {
        std::cout << int_dist(gen) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "  Random reals (0-1): ";
    for (int i = 0; i < 5; ++i) {
        std::cout << std::fixed << std::setprecision(3) << real_dist(gen) << " ";
    }
    std::cout << std::endl;
    
    // Different distributions
    std::normal_distribution<> normal_dist(0.0, 1.0);
    std::exponential_distribution<> exp_dist(1.0);
    std::poisson_distribution<> poisson_dist(5.0);
    
    std::cout << "  Normal distribution: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << std::fixed << std::setprecision(2) << normal_dist(gen) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "  Exponential distribution: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << std::fixed << std::setprecision(2) << exp_dist(gen) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "  Poisson distribution: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << poisson_dist(gen) << " ";
    }
    std::cout << std::endl;
    
    // 2. Complex Numbers
    std::cout << "\n2. COMPLEX NUMBERS:" << std::endl;
    
    std::complex<double> c1(3.0, 4.0);
    std::complex<double> c2(1.0, 2.0);
    
    std::cout << "  c1 = " << c1 << std::endl;
    std::cout << "  c2 = " << c2 << std::endl;
    std::cout << "  c1 + c2 = " << (c1 + c2) << std::endl;
    std::cout << "  c1 - c2 = " << (c1 - c2) << std::endl;
    std::cout << "  c1 * c2 = " << (c1 * c2) << std::endl;
    std::cout << "  c1 / c2 = " << (c1 / c2) << std::endl;
    
    std::cout << "  |c1| = " << std::abs(c1) << std::endl;
    std::cout << "  arg(c1) = " << std::arg(c1) << std::endl;
    std::cout << "  conj(c1) = " << std::conj(c1) << std::endl;
    std::cout << "  real(c1) = " << c1.real() << std::endl;
    std::cout << "  imag(c1) = " << c1.imag() << std::endl;
    
    // Complex functions
    std::cout << "  exp(c1) = " << std::exp(c1) << std::endl;
    std::cout << "  log(c1) = " << std::log(c1) << std::endl;
    std::cout << "  sqrt(c1) = " << std::sqrt(c1) << std::endl;
    std::cout << "  pow(c1, 2) = " << std::pow(c1, 2) << std::endl;
    
    // 3. Mathematical Constants
    std::cout << "\n3. MATHEMATICAL CONSTANTS:" << std::endl;
    
    std::cout << "  π = " << std::numbers::pi << std::endl;
    std::cout << "  e = " << std::numbers::e << std::endl;
    std::cout << "  √2 = " << std::numbers::sqrt2 << std::endl;
    std::cout << "  √3 = " << std::numbers::sqrt3 << std::endl;
    std::cout << "  ln(2) = " << std::numbers::ln2 << std::endl;
    std::cout << "  ln(10) = " << std::numbers::ln10 << std::endl;
    std::cout << "  φ (golden ratio) = " << std::numbers::phi << std::endl;
    
    // 4. Mathematical Functions
    std::cout << "\n4. MATHEMATICAL FUNCTIONS:" << std::endl;
    
    double x = 2.5;
    std::cout << "  x = " << x << std::endl;
    std::cout << "  sin(x) = " << std::sin(x) << std::endl;
    std::cout << "  cos(x) = " << std::cos(x) << std::endl;
    std::cout << "  tan(x) = " << std::tan(x) << std::endl;
    std::cout << "  asin(0.5) = " << std::asin(0.5) << std::endl;
    std::cout << "  acos(0.5) = " << std::acos(0.5) << std::endl;
    std::cout << "  atan(1) = " << std::atan(1) << std::endl;
    
    std::cout << "  exp(x) = " << std::exp(x) << std::endl;
    std::cout << "  log(x) = " << std::log(x) << std::endl;
    std::cout << "  log10(x) = " << std::log10(x) << std::endl;
    std::cout << "  log2(x) = " << std::log2(x) << std::endl;
    
    std::cout << "  sqrt(x) = " << std::sqrt(x) << std::endl;
    std::cout << "  cbrt(x) = " << std::cbrt(x) << std::endl;
    std::cout << "  pow(x, 2) = " << std::pow(x, 2) << std::endl;
    std::cout << "  pow(x, 0.5) = " << std::pow(x, 0.5) << std::endl;
    
    // 5. Numeric Algorithms
    std::cout << "\n5. NUMERIC ALGORITHMS:" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "  Numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Accumulate
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "  Sum: " << sum << std::endl;
    
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
    std::cout << "  Product: " << product << std::endl;
    
    // Inner product
    std::vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int weighted_sum = std::inner_product(numbers.begin(), numbers.end(), weights.begin(), 0);
    std::cout << "  Weighted sum: " << weighted_sum << std::endl;
    
    // Partial sum
    std::vector<int> partial_sums(numbers.size());
    std::partial_sum(numbers.begin(), numbers.end(), partial_sums.begin());
    std::cout << "  Partial sums: ";
    for (int ps : partial_sums) {
        std::cout << ps << " ";
    }
    std::cout << std::endl;
    
    // Adjacent difference
    std::vector<int> differences(numbers.size());
    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
    std::cout << "  Adjacent differences: ";
    for (int diff : differences) {
        std::cout << diff << " ";
    }
    std::cout << std::endl;
    
    // 6. Statistical Functions
    std::cout << "\n6. STATISTICAL FUNCTIONS:" << std::endl;
    
    std::vector<double> data = {1.5, 2.3, 3.7, 4.1, 5.9, 6.2, 7.8, 8.4, 9.1, 10.5};
    std::cout << "  Data: ";
    for (double d : data) {
        std::cout << std::fixed << std::setprecision(1) << d << " ";
    }
    std::cout << std::endl;
    
    // Mean
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    std::cout << "  Mean: " << std::fixed << std::setprecision(2) << mean << std::endl;
    
    // Variance
    double variance = std::accumulate(data.begin(), data.end(), 0.0, 
        [mean](double acc, double x) { return acc + (x - mean) * (x - mean); }) / data.size();
    std::cout << "  Variance: " << std::fixed << std::setprecision(2) << variance << std::endl;
    
    // Standard deviation
    double std_dev = std::sqrt(variance);
    std::cout << "  Standard deviation: " << std::fixed << std::setprecision(2) << std_dev << std::endl;
    
    // Min and max
    auto minmax = std::minmax_element(data.begin(), data.end());
    std::cout << "  Min: " << std::fixed << std::setprecision(1) << *minmax.first << std::endl;
    std::cout << "  Max: " << std::fixed << std::setprecision(1) << *minmax.second << std::endl;
    
    // 7. Fixed-Point Arithmetic
    std::cout << "\n7. FIXED-POINT ARITHMETIC:" << std::endl;
    
    // Simple fixed-point implementation
    class FixedPoint {
    private:
        int value;
        static const int SCALE = 1000;  // 3 decimal places
        
    public:
        FixedPoint(double d) : value(static_cast<int>(d * SCALE)) {}
        FixedPoint(int v) : value(v) {}
        
        double to_double() const { return static_cast<double>(value) / SCALE; }
        
        FixedPoint operator+(const FixedPoint& other) const {
            return FixedPoint(value + other.value);
        }
        
        FixedPoint operator-(const FixedPoint& other) const {
            return FixedPoint(value - other.value);
        }
        
        FixedPoint operator*(const FixedPoint& other) const {
            return FixedPoint((static_cast<long long>(value) * other.value) / SCALE);
        }
        
        FixedPoint operator/(const FixedPoint& other) const {
            return FixedPoint((static_cast<long long>(value) * SCALE) / other.value);
        }
        
        friend std::ostream& operator<<(std::ostream& os, const FixedPoint& fp) {
            os << fp.to_double();
            return os;
        }
    };
    
    FixedPoint fp1(3.14159);
    FixedPoint fp2(2.71828);
    
    std::cout << "  fp1 = " << fp1 << std::endl;
    std::cout << "  fp2 = " << fp2 << std::endl;
    std::cout << "  fp1 + fp2 = " << (fp1 + fp2) << std::endl;
    std::cout << "  fp1 - fp2 = " << (fp1 - fp2) << std::endl;
    std::cout << "  fp1 * fp2 = " << (fp1 * fp2) << std::endl;
    std::cout << "  fp1 / fp2 = " << (fp1 / fp2) << std::endl;
    
    // 8. Numerical Integration
    std::cout << "\n8. NUMERICAL INTEGRATION:" << std::endl;
    
    // Simple trapezoidal rule
    auto integrate = [](std::function<double(double)> f, double a, double b, int n) -> double {
        double h = (b - a) / n;
        double sum = (f(a) + f(b)) / 2.0;
        
        for (int i = 1; i < n; ++i) {
            sum += f(a + i * h);
        }
        
        return sum * h;
    };
    
    // Integrate x^2 from 0 to 1
    auto f = [](double x) { return x * x; };
    double integral = integrate(f, 0.0, 1.0, 1000);
    std::cout << "  ∫₀¹ x² dx ≈ " << std::fixed << std::setprecision(6) << integral << std::endl;
    std::cout << "  Exact value: " << std::fixed << std::setprecision(6) << 1.0/3.0 << std::endl;
    
    // Integrate sin(x) from 0 to π
    auto g = [](double x) { return std::sin(x); };
    double integral2 = integrate(g, 0.0, std::numbers::pi, 1000);
    std::cout << "  ∫₀^π sin(x) dx ≈ " << std::fixed << std::setprecision(6) << integral2 << std::endl;
    std::cout << "  Exact value: " << std::fixed << std::setprecision(6) << 2.0 << std::endl;
    
    // 9. Root Finding
    std::cout << "\n9. ROOT FINDING:" << std::endl;
    
    // Bisection method
    auto bisection = [](std::function<double(double)> f, double a, double b, double tolerance) -> double {
        while (std::abs(b - a) > tolerance) {
            double c = (a + b) / 2.0;
            if (f(a) * f(c) < 0) {
                b = c;
            } else {
                a = c;
            }
        }
        return (a + b) / 2.0;
    };
    
    // Find root of x² - 2 = 0
    auto h = [](double x) { return x * x - 2.0; };
    double root = bisection(h, 0.0, 2.0, 1e-6);
    std::cout << "  Root of x² - 2 = 0: " << std::fixed << std::setprecision(6) << root << std::endl;
    std::cout << "  √2 ≈ " << std::fixed << std::setprecision(6) << std::sqrt(2.0) << std::endl;
    
    // 10. Matrix Operations
    std::cout << "\n10. MATRIX OPERATIONS:" << std::endl;
    
    // Simple matrix class
    class Matrix {
    private:
        std::vector<std::vector<double>> data;
        size_t rows, cols;
        
    public:
        Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}
        
        double& operator()(size_t r, size_t c) { return data[r][c]; }
        const double& operator()(size_t r, size_t c) const { return data[r][c]; }
        
        Matrix operator+(const Matrix& other) const {
            Matrix result(rows, cols);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    result(i, j) = data[i][j] + other(i, j);
                }
            }
            return result;
        }
        
        Matrix operator*(const Matrix& other) const {
            Matrix result(rows, other.cols);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < other.cols; ++j) {
                    for (size_t k = 0; k < cols; ++k) {
                        result(i, j) += data[i][k] * other(k, j);
                    }
                }
            }
            return result;
        }
        
        void print() const {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    std::cout << std::fixed << std::setprecision(2) << data[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    };
    
    Matrix A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;
    
    Matrix B(2, 2);
    B(0, 0) = 5; B(0, 1) = 6;
    B(1, 0) = 7; B(1, 1) = 8;
    
    std::cout << "  Matrix A:" << std::endl;
    A.print();
    
    std::cout << "  Matrix B:" << std::endl;
    B.print();
    
    Matrix C = A + B;
    std::cout << "  A + B:" << std::endl;
    C.print();
    
    Matrix D = A * B;
    std::cout << "  A * B:" << std::endl;
    D.print();
    
    // 11. Special Functions
    std::cout << "\n11. SPECIAL FUNCTIONS:" << std::endl;
    
    double special_x = 2.5;
    std::cout << "  x = " << special_x << std::endl;
    
    // Gamma function approximation
    auto gamma_approx = [](double x) -> double {
        if (x < 0.5) {
            return std::numbers::pi / (std::sin(std::numbers::pi * x) * gamma_approx(1.0 - x));
        }
        x -= 1.0;
        double result = 0.99999999999980993;
        double coefficients[] = {
            676.5203681218851, -1259.1392167224028, 771.32342877765313,
            -176.61502916214059, 12.507343278686905, -0.13857109526572012,
            9.9843695780195716e-6, 1.5056327351493116e-7
        };
        
        for (int i = 0; i < 8; ++i) {
            result += coefficients[i] / (x + i + 1);
        }
        
        double t = x + 7.5;
        return std::sqrt(2 * std::numbers::pi) * std::pow(t, x + 0.5) * std::exp(-t) * result;
    };
    
    std::cout << "  Γ(" << special_x << ") ≈ " << std::fixed << std::setprecision(6) << gamma_approx(special_x) << std::endl;
    
    // Bessel functions (approximations)
    auto bessel_j0 = [](double x) -> double {
        if (std::abs(x) < 1e-10) return 1.0;
        return std::sin(x) / x;
    };
    
    std::cout << "  J₀(" << special_x << ") ≈ " << std::fixed << std::setprecision(6) << bessel_j0(special_x) << std::endl;
    
    // 12. Performance Comparison
    std::cout << "\n12. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_calculations = 1000000;
    
    // Double precision
    auto start = std::chrono::high_resolution_clock::now();
    double sum_double = 0.0;
    for (int i = 0; i < num_calculations; ++i) {
        sum_double += std::sin(i * 0.001);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto double_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Float precision
    start = std::chrono::high_resolution_clock::now();
    float sum_float = 0.0f;
    for (int i = 0; i < num_calculations; ++i) {
        sum_float += std::sinf(i * 0.001f);
    }
    end = std::chrono::high_resolution_clock::now();
    auto float_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Double precision time: " << double_time.count() << " microseconds" << std::endl;
    std::cout << "  Float precision time: " << float_time.count() << " microseconds" << std::endl;
    std::cout << "  Float speedup: " << (double)double_time.count() / float_time.count() << "x" << std::endl;
    std::cout << "  Double sum: " << std::fixed << std::setprecision(6) << sum_double << std::endl;
    std::cout << "  Float sum: " << std::fixed << std::setprecision(6) << sum_float << std::endl;
    
    std::cout << "\nNumerics demonstration completed!" << std::endl;
    return 0;
}
