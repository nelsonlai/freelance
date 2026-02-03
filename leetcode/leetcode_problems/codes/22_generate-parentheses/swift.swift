class Solution {
    func generateParenthesis(_ n: Int) -> [String] {
        var result: [String] = []
        
        func backtrack(_ current: String, _ open: Int, _ close: Int) {
            if current.count == 2 * n {
                result.append(current)
                return
            }
            
            if open < n {
                backtrack(current + "(", open + 1, close)
            }
            
            if close < open {
                backtrack(current + ")", open, close + 1)
            }
        }
        
        backtrack("", 0, 0)
        return result
    }
}