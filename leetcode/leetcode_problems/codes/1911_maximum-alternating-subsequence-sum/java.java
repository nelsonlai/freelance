/**
 * Problem: Maximum Alternating Subsequence Sum
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: DP - track max sum ending with even/odd index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public long maxAlternatingSum(int[] nums) {
        long even = 0;  // max sum ending at even index (add)
        long odd = 0;   // max sum ending at odd index (subtract)
        
        for (int num : nums) {
            long newEven = Math.max(even, odd + num);
            long newOdd = Math.max(odd, even - num);
            even = newEven;
            odd = newOdd;
        }
        
        return Math.max(even, odd);
    }
}