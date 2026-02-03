/**
 * Problem: Two Best Non-Overlapping Events
 * Difficulty: Medium
 * Tags: array, dp, sort, search, binary search
 * 
 * Approach: Sort by end time, use DP with binary search to find best previous event
 * Time Complexity: O(n log n) where n is number of events
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int maxTwoEvents(int[][] events) {
        // Sort by end time
        Arrays.sort(events, (a, b) -> Integer.compare(a[1], b[1]));
        int n = events.length;
        
        // dp[i] = maximum value using events up to index i
        int[] dp = new int[n];
        dp[0] = events[0][2];
        
        // Track maximum value seen so far
        int[] maxSoFar = new int[n];
        maxSoFar[0] = events[0][2];
        
        int result = events[0][2];
        
        for (int i = 1; i < n; i++) {
            int start = events[i][0];
            int end = events[i][1];
            int value = events[i][2];
            
            // Binary search for last event that ends before current starts
            int left = 0, right = i - 1;
            int bestPrev = -1;
            
            while (left <= right) {
                int mid = (left + right) / 2;
                if (events[mid][1] < start) {
                    bestPrev = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            
            // Take current event alone or with best previous
            dp[i] = value;
            if (bestPrev >= 0) {
                dp[i] = Math.max(dp[i], maxSoFar[bestPrev] + value);
            }
            
            maxSoFar[i] = Math.max(maxSoFar[i - 1], dp[i]);
            result = Math.max(result, dp[i]);
        }
        
        return result;
    }
}