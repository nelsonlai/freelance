"""
Problem: Number of Strings That Appear as Substrings in Word
Difficulty: Easy
Tags: array, string

Approach: Check if each pattern is a substring of word
Time Complexity: O(n * m) where n is patterns, m is word length
Space Complexity: O(1)
"""

class Solution:
    def numOfStrings(self, patterns: List[str], word: str) -> int:
        count = 0
        for pattern in patterns:
            if pattern in word:
                count += 1
        return count