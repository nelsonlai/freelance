/*
 * VECTOR BEGINNER EXAMPLES
 * 
 * This file demonstrates basic vector concepts including dynamic arrays, resizing, and STL algorithms:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced VECTOR concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic VECTOR concepts
 * - Familiarity with intermediate C++ features
 * - Understanding of memory management
 * - Knowledge of STL containers and algorithms
 * 
 * Key Topics Covered:
 * - Advanced syntax and features
 * - Performance optimization
 * - Error handling and safety
 * - Modern C++ practices
 * - Real-world applications
 */

/*
 * VECTOR BEGINNER EXAMPLES
 * 
 * This file demonstrates basic vector concepts in C++:
 * - Basic vector declaration and usage
 * - Adding and accessing elements
 * - Different initialization methods
 * - Vector operations and iteration
 * - Vectors with different data types
 * 
 * Learning Objectives:
 * - Understand what vectors are and how to use them
 * - Learn how to add, access, and modify vector elements
 * - Master different ways to initialize vectors
 * - Understand vector size and capacity
 * - Learn how to iterate through vectors
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <vector>    // For vector container
#include <string>    // For string data type
using namespace std; // Using standard namespace (for beginners)

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various ways to use vectors in C++.
 * Vectors are dynamic arrays that can grow and shrink as needed.
 * They are part of the Standard Template Library (STL) and provide
 * many useful methods for data manipulation.
 */
int main() {
    // Display program header
    cout << "=== VECTOR BEGINNER EXAMPLES ===" << endl << endl;
    
    // Example 1: Basic vector declaration and usage
    cout << "1. Basic Vector Declaration:" << endl;
    vector<int> numbers;
    
    // Adding elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);
    
    cout << "Vector elements: ";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "Vector size: " << numbers.size() << endl;
    cout << endl;
    
    // Example 2: Vector initialization
    cout << "2. Vector Initialization:" << endl;
    vector<string> fruits = {"Apple", "Banana", "Orange", "Grape"};
    
    cout << "Fruits: ";
    for (const string& fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl;
    cout << "Number of fruits: " << fruits.size() << endl;
    cout << endl;
    
    // Example 3: Accessing vector elements
    cout << "3. Accessing Vector Elements:" << endl;
    vector<double> prices = {1.99, 2.49, 3.99, 4.50, 5.25};
    
    cout << "Prices: ";
    for (size_t i = 0; i < prices.size(); i++) {
        cout << "$" << prices[i] << " ";
    }
    cout << endl;
    
    cout << "First price: $" << prices[0] << endl;
    cout << "Last price: $" << prices[prices.size() - 1] << endl;
    cout << "Middle price: $" << prices[prices.size() / 2] << endl;
    cout << endl;
    
    // Example 4: Vector with different data types
    cout << "4. Vector with Different Data Types:" << endl;
    vector<char> letters = {'A', 'B', 'C', 'D', 'E'};
    vector<bool> flags = {true, false, true, true, false};
    
    cout << "Letters: ";
    for (char letter : letters) {
        cout << letter << " ";
    }
    cout << endl;
    
    cout << "Flags: ";
    for (bool flag : flags) {
        cout << (flag ? "true" : "false") << " ";
    }
    cout << endl;
    cout << endl;
    
    // Example 5: Vector operations
    cout << "5. Vector Operations:" << endl;
    vector<int> scores = {85, 92, 78, 96, 88};
    
    cout << "Original scores: ";
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    // Add new score
    scores.push_back(91);
    cout << "After adding 91: ";
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    // Remove last element
    scores.pop_back();
    cout << "After removing last: ";
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    cout << endl;
    
    // Example 6: Vector of vectors (2D)
    cout << "6. Vector of Vectors (2D):" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    cout << "Matrix:" << endl;
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Example 7: Vector with user input
    cout << "7. Vector with User Input:" << endl;
    vector<string> names;
    string name;
    
    cout << "Enter names (type 'done' to finish):" << endl;
    while (true) {
        cout << "Name: ";
        getline(cin, name);
        if (name == "done") break;
        names.push_back(name);
    }
    
    cout << "You entered " << names.size() << " names:" << endl;
    for (size_t i = 0; i < names.size(); i++) {
        cout << (i + 1) << ". " << names[i] << endl;
    }
    
    return 0;
}
