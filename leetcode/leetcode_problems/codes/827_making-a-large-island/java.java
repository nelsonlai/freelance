import java.util.*;

class Solution {
    private int n;
    
    public int largestIsland(int[][] grid) {
        n = grid.length;
        int index = 2;
        Map<Integer, Integer> area = new HashMap<>();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    area.put(index, dfs(grid, i, j, index));
                    index++;
                }
            }
        }
        
        int result = area.values().stream().mapToInt(Integer::intValue).max().orElse(0);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    Set<Integer> seen = new HashSet<>();
                    int[][] dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
                    for (int[] dir : dirs) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                            seen.add(grid[ni][nj]);
                        }
                    }
                    int sum = 1;
                    for (int idx : seen) {
                        sum += area.get(idx);
                    }
                    result = Math.max(result, sum);
                }
            }
        }
        return result;
    }
    
    private int dfs(int[][] grid, int r, int c, int idx) {
        if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) {
            return 0;
        }
        grid[r][c] = idx;
        return 1 + dfs(grid, r+1, c, idx) + dfs(grid, r-1, c, idx) + 
               dfs(grid, r, c+1, idx) + dfs(grid, r, c-1, idx);
    }
}
