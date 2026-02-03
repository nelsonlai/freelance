/**
 * Problem: Find the Middle Index in Array
 * Difficulty: Easy
 * Tags: array, prefix sum
 * 
 * Approach: Find index where left sum equals right sum
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int findMiddleIndex(int[] nums) {
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        
        int leftSum = 0;
        for (int i = 0; i < nums.length; i++) {
            if (leftSum == total - leftSum - nums[i]) {
                return i;
            }
            leftSum += nums[i];
        }
        
        return -1;
    }
}