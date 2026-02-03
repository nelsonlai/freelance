/*
 * This program demonstrates the use of function in C.
*/
#include <stdio.h>

void sayHello() {
    printf("Hello, World!\n");
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(int a, int b) {
    return (double) a / (double) b;
}

int main() {
    printf("Hello, World!\n");
    sayHello();
    printf("Sum of 3 and 5: %d\n", add(3, 5));
    printf("Difference of 3 and 5: %d\n", subtract(3, 5));
    printf("Product of 3 and 5: %d\n", multiply(3, 5));
    printf("Quotient of 3 and 5: %lf\n", divide(3, 5));
    return 0;
}