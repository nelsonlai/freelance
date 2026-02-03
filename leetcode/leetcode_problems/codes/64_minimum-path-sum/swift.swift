class Solution {
    func minPathSum(_ grid: [[Int]]) -> Int {
        let m = grid.count
        let n = grid[0].count
        var dp = Array(repeating: Int.max, count: n)
        dp[0] = 0
        
        for i in 0..<m {
            dp[0] += grid[i][0]
            for j in 1..<n {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j]
            }
        }
        
        return dp[n - 1]
    }
}