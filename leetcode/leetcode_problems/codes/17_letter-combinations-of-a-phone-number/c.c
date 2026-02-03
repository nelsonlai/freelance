/*
 * Problem: Letter Combinations of a Phone Number
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

char** letterCombinations(char* digits, int* returnSize) {
    *returnSize = 0;
    if (!digits || strlen(digits) == 0) {
        return NULL;
    }
    
    char* phoneMap[10] = {
        "", "", "abc", "def", "ghi", "jkl",
        "mno", "pqrs", "tuv", "wxyz"
    };
    
    int len = strlen(digits);
    int maxSize = 1;
    for (int i = 0; i < len; i++) {
        maxSize *= 4;
    }
    
    char** result = (char**)malloc(maxSize * sizeof(char*));
    *returnSize = 0;
    
    void backtrack(int index, char* current, int currentLen) {
        if (index == len) {
            result[*returnSize] = (char*)malloc((currentLen + 1) * sizeof(char));
            strcpy(result[*returnSize], current);
            (*returnSize)++;
            return;
        }
        
        int digit = digits[index] - '0';
        char* letters = phoneMap[digit];
        int lettersLen = strlen(letters);
        
        for (int i = 0; i < lettersLen; i++) {
            current[currentLen] = letters[i];
            current[currentLen + 1] = '\0';
            backtrack(index + 1, current, currentLen + 1);
        }
    }
    
    char* current = (char*)malloc((len + 1) * sizeof(char));
    backtrack(0, current, 0);
    free(current);
    
    return result;
}