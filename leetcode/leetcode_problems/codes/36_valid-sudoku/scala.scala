import scala.collection.mutable

object Solution {
    def isValidSudoku(board: Array[Array[Char]]): Boolean = {
        val seen = mutable.Set[String]()
        
        for (i <- 0 until 9) {
            for (j <- 0 until 9) {
                if (board(i)(j) != '.') {
                    val num = board(i)(j)
                    val rowKey = s"row-$i-$num"
                    val colKey = s"col-$j-$num"
                    val boxKey = s"box-${i / 3}-${j / 3}-$num"
                    
                    if (seen.contains(rowKey) || seen.contains(colKey) || seen.contains(boxKey)) {
                        return false
                    }
                    
                    seen.add(rowKey)
                    seen.add(colKey)
                    seen.add(boxKey)
                }
            }
        }
        
        true
    }
}