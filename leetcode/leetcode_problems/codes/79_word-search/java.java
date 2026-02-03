/**
 * Problem: Word Search
 * Difficulty: Medium
 * Tags: array, string, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    private int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    public boolean exist(char[][] board, String word) {
        int m = board.length;
        int n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    private boolean dfs(char[][] board, int row, int col, String word, int index) {
        if (index == word.length()) {
            return true;
        }
        
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
            return false;
        }
        
        if (board[row][col] != word.charAt(index)) {
            return false;
        }
        
        char temp = board[row][col];
        board[row][col] = '#';
        
        for (int[] dir : directions) {
            if (dfs(board, row + dir[0], col + dir[1], word, index + 1)) {
                return true;
            }
        }
        
        board[row][col] = temp;
        return false;
    }
}