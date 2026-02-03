/**
 * Problem: Stone Game VIII
 * Difficulty: Hard
 * Tags: array, dp, math, prefix sum
 * 
 * Approach: DP - dp[i] = max score difference starting from position i
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public int stoneGameVIII(int[] stones) {
        int n = stones.length;
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }
        
        long[] dp = new long[n];
        dp[n - 1] = prefix[n];
        
        for (int i = n - 2; i > 0; i--) {
            dp[i] = Math.max(prefix[i + 1] - dp[i + 1], dp[i + 1]);
        }
        
        return (int) dp[1];
    }
}