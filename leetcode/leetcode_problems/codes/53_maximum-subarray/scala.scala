object Solution {
    def maxSubArray(nums: Array[Int]): Int = {
        var maxSum = nums(0)
        var currentSum = nums(0)
        for (i <- 1 until nums.length) {
            currentSum = math.max(nums(i), currentSum + nums(i))
            maxSum = math.max(maxSum, currentSum)
        }
        maxSum
    }
}