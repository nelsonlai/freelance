/*
 * Problem: Longest Palindromic Substring
 * Difficulty: Medium
 * Tags: array, string, tree, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string.h>
#include <stdlib.h>

char* longestPalindrome(char* s) {
    int len = strlen(s);
    if (len == 0) {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }
    
    int start = 0, maxLen = 1;
    
    int expandAroundCenter(int left, int right) {
        while (left >= 0 && right < len && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
    
    for (int i = 0; i < len; i++) {
        int len1 = expandAroundCenter(i, i);
        int len2 = expandAroundCenter(i, i + 1);
        int length = (len1 > len2) ? len1 : len2;
        
        if (length > maxLen) {
            start = i - (length - 1) / 2;
            maxLen = length;
        }
    }
    
    char* result = (char*)malloc((maxLen + 1) * sizeof(char));
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0';
    return result;
}