"""
Problem: Number of Substrings With Only 1s
Difficulty: Medium
Tags: string, tree, math

Approach: Count consecutive 1s, for length n, there are n*(n+1)/2 substrings
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def numSub(self, s: str) -> int:
        MOD = 10**9 + 7
        result = 0
        count = 0
        
        for char in s:
            if char == '1':
                count += 1
                result = (result + count) % MOD
            else:
                count = 0
        
        return result