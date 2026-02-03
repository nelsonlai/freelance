object Solution {
    def reverse(x: Int): Int = {
        var x = x
        var result = 0
        val INT_MAX = Int.MaxValue
        val INT_MIN = Int.MinValue
        
        while (x != 0) {
            val digit = x % 10
            x /= 10
            
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)) {
                return 0
            }
            if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8)) {
                return 0
            }
            
            result = result * 10 + digit
        }
        
        result
    }
}