/**
 * Problem: Find Unique Binary String
 * Difficulty: Medium
 * Tags: array, string, hash, Cantor's diagonal argument
 * 
 * Approach: Use diagonal argument - flip i-th bit of i-th string
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public String findDifferentBinaryString(String[] nums) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < nums.length; i++) {
            // Flip the i-th bit of the i-th string
            if (nums[i].charAt(i) == '0') {
                result.append('1');
            } else {
                result.append('0');
            }
        }
        return result.toString();
    }
}