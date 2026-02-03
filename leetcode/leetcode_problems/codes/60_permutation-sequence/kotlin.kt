class Solution {
    fun getPermutation(n: Int, k: Int): String {
        val nums = mutableListOf<Int>()
        for (i in 1..n) {
            nums.add(i)
        }
        
        val fact = IntArray(n)
        fact[0] = 1
        for (i in 1 until n) {
            fact[i] = fact[i - 1] * i
        }
        
        var k = k - 1 // Convert to 0-indexed
        val result = StringBuilder()
        
        for (i in n - 1 downTo 0) {
            val index = k / fact[i]
            result.append(nums[index])
            nums.removeAt(index)
            k %= fact[i]
        }
        
        return result.toString()
    }
}