class Solution {
    func intToRoman(_ num: Int) -> String {
        let values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
        let symbols = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
        
        var num = num
        var result = ""
        
        for i in 0..<values.count {
            let count = num / values[i]
            result += String(repeating: symbols[i], count: count)
            num %= values[i]
        }
        
        return result
    }
}