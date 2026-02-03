/**
 * Problem: The Maze III
 * Difficulty: Hard
 * Tags: array, string, graph, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String findShortestWay(int[][] maze, int[] ball, int[] hole) {
        int m = maze.length, n = maze[0].length;
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        String[] dirNames = {"u", "d", "l", "r"};
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> {
            if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
            return a[3] != 0 ? a[3] : Integer.compare(a[2], b[2]);
        });
        Map<String, Integer> visited = new HashMap<>();
        heap.offer(new int[]{0, ball[0], ball[1], 0, 0});
        visited.put(ball[0] + "," + ball[1], 0);
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            int dist = curr[0], x = curr[1], y = curr[2], pathCode = curr[3], steps = curr[4];
            
            if (x == hole[0] && y == hole[1]) {
                StringBuilder path = new StringBuilder();
                int code = pathCode;
                while (code > 0) {
                    path.append(dirNames[code % 4]);
                    code /= 4;
                }
                return path.reverse().toString();
            }
            
            String key = x + "," + y;
            if (visited.containsKey(key) && visited.get(key) < dist) {
                continue;
            }
            visited.put(key, dist);
            
            for (int i = 0; i < 4; i++) {
                int[] dir = directions[i];
                int nx = x, ny = y, newSteps = 0;
                while (nx + dir[0] >= 0 && nx + dir[0] < m && 
                       ny + dir[1] >= 0 && ny + dir[1] < n && 
                       maze[nx + dir[0]][ny + dir[1]] == 0) {
                    nx += dir[0];
                    ny += dir[1];
                    newSteps++;
                    if (nx == hole[0] && ny == hole[1]) {
                        break;
                    }
                }
                
                String newKey = nx + "," + ny;
                if (!visited.containsKey(newKey) || visited.get(newKey) > dist + newSteps) {
                    int newPathCode = pathCode * 4 + i + 1;
                    heap.offer(new int[]{dist + newSteps, nx, ny, newPathCode, newSteps});
                }
            }
        }
        
        return "impossible";
    }
}