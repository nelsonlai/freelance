class Solution {
    fun countAndSay(n: Int): String {
        if (n == 1) {
            return "1"
        }
        
        var result = "1"
        for (i in 1 until n) {
            val newResult = StringBuilder()
            var j = 0
            while (j < result.length) {
                var count = 1
                while (j + 1 < result.length && result[j] == result[j + 1]) {
                    count++
                    j++
                }
                newResult.append(count)
                newResult.append(result[j])
                j++
            }
            result = newResult.toString()
        }
        
        return result
    }
}