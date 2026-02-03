/*
 * Problem: Longest Palindromic Substring
 * Difficulty: Medium
 * Tags: array, string, tree, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

public class Solution {
    public string LongestPalindrome(string s) {
        if (string.IsNullOrEmpty(s)) return "";
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < s.Length; i++) {
            int len1 = ExpandAroundCenter(s, i, i);
            int len2 = ExpandAroundCenter(s, i, i + 1);
            int len = Math.Max(len1, len2);
            
            if (len > maxLen) {
                start = i - (len - 1) / 2;
                maxLen = len;
            }
        }
        
        return s.Substring(start, maxLen);
    }
    
    private int ExpandAroundCenter(string s, int left, int right) {
        while (left >= 0 && right < s.Length && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
}