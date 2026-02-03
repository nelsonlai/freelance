/**
 * Solution 2.4: Swap Numbers Without Third Variable
 * Week 2 - Variables, Data Types, and Operators
 * 
 * Description: Swap two numbers without using a third variable
 */

#include <stdio.h>

int main() {
    int a, b;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    
    printf("Before swapping: a = %d, b = %d\n", a, b);
    
    // Swapping without third variable
    a = a + b;
    b = a - b;
    a = a - b;
    
    printf("After swapping: a = %d, b = %d\n", a, b);
    
    return 0;
}
