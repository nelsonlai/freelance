/*
 * STRUCT BEGINNER EXAMPLES
 * 
 * This file demonstrates basic struct concepts in C++:
 * - Basic struct declaration and usage
 * - Data members and member functions
 * - Different initialization methods
 * - Structs with different data types
 * - Arrays of structs
 * - Structs as function parameters
 * 
 * Learning Objectives:
 * - Understand what a struct is and how to declare one
 * - Learn how to access struct members using the dot operator
 * - Master different ways to initialize structs
 * - Understand the difference between structs and classes
 * - Learn how to use structs in arrays and as function parameters
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
using namespace std; // Using standard namespace (for beginners)

/*
 * BASIC STRUCT DECLARATION
 * 
 * A struct is a user-defined data type that groups related data together.
 * In C++, structs are similar to classes but with public access by default.
 * 
 * Key Points:
 * - 'struct' keyword is used to declare a struct
 * - Data members are variables that hold the actual data
 * - Member functions are functions that operate on the data
 * - Default access is public (unlike classes which default to private)
 */
struct Student {
    // DATA MEMBERS - These hold the actual data
    string name;  // Student's full name (string type)
    int age;      // Student's age in years (integer type)
    float gpa;    // Grade Point Average (floating-point type)
    
    /*
     * MEMBER FUNCTION - Functions that operate on the struct's data
     * 
     * This function displays all the student's information.
     * It can access all data members directly because they're in the same struct.
     */
    void displayInfo() {
        cout << "Name: " << name << endl;    // Display the student's name
        cout << "Age: " << age << endl;      // Display the student's age
        cout << "GPA: " << gpa << endl;      // Display the student's GPA
    }
};

/*
 * STRUCT WITH DIFFERENT DATA TYPES
 * 
 * This struct demonstrates how to group different types of data together
 * and provides functions to perform calculations on that data.
 * 
 * Key Points:
 * - Structs can contain any data type (primitive or user-defined)
 * - Member functions can perform calculations using the data members
 * - Functions can return values based on the struct's data
 */
struct Rectangle {
    double width;   // Width of the rectangle (double precision floating-point)
    double height;  // Height of the rectangle (double precision floating-point)
    
    /*
     * CALCULATION FUNCTION
     * 
     * This function calculates the area of the rectangle.
     * Area = width × height
     * 
     * @return The area of the rectangle as a double
     */
    double calculateArea() {
        return width * height;  // Multiply width by height to get area
    }
    
    /*
     * CALCULATION FUNCTION
     * 
     * This function calculates the perimeter of the rectangle.
     * Perimeter = 2 × (width + height)
     * 
     * @return The perimeter of the rectangle as a double
     */
    double calculatePerimeter() {
        return 2 * (width + height);  // 2 times the sum of width and height
    }
};

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various ways to use structs in C++.
 * It shows different initialization methods, member access, and
 * how structs can be used in arrays and as function parameters.
 */
int main() {
    // Display program header
    cout << "=== STRUCT BEGINNER EXAMPLES ===" << endl << endl;
    
    /*
     * EXAMPLE 1: BASIC STRUCT USAGE
     * 
     * This demonstrates the most basic way to use a struct:
     * 1. Declare a struct variable
     * 2. Access members using the dot operator (.)
     * 3. Assign values to each member individually
     * 4. Call member functions
     */
    cout << "1. Basic Student Struct:" << endl;
    
    // Declare a Student struct variable (creates an instance)
    Student student1;

    
    // Access and assign values to each member using the dot operator
    student1.name = "Alice Johnson";  // Assign string value to name member
    student1.age = 20;                // Assign integer value to age member
    student1.gpa = 3.8;               // Assign float value to gpa member
    
    // Display the student information using the member function
    cout << "Student Information:" << endl;
    student1.displayInfo();  // Call the displayInfo() member function
    cout << endl;
    
    /*
     * EXAMPLE 2: DIRECT INITIALIZATION (AGGREGATE INITIALIZATION)
     * 
     * This demonstrates a more concise way to initialize a struct.
     * The values are provided in the same order as the members are declared.
     * This is called "aggregate initialization" or "brace initialization".
     * 
     * Syntax: StructName variable = {value1, value2, value3, ...};
     */
    cout << "2. Direct Initialization:" << endl;
    
    // Initialize struct with values in declaration order
    // {"Bob Smith", 22, 3.5} corresponds to {name, age, gpa}
    Student student2 = {"Bob Smith", 22, 3.5};
    
    // Display the student information
    student2.displayInfo();
    cout << endl;
    
    /*
     * EXAMPLE 3: RECTANGLE CALCULATIONS
     * 
     * This demonstrates how structs can be used for mathematical calculations.
     * We'll create a rectangle, set its dimensions, and calculate its area and perimeter.
     */
    cout << "3. Rectangle Calculations:" << endl;
    
    // Create a Rectangle struct instance
    Rectangle rect;
    
    // Set the rectangle's dimensions
    rect.width = 5.5;   // Set width to 5.5 units
    rect.height = 3.2;  // Set height to 3.2 units
    
    // Display the rectangle's dimensions
    cout << "Rectangle with width " << rect.width 
         << " and height " << rect.height << endl;
    
    // Calculate and display the area using the member function
    cout << "Area: " << rect.calculateArea() << endl;
    
    // Calculate and display the perimeter using the member function
    cout << "Perimeter: " << rect.calculatePerimeter() << endl;
    cout << endl;
    
    /*
     * EXAMPLE 4: ARRAY OF STRUCTS
     * 
     * This demonstrates how to create and use arrays of structs.
     * Arrays of structs are useful when you need to store multiple
     * instances of the same struct type.
     */
    cout << "4. Array of Students:" << endl;
    
    // Create an array of 3 Student structs with initial values
    // Each element is initialized using aggregate initialization
    Student students[3] = {
        {"Charlie Brown", 19, 3.9},  // First student
        {"Diana Prince", 21, 3.7},   // Second student
        {"Eve Wilson", 20, 3.6}      // Third student
    };
    
    // Loop through the array and display each student's information
    for (int i = 0; i < 3; i++) {
        cout << "Student " << (i + 1) << ":" << endl;  // Display student number
        students[i].displayInfo();  // Call displayInfo() for current student
        cout << endl;  // Add blank line for readability
    }
    
    /*
     * EXAMPLE 5: STRUCT AS FUNCTION PARAMETER
     * 
     * This demonstrates how to pass structs to functions.
     * We'll use a lambda function (anonymous function) to show
     * how structs can be passed as parameters.
     * 
     * Note: We use 'const Student& s' to pass by reference
     * to avoid copying the entire struct (more efficient).
     */
    cout << "5. Struct as Function Parameter:" << endl;
    
    // Create a lambda function that takes a Student struct as parameter
    // The 'const Student& s' means we're passing by reference (efficient)
    // and promising not to modify the struct (const)
    auto printStudent = [](const Student& s) {
        // Access struct members using the dot operator
        cout << "Student: " << s.name << " (Age: " << s.age << ", GPA: " << s.gpa << ")" << endl;
    };
    
    // Call the lambda function with our student structs
    printStudent(student1);  // Pass student1 to the function
    printStudent(student2);  // Pass student2 to the function
    
    // Return 0 to indicate successful program execution
    return 0;
}
