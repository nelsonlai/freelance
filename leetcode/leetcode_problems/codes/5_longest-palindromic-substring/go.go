// Problem: Longest Palindromic Substring
// Difficulty: Medium
// Tags: array, string, tree, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func longestPalindrome(s string) string {
    if len(s) == 0 {
        return ""
    }
    
    start, maxLen := 0, 1
    
    expandAroundCenter := func(left, right int) int {
        for left >= 0 && right < len(s) && s[left] == s[right] {
            left--
            right++
        }
        return right - left - 1
    }
    
    for i := 0; i < len(s); i++ {
        len1 := expandAroundCenter(i, i)
        len2 := expandAroundCenter(i, i+1)
        length := len1
        if len2 > len1 {
            length = len2
        }
        
        if length > maxLen {
            start = i - (length-1)/2
            maxLen = length
        }
    }
    
    return s[start : start+maxLen]
}