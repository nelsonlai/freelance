/*
 * Problem: String to Integer (atoi)
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <ctype.h>
#include <limits.h>

int myAtoi(char* s) {
    // Skip whitespace
    while (*s == ' ') {
        s++;
    }
    
    if (*s == '\0') {
        return 0;
    }
    
    int sign = 1;
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }
    
    int result = 0;
    while (*s != '\0' && isdigit(*s)) {
        int digit = *s - '0';
        if (result > INT_MAX / 10 || 
            (result == INT_MAX / 10 && digit > 7)) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        result = result * 10 + digit;
        s++;
    }
    
    return sign * result;
}