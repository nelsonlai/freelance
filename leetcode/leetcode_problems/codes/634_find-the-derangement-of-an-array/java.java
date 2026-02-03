/**
 * Problem: Find the Derangement of An Array
 * Difficulty: Medium
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int findDerangement(int n) {
        int MOD = 1000000007;
        if (n <= 1) {
            return 0;
        }
        if (n == 2) {
            return 1;
        }
        
        long[] dp = new long[n + 1];
        dp[1] = 0;
        dp[2] = 1;
        
        for (int i = 3; i <= n; i++) {
            dp[i] = ((i - 1) * (dp[i-1] + dp[i-2])) % MOD;
        }
        
        return (int)dp[n];
    }
}