/**
 * Problem: Longest Arithmetic Subsequence
 * Difficulty: Medium
 * Tags: array, dp, hash, search
 * 
 * Approach: DP - for each position and difference, track longest sequence
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2) for DP dictionary
 */

import java.util.*;

class Solution {
    public int longestArithSeqLength(int[] nums) {
        Map<String, Integer> dp = new HashMap<>();
        int n = nums.length;
        int maxLen = 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int diff = nums[i] - nums[j];
                String key = j + "," + diff;
                int len = dp.getOrDefault(key, 1) + 1;
                dp.put(i + "," + diff, len);
                maxLen = Math.max(maxLen, len);
            }
        }
        
        return maxLen;
    }
}