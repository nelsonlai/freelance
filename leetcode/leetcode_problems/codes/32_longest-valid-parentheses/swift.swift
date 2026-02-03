class Solution {
    func longestValidParentheses(_ s: String) -> Int {
        var stack = [-1]
        var maxLen = 0
        let chars = Array(s)
        
        for i in 0..<chars.count {
            if chars[i] == "(" {
                stack.append(i)
            } else {
                stack.removeLast()
                if stack.isEmpty {
                    stack.append(i)
                } else {
                    maxLen = max(maxLen, i - stack.last!)
                }
            }
        }
        
        return maxLen
    }
}