/**
 * Problem: Ugly Number
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean isUgly(int n) {
        if (n <= 0) {
            return false;
        }
        
        for (int factor : new int[]{2, 3, 5}) {
            while (n % factor == 0) {
                n /= factor;
            }
        }
        
        return n == 1;
    }
}