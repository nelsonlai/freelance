"""
Problem: Minimum Moves to Convert String
Difficulty: Easy
Tags: string, greedy

Approach: Greedy - convert leftmost 'X' and next 2 characters in each move
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minimumMoves(self, s: str) -> int:
        moves = 0
        i = 0
        
        while i < len(s):
            if s[i] == 'X':
                moves += 1
                i += 3  # Skip next 2 characters
            else:
                i += 1
        
        return moves