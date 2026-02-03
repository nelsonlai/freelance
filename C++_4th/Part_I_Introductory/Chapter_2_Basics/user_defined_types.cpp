#include <iostream>
#include <string>
#include <vector>

// User-defined types demonstration

// 1. Enumerations
enum Color {
    RED,    // default startingvalue is 0
    GREEN,
    BLUE,
    YELLOW
};

// Scoped enumeration (C++11)
enum class Size {
    SMALL = 1,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

// 2. Structures
struct Point {
    double x;
    double y;
    
    // Constructor
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    // Member function
    void display() const {
        std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }
    
    // Member function to calculate distance from origin
    double distance_from_origin() const {
        return std::sqrt(x * x + y * y);
    }
};

// 3. Structure with various data types
struct Student {
    std::string name;
    int age;
    double gpa;
    Color favorite_color;
    Size shirt_size;
    
    // Constructor
    Student(const std::string& name, int age, double gpa, 
            Color color = BLUE, Size size = Size::MEDIUM)
        : name(name), age(age), gpa(gpa), favorite_color(color), shirt_size(size) {}
    
    // Member function
    void display_info() const {
        std::cout << "Student: " << name << std::endl;
        std::cout << "  Age: " << age << std::endl;
        std::cout << "  GPA: " << gpa << std::endl;
        std::cout << "  Favorite Color: ";
        
        switch (favorite_color) {
            case RED: std::cout << "Red"; break;
            case GREEN: std::cout << "Green"; break;
            case BLUE: std::cout << "Blue"; break;
            case YELLOW: std::cout << "Yellow"; break;
        }
        std::cout << std::endl;
        
        std::cout << "  Shirt Size: ";
        switch (shirt_size) {
            case Size::SMALL: std::cout << "Small"; break;
            case Size::MEDIUM: std::cout << "Medium"; break;
            case Size::LARGE: std::cout << "Large"; break;
            case Size::EXTRA_LARGE: std::cout << "Extra Large"; break;
        }
        std::cout << std::endl;
    }
    
    // Member function to check if student is honor roll
    bool is_honor_roll() const {
        return gpa >= 3.5;
    }
};

// 4. Union (for memory efficiency when storing different types)
union Number {
    int integer;
    double floating_point;
    char character;
    
    // Constructor
    Number(int value) : integer(value) {}
    Number(double value) : floating_point(value) {}
    Number(char value) : character(value) {}
};

// 5. Function to work with user-defined types
void demonstrate_point_operations() {
    std::cout << "Point Operations:" << std::endl;
    
    Point p1(3.0, 4.0);
    Point p2(1.0, 2.0);
    
    std::cout << "Point 1: ";
    p1.display();
    std::cout << "Distance from origin: " << p1.distance_from_origin() << std::endl;
    
    std::cout << "Point 2: ";
    p2.display();
    std::cout << "Distance from origin: " << p2.distance_from_origin() << std::endl;
}

void demonstrate_student_management() {
    std::cout << "\nStudent Management:" << std::endl;
    
    Student david("David Leung", 20, 3.8, GREEN, Size::SMALL);
    david.display_info();
    std::cout << "Is honor roll: " << std::boolalpha << david.is_honor_roll() << std::endl;
    
    std::vector<Student> students = {
        Student("Alice Johnson", 20, 3.8, GREEN, Size::SMALL),
        Student("Bob Smith", 22, 3.2, BLUE, Size::LARGE),
        Student("Charlie Brown", 19, 3.9, RED, Size::MEDIUM),
        Student("Diana Prince", 21, 3.6, YELLOW, Size::MEDIUM)
    };
    
    std::cout << "All Students:" << std::endl;
    for (const auto& student : students) {
        student.display_info();
        std::cout << std::endl;
    }
    
    std::cout << "Honor Roll Students:" << std::endl;
    for (const auto& student : students) {
        if (student.is_honor_roll()) {
            std::cout << "- " << student.name << " (GPA: " << student.gpa << ")" << std::endl;
        }
    }
}

void demonstrate_unions() {
    std::cout << "\nUnion Demonstration:" << std::endl;
    
    Number num1(42);
    Number num2(3.14);
    Number num3('A');
    
    std::cout << "Integer: " << num1.integer << std::endl;
    std::cout << "Float: " << num2.floating_point << std::endl;
    std::cout << "Character: " << num3.character << std::endl;
    
    // Note: Only one member should be accessed at a time in a union
    std::cout << "Size of union: " << sizeof(Number) << " bytes" << std::endl;
}

int main() {
    std::cout << "User-Defined Types Demonstration" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // Demonstrate enumerations
    std::cout << "\n1. ENUMERATIONS:" << std::endl;
    Color my_color = GREEN;
    Size my_size = Size::LARGE;
    
    std::cout << "My color: " << my_color << std::endl;
    std::cout << "My size: " << static_cast<int>(my_size) << std::endl;
    
    // Demonstrate structures
    std::cout << "\n2. STRUCTURES:" << std::endl;
    demonstrate_point_operations();
    demonstrate_student_management();
    
    // Demonstrate unions
    demonstrate_unions();
    
    // Demonstrate type safety with scoped enumerations
    std::cout << "\n3. TYPE SAFETY:" << std::endl;
    
    // This would cause a compile error if uncommented:
    // Color c = Size::SMALL;  // Cannot assign scoped enum to unscoped enum
    
    Size size1 = Size::MEDIUM;
    Size size2 = Size::LARGE;
    
    // This works fine:
    if (size1 == Size::MEDIUM) {
        std::cout << "Size is medium" << std::endl;
    }
    
    return 0;
}
