// Problem: N-Queens II
// Difficulty: Hard
// Tags: general
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

func totalNQueens(n int) int {
    count := 0
    cols := make(map[int]bool)
    diag1 := make(map[int]bool)
    diag2 := make(map[int]bool)
    
    var backtrack func(int)
    backtrack = func(row int) {
        if row == n {
            count++
            return
        }
        
        for col := 0; col < n; col++ {
            if cols[col] || diag1[row-col] || diag2[row+col] {
                continue
            }
            
            cols[col] = true
            diag1[row-col] = true
            diag2[row+col] = true
            
            backtrack(row + 1)
            
            delete(cols, col)
            delete(diag1, row-col)
            delete(diag2, row+col)
        }
    }
    
    backtrack(0)
    return count
}