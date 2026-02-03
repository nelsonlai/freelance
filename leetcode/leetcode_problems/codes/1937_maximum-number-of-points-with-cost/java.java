/**
 * Problem: Maximum Number of Points with Cost
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP with optimization - track max from left and right
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(n)
 */

class Solution {
    public long maxPoints(int[][] points) {
        int m = points.length;
        int n = points[0].length;
        long[] dp = new long[n];
        for (int j = 0; j < n; j++) {
            dp[j] = points[0][j];
        }
        
        for (int i = 1; i < m; i++) {
            long[] left = new long[n];
            left[0] = dp[0];
            for (int j = 1; j < n; j++) {
                left[j] = Math.max(left[j - 1] - 1, dp[j]);
            }
            
            long[] right = new long[n];
            right[n - 1] = dp[n - 1];
            for (int j = n - 2; j >= 0; j--) {
                right[j] = Math.max(right[j + 1] - 1, dp[j]);
            }
            
            for (int j = 0; j < n; j++) {
                dp[j] = points[i][j] + Math.max(left[j], right[j]);
            }
        }
        
        long result = 0;
        for (long val : dp) {
            result = Math.max(result, val);
        }
        return result;
    }
}