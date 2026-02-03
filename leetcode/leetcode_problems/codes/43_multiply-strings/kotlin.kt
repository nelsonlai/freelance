class Solution {
    fun multiply(num1: String, num2: String): String {
        if (num1 == "0" || num2 == "0") {
            return "0"
        }
        
        val m = num1.length
        val n = num2.length
        val result = IntArray(m + n)
        
        for (i in m - 1 downTo 0) {
            for (j in n - 1 downTo 0) {
                val mul = (num1[i] - '0') * (num2[j] - '0')
                val p1 = i + j
                val p2 = i + j + 1
                val total = mul + result[p2]
                
                result[p2] = total % 10
                result[p1] += total / 10
            }
        }
        
        // Remove leading zeros
        var start = 0
        while (start < result.size && result[start] == 0) {
            start++
        }
        
        return result.sliceArray(start until result.size).joinToString("")
    }
}