object Solution {
    def myPow(x: Double, n: Int): Double = {
        if (n == 0) {
            return 1.0
        }
        var base = x
        var exp = n.toLong
        if (exp < 0) {
            base = 1.0 / base
            exp = -exp
        }
        
        var result = 1.0
        while (exp > 0) {
            if (exp % 2 == 1) {
                result *= base
            }
            base *= base
            exp /= 2
        }
        
        result
    }
}