class Solution {
    func countAndSay(_ n: Int) -> String {
        if n == 1 {
            return "1"
        }
        
        var result = "1"
        for _ in 1..<n {
            var newResult = ""
            var i = 0
            let chars = Array(result)
            while i < chars.count {
                var count = 1
                while i + 1 < chars.count && chars[i] == chars[i + 1] {
                    count += 1
                    i += 1
                }
                newResult += String(count)
                newResult += String(chars[i])
                i += 1
            }
            result = newResult
        }
        
        return result
    }
}