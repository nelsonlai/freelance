/**
 * Problem: Minimum Falling Path Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Dynamic programming - for each cell, take minimum from three possible paths above
 * Time Complexity: O(n * m) where n and m are dimensions
 * Space Complexity: O(1) by modifying input matrix
 */

class Solution {
    public int minFallingPathSum(int[][] matrix) {
        int n = matrix.length;
        int m = matrix[0].length;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int minPrev = matrix[i-1][j];
                if (j > 0) {
                    minPrev = Math.min(minPrev, matrix[i-1][j-1]);
                }
                if (j < m - 1) {
                    minPrev = Math.min(minPrev, matrix[i-1][j+1]);
                }
                matrix[i][j] += minPrev;
            }
        }
        
        int result = Integer.MAX_VALUE;
        for (int j = 0; j < m; j++) {
            result = Math.min(result, matrix[n-1][j]);
        }
        return result;
    }
}