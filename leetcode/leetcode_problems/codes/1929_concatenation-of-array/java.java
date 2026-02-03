/**
 * Problem: Concatenation of Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Concatenate array with itself
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public int[] getConcatenation(int[] nums) {
        int n = nums.length;
        int[] result = new int[2 * n];
        System.arraycopy(nums, 0, result, 0, n);
        System.arraycopy(nums, 0, result, n, n);
        return result;
    }
}