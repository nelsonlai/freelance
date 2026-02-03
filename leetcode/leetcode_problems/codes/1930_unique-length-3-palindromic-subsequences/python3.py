"""
Problem: Unique Length-3 Palindromic Subsequences
Difficulty: Medium
Tags: array, string, hash

Approach: For each character, find first and last occurrence, count unique middle chars
Time Complexity: O(n * 26) where n is length
Space Complexity: O(26)
"""

class Solution:
    def countPalindromicSubsequence(self, s: str) -> int:
        first = {}
        last = {}
        
        for i, char in enumerate(s):
            if char not in first:
                first[char] = i
            last[char] = i
        
        result = 0
        for char in first:
            if first[char] < last[char]:
                middle = set(s[first[char] + 1:last[char]])
                result += len(middle)
        
        return result