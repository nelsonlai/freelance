/**
 * Problem: Last Day Where You Can Still Cross
 * Difficulty: Hard
 * Tags: array, graph, search, binary search, BFS/DFS
 * 
 * Approach: Binary search on day, check if path exists using BFS
 * Time Complexity: O(row * col * log(len(cells)))
 * Space Complexity: O(row * col)
 */

import java.util.*;

class Solution {
    public int latestDayToCross(int row, int col, int[][] cells) {
        int left = 0, right = cells.length;
        int result = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (canCross(row, col, cells, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    private boolean canCross(int row, int col, int[][] cells, int day) {
        int[][] grid = new int[row][col];
        for (int i = 0; i < day; i++) {
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;
            grid[r][c] = 1;
        }
        
        Queue<int[]> queue = new LinkedList<>();
        for (int c = 0; c < col; c++) {
            if (grid[0][c] == 0) {
                queue.offer(new int[]{0, c});
                grid[0][c] = 1;
            }
        }
        
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int r = curr[0], c = curr[1];
            if (r == row - 1) {
                return true;
            }
            
            for (int[] dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1;
                    queue.offer(new int[]{nr, nc});
                }
            }
        }
        
        return false;
    }
}