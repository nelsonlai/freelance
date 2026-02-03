class Solution {
    fun solveNQueens(n: Int): List<List<String>> {
        val result = mutableListOf<List<String>>()
        val board = Array(n) { CharArray(n) { '.' } }
        val cols = mutableSetOf<Int>()
        val diag1 = mutableSetOf<Int>()
        val diag2 = mutableSetOf<Int>()
        
        fun backtrack(row: Int) {
            if (row == n) {
                result.add(board.map { it.joinToString("") })
                return
            }
            
            for (col in 0 until n) {
                if (cols.contains(col) || diag1.contains(row - col) || diag2.contains(row + col)) {
                    continue
                }
                
                board[row][col] = 'Q'
                cols.add(col)
                diag1.add(row - col)
                diag2.add(row + col)
                
                backtrack(row + 1)
                
                board[row][col] = '.'
                cols.remove(col)
                diag1.remove(row - col)
                diag2.remove(row + col)
            }
        }
        
        backtrack(0)
        return result
    }
}