// Problem: Generate Parentheses
// Difficulty: Medium
// Tags: string, dp
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func generateParenthesis(n int) []string {
    var result []string
    
    var backtrack func(string, int, int)
    backtrack = func(current string, open int, close int) {
        if len(current) == 2*n {
            result = append(result, current)
            return
        }
        
        if open < n {
            backtrack(current+"(", open+1, close)
        }
        
        if close < open {
            backtrack(current+")", open, close+1)
        }
    }
    
    backtrack("", 0, 0)
    return result
}