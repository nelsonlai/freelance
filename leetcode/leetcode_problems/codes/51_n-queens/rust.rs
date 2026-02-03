// Problem: N-Queens
// Difficulty: Hard
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

use std::collections::HashSet;

impl Solution {
    pub fn solve_n_queens(n: i32) -> Vec<Vec<String>> {
        let mut result = Vec::new();
        let mut board = vec![vec!['.'; n as usize]; n as usize];
        let mut cols = HashSet::new();
        let mut diag1 = HashSet::new();
        let mut diag2 = HashSet::new();
        
        Self::backtrack(&mut result, &mut board, 0, n as usize, 
                       &mut cols, &mut diag1, &mut diag2);
        result
    }
    
    fn backtrack(result: &mut Vec<Vec<String>>, board: &mut Vec<Vec<char>>, row: usize,
                 n: usize, cols: &mut HashSet<i32>, diag1: &mut HashSet<i32>, 
                 diag2: &mut HashSet<i32>) {
        if row == n {
            let solution: Vec<String> = board.iter()
                .map(|r| r.iter().collect())
                .collect();
            result.push(solution);
            return;
        }
        
        for col in 0..n {
            let col_i32 = col as i32;
            let row_i32 = row as i32;
            if cols.contains(&col_i32) || diag1.contains(&(row_i32 - col_i32)) || 
               diag2.contains(&(row_i32 + col_i32)) {
                continue;
            }
            
            board[row][col] = 'Q';
            cols.insert(col_i32);
            diag1.insert(row_i32 - col_i32);
            diag2.insert(row_i32 + col_i32);
            
            Self::backtrack(result, board, row + 1, n, cols, diag1, diag2);
            
            board[row][col] = '.';
            cols.remove(&col_i32);
            diag1.remove(&(row_i32 - col_i32));
            diag2.remove(&(row_i32 + col_i32));
        }
    }
}