"""
Problem: Last Substring in Lexicographical Order
Difficulty: Hard
Tags: array, string, tree, graph

Approach: Two pointers - find starting position of lexicographically largest substring
Time Complexity: O(n) where n is the length of s
Space Complexity: O(1)
"""

class Solution:
    def lastSubstring(self, s: str) -> str:
        i, j, k = 0, 1, 0
        n = len(s)
        
        while j + k < n:
            if s[i + k] == s[j + k]:
                k += 1
            elif s[i + k] < s[j + k]:
                i = max(i + k + 1, j)
                j = i + 1
                k = 0
            else:
                j += k + 1
                k = 0
        
        return s[i:]