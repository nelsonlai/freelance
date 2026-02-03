"""
Problem: Remove Palindromic Subsequences
Difficulty: Easy
Tags: array, string

Approach: If string is palindrome, return 1. Otherwise return 2 (remove all 'a', then all 'b')
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def removePalindromeSub(self, s: str) -> int:
        if not s:
            return 0
        if s == s[::-1]:
            return 1
        return 2