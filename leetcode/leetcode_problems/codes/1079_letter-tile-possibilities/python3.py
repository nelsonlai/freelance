"""
Problem: Letter Tile Possibilities
Difficulty: Medium
Tags: string, hash

Approach: Backtracking - generate all possible sequences with counts
Time Complexity: O(2^n) worst case
Space Complexity: O(n) for recursion
"""

from collections import Counter

class Solution:
    def numTilePossibilities(self, tiles: str) -> int:
        count = Counter(tiles)
        self.result = 0
        
        def backtrack():
            self.result += 1
            for char in count:
                if count[char] > 0:
                    count[char] -= 1
                    backtrack()
                    count[char] += 1
        
        backtrack()
        return self.result - 1  # Subtract empty sequence