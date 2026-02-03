/**
 * Problem: Subarray Sum Equals K
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int subarraySum(int[] nums, int k) {
        Map<Integer, Integer> count = new HashMap<>();
        count.put(0, 1);
        int prefixSum = 0;
        int result = 0;
        
        for (int num : nums) {
            prefixSum += num;
            result += count.getOrDefault(prefixSum - k, 0);
            count.put(prefixSum, count.getOrDefault(prefixSum, 0) + 1);
        }
        
        return result;
    }
}