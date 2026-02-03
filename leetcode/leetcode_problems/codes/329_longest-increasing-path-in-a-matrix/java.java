/**
 * Problem: Longest Increasing Path in a Matrix
 * Difficulty: Hard
 * Tags: array, graph, dp, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    private Map<String, Integer> memo = new HashMap<>();
    
    public int longestIncreasingPath(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return 0;
        }
        
        int m = matrix.length;
        int n = matrix[0].length;
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result = Math.max(result, dfs(matrix, i, j));
            }
        }
        
        return result;
    }
    
    private int dfs(int[][] matrix, int i, int j) {
        String key = i + "," + j;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int maxPath = 1;
        for (int[] dir : directions) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if (ni >= 0 && ni < matrix.length && nj >= 0 && nj < matrix[0].length && 
                matrix[ni][nj] > matrix[i][j]) {
                maxPath = Math.max(maxPath, 1 + dfs(matrix, ni, nj));
            }
        }
        
        memo.put(key, maxPath);
        return maxPath;
    }
}