/**
 * Problem: Allocate Mailboxes
 * Difficulty: Hard
 * Tags: array, tree, dp, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int minDistance(int[] houses, int k) {
        Arrays.sort(houses);
        int n = houses.length;
        
        // cost[i][j] = min distance if one mailbox serves houses[i:j+1]
        int[][] cost = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int median = houses[(i + j) / 2];
                int sum = 0;
                for (int m = i; m <= j; m++) {
                    sum += Math.abs(houses[m] - median);
                }
                cost[i][j] = sum;
            }
        }
        
        // dp[i][j] = min distance using j mailboxes for first i houses
        int[][] dp = new int[n + 1][k + 1];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE);
        }
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= Math.min(i, k); j++) {
                for (int p = j - 1; p < i; p++) {
                    if (dp[p][j - 1] != Integer.MAX_VALUE) {
                        dp[i][j] = Math.min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);
                    }
                }
            }
        }
        
        return dp[n][k];
    }
}