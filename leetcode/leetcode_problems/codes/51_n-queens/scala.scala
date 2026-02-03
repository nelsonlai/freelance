import scala.collection.mutable

object Solution {
    def solveNQueens(n: Int): List[List[String]] = {
        val result = mutable.ListBuffer[List[String]]()
        val board = Array.fill(n)(Array.fill(n)('.'))
        val cols = mutable.Set[Int]()
        val diag1 = mutable.Set[Int]()
        val diag2 = mutable.Set[Int]()
        
        def backtrack(row: Int): Unit = {
            if (row == n) {
                result += board.map(_.mkString).toList
                return
            }
            
            for (col <- 0 until n) {
                if (cols.contains(col) || diag1.contains(row - col) || diag2.contains(row + col)) {
                    // skip
                } else {
                    board(row)(col) = 'Q'
                    cols += col
                    diag1 += (row - col)
                    diag2 += (row + col)
                    
                    backtrack(row + 1)
                    
                    board(row)(col) = '.'
                    cols -= col
                    diag1 -= (row - col)
                    diag2 -= (row + col)
                }
            }
        }
        
        backtrack(0)
        result.toList
    }
}