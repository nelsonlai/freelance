/*
 * SWITCH-CASE STATEMENT DEMONSTRATION
 * 
 * This file demonstrates the switch-case control structure in C++:
 * - Basic switch-case syntax and usage
 * - Multiple case handling
 * - Character-based decision making
 * - User input processing
 * - Calculator implementation using switch-case
 * 
 * Learning Objectives:
 * - Understand switch-case control structure
 * - Learn character-based decision making
 * - Master user input handling
 * - Apply switch-case in practical applications
 * - Develop problem-solving skills with control structures
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of variables and data types
 * - Familiarity with input/output operations
 * - Basic understanding of control structures
 * 
 * Key Topics Covered:
 * - Switch-case syntax
 * - Character input processing
 * - Multiple case handling
 * - Break statement usage
 * - Default case handling
 */

#include <iostream>  // For input/output operations (cout, cin)
using namespace std; // Using standard namespace (for beginners)

/*
 * MAIN FUNCTION - CALCULATOR USING SWITCH-CASE
 * 
 * This function implements a simple calculator using switch-case statements.
 * It demonstrates how to use switch-case for character-based decision making
 * and how to handle multiple operations based on user input.
 */
int main() {
    /*
     * VARIABLE DECLARATION
     * 
     * Declare variables to store user input and operation choice.
     * - no1, no2: Store the two numbers for calculation
     * - button: Store the operation character (+,-,*,/)
     */
    int no1, no2;  // Variables to store the two numbers
    char button;   // Variable to store the operation character
    
    /*
     * USER INPUT COLLECTION
     * 
     * Get input from the user for the two numbers and the operation.
     * This demonstrates basic input/output operations in C++.
     */
    cout << "Enter two Numbers: ";  // Prompt user for two numbers
    cin >> no1 >> no2;              // Read two numbers from user
    
    cout << "Enter Action (+, -, *, /): ";  // Prompt user for operation
    cin >> button;                          // Read operation character from user
    
    /*
     * SWITCH-CASE DECISION MAKING
     * 
     * Use switch-case to perform different operations based on the
     * character input. Each case handles a specific operation.
     * 
     * Switch-case is more efficient than if-else chains when dealing
     * with multiple discrete values (like characters).
     */
    switch (button) {
        /*
         * ADDITION CASE
         * 
         * Handle addition operation when user enters '+'
         */
        case '+':
            cout << "Addition of Given Numbers: " << no1 + no2 << endl;
            break;  // Exit switch statement after handling this case
            
        /*
         * SUBTRACTION CASE
         * 
         * Handle subtraction operation when user enters '-'
         */
        case '-':
            cout << "Subtraction of Given Numbers: " << no1 - no2 << endl;
            break;  // Exit switch statement after handling this case
            
        /*
         * MULTIPLICATION CASE
         * 
         * Handle multiplication operation when user enters '*'
         */
        case '*':
            cout << "Multiplication of Given Numbers: " << no1 * no2 << endl;
            break;  // Exit switch statement after handling this case
            
        /*
         * DIVISION CASE
         * 
         * Handle division operation when user enters '/'
         * Note: This doesn't handle division by zero
         */
        case '/':
            if (no2 != 0) {
                cout << "Division of Given Numbers: " << no1 / no2 << endl;
            } else {
                cout << "Error: Division by zero is not allowed!" << endl;
            }
            break;  // Exit switch statement after handling this case
            
        /*
         * DEFAULT CASE
         * 
         * Handle any character that doesn't match the defined cases.
         * This provides error handling for invalid input.
         */
        default:
            cout << "Error: Invalid operation! Please use +, -, *, or /" << endl;
            break;  // Exit switch statement (optional for default case)
    }
    
    // Return 0 to indicate successful program execution
    return 0;
}