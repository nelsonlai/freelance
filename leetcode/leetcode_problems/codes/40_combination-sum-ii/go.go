// Problem: Combination Sum II
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import "sort"

func combinationSum2(candidates []int, target int) [][]int {
    sort.Ints(candidates)
    var result [][]int
    var path []int
    
    var backtrack func(int, int)
    backtrack = func(start, remaining int) {
        if remaining == 0 {
            temp := make([]int, len(path))
            copy(temp, path)
            result = append(result, temp)
            return
        }
        if remaining < 0 {
            return
        }
        
        for i := start; i < len(candidates); i++ {
            if i > start && candidates[i] == candidates[i-1] {
                continue
            }
            path = append(path, candidates[i])
            backtrack(i+1, remaining-candidates[i])
            path = path[:len(path)-1]
        }
    }
    
    backtrack(0, target)
    return result
}