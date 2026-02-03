import scala.collection.mutable

object Solution {
    def longestValidParentheses(s: String): Int = {
        val stack = mutable.Stack[Int]()
        stack.push(-1)
        var maxLen = 0
        
        for (i <- s.indices) {
            if (s(i) == '(') {
                stack.push(i)
            } else {
                stack.pop()
                if (stack.isEmpty) {
                    stack.push(i)
                } else {
                    maxLen = maxLen.max(i - stack.top)
                }
            }
        }
        
        maxLen
    }
}