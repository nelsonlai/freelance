/**
 * Problem: Out of Boundary Paths
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private int MOD = 1000000007;
    private Map<String, Integer> memo = new HashMap<>();
    
    public int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        return dp(maxMove, startRow, startColumn, m, n);
    }
    
    private int dp(int moves, int row, int col, int m, int n) {
        if (row < 0 || row >= m || col < 0 || col >= n) {
            return 1;
        }
        if (moves == 0) {
            return 0;
        }
        
        String key = moves + "," + row + "," + col;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = 0;
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int[] dir : directions) {
            result = (result + dp(moves - 1, row + dir[0], col + dir[1], m, n)) % MOD;
        }
        
        memo.put(key, result);
        return result;
    }
}