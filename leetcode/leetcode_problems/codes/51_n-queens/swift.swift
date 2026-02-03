class Solution {
    func solveNQueens(_ n: Int) -> [[String]] {
        var result: [[String]] = []
        var board = Array(repeating: Array(repeating: Character("."), count: n), count: n)
        var cols = Set<Int>()
        var diag1 = Set<Int>()
        var diag2 = Set<Int>()
        
        func backtrack(_ row: Int) {
            if row == n {
                result.append(board.map { String($0) })
                return
            }
            
            for col in 0..<n {
                if cols.contains(col) || diag1.contains(row - col) || diag2.contains(row + col) {
                    continue
                }
                
                board[row][col] = Character("Q")
                cols.insert(col)
                diag1.insert(row - col)
                diag2.insert(row + col)
                
                backtrack(row + 1)
                
                board[row][col] = Character(".")
                cols.remove(col)
                diag1.remove(row - col)
                diag2.remove(row + col)
            }
        }
        
        backtrack(0)
        return result
    }
}