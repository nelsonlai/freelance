object Solution {
    def uniquePathsWithObstacles(obstacleGrid: Array[Array[Int]]): Int = {
        val m = obstacleGrid.length
        val n = obstacleGrid(0).length
        
        if (obstacleGrid(0)(0) == 1 || obstacleGrid(m - 1)(n - 1) == 1) {
            return 0
        }
        
        val dp = Array.fill(n)(0)
        dp(0) = 1
        
        for (i <- 0 until m) {
            for (j <- 0 until n) {
                if (obstacleGrid(i)(j) == 1) {
                    dp(j) = 0
                } else if (j > 0) {
                    dp(j) += dp(j - 1)
                }
            }
        }
        
        dp(n - 1)
    }
}