/*
 * Problem: Longest Substring Without Repeating Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

using System.Collections.Generic;

public class Solution {
    public int LengthOfLongestSubstring(string s) {
        Dictionary<char, int> charIndex = new Dictionary<char, int>();
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.Length; right++) {
            char c = s[right];
            if (charIndex.ContainsKey(c) && charIndex[c] >= left) {
                left = charIndex[c] + 1;
            }
            charIndex[c] = right;
            maxLen = Math.Max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
}