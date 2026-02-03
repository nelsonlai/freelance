class Solution {
    func isValidSudoku(_ board: [[Character]]) -> Bool {
        var seen = Set<String>()
        
        for i in 0..<9 {
            for j in 0..<9 {
                if board[i][j] != "." {
                    let num = String(board[i][j])
                    let rowKey = "row-\(i)-\(num)"
                    let colKey = "col-\(j)-\(num)"
                    let boxKey = "box-\(i / 3)-\(j / 3)-\(num)"
                    
                    if seen.contains(rowKey) || seen.contains(colKey) || seen.contains(boxKey) {
                        return false
                    }
                    
                    seen.insert(rowKey)
                    seen.insert(colKey)
                    seen.insert(boxKey)
                }
            }
        }
        
        return true
    }
}