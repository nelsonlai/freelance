/**
 * Problem: Convert 1D Array Into 2D Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Check if size matches, then reshape array
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

class Solution {
    public int[][] construct2DArray(int[] original, int m, int n) {
        if (original.length != m * n) {
            return new int[0][];
        }
        
        int[][] result = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = original[i * n + j];
            }
        }
        
        return result;
    }
}