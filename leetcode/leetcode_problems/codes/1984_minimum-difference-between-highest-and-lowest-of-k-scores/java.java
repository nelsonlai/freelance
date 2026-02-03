/**
 * Problem: Minimum Difference Between Highest and Lowest of K Scores
 * Difficulty: Easy
 * Tags: array, sort, sliding window
 * 
 * Approach: Sort and use sliding window of size k
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int minimumDifference(int[] nums, int k) {
        Arrays.sort(nums);
        int minDiff = Integer.MAX_VALUE;
        
        for (int i = 0; i <= nums.length - k; i++) {
            minDiff = Math.min(minDiff, nums[i + k - 1] - nums[i]);
        }
        
        return minDiff;
    }
}