/*
 * FUNCTION BEGINNER EXAMPLES
 * 
 * This file demonstrates basic function concepts in C++:
 * - Function declaration and definition
 * - Parameters and return values
 * - Different data types in functions
 * - Local variables and scope
 * - Function calls and composition
 * 
 * Learning Objectives:
 * - Understand what functions are and why they're useful
 * - Learn how to declare and define functions
 * - Master function parameters and return values
 * - Understand local variables and scope
 * - Learn how to call functions and compose them
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types
 * - Familiarity with control structures
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
using namespace std; // Using standard namespace (for beginners)

/*
 * BASIC FUNCTION DECLARATION AND DEFINITION
 * 
 * A function is a block of code that performs a specific task.
 * Functions help organize code, make it reusable, and easier to maintain.
 * 
 * Key Points:
 * - 'void' means the function doesn't return a value
 * - Function name should be descriptive
 * - Functions can be called multiple times
 * - Code inside functions is executed when called
 */
void sayHello() {
    cout << "Hello, World!" << endl;  // Print a greeting message
}

/*
 * FUNCTION WITH PARAMETERS
 * 
 * Parameters allow functions to receive data from the caller.
 * Parameters are like variables that get their values when the function is called.
 * 
 * @param name The name to greet (string type)
 */
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;  // Print personalized greeting
}

/*
 * FUNCTION WITH RETURN VALUE
 * 
 * Functions can return values to the caller using the 'return' statement.
 * The return type must match the function's declared return type.
 * 
 * @param a First number to add (int)
 * @param b Second number to add (int)
 * @return The sum of a and b (int)
 */
int add(int a, int b) {
    return a + b;  // Return the sum of the two parameters
}

/*
 * FUNCTION WITH MULTIPLE PARAMETERS
 * 
 * Functions can have multiple parameters of different types.
 * Parameters are separated by commas.
 * 
 * @param length The length of the rectangle (double)
 * @param width The width of the rectangle (double)
 * @return The area of the rectangle (double)
 */
double calculateArea(double length, double width) {
    return length * width;  // Calculate and return the area
}

/*
 * FUNCTION WITH DIFFERENT RETURN TYPES
 * 
 * Functions can return different data types based on their purpose.
 * This function returns a string based on a numeric score.
 * 
 * @param score The numeric score (int)
 * @return The letter grade corresponding to the score (string)
 */
string getGrade(int score) {
    // Use if-else chain to determine grade
    if (score >= 90) return "A";      // 90-100 gets A
    else if (score >= 80) return "B"; // 80-89 gets B
    else if (score >= 70) return "C"; // 70-79 gets C
    else if (score >= 60) return "D"; // 60-69 gets D
    else return "F";                  // Below 60 gets F
}

/*
 * FUNCTION THAT DOESN'T RETURN ANYTHING (VOID)
 * 
 * Void functions perform actions but don't return values.
 * They're useful for printing, calculations that don't need results,
 * or any task that doesn't produce a value to return.
 * 
 * @param start The starting number for the range (int)
 * @param end The ending number for the range (int)
 */
void printNumbers(int start, int end) {
    cout << "Numbers from " << start << " to " << end << ": ";
    
    // Loop through the range and print each number
    for (int i = start; i <= end; i++) {
        cout << i << " ";  // Print current number followed by space
    }
    cout << endl;  // Move to next line after printing all numbers
}

/*
 * FUNCTION WITH LOCAL VARIABLES
 * 
 * Local variables are declared inside functions and only exist
 * while the function is executing. They're not accessible outside the function.
 * 
 * @param n The number to calculate factorial for (int)
 * @return The factorial of n (int)
 */
int factorial(int n) {
    int result = 1;  // Local variable to store the result
    
    // Calculate factorial: n! = 1 * 2 * 3 * ... * n
    for (int i = 1; i <= n; i++) {
        result *= i;  // Multiply result by current value of i
    }
    
    return result;  // Return the calculated factorial
}

/*
 * FUNCTION THAT CALLS OTHER FUNCTIONS
 * 
 * Functions can call other functions, creating a hierarchy of function calls.
 * This allows for code reuse and modular design.
 * 
 * This function demonstrates calling multiple other functions.
 */
void demonstrateFunctions() {
    cout << "This function demonstrates calling other functions:" << endl;
    
    sayHello();                    // Call the sayHello function
    greet("Alice");                // Call the greet function with "Alice"
    cout << "5 + 3 = " << add(5, 3) << endl;  // Call add function and display result
}

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various ways to use functions in C++.
 * It shows function calls, parameter passing, return values, and
 * how functions can work together to solve problems.
 */
int main() {
    // Display program header
    cout << "=== FUNCTION BEGINNER EXAMPLES ===" << endl << endl;
    
    /*
     * EXAMPLE 1: BASIC FUNCTION CALLS
     * 
     * This demonstrates the simplest way to call functions:
     * - Functions with no parameters
     * - Functions with parameters
     * - Functions that don't return values (void functions)
     */
    cout << "1. Basic Function Calls:" << endl;
    
    sayHello();        // Call function with no parameters
    greet("Bob");      // Call function with one parameter
    cout << endl;
    
    /*
     * EXAMPLE 2: FUNCTIONS WITH PARAMETERS AND RETURN VALUES
     * 
     * This demonstrates how to:
     * - Pass parameters to functions
     * - Capture return values from functions
     * - Use functions in expressions
     */
    cout << "2. Functions with Parameters and Return Values:" << endl;
    
    // Call add function and store the result
    int sum = add(10, 20);
    cout << "Sum of 10 and 20: " << sum << endl;
    
    // Call calculateArea function and store the result
    double area = calculateArea(5.5, 3.2);
    cout << "Area of rectangle (5.5 x 3.2): " << area << endl;
    cout << endl;
    
    /*
     * EXAMPLE 3: FUNCTIONS WITH DIFFERENT DATA TYPES
     * 
     * This demonstrates how functions can work with different data types:
     * - Functions can take different types as parameters
     * - Functions can return different types
     * - The same function can be called with different values
     */
    cout << "3. Functions with Different Data Types:" << endl;
    
    // Test getGrade function with different scores
    int score = 85;
    string grade = getGrade(score);  // Call function and store result
    cout << "Score " << score << " gets grade: " << grade << endl;
    
    // Test with a different score
    score = 95;
    grade = getGrade(score);  // Call function again with new score
    cout << "Score " << score << " gets grade: " << grade << endl;
    cout << endl;
    
    /*
     * EXAMPLE 4: FUNCTIONS WITH LOOPS
     * 
     * This demonstrates how functions can contain control structures:
     * - Functions can have loops inside them
     * - Functions can perform repetitive tasks
     * - Functions can be called multiple times with different parameters
     */
    cout << "4. Functions with Loops:" << endl;
    
    printNumbers(1, 5);    // Call function to print numbers 1-5
    printNumbers(10, 15);  // Call function to print numbers 10-15
    cout << endl;
    
    /*
     * EXAMPLE 5: FUNCTIONS WITH CALCULATIONS
     * 
     * This demonstrates how functions can perform complex calculations:
     * - Functions can have local variables
     * - Functions can use loops for calculations
     * - Functions can return calculated results
     */
    cout << "5. Functions with Calculations:" << endl;
    
    // Calculate factorial of 5
    int num = 5;
    int fact = factorial(num);  // Call factorial function
    cout << "Factorial of " << num << " is: " << fact << endl;
    
    // Calculate factorial of 7
    num = 7;
    fact = factorial(num);  // Call factorial function again
    cout << "Factorial of " << num << " is: " << fact << endl;
    cout << endl;
    
    /*
     * EXAMPLE 6: FUNCTIONS CALLING OTHER FUNCTIONS
     * 
     * This demonstrates function composition:
     * - Functions can call other functions
     * - This creates a hierarchy of function calls
     * - Functions can be combined to create more complex behavior
     */
    cout << "6. Functions Calling Other Functions:" << endl;
    
    demonstrateFunctions();  // Call function that calls other functions
    cout << endl;
    
    /*
     * EXAMPLE 7: MULTIPLE FUNCTION CALLS
     * 
     * This demonstrates how functions can be used repeatedly:
     * - The same function can be called multiple times
     * - Functions can be used in different contexts
     * - Functions make code more organized and readable
     */
    cout << "7. Multiple Function Calls:" << endl;
    
    // Demonstrate multiple calls to add function
    cout << "Math operations:" << endl;
    cout << "2 + 3 = " << add(2, 3) << endl;      // Call add function
    cout << "7 + 8 = " << add(7, 8) << endl;      // Call add function again
    cout << "12 + 15 = " << add(12, 15) << endl;  // Call add function again
    
    // Demonstrate multiple calls to calculateArea function
    cout << "\nArea calculations:" << endl;
    cout << "Square (4x4): " << calculateArea(4, 4) << endl;    // Call calculateArea
    cout << "Rectangle (6x3): " << calculateArea(6, 3) << endl; // Call calculateArea
    cout << "Rectangle (8x2): " << calculateArea(8, 2) << endl; // Call calculateArea
    
    // Return 0 to indicate successful program execution
    return 0;
}
