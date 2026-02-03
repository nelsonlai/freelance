// Problem: Jump Game II
// Difficulty: Medium
// Tags: array, dp, greedy
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func jump(nums []int) int {
    jumps := 0
    currentEnd := 0
    farthest := 0
    
    for i := 0; i < len(nums)-1; i++ {
        if i+nums[i] > farthest {
            farthest = i + nums[i]
        }
        if i == currentEnd {
            jumps++
            currentEnd = farthest
        }
    }
    
    return jumps
}