/**
 * Problem: Max Consecutive Ones II
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int findMaxConsecutiveOnes(int[] nums) {
        int maxCount = 0;
        int count = 0;
        int prevCount = 0;
        
        for (int num : nums) {
            if (num == 1) {
                count++;
            } else {
                prevCount = count;
                count = 0;
            }
            maxCount = Math.max(maxCount, prevCount + count + 1);
        }
        
        return Math.min(maxCount, nums.length);
    }
}