/**
 * Problem: House Robber II
 * Difficulty: Medium
 * Tags: array, tree, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int rob(int[] nums) {
        if (nums.length == 1) {
            return nums[0];
        }
        
        return Math.max(robLinear(nums, 0, nums.length - 1), 
                       robLinear(nums, 1, nums.length));
    }
    
    private int robLinear(int[] nums, int start, int end) {
        int prev2 = 0;
        int prev1 = 0;
        
        for (int i = start; i < end; i++) {
            int current = Math.max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
}