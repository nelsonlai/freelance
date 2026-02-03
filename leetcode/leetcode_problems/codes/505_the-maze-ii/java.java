/**
 * Problem: The Maze II
 * Difficulty: Medium
 * Tags: array, graph, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int shortestDistance(int[][] maze, int[] start, int[] destination) {
        int m = maze.length, n = maze[0].length;
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        Map<String, Integer> distances = new HashMap<>();
        
        heap.offer(new int[]{0, start[0], start[1]});
        distances.put(start[0] + "," + start[1], 0);
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            int dist = curr[0], x = curr[1], y = curr[2];
            
            if (x == destination[0] && y == destination[1]) {
                return dist;
            }
            
            String key = x + "," + y;
            if (distances.containsKey(key) && distances.get(key) < dist) {
                continue;
            }
            
            for (int[] dir : directions) {
                int nx = x, ny = y, steps = 0;
                while (nx + dir[0] >= 0 && nx + dir[0] < m && 
                       ny + dir[1] >= 0 && ny + dir[1] < n && 
                       maze[nx + dir[0]][ny + dir[1]] == 0) {
                    nx += dir[0];
                    ny += dir[1];
                    steps++;
                }
                
                String newKey = nx + "," + ny;
                if (!distances.containsKey(newKey) || distances.get(newKey) > dist + steps) {
                    distances.put(newKey, dist + steps);
                    heap.offer(new int[]{dist + steps, nx, ny});
                }
            }
        }
        
        return -1;
    }
}