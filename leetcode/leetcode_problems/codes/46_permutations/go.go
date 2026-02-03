// Problem: Permutations
// Difficulty: Medium
// Tags: array
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func permute(nums []int) [][]int {
    var result [][]int
    var backtrack func([]int, []bool)
    
    backtrack = func(current []int, used []bool) {
        if len(current) == len(nums) {
            temp := make([]int, len(current))
            copy(temp, current)
            result = append(result, temp)
            return
        }
        
        for i, num := range nums {
            if used[i] {
                continue
            }
            used[i] = true
            current = append(current, num)
            backtrack(current, used)
            current = current[:len(current)-1]
            used[i] = false
        }
    }
    
    used := make([]bool, len(nums))
    backtrack([]int{}, used)
    return result
}