class Solution {
    fun solveSudoku(board: Array<CharArray>): Unit {
        solve(board)
    }
    
    private fun solve(board: Array<CharArray>): Boolean {
        for (i in 0 until 9) {
            for (j in 0 until 9) {
                if (board[i][j] == '.') {
                    for (num in '1'..'9') {
                        if (isValid(board, i, j, num)) {
                            board[i][j] = num
                            if (solve(board)) {
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
    
    private fun isValid(board: Array<CharArray>, row: Int, col: Int, num: Char): Boolean {
        for (i in 0 until 9) {
            if (board[row][i] == num || board[i][col] == num) {
                return false
            }
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) {
                return false
            }
        }
        return true
    }
}