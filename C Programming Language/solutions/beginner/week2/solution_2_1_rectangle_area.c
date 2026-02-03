/**
 * Solution 2.1: Rectangle Area Calculator
 * Week 2 - Variables, Data Types, and Operators
 * 
 * Description: Calculate the area of a rectangle given length and width
 */

#include <stdio.h>

int main() {
    float length, width, area;
    
    printf("Enter the length of rectangle: ");
    scanf("%f", &length);
    
    printf("Enter the width of rectangle: ");
    scanf("%f", &width);
    
    area = length * width;
    
    printf("Area of rectangle = %.2f square units\n", area);
    
    return 0;
}
