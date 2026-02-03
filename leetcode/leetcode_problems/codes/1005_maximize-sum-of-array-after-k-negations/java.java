/**
 * Problem: Maximize Sum Of Array After K Negations
 * Difficulty: Easy
 * Tags: array, greedy, sort
 * 
 * Approach: Greedy - negate smallest numbers first, then smallest absolute value if k remains
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int largestSumAfterKNegations(int[] nums, int k) {
        Arrays.sort(nums);
        
        for (int i = 0; i < nums.length && k > 0 && nums[i] < 0; i++) {
            nums[i] = -nums[i];
            k--;
        }
        
        if (k % 2 == 1) {
            Arrays.sort(nums);
            nums[0] = -nums[0];
        }
        
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum;
    }
}