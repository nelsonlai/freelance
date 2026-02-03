/**
 * Problem: Count Pairs in Two Arrays
 * Difficulty: Medium
 * Tags: array, sort, search, binary search
 * 
 * Approach: Rearrange inequality, sort and use binary search
 * Time Complexity: O(n log n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public long countPairs(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int[] diff = new int[n];
        for (int i = 0; i < n; i++) {
            diff[i] = nums1[i] - nums2[i];
        }
        Arrays.sort(diff);
        
        long result = 0;
        for (int i = 0; i < n; i++) {
            int target = -diff[i];
            int idx = Arrays.binarySearch(diff, target);
            if (idx < 0) {
                idx = -idx - 1;
            } else {
                while (idx < n && diff[idx] == target) {
                    idx++;
                }
            }
            result += n - Math.max(idx, i + 1);
        }
        
        return result;
    }
}