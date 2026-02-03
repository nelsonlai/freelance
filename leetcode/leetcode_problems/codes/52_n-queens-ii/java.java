/**
 * Problem: N-Queens II
 * Difficulty: Hard
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int totalNQueens(int n) {
        int[] count = new int[1];
        Set<Integer> cols = new HashSet<>();
        Set<Integer> diag1 = new HashSet<>();
        Set<Integer> diag2 = new HashSet<>();
        
        backtrack(count, 0, n, cols, diag1, diag2);
        return count[0];
    }
    
    private void backtrack(int[] count, int row, int n, Set<Integer> cols, 
                          Set<Integer> diag1, Set<Integer> diag2) {
        if (row == n) {
            count[0]++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (cols.contains(col) || diag1.contains(row - col) || diag2.contains(row + col)) {
                continue;
            }
            
            cols.add(col);
            diag1.add(row - col);
            diag2.add(row + col);
            
            backtrack(count, row + 1, n, cols, diag1, diag2);
            
            cols.remove(col);
            diag1.remove(row - col);
            diag2.remove(row + col);
        }
    }
}