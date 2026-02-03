class Solution {
    fun convert(s: String, numRows: Int): String {
        if (numRows == 1 || numRows >= s.length) {
            return s
        }
        
        val rows = Array(numRows) { StringBuilder() }
        var currentRow = 0
        var goingDown = false
        
        for (char in s) {
            rows[currentRow].append(char)
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown
            }
            currentRow += if (goingDown) 1 else -1
        }
        
        return rows.joinToString("")
    }
}