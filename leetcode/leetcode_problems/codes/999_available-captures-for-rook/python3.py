"""
Problem: Available Captures for Rook
Difficulty: Easy
Tags: array

Approach: Find rook position, check four directions for pawns
Time Complexity: O(8) = O(1)
Space Complexity: O(1)
"""

class Solution:
    def numRookCaptures(self, board: List[List[str]]) -> int:
        # Find rook
        for i in range(8):
            for j in range(8):
                if board[i][j] == 'R':
                    rook_i, rook_j = i, j
                    break
        
        count = 0
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        for di, dj in directions:
            ni, nj = rook_i + di, rook_j + dj
            while 0 <= ni < 8 and 0 <= nj < 8:
                if board[ni][nj] == 'p':
                    count += 1
                    break
                if board[ni][nj] == 'B':
                    break
                ni += di
                nj += dj
        
        return count