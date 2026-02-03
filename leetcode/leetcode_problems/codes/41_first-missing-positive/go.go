// Problem: First Missing Positive
// Difficulty: Hard
// Tags: array, hash, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

func firstMissingPositive(nums []int) int {
    n := len(nums)
    
    // Place each number in its correct position
    for i := 0; i < n; i++ {
        for nums[i] >= 1 && nums[i] <= n && nums[nums[i]-1] != nums[i] {
            nums[nums[i]-1], nums[i] = nums[i], nums[nums[i]-1]
        }
    }
    
    // Find the first missing positive
    for i := 0; i < n; i++ {
        if nums[i] != i+1 {
            return i + 1
        }
    }
    
    return n + 1
}