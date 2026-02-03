class Solution {
    func solveSudoku(_ board: inout [[Character]]) {
        solve(&board)
    }
    
    private func solve(_ board: inout [[Character]]) -> Bool {
        for i in 0..<9 {
            for j in 0..<9 {
                if board[i][j] == "." {
                    for num in "123456789" {
                        if isValid(board, row: i, col: j, num: num) {
                            board[i][j] = num
                            if solve(&board) {
                                return true
                            }
                            board[i][j] = "."
                        }
                    }
                    return false
                }
            }
        }
        return true
    }
    
    private func isValid(_ board: [[Character]], row: Int, col: Int, num: Character) -> Bool {
        for i in 0..<9 {
            if board[row][i] == num || board[i][col] == num {
                return false
            }
            if board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num {
                return false
            }
        }
        return true
    }
}