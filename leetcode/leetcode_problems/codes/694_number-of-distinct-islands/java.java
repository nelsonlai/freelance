/**
 * Problem: Number of Distinct Islands
 * Difficulty: Medium
 * Tags: graph, hash, search
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int numDistinctIslands(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        Set<String> seen = new HashSet<>();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    List<String> shape = new ArrayList<>();
                    dfs(grid, i, j, shape, i, j);
                    seen.add(String.join(",", shape));
                }
            }
        }
        
        return seen.size();
    }
    
    private void dfs(int[][] grid, int i, int j, List<String> shape, int startI, int startJ) {
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] == 0) {
            return;
        }
        
        grid[i][j] = 0;
        shape.add((i - startI) + "," + (j - startJ));
        
        dfs(grid, i + 1, j, shape, startI, startJ);
        dfs(grid, i - 1, j, shape, startI, startJ);
        dfs(grid, i, j + 1, shape, startI, startJ);
        dfs(grid, i, j - 1, shape, startI, startJ);
    }
}