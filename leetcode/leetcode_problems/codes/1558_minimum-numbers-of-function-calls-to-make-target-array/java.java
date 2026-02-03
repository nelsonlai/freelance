/**
 * Problem: Minimum Numbers of Function Calls to Make Target Array
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int minOperations(int[] nums) {
        int totalBits = 0;
        int maxBits = 0;
        
        for (int num : nums) {
            int bits = 0;
            while (num > 0) {
                if ((num & 1) == 1) {
                    totalBits++;
                }
                num >>= 1;
                bits++;
            }
            maxBits = Math.max(maxBits, bits);
        }
        
        return totalBits + Math.max(0, maxBits - 1);
    }
}