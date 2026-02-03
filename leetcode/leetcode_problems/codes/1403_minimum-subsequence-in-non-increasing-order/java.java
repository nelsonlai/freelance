/**
 * Problem: Minimum Subsequence in Non-Increasing Order
 * Difficulty: Easy
 * Tags: array, greedy, sort
 * 
 * Approach: Sort descending, greedily take largest numbers until sum > remaining
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for result
 */

import java.util.*;

class Solution {
    public List<Integer> minSubsequence(int[] nums) {
        Arrays.sort(nums);
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        
        List<Integer> result = new ArrayList<>();
        int currentSum = 0;
        
        for (int i = nums.length - 1; i >= 0; i--) {
            result.add(nums[i]);
            currentSum += nums[i];
            if (currentSum > total - currentSum) {
                break;
            }
        }
        
        return result;
    }
}