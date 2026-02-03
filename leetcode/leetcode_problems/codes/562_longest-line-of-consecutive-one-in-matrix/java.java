/**
 * Problem: Longest Line of Consecutive One in Matrix
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int longestLine(int[][] mat) {
        if (mat == null || mat.length == 0 || mat[0].length == 0) {
            return 0;
        }
        
        int m = mat.length, n = mat[0].length;
        int[][] directions = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        int maxLength = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    for (int[] dir : directions) {
                        int length = 0;
                        int x = i, y = j;
                        while (x >= 0 && x < m && y >= 0 && y < n && mat[x][y] == 1) {
                            length++;
                            x += dir[0];
                            y += dir[1];
                        }
                        maxLength = Math.max(maxLength, length);
                    }
                }
            }
        }
        
        return maxLength;
    }
}