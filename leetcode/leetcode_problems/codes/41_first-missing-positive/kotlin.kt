class Solution {
    fun firstMissingPositive(nums: IntArray): Int {
        val n = nums.size
        
        // Place each number in its correct position
        var i = 0
        while (i < n) {
            val num = nums[i]
            if (num >= 1 && num <= n && nums[num - 1] != num) {
                val temp = nums[num - 1]
                nums[num - 1] = num
                nums[i] = temp
            } else {
                i++
            }
        }
        
        // Find the first missing positive
        for (i in 0 until n) {
            if (nums[i] != i + 1) {
                return i + 1
            }
        }
        
        return n + 1
    }
}