// Problem: Multiply Strings
// Difficulty: Medium
// Tags: string, math
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import "strings"

func multiply(num1 string, num2 string) string {
    if num1 == "0" || num2 == "0" {
        return "0"
    }
    
    m, n := len(num1), len(num2)
    result := make([]int, m+n)
    
    for i := m - 1; i >= 0; i-- {
        for j := n - 1; j >= 0; j-- {
            mul := int(num1[i]-'0') * int(num2[j]-'0')
            p1, p2 := i+j, i+j+1
            total := mul + result[p2]
            
            result[p2] = total % 10
            result[p1] += total / 10
        }
    }
    
    // Remove leading zeros
    start := 0
    for start < len(result) && result[start] == 0 {
        start++
    }
    
    var sb strings.Builder
    for i := start; i < len(result); i++ {
        sb.WriteByte(byte(result[i] + '0'))
    }
    
    return sb.String()
}