/*
 * Lesson 7.1: Structures
 * 
 * This file demonstrates structure declaration, initialization,
 * member access, and structure operations.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Basic structure example
struct Person {
    std::string name;
    int age;
    double height;
    bool is_student;
    
    // Member function
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age 
                  << ", Height: " << height << ", Student: " << (is_student ? "Yes" : "No") << std::endl;
    }
    
    // Member function with calculation
    double height_in_cm() const {
        return height * 30.48;  // Convert feet to cm
    }
};

// Structure with constructor
struct Point {
    double x, y;
    
    // Constructor
    Point(double x_val = 0.0, double y_val = 0.0) : x(x_val), y(y_val) {}
    
    // Member functions
    void display() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
    
    double distance_from_origin() const {
        return std::sqrt(x*x + y*y);
    }
    
    double distance_to(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx*dx + dy*dy);
    }
};

// Structure with nested structure
struct Address {
    std::string street;
    std::string city;
    std::string state;
    int zip_code;
    
    void display() const {
        std::cout << street << ", " << city << ", " << state << " " << zip_code << std::endl;
    }
};

struct Employee {
    std::string name;
    int employee_id;
    double salary;
    Address address;
    
    void display() const {
        std::cout << "Employee: " << name << " (ID: " << employee_id << ")" << std::endl;
        std::cout << "Salary: $" << salary << std::endl;
        std::cout << "Address: ";
        address.display();
    }
};

// Function to demonstrate basic structures
void demonstrateBasicStructures() {
    std::cout << "=== Basic Structures Demonstration ===" << std::endl;
    
    // Structure initialization
    Person person1 = {"Alice", 25, 5.6, true};
    Person person2{"Bob", 30, 6.0, false};
    Person person3;
    person3.name = "Charlie";
    person3.age = 35;
    person3.height = 5.8;
    person3.is_student = false;
    
    std::cout << "Person 1:" << std::endl;
    person1.display();
    std::cout << "Height in cm: " << person1.height_in_cm() << std::endl;
    
    std::cout << "
Person 2:" << std::endl;
    person2.display();
    
    std::cout << "
Person 3:" << std::endl;
    person3.display();
    
    // Structure assignment
    Person person4 = person1;
    std::cout << "
Person 4 (copy of Person 1):" << std::endl;
    person4.display();
}

// Function to demonstrate structure with constructor
void demonstrateStructureWithConstructor() {
    std::cout << "
=== Structure with Constructor ===" << std::endl;
    
    // Different ways to create Point objects
    Point p1;                    // Default constructor
    Point p2(3.0, 4.0);         // Parameterized constructor
    Point p3{1.0, 2.0};         // C++11 initialization
    
    std::cout << "Point 1 (default): ";
    p1.display();
    std::cout << "Distance from origin: " << p1.distance_from_origin() << std::endl;
    
    std::cout << "
Point 2 (3, 4): ";
    p2.display();
    std::cout << "Distance from origin: " << p2.distance_from_origin() << std::endl;
    
    std::cout << "
Point 3 (1, 2): ";
    p3.display();
    std::cout << "Distance from origin: " << p3.distance_from_origin() << std::endl;
    
    // Calculate distance between points
    double dist = p2.distance_to(p3);
    std::cout << "
Distance between Point 2 and Point 3: " << dist << std::endl;
}

// Function to demonstrate nested structures
void demonstrateNestedStructures() {
    std::cout << "
=== Nested Structures ===" << std::endl;
    
    // Create employee with nested address
    Employee emp1;
    emp1.name = "John Doe";
    emp1.employee_id = 1001;
    emp1.salary = 75000.0;
    emp1.address.street = "123 Main St";
    emp1.address.city = "Anytown";
    emp1.address.state = "CA";
    emp1.address.zip_code = 12345;
    
    std::cout << "Employee 1:" << std::endl;
    emp1.display();
    
    // Create employee with initialization
    Employee emp2 = {
        "Jane Smith",
        1002,
        80000.0,
        {"456 Oak Ave", "Somewhere", "NY", 54321}
    };
    
    std::cout << "
Employee 2:" << std::endl;
    emp2.display();
}

// Function to demonstrate structure arrays
void demonstrateStructureArrays() {
    std::cout << "
=== Structure Arrays ===" << std::endl;
    
    // Array of structures
    Person people[3] = {
        {"Alice", 25, 5.6, true},
        {"Bob", 30, 6.0, false},
        {"Charlie", 35, 5.8, true}
    };
    
    std::cout << "People array:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Person " << (i+1) << ": ";
        people[i].display();
    }
    
    // Array of points
    Point points[4] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0},
        {1.0, 1.0}
    };
    
    std::cout << "
Points array:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Point " << (i+1) << ": ";
        points[i].display();
    }
}

// Function to demonstrate structure pointers
void demonstrateStructurePointers() {
    std::cout << "
=== Structure Pointers ===" << std::endl;
    
    Person person = {"David", 28, 5.9, false};
    Person* ptr = &person;
    
    // Access members through pointer
    std::cout << "Access through pointer:" << std::endl;
    std::cout << "Name: " << (*ptr).name << std::endl;
    std::cout << "Age: " << (*ptr).age << std::endl;
    
    // Arrow operator (preferred)
    std::cout << "
Access through arrow operator:" << std::endl;
    std::cout << "Height: " << ptr->height << std::endl;
    std::cout << "Student: " << (ptr->is_student ? "Yes" : "No") << std::endl;
    
    // Call member function through pointer
    std::cout << "
Call member function through pointer:" << std::endl;
    ptr->display();
    
    // Dynamic allocation
    Person* dynamic_person = new Person{"Eve", 32, 5.7, true};
    std::cout << "
Dynamic person:" << std::endl;
    dynamic_person->display();
    delete dynamic_person;
}

// Function to demonstrate structure comparison
void demonstrateStructureComparison() {
    std::cout << "
=== Structure Comparison ===" << std::endl;
    
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(3.0, 4.0);
    
    // Compare coordinates
    std::cout << "Point 1: ";
    p1.display();
    std::cout << "Point 2: ";
    p2.display();
    std::cout << "Point 3: ";
    p3.display();
    
    // Compare x coordinates
    std::cout << "
Comparison:" << std::endl;
    std::cout << "p1.x == p2.x: " << (p1.x == p2.x) << std::endl;
    std::cout << "p1.y == p2.y: " << (p1.y == p2.y) << std::endl;
    std::cout << "p1.x == p3.x: " << (p1.x == p3.x) << std::endl;
    
    // Compare distances
    std::cout << "
Distance comparison:" << std::endl;
    std::cout << "p1 distance: " << p1.distance_from_origin() << std::endl;
    std::cout << "p2 distance: " << p2.distance_from_origin() << std::endl;
    std::cout << "p3 distance: " << p3.distance_from_origin() << std::endl;
}

// Function to demonstrate structure size and alignment
void demonstrateStructureSize() {
    std::cout << "
=== Structure Size and Alignment ===" << std::endl;
    
    struct SmallStruct {
        char a;
        char b;
        char c;
    };
    
    struct MixedStruct {
        char a;
        int b;
        char c;
    };
    
    struct LargeStruct {
        double a;
        int b;
        char c;
    };
    
    std::cout << "Size of SmallStruct: " << sizeof(SmallStruct) << " bytes" << std::endl;
    std::cout << "Size of MixedStruct: " << sizeof(MixedStruct) << " bytes" << std::endl;
    std::cout << "Size of LargeStruct: " << sizeof(LargeStruct) << " bytes" << std::endl;
    
    std::cout << "
Individual member sizes:" << std::endl;
    std::cout << "sizeof(char): " << sizeof(char) << " bytes" << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << " bytes" << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << " bytes" << std::endl;
}

// Function to demonstrate structure with functions
void demonstrateStructureWithFunctions() {
    std::cout << "
=== Structure with Functions ===" << std::endl;
    
    struct Rectangle {
        double width, height;
        
        // Constructor
        Rectangle(double w = 0.0, double h = 0.0) : width(w), height(h) {}
        
        // Member functions
        double area() const {
            return width * height;
        }
        
        double perimeter() const {
            return 2 * (width + height);
        }
        
        void scale(double factor) {
            width *= factor;
            height *= factor;
        }
        
        void display() const {
            std::cout << "Rectangle: " << width << " x " << height 
                      << " (Area: " << area() << ", Perimeter: " << perimeter() << ")" << std::endl;
        }
    };
    
    Rectangle rect(5.0, 3.0);
    std::cout << "Original rectangle:" << std::endl;
    rect.display();
    
    rect.scale(2.0);
    std::cout << "
After scaling by 2:" << std::endl;
    rect.display();
}

// Function to demonstrate structure initialization
void demonstrateStructureInitialization() {
    std::cout << "
=== Structure Initialization ===" << std::endl;
    
    struct Student {
        std::string name;
        int age;
        double gpa;
        bool is_graduated;
    };
    
    // Different initialization methods
    Student s1 = {"Alice", 20, 3.8, false};  // C-style
    Student s2{"Bob", 22, 3.5, false};       // C++11
    Student s3;                               // Default
    s3.name = "Charlie";
    s3.age = 21;
    s3.gpa = 3.9;
    s3.is_graduated = false;
    
    // Partial initialization
    Student s4 = {"David", 23};  // gpa and is_graduated default to 0.0 and false
    
    std::cout << "Student 1: " << s1.name << ", Age: " << s1.age << ", GPA: " << s1.gpa << std::endl;
    std::cout << "Student 2: " << s2.name << ", Age: " << s2.age << ", GPA: " << s2.gpa << std::endl;
    std::cout << "Student 3: " << s3.name << ", Age: " << s3.age << ", GPA: " << s3.gpa << std::endl;
    std::cout << "Student 4: " << s4.name << ", Age: " << s4.age << ", GPA: " << s4.gpa << std::endl;
}

int main() {
    std::cout << "=== Structures Demonstration ===" << std::endl;
    std::cout << "This program demonstrates structure declaration, initialization,
"
              << "member access, and structure operations.
" << std::endl;
    
    // Demonstrate various structure concepts
    demonstrateBasicStructures();
    demonstrateStructureWithConstructor();
    demonstrateNestedStructures();
    demonstrateStructureArrays();
    demonstrateStructurePointers();
    demonstrateStructureComparison();
    demonstrateStructureSize();
    demonstrateStructureWithFunctions();
    demonstrateStructureInitialization();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. Structures group related data together" << std::endl;
    std::cout << "2. Structures can have member functions" << std::endl;
    std::cout << "3. Structures support various initialization methods" << std::endl;
    std::cout << "4. Structures can be nested and used in arrays" << std::endl;
    std::cout << "5. Structures can be accessed through pointers" << std::endl;
    std::cout << "6. Structure size depends on member alignment" << std::endl;
    std::cout << "7. Structures provide a foundation for classes" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o structures 01_Structures.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o structures 01_Structures.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Structures.cpp
 * 
 * Running:
 * ./structures (Linux/macOS)
 * structures.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for uniform initialization.
 * C++17 is recommended for best structure support.
 * 
 * Structure Notes:
 * - Structures group related data together
 * - Members are public by default
 * - Structures support member functions
 * - Memory layout depends on alignment
 * - Structures are the foundation for classes
 */