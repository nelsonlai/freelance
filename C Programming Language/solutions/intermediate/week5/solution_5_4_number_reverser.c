/**
 * Solution 5.4: Number Reverser Function
 * Week 5 - Functions and Modular Programming
 * 
 * Description: Create a function to reverse a number
 */

#include <stdio.h>

int reverseNumber(int num) {
    int reversed = 0;
    
    while (num != 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    
    return reversed;
}

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    printf("Reversed number: %d\n", reverseNumber(number));
    
    return 0;
}
