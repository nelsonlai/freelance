/**
 * Problem: Battleships in a Board
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int countBattleships(char[][] board) {
        int count = 0;
        int m = board.length;
        int n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'X') {
                    if ((i == 0 || board[i-1][j] != 'X') && (j == 0 || board[i][j-1] != 'X')) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
}