/*
 * C++ PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates C++ programming concepts and techniques:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental C++ PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

#include <stdio.h>

int main() {
    int a = 5, b = 5; // a++; ++a;

    printf("Initial values: a = %d, b = %d\n", a, b);

    // Pre-increment (++i)
    printf("\n--- Pre-increment (++a) ---\n");
    printf("Value returned: %d\n", ++a);  // a is incremented first, then returned
    printf("Value of a after operation: %d\n", a);

    // Post-increment (i++)
    printf("\n--- Post-increment (b++) ---\n");
    printf("Value returned: %d\n", b++);  // b is returned first, then incremented
    printf("Value of b after operation: %d\n", b);

    // Demonstrating in an expression
    int x = 5, y = 5, result1, result2;

    result1 = ++x * 2; // increment x first, then multiply by 2 ==> x = 6, result1 = 12
    result2 = y++ * 2; // multiply y first, then increment ==>  ( 5 * 2 ) = 10, y = 6

    printf("\n--- In expressions ---\n");
    printf("result1 = ++x * 2 => %d (x = %d)\n", result1, x);
    printf("result2 = y++ * 2 => %d (y = %d)\n", result2, y);

    return 0;
}