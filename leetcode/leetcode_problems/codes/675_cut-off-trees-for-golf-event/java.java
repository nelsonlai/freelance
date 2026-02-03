/**
 * Problem: Cut Off Trees for Golf Event
 * Difficulty: Hard
 * Tags: array, tree, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int cutOffTree(List<List<Integer>> forest) {
        List<int[]> trees = new ArrayList<>();
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest.get(i).size(); j++) {
                if (forest.get(i).get(j) > 1) {
                    trees.add(new int[]{forest.get(i).get(j), i, j});
                }
            }
        }
        
        trees.sort((a, b) -> a[0] - b[0]);
        
        int result = 0;
        int[] start = {0, 0};
        
        for (int[] tree : trees) {
            int steps = bfs(forest, start, new int[]{tree[1], tree[2]});
            if (steps == -1) {
                return -1;
            }
            result += steps;
            start = new int[]{tree[1], tree[2]};
        }
        
        return result;
    }
    
    private int bfs(List<List<Integer>> forest, int[] start, int[] end) {
        int m = forest.size();
        int n = forest.get(0).size();
        Queue<int[]> queue = new LinkedList<>();
        boolean[][] seen = new boolean[m][n];
        queue.offer(new int[]{start[0], start[1], 0});
        seen[start[0]][start[1]] = true;
        
        int[][] dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int x = curr[0], y = curr[1], steps = curr[2];
            
            if (x == end[0] && y == end[1]) {
                return steps;
            }
            
            for (int[] dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    !seen[nx][ny] && forest.get(nx).get(ny) != 0) {
                    seen[nx][ny] = true;
                    queue.offer(new int[]{nx, ny, steps + 1});
                }
            }
        }
        
        return -1;
    }
}