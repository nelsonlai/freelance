/**
 * Problem: Distinct Numbers in Each Subarray
 * Difficulty: Medium
 * Tags: array, hash, sliding window
 * 
 * Approach: Sliding window with frequency map
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(k)
 */

import java.util.*;

class Solution {
    public int[] distinctNumbers(int[] nums, int k) {
        Map<Integer, Integer> count = new HashMap<>();
        List<Integer> result = new ArrayList<>();
        
        for (int i = 0; i < nums.length; i++) {
            count.put(nums[i], count.getOrDefault(nums[i], 0) + 1);
            
            if (i >= k - 1) {
                result.add(count.size());
                
                int left = nums[i - k + 1];
                count.put(left, count.get(left) - 1);
                if (count.get(left) == 0) {
                    count.remove(left);
                }
            }
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
}