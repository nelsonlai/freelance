/**
 * Problem: Wiggle Sort II
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public void wiggleSort(int[] nums) {
        int[] sorted = nums.clone();
        Arrays.sort(sorted);
        int n = nums.length;
        int mid = (n + 1) / 2;
        
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                nums[i] = sorted[mid - 1 - i / 2];
            } else {
                nums[i] = sorted[n - 1 - i / 2];
            }
        }
    }
}