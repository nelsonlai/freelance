#include <iostream>
#include <string>

// Demonstrates C++ type safety and compilation model
int main() {
    // Basic types with explicit initialization
    int age = 25;
    double height = 5.9;    // float
    char grade = 'A';
    bool is_student = true;
    
    std::cout << "Type Safety Demonstration" << std::endl;
    std::cout << "=========================" << std::endl;
    
    // Safe implicit conversions
    double age_as_double = age;  // int to double
    std::cout << "Age as int: " << age << std::endl;
    std::cout << "Age as double: " << age_as_double << std::endl;
    
    // Explicit type conversions
    int height_as_int = static_cast<int>(height);
    std::cout << "Height as double: " << height << std::endl;
    std::cout << "Height as int: " << height_as_int << std::endl;
    
    // String operations (type-safe)
    std::string name = "Alice";
    std::string greeting = "Hello, " + name + "!";
    std::cout << greeting << std::endl;
    
    // Compile-time type checking
    // The following lines would cause compile errors if uncommented:
    // std::string invalid = age;  // No implicit int to string conversion
    // bool invalid_bool = name;   // No implicit string to bool conversion
    
    std::cout << "\nGrade: " << grade << std::endl;
    std::cout << "Is student: " << std::boolalpha << is_student << std::endl;
    
    return 0;
}
