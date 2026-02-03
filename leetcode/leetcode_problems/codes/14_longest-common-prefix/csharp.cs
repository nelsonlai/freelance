/*
 * Problem: Longest Common Prefix
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

public class Solution {
    public string LongestCommonPrefix(string[] strs) {
        if (strs.Length == 0) {
            return "";
        }
        
        for (int i = 0; i < strs[0].Length; i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.Length; j++) {
                if (i >= strs[j].Length || strs[j][i] != c) {
                    return strs[0].Substring(0, i);
                }
            }
        }
        
        return strs[0];
    }
}