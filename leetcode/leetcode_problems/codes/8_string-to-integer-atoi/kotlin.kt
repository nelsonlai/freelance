class Solution {
    fun myAtoi(s: String): Int {
        val trimmed = s.trim()
        if (trimmed.isEmpty()) {
            return 0
        }
        
        var sign = 1
        var i = 0
        
        if (trimmed[0] == '-') {
            sign = -1
            i = 1
        } else if (trimmed[0] == '+') {
            i = 1
        }
        
        var result = 0
        while (i < trimmed.length && trimmed[i].isDigit()) {
            val digit = trimmed[i] - '0'
            if (result > Int.MAX_VALUE / 10 || 
                (result == Int.MAX_VALUE / 10 && digit > 7)) {
                return if (sign == 1) Int.MAX_VALUE else Int.MIN_VALUE
            }
            result = result * 10 + digit
            i++
        }
        
        return sign * result
    }
}