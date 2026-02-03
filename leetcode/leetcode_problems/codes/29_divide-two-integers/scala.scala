object Solution {
    def divide(dividend: Int, divisor: Int): Int = {
        if (dividend == Int.MinValue && divisor == -1) {
            return Int.MaxValue
        }
        
        val negative = (dividend < 0) != (divisor < 0)
        var dvd = Math.abs(dividend.toLong)
        val dvs = Math.abs(divisor.toLong)
        
        var quotient = 0
        while (dvd >= dvs) {
            var temp = dvs
            var multiple = 1
            while (dvd >= (temp << 1)) {
                temp <<= 1
                multiple <<= 1
            }
            dvd -= temp
            quotient += multiple
        }
        
        if (negative) -quotient else quotient
    }
}