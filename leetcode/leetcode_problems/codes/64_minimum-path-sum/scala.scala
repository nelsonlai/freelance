object Solution {
    def minPathSum(grid: Array[Array[Int]]): Int = {
        val m = grid.length
        val n = grid(0).length
        val dp = Array.fill(n)(Int.MaxValue)
        dp(0) = 0
        
        for (i <- 0 until m) {
            dp(0) += grid(i)(0)
            for (j <- 1 until n) {
                dp(j) = math.min(dp(j), dp(j - 1)) + grid(i)(j)
            }
        }
        
        dp(n - 1)
    }
}