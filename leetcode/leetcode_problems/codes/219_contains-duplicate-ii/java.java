/**
 * Problem: Contains Duplicate II
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean containsNearbyDuplicate(int[] nums, int k) {
        Map<Integer, Integer> seen = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (seen.containsKey(nums[i]) && i - seen.get(nums[i]) <= k) {
                return true;
            }
            seen.put(nums[i], i);
        }
        return false;
    }
}