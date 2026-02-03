"""
Problem: Check if String Is Decomposable Into Value-Equal Substrings
Difficulty: Easy
Tags: string, greedy

Approach: Check if can be decomposed into substrings of length 2 or 3, exactly one of length 2
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def isDecomposable(self, s: str) -> int:
        i = 0
        n = len(s)
        has_two = False
        
        while i < n:
            if i + 2 < n and s[i] == s[i+1] == s[i+2]:
                i += 3
            elif i + 1 < n and s[i] == s[i+1]:
                if has_two:
                    return False
                has_two = True
                i += 2
            else:
                return False
        
        return has_two