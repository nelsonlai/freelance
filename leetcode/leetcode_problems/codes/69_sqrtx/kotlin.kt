class Solution {
    fun mySqrt(x: Int): Int {
        if (x < 2) {
            return x
        }
        
        // Newton's method: x_{n+1} = (x_n + S/x_n) / 2
        var guess = x.toLong()
        while (guess * guess > x) {
            guess = (guess + x / guess) / 2
        }
        
        return guess.toInt()
    }
}