"""
Problem: Replace All Digits with Characters
Difficulty: Easy
Tags: string

Approach: Shift each digit by previous character
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def replaceDigits(self, s: str) -> str:
        result = []
        for i, char in enumerate(s):
            if i % 2 == 0:
                result.append(char)
            else:
                result.append(chr(ord(s[i-1]) + int(char)))
        return ''.join(result)