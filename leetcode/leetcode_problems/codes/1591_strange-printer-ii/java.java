/**
 * Problem: Strange Printer II
 * Difficulty: Hard
 * Tags: array, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean isPrintable(int[][] targetGrid) {
        int m = targetGrid.length;
        int n = targetGrid[0].length;
        Set<Integer> colors = new HashSet<>();
        for (int[] row : targetGrid) {
            for (int cell : row) {
                colors.add(cell);
            }
        }
        
        Map<Integer, int[]> bounds = new HashMap<>();
        for (int color : colors) {
            int minR = Integer.MAX_VALUE, maxR = -1;
            int minC = Integer.MAX_VALUE, maxC = -1;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (targetGrid[i][j] == color) {
                        minR = Math.min(minR, i);
                        maxR = Math.max(maxR, i);
                        minC = Math.min(minC, j);
                        maxC = Math.max(maxC, j);
                    }
                }
            }
            bounds.put(color, new int[]{minR, maxR, minC, maxC});
        }
        
        Map<Integer, Set<Integer>> graph = new HashMap<>();
        for (int color : colors) {
            graph.put(color, new HashSet<>());
        }
        
        for (int color : colors) {
            int[] b = bounds.get(color);
            for (int i = b[0]; i <= b[1]; i++) {
                for (int j = b[2]; j <= b[3]; j++) {
                    int other = targetGrid[i][j];
                    if (other != color) {
                        graph.get(other).add(color);
                    }
                }
            }
        }
        
        Map<Integer, Integer> inDegree = new HashMap<>();
        for (int color : colors) {
            inDegree.put(color, 0);
        }
        
        for (int color : colors) {
            for (int neighbor : graph.get(color)) {
                inDegree.put(neighbor, inDegree.get(neighbor) + 1);
            }
        }
        
        Queue<Integer> queue = new LinkedList<>();
        for (int color : colors) {
            if (inDegree.get(color) == 0) {
                queue.offer(color);
            }
        }
        
        int processed = 0;
        while (!queue.isEmpty()) {
            int color = queue.poll();
            processed++;
            
            for (int neighbor : graph.get(color)) {
                inDegree.put(neighbor, inDegree.get(neighbor) - 1);
                if (inDegree.get(neighbor) == 0) {
                    queue.offer(neighbor);
                }
            }
        }
        
        return processed == colors.size();
    }
}