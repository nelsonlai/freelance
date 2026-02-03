/*
 * Problem: Longest Valid Parentheses
 * Difficulty: Hard
 * Tags: string, tree, dp, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s) {
    int len = strlen(s);
    int* stack = (int*)malloc((len + 1) * sizeof(int));
    int top = 0;
    stack[top++] = -1;
    int maxLen = 0;
    
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[top++] = i;
        } else {
            top--;
            if (top == 0) {
                stack[top++] = i;
            } else {
                int currentLen = i - stack[top - 1];
                if (currentLen > maxLen) {
                    maxLen = currentLen;
                }
            }
        }
    }
    
    free(stack);
    return maxLen;
}