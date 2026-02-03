/**
 * Problem: Two Furthest Houses With Different Colors
 * Difficulty: Easy
 * Tags: array, greedy
 * 
 * Approach: Find maximum distance by checking first/last house with each color
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1)
 */

class Solution {
    public int maxDistance(int[] colors) {
        int n = colors.length;
        int maxDist = 0;
        
        // Check distance from first house to last house with different color
        for (int i = 0; i < n; i++) {
            if (colors[i] != colors[0]) {
                maxDist = Math.max(maxDist, i);
            }
            if (colors[i] != colors[n - 1]) {
                maxDist = Math.max(maxDist, n - 1 - i);
            }
        }
        
        return maxDist;
    }
}