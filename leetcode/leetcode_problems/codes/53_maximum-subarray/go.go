// Problem: Maximum Subarray
// Difficulty: Medium
// Tags: array, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func maxSubArray(nums []int) int {
    maxSum := nums[0]
    currentSum := nums[0]
    for i := 1; i < len(nums); i++ {
        if currentSum+nums[i] > nums[i] {
            currentSum += nums[i]
        } else {
            currentSum = nums[i]
        }
        if currentSum > maxSum {
            maxSum = currentSum
        }
    }
    return maxSum
}