/**
 * Problem: Remove One Element to Make the Array Strictly Increasing
 * Difficulty: Easy
 * Tags: array, greedy
 * 
 * Approach: Check if removing one element makes array strictly increasing
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public boolean canBeIncreasing(int[] nums) {
        if (isStrictlyIncreasing(nums)) {
            return true;
        }
        
        for (int i = 0; i < nums.length; i++) {
            int[] newNums = new int[nums.length - 1];
            System.arraycopy(nums, 0, newNums, 0, i);
            System.arraycopy(nums, i + 1, newNums, i, nums.length - i - 1);
            if (isStrictlyIncreasing(newNums)) {
                return true;
            }
        }
        
        return false;
    }
    
    private boolean isStrictlyIncreasing(int[] arr) {
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] <= arr[i - 1]) {
                return false;
            }
        }
        return true;
    }
}