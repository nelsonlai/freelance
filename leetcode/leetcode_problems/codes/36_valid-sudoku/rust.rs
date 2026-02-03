// Problem: Valid Sudoku
// Difficulty: Medium
// Tags: array, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

use std::collections::HashSet;

impl Solution {
    pub fn is_valid_sudoku(board: Vec<Vec<char>>) -> bool {
        let mut seen = HashSet::new();
        
        for i in 0..9 {
            for j in 0..9 {
                if board[i][j] != '.' {
                    let num = board[i][j];
                    let row_key = format!("row-{}-{}", i, num);
                    let col_key = format!("col-{}-{}", j, num);
                    let box_key = format!("box-{}-{}-{}", i / 3, j / 3, num);
                    
                    if seen.contains(&row_key) || seen.contains(&col_key) || seen.contains(&box_key) {
                        return false;
                    }
                    
                    seen.insert(row_key);
                    seen.insert(col_key);
                    seen.insert(box_key);
                }
            }
        }
        
        true
    }
}