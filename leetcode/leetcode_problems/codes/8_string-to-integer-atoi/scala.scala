object Solution {
    def myAtoi(s: String): Int = {
        val trimmed = s.trim
        if (trimmed.isEmpty) {
            return 0
        }
        
        var sign = 1
        var i = 0
        
        if (trimmed(0) == '-') {
            sign = -1
            i = 1
        } else if (trimmed(0) == '+') {
            i = 1
        }
        
        val INT_MAX = Int.MaxValue
        val INT_MIN = Int.MinValue
        var result = 0
        
        while (i < trimmed.length && trimmed(i).isDigit) {
            val digit = trimmed(i) - '0'
            if (result > INT_MAX / 10 || 
                (result == INT_MAX / 10 && digit > 7)) {
                return if (sign == 1) INT_MAX else INT_MIN
            }
            result = result * 10 + digit
            i += 1
        }
        
        sign * result
    }
}