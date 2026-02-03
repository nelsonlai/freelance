object Solution {
    def romanToInt(s: String): Int = {
        val romanMap = Map(
            'I' -> 1, 'V' -> 5, 'X' -> 10, 'L' -> 50,
            'C' -> 100, 'D' -> 500, 'M' -> 1000
        )
        
        var result = 0
        for (i <- s.indices) {
            val current = romanMap(s(i))
            if (i < s.length - 1) {
                val next = romanMap(s(i + 1))
                if (current < next) {
                    result -= current
                } else {
                    result += current
                }
            } else {
                result += current
            }
        }
        
        result
    }
}