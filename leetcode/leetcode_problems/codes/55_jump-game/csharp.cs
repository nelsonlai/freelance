/*
 * Problem: Jump Game
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

public class Solution {
    public bool CanJump(int[] nums) {
        int farthest = 0;
        for (int i = 0; i < nums.Length; i++) {
            if (i > farthest) {
                return false;
            }
            farthest = System.Math.Max(farthest, i + nums[i]);
            if (farthest >= nums.Length - 1) {
                return true;
            }
        }
        return true;
    }
}