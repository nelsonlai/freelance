object Solution {
    def countAndSay(n: Int): String = {
        if (n == 1) {
            return "1"
        }
        
        var result = "1"
        for (i <- 1 until n) {
            val newResult = new StringBuilder()
            var j = 0
            while (j < result.length) {
                var count = 1
                while (j + 1 < result.length && result(j) == result(j + 1)) {
                    count += 1
                    j += 1
                }
                newResult.append(count)
                newResult.append(result(j))
                j += 1
            }
            result = newResult.toString()
        }
        
        result
    }
}