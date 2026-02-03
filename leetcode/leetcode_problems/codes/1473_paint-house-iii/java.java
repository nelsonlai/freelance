/**
 * Problem: Paint House III
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int minCost(int[] houses, int[][] cost, int m, int n, int target) {
        int[][][] dp = new int[m + 1][n + 1][target + 1];
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= target; k++) {
                    dp[i][j][k] = Integer.MAX_VALUE;
                }
            }
        }
        
        dp[0][0][0] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (houses[i - 1] != 0 && houses[i - 1] != j) {
                    continue;
                }
                
                int paintCost = (houses[i - 1] == j) ? 0 : cost[i - 1][j - 1];
                
                for (int k = 1; k <= target; k++) {
                    for (int prevColor = 0; prevColor <= n; prevColor++) {
                        if (dp[i - 1][prevColor][k - (prevColor == j ? 0 : 1)] == Integer.MAX_VALUE) {
                            continue;
                        }
                        
                        if (prevColor == j) {
                            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][j][k] + paintCost);
                        } else {
                            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][prevColor][k - 1] + paintCost);
                        }
                    }
                }
            }
        }
        
        int result = Integer.MAX_VALUE;
        for (int j = 1; j <= n; j++) {
            result = Math.min(result, dp[m][j][target]);
        }
        
        return result == Integer.MAX_VALUE ? -1 : result;
    }
}