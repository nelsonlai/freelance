/*
 * HAPPY NUMBER ALGORITHM IMPLEMENTATION
 * 
 * This file demonstrates the Happy Number algorithm with multiple approaches:
 * - Mathematical problem solving
 * - Cycle detection algorithms
 * - Hash set usage for tracking
 * - Floyd's cycle detection algorithm
 * - Input validation and user interaction
 * 
 * Learning Objectives:
 * - Understand the Happy Number mathematical concept
 * - Learn cycle detection algorithms
 * - Master hash set usage for tracking visited numbers
 * - Apply Floyd's cycle detection technique
 * - Develop problem-solving skills with mathematical algorithms
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of loops and conditionals
 * - Familiarity with data structures (unordered_set)
 * - Basic understanding of mathematical algorithms
 * 
 * Key Topics Covered:
 * - Happy Number algorithm
 * - Cycle detection techniques
 * - Hash set operations
 * - Floyd's cycle detection
 * - Mathematical problem solving
 */

/*
 * PROBLEM DESCRIPTION
 * 
 * A happy number is a number defined by the following process:
 * 1. Starting with any positive integer, replace the number by the sum of the squares of its digits
 * 2. Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle
 * 3. Those numbers for which this process ends in 1 are happy
 * 
 * Examples:
 * - 19 is happy: 1² + 9² = 82 → 8² + 2² = 68 → 6² + 8² = 100 → 1² + 0² + 0² = 1
 * - 2 is not happy: enters a cycle that doesn't include 1
 */

#include <iostream>      // For input/output operations (cout, cin)
#include <unordered_set> // For hash set data structure

using namespace std; // Using standard namespace

/*
 * HELPER FUNCTION: SUM OF SQUARES OF DIGITS
 * 
 * This function calculates the sum of squares of all digits in a number.
 * It extracts each digit using modulo and division operations.
 * 
 * @param n The number to process
 * @return The sum of squares of all digits
 */
int sumOfSquares(int n) {
    int sum = 0;  // Initialize sum to 0
    
    // Process each digit of the number
    while (n > 0) {
        int digit = n % 10;        // Extract the last digit
        sum += digit * digit;      // Add square of digit to sum
        n /= 10;                   // Remove the last digit
    }
    
    return sum;  // Return the calculated sum
}

/*
 * HAPPY NUMBER DETECTION USING HASH SET
 * 
 * This function determines if a number is happy using a hash set to detect cycles.
 * It keeps track of all numbers seen during the process to detect infinite loops.
 * 
 * @param n The number to check
 * @return true if the number is happy, false otherwise
 */
bool isHappy(int n) {
    unordered_set<int> seen;  // Hash set to track seen numbers
    
    // Continue until we reach 1 or detect a cycle
    while (n != 1 && !seen.count(n)) {
        seen.insert(n);           // Mark current number as seen
        n = sumOfSquares(n);      // Calculate next number in sequence
    }
    
    return n == 1;  // Return true if we reached 1
}

/*
 * HAPPY NUMBER DETECTION USING FLOYD'S CYCLE DETECTION
 * 
 * This function uses Floyd's cycle detection algorithm (tortoise and hare) to detect cycles.
 * It uses two pointers moving at different speeds to detect cycles without extra space.
 * 
 * @param n The number to check
 * @return true if the number is happy, false otherwise
 */
bool isHappyFloyd(int n) {
    int slow = n;                    // Slow pointer (tortoise)
    int fast = sumOfSquares(n);      // Fast pointer (hare)
    
    // Move pointers until they meet or reach 1
    while (fast != 1 && fast != slow) {
        slow = sumOfSquares(slow);                    // Move slow pointer 1 step
        fast = sumOfSquares(sumOfSquares(fast));      // Move fast pointer 2 steps
    }
    
    return fast == 1;  // Return true if fast pointer reached 1
}

/*
 * MAIN FUNCTION - HAPPY NUMBER CHECKER
 * 
 * This function provides an interactive interface for checking if a number is happy.
 * It demonstrates both approaches to solving the happy number problem.
 */
int main() {
    int num;  // Variable to store user input
    
    // Get number from user
    cout << "Enter a number: ";
    cin >> num;
    
    // Check if the number is happy using hash set approach
    if (isHappy(num)) {
        cout << num << " is a happy number." << endl;
    } else {
        cout << num << " is not a happy number." << endl;
    }
    
    // Return 0 to indicate successful program execution
    return 0;
}

/*

#include <iostream>

using namespace std;

int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n;
    int fast = sumOfSquares(n);

    while (fast != 1 && slow != fast) {
        slow = sumOfSquares(slow);           // move 1 step
        fast = sumOfSquares(sumOfSquares(fast)); // move 2 steps
    }

    return fast == 1;
}

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (isHappy(num)) {
        cout << num << " is a happy number." << endl;
    } else {
        cout << num << " is not a happy number." << endl;
    }

    return 0;
}

*/