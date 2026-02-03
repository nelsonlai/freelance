/**
 * Problem: Max Dot Product of Two Subsequences
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP - dp[i][j] = max dot product using nums1[:i] and nums2[:j]
 * Time Complexity: O(n * m) where n, m are array lengths
 * Space Complexity: O(n * m) for DP table
 */

class Solution {
    public int maxDotProduct(int[] nums1, int[] nums2) {
        int m = nums1.length, n = nums2.length;
        long[][] dp = new long[m + 1][n + 1];
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = Long.MIN_VALUE;
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                long product = (long) nums1[i-1] * nums2[j-1];
                dp[i][j] = Math.max(
                    Math.max(dp[i-1][j-1] + product, dp[i-1][j]),
                    Math.max(dp[i][j-1], product)
                );
            }
        }
        
        return (int) dp[m][n];
    }
}