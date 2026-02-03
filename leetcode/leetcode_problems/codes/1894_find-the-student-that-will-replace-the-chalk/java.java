/**
 * Problem: Find the Student that Will Replace the Chalk
 * Difficulty: Medium
 * Tags: array, search, prefix sum
 * 
 * Approach: Use prefix sum, find position after k mod total
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int chalkReplacer(int[] chalk, int k) {
        long total = 0;
        for (int c : chalk) {
            total += c;
        }
        k %= total;
        
        for (int i = 0; i < chalk.length; i++) {
            if (k < chalk[i]) {
                return i;
            }
            k -= chalk[i];
        }
        
        return 0;
    }
}