#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Demonstrates C++ namespaces and their usage
int main() {
    std::cout << "C++ Namespaces Demonstration" << std::endl;
    std::cout << "============================" << std::endl;
    
    // 1. Basic namespace declaration
    std::cout << "\n1. BASIC NAMESPACE DECLARATION:" << std::endl;
    
    namespace math {
        int add(int a, int b) {
            return a + b;
        }
        
        int multiply(int a, int b) {
            return a * b;
        }
        
        double divide(double a, double b) {
            if (b != 0) {
                return a / b;
            }
            return 0.0;
        }
    }
    
    std::cout << "math::add(5, 3) = " << math::add(5, 3) << std::endl;
    std::cout << "math::multiply(4, 6) = " << math::multiply(4, 6) << std::endl;
    std::cout << "math::divide(10.0, 2.0) = " << math::divide(10.0, 2.0) << std::endl;
    
    // 2. Multiple namespaces
    std::cout << "\n2. MULTIPLE NAMESPACES:" << std::endl;
    
    namespace string_utils {
        std::string to_upper(const std::string& str) {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(), ::toupper);
            return result;
        }
        
        std::string to_lower(const std::string& str) {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }
        
        std::string reverse(const std::string& str) {
            std::string result = str;
            std::reverse(result.begin(), result.end());
            return result;
        }
    }
    
    namespace container_utils {
        template<typename T>
        void print_vector(const std::vector<T>& vec) {
            std::cout << "Vector: ";
            for (const auto& item : vec) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
        
        template<typename T>
        T sum_vector(const std::vector<T>& vec) {
            T sum = T{};
            for (const auto& item : vec) {
                sum += item;
            }
            return sum;
        }
    }
    
    std::cout << "string_utils::to_upper(\"hello\") = " 
              << string_utils::to_upper("hello") << std::endl;
    std::cout << "string_utils::to_lower(\"WORLD\") = " 
              << string_utils::to_lower("WORLD") << std::endl;
    std::cout << "string_utils::reverse(\"cpp\") = " 
              << string_utils::reverse("cpp") << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    container_utils::print_vector(numbers);
    std::cout << "Sum: " << container_utils::sum_vector(numbers) << std::endl;
    
    // 3. Using declarations
    std::cout << "\n3. USING DECLARATIONS:" << std::endl;
    
    using math::add;  // Using declaration - brings add into current scope
    using string_utils::to_upper;
    
    std::cout << "add(10, 20) = " << add(10, 20) << std::endl;  // No math:: prefix needed
    std::cout << "to_upper(\"namespace\") = " << to_upper("namespace") << std::endl;
    
    // Still need prefix for other functions
    std::cout << "math::multiply(3, 4) = " << math::multiply(3, 4) << std::endl;
    
    // 4. Using directives
    std::cout << "\n4. USING DIRECTIVES:" << std::endl;
    
    {
        using namespace math;  // Using directive - brings all names from math into scope
        
        std::cout << "add(15, 25) = " << add(15, 25) << std::endl;
        std::cout << "multiply(5, 6) = " << multiply(5, 6) << std::endl;
        std::cout << "divide(20.0, 4.0) = " << divide(20.0, 4.0) << std::endl;
    }  // Using directive scope ends here
    
    // Now we need prefixes again
    std::cout << "math::add(1, 2) = " << math::add(1, 2) << std::endl;
    
    // 5. Namespace aliases
    std::cout << "\n5. NAMESPACE ALIASES:" << std::endl;
    
    namespace very_long_namespace_name {
        int function1() { return 1; }
        int function2() { return 2; }
        int function3() { return 3; }
    }
    
    // Create alias for long namespace name
    namespace vlnn = very_long_namespace_name;
    
    std::cout << "vlnn::function1() = " << vlnn::function1() << std::endl;
    std::cout << "vlnn::function2() = " << vlnn::function2() << std::endl;
    std::cout << "vlnn::function3() = " << vlnn::function3() << std::endl;
    
    // 6. Nested namespaces
    std::cout << "\n6. NESTED NAMESPACES:" << std::endl;
    
    namespace outer {
        int outer_var = 100;
        
        namespace inner {
            int inner_var = 200;
            
            namespace deep {
                int deep_var = 300;
                
                void display_values() {
                    std::cout << "outer::outer_var = " << outer::outer_var << std::endl;
                    std::cout << "inner::inner_var = " << inner::inner_var << std::endl;
                    std::cout << "deep::deep_var = " << deep_var << std::endl;
                }
            }
        }
    }
    
    std::cout << "outer::outer_var = " << outer::outer_var << std::endl;
    std::cout << "outer::inner::inner_var = " << outer::inner::inner_var << std::endl;
    std::cout << "outer::inner::deep::deep_var = " << outer::inner::deep::deep_var << std::endl;
    
    outer::inner::deep::display_values();
    
    // 7. Anonymous namespaces
    std::cout << "\n7. ANONYMOUS NAMESPACES:" << std::endl;
    
    namespace {  // Anonymous namespace
        int internal_var = 42;
        
        void internal_function() {
            std::cout << "Internal function called, internal_var = " << internal_var << std::endl;
        }
        
        class InternalClass {
        public:
            void display() {
                std::cout << "Internal class display method" << std::endl;
            }
        };
    }
    
    // These are accessible in this file only
    internal_function();
    InternalClass obj;
    obj.display();
    std::cout << "internal_var = " << internal_var << std::endl;
    
    // 8. Namespace with classes
    std::cout << "\n8. NAMESPACE WITH CLASSES:" << std::endl;
    
    namespace geometry {
        class Point {
        private:
            double x, y;
            
        public:
            Point(double x = 0, double y = 0) : x(x), y(y) {}
            
            double get_x() const { return x; }
            double get_y() const { return y; }
            
            void display() const {
                std::cout << "Point(" << x << ", " << y << ")" << std::endl;
            }
        };
        
        class Circle {
        private:
            Point center;
            double radius;
            
        public:
            Circle(const Point& c, double r) : center(c), radius(r) {}
            
            double area() const {
                return 3.14159 * radius * radius;
            }
            
            double circumference() const {
                return 2 * 3.14159 * radius;
            }
            
            void display() const {
                std::cout << "Circle with center ";
                center.display();
                std::cout << " and radius " << radius << std::endl;
            }
        };
    }
    
    geometry::Point p(3, 4);
    geometry::Circle c(p, 5);
    
    p.display();
    c.display();
    std::cout << "Circle area: " << c.area() << std::endl;
    std::cout << "Circle circumference: " << c.circumference() << std::endl;
    
    // 9. Namespace with templates
    std::cout << "\n9. NAMESPACE WITH TEMPLATES:" << std::endl;
    
    namespace algorithms {
        template<typename T>
        T find_max(const std::vector<T>& vec) {
            if (vec.empty()) return T{};
            
            T max_val = vec[0];
            for (const auto& item : vec) {
                if (item > max_val) {
                    max_val = item;
                }
            }
            return max_val;
        }
        
        template<typename T>
        T find_min(const std::vector<T>& vec) {
            if (vec.empty()) return T{};
            
            T min_val = vec[0];
            for (const auto& item : vec) {
                if (item < min_val) {
                    min_val = item;
                }
            }
            return min_val;
        }
        
        template<typename T>
        void bubble_sort(std::vector<T>& vec) {
            for (size_t i = 0; i < vec.size() - 1; ++i) {
                for (size_t j = 0; j < vec.size() - i - 1; ++j) {
                    if (vec[j] > vec[j + 1]) {
                        std::swap(vec[j], vec[j + 1]);
                    }
                }
            }
        }
    }
    
    std::vector<int> sort_numbers = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Original: ";
    for (int num : sort_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    std::cout << "Max: " << algorithms::find_max(sort_numbers) << std::endl;
    std::cout << "Min: " << algorithms::find_min(sort_numbers) << std::endl;
    
    algorithms::bubble_sort(sort_numbers);
    std::cout << "Sorted: ";
    for (int num : sort_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // 10. Namespace with constants and enums
    std::cout << "\n10. NAMESPACE WITH CONSTANTS AND ENUMS:" << std::endl;
    
    namespace constants {
        const double PI = 3.14159;
        const double E = 2.71828;
        const int MAX_SIZE = 1000;
        
        enum class Color {
            RED, GREEN, BLUE, YELLOW, PURPLE
        };
        
        enum class Size {
            SMALL, MEDIUM, LARGE, EXTRA_LARGE
        };
        
        std::string color_to_string(Color color) {
            switch (color) {
                case Color::RED: return "Red";
                case Color::GREEN: return "Green";
                case Color::BLUE: return "Blue";
                case Color::YELLOW: return "Yellow";
                case Color::PURPLE: return "Purple";
                default: return "Unknown";
            }
        }
        
        std::string size_to_string(Size size) {
            switch (size) {
                case Size::SMALL: return "Small";
                case Size::MEDIUM: return "Medium";
                case Size::LARGE: return "Large";
                case Size::EXTRA_LARGE: return "Extra Large";
                default: return "Unknown";
            }
        }
    }
    
    std::cout << "PI = " << constants::PI << std::endl;
    std::cout << "E = " << constants::E << std::endl;
    std::cout << "MAX_SIZE = " << constants::MAX_SIZE << std::endl;
    
    constants::Color color = constants::Color::BLUE;
    constants::Size size = constants::Size::LARGE;
    
    std::cout << "Color: " << constants::color_to_string(color) << std::endl;
    std::cout << "Size: " << constants::size_to_string(size) << std::endl;
    
    // 11. Namespace with function overloading
    std::cout << "\n11. NAMESPACE WITH FUNCTION OVERLOADING:" << std::endl;
    
    namespace utilities {
        void print(int value) {
            std::cout << "Integer: " << value << std::endl;
        }
        
        void print(double value) {
            std::cout << "Double: " << value << std::endl;
        }
        
        void print(const std::string& value) {
            std::cout << "String: " << value << std::endl;
        }
        
        void print(bool value) {
            std::cout << "Boolean: " << std::boolalpha << value << std::endl;
        }
    }
    
    utilities::print(42);
    utilities::print(3.14159);
    utilities::print("Hello, Namespace!");
    utilities::print(true);
    
    // 12. Namespace with static variables
    std::cout << "\n12. NAMESPACE WITH STATIC VARIABLES:" << std::endl;
    
    namespace counter {
        static int count = 0;
        
        int increment() {
            return ++count;
        }
        
        int decrement() {
            return --count;
        }
        
        int get_count() {
            return count;
        }
        
        void reset() {
            count = 0;
        }
    }
    
    std::cout << "Initial count: " << counter::get_count() << std::endl;
    std::cout << "After increment: " << counter::increment() << std::endl;
    std::cout << "After increment: " << counter::increment() << std::endl;
    std::cout << "After decrement: " << counter::decrement() << std::endl;
    std::cout << "Final count: " << counter::get_count() << std::endl;
    
    // 13. Namespace with nested functions
    std::cout << "\n13. NAMESPACE WITH NESTED FUNCTIONS:" << std::endl;
    
    namespace math_advanced {
        namespace trigonometry {
            double sin(double angle) {
                return std::sin(angle * 3.14159 / 180.0);  // Convert to radians
            }
            
            double cos(double angle) {
                return std::cos(angle * 3.14159 / 180.0);
            }
            
            double tan(double angle) {
                return std::tan(angle * 3.14159 / 180.0);
            }
        }
        
        namespace statistics {
            double mean(const std::vector<double>& data) {
                if (data.empty()) return 0.0;
                
                double sum = 0.0;
                for (double value : data) {
                    sum += value;
                }
                return sum / data.size();
            }
            
            double variance(const std::vector<double>& data) {
                if (data.empty()) return 0.0;
                
                double mean_val = mean(data);
                double sum_squared_diff = 0.0;
                
                for (double value : data) {
                    double diff = value - mean_val;
                    sum_squared_diff += diff * diff;
                }
                
                return sum_squared_diff / data.size();
            }
        }
    }
    
    std::cout << "sin(30) = " << math_advanced::trigonometry::sin(30) << std::endl;
    std::cout << "cos(60) = " << math_advanced::trigonometry::cos(60) << std::endl;
    std::cout << "tan(45) = " << math_advanced::trigonometry::tan(45) << std::endl;
    
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::cout << "Mean: " << math_advanced::statistics::mean(data) << std::endl;
    std::cout << "Variance: " << math_advanced::statistics::variance(data) << std::endl;
    
    // 14. Namespace with friend functions
    std::cout << "\n14. NAMESPACE WITH FRIEND FUNCTIONS:" << std::endl;
    
    namespace friendship {
        class MyClass {
        private:
            int value;
            
        public:
            MyClass(int v) : value(v) {}
            
            friend void display_value(const MyClass& obj);
            friend class FriendClass;
        };
        
        void display_value(const MyClass& obj) {
            std::cout << "Friend function accessing private value: " << obj.value << std::endl;
        }
        
        class FriendClass {
        public:
            static void modify_value(MyClass& obj, int new_value) {
                obj.value = new_value;
                std::cout << "Friend class modified value to: " << obj.value << std::endl;
            }
        };
    }
    
    friendship::MyClass obj(42);
    friendship::display_value(obj);
    friendship::FriendClass::modify_value(obj, 100);
    friendship::display_value(obj);
    
    // 15. Namespace with operator overloading
    std::cout << "\n15. NAMESPACE WITH OPERATOR OVERLOADING:" << std::endl;
    
    namespace operators {
        class Complex {
        private:
            double real, imag;
            
        public:
            Complex(double r = 0, double i = 0) : real(r), imag(i) {}
            
            Complex operator+(const Complex& other) const {
                return Complex(real + other.real, imag + other.imag);
            }
            
            Complex operator*(const Complex& other) const {
                return Complex(real * other.real - imag * other.imag,
                              real * other.imag + imag * other.real);
            }
            
            friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
                os << "(" << c.real << " + " << c.imag << "i)";
                return os;
            }
        };
    }
    
    operators::Complex c1(3, 4);
    operators::Complex c2(1, 2);
    operators::Complex c3 = c1 + c2;
    operators::Complex c4 = c1 * c2;
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    std::cout << "c1 * c2 = " << c4 << std::endl;
    
    std::cout << "\nNamespaces demonstration completed!" << std::endl;
    return 0;
}
