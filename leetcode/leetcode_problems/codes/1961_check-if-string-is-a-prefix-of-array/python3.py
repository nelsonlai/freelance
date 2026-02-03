"""
Problem: Check If String Is a Prefix of Array
Difficulty: Easy
Tags: array, string

Approach: Concatenate words and check if equals s
Time Complexity: O(n * m) where n is words, m is avg length
Space Complexity: O(n * m)
"""

class Solution:
    def isPrefixString(self, s: str, words: List[str]) -> bool:
        concatenated = ""
        for word in words:
            concatenated += word
            if concatenated == s:
                return True
            if len(concatenated) >= len(s):
                return False
        return False