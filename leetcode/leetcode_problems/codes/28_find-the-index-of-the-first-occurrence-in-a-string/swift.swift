class Solution {
    func strStr(_ haystack: String, _ needle: String) -> Int {
        if needle.isEmpty {
            return 0
        }
        
        let n = haystack.count
        let m = needle.count
        
        for i in 0...(n - m) {
            let startIndex = haystack.index(haystack.startIndex, offsetBy: i)
            let endIndex = haystack.index(startIndex, offsetBy: m)
            if haystack[startIndex..<endIndex] == needle {
                return i
            }
        }
        
        return -1
    }
}