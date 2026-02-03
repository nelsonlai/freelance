/**
 * Problem: Minesweeper
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    private int[][] directions = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    
    public char[][] updateBoard(char[][] board, int[] click) {
        int m = board.length, n = board[0].length;
        int row = click[0], col = click[1];
        
        if (board[row][col] == 'M') {
            board[row][col] = 'X';
            return board;
        }
        
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{row, col});
        board[row][col] = 'B';
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int r = curr[0], c = curr[1];
            int mines = 0;
            
            for (int[] dir : directions) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'M') {
                    mines++;
                }
            }
            
            if (mines > 0) {
                board[r][c] = (char)('0' + mines);
            } else {
                for (int[] dir : directions) {
                    int nr = r + dir[0], nc = c + dir[1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'E') {
                        board[nr][nc] = 'B';
                        queue.offer(new int[]{nr, nc});
                    }
                }
            }
        }
        
        return board;
    }
}