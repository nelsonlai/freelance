class Solution {
    fun romanToInt(s: String): Int {
        val romanMap = mapOf(
            'I' to 1, 'V' to 5, 'X' to 10, 'L' to 50,
            'C' to 100, 'D' to 500, 'M' to 1000
        )
        
        var result = 0
        for (i in s.indices) {
            val current = romanMap[s[i]]!!
            if (i < s.length - 1) {
                val next = romanMap[s[i + 1]]!!
                if (current < next) {
                    result -= current
                } else {
                    result += current
                }
            } else {
                result += current
            }
        }
        
        return result
    }
}