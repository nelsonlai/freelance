/**
 * Problem: Shortest Unsorted Continuous Subarray
 * Difficulty: Medium
 * Tags: array, greedy, sort, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int findUnsortedSubarray(int[] nums) {
        int[] sorted = nums.clone();
        Arrays.sort(sorted);
        
        int start = -1, end = -1;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != sorted[i]) {
                if (start == -1) {
                    start = i;
                }
                end = i;
            }
        }
        
        return start == -1 ? 0 : end - start + 1;
    }
}