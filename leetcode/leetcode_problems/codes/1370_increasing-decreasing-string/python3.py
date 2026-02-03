"""
Problem: Increasing Decreasing String
Difficulty: Easy
Tags: string, hash

Approach: Count characters, alternate between ascending and descending order
Time Complexity: O(n) where n is length of s
Space Complexity: O(1) for character counts
"""

from collections import Counter

class Solution:
    def sortString(self, s: str) -> str:
        count = Counter(s)
        result = []
        chars = sorted(count.keys())
        
        while len(result) < len(s):
            for char in chars:
                if count[char] > 0:
                    result.append(char)
                    count[char] -= 1
            for char in reversed(chars):
                if count[char] > 0:
                    result.append(char)
                    count[char] -= 1
        
        return ''.join(result)