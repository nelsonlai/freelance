/*
 * Problem: Merge Intervals
 * Difficulty: Medium
 * Tags: array, sort
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

int compare(const void* a, const void* b) {
    int* interval1 = *(int**)a;
    int* interval2 = *(int**)b;
    return interval1[0] - interval2[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // Sort intervals by start time
    qsort(intervals, intervalsSize, sizeof(int*), compare);
    
    int capacity = intervalsSize;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    
    result[0] = (int*)malloc(2 * sizeof(int));
    result[0][0] = intervals[0][0];
    result[0][1] = intervals[0][1];
    (*returnColumnSizes)[0] = 2;
    *returnSize = 1;
    
    for (int i = 1; i < intervalsSize; i++) {
        int* current = intervals[i];
        int* last = result[*returnSize - 1];
        
        if (current[0] <= last[1]) {
            if (current[1] > last[1]) {
                last[1] = current[1];
            }
        } else {
            result[*returnSize] = (int*)malloc(2 * sizeof(int));
            result[*returnSize][0] = current[0];
            result[*returnSize][1] = current[1];
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
    }
    
    return result;
}