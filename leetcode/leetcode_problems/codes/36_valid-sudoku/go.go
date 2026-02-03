// Problem: Valid Sudoku
// Difficulty: Medium
// Tags: array, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

import "fmt"

func isValidSudoku(board [][]byte) bool {
    seen := make(map[string]bool)
    
    for i := 0; i < 9; i++ {
        for j := 0; j < 9; j++ {
            if board[i][j] != '.' {
                num := string(board[i][j])
                rowKey := fmt.Sprintf("row-%d-%s", i, num)
                colKey := fmt.Sprintf("col-%d-%s", j, num)
                boxKey := fmt.Sprintf("box-%d-%d-%s", i/3, j/3, num)
                
                if seen[rowKey] || seen[colKey] || seen[boxKey] {
                    return false
                }
                
                seen[rowKey] = true
                seen[colKey] = true
                seen[boxKey] = true
            }
        }
    }
    
    return true
}