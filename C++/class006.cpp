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

/*
 * This program demonstrates the use of if - else if - else in C.
 */
#include <stdio.h>

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n > 0) {
        printf("%d is positive.\n", n);
    } else if (n < 0) {
        printf("%d is negative.\n", n);
    } else {
        printf("You entered zero.\n");
    }

    return 0;
}
