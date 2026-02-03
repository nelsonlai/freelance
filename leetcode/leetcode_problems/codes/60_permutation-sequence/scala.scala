object Solution {
    def getPermutation(n: Int, k: Int): String = {
        var nums = (1 to n).toList
        val fact = Array.ofDim[Int](n)
        fact(0) = 1
        for (i <- 1 until n) {
            fact(i) = fact(i - 1) * i
        }
        
        var k = k - 1 // Convert to 0-indexed
        var result = ""
        
        for (i <- n - 1 to 0 by -1) {
            val index = k / fact(i)
            result += nums(index).toString
            nums = nums.patch(index, Nil, 1)
            k %= fact(i)
        }
        
        result
    }
}