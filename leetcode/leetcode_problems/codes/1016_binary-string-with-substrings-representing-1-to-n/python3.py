"""
Problem: Binary String With Substrings Representing 1 To N
Difficulty: Medium
Tags: array, string, tree, hash

Approach: Check if all numbers from 1 to n have binary representation as substring
Time Complexity: O(n * log n * m) where m is string length
Space Complexity: O(n) for set
"""

class Solution:
    def queryString(self, s: str, n: int) -> bool:
        found = set()
        
        for i in range(len(s)):
            num = 0
            for j in range(i, min(i + 32, len(s))):
                num = num * 2 + int(s[j])
                if 1 <= num <= n:
                    found.add(num)
                if num > n:
                    break
        
        return len(found) == n