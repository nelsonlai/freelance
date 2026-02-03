/**
 * Problem: Determine Whether Matrix Can Be Obtained By Rotation
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Try all 4 rotations (0, 90, 180, 270 degrees)
 * Time Complexity: O(n^2) where n is dimension
 * Space Complexity: O(1)
 */

class Solution {
    public boolean findRotation(int[][] mat, int[][] target) {
        int n = mat.length;
        
        for (int rotation = 0; rotation < 4; rotation++) {
            if (equals(mat, target)) {
                return true;
            }
            rotate(mat);
        }
        
        return false;
    }
    
    private boolean equals(int[][] a, int[][] b) {
        int n = a.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] != b[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    private void rotate(int[][] mat) {
        int n = mat.length;
        for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - 1 - i; j++) {
                int temp = mat[i][j];
                mat[i][j] = mat[n - 1 - j][i];
                mat[n - 1 - j][i] = mat[n - 1 - i][n - 1 - j];
                mat[n - 1 - i][n - 1 - j] = mat[j][n - 1 - i];
                mat[j][n - 1 - i] = temp;
            }
        }
    }
}