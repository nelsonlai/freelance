class Solution {
    fun maxSubArray(nums: IntArray): Int {
        var maxSum = nums[0]
        var currentSum = nums[0]
        for (i in 1 until nums.size) {
            currentSum = maxOf(nums[i], currentSum + nums[i])
            maxSum = maxOf(maxSum, currentSum)
        }
        return maxSum
    }
}