/*
 * DATA TYPE EXAMPLES
 * 
 * This file demonstrates basic data type concepts in C++:
 * - Different primitive data types
 * - Size of data types using sizeof operator
 * - Type information using typeid operator
 * - Variable declaration and initialization
 * 
 * Learning Objectives:
 * - Understand different C++ data types
 * - Learn how to check the size of data types
 * - Master variable declaration and initialization
 * - Understand type information and identification
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of variables
 * - Familiarity with input/output operations
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
#include <typeinfo>  // For type information (typeid operator)
using namespace std; // Using standard namespace (for beginners)

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various data types and their properties.
 * It shows how to check the size and type of different variables.
 */
int main() {
    /*
     * INTEGER DATA TYPE DEMONSTRATION
     * 
     * This section demonstrates integer data type properties:
     * - Declaration and initialization
     * - Size checking with sizeof operator
     * - Type identification with typeid operator
     */
    
    int x = 47385;  // Declare and initialize integer variable
    
    // Display the size of the variable x in bytes
    cout << "Size of variable x: " << sizeof(x) << " bytes" << endl;
    
    // Display the type name of variable x
    cout << "Type of x: " << typeid(x).name() << endl;
    
    // Display the size of int data type in bytes
    cout << "Size of int data type: " << sizeof(int) << " bytes" << endl;
    cout << endl;  // Add blank line for readability
    
    /*
     * CHARACTER DATA TYPE DEMONSTRATION
     * 
     * This section demonstrates character data type properties.
     * Note: 'hello' is not a valid character literal - it should be 'h'
     * This demonstrates what happens with invalid character literals.
     */
    
    char c = 'hello';  // WARNING: This is invalid! Should be 'h' for single character
    
    // Display the size of the variable c in bytes
    cout << "Size of variable c: " << sizeof(c) << " bytes" << endl;
    
    // Display the type name of variable c
    cout << "Type of c: " << typeid(c).name() << endl;
    
    // Display the size of char data type in bytes
    cout << "Size of char data type: " << sizeof(char) << " bytes" << endl;
    
    // Return 0 to indicate successful program execution
    return 0;
}