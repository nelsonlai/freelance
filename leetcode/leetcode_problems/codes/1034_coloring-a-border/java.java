/**
 * Problem: Coloring A Border
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: DFS to find connected component, mark border cells
 * Time Complexity: O(m * n) where m and n are grid dimensions
 * Space Complexity: O(m * n) for recursion stack
 */

import java.util.*;

class Solution {
    public int[][] colorBorder(int[][] grid, int row, int col, int color) {
        int m = grid.length, n = grid[0].length;
        int originalColor = grid[row][col];
        boolean[][] visited = new boolean[m][n];
        List<int[]> border = new ArrayList<>();
        
        dfs(grid, row, col, originalColor, visited, border, m, n);
        
        for (int[] cell : border) {
            grid[cell[0]][cell[1]] = color;
        }
        
        return grid;
    }
    
    private void dfs(int[][] grid, int i, int j, int originalColor, boolean[][] visited, 
                     List<int[]> border, int m, int n) {
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] != originalColor) {
            return;
        }
        
        visited[i][j] = true;
        boolean isBorder = false;
        
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int[] dir : directions) {
            int ni = i + dir[0], nj = j + dir[1];
            if (ni < 0 || ni >= m || nj < 0 || nj >= n || grid[ni][nj] != originalColor) {
                isBorder = true;
            } else if (!visited[ni][nj]) {
                dfs(grid, ni, nj, originalColor, visited, border, m, n);
            }
        }
        
        if (isBorder) {
            border.add(new int[]{i, j});
        }
    }
}