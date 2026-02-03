/**
 * Problem: Degree of an Array
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findShortestSubArray(int[] nums) {
        Map<Integer, Integer> first = new HashMap<>();
        Map<Integer, Integer> count = new HashMap<>();
        int maxCount = 0;
        int result = nums.length;
        
        for (int i = 0; i < nums.length; i++) {
            int num = nums[i];
            if (!first.containsKey(num)) {
                first.put(num, i);
            }
            count.put(num, count.getOrDefault(num, 0) + 1);
            
            if (count.get(num) > maxCount) {
                maxCount = count.get(num);
                result = i - first.get(num) + 1;
            } else if (count.get(num) == maxCount) {
                result = Math.min(result, i - first.get(num) + 1);
            }
        }
        
        return result;
    }
}