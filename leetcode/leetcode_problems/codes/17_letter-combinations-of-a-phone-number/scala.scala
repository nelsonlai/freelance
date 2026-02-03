object Solution {
    def letterCombinations(digits: String): List[String] = {
        if (digits.isEmpty) {
            return List.empty
        }
        
        val phoneMap = Map(
            '2' -> "abc", '3' -> "def", '4' -> "ghi", '5' -> "jkl",
            '6' -> "mno", '7' -> "pqrs", '8' -> "tuv", '9' -> "wxyz"
        )
        
        var result = List[String]()
        
        def backtrack(index: Int, current: String): Unit = {
            if (index == digits.length) {
                result = current :: result
                return
            }
            
            phoneMap(digits(index)).foreach { letter =>
                backtrack(index + 1, current + letter)
            }
        }
        
        backtrack(0, "")
        result.reverse
    }
}