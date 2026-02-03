/**
 * Solution 7.3: String Reverser Using Pointers
 * Week 7 - Pointers Fundamentals
 * 
 * Description: Create a function to reverse a string using pointers
 */

#include <stdio.h>
#include <string.h>

void reverseString(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    
    while (start < end) {
        // Swap characters
        char temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\n")] = '\0'; /* \0 is the null character */
    
    printf("Original string: %s\n", str);
    
    reverseString(str); // reverse 反轉
    
    printf("Reversed string: %s\n", str);
    
    return 0;
}