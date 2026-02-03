/**
 * Problem: Maximal Rectangle
 * Difficulty: Hard
 * Tags: array, dp, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int maximalRectangle(char[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return 0;
        }
        
        int rows = matrix.length;
        int cols = matrix[0].length;
        int[] heights = new int[cols];
        int maxArea = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }
            
            Deque<Integer> stack = new ArrayDeque<>();
            for (int j = 0; j <= cols; j++) {
                while (!stack.isEmpty() && (j == cols || heights[stack.peek()] > heights[j])) {
                    int height = heights[stack.pop()];
                    int width = stack.isEmpty() ? j : j - stack.peek() - 1;
                    maxArea = Math.max(maxArea, height * width);
                }
                if (j < cols) {
                    stack.push(j);
                }
            }
        }
        
        return maxArea;
    }
}