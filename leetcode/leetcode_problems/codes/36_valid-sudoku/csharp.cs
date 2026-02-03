/*
 * Problem: Valid Sudoku
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

using System.Collections.Generic;

public class Solution {
    public bool IsValidSudoku(char[][] board) {
        HashSet<string> seen = new HashSet<string>();
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    char num = board[i][j];
                    string rowKey = $"row-{i}-{num}";
                    string colKey = $"col-{j}-{num}";
                    string boxKey = $"box-{i / 3}-{j / 3}-{num}";
                    
                    if (seen.Contains(rowKey) || seen.Contains(colKey) || seen.Contains(boxKey)) {
                        return false;
                    }
                    
                    seen.Add(rowKey);
                    seen.Add(colKey);
                    seen.Add(boxKey);
                }
            }
        }
        
        return true;
    }
}