/*
 * FUNCTION EXAMPLES - COMPREHENSIVE DEMONSTRATION
 * 
 * This file demonstrates various function concepts and usage patterns in C++:
 * - Basic function declaration and definition
 * - Function parameters and return values
 * - Default parameters and function overloading
 * - Pass by reference and pass by value
 * - Recursive functions and iterative alternatives
 * - Variadic functions with variable arguments
 * 
 * Learning Objectives:
 * - Understand fundamental function concepts
 * - Learn proper function syntax and implementation
 * - Master different parameter passing techniques
 * - Apply recursive and iterative approaches
 * - Develop problem-solving skills with functions
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and parameters
 * 
 * Key Topics Covered:
 * - Function declaration and definition
 * - Parameter passing (value vs reference)
 * - Default parameters
 * - Recursive programming
 * - Variadic functions
 * - Function overloading
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <cstdarg>   // For variadic functions (va_list, va_start, etc.)
using namespace std; // Using standard namespace (for beginners)

/*
 * BASIC FUNCTION WITH PARAMETERS AND RETURN VALUE
 * 
 * This function demonstrates the most basic function structure:
 * - Takes two integer parameters
 * - Returns an integer value
 * - Performs a simple mathematical operation
 * 
 * @param a First integer to add
 * @param b Second integer to add
 * @return The sum of a and b
 */
int add(int a, int b) {
    return a + b;  // Return the sum of the two parameters
}

/*
 * VOID FUNCTION (NO RETURN VALUE)
 * 
 * This function demonstrates a void function that performs an action
 * but doesn't return a value. Useful for printing, calculations that
 * don't need results, or any task that doesn't produce a value.
 */
void greet() {
    cout << "Hello, World!" << endl;  // Print greeting message
}

/*
 * FUNCTION WITH DEFAULT PARAMETERS
 * 
 * This function demonstrates default parameter usage:
 * - One parameter has a default value (b = 2)
 * - Can be called with one or two arguments
 * - Default value is used when parameter is not provided
 * 
 * @param a First integer to multiply
 * @param b Second integer to multiply (defaults to 2)
 * @return The product of a and b
 */
int multiply(int a, int b = 2) {
    return a * b;  // Return the product of the two parameters
}

/*
 * FUNCTION WITH REFERENCE PARAMETER
 * 
 * This function demonstrates pass by reference:
 * - Parameter is passed by reference (int &x)
 * - Changes to the parameter affect the original variable
 * - No return value needed since we modify the original
 * 
 * @param x Reference to integer to increment
 */
void increment(int &x) {
    x += 1;  // Increment the referenced variable
}

/*
 * RECURSIVE FACTORIAL FUNCTION
 * 
 * This function demonstrates recursion:
 * - Calls itself with a smaller value
 * - Has a base case to stop recursion
 * - Implements factorial: n! = n * (n-1)!
 * 
 * @param n The number to calculate factorial for
 * @return The factorial of n
 */
int factorialRecursive(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n <= 1) return 1;
    
    // Recursive case: n! = n * (n-1)!
    return n * factorialRecursive(n - 1);
}

/*
 * ITERATIVE FACTORIAL FUNCTION
 * 
 * This function demonstrates the iterative approach to factorial:
 * - Uses a loop instead of recursion
 * - More memory efficient than recursive version
 * - Same result as recursive version
 * 
 * @param n The number to calculate factorial for
 * @return The factorial of n
 */
int factorialIterative(int n) {
    int result = 1;  // Initialize result to 1
    
    // Multiply by all numbers from 1 to n
    for (int i = 1; i <= n; ++i) {
        result *= i;  // Multiply result by current value of i
    }
    
    return result;  // Return the calculated factorial
}

/*
 * VARIADIC FUNCTION (VARIABLE ARGUMENTS)
 * 
 * This function demonstrates variadic functions that can accept
 * a variable number of arguments. Uses C-style variadic arguments.
 * 
 * @param count Number of arguments to sum
 * @param ... Variable number of integer arguments
 * @return The sum of all provided integers
 */
int sum(int count, ...) {
    va_list args;           // Variable argument list
    va_start(args, count);  // Initialize argument list
    
    int total = 0;  // Initialize sum to 0
    
    // Sum all provided arguments
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int);  // Get next integer argument
    }
    
    va_end(args);  // Clean up argument list
    return total;  // Return the calculated sum
}

/*
 * MAIN FUNCTION - FUNCTION DEMONSTRATIONS
 * 
 * This function demonstrates all the different types of functions
 * defined above. It shows various function calling patterns and
 * their expected outputs.
 */
int main() {
    cout << "=== FUNCTION EXAMPLES DEMONSTRATION ===" << endl << endl;
    
    /*
     * DEMONSTRATION 1: BASIC FUNCTION WITH PARAMETERS
     */
    cout << "1. Basic Function with Parameters:" << endl;
    cout << "Sum: " << add(3, 5) << endl;  // Call add function with 3 and 5
    cout << endl;
    
    /*
     * DEMONSTRATION 2: VOID FUNCTION
     */
    cout << "2. Void Function:" << endl;
    greet();  // Call greet function (no parameters, no return value)
    cout << endl;
    
    /*
     * DEMONSTRATION 3: DEFAULT PARAMETERS
     */
    cout << "3. Default Parameters:" << endl;
    cout << "multiply(5): " << multiply(5) << endl;        // Uses default b=2
    cout << "multiply(5, 4): " << multiply(5, 4) << endl;  // Uses provided b=4
    cout << endl;
    
    /*
     * DEMONSTRATION 4: PASS BY REFERENCE
     */
    cout << "4. Pass by Reference:" << endl;
    int num = 10;  // Initialize variable
    cout << "Before increment: " << num << endl;
    increment(num);  // Call function that modifies the original variable
    cout << "After increment: " << num << endl;
    cout << endl;
    
    /*
     * DEMONSTRATION 5: RECURSIVE VS ITERATIVE
     */
    cout << "5. Recursive vs Iterative Factorial:" << endl;
    int n = 5;  // Calculate factorial of 5
    cout << "Factorial of " << n << " (recursive): " << factorialRecursive(n) << endl;
    cout << "Factorial of " << n << " (iterative): " << factorialIterative(n) << endl;
    cout << endl;
    
    /*
     * DEMONSTRATION 6: VARIADIC FUNCTION
     */
    cout << "6. Variadic Function:" << endl;
    cout << "sum(3, 1, 2, 3): " << sum(3, 1, 2, 3) << endl;                    // Sum 3 numbers
    cout << "sum(5, 10, 20, 30, 40, 50): " << sum(5, 10, 20, 30, 40, 50) << endl;  // Sum 5 numbers
    cout << endl;
    
    // Return 0 to indicate successful program execution
    return 0;
}