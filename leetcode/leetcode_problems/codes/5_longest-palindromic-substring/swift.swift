class Solution {
    func longestPalindrome(_ s: String) -> String {
        if s.isEmpty {
            return ""
        }
        
        let chars = Array(s)
        var start = 0
        var maxLen = 1
        
        func expandAroundCenter(_ left: Int, _ right: Int) -> Int {
            var left = left
            var right = right
            while left >= 0 && right < chars.count && chars[left] == chars[right] {
                left -= 1
                right += 1
            }
            return right - left - 1
        }
        
        for i in 0..<chars.count {
            let len1 = expandAroundCenter(i, i)
            let len2 = expandAroundCenter(i, i + 1)
            let len = max(len1, len2)
            
            if len > maxLen {
                start = i - (len - 1) / 2
                maxLen = len
            }
        }
        
        let startIndex = s.index(s.startIndex, offsetBy: start)
        let endIndex = s.index(startIndex, offsetBy: maxLen)
        return String(s[startIndex..<endIndex])
    }
}