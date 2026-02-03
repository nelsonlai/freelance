/**
 * Problem: Smallest Good Base
 * Difficulty: Hard
 * Tags: string, math, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String smallestGoodBase(String n) {
        long num = Long.parseLong(n);
        
        for (int m = (int)(Math.log(num) / Math.log(2)); m > 1; m--) {
            long k = (long)Math.pow(num, 1.0 / m);
            if (k >= 2) {
                long total = (long)((Math.pow(k, m + 1) - 1) / (k - 1));
                if (total == num) {
                    return String.valueOf(k);
                }
            }
        }
        
        return String.valueOf(num - 1);
    }
}