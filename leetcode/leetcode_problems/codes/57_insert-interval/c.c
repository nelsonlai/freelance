/*
 * Problem: Insert Interval
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

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    int capacity = intervalsSize + 1;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;
    
    int i = 0;
    int newStart = newInterval[0];
    int newEnd = newInterval[1];
    
    // Add all intervals before newInterval
    while (i < intervalsSize && intervals[i][1] < newStart) {
        result[*returnSize] = (int*)malloc(2 * sizeof(int));
        result[*returnSize][0] = intervals[i][0];
        result[*returnSize][1] = intervals[i][1];
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;
        i++;
    }
    
    // Merge overlapping intervals
    while (i < intervalsSize && intervals[i][0] <= newEnd) {
        if (intervals[i][0] < newStart) {
            newStart = intervals[i][0];
        }
        if (intervals[i][1] > newEnd) {
            newEnd = intervals[i][1];
        }
        i++;
    }
    
    // Add merged interval
    result[*returnSize] = (int*)malloc(2 * sizeof(int));
    result[*returnSize][0] = newStart;
    result[*returnSize][1] = newEnd;
    (*returnColumnSizes)[*returnSize] = 2;
    (*returnSize)++;
    
    // Add remaining intervals
    while (i < intervalsSize) {
        result[*returnSize] = (int*)malloc(2 * sizeof(int));
        result[*returnSize][0] = intervals[i][0];
        result[*returnSize][1] = intervals[i][1];
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;
        i++;
    }
    
    return result;
}