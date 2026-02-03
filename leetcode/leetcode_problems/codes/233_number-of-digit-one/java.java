/**
 * Problem: Number of Digit One
 * Difficulty: Hard
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int countDigitOne(int n) {
        int count = 0;
        long i = 1;
        
        while (i <= n) {
            long divider = i * 10;
            count += (n / divider) * i + Math.min(Math.max(n % divider - i + 1, 0), i);
            i *= 10;
        }
        
        return count;
    }
}