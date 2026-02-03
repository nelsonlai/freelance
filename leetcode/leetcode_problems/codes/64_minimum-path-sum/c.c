/*
 * Problem: Minimum Path Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <stdlib.h>
#include <limits.h>

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int* dp = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    
    for (int i = 0; i < m; i++) {
        dp[0] += grid[i][0];
        for (int j = 1; j < n; j++) {
            dp[j] = (dp[j] < dp[j - 1] ? dp[j] : dp[j - 1]) + grid[i][j];
        }
    }
    
    int result = dp[n - 1];
    free(dp);
    return result;
}