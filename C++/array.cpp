
/*
 * ARRAY OPERATIONS EXAMPLE
 * 
 * This file demonstrates basic array operations using C++ vectors:
 * - Vector declaration and initialization
 * - Traditional for loop iteration
 * - Element access and summation
 * - Basic vector operations
 * 
 * Learning Objectives:
 * - Understand how to create and initialize vectors
 * - Learn traditional for loop syntax for array iteration
 * - Master element access using index notation
 * - Understand basic array operations like summation
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types
 * - Familiarity with loops and variables
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <vector>    // For vector container (dynamic array)
using namespace std; // Using standard namespace (for beginners)

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates basic array operations using C++ vectors.
 * Vectors are dynamic arrays that can grow and shrink as needed,
 * making them more flexible than traditional C-style arrays.
 */
int main() {
    /*
     * VECTOR DECLARATION AND INITIALIZATION
     * 
     * This demonstrates how to create and initialize a vector with values.
     * The vector is declared as vector<int> which means it stores integers.
     * Initialization uses brace initialization syntax.
     */
    vector<int> arr = {15, 2, 5, 6, 8, 11};  // Create vector with 6 integer elements
    
    /*
     * TRADITIONAL FOR LOOP ITERATION
     * 
     * This demonstrates how to iterate through a vector using a traditional for loop.
     * We use the size() method to get the number of elements and access each element
     * using array notation with square brackets.
     * 
     * Key Points:
     * - arr.size() returns the number of elements (size_t type)
     * - We cast to int for the loop variable (not always necessary)
     * - Array indices start from 0 and go to size()-1
     * - We can access elements using arr[index] notation
     */
    int sum = 0;  // Initialize sum variable to store the total
    
    // Loop through all elements of the vector
    for (int i = 0; i < (int) arr.size(); i++) {
        sum += arr[i];  // Add current element to the sum
    }
    
    // Display the calculated sum
    cout << "Sum of all elements: " << sum << endl;
    
    // Return 0 to indicate successful program execution
    return 0;
}