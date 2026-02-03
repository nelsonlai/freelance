/**
 * Problem: Bomb Enemy
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int maxKilledEnemies(char[][] grid) {
        if (grid == null || grid.length == 0 || grid[0].length == 0) {
            return 0;
        }
        
        int m = grid.length;
        int n = grid[0].length;
        int rowHits = 0;
        int[] colHits = new int[n];
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0 || grid[i][j - 1] == 'W') {
                    rowHits = 0;
                    for (int k = j; k < n; k++) {
                        if (grid[i][k] == 'W') {
                            break;
                        }
                        if (grid[i][k] == 'E') {
                            rowHits++;
                        }
                    }
                }
                
                if (i == 0 || grid[i - 1][j] == 'W') {
                    colHits[j] = 0;
                    for (int k = i; k < m; k++) {
                        if (grid[k][j] == 'W') {
                            break;
                        }
                        if (grid[k][j] == 'E') {
                            colHits[j]++;
                        }
                    }
                }
                
                if (grid[i][j] == '0') {
                    result = Math.max(result, rowHits + colHits[j]);
                }
            }
        }
        
        return result;
    }
}