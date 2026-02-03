/**
 * Problem: Burst Balloons
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxCoins(int[] nums) {
        int n = nums.length;
        int[] extended = new int[n + 2];
        extended[0] = 1;
        extended[n + 1] = 1;
        System.arraycopy(nums, 0, extended, 1, n);
        
        int[][] dp = new int[n + 2][n + 2];
        
        for (int length = 2; length < n + 2; length++) {
            for (int left = 0; left < n + 2 - length; left++) {
                int right = left + length;
                for (int i = left + 1; i < right; i++) {
                    dp[left][right] = Math.max(dp[left][right],
                        extended[left] * extended[i] * extended[right] + 
                        dp[left][i] + dp[i][right]);
                }
            }
        }
        
        return dp[0][n + 1];
    }
}