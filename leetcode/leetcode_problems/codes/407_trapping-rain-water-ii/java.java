/**
 * Problem: Trapping Rain Water II
 * Difficulty: Hard
 * Tags: array, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int trapRainWater(int[][] heightMap) {
        if (heightMap == null || heightMap.length == 0 || heightMap[0].length == 0) {
            return 0;
        }
        
        int m = heightMap.length;
        int n = heightMap[0].length;
        boolean[][] visited = new boolean[m][n];
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        
        for (int i = 0; i < m; i++) {
            heap.offer(new int[]{heightMap[i][0], i, 0});
            heap.offer(new int[]{heightMap[i][n-1], i, n-1});
            visited[i][0] = true;
            visited[i][n-1] = true;
        }
        
        for (int j = 0; j < n; j++) {
            heap.offer(new int[]{heightMap[0][j], 0, j});
            heap.offer(new int[]{heightMap[m-1][j], m-1, j});
            visited[0][j] = true;
            visited[m-1][j] = true;
        }
        
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int water = 0;
        
        while (!heap.isEmpty()) {
            int[] cell = heap.poll();
            int height = cell[0];
            int i = cell[1];
            int j = cell[2];
            
            for (int[] dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    water += Math.max(0, height - heightMap[ni][nj]);
                    heap.offer(new int[]{Math.max(height, heightMap[ni][nj]), ni, nj});
                }
            }
        }
        
        return water;
    }
}