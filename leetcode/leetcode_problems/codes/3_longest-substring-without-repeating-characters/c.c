/*
 * Problem: Longest Substring Without Repeating Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string.h>

int lengthOfLongestSubstring(char* s) {
    int charIndex[128];
    memset(charIndex, -1, sizeof(charIndex));
    int left = 0;
    int maxLen = 0;
    int len = strlen(s);
    
    for (int right = 0; right < len; right++) {
        char c = s[right];
        if (charIndex[c] != -1 && charIndex[c] >= left) {
            left = charIndex[c] + 1;
        }
        charIndex[c] = right;
        maxLen = maxLen > (right - left + 1) ? maxLen : (right - left + 1);
    }
    
    return maxLen;
}