/**
 * Problem: Two Sum Less Than K
 * Difficulty: Easy
 * Tags: array, sort, search
 * 
 * Approach: Sort array, use two pointers to find maximum sum less than k
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int twoSumLessThanK(int[] nums, int k) {
        Arrays.sort(nums);
        int left = 0, right = nums.length - 1;
        int maxSum = -1;
        
        while (left < right) {
            int currentSum = nums[left] + nums[right];
            if (currentSum < k) {
                maxSum = Math.max(maxSum, currentSum);
                left++;
            } else {
                right--;
            }
        }
        
        return maxSum;
    }
}