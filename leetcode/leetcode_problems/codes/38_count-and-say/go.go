// Problem: Count and Say
// Difficulty: Medium
// Tags: string
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import (
    "strconv"
    "strings"
)

func countAndSay(n int) string {
    if n == 1 {
        return "1"
    }
    
    result := "1"
    for i := 1; i < n; i++ {
        var newResult strings.Builder
        j := 0
        for j < len(result) {
            count := 1
            for j+1 < len(result) && result[j] == result[j+1] {
                count++
                j++
            }
            newResult.WriteString(strconv.Itoa(count))
            newResult.WriteByte(result[j])
            j++
        }
        result = newResult.String()
    }
    
    return result
}