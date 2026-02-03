/**
 * Problem: Valid Sudoku
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean isValidSudoku(char[][] board) {
        Set<String> seen = new HashSet<>();
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    char num = board[i][j];
                    String rowKey = "row-" + i + "-" + num;
                    String colKey = "col-" + j + "-" + num;
                    String boxKey = "box-" + (i / 3) + "-" + (j / 3) + "-" + num;
                    
                    if (seen.contains(rowKey) || seen.contains(colKey) || seen.contains(boxKey)) {
                        return false;
                    }
                    
                    seen.add(rowKey);
                    seen.add(colKey);
                    seen.add(boxKey);
                }
            }
        }
        
        return true;
    }
}