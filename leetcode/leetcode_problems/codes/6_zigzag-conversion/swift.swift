class Solution {
    func convert(_ s: String, _ numRows: Int) -> String {
        if numRows == 1 || numRows >= s.count {
            return s
        }
        
        var rows = Array(repeating: "", count: numRows)
        var currentRow = 0
        var goingDown = false
        let chars = Array(s)
        
        for char in chars {
            rows[currentRow].append(char)
            if currentRow == 0 || currentRow == numRows - 1 {
                goingDown = !goingDown
            }
            currentRow += goingDown ? 1 : -1
        }
        
        return rows.joined()
    }
}