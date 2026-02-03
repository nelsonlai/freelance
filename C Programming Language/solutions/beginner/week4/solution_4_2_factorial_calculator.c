/**
 * Solution 4.2: Factorial Calculator
 * Week 4 - Loops and Problem Solving
 * 
 * Description: Calculate factorial of a number
 */

/**
 * @file solution_4_2_factorial_calculator.c
 * @author [your name]
 * @brief Write a program to calculate the factorial of a number by recursion way
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

#include <stdio.h>

int main() {
    int number;
    long long factorial = 1;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (number < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        for (int i = 1; i <= number; i++) {
            factorial *= i;
        }
        printf("Factorial of %d = %lld\n", number, factorial);
    }
    
    return 0;
}
