class Solution {
    func divide(_ dividend: Int, _ divisor: Int) -> Int {
        if dividend == Int32.min && divisor == -1 {
            return Int(Int32.max)
        }
        
        let negative = (dividend < 0) != (divisor < 0)
        var dvd = abs(dividend)
        let dvs = abs(divisor)
        
        var quotient = 0
        while dvd >= dvs {
            var temp = dvs
            var multiple = 1
            while dvd >= (temp << 1) {
                temp <<= 1
                multiple <<= 1
            }
            dvd -= temp
            quotient += multiple
        }
        
        return negative ? -quotient : quotient
    }
}