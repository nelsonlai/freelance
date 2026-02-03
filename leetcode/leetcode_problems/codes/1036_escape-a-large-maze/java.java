/**
 * Problem: Escape a Large Maze
 * Difficulty: Hard
 * Tags: array, hash, search
 * 
 * Approach: BFS with limited search - if we can explore 20000 cells from source/target, we can escape
 * Time Complexity: O(B^2) where B is number of blocked cells
 * Space Complexity: O(B^2) for visited set
 */

import java.util.*;

class Solution {
    private static final int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    private static final int MAX_AREA = 20000;
    
    public boolean isEscapePossible(int[][] blocked, int[] source, int[] target) {
        Set<String> blockedSet = new HashSet<>();
        for (int[] cell : blocked) {
            blockedSet.add(cell[0] + "," + cell[1]);
        }
        
        return bfs(blockedSet, source, target) && bfs(blockedSet, target, source);
    }
    
    private boolean bfs(Set<String> blockedSet, int[] start, int[] end) {
        Queue<int[]> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.offer(start);
        visited.add(start[0] + "," + start[1]);
        
        while (!queue.isEmpty() && visited.size() < MAX_AREA) {
            int[] curr = queue.poll();
            if (curr[0] == end[0] && curr[1] == end[1]) {
                return true;
            }
            
            for (int[] dir : directions) {
                int nr = curr[0] + dir[0], nc = curr[1] + dir[1];
                String key = nr + "," + nc;
                if (nr >= 0 && nr < 1000000 && nc >= 0 && nc < 1000000 && 
                    !blockedSet.contains(key) && !visited.contains(key)) {
                    visited.add(key);
                    queue.offer(new int[]{nr, nc});
                }
            }
        }
        
        return visited.size() >= MAX_AREA;
    }
}