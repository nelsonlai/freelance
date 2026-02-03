/**
 * Problem: Count Number of Pairs With Absolute Difference K
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use hash map to count occurrences, check for nums[i] ± k
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int countKDifference(int[] nums, int k) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        int result = 0;
        for (int num : count.keySet()) {
            if (count.containsKey(num + k)) {
                result += count.get(num) * count.get(num + k);
            }
        }
        
        return result;
    }
}