/**
 * Problem: Matrix Diagonal Sum
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int diagonalSum(int[][] mat) {
        int n = mat.length;
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            result += mat[i][i];
            result += mat[i][n - 1 - i];
        }
        
        if (n % 2 == 1) {
            result -= mat[n / 2][n / 2];
        }
        
        return result;
    }
}