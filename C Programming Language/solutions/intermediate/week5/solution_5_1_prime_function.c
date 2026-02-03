/**
 * Solution 5.1: Prime Number Function
 * Week 5 - Functions and Modular Programming
 * 
 * Description: Create a function to check if a number is prime
 */

#include <stdio.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;  // Not prime
    }
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;  // Not prime
        }
    }
    
    return 1;  // Prime
}

int main() {
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if (isPrime(number)) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is not a prime number.\n", number);
    }
    
    return 0;
}
