/**
 * Problem: Power of Four
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean isPowerOfFour(int n) {
        if (n <= 0) {
            return false;
        }
        return (n & (n - 1)) == 0 && (n - 1) % 3 == 0;
    }
}