/**
 * Problem: Path With Maximum Minimum Value
 * Difficulty: Medium
 * Tags: array, graph, search, queue, heap
 * 
 * Approach: Use max-heap to always explore highest value paths
 * Time Complexity: O(m * n * log(m * n))
 * Space Complexity: O(m * n) for visited
 */
import java.util.PriorityQueue;

class Solution {
    public int maximumMinimumPath(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));
        boolean[][] visited = new boolean[m][n];
        heap.offer(new int[]{grid[0][0], 0, 0});
        int minVal = grid[0][0];
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            int val = curr[0];
            int r = curr[1];
            int c = curr[2];
            
            minVal = Math.min(minVal, val);
            
            if (r == m - 1 && c == n - 1) {
                return minVal;
            }
            
            if (visited[r][c]) {
                continue;
            }
            visited[r][c] = true;
            
            for (int[] dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    heap.offer(new int[]{grid[nr][nc], nr, nc});
                }
            }
        }
        
        return minVal;
    }
}