"""
Problem: Decrypt String from Alphabet to Integer Mapping
Difficulty: Easy
Tags: string

Approach: Process from right to left, check for '#' pattern (two digits + #)
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def freqAlphabets(self, s: str) -> str:
        result = []
        i = len(s) - 1
        
        while i >= 0:
            if s[i] == '#':
                num = int(s[i-2:i])
                result.append(chr(ord('a') + num - 1))
                i -= 3
            else:
                num = int(s[i])
                result.append(chr(ord('a') + num - 1))
                i -= 1
        
        return ''.join(reversed(result))