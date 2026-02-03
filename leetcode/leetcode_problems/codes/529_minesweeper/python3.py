"""
Problem: Minesweeper
Difficulty: Medium
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import deque

class Solution:
    def updateBoard(self, board: List[List[str]], click: List[int]) -> List[List[str]]:
        m, n = len(board), len(board[0])
        directions = [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
        row, col = click
        
        if board[row][col] == 'M':
            board[row][col] = 'X'
            return board
        
        queue = deque([(row, col)])
        board[row][col] = 'B'
        
        while queue:
            r, c = queue.popleft()
            mines = 0
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and board[nr][nc] == 'M':
                    mines += 1
            
            if mines > 0:
                board[r][c] = str(mines)
            else:
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and board[nr][nc] == 'E':
                        board[nr][nc] = 'B'
                        queue.append((nr, nc))
        
        return board