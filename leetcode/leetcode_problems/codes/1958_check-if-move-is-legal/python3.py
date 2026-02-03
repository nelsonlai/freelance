"""
Problem: Check if Move is Legal
Difficulty: Medium
Tags: array, simulation

Approach: Check all 8 directions for valid line of opposite color ending with same color
Time Complexity: O(8 * n) where n is board size
Space Complexity: O(1)
"""

class Solution:
    def checkMove(self, board: List[List[str]], rMove: int, cMove: int, color: str) -> bool:
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0), 
                      (1, 1), (1, -1), (-1, 1), (-1, -1)]
        rows, cols = len(board), len(board[0])
        
        for dr, dc in directions:
            r, c = rMove + dr, cMove + dc
            count = 0
            
            while 0 <= r < rows and 0 <= c < cols:
                if board[r][c] == '.':
                    break
                if board[r][c] == color:
                    if count >= 1:
                        return True
                    break
                if board[r][c] != color:
                    count += 1
                r += dr
                c += dc
        
        return False