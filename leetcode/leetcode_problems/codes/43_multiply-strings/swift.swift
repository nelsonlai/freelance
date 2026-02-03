class Solution {
    func multiply(_ num1: String, _ num2: String) -> String {
        if num1 == "0" || num2 == "0" {
            return "0"
        }
        
        let num1Array = Array(num1)
        let num2Array = Array(num2)
        let m = num1Array.count
        let n = num2Array.count
        var result = Array(repeating: 0, count: m + n)
        
        for i in stride(from: m - 1, through: 0, by: -1) {
            for j in stride(from: n - 1, through: 0, by: -1) {
                let mul = Int(String(num1Array[i]))! * Int(String(num2Array[j]))!
                let p1 = i + j
                let p2 = i + j + 1
                let total = mul + result[p2]
                
                result[p2] = total % 10
                result[p1] += total / 10
            }
        }
        
        // Remove leading zeros
        var start = 0
        while start < result.count && result[start] == 0 {
            start += 1
        }
        
        return result[start...].map { String($0) }.joined()
    }
}