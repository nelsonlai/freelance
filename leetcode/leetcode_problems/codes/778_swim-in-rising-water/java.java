import java.util.*;

class Solution {
    public int swimInWater(int[][] grid) {
        int n = grid.length;
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        heap.offer(new int[]{grid[0][0], 0, 0});
        Set<String> visited = new HashSet<>();
        visited.add("0,0");
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            int time = curr[0], r = curr[1], c = curr[2];
            if (r == n - 1 && c == n - 1) {
                return time;
            }
            
            for (int[] dir : directions) {
                int nr = r + dir[0], nc = c + dir[1];
                String key = nr + "," + nc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited.contains(key)) {
                    visited.add(key);
                    heap.offer(new int[]{Math.max(time, grid[nr][nc]), nr, nc});
                }
            }
        }
        
        return -1;
    }
}
