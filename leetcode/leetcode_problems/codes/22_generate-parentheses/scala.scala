object Solution {
    def generateParenthesis(n: Int): List[String] = {
        var result = List[String]()
        
        def backtrack(current: String, open: Int, close: Int): Unit = {
            if (current.length == 2 * n) {
                result = current :: result
                return
            }
            
            if (open < n) {
                backtrack(current + "(", open + 1, close)
            }
            
            if (close < open) {
                backtrack(current + ")", open, close + 1)
            }
        }
        
        backtrack("", 0, 0)
        result.reverse
    }
}