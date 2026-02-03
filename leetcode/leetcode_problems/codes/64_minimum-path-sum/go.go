// Problem: Minimum Path Sum
// Difficulty: Medium
// Tags: array, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

import "math"

func minPathSum(grid [][]int) int {
    m := len(grid)
    n := len(grid[0])
    dp := make([]int, n)
    for i := range dp {
        dp[i] = math.MaxInt32
    }
    dp[0] = 0
    
    for i := 0; i < m; i++ {
        dp[0] += grid[i][0]
        for j := 1; j < n; j++ {
            if dp[j] < dp[j-1] {
                dp[j] = dp[j] + grid[i][j]
            } else {
                dp[j] = dp[j-1] + grid[i][j]
            }
        }
    }
    
    return dp[n-1]
}