/*
 * Problem: Spiral Matrix II
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

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = n;
    int** matrix = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
        (*returnColumnSizes)[i] = n;
    }
    
    int num = 1;
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    
    while (top <= bottom && left <= right) {
        // Right
        for (int j = left; j <= right; j++) {
            matrix[top][j] = num++;
        }
        top++;
        
        // Down
        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;
        
        // Left
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                matrix[bottom][j] = num++;
            }
            bottom--;
        }
        
        // Up
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = num++;
            }
            left++;
        }
    }
    
    return matrix;
}