// Problem: String to Integer (atoi)
// Difficulty: Medium
// Tags: string
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func myAtoi(s string) int {
    s = strings.TrimSpace(s)
    if len(s) == 0 {
        return 0
    }
    
    sign := 1
    i := 0
    
    if s[0] == '-' {
        sign = -1
        i = 1
    } else if s[0] == '+' {
        i = 1
    }
    
    result := 0
    for i < len(s) && s[i] >= '0' && s[i] <= '9' {
        digit := int(s[i] - '0')
        if result > 214748364 || (result == 214748364 && digit > 7) {
            if sign == 1 {
                return 2147483647
            }
            return -2147483648
        }
        result = result*10 + digit
        i++
    }
    
    return sign * result
}