"""
Problem: Game of Life
Difficulty: Medium
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        m, n = len(board), len(board[0])
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
        
        for i in range(m):
            for j in range(n):
                live_neighbors = 0
                for dr, dc in directions:
                    r, c = i + dr, j + dc
                    if 0 <= r < m and 0 <= c < n:
                        if board[r][c] == 1 or board[r][c] == -1:
                            live_neighbors += 1
                
                if board[i][j] == 1:
                    if live_neighbors < 2 or live_neighbors > 3:
                        board[i][j] = -1
                else:
                    if live_neighbors == 3:
                        board[i][j] = 2
        
        for i in range(m):
            for j in range(n):
                if board[i][j] == -1:
                    board[i][j] = 0
                elif board[i][j] == 2:
                    board[i][j] = 1