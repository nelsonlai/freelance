/*
 * Problem: Maximum Subarray
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

int maxSubArray(int* nums, int numsSize) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (currentSum + nums[i] > nums[i]) {
            currentSum += nums[i];
        } else {
            currentSum = nums[i];
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }
    return maxSum;
}