/**
 * Problem: Maximum Alternating Subarray Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - track max sum ending at each position with even/odd index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public long maximumAlternatingSubarraySum(int[] nums) {
        // dp[0] = max sum ending here with even index (add)
        // dp[1] = max sum ending here with odd index (subtract)
        long dpEven = nums[0];
        long dpOdd = Long.MIN_VALUE;
        long result = nums[0];
        
        for (int i = 1; i < nums.length; i++) {
            long newDpEven, newDpOdd;
            
            // Current position is even index (i % 2 == 0 means even position)
            if (i % 2 == 0) {
                // Can continue from previous even or start new
                newDpEven = Math.max(nums[i], dpOdd != Long.MIN_VALUE ? dpOdd + nums[i] : nums[i]);
                // Can continue from previous odd
                newDpOdd = dpOdd != Long.MIN_VALUE ? dpOdd + nums[i] : Long.MIN_VALUE;
            } else {
                // Current position is odd index
                // Can continue from previous even
                newDpOdd = dpEven - nums[i];
                // Can continue from previous odd or start new
                newDpEven = dpEven;
            }
            
            dpEven = newDpEven;
            dpOdd = newDpOdd;
            
            result = Math.max(result, Math.max(dpEven, dpOdd != Long.MIN_VALUE ? dpOdd : Long.MIN_VALUE));
        }
        
        return result;
    }
}