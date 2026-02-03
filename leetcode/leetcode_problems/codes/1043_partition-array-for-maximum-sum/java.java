/**
 * Problem: Partition Array for Maximum Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - for each position, try all partition sizes up to k
 * Time Complexity: O(n * k)
 * Space Complexity: O(n) for DP array
 */

class Solution {
    public int maxSumAfterPartitioning(int[] arr, int k) {
        int n = arr.length;
        int[] dp = new int[n + 1];
        
        for (int i = 1; i <= n; i++) {
            int maxVal = 0;
            for (int j = 1; j <= Math.min(k, i); j++) {
                maxVal = Math.max(maxVal, arr[i - j]);
                dp[i] = Math.max(dp[i], dp[i - j] + maxVal * j);
            }
        }
        
        return dp[n];
    }
}