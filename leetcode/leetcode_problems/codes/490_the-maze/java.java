/**
 * Problem: The Maze
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean hasPath(int[][] maze, int[] start, int[] destination) {
        int m = maze.length, n = maze[0].length;
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        Set<String> visited = new HashSet<>();
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(start);
        visited.add(start[0] + "," + start[1]);
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            if (curr[0] == destination[0] && curr[1] == destination[1]) {
                return true;
            }
            
            for (int[] dir : directions) {
                int x = curr[0], y = curr[1];
                while (x + dir[0] >= 0 && x + dir[0] < m && 
                       y + dir[1] >= 0 && y + dir[1] < n && 
                       maze[x + dir[0]][y + dir[1]] == 0) {
                    x += dir[0];
                    y += dir[1];
                }
                
                String key = x + "," + y;
                if (!visited.contains(key)) {
                    visited.add(key);
                    queue.offer(new int[]{x, y});
                }
            }
        }
        
        return false;
    }
}