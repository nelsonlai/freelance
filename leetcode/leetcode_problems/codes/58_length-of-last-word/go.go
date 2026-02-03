// Problem: Length of Last Word
// Difficulty: Easy
// Tags: string, tree
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

import "strings"

func lengthOfLastWord(s string) int {
    s = strings.TrimRight(s, " ")
    length := 0
    for i := len(s) - 1; i >= 0; i-- {
        if s[i] == ' ' {
            break
        }
        length++
    }
    return length
}