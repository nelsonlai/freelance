/**
 * Problem: Maximum Length of Subarray With Positive Product
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int getMaxLen(int[] nums) {
        int posLen = 0, negLen = 0;
        int maxLen = 0;
        
        for (int num : nums) {
            if (num > 0) {
                posLen = posLen + 1;
                negLen = negLen > 0 ? negLen + 1 : 0;
            } else if (num < 0) {
                int newPos = negLen > 0 ? negLen + 1 : 0;
                int newNeg = posLen + 1;
                posLen = newPos;
                negLen = newNeg;
            } else {
                posLen = 0;
                negLen = 0;
            }
            
            maxLen = Math.max(maxLen, posLen);
        }
        
        return maxLen;
    }
}