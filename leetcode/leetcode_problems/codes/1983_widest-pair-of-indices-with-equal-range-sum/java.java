/**
 * Problem: Widest Pair of Indices With Equal Range Sum
 * Difficulty: Medium
 * Tags: array, hash, prefix sum
 * 
 * Approach: Use prefix sum difference, find widest pair with same difference
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int widestPairOfIndices(int[] nums1, int[] nums2) {
        Map<Integer, Integer> diffMap = new HashMap<>();
        diffMap.put(0, -1);
        int diff = 0;
        int maxWidth = 0;
        
        for (int i = 0; i < nums1.length; i++) {
            diff += nums1[i] - nums2[i];
            if (diffMap.containsKey(diff)) {
                maxWidth = Math.max(maxWidth, i - diffMap.get(diff));
            } else {
                diffMap.put(diff, i);
            }
        }
        
        return maxWidth;
    }
}