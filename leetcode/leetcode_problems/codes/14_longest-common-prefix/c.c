/*
 * Problem: Longest Common Prefix
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }
    
    int len = strlen(strs[0]);
    for (int i = 0; i < len; i++) {
        char c = strs[0][i];
        for (int j = 1; j < strsSize; j++) {
            if (i >= strlen(strs[j]) || strs[j][i] != c) {
                char* result = (char*)malloc((i + 1) * sizeof(char));
                strncpy(result, strs[0], i);
                result[i] = '\0';
                return result;
            }
        }
    }
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    strcpy(result, strs[0]);
    return result;
}