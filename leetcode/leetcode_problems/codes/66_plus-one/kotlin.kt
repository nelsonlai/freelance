class Solution {
    fun plusOne(digits: IntArray): IntArray {
        val result = digits.copyOf()
        for (i in result.size - 1 downTo 0) {
            if (result[i] < 9) {
                result[i]++
                return result
            }
            result[i] = 0
        }
        
        return intArrayOf(1) + result
    }
}