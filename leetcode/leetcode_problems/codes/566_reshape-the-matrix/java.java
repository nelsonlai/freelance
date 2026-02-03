/**
 * Problem: Reshape the Matrix
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int[][] matrixReshape(int[][] mat, int r, int c) {
        int m = mat.length, n = mat[0].length;
        if (m * n != r * c) {
            return mat;
        }
        
        int[][] result = new int[r][c];
        List<Integer> flat = new ArrayList<>();
        for (int[] row : mat) {
            for (int num : row) {
                flat.add(num);
            }
        }
        
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                result[i][j] = flat.get(i * c + j);
            }
        }
        
        return result;
    }
}