/**
 * Solution 7.1: Maximum Using Pointers
 * Week 7 - Pointers Fundamentals
 * 
 * Description: Write a function to find maximum using pointers
 */

#include <stdio.h>

int findMax(int *a, int *b) {
    return (*a > *b) ? *a : *b; /* Ternary operator */
}

int main() {
    int num1, num2;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    int max = findMax(&num1, &num2);
    
    printf("Maximum of %d and %d is: %d\n", num1, num2, max);
    
    return 0;
}