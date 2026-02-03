object Solution {
    def convert(s: String, numRows: Int): String = {
        if (numRows == 1 || numRows >= s.length) {
            return s
        }
        
        val rows = Array.fill(numRows)(new StringBuilder)
        var currentRow = 0
        var goingDown = false
        
        for (char <- s) {
            rows(currentRow).append(char)
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown
            }
            currentRow += (if (goingDown) 1 else -1)
        }
        
        rows.mkString("")
    }
}