"""
Problem: Check If Two String Arrays are Equivalent
Difficulty: Easy
Tags: array, string

Approach: Concatenate both arrays and compare
Time Complexity: O(n + m) where n, m are total characters
Space Complexity: O(n + m) for concatenated strings
"""

class Solution:
    def arrayStringsAreEqual(self, word1: List[str], word2: List[str]) -> bool:
        return ''.join(word1) == ''.join(word2)