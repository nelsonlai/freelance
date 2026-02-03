// Problem: Unique Paths II
// Difficulty: Medium
// Tags: array, tree, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn unique_paths_with_obstacles(obstacle_grid: Vec<Vec<i32>>) -> i32 {
        let m = obstacle_grid.len();
        let n = obstacle_grid[0].len();
        
        if obstacle_grid[0][0] == 1 || obstacle_grid[m - 1][n - 1] == 1 {
            return 0;
        }
        
        let mut dp = vec![0; n];
        dp[0] = 1;
        
        for i in 0..m {
            for j in 0..n {
                if obstacle_grid[i][j] == 1 {
                    dp[j] = 0;
                } else if j > 0 {
                    dp[j] += dp[j - 1];
                }
            }
        }
        
        dp[n - 1]
    }
}