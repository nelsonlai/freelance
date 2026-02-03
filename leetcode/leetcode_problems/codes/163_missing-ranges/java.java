/**
 * Problem: Missing Ranges
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<List<Integer>> findMissingRanges(int[] nums, int lower, int upper) {
        List<List<Integer>> result = new ArrayList<>();
        int prev = lower - 1;
        
        for (int num : nums) {
            if (prev + 1 < num) {
                result.add(Arrays.asList(prev + 1, num - 1));
            }
            prev = num;
        }
        
        if (prev < upper) {
            result.add(Arrays.asList(prev + 1, upper));
        }
        
        return result;
    }
}