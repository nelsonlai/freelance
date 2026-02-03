class Solution {
    func isValid(_ s: String) -> Bool {
        var stack: [Character] = []
        let mapping: [Character: Character] = [
            ")": "(",
            "}": "{",
            "]": "["
        ]
        
        for char in s {
            if let opening = mapping[char] {
                if stack.isEmpty || stack.removeLast() != opening {
                    return false
                }
            } else {
                stack.append(char)
            }
        }
        
        return stack.isEmpty
    }
}