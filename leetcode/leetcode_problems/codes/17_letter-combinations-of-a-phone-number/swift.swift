class Solution {
    func letterCombinations(_ digits: String) -> [String] {
        if digits.isEmpty {
            return []
        }
        
        let phoneMap: [Character: String] = [
            "2": "abc", "3": "def", "4": "ghi", "5": "jkl",
            "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"
        ]
        
        var result: [String] = []
        let chars = Array(digits)
        
        func backtrack(_ index: Int, _ current: String) {
            if index == chars.count {
                result.append(current)
                return
            }
            
            if let letters = phoneMap[chars[index]] {
                for letter in letters {
                    backtrack(index + 1, current + String(letter))
                }
            }
        }
        
        backtrack(0, "")
        return result
    }
}