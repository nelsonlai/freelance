/**
 * Problem: Sum of All Subset XOR Totals
 * Difficulty: Easy
 * Tags: array, math, bit manipulation
 * 
 * Approach: For each bit position, count subsets where bit is set
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int subsetXORSum(int[] nums) {
        int result = 0;
        int n = nums.length;
        
        for (int bit = 0; bit < 32; bit++) {
            int count = 0;
            for (int num : nums) {
                if ((num & (1 << bit)) != 0) {
                    count++;
                }
            }
            
            if (count > 0) {
                result += (1 << bit) * (1 << (n - 1));
            }
        }
        
        return result;
    }
}