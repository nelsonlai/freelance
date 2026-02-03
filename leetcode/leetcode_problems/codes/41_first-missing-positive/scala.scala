object Solution {
    def firstMissingPositive(nums: Array[Int]): Int = {
        val n = nums.length
        var i = 0
        
        // Place each number in its correct position
        while (i < n) {
            val num = nums(i)
            if (num >= 1 && num <= n && nums(num - 1) != num) {
                val temp = nums(num - 1)
                nums(num - 1) = num
                nums(i) = temp
            } else {
                i += 1
            }
        }
        
        // Find the first missing positive
        for (i <- 0 until n) {
            if (nums(i) != i + 1) {
                return i + 1
            }
        }
        
        n + 1
    }
}