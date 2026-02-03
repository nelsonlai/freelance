class Solution {
    func romanToInt(_ s: String) -> Int {
        let romanMap: [Character: Int] = [
            "I": 1, "V": 5, "X": 10, "L": 50,
            "C": 100, "D": 500, "M": 1000
        ]
        
        let chars = Array(s)
        var result = 0
        
        for i in 0..<chars.count {
            let current = romanMap[chars[i]]!
            if i < chars.count - 1 {
                let next = romanMap[chars[i + 1]]!
                if current < next {
                    result -= current
                } else {
                    result += current
                }
            } else {
                result += current
            }
        }
        
        return result
    }
}