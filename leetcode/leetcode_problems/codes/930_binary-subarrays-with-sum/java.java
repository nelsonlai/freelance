/**
 * Problem: Binary Subarrays With Sum
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use prefix sum with hash map to count subarrays with sum equal to goal
 * Time Complexity: O(n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int numSubarraysWithSum(int[] nums, int goal) {
        Map<Integer, Integer> count = new HashMap<>();
        count.put(0, 1);
        int prefixSum = 0;
        int result = 0;
        
        for (int num : nums) {
            prefixSum += num;
            if (count.containsKey(prefixSum - goal)) {
                result += count.get(prefixSum - goal);
            }
            count.put(prefixSum, count.getOrDefault(prefixSum, 0) + 1);
        }
        
        return result;
    }
}