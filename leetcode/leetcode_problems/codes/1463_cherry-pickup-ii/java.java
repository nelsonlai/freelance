/**
 * Problem: Cherry Pickup II
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP - dp[row][col1][col2] = max cherries with robots at (row, col1) and (row, col2)
 * Time Complexity: O(rows * cols^2) where rows, cols are grid dimensions
 * Space Complexity: O(rows * cols^2) for DP table
 */

class Solution {
    public int cherryPickup(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int[][][] dp = new int[rows][cols][cols];
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < cols; k++) {
                    dp[i][j][k] = Integer.MIN_VALUE;
                }
            }
        }
        
        dp[0][0][cols - 1] = grid[0][0] + grid[0][cols - 1];
        
        for (int row = 1; row < rows; row++) {
            for (int col1 = 0; col1 < cols; col1++) {
                for (int col2 = 0; col2 < cols; col2++) {
                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int prevCol1 = col1 - d1;
                            int prevCol2 = col2 - d2;
                            if (prevCol1 >= 0 && prevCol1 < cols && prevCol2 >= 0 && prevCol2 < cols) {
                                if (dp[row - 1][prevCol1][prevCol2] != Integer.MIN_VALUE) {
                                    int cherries = grid[row][col1];
                                    if (col1 != col2) {
                                        cherries += grid[row][col2];
                                    }
                                    dp[row][col1][col2] = Math.max(
                                        dp[row][col1][col2],
                                        dp[row - 1][prevCol1][prevCol2] + cherries
                                    );
                                }
                            }
                        }
                    }
                }
            }
        }
        
        int result = 0;
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                result = Math.max(result, dp[rows - 1][j][k]);
            }
        }
        
        return result;
    }
}