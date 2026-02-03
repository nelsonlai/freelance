/**
 * Problem: Maximum Vacation Days
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxVacationDays(int[][] flights, int[][] days) {
        int n = flights.length;
        int k = days[0].length;
        
        int[][] dp = new int[k][n];
        for (int i = 0; i < n; i++) {
            if (i == 0 || flights[0][i] == 1) {
                dp[0][i] = days[i][0];
            } else {
                dp[0][i] = -1;
            }
        }
        
        for (int week = 1; week < k; week++) {
            for (int city = 0; city < n; city++) {
                dp[week][city] = -1;
                for (int prevCity = 0; prevCity < n; prevCity++) {
                    if (dp[week-1][prevCity] != -1) {
                        if (prevCity == city || flights[prevCity][city] == 1) {
                            dp[week][city] = Math.max(dp[week][city], 
                                                     dp[week-1][prevCity] + days[city][week]);
                        }
                    }
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            result = Math.max(result, dp[k-1][i]);
        }
        
        return result;
    }
}