/**
 * Problem: Number of Ways of Cutting a Pizza
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP with memoization - dp[r][c][cuts] = ways to cut from (r,c) with cuts remaining
 * Time Complexity: O(rows * cols * k * (rows + cols))
 * Space Complexity: O(rows * cols * k)
 */

import java.util.*;

class Solution {
    private int MOD = 1000000007;
    private int rows, cols;
    private int[][] prefix;
    private Map<String, Long> memo;
    
    public int ways(String[] pizza, int k) {
        rows = pizza.length;
        cols = pizza[0].length();
        prefix = new int[rows + 1][cols + 1];
        
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                prefix[i][j] = prefix[i+1][j] + prefix[i][j+1] - prefix[i+1][j+1] +
                               (pizza[i].charAt(j) == 'A' ? 1 : 0);
            }
        }
        
        memo = new HashMap<>();
        return (int) dp(0, 0, k - 1);
    }
    
    private boolean hasApple(int r1, int c1, int r2, int c2) {
        return prefix[r1][c1] - prefix[r2][c1] - prefix[r1][c2] + prefix[r2][c2] > 0;
    }
    
    private long dp(int r, int c, int cuts) {
        String key = r + "," + c + "," + cuts;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        if (cuts == 0) {
            return hasApple(r, c, rows, cols) ? 1 : 0;
        }
        
        long result = 0;
        
        for (int i = r + 1; i < rows; i++) {
            if (hasApple(r, c, i, cols)) {
                result = (result + dp(i, c, cuts - 1)) % MOD;
            }
        }
        
        for (int j = c + 1; j < cols; j++) {
            if (hasApple(r, c, rows, j)) {
                result = (result + dp(r, j, cuts - 1)) % MOD;
            }
        }
        
        memo.put(key, result);
        return result;
    }
}