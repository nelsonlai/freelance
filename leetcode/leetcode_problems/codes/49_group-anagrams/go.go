// Problem: Group Anagrams
// Difficulty: Medium
// Tags: array, string, hash, sort
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

import (
    "sort"
    "strings"
)

func groupAnagrams(strs []string) [][]string {
    groups := make(map[string][]string)
    for _, s := range strs {
        chars := strings.Split(s, "")
        sort.Strings(chars)
        key := strings.Join(chars, "")
        groups[key] = append(groups[key], s)
    }
    result := make([][]string, 0, len(groups))
    for _, group := range groups {
        result = append(result, group)
    }
    return result
}