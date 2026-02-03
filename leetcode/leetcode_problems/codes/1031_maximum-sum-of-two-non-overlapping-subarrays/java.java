/**
 * Problem: Maximum Sum of Two Non-Overlapping Subarrays
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - track max sum of subarray ending at each position for both lengths
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

class Solution {
    public int maxSumTwoNoOverlap(int[] nums, int firstLen, int secondLen) {
        return Math.max(maxSum(nums, firstLen, secondLen), maxSum(nums, secondLen, firstLen));
    }
    
    private int maxSum(int[] nums, int L, int M) {
        int n = nums.length;
        int[] prefix = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        int[] maxL = new int[n];
        int maxSum = 0;
        
        for (int i = L - 1; i < n; i++) {
            if (i >= L) {
                maxL[i] = Math.max(maxL[i - 1], prefix[i + 1] - prefix[i + 1 - L]);
            } else {
                maxL[i] = prefix[i + 1] - prefix[i + 1 - L];
            }
        }
        
        for (int i = L + M - 1; i < n; i++) {
            int currentM = prefix[i + 1] - prefix[i + 1 - M];
            maxSum = Math.max(maxSum, maxL[i - M] + currentM);
        }
        
        return maxSum;
    }
}