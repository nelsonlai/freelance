"""
Problem: Reverse Prefix of Word
Difficulty: Easy
Tags: array, string

Approach: Find first occurrence of ch, reverse prefix up to that index
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def reversePrefix(self, word: str, ch: str) -> str:
        idx = word.find(ch)
        if idx == -1:
            return word
        return word[:idx+1][::-1] + word[idx+1:]