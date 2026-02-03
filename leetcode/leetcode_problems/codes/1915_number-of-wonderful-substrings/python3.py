"""
Problem: Number of Wonderful Substrings
Difficulty: Medium
Tags: array, string, hash, bit manipulation

Approach: Use prefix XOR to track character parity, count substrings with at most 1 odd count
Time Complexity: O(n * 10) where n is length, 10 is possible characters
Space Complexity: O(1024) for mask counts
"""

from collections import defaultdict

class Solution:
    def wonderfulSubstrings(self, word: str) -> int:
        count = defaultdict(int)
        count[0] = 1
        mask = 0
        result = 0
        
        for char in word:
            idx = ord(char) - ord('a')
            mask ^= (1 << idx)
            
            # All even counts
            result += count[mask]
            
            # One odd count
            for i in range(10):
                result += count[mask ^ (1 << i)]
            
            count[mask] += 1
        
        return result