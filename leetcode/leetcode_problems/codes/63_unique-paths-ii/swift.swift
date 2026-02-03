class Solution {
    func uniquePathsWithObstacles(_ obstacleGrid: [[Int]]) -> Int {
        let m = obstacleGrid.count
        let n = obstacleGrid[0].count
        
        if obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1 {
            return 0
        }
        
        var dp = Array(repeating: 0, count: n)
        dp[0] = 1
        
        for i in 0..<m {
            for j in 0..<n {
                if obstacleGrid[i][j] == 1 {
                    dp[j] = 0
                } else if j > 0 {
                    dp[j] += dp[j - 1]
                }
            }
        }
        
        return dp[n - 1]
    }
}