/**
 * Problem: Minimum Total Space Wasted With K Resizing Operations
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - dp[i][j] = min waste using j resizes for first i elements
 * Time Complexity: O(n^2 * k) where n is length
 * Space Complexity: O(n * k)
 */

class Solution {
    public int minSpaceWastedKResizing(int[] nums, int k) {
        int n = nums.length;
        Integer[][] memo = new Integer[n + 1][k + 1];
        return waste(0, k, nums, memo);
    }
    
    private int waste(int i, int j, int[] nums, Integer[][] memo) {
        if (i == nums.length) {
            return 0;
        }
        if (j == 0) {
            int max = 0;
            int sum = 0;
            for (int k = i; k < nums.length; k++) {
                max = Math.max(max, nums[k]);
                sum += nums[k];
            }
            return max * (nums.length - i) - sum;
        }
        
        if (memo[i][j] != null) {
            return memo[i][j];
        }
        
        int result = Integer.MAX_VALUE;
        int max = 0;
        int sum = 0;
        
        for (int start = i; start < nums.length; start++) {
            max = Math.max(max, nums[start]);
            sum += nums[start];
            int wasteVal = max * (start - i + 1) - sum;
            result = Math.min(result, waste(start + 1, j - 1, nums, memo) + wasteVal);
        }
        
        memo[i][j] = result;
        return result;
    }
}