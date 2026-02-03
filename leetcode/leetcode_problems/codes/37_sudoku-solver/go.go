// Problem: Sudoku Solver
// Difficulty: Hard
// Tags: array, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

func solveSudoku(board [][]byte) {
    var solve func() bool
    solve = func() bool {
        for i := 0; i < 9; i++ {
            for j := 0; j < 9; j++ {
                if board[i][j] == '.' {
                    for num := byte('1'); num <= '9'; num++ {
                        if isValid(board, i, j, num) {
                            board[i][j] = num
                            if solve() {
                                return true
                            }
                            board[i][j] = '.'
                        }
                    }
                    return false
                }
            }
        }
        return true
    }
    solve()
}

func isValid(board [][]byte, row, col int, num byte) bool {
    for i := 0; i < 9; i++ {
        if board[row][i] == num || board[i][col] == num {
            return false
        }
        if board[3*(row/3)+i/3][3*(col/3)+i%3] == num {
            return false
        }
    }
    return true
}