import java.util.*;

class Solution {
    public int shortestPathAllKeys(String[] grid) {
        int m = grid.length, n = grid[0].length();
        int[] start = null;
        int keys = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = grid[i].charAt(j);
                if (c == '@') {
                    start = new int[]{i, j};
                } else if (Character.isLowerCase(c)) {
                    keys |= 1 << (c - 'a');
                }
            }
        }
        
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{start[0], start[1], 0, 0});
        Set<String> visited = new HashSet<>();
        visited.add(start[0] + "," + start[1] + ",0");
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int r = curr[0], c = curr[1], collected = curr[2], steps = curr[3];
            
            if (collected == keys) {
                return steps;
            }
            
            int[][] dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
            for (int[] dir : dirs) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr].charAt(nc) != '#') {
                    char cell = grid[nr].charAt(nc);
                    int newCollected = collected;
                    
                    if (Character.isLowerCase(cell)) {
                        newCollected |= 1 << (cell - 'a');
                    } else if (Character.isUpperCase(cell)) {
                        if ((collected & (1 << (cell - 'A'))) == 0) {
                            continue;
                        }
                    }
                    
                    String state = nr + "," + nc + "," + newCollected;
                    if (!visited.contains(state)) {
                        visited.add(state);
                        queue.offer(new int[]{nr, nc, newCollected, steps + 1});
                    }
                }
            }
        }
        return -1;
    }
}
