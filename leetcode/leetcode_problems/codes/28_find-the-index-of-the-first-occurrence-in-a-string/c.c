/*
 * Problem: Find the Index of the First Occurrence in a String
 * Difficulty: Easy
 * Tags: array, string, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string.h>

int strStr(char* haystack, char* needle) {
    if (strlen(needle) == 0) {
        return 0;
    }
    
    int n = strlen(haystack);
    int m = strlen(needle);
    
    for (int i = 0; i <= n - m; i++) {
        if (strncmp(haystack + i, needle, m) == 0) {
            return i;
        }
    }
    
    return -1;
}