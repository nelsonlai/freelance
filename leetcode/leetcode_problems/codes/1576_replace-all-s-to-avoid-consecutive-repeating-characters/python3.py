"""
Problem: Replace All ?'s to Avoid Consecutive Repeating Characters
Difficulty: Easy
Tags: string

Approach: For each ?, choose a character different from neighbors
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def modifyString(self, s: str) -> str:
        result = list(s)
        n = len(s)
        
        for i in range(n):
            if result[i] == '?':
                for char in 'abc':
                    if (i == 0 or result[i-1] != char) and (i == n-1 or result[i+1] != char):
                        result[i] = char
                        break
        
        return ''.join(result)