/**
 * Problem: Count Number of Maximum Bitwise-OR Subsets
 * Difficulty: Medium
 * Tags: array, bit manipulation, dp
 * 
 * Approach: Find max OR value, then count subsets with that OR value
 * Time Complexity: O(n * 2^n) or O(n * max_or) with DP
 * Space Complexity: O(max_or)
 */

import java.util.*;

class Solution {
    public int countMaxOrSubsets(int[] nums) {
        // Find maximum OR value
        int maxOr = 0;
        for (int num : nums) {
            maxOr |= num;
        }
        
        // Count subsets with OR = max_or using DP
        int n = nums.length;
        // dp[mask] = number of ways to achieve OR = mask
        Map<Integer, Integer> dp = new HashMap<>();
        dp.put(0, 1);
        
        for (int num : nums) {
            Map<Integer, Integer> newDp = new HashMap<>(dp);
            for (Map.Entry<Integer, Integer> entry : dp.entrySet()) {
                int newMask = entry.getKey() | num;
                newDp.put(newMask, newDp.getOrDefault(newMask, 0) + entry.getValue());
            }
            dp = newDp;
        }
        
        return dp.getOrDefault(maxOr, 0);
    }
}