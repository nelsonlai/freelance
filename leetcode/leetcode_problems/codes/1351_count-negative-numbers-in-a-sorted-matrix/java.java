/**
 * Problem: Count Negative Numbers in a Sorted Matrix
 * Difficulty: Easy
 * Tags: array, sort, search
 * 
 * Approach: Start from top-right, move left if negative, down if positive
 * Time Complexity: O(m + n) where m, n are matrix dimensions
 * Space Complexity: O(1)
 */

class Solution {
    public int countNegatives(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int count = 0;
        int row = 0, col = n - 1;
        
        while (row < m && col >= 0) {
            if (grid[row][col] < 0) {
                count += m - row;
                col--;
            } else {
                row++;
            }
        }
        
        return count;
    }
}
