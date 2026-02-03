/**
 * Problem: K Inverse Pairs Array
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int kInversePairs(int n, int k) {
        int MOD = 1000000007;
        int[][] dp = new int[n + 1][k + 1];
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1;
            for (int j = 1; j <= k; j++) {
                dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % MOD;
                if (j >= i) {
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + MOD) % MOD;
                }
            }
        }
        
        return dp[n][k];
    }
}