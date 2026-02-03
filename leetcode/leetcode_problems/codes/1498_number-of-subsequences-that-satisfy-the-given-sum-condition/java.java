/**
 * Problem: Number of Subsequences That Satisfy the Given Sum Condition
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int numSubseq(int[] nums, int target) {
        int MOD = 1000000007;
        Arrays.sort(nums);
        int n = nums.length;
        
        // Precompute powers of 2
        long[] power = new long[n + 1];
        power[0] = 1;
        for (int i = 1; i <= n; i++) {
            power[i] = (power[i - 1] * 2) % MOD;
        }
        
        long result = 0;
        int left = 0, right = n - 1;
        
        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                result = (result + power[right - left]) % MOD;
                left++;
            } else {
                right--;
            }
        }
        
        return (int) result;
    }
}