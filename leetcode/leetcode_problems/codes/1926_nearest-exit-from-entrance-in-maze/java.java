/**
 * Problem: Nearest Exit from Entrance in Maze
 * Difficulty: Medium
 * Tags: array, graph, search, BFS
 * 
 * Approach: BFS from entrance, find nearest border cell
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

import java.util.*;

class Solution {
    public int nearestExit(char[][] maze, int[] entrance) {
        int m = maze.length;
        int n = maze[0].length;
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{entrance[0], entrance[1], 0});
        boolean[][] visited = new boolean[m][n];
        visited[entrance[0]][entrance[1]] = true;
        
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int i = curr[0], j = curr[1], steps = curr[2];
            
            if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && 
                (i != entrance[0] || j != entrance[1])) {
                return steps;
            }
            
            for (int[] dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && 
                    maze[ni][nj] == '.' && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    queue.offer(new int[]{ni, nj, steps + 1});
                }
            }
        }
        
        return -1;
    }
}