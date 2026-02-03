/**
 * Solution 7.6: Function Pointers Comprehensive
 * Week 7 - Pointers Fundamentals
 * 
 * Description: Complete demonstration of function pointers in C
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <stdbool.h>
 
 // Function prototypes for basic operations
 int add(int a, int b) { return a + b; }
 int subtract(int a, int b) { return a - b; }
 int multiply(int a, int b) { return a * b; }
 int divide_op(int a, int b) { return a / b; }

 int main () {
     printf("\n=== Arrays of Function Pointers ===\n");
     
     // int (*math_function_pointers)(int, int) = add;
     // Array of function pointers (array of function pointers)
     int (*math_operations[])(int, int) = {add, subtract, multiply, divide_op};
     char *operation_names[] = {"Addition", "Subtraction", "Multiplication", "Division"};
     char operation_symbols[] = {'+', '-', '*', '/'};
     int num_operations = sizeof(math_operations) / sizeof(math_operations[0]);
     
     int x = 20, y = 4;
     printf("Performing operations on %d and %d:\n", x, y);
     
     for (int i = 0; i < num_operations; i++) {
         int result = math_operations[i](x, y);
         printf("%s (%c): %d\n", operation_names[i], operation_symbols[i], result);
     }

     return 0;
 }
 