/*
 * LAMBDA BEGINNER EXAMPLES
 * 
 * This file demonstrates basic lambda function concepts in C++:
 * - Basic lambda syntax and declaration
 * - Lambda parameters and return types
 * - Capture modes (by value and by reference)
 * - Lambda functions with STL algorithms
 * - Practical applications of lambdas
 * 
 * Learning Objectives:
 * - Understand what lambda functions are and why they're useful
 * - Learn basic lambda syntax and declaration
 * - Master different capture modes
 * - Understand how to use lambdas with STL algorithms
 * - Learn when and how to use lambda functions effectively
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of functions and variables
 * - Familiarity with STL containers and algorithms
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <vector>    // For vector container
#include <algorithm> // For STL algorithms (count_if, find_if, for_each, transform, sort)
using namespace std; // Using standard namespace (for beginners)

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various ways to use lambda functions in C++.
 * Lambda functions are anonymous functions that can be defined inline
 * and are particularly useful with STL algorithms and functional programming.
 */
int main() {
    // Display program header
    cout << "=== LAMBDA BEGINNER EXAMPLES ===" << endl << endl;
    
    /*
     * EXAMPLE 1: BASIC LAMBDA SYNTAX
     * 
     * This demonstrates the most basic lambda function:
     * - [] is the capture clause (empty in this case)
     * - () is the parameter list (empty in this case)
     * - {} contains the function body
     * - auto keyword lets the compiler deduce the type
     * 
     * Lambda syntax: [capture](parameters) -> return_type { body }
     */
    cout << "1. Basic Lambda Syntax:" << endl;
    
    // Create a lambda function with no parameters and no return value
    auto simpleLambda = []() {
        cout << "Hello from lambda!" << endl;  // Lambda body
    };
    
    simpleLambda();  // Call the lambda function
    cout << endl;
    
    /*
     * EXAMPLE 2: LAMBDA WITH PARAMETERS
     * 
     * This demonstrates lambda functions with parameters:
     * - Parameters are declared in parentheses
     * - Return type is automatically deduced
     * - Lambda can be called like a regular function
     */
    cout << "2. Lambda with Parameters:" << endl;
    
    // Create a lambda function that takes two integers and returns their sum
    auto add = [](int a, int b) {
        return a + b;  // Return the sum of parameters
    };
    
    // Call the lambda function with different arguments
    cout << "5 + 3 = " << add(5, 3) << endl;    // Call lambda with 5 and 3
    cout << "10 + 7 = " << add(10, 7) << endl;  // Call lambda with 10 and 7
    cout << endl;
    
    /*
     * EXAMPLE 3: LAMBDA WITH EXPLICIT RETURN TYPE
     * 
     * This demonstrates how to specify the return type explicitly:
     * - Use -> return_type after the parameter list
     * - Useful when the compiler can't deduce the return type
     * - Makes the code more readable and explicit
     */
    cout << "3. Lambda with Explicit Return Type:" << endl;
    
    // Create a lambda function with explicit double return type
    auto multiply = [](double x, double y) -> double {
        return x * y;  // Return the product of parameters
    };
    
    // Call the lambda function with double values
    cout << "2.5 * 4.0 = " << multiply(2.5, 4.0) << endl;    // Call with 2.5 and 4.0
    cout << "3.14 * 2.0 = " << multiply(3.14, 2.0) << endl;  // Call with 3.14 and 2.0
    cout << endl;
    
    /*
     * EXAMPLE 4: LAMBDA WITH CAPTURE BY VALUE
     * 
     * This demonstrates how to capture variables from the surrounding scope:
     * - [multiplier] captures the variable by value
     * - The lambda gets a copy of the variable
     * - Changes to the original variable don't affect the lambda
     */
    cout << "4. Lambda with Capture by Value:" << endl;
    
    int multiplier = 5;  // Variable to be captured
    
    // Create a lambda that captures multiplier by value
    auto multiplyBy = [multiplier](int x) {
        return x * multiplier;  // Use the captured multiplier value
        multiplier = 10;  // This will cause a compilation error
    };
    
    // Call the lambda function
    cout << "Multiply 3 by " << multiplier << ": " << multiplyBy(3) << endl;
    cout << "Multiply 7 by " << multiplier << ": " << multiplyBy(7) << endl;
    cout << endl;
    
    /*
     * EXAMPLE 5: LAMBDA WITH CAPTURE BY REFERENCE
     * 
     * This demonstrates how to capture variables by reference:
     * - [&counter] captures the variable by reference
     * - The lambda can modify the original variable
     * - Changes made in the lambda affect the original variable
     */
    cout << "5. Lambda with Capture by Reference:" << endl;
    
    int counter = 0;  // Variable to be captured by reference
    
    // Create a lambda that captures counter by reference
    auto increment = [&counter]() {
        counter++;  // Modify the original counter variable
        cout << "Counter is now: " << counter << endl;
    };
    
    // Call the lambda function multiple times
    increment();  // Counter becomes 1
    increment();  // Counter becomes 2
    increment();  // Counter becomes 3
    
    cout << "Final counter value: " << counter << endl;  // Should be 3
    cout << endl;
    
    /*
     * EXAMPLE 6: LAMBDA WITH STL ALGORITHMS
     * 
     * This demonstrates how lambda functions work with STL algorithms:
     * - count_if: counts elements that satisfy a condition
     * - find_if: finds the first element that satisfies a condition
     * - Lambdas are perfect for providing custom predicates
     */
    cout << "6. Lambda with STL Algorithms:" << endl;
    
    // Create a vector of numbers
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Display the original numbers
    cout << "Original numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Count even numbers using count_if with a lambda predicate
    int evenCount = count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;  // Return true if n is even
    });
    cout << "Number of even numbers: " << evenCount << endl;
    
    // Find first number greater than 5 using find_if with a lambda predicate
    auto it = find_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5;  // Return true if n > 5
    });
    if (it != numbers.end()) {
        cout << "First number greater than 5: " << *it << endl;
    }
    cout << endl;
    
    /*
     * EXAMPLE 7: LAMBDA WITH FOR_EACH
     * 
     * This demonstrates how to use lambda functions with for_each:
     * - for_each applies a function to each element
     * - Lambda can perform any operation on each element
     * - Useful for side effects like printing or modifying elements
     */
    cout << "7. Lambda with for_each:" << endl;
    
    // Create a vector of words
    vector<string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    // Print all words using for_each with a lambda
    cout << "Words in uppercase: ";
    for_each(words.begin(), words.end(), [](const string& word) {
        cout << word << " ";  // Print each word
    });
    cout << endl;
    
    // Print words with their lengths using for_each with a lambda
    cout << "Words with length: ";
    for_each(words.begin(), words.end(), [](const string& word) {
        cout << word << "(" << word.length() << ") ";  // Print word and its length
    });
    cout << endl;
    cout << endl;
    
    /*
     * EXAMPLE 8: LAMBDA WITH TRANSFORM
     * 
     * This demonstrates how to use lambda functions with transform:
     * - transform applies a function to each element and stores the result
     * - Lambda defines the transformation to apply
     * - Results are stored in a destination container
     */
    cout << "8. Lambda with transform:" << endl;
    
    // Create source and destination vectors
    vector<int> original = {1, 2, 3, 4, 5};
    vector<int> doubled(original.size());  // Destination vector with same size
    
    // Transform each element by doubling it using a lambda
    transform(original.begin(), original.end(), doubled.begin(), [](int x) {
        return x * 2;  // Return doubled value
    });
    
    // Display original and transformed vectors
    cout << "Original: ";
    for (int num : original) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "Doubled: ";
    for (int num : doubled) {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;
    
    /*
     * EXAMPLE 9: LAMBDA WITH SORT
     * 
     * This demonstrates how to use lambda functions with sort:
     * - sort uses a comparison function to determine order
     * - Lambda defines the comparison criteria
     * - Can implement custom sorting logic
     */
    cout << "9. Lambda with sort:" << endl;
    
    // Create a vector of unsorted numbers
    vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    
    // Display numbers before sorting
    cout << "Before sorting: ";
    for (int num : unsorted) {
        cout << num << " ";
    }
    cout << endl;
    
    // Sort using a lambda comparison function
    sort(unsorted.begin(), unsorted.end(), [](int a, int b) {
        return a < b;  // Return true if a should come before b (ascending order)
    });
    
    // Display numbers after sorting
    cout << "After sorting: ";
    for (int num : unsorted) {
        cout << num << " ";
    }
    cout << endl;
    
    // Return 0 to indicate successful program execution
    return 0;
}
