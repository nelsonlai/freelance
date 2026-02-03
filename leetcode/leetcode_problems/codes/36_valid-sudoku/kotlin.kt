class Solution {
    fun isValidSudoku(board: Array<CharArray>): Boolean {
        val seen = mutableSetOf<String>()
        
        for (i in 0 until 9) {
            for (j in 0 until 9) {
                if (board[i][j] != '.') {
                    val num = board[i][j]
                    val rowKey = "row-$i-$num"
                    val colKey = "col-$j-$num"
                    val boxKey = "box-${i / 3}-${j / 3}-$num"
                    
                    if (seen.contains(rowKey) || seen.contains(colKey) || seen.contains(boxKey)) {
                        return false
                    }
                    
                    seen.add(rowKey)
                    seen.add(colKey)
                    seen.add(boxKey)
                }
            }
        }
        
        return true
    }
}