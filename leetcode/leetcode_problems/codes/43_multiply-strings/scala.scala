object Solution {
    def multiply(num1: String, num2: String): String = {
        if (num1 == "0" || num2 == "0") {
            return "0"
        }
        
        val m = num1.length
        val n = num2.length
        val result = Array.fill(m + n)(0)
        
        for (i <- m - 1 to 0 by -1) {
            for (j <- n - 1 to 0 by -1) {
                val mul = (num1(i) - '0') * (num2(j) - '0')
                val p1 = i + j
                val p2 = i + j + 1
                val total = mul + result(p2)
                
                result(p2) = total % 10
                result(p1) += total / 10
            }
        }
        
        // Remove leading zeros
        var start = 0
        while (start < result.length && result(start) == 0) {
            start += 1
        }
        
        result.slice(start, result.length).mkString("")
    }
}