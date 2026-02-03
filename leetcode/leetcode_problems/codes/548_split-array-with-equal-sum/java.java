/**
 * Problem: Split Array with Equal Sum
 * Difficulty: Hard
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean splitArray(int[] nums) {
        int n = nums.length;
        if (n < 7) {
            return false;
        }
        
        int[] prefixSum = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        
        for (int j = 3; j < n - 3; j++) {
            Set<Integer> seen = new HashSet<>();
            for (int i = 1; i < j - 1; i++) {
                if (prefixSum[i] == prefixSum[j] - prefixSum[i + 1]) {
                    seen.add(prefixSum[i]);
                }
            }
            
            for (int k = j + 2; k < n - 1; k++) {
                if (prefixSum[n] - prefixSum[k + 1] == prefixSum[k] - prefixSum[j + 1]) {
                    if (seen.contains(prefixSum[n] - prefixSum[k + 1])) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
}