/*
 * Problem: Minimum Path Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

public class Solution {
    public int MinPathSum(int[][] grid) {
        int m = grid.Length;
        int n = grid[0].Length;
        int[] dp = new int[n];
        System.Array.Fill(dp, int.MaxValue);
        dp[0] = 0;
        
        for (int i = 0; i < m; i++) {
            dp[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                dp[j] = System.Math.Min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }
        
        return dp[n - 1];
    }
}