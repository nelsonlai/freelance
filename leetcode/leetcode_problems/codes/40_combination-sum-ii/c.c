/*
 * Problem: Combination Sum II
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
#include <string.h>

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

void backtrack(int* candidates, int candidatesSize, int target, int start,
               int* path, int pathSize, int** result, int* resultSize,
               int** returnColumnSizes, int maxPathSize) {
    if (target == 0) {
        result[*resultSize] = (int*)malloc(pathSize * sizeof(int));
        memcpy(result[*resultSize], path, pathSize * sizeof(int));
        (*returnColumnSizes)[*resultSize] = pathSize;
        (*resultSize)++;
        return;
    }
    if (target < 0) {
        return;
    }
    
    for (int i = start; i < candidatesSize; i++) {
        if (i > start && candidates[i] == candidates[i - 1]) {
            continue;
        }
        path[pathSize] = candidates[i];
        backtrack(candidates, candidatesSize, target - candidates[i], i + 1,
                 path, pathSize + 1, result, resultSize, returnColumnSizes, maxPathSize);
    }
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), compare);
    *returnSize = 0;
    int maxCombinations = 150;
    int** result = (int**)malloc(maxCombinations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxCombinations * sizeof(int));
    int* path = (int*)malloc(500 * sizeof(int));
    
    backtrack(candidates, candidatesSize, target, 0, path, 0, result, returnSize, returnColumnSizes, 500);
    
    free(path);
    return result;
}