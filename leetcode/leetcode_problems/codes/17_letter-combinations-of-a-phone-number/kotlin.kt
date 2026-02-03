class Solution {
    fun letterCombinations(digits: String): List<String> {
        if (digits.isEmpty()) {
            return emptyList()
        }
        
        val phoneMap = mapOf(
            '2' to "abc", '3' to "def", '4' to "ghi", '5' to "jkl",
            '6' to "mno", '7' to "pqrs", '8' to "tuv", '9' to "wxyz"
        )
        
        val result = mutableListOf<String>()
        
        fun backtrack(index: Int, current: StringBuilder) {
            if (index == digits.length) {
                result.add(current.toString())
                return
            }
            
            phoneMap[digits[index]]?.forEach { letter ->
                current.append(letter)
                backtrack(index + 1, current)
                current.deleteCharAt(current.length - 1)
            }
        }
        
        backtrack(0, StringBuilder())
        return result
    }
}