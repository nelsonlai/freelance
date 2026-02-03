/**
 * Problem: Shortest Bridge
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: DFS to find first island, then BFS to find shortest path to second island
 * Time Complexity: O(n * m) where n and m are dimensions
 * Space Complexity: O(n * m) for queue and visited set
 */

import java.util.*;

class Solution {
    private int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    public int shortestBridge(int[][] grid) {
        int n = grid.length;
        List<int[]> island = new ArrayList<>();
        
        // Find first island using DFS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j, island, n);
                    break;
                }
            }
            if (!island.isEmpty()) break;
        }
        
        // BFS to find shortest path to second island
        Queue<int[]> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        
        for (int[] cell : island) {
            queue.offer(new int[]{cell[0], cell[1], 0});
            visited.add(cell[0] + "," + cell[1]);
        }
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int i = curr[0], j = curr[1], dist = curr[2];
            
            for (int[] dir : directions) {
                int ni = i + dir[0], nj = j + dir[1];
                String key = ni + "," + nj;
                
                if (ni >= 0 && ni < n && nj >= 0 && nj < n && !visited.contains(key)) {
                    if (grid[ni][nj] == 1) {
                        return dist;
                    }
                    visited.add(key);
                    queue.offer(new int[]{ni, nj, dist + 1});
                }
            }
        }
        
        return -1;
    }
    
    private void dfs(int[][] grid, int i, int j, List<int[]> island, int n) {
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1) {
            return;
        }
        grid[i][j] = 2;
        island.add(new int[]{i, j});
        for (int[] dir : directions) {
            dfs(grid, i + dir[0], j + dir[1], island, n);
        }
    }
}