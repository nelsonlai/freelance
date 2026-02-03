"""
Problem: Find Winner on a Tic Tac Toe Game
Difficulty: Easy
Tags: array, hash

Approach: Track row, column, and diagonal counts for each player
Time Complexity: O(n) where n is number of moves
Space Complexity: O(1)
"""

class Solution:
    def tictactoe(self, moves: List[List[int]]) -> str:
        rows = [0] * 3
        cols = [0] * 3
        diag1 = diag2 = 0
        
        for i, (r, c) in enumerate(moves):
            player = 1 if i % 2 == 0 else -1
            rows[r] += player
            cols[c] += player
            if r == c:
                diag1 += player
            if r + c == 2:
                diag2 += player
            
            if abs(rows[r]) == 3 or abs(cols[c]) == 3 or abs(diag1) == 3 or abs(diag2) == 3:
                return "A" if player == 1 else "B"
        
        return "Draw" if len(moves) == 9 else "Pending"