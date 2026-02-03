class Solution {
    func longestCommonPrefix(_ strs: [String]) -> String {
        if strs.isEmpty {
            return ""
        }
        
        let first = Array(strs[0])
        for i in 0..<first.count {
            let char = first[i]
            for j in 1..<strs.count {
                let str = Array(strs[j])
                if i >= str.count || str[i] != char {
                    return String(strs[0].prefix(i))
                }
            }
        }
        
        return strs[0]
    }
}