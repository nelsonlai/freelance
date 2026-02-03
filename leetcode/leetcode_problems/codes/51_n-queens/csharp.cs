/*
 * Problem: N-Queens
 * Difficulty: Hard
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public IList<IList<string>> SolveNQueens(int n) {
        IList<IList<string>> result = new List<IList<string>>();
        char[][] board = new char[n][];
        for (int i = 0; i < n; i++) {
            board[i] = new char[n];
            for (int j = 0; j < n; j++) {
                board[i][j] = '.';
            }
        }
        HashSet<int> cols = new HashSet<int>();
        HashSet<int> diag1 = new HashSet<int>();
        HashSet<int> diag2 = new HashSet<int>();
        
        Backtrack(result, board, 0, n, cols, diag1, diag2);
        return result;
    }
    
    private void Backtrack(IList<IList<string>> result, char[][] board, int row,
                           int n, HashSet<int> cols, HashSet<int> diag1, HashSet<int> diag2) {
        if (row == n) {
            List<string> solution = new List<string>();
            for (int i = 0; i < n; i++) {
                solution.Add(new string(board[i]));
            }
            result.Add(solution);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (cols.Contains(col) || diag1.Contains(row - col) || diag2.Contains(row + col)) {
                continue;
            }
            
            board[row][col] = 'Q';
            cols.Add(col);
            diag1.Add(row - col);
            diag2.Add(row + col);
            
            Backtrack(result, board, row + 1, n, cols, diag1, diag2);
            
            board[row][col] = '.';
            cols.Remove(col);
            diag1.Remove(row - col);
            diag2.Remove(row + col);
        }
    }
}