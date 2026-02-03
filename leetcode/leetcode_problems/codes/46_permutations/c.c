/*
 * Problem: Permutations
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

void backtrack(int* nums, int numsSize, int*** result, int* resultSize, 
               int* current, int currentSize, bool* used, int* capacity, int** returnColumnSizes) {
    if (currentSize == numsSize) {
        if (*resultSize >= *capacity) {
            *capacity *= 2;
            *result = (int**)realloc(*result, *capacity * sizeof(int*));
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, *capacity * sizeof(int));
        }
        (*result)[*resultSize] = (int*)malloc(numsSize * sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            (*result)[*resultSize][i] = current[i];
        }
        (*returnColumnSizes)[*resultSize] = numsSize;
        (*resultSize)++;
        return;
    }
    
    for (int i = 0; i < numsSize; i++) {
        if (used[i]) continue;
        used[i] = true;
        current[currentSize] = nums[i];
        backtrack(nums, numsSize, result, resultSize, current, currentSize + 1, used, capacity, returnColumnSizes);
        used[i] = false;
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int capacity = 16;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    
    int* current = (int*)malloc(numsSize * sizeof(int));
    bool* used = (bool*)calloc(numsSize, sizeof(bool));
    
    backtrack(nums, numsSize, &result, returnSize, current, 0, used, &capacity, returnColumnSizes);
    
    free(current);
    free(used);
    
    return result;
}