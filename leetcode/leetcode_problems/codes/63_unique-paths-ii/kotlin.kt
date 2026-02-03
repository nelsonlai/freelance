class Solution {
    fun uniquePathsWithObstacles(obstacleGrid: Array<IntArray>): Int {
        val m = obstacleGrid.size
        val n = obstacleGrid[0].size
        
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
            return 0
        }
        
        val dp = IntArray(n)
        dp[0] = 1
        
        for (i in 0 until m) {
            for (j in 0 until n) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0
                } else if (j > 0) {
                    dp[j] += dp[j - 1]
                }
            }
        }
        
        return dp[n - 1]
    }
}