/**
 * Solution 4.3: Palindrome Checker
 * Week 4 - Loops and Problem Solving
 * 
 * Description: Check if a number is palindrome
 */
 /*
 hannah
 85358
 */

#include <stdio.h>

int main() {
    int number, original, reversed = 0, remainder;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    original = number;
    
    while (number != 0) {
        remainder = number % 10;
        reversed = reversed * 10 + remainder;
        number /= 10;
    }
    
    if (original == reversed) {
        printf("%d is a palindrome.\n", original);
    } else {
        printf("%d is not a palindrome.\n", original);
    }
    
    return 0;
}
