/**
 * Problem: Target Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        Map<Integer, Integer> dp = new HashMap<>();
        dp.put(0, 1);
        
        for (int num : nums) {
            Map<Integer, Integer> newDp = new HashMap<>();
            for (Map.Entry<Integer, Integer> entry : dp.entrySet()) {
                int sum = entry.getKey();
                int count = entry.getValue();
                newDp.put(sum + num, newDp.getOrDefault(sum + num, 0) + count);
                newDp.put(sum - num, newDp.getOrDefault(sum - num, 0) + count);
            }
            dp = newDp;
        }
        
        return dp.getOrDefault(target, 0);
    }
}