/**
 * Problem: 4 Keys Keyboard
 * Difficulty: Medium
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxA(int n) {
        int[] dp = new int[n + 1];
        
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i-1] + 1;
            
            for (int j = 3; j < i; j++) {
                dp[i] = Math.max(dp[i], dp[i-j] * (j - 1));
            }
        }
        
        return dp[n];
    }
}