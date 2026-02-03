/**
 * Problem: Shortest Distance from All Buildings
 * Difficulty: Hard
 * Tags: array, tree, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int shortestDistance(int[][] grid) {
        if (grid == null || grid.length == 0 || grid[0].length == 0) {
            return -1;
        }
        
        int m = grid.length;
        int n = grid[0].length;
        int buildings = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    buildings++;
                }
            }
        }
        
        int[][] distance = new int[m][n];
        int[][] reach = new int[m][n];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (!bfs(grid, i, j, distance, reach, buildings)) {
                        return -1;
                    }
                }
            }
        }
        
        int minDistance = Integer.MAX_VALUE;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && reach[i][j] == buildings) {
                    minDistance = Math.min(minDistance, distance[i][j]);
                }
            }
        }
        
        return minDistance == Integer.MAX_VALUE ? -1 : minDistance;
    }
    
    private boolean bfs(int[][] grid, int startI, int startJ, int[][] distance, 
                       int[][] reach, int totalBuildings) {
        int m = grid.length;
        int n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{startI, startJ, 0});
        visited[startI][startJ] = true;
        int count = 1;
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int i = curr[0];
            int j = curr[1];
            int dist = curr[2];
            
            for (int[] dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    if (grid[ni][nj] == 0) {
                        distance[ni][nj] += dist + 1;
                        reach[ni][nj]++;
                        queue.offer(new int[]{ni, nj, dist + 1});
                    } else if (grid[ni][nj] == 1) {
                        count++;
                    }
                }
            }
        }
        
        return count == totalBuildings;
    }
}