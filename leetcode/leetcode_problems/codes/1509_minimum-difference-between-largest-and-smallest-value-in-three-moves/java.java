/**
 * Problem: Minimum Difference Between Largest and Smallest Value in Three Moves
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort, try removing 0-3 smallest and 0-3 largest, find minimum difference
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.Arrays;

class Solution {
    public int minDifference(int[] nums) {
        if (nums.length <= 4) {
            return 0;
        }
        
        Arrays.sort(nums);
        int n = nums.length;
        
        int result = Integer.MAX_VALUE;
        for (int i = 0; i < 4; i++) {
            result = Math.min(result, nums[n - 1 - (3 - i)] - nums[i]);
        }
        
        return result;
    }
}