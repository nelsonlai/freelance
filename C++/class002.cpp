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
 * This program demonstrates how to read user input.
 */
#include <stdio.h>

int main() {
    int age;

    printf("Enter your age: ");
    scanf("%d", &age);
    printf("You entered the age: %d\n", age);

    double radius;
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    printf("The area of the circle is: %.2lf\n", 3.14159 * radius * radius);

    return 0;
}