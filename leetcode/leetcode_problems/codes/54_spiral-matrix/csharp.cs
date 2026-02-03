/*
 * Problem: Spiral Matrix
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public IList<int> SpiralOrder(int[][] matrix) {
        List<int> result = new List<int>();
        if (matrix == null || matrix.Length == 0 || matrix[0].Length == 0) {
            return result;
        }
        
        int top = 0, bottom = matrix.Length - 1;
        int left = 0, right = matrix[0].Length - 1;
        
        while (top <= bottom && left <= right) {
            // Right
            for (int j = left; j <= right; j++) {
                result.Add(matrix[top][j]);
            }
            top++;
            
            // Down
            for (int i = top; i <= bottom; i++) {
                result.Add(matrix[i][right]);
            }
            right--;
            
            // Left
            if (top <= bottom) {
                for (int j = right; j >= left; j--) {
                    result.Add(matrix[bottom][j]);
                }
                bottom--;
            }
            
            // Up
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    result.Add(matrix[i][left]);
                }
                left++;
            }
        }
        
        return result;
    }
}