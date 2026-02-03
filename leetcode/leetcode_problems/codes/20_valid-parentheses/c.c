/*
 * Problem: Valid Parentheses
 * Difficulty: Easy
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValid(char* s) {
    int len = strlen(s);
    if (len % 2 != 0) {
        return false;
    }
    
    char* stack = (char*)malloc(len * sizeof(char));
    int top = -1;
    
    for (int i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++top] = s[i];
        } else {
            if (top == -1) {
                free(stack);
                return false;
            }
            
            char opening = stack[top--];
            if ((s[i] == ')' && opening != '(') ||
                (s[i] == '}' && opening != '{') ||
                (s[i] == ']' && opening != '[')) {
                free(stack);
                return false;
            }
        }
    }
    
    bool result = (top == -1);
    free(stack);
    return result;
}