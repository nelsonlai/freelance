/**
 * Problem: Minimum XOR Sum of Two Arrays
 * Difficulty: Hard
 * Tags: array, dp, bitmask
 * 
 * Approach: DP with bitmask - dp[mask] = min XOR sum using elements in mask
 * Time Complexity: O(n * 2^n) where n is length
 * Space Complexity: O(2^n)
 */

class Solution {
    public int minimumXORSum(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int[] dp = new int[1 << n];
        for (int i = 1; i < (1 << n); i++) {
            dp[i] = Integer.MAX_VALUE;
        }
        
        for (int mask = 0; mask < (1 << n); mask++) {
            int count = Integer.bitCount(mask);
            if (count >= n) continue;
            
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) == 0) {
                    int newMask = mask | (1 << j);
                    dp[newMask] = Math.min(dp[newMask], dp[mask] + (nums1[count] ^ nums2[j]));
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
}