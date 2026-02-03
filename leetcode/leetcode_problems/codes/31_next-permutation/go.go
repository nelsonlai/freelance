// Problem: Next Permutation
// Difficulty: Medium
// Tags: array, graph, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func nextPermutation(nums []int) {
    i := len(nums) - 2
    for i >= 0 && nums[i] >= nums[i+1] {
        i--
    }
    
    if i >= 0 {
        j := len(nums) - 1
        for nums[j] <= nums[i] {
            j--
        }
        nums[i], nums[j] = nums[j], nums[i]
    }
    
    reverse(nums, i+1)
}

func reverse(nums []int, start int) {
    end := len(nums) - 1
    for start < end {
        nums[start], nums[end] = nums[end], nums[start]
        start++
        end--
    }
}