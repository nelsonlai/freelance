/**
 * Problem: Stone Game III
 * Difficulty: Hard
 * Tags: array, dp, math
 * 
 * Approach: DP - dp[i] = max score difference from position i, Alice wins if dp[0] > 0
 * Time Complexity: O(n) where n is length of stoneValue
 * Space Complexity: O(n) for DP table
 */

import java.util.Arrays;

class Solution {
    public String stoneGameIII(int[] stoneValue) {
        int n = stoneValue.length;
        int[] dp = new int[n + 1];
        Arrays.fill(dp, Integer.MIN_VALUE);
        dp[n] = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int total = 0;
            for (int j = i; j < Math.min(i + 3, n); j++) {
                total += stoneValue[j];
                dp[i] = Math.max(dp[i], total - dp[j + 1]);
            }
        }
        
        if (dp[0] > 0) {
            return "Alice";
        } else if (dp[0] < 0) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
}