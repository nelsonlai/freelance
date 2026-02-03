/**
 * Solution 2.2: Temperature Converter
 * Week 2 - Variables, Data Types, and Operators
 * 
 * Description: Convert temperature from Fahrenheit to Celsius
 */

#include <stdio.h>

int main() {
    float fahrenheit, celsius;
    
    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);
    
    celsius = (fahrenheit - 32) * 5.0 / 9.0;
    
    printf("%.2f°F = %.2f°C\n", fahrenheit, celsius);
    
    return 0;
}
