/*
 * Problem: Maximum Subarray
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

public class Solution {
    public int MaxSubArray(int[] nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];
        for (int i = 1; i < nums.Length; i++) {
            currentSum = System.Math.Max(nums[i], currentSum + nums[i]);
            maxSum = System.Math.Max(maxSum, currentSum);
        }
        return maxSum;
    }
}