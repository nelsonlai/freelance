/*
 * Problem: N-Queens II
 * Difficulty: Hard
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public int TotalNQueens(int n) {
        int count = 0;
        HashSet<int> cols = new HashSet<int>();
        HashSet<int> diag1 = new HashSet<int>();
        HashSet<int> diag2 = new HashSet<int>();
        
        Backtrack(ref count, 0, n, cols, diag1, diag2);
        return count;
    }
    
    private void Backtrack(ref int count, int row, int n, HashSet<int> cols, 
                           HashSet<int> diag1, HashSet<int> diag2) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (cols.Contains(col) || diag1.Contains(row - col) || diag2.Contains(row + col)) {
                continue;
            }
            
            cols.Add(col);
            diag1.Add(row - col);
            diag2.Add(row + col);
            
            Backtrack(ref count, row + 1, n, cols, diag1, diag2);
            
            cols.Remove(col);
            diag1.Remove(row - col);
            diag2.Remove(row + col);
        }
    }
}