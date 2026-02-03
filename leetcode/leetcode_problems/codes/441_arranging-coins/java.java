/**
 * Problem: Arranging Coins
 * Difficulty: Easy
 * Tags: math, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int arrangeCoins(int n) {
        return (int)((Math.sqrt(8.0 * n + 1) - 1) / 2);
    }
}