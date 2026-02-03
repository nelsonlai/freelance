// Problem: Minimum Path Sum
// Difficulty: Medium
// Tags: array, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn min_path_sum(grid: Vec<Vec<i32>>) -> i32 {
        let m = grid.len();
        let n = grid[0].len();
        let mut dp = vec![i32::MAX; n];
        dp[0] = 0;
        
        for i in 0..m {
            dp[0] += grid[i][0];
            for j in 1..n {
                dp[j] = dp[j].min(dp[j - 1]) + grid[i][j];
            }
        }
        
        dp[n - 1]
    }
}