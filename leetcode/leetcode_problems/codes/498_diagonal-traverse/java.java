/**
 * Problem: Diagonal Traverse
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int[] findDiagonalOrder(int[][] mat) {
        if (mat == null || mat.length == 0 || mat[0].length == 0) {
            return new int[0];
        }
        
        int m = mat.length, n = mat[0].length;
        int[] result = new int[m * n];
        int direction = 1;
        int row = 0, col = 0;
        
        for (int i = 0; i < m * n; i++) {
            result[i] = mat[row][col];
            
            if (direction == 1) {
                if (col == n - 1) {
                    row++;
                    direction = -1;
                } else if (row == 0) {
                    col++;
                    direction = -1;
                } else {
                    row--;
                    col++;
                }
            } else {
                if (row == m - 1) {
                    col++;
                    direction = 1;
                } else if (col == 0) {
                    row++;
                    direction = 1;
                } else {
                    row++;
                    col--;
                }
            }
        }
        
        return result;
    }
}