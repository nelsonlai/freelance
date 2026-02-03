/**
 * Solution 7.2: String Length Using Pointers
 * Week 7 - Pointers Fundamentals
 * 
 * Description: Implement string length function using pointers
 */

#include <stdio.h>

int stringLength(char *str) {
    int length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    if (str[stringLength(str) - 1] == '\n') {
        str[stringLength(str) - 1] = '\0';
    }
    
    printf("Length of string: %d\n", stringLength(str));
    
    return 0;
}