// Problem: Unique Paths II
// Difficulty: Medium
// Tags: array, tree, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func uniquePathsWithObstacles(obstacleGrid [][]int) int {
    m := len(obstacleGrid)
    n := len(obstacleGrid[0])
    
    if obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1 {
        return 0
    }
    
    dp := make([]int, n)
    dp[0] = 1
    
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            if obstacleGrid[i][j] == 1 {
                dp[j] = 0
            } else if j > 0 {
                dp[j] += dp[j-1]
            }
        }
    }
    
    return dp[n-1]
}