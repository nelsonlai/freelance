/**
 * Problem: Maximum Earnings From Taxi
 * Difficulty: Medium
 * Tags: array, dp, hash, sort, search
 * 
 * Approach: DP - sort rides by end time, use binary search to find previous compatible ride
 * Time Complexity: O(n log n) where n is number of rides
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public long maxTaxiEarnings(int n, int[][] rides) {
        Arrays.sort(rides, (a, b) -> Integer.compare(a[1], b[1]));
        int m = rides.length;
        long[] dp = new long[m + 1];
        
        for (int i = 0; i < m; i++) {
            int start = rides[i][0];
            int end = rides[i][1];
            int tip = rides[i][2];
            long earnings = end - start + tip;
            
            // Binary search for last ride that ends before current start
            int left = 0, right = i;
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (rides[mid][1] <= start) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            
            // Take current ride or skip it
            if (rides[left][1] <= start) {
                dp[i + 1] = Math.max(dp[i], dp[left + 1] + earnings);
            } else {
                dp[i + 1] = Math.max(dp[i], earnings);
            }
        }
        
        return dp[m];
    }
}