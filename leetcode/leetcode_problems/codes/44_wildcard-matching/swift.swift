class Solution {
    func isMatch(_ s: String, _ p: String) -> Bool {
        let sArray = Array(s)
        let pArray = Array(p)
        let m = sArray.count
        let n = pArray.count
        var dp = Array(repeating: Array(repeating: false, count: n + 1), count: m + 1)
        dp[0][0] = true
        
        // Handle patterns starting with *
        for j in 1...n {
            if pArray[j - 1] == Character("*") {
                dp[0][j] = dp[0][j - 1]
            }
        }
        
        for i in 1...m {
            for j in 1...n {
                if pArray[j - 1] == Character("*") {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j]
                } else if pArray[j - 1] == Character("?") || sArray[i - 1] == pArray[j - 1] {
                    dp[i][j] = dp[i - 1][j - 1]
                }
            }
        }
        
        return dp[m][n]
    }
}