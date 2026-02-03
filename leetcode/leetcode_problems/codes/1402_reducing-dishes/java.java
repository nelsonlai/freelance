/**
 * Problem: Reducing Dishes
 * Difficulty: Hard
 * Tags: array, dp, greedy, sort
 * 
 * Approach: Sort descending, use DP - dp[i][j] = max satisfaction using first i dishes, j cooked
 * Time Complexity: O(n^2) where n is number of dishes
 * Space Complexity: O(n) using rolling array
 */

import java.util.Arrays;

class Solution {
    public int maxSatisfaction(int[] satisfaction) {
        Arrays.sort(satisfaction);
        int n = satisfaction.length;
        int[] dp = new int[n + 1];
        
        for (int i = n - 1; i >= 0; i--) {
            int[] newDp = new int[n + 1];
            for (int j = 1; j <= n - i; j++) {
                newDp[j] = Math.max(dp[j], dp[j - 1] + satisfaction[i] * j);
            }
            dp = newDp;
        }
        
        int result = 0;
        for (int val : dp) {
            result = Math.max(result, val);
        }
        return result;
    }
}