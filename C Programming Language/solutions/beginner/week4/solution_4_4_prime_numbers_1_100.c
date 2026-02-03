/**
 * Solution 4.4: Prime Numbers 1-100
 * Week 4 - Loops and Problem Solving
 * 
 * Description: Print all prime numbers between 1 and 100
 */

#include <stdio.h>

int main() {
    int isPrime;
    
    printf("Prime numbers between 1 and 100:\n");
    
    for (int num = 2; num <= 100; num++) {
        isPrime = 1;  // Assume number is prime
        
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;  // Number is not prime
                break;
            }
        }
        
        if (isPrime) {
            printf("%d ", num);
        }
    }
    printf("\n");
    
    return 0;
}
