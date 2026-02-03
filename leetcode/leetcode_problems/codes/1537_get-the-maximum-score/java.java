/**
 * Problem: Get the Maximum Score
 * Difficulty: Hard
 * Tags: array, dp, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxSum(int[] nums1, int[] nums2) {
        int MOD = 1000000007;
        int i = 0, j = 0;
        long sum1 = 0, sum2 = 0;
        long result = 0;
        
        while (i < nums1.length || j < nums2.length) {
            if (i < nums1.length && (j >= nums2.length || nums1[i] < nums2[j])) {
                sum1 += nums1[i];
                i++;
            } else if (j < nums2.length && (i >= nums1.length || nums2[j] < nums1[i])) {
                sum2 += nums2[j];
                j++;
            } else {
                result = (result + Math.max(sum1, sum2) + nums1[i]) % MOD;
                sum1 = sum2 = 0;
                i++;
                j++;
            }
        }
        
        result = (result + Math.max(sum1, sum2)) % MOD;
        return (int) result;
    }
}