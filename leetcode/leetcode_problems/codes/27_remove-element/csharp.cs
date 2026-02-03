/*
 * Problem: Remove Element
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

public class Solution {
    public int RemoveElement(int[] nums, int val) {
        int writeIndex = 0;
        for (int i = 0; i < nums.Length; i++) {
            if (nums[i] != val) {
                nums[writeIndex] = nums[i];
                writeIndex++;
            }
        }
        return writeIndex;
    }
}