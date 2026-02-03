class Solution {
    fun divide(dividend: Int, divisor: Int): Int {
        if (dividend == Int.MIN_VALUE && divisor == -1) {
            return Int.MAX_VALUE
        }
        
        val negative = (dividend < 0) != (divisor < 0)
        var dvd = Math.abs(dividend.toLong())
        val dvs = Math.abs(divisor.toLong())
        
        var quotient = 0
        while (dvd >= dvs) {
            var temp = dvs
            var multiple = 1
            while (dvd >= (temp shl 1)) {
                temp = temp shl 1
                multiple = multiple shl 1
            }
            dvd -= temp
            quotient += multiple
        }
        
        return if (negative) -quotient else quotient
    }
}