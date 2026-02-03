// Problem: Valid Parentheses
// Difficulty: Easy
// Tags: string, stack
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func isValid(s string) bool {
    stack := []rune{}
    mapping := map[rune]rune{
        ')': '(',
        '}': '{',
        ']': '[',
    }
    
    for _, char := range s {
        if closing, exists := mapping[char]; exists {
            if len(stack) == 0 || stack[len(stack)-1] != closing {
                return false
            }
            stack = stack[:len(stack)-1]
        } else {
            stack = append(stack, char)
        }
    }
    
    return len(stack) == 0
}