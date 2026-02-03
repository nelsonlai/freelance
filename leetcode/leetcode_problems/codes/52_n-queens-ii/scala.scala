import scala.collection.mutable

object Solution {
    def totalNQueens(n: Int): Int = {
        var count = 0
        val cols = mutable.Set[Int]()
        val diag1 = mutable.Set[Int]()
        val diag2 = mutable.Set[Int]()
        
        def backtrack(row: Int): Unit = {
            if (row == n) {
                count += 1
                return
            }
            
            for (col <- 0 until n) {
                if (!cols.contains(col) && !diag1.contains(row - col) && !diag2.contains(row + col)) {
                    cols += col
                    diag1 += (row - col)
                    diag2 += (row + col)
                    
                    backtrack(row + 1)
                    
                    cols -= col
                    diag1 -= (row - col)
                    diag2 -= (row + col)
                }
            }
        }
        
        backtrack(0)
        count
    }
}