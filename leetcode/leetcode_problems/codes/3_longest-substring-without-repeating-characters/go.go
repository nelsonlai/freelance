// Problem: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

func lengthOfLongestSubstring(s string) int {
    charIndex := make(map[byte]int)
    left := 0
    maxLen := 0
    
    for right := 0; right < len(s); right++ {
        c := s[right]
        if idx, ok := charIndex[c]; ok && idx >= left {
            left = idx + 1
        }
        charIndex[c] = right
        if right-left+1 > maxLen {
            maxLen = right - left + 1
        }
    }
    
    return maxLen
}