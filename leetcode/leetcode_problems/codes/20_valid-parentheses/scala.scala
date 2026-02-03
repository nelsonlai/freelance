import scala.collection.mutable

object Solution {
    def isValid(s: String): Boolean = {
        val stack = mutable.Stack[Char]()
        val mapping = Map(
            ')' -> '(',
            '}' -> '{',
            ']' -> '['
        )
        
        for (char <- s) {
            if (mapping.contains(char)) {
                if (stack.isEmpty || stack.pop() != mapping(char)) {
                    return false
                }
            } else {
                stack.push(char)
            }
        }
        
        stack.isEmpty
    }
}