/**
 * Problem: Game of Life
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public void gameOfLife(int[][] board) {
        int m = board.length;
        int n = board[0].length;
        int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int liveNeighbors = 0;
                for (int[] dir : directions) {
                    int r = i + dir[0];
                    int c = j + dir[1];
                    if (r >= 0 && r < m && c >= 0 && c < n) {
                        if (board[r][c] == 1 || board[r][c] == -1) {
                            liveNeighbors++;
                        }
                    }
                }
                
                if (board[i][j] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        board[i][j] = -1;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        board[i][j] = 2;
                    }
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == -1) {
                    board[i][j] = 0;
                } else if (board[i][j] == 2) {
                    board[i][j] = 1;
                }
            }
        }
    }
}