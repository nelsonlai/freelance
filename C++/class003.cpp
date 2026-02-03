/*
 * CLASS EXAMPLES EXAMPLES
 * 
 * This file demonstrates class concepts and object-oriented programming:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental CLASS concepts
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

/**
 * This program demonstrates the use of arithmetic operations and assignment in C.
 */
#include <stdio.h>
#include <math.h>

int main() {
    /* Arithmetic + assigment*/

    int x = 5, y = 2;
    int sum = x + y;
    int prod = x * y;
    int div = x / y;

    double div2 = (double) x / (double) y;

    printf("Sum: %d\n", sum);
    printf("Product: %d\n", prod);
    printf("Integer Division: %d\n", div);
    printf("Floating-point Division: %.3f\n", div2);

    return 0;
}
