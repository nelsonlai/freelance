class Solution {
    func lengthOfLongestSubstring(_ s: String) -> Int {
        var charIndex = [Character: Int]()
        var left = 0
        var maxLen = 0
        let chars = Array(s)
        
        for right in 0..<chars.count {
            let c = chars[right]
            if let idx = charIndex[c], idx >= left {
                left = idx + 1
            }
            charIndex[c] = right
            maxLen = max(maxLen, right - left + 1)
        }
        
        return maxLen
    }
}