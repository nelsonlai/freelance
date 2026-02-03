import java.util.*

class Solution {
    fun longestValidParentheses(s: String): Int {
        val stack = Stack<Int>()
        stack.push(-1)
        var maxLen = 0
        
        for (i in s.indices) {
            if (s[i] == '(') {
                stack.push(i)
            } else {
                stack.pop()
                if (stack.isEmpty()) {
                    stack.push(i)
                } else {
                    maxLen = maxOf(maxLen, i - stack.peek())
                }
            }
        }
        
        return maxLen
    }
}