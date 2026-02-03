// Problem: Longest Common Prefix
// Difficulty: Easy
// Tags: array, string
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func longestCommonPrefix(strs []string) string {
    if len(strs) == 0 {
        return ""
    }
    
    for i := 0; i < len(strs[0]); i++ {
        char := strs[0][i]
        for j := 1; j < len(strs); j++ {
            if i >= len(strs[j]) || strs[j][i] != char {
                return strs[0][:i]
            }
        }
    }
    
    return strs[0]
}