/**
 * Problem: Maximum Size Subarray Sum Equals k
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int maxSubArrayLen(int[] nums, int k) {
        Map<Integer, Integer> sumMap = new HashMap<>();
        sumMap.put(0, -1);
        int prefixSum = 0;
        int maxLength = 0;
        
        for (int i = 0; i < nums.length; i++) {
            prefixSum += nums[i];
            if (sumMap.containsKey(prefixSum - k)) {
                maxLength = Math.max(maxLength, i - sumMap.get(prefixSum - k));
            }
            if (!sumMap.containsKey(prefixSum)) {
                sumMap.put(prefixSum, i);
            }
        }
        
        return maxLength;
    }
}