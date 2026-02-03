/**
 * Problem: Partition to K Equal Sum Subsets
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public boolean canPartitionKSubsets(int[] nums, int k) {
        int total = Arrays.stream(nums).sum();
        if (total % k != 0) {
            return false;
        }
        
        int target = total / k;
        Arrays.sort(nums);
        reverse(nums);
        boolean[] used = new boolean[nums.length];
        
        return backtrack(nums, used, 0, 0, target, k);
    }
    
    private boolean backtrack(int[] nums, boolean[] used, int start, int currentSum, int target, int remaining) {
        if (remaining == 0) {
            return true;
        }
        
        if (currentSum == target) {
            return backtrack(nums, used, 0, 0, target, remaining - 1);
        }
        
        for (int i = start; i < nums.length; i++) {
            if (used[i] || currentSum + nums[i] > target) {
                continue;
            }
            
            used[i] = true;
            if (backtrack(nums, used, i + 1, currentSum + nums[i], target, remaining)) {
                return true;
            }
            used[i] = false;
            
            while (i + 1 < nums.length && nums[i] == nums[i + 1]) {
                i++;
            }
        }
        
        return false;
    }
    
    private void reverse(int[] nums) {
        int left = 0, right = nums.length - 1;
        while (left < right) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }
}