/**
 * Problem: Rotate Function
 * Difficulty: Medium
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxRotateFunction(int[] nums) {
        int n = nums.length;
        int totalSum = 0;
        int f0 = 0;
        
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
            f0 += i * nums[i];
        }
        
        int maxVal = f0;
        for (int i = 1; i < n; i++) {
            f0 = f0 + totalSum - n * nums[n - i];
            maxVal = Math.max(maxVal, f0);
        }
        
        return maxVal;
    }
}