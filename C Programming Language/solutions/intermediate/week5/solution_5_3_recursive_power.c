/**
 * Solution 5.3: Recursive Power Function
 * Week 5 - Functions and Modular Programming
 * 
 * Description: Implement power function (x^y) using recursion
 */

#include <stdio.h>

double power(double base, int exponent) {
    if (exponent == 0) {
        return 1;
    } else if (exponent > 0) {
        return base * power(base, exponent - 1);
    } else {
        return 1 / power(base, -exponent);
    }
}

int main() {
    double base;
    int exponent;
    
    printf("Enter base: ");
    scanf("%lf", &base);
    
    printf("Enter exponent: ");
    scanf("%d", &exponent);
    
    printf("%.2f^%d = %.2f\n", base, exponent, power(base, exponent));
    
    return 0;
}
