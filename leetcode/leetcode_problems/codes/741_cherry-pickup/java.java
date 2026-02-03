import java.util.*;

class Solution {
    private int n;
    private int[][] grid;
    private Map<String, Integer> memo;
    
    public int cherryPickup(int[][] grid) {
        this.n = grid.length;
        this.grid = grid;
        this.memo = new HashMap<>();
        return Math.max(0, dp(0, 0, 0, 0));
    }
    
    private int dp(int r1, int c1, int r2, int c2) {
        if (r1 == n || c1 == n || r2 == n || c2 == n || grid[r1][c1] == -1 || grid[r2][c2] == -1) {
            return Integer.MIN_VALUE;
        }
        
        if (r1 == n - 1 && c1 == n - 1) {
            return grid[r1][c1];
        }
        
        String key = r1 + "," + c1 + "," + r2 + "," + c2;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = grid[r1][c1];
        if (r1 != r2 || c1 != c2) {
            result += grid[r2][c2];
        }
        
        result += Math.max(
            Math.max(dp(r1 + 1, c1, r2 + 1, c2), dp(r1 + 1, c1, r2, c2 + 1)),
            Math.max(dp(r1, c1 + 1, r2 + 1, c2), dp(r1, c1 + 1, r2, c2 + 1))
        );
        
        memo.put(key, result);
        return result;
    }
}
