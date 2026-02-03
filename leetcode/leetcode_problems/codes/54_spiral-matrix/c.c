/*
 * Problem: Spiral Matrix
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int total = matrixSize * matrixColSize[0];
    int* result = (int*)malloc(total * sizeof(int));
    *returnSize = 0;
    
    int top = 0, bottom = matrixSize - 1;
    int left = 0, right = matrixColSize[0] - 1;
    
    while (top <= bottom && left <= right) {
        // Right
        for (int j = left; j <= right; j++) {
            result[(*returnSize)++] = matrix[top][j];
        }
        top++;
        
        // Down
        for (int i = top; i <= bottom; i++) {
            result[(*returnSize)++] = matrix[i][right];
        }
        right--;
        
        // Left
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                result[(*returnSize)++] = matrix[bottom][j];
            }
            bottom--;
        }
        
        // Up
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                result[(*returnSize)++] = matrix[i][left];
            }
            left++;
        }
    }
    
    return result;
}