// Problem: N-Queens II
// Difficulty: Hard
// Tags: general
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

use std::collections::HashSet;

impl Solution {
    pub fn total_n_queens(n: i32) -> i32 {
        let mut count = 0;
        let mut cols = HashSet::new();
        let mut diag1 = HashSet::new();
        let mut diag2 = HashSet::new();
        
        Self::backtrack(&mut count, 0, n as usize, &mut cols, &mut diag1, &mut diag2);
        count
    }
    
    fn backtrack(count: &mut i32, row: usize, n: usize, cols: &mut HashSet<i32>,
                 diag1: &mut HashSet<i32>, diag2: &mut HashSet<i32>) {
        if row == n {
            *count += 1;
            return;
        }
        
        for col in 0..n {
            let col_i32 = col as i32;
            let row_i32 = row as i32;
            if cols.contains(&col_i32) || diag1.contains(&(row_i32 - col_i32)) || 
               diag2.contains(&(row_i32 + col_i32)) {
                continue;
            }
            
            cols.insert(col_i32);
            diag1.insert(row_i32 - col_i32);
            diag2.insert(row_i32 + col_i32);
            
            Self::backtrack(count, row + 1, n, cols, diag1, diag2);
            
            cols.remove(&col_i32);
            diag1.remove(&(row_i32 - col_i32));
            diag2.remove(&(row_i32 + col_i32));
        }
    }
}