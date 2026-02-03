object Solution {
    def uniquePaths(m: Int, n: Int): Int = {
        val dp = Array.fill(n)(1)
        
        for (i <- 1 until m) {
            for (j <- 1 until n) {
                dp(j) += dp(j - 1)
            }
        }
        
        dp(n - 1)
    }
}