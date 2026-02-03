/**
 * Problem: Minimum Number of Days to Disconnect Island
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int minDays(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        
        int islands = countIslands(grid, m, n);
        if (islands != 1) {
            return 0;
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if (countIslands(grid, m, n) != 1) {
                        return 1;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        
        return 2;
    }
    
    private int countIslands(int[][] grid, int m, int n) {
        boolean[][] visited = new boolean[m][n];
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    count++;
                    dfs(grid, i, j, visited, m, n);
                }
            }
        }
        
        return count;
    }
    
    private void dfs(int[][] grid, int r, int c, boolean[][] visited, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c] || grid[r][c] == 0) {
            return;
        }
        visited[r][c] = true;
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int[] dir : directions) {
            dfs(grid, r + dir[0], c + dir[1], visited, m, n);
        }
    }
}