// Problem: Longest Valid Parentheses
// Difficulty: Hard
// Tags: string, tree, dp, stack
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func longestValidParentheses(s string) int {
    stack := []int{-1}
    maxLen := 0
    
    for i := 0; i < len(s); i++ {
        if s[i] == '(' {
            stack = append(stack, i)
        } else {
            stack = stack[:len(stack)-1]
            if len(stack) == 0 {
                stack = append(stack, i)
            } else {
                if i-stack[len(stack)-1] > maxLen {
                    maxLen = i - stack[len(stack)-1]
                }
            }
        }
    }
    
    return maxLen
}