class Solution {
    func reverse(_ x: Int) -> Int {
        var x = x
        var result = 0
        
        while x != 0 {
            let digit = x % 10
            x /= 10
            
            if result > Int32.max / 10 || (result == Int32.max / 10 && digit > 7) {
                return 0
            }
            if result < Int32.min / 10 || (result == Int32.min / 10 && digit < -8) {
                return 0
            }
            
            result = result * 10 + digit
        }
        
        return result
    }
}