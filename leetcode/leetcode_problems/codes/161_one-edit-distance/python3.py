"""
Problem: One Edit Distance
Difficulty: Medium
Tags: array, string

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isOneEditDistance(self, s: str, t: str) -> bool:
        m, n = len(s), len(t)
        
        if abs(m - n) > 1:
            return False
        
        if m > n:
            return self.isOneEditDistance(t, s)
        
        i = 0
        while i < m and s[i] == t[i]:
            i += 1
        
        if i == m:
            return n == m + 1
        
        if m == n:
            return s[i+1:] == t[i+1:]
        else:
            return s[i:] == t[i+1:]