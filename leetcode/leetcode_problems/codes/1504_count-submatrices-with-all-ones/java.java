/**
 * Problem: Count Submatrices With All Ones
 * Difficulty: Medium
 * Tags: array, dp, stack
 * 
 * Approach: For each row, calculate consecutive 1s, use histogram approach to count rectangles
 * Time Complexity: O(m * n^2) where m, n are matrix dimensions
 * Space Complexity: O(n) for heights
 */

import java.util.Stack;

class Solution {
    public int numSubmat(int[][] mat) {
        int m = mat.length;
        int n = mat[0].length;
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            int[] heights = new int[n];
            for (int j = i; j < m; j++) {
                for (int k = 0; k < n; k++) {
                    if (mat[j][k] == 1) {
                        heights[k]++;
                    } else {
                        heights[k] = 0;
                    }
                }
                
                Stack<Integer> stack = new Stack<>();
                for (int k = 0; k < n; k++) {
                    while (!stack.isEmpty() && heights[stack.peek()] >= heights[k]) {
                        stack.pop();
                    }
                    
                    if (!stack.isEmpty()) {
                        int prev = stack.peek();
                        result += heights[k] * (k - prev);
                    } else {
                        result += heights[k] * (k + 1);
                    }
                    
                    stack.push(k);
                }
            }
        }
        
        return result;
    }
}