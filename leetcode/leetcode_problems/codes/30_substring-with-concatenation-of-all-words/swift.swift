class Solution {
    func findSubstring(_ s: String, _ words: [String]) -> [Int] {
        var result: [Int] = []
        if s.isEmpty || words.isEmpty {
            return result
        }
        
        let wordLen = words[0].count
        var wordCount: [String: Int] = [:]
        for word in words {
            wordCount[word, default: 0] += 1
        }
        
        let sArray = Array(s)
        for i in 0..<wordLen {
            var left = i
            var seen: [String: Int] = [:]
            var count = 0
            
            var j = i
            while j <= sArray.count - wordLen {
                let startIdx = sArray.index(sArray.startIndex, offsetBy: j)
                let endIdx = sArray.index(startIdx, offsetBy: wordLen)
                let word = String(sArray[startIdx..<endIdx])
                
                if wordCount[word] != nil {
                    seen[word, default: 0] += 1
                    count += 1
                    
                    while seen[word]! > wordCount[word]! {
                        let leftStartIdx = sArray.index(sArray.startIndex, offsetBy: left)
                        let leftEndIdx = sArray.index(leftStartIdx, offsetBy: wordLen)
                        let leftWord = String(sArray[leftStartIdx..<leftEndIdx])
                        seen[leftWord]! -= 1
                        count -= 1
                        left += wordLen
                    }
                    
                    if count == words.count {
                        result.append(left)
                        let leftStartIdx = sArray.index(sArray.startIndex, offsetBy: left)
                        let leftEndIdx = sArray.index(leftStartIdx, offsetBy: wordLen)
                        let leftWord = String(sArray[leftStartIdx..<leftEndIdx])
                        seen[leftWord]! -= 1
                        count -= 1
                        left += wordLen
                    }
                } else {
                    seen.removeAll()
                    count = 0
                    left = j + wordLen
                }
                j += wordLen
            }
        }
        
        return result
    }
}