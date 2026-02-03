/**
 * Problem: Max Consecutive Ones III
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Sliding window - maintain window with at most k zeros
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public int longestOnes(int[] nums, int k) {
        int left = 0;
        int maxLen = 0;
        int zeroCount = 0;
        
        for (int right = 0; right < nums.length; right++) {
            if (nums[right] == 0) {
                zeroCount++;
            }
            
            while (zeroCount > k) {
                if (nums[left] == 0) {
                    zeroCount--;
                }
                left++;
            }
            
            maxLen = Math.max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
}