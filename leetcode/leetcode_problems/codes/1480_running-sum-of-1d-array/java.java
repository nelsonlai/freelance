/**
 * Problem: Running Sum of 1d Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int[] runningSum(int[] nums) {
        int[] result = new int[nums.length];
        int prefix = 0;
        for (int i = 0; i < nums.length; i++) {
            prefix += nums[i];
            result[i] = prefix;
        }
        return result;
    }
}