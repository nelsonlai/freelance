object Solution {
    def intToRoman(num: Int): String = {
        val values = Array(1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1)
        val symbols = Array("M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I")
        
        var num = num
        val result = new StringBuilder
        
        for (i <- values.indices) {
            val count = num / values(i)
            for (_ <- 0 until count) {
                result.append(symbols(i))
            }
            num %= values(i)
        }
        
        result.toString
    }
}