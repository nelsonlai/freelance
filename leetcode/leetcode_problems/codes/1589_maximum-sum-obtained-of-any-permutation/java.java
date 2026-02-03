/**
 * Problem: Maximum Sum Obtained of Any Permutation
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    
    public int maxSumRangeQuery(int[] nums, int[][] requests) {
        int n = nums.length;
        int[] freq = new int[n + 1];
        
        for (int[] req : requests) {
            freq[req[0]]++;
            freq[req[1] + 1]--;
        }
        
        for (int i = 1; i < n; i++) {
            freq[i] += freq[i - 1];
        }
        
        Arrays.sort(freq, 0, n);
        Arrays.sort(nums);
        
        long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + (long)freq[i] * nums[i]) % MOD;
        }
        
        return (int) result;
    }
}