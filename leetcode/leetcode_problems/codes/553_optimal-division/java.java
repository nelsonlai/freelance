/**
 * Problem: Optimal Division
 * Difficulty: Medium
 * Tags: array, string, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public String optimalDivision(int[] nums) {
        if (nums.length == 1) {
            return String.valueOf(nums[0]);
        }
        if (nums.length == 2) {
            return nums[0] + "/" + nums[1];
        }
        
        StringBuilder result = new StringBuilder();
        result.append(nums[0]).append("/(").append(nums[1]);
        for (int i = 2; i < nums.length; i++) {
            result.append("/").append(nums[i]);
        }
        result.append(")");
        
        return result.toString();
    }
}