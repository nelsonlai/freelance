/**
 * Solution 3.4: Multiplication Table
 * Week 3 - Input/Output and Control Flow Basics
 * 
 * Description: Print multiplication table for a given number
 */

#include <stdio.h>

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    printf("Multiplication table of %d:\n", number);
    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", number, i, number * i);
    }
    
    return 0;
}
