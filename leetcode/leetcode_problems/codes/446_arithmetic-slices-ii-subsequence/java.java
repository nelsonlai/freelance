/**
 * Problem: Arithmetic Slices II - Subsequence
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int numberOfArithmeticSlices(int[] nums) {
        int n = nums.length;
        Map<Long, Integer>[] dp = new Map[n];
        for (int i = 0; i < n; i++) {
            dp[i] = new HashMap<>();
        }
        int total = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                long diff = (long)nums[i] - nums[j];
                int count = dp[j].getOrDefault(diff, 0);
                dp[i].put(diff, dp[i].getOrDefault(diff, 0) + count + 1);
                total += count;
            }
        }
        
        return total;
    }
}