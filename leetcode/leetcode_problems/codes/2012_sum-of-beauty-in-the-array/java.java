/**
 * Problem: Sum of Beauty in the Array
 * Difficulty: Medium
 * Tags: array, prefix/suffix arrays
 * 
 * Approach: Precompute max from left and min from right for each position
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public int sumOfBeauties(int[] nums) {
        int n = nums.length;
        int[] maxLeft = new int[n];
        int[] minRight = new int[n];
        
        maxLeft[0] = nums[0];
        for (int i = 1; i < n; i++) {
            maxLeft[i] = Math.max(maxLeft[i - 1], nums[i]);
        }
        
        minRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minRight[i] = Math.min(minRight[i + 1], nums[i]);
        }
        
        int result = 0;
        for (int i = 1; i < n - 1; i++) {
            if (maxLeft[i - 1] < nums[i] && nums[i] < minRight[i + 1]) {
                result += 2;
            } else if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1]) {
                result += 1;
            }
        }
        
        return result;
    }
}