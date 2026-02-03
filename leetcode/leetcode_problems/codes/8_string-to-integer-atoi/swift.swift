class Solution {
    func myAtoi(_ s: String) -> Int {
        let s = s.trimmingCharacters(in: .whitespaces)
        if s.isEmpty {
            return 0
        }
        
        var sign = 1
        var i = s.startIndex
        
        if s[i] == "-" {
            sign = -1
            i = s.index(after: i)
        } else if s[i] == "+" {
            i = s.index(after: i)
        }
        
        var result = 0
        let chars = Array(s)
        var idx = s.distance(from: s.startIndex, to: i)
        
        while idx < chars.count && chars[idx].isNumber {
            let digit = Int(String(chars[idx]))!
            if result > Int32.max / 10 || 
                (result == Int32.max / 10 && digit > 7) {
                return sign == 1 ? Int(Int32.max) : Int(Int32.min)
            }
            result = result * 10 + digit
            idx += 1
        }
        
        return sign * result
    }
}