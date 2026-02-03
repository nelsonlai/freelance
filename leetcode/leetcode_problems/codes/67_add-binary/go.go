// Problem: Add Binary
// Difficulty: Easy
// Tags: string, math
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import "strings"

func addBinary(a string, b string) string {
    var result strings.Builder
    carry := 0
    i, j := len(a)-1, len(b)-1
    
    for i >= 0 || j >= 0 || carry > 0 {
        total := carry
        if i >= 0 {
            total += int(a[i] - '0')
            i--
        }
        if j >= 0 {
            total += int(b[j] - '0')
            j--
        }
        result.WriteByte(byte(total%2) + '0')
        carry = total / 2
    }
    
    s := result.String()
    runes := []rune(s)
    for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
        runes[i], runes[j] = runes[j], runes[i]
    }
    return string(runes)
}