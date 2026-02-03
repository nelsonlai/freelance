// Problem: Zigzag Conversion
// Difficulty: Medium
// Tags: string
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func convert(s string, numRows int) string {
    if numRows == 1 || numRows >= len(s) {
        return s
    }
    
    rows := make([]string, numRows)
    currentRow := 0
    goingDown := false
    
    for _, char := range s {
        rows[currentRow] += string(char)
        if currentRow == 0 || currentRow == numRows-1 {
            goingDown = !goingDown
        }
        if goingDown {
            currentRow++
        } else {
            currentRow--
        }
    }
    
    result := ""
    for _, row := range rows {
        result += row
    }
    
    return result
}