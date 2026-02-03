import java.util.*;

class Solution {
    public int numDistinctIslands2(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        Set<String> seen = new HashSet<>();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    List<int[]> shape = dfs(grid, i, j);
                    seen.add(normalize(shape));
                }
            }
        }
        
        return seen.size();
    }
    
    private List<int[]> dfs(int[][] grid, int i, int j) {
        int m = grid.length, n = grid[0].length;
        List<int[]> shape = new ArrayList<>();
        Stack<int[]> stack = new Stack<>();
        stack.push(new int[]{i, j});
        grid[i][j] = 0;
        
        while (!stack.isEmpty()) {
            int[] curr = stack.pop();
            shape.add(new int[]{curr[0] - i, curr[1] - j});
            int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (int[] dir : dirs) {
                int nr = curr[0] + dir[0], nc = curr[1] + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    grid[nr][nc] = 0;
                    stack.push(new int[]{nr, nc});
                }
            }
        }
        return shape;
    }
    
    private String normalize(List<int[]> shape) {
        List<List<int[]>> rotations = new ArrayList<>();
        rotations.add(new ArrayList<>(shape));
        rotations.add(transform(shape, (x, y) -> new int[]{-x, y}));
        rotations.add(transform(shape, (x, y) -> new int[]{x, -y}));
        rotations.add(transform(shape, (x, y) -> new int[]{-x, -y}));
        rotations.add(transform(shape, (x, y) -> new int[]{y, x}));
        rotations.add(transform(shape, (x, y) -> new int[]{-y, x}));
        rotations.add(transform(shape, (x, y) -> new int[]{y, -x}));
        rotations.add(transform(shape, (x, y) -> new int[]{-y, -x}));
        
        for (List<int[]> rot : rotations) {
            rot.sort((a, b) -> a[0] != b[0] ? a[0] - b[0] : a[1] - b[1]);
        }
        
        rotations.sort((a, b) -> {
            for (int i = 0; i < Math.min(a.size(), b.size()); i++) {
                if (a.get(i)[0] != b.get(i)[0]) return a.get(i)[0] - b.get(i)[0];
                if (a.get(i)[1] != b.get(i)[1]) return a.get(i)[1] - b.get(i)[1];
            }
            return a.size() - b.size();
        });
        
        List<int[]> first = rotations.get(0);
        if (first.isEmpty()) return "";
        int minX = first.get(0)[0], minY = first.get(0)[1];
        StringBuilder sb = new StringBuilder();
        for (int[] p : first) {
            sb.append((p[0] - minX)).append(",").append((p[1] - minY)).append(";");
        }
        return sb.toString();
    }
    
    private List<int[]> transform(List<int[]> shape, java.util.function.BiFunction<Integer, Integer, int[]> func) {
        List<int[]> result = new ArrayList<>();
        for (int[] p : shape) {
            result.add(func.apply(p[0], p[1]));
        }
        return result;
    }
}
