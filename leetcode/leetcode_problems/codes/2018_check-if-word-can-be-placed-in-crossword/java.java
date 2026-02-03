/**
 * Problem: Check if Word Can Be Placed In Crossword
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Check all horizontal and vertical spaces, try placing word forward and backward
 * Time Complexity: O(m * n * len(word)) where m, n are board dimensions
 * Space Complexity: O(1)
 */

class Solution {
    public boolean placeWordInCrossword(char[][] board, String word) {
        int m = board.length;
        int n = board[0].length;
        int wordLen = word.length();
        
        // Check horizontal spaces
        for (int i = 0; i < m; i++) {
            int j = 0;
            while (j < n) {
                if (board[i][j] == '#') {
                    j++;
                    continue;
                }
                
                int start = j;
                while (j < n && board[i][j] != '#') {
                    j++;
                }
                
                int spaceLen = j - start;
                if (spaceLen == wordLen) {
                    // Try forward
                    if (canPlace(board, i, start, 0, 1, word)) {
                        return true;
                    }
                    // Try backward
                    if (canPlace(board, i, start + wordLen - 1, 0, -1, word)) {
                        return true;
                    }
                }
            }
        }
        
        // Check vertical spaces
        for (int j = 0; j < n; j++) {
            int i = 0;
            while (i < m) {
                if (board[i][j] == '#') {
                    i++;
                    continue;
                }
                
                int start = i;
                while (i < m && board[i][j] != '#') {
                    i++;
                }
                
                int spaceLen = i - start;
                if (spaceLen == wordLen) {
                    // Try forward
                    if (canPlace(board, start, j, 1, 0, word)) {
                        return true;
                    }
                    // Try backward
                    if (canPlace(board, start + wordLen - 1, j, -1, 0, word)) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    private boolean canPlace(char[][] board, int i, int j, int di, int dj, String word) {
        for (int idx = 0; idx < word.length(); idx++) {
            int ni = i + di * idx;
            int nj = j + dj * idx;
            if (board[ni][nj] != ' ' && board[ni][nj] != word.charAt(idx)) {
                return false;
            }
        }
        return true;
    }
}