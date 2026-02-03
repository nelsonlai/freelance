/*
 * Problem: Add Binary
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdlib.h>
#include <string.h>

char* addBinary(char* a, char* b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = (lenA > lenB ? lenA : lenB) + 2;
    char* result = (char*)malloc(maxLen * sizeof(char));
    
    int i = lenA - 1;
    int j = lenB - 1;
    int carry = 0;
    int pos = maxLen - 1;
    result[pos] = '\0';
    pos--;
    
    while (i >= 0 || j >= 0 || carry > 0) {
        int total = carry;
        if (i >= 0) {
            total += a[i--] - '0';
        }
        if (j >= 0) {
            total += b[j--] - '0';
        }
        result[pos--] = (total % 2) + '0';
        carry = total / 2;
    }
    
    return result + pos + 1;
}