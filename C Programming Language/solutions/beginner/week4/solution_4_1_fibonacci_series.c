/**
 * Solution 4.1: Fibonacci Series
 * Week 4 - Loops and Problem Solving
 * 
 * Description: Print Fibonacci series up to n terms
 */

/**
 * @brief Print Fibonacci series up to n terms
 * Write a program to print the Fibonacci series up to n terms by recursion way
 * @param n Number of terms
 * @return int 0 if successful
 */

/**
 * @brief Print Fibonacci series up to n terms
 * Write a program to print the Fibonacci series up to n terms by recursion way
 * @param n Number of terms
 * @return int 0 if successful
 * f(x) = f(x-1) + f(x-2)
 * f(0) = 0
 * f(1) = 1
 */
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

#include <stdio.h>

int main() {
    int n, first = 0, second = 1, next;
    
    printf("Enter number of terms: ");
    scanf("%d", &n);
    
    printf("Fibonacci Series: ");
    
    if (n >= 1) {
        printf("%d ", first);
    }
    if (n >= 2) {
        printf("%d ", second);
    }
    
    for (int i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }
    printf("\n");
    
    return 0;
}
