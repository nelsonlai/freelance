/**
 * Problem: Smallest Index With Equal Value
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Check if nums[i] == i % 10 for each index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int smallestEqual(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            if (i % 10 == nums[i]) {
                return i;
            }
        }
        return -1;
    }
}