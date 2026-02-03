/**
 * Problem: Stone Game IV
 * Difficulty: Hard
 * Tags: dp, math
 * 
 * Approach: DP - dp[i] = True if current player can win with i stones
 * Time Complexity: O(n * sqrt(n))
 * Space Complexity: O(n) for DP table
 */

class Solution {
    public boolean winnerSquareGame(int n) {
        boolean[] dp = new boolean[n + 1];
        
        for (int i = 1; i <= n; i++) {
            int j = 1;
            while (j * j <= i) {
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
                j++;
            }
        }
        
        return dp[n];
    }
}