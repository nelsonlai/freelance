import java.util.*;

class Solution {
    public int containVirus(int[][] isInfected) {
        int m = isInfected.length, n = isInfected[0].length;
        int result = 0;
        
        while (true) {
            List<Region> regions = new ArrayList<>();
            Set<String> visited = new HashSet<>();
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (isInfected[i][j] == 1 && !visited.contains(i + "," + j)) {
                        Region region = new Region();
                        dfs(isInfected, i, j, visited, region);
                        if (!region.frontiers.isEmpty()) {
                            regions.add(region);
                        }
                    }
                }
            }
            
            if (regions.isEmpty()) break;
            
            regions.sort((a, b) -> b.frontiers.size() - a.frontiers.size());
            Region target = regions.get(0);
            
            for (int[] cell : target.infected) {
                isInfected[cell[0]][cell[1]] = 2;
            }
            
            result += target.frontiers.size();
            
            for (int idx = 1; idx < regions.size(); idx++) {
                Region region = regions.get(idx);
                for (int[] cell : region.infected) {
                    int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
                    for (int[] dir : dirs) {
                        int ni = cell[0] + dir[0], nj = cell[1] + dir[1];
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && isInfected[ni][nj] == 0) {
                            isInfected[ni][nj] = 1;
                        }
                    }
                }
            }
        }
        
        return result;
    }
    
    private void dfs(int[][] grid, int i, int j, Set<String> visited, Region region) {
        String key = i + "," + j;
        if (visited.contains(key)) return;
        visited.add(key);
        region.infected.add(new int[]{i, j});
        int m = grid.length, n = grid[0].length;
        int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int[] dir : dirs) {
            int ni = i + dir[0], nj = j + dir[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                if (grid[ni][nj] == 0) {
                    region.frontiers.add(ni + "," + nj);
                } else if (grid[ni][nj] == 1) {
                    dfs(grid, ni, nj, visited, region);
                }
            }
        }
    }
    
    class Region {
        List<int[]> infected = new ArrayList<>();
        Set<String> frontiers = new HashSet<>();
    }
}
