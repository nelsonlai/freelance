class Solution {
    fun minPathSum(grid: Array<IntArray>): Int {
        val m = grid.size
        val n = grid[0].size
        val dp = IntArray(n) { Int.MAX_VALUE }
        dp[0] = 0
        
        for (i in 0 until m) {
            dp[0] += grid[i][0]
            for (j in 1 until n) {
                dp[j] = minOf(dp[j], dp[j - 1]) + grid[i][j]
            }
        }
        
        return dp[n - 1]
    }
}