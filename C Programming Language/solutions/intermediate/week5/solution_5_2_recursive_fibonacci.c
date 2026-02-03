/**
 * Solution 5.2: Recursive Fibonacci
 * Week 5 - Functions and Modular Programming
 * 
 * Description: Write a recursive function for Fibonacci series
 * f(n) = f(n-1) + f(n-2)
 * f(0) = 0
 * f(1) = 1
 */

#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int terms;
    
    printf("Enter number of terms: ");
    scanf("%d", &terms);
    
    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    
    return 0;
}
