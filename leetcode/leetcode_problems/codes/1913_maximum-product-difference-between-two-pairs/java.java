/**
 * Problem: Maximum Product Difference Between Two Pairs
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Find two largest and two smallest numbers
 * Time Complexity: O(n) - can use partial sort
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int maxProductDifference(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        return nums[n - 1] * nums[n - 2] - nums[0] * nums[1];
    }
}