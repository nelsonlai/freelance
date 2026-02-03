/**
 * Problem: Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
 * Difficulty: Medium
 * Tags: array, greedy, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int maxNonOverlapping(int[] nums, int target) {
        Map<Integer, Integer> prefixSum = new HashMap<>();
        prefixSum.put(0, -1);
        int currentSum = 0;
        int count = 0;
        int lastEnd = -1;
        
        for (int i = 0; i < nums.length; i++) {
            currentSum += nums[i];
            if (prefixSum.containsKey(currentSum - target)) {
                int prevIdx = prefixSum.get(currentSum - target);
                if (prevIdx >= lastEnd) {
                    count++;
                    lastEnd = i;
                }
            }
            prefixSum.put(currentSum, i);
        }
        
        return count;
    }
}