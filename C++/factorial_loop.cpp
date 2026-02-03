/*
 * FACTORIAL CALCULATION USING LOOPS
 * 
 * This file demonstrates factorial calculation using iterative approach:
 * - Loop-based factorial computation
 * - Variable initialization and iteration
 * - Mathematical operations and accumulation
 * - Input/output operations
 * 
 * Learning Objectives:
 * - Understand factorial mathematical concept
 * - Learn iterative loop implementation
 * - Master variable accumulation patterns
 * - Apply mathematical operations in programming
 * - Develop problem-solving skills with loops
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of variables and data types
 * - Familiarity with for loops
 * - Basic understanding of mathematical operations
 * 
 * Key Topics Covered:
 * - Factorial calculation algorithm
 * - Loop iteration and control
 * - Variable accumulation
 * - Mathematical operations
 * - Input/output formatting
 */

#include <iostream>  // For input/output operations (cout)
using namespace std; // Using standard namespace (for beginners)

/*
 * MAIN FUNCTION - FACTORIAL CALCULATION
 * 
 * This function calculates the factorial of a given number using an iterative approach.
 * Factorial of n (n!) is the product of all positive integers from 1 to n.
 * 
 * Algorithm:
 * 1. Initialize factorial result to 1
 * 2. Iterate from 1 to the target number
 * 3. Multiply current result by current iteration value
 * 4. Display the final result
 */
int main() {
    /*
     * VARIABLE DECLARATION AND INITIALIZATION
     * 
     * Initialize variables for factorial calculation:
     * - factorial: accumulates the result (starts at 1)
     * - number: the value to calculate factorial for
     */
    int factorial = 1;  // Initialize factorial result to 1 (0! = 1, 1! = 1)
    int number = 12;    // Set the number to calculate factorial for
    
    /*
     * ITERATIVE FACTORIAL CALCULATION
     * 
     * Use a for loop to calculate factorial iteratively:
     * - Start from i = 1 (first positive integer)
     * - Continue until i <= number (inclusive)
     * - Multiply factorial by current value of i
     * - This implements: n! = 1 × 2 × 3 × ... × n
     */
    for (int i = 1; i <= number; i++) {
        factorial *= i;  // Multiply current factorial by i
        // This is equivalent to: factorial = factorial * i
    }
    
    /*
     * DISPLAY RESULTS
     * 
     * Output the calculated factorial with proper formatting.
     * The result shows both the input number and its factorial.
     */
    cout << "Factorial of " << number << " is: " << factorial;
    
    // Return 0 to indicate successful program execution
    return 0;
}