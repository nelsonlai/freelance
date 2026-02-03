/**
 * Problem: Build Array from Permutation
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Build new array using nums as indices
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public int[] buildArray(int[] nums) {
        int[] result = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            result[i] = nums[nums[i]];
        }
        return result;
    }
}