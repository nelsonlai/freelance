// Problem: Unique Paths
// Difficulty: Medium
// Tags: dp, math
// 
// Approach: Dynamic programming with memoization or tabulation
// Time Complexity: O(n * m) where n and m are problem dimensions
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        let n = n as usize;
        let mut dp = vec![1; n];
        
        for _ in 1..m {
            for j in 1..n {
                dp[j] += dp[j - 1];
            }
        }
        
        dp[n - 1]
    }
}