// Problem: Find the Index of the First Occurrence in a String
// Difficulty: Easy
// Tags: array, string, stack
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func strStr(haystack string, needle string) int {
    if len(needle) == 0 {
        return 0
    }
    
    n := len(haystack)
    m := len(needle)
    
    for i := 0; i <= n-m; i++ {
        if haystack[i:i+m] == needle {
            return i
        }
    }
    
    return -1
}