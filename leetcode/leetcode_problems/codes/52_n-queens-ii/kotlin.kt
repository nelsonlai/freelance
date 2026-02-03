class Solution {
    fun totalNQueens(n: Int): Int {
        var count = 0
        val cols = mutableSetOf<Int>()
        val diag1 = mutableSetOf<Int>()
        val diag2 = mutableSetOf<Int>()
        
        fun backtrack(row: Int) {
            if (row == n) {
                count++
                return
            }
            
            for (col in 0 until n) {
                if (cols.contains(col) || diag1.contains(row - col) || diag2.contains(row + col)) {
                    continue
                }
                
                cols.add(col)
                diag1.add(row - col)
                diag2.add(row + col)
                
                backtrack(row + 1)
                
                cols.remove(col)
                diag1.remove(row - col)
                diag2.remove(row + col)
            }
        }
        
        backtrack(0)
        return count
    }
}