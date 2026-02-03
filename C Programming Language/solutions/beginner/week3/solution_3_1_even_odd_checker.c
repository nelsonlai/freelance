/**
 * Solution 3.1: Even or Odd Checker
 * Week 3 - Input/Output and Control Flow Basics
 * 
 * Description: Check if a number is even or odd
 */

#include <stdio.h>

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (number % 2 == 0) {
        printf("%d is even.\n", number);
    } else {
        printf("%d is odd.\n", number);
    }
    
    return 0;
}
