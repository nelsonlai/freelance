"""
Problem: Longest Happy Prefix
Difficulty: Hard
Tags: string, hash

Approach: KMP algorithm - compute longest prefix suffix array
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for LPS array
"""

class Solution:
    def longestPrefix(self, s: str) -> str:
        n = len(s)
        lps = [0] * n
        length = 0
        i = 1
        
        while i < n:
            if s[i] == s[length]:
                length += 1
                lps[i] = length
                i += 1
            else:
                if length != 0:
                    length = lps[length - 1]
                else:
                    lps[i] = 0
                    i += 1
        
        return s[:lps[-1]]