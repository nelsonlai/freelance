/**
 * Problem: Minimum Cost to Cut a Stick
 * Difficulty: Hard
 * Tags: array, dp, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int minCost(int n, int[] cuts) {
        List<Integer> cutsList = new ArrayList<>();
        cutsList.add(0);
        for (int cut : cuts) {
            cutsList.add(cut);
        }
        cutsList.add(n);
        Collections.sort(cutsList);
        
        int m = cutsList.size();
        int[][] dp = new int[m][m];
        
        for (int length = 2; length < m; length++) {
            for (int i = 0; i < m - length; i++) {
                int j = i + length;
                dp[i][j] = Integer.MAX_VALUE;
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[k][j] + cutsList.get(j) - cutsList.get(i));
                }
            }
        }
        
        return dp[0][m-1];
    }
}