/*
 * Problem: Plus One
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            *returnSize = digitsSize;
            int* result = (int*)malloc(digitsSize * sizeof(int));
            for (int j = 0; j < digitsSize; j++) {
                result[j] = digits[j];
            }
            return result;
        }
        digits[i] = 0;
    }
    
    *returnSize = digitsSize + 1;
    int* result = (int*)malloc((digitsSize + 1) * sizeof(int));
    result[0] = 1;
    for (int i = 0; i < digitsSize; i++) {
        result[i + 1] = digits[i];
    }
    return result;
}