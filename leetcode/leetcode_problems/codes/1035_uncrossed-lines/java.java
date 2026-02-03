/**
 * Problem: Uncrossed Lines
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Longest Common Subsequence - same as finding max uncrossed lines
 * Time Complexity: O(n * m) where n and m are array lengths
 * Space Complexity: O(n * m) for DP table
 */

class Solution {
    public int maxUncrossedLines(int[] nums1, int[] nums2) {
        int m = nums1.length, n = nums2.length;
        int[][] dp = new int[m + 1][n + 1];
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
}