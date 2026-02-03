class Solution {
    private int m, n;
    
    public int[] hitBricks(int[][] grid, int[][] hits) {
        m = grid.length;
        n = grid[0].length;
        
        for (int[] hit : hits) {
            if (grid[hit[0]][hit[1]] == 1) {
                grid[hit[0]][hit[1]] = 0;
            }
        }
        
        for (int j = 0; j < n; j++) {
            dfs(grid, 0, j);
        }
        
        int[] result = new int[hits.length];
        for (int k = hits.length - 1; k >= 0; k--) {
            int i = hits[k][0], j = hits[k][1];
            grid[i][j] = 1;
            if (i == 0 || isConnected(grid, i, j)) {
                int count = dfs(grid, i, j) - 1;
                result[k] = count;
            }
        }
        return result;
    }
    
    private int dfs(int[][] grid, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 1) {
            return 0;
        }
        grid[i][j] = 2;
        return 1 + dfs(grid, i+1, j) + dfs(grid, i-1, j) + 
               dfs(grid, i, j+1) + dfs(grid, i, j-1);
    }
    
    private boolean isConnected(int[][] grid, int i, int j) {
        int[][] dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        for (int[] dir : dirs) {
            int ni = i + dir[0], nj = j + dir[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 2) {
                return true;
            }
        }
        return false;
    }
}
