// Problem: Jump Game
// Difficulty: Medium
// Tags: array, dp, greedy
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func canJump(nums []int) bool {
    farthest := 0
    for i := 0; i < len(nums); i++ {
        if i > farthest {
            return false
        }
        if i+nums[i] > farthest {
            farthest = i + nums[i]
        }
        if farthest >= len(nums)-1 {
            return true
        }
    }
    return true
}