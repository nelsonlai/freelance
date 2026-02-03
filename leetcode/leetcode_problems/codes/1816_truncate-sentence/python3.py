"""
Problem: Truncate Sentence
Difficulty: Easy
Tags: array, string

Approach: Split and join first k words
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def truncateSentence(self, s: str, k: int) -> str:
        return ' '.join(s.split()[:k])