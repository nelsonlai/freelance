"""
Problem: Remove Colored Pieces if Both Neighbors are the Same Color
Difficulty: Medium
Tags: string, greedy, math

Approach: Count consecutive A's and B's of length >= 3, Alice wins if more moves
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def winnerOfGame(self, colors: str) -> bool:
        alice_moves = 0
        bob_moves = 0
        
        i = 0
        while i < len(colors):
            char = colors[i]
            count = 0
            while i < len(colors) and colors[i] == char:
                count += 1
                i += 1
            
            if char == 'A' and count >= 3:
                alice_moves += count - 2
            elif char == 'B' and count >= 3:
                bob_moves += count - 2
        
        return alice_moves > bob_moves