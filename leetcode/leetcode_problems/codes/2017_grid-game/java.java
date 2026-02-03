/**
 * Problem: Grid Game
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public long gridGame(int[][] grid) {
        int n = grid[0].length;
        long topSum = 0;
        for (int num : grid[0]) {
            topSum += num;
        }
        long bottomSum = 0;
        long result = Long.MAX_VALUE;
        
        for (int i = 0; i < n; i++) {
            topSum -= grid[0][i];
            result = Math.min(result, Math.max(topSum, bottomSum));
            bottomSum += grid[1][i];
        }
        
        return result;
    }
}