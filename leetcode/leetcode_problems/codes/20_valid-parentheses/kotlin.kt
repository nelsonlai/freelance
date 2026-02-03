class Solution {
    fun isValid(s: String): Boolean {
        val stack = mutableListOf<Char>()
        val mapping = mapOf(
            ')' to '(',
            '}' to '{',
            ']' to '['
        )
        
        for (char in s) {
            if (char in mapping) {
                if (stack.isEmpty() || stack.removeAt(stack.size - 1) != mapping[char]) {
                    return false
                }
            } else {
                stack.add(char)
            }
        }
        
        return stack.isEmpty()
    }
}