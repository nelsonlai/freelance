object Solution {
    def solveSudoku(board: Array[Array[Char]]): Unit = {
        solve(board)
    }
    
    def solve(board: Array[Array[Char]]): Boolean = {
        for (i <- 0 until 9) {
            for (j <- 0 until 9) {
                if (board(i)(j) == '.') {
                    for (num <- '1' to '9') {
                        if (isValid(board, i, j, num)) {
                            board(i)(j) = num
                            if (solve(board)) {
                                return true
                            }
                            board(i)(j) = '.'
                        }
                    }
                    return false
                }
            }
        }
        true
    }
    
    def isValid(board: Array[Array[Char]], row: Int, col: Int, num: Char): Boolean = {
        for (i <- 0 until 9) {
            if (board(row)(i) == num || board(i)(col) == num) {
                return false
            }
            if (board(3 * (row / 3) + i / 3)(3 * (col / 3) + i % 3) == num) {
                return false
            }
        }
        true
    }
}