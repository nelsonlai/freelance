class Solution {
    fun intToRoman(num: Int): String {
        val values = intArrayOf(1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1)
        val symbols = arrayOf("M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I")
        
        var num = num
        val result = StringBuilder()
        
        for (i in values.indices) {
            val count = num / values[i]
            repeat(count) {
                result.append(symbols[i])
            }
            num %= values[i]
        }
        
        return result.toString()
    }
}