/**
 * Problem: Shortest Path in Binary Matrix
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: BFS to find shortest path from (0,0) to (n-1,n-1)
 * Time Complexity: O(n^2) where n is grid size
 * Space Complexity: O(n^2) for queue
 */

import java.util.*;

class Solution {
    public int shortestPathBinaryMatrix(int[][] grid) {
        int n = grid.length;
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1;
        }
        
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, 1});
        grid[0][0] = 1;
        
        int[][] directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int r = curr[0], c = curr[1], dist = curr[2];
            
            if (r == n - 1 && c == n - 1) {
                return dist;
            }
            
            for (int[] dir : directions) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1;
                    queue.offer(new int[]{nr, nc, dist + 1});
                }
            }
        }
        
        return -1;
    }
}