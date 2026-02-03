/*
 * Problem: Generate Parentheses
 * Difficulty: Medium
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

void backtrack(char*** result, int* returnSize, char* current, int open, int close, int max, int currentLen) {
    if (currentLen == 2 * max) {
        (*returnSize)++;
        *result = (char**)realloc(*result, (*returnSize) * sizeof(char*));
        (*result)[(*returnSize) - 1] = (char*)malloc((currentLen + 1) * sizeof(char));
        strcpy((*result)[(*returnSize) - 1], current);
        return;
    }
    
    if (open < max) {
        current[currentLen] = '(';
        current[currentLen + 1] = '\0';
        backtrack(result, returnSize, current, open + 1, close, max, currentLen + 1);
    }
    
    if (close < open) {
        current[currentLen] = ')';
        current[currentLen + 1] = '\0';
        backtrack(result, returnSize, current, open, close + 1, max, currentLen + 1);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    char** result = NULL;
    char* current = (char*)malloc((2 * n + 1) * sizeof(char));
    current[0] = '\0';
    
    backtrack(&result, returnSize, current, 0, 0, n, 0);
    
    free(current);
    return result;
}