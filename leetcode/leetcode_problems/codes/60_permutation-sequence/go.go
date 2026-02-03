// Problem: Permutation Sequence
// Difficulty: Hard
// Tags: math
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

import (
    "strconv"
    "strings"
)

func getPermutation(n int, k int) string {
    nums := make([]int, n)
    for i := 0; i < n; i++ {
        nums[i] = i + 1
    }
    
    fact := make([]int, n)
    fact[0] = 1
    for i := 1; i < n; i++ {
        fact[i] = fact[i-1] * i
    }
    
    k-- // Convert to 0-indexed
    var result strings.Builder
    
    for i := n - 1; i >= 0; i-- {
        index := k / fact[i]
        result.WriteString(strconv.Itoa(nums[index]))
        nums = append(nums[:index], nums[index+1:]...)
        k %= fact[i]
    }
    
    return result.String()
}