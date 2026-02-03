/**
 * Problem: Knight Probability in Chessboard
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    private double[][][] memo;
    private int[][] directions = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                                 {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    
    public double knightProbability(int n, int k, int row, int column) {
        memo = new double[n][n][k + 1];
        return dp(n, k, row, column);
    }
    
    private double dp(int n, int moves, int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= n) {
            return 0;
        }
        if (moves == 0) {
            return 1;
        }
        if (memo[r][c][moves] != 0) {
            return memo[r][c][moves];
        }
        
        double total = 0;
        for (int[] dir : directions) {
            total += dp(n, moves - 1, r + dir[0], c + dir[1]);
        }
        
        memo[r][c][moves] = total / 8.0;
        return memo[r][c][moves];
    }
}