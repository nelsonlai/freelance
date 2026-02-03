/**
 * Problem: 4Sum II
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int fourSumCount(int[] nums1, int[] nums2, int[] nums3, int[] nums4) {
        Map<Integer, Integer> sumCount = new HashMap<>();
        for (int a : nums1) {
            for (int b : nums2) {
                sumCount.put(a + b, sumCount.getOrDefault(a + b, 0) + 1);
            }
        }
        
        int count = 0;
        for (int c : nums3) {
            for (int d : nums4) {
                count += sumCount.getOrDefault(-(c + d), 0);
            }
        }
        
        return count;
    }
}