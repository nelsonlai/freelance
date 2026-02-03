"""
Problem: Count Number of Homogenous Substrings
Difficulty: Medium
Tags: string, math

Approach: Count consecutive same characters, for length n, add n*(n+1)/2 substrings
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

MOD = 10**9 + 7

class Solution:
    def countHomogenous(self, s: str) -> int:
        result = 0
        count = 1
        
        for i in range(1, len(s)):
            if s[i] == s[i-1]:
                count += 1
            else:
                result = (result + count * (count + 1) // 2) % MOD
                count = 1
        
        result = (result + count * (count + 1) // 2) % MOD
        return result