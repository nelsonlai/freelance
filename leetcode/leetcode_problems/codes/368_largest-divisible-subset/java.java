/**
 * Problem: Largest Divisible Subset
 * Difficulty: Medium
 * Tags: array, dp, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public List<Integer> largestDivisibleSubset(int[] nums) {
        if (nums.length == 0) {
            return new ArrayList<>();
        }
        
        Arrays.sort(nums);
        int n = nums.length;
        int[] dp = new int[n];
        int[] parent = new int[n];
        Arrays.fill(dp, 1);
        Arrays.fill(parent, -1);
        
        int maxLen = 1;
        int maxIdx = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                    if (dp[i] > maxLen) {
                        maxLen = dp[i];
                        maxIdx = i;
                    }
                }
            }
        }
        
        List<Integer> result = new ArrayList<>();
        int idx = maxIdx;
        while (idx != -1) {
            result.add(nums[idx]);
            idx = parent[idx];
        }
        
        Collections.reverse(result);
        return result;
    }
}