/**
 * Problem: Minimize Maximum Pair Sum in Array
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort, pair smallest with largest
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int minPairSum(int[] nums) {
        Arrays.sort(nums);
        int result = 0;
        int n = nums.length;
        for (int i = 0; i < n / 2; i++) {
            result = Math.max(result, nums[i] + nums[n - 1 - i]);
        }
        return result;
    }
}