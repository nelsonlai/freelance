"""
Problem: Count Substrings with Only One Distinct Letter
Difficulty: Easy
Tags: string, tree, math

Approach: Count consecutive same characters, add triangular number for each group
Time Complexity: O(n) where n is the length of s
Space Complexity: O(1)
"""

class Solution:
    def countLetters(self, s: str) -> int:
        if not s:
            return 0
        
        total = 0
        i = 0
        while i < len(s):
            j = i
            while j < len(s) and s[j] == s[i]:
                j += 1
            length = j - i
            # Number of substrings with same character: 1 + 2 + ... + length = length * (length + 1) / 2
            total += length * (length + 1) // 2
            i = j
        
        return total