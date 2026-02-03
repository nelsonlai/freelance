// Problem: Permutations II
// Difficulty: Medium
// Tags: array, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import "sort"

func permuteUnique(nums []int) [][]int {
    sort.Ints(nums)
    var result [][]int
    used := make([]bool, len(nums))
    
    var backtrack func([]int)
    backtrack = func(current []int) {
        if len(current) == len(nums) {
            temp := make([]int, len(current))
            copy(temp, current)
            result = append(result, temp)
            return
        }
        
        for i := 0; i < len(nums); i++ {
            if used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1]) {
                continue
            }
            used[i] = true
            current = append(current, nums[i])
            backtrack(current)
            current = current[:len(current)-1]
            used[i] = false
        }
    }
    
    backtrack([]int{})
    return result
}