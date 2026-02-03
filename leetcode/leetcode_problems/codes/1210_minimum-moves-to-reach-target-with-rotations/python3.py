"""
Problem: Minimum Moves to Reach Target with Rotations
Difficulty: Hard
Tags: array, search

Approach: BFS - snake can be horizontal or vertical, try moving right/down or rotating
Time Complexity: O(n^2) where n is grid size
Space Complexity: O(n^2) for visited states
"""

from collections import deque

class Solution:
    def minimumMoves(self, grid: List[List[int]]) -> int:
        n = len(grid)
        # State: (tail_row, tail_col, is_horizontal)
        # Horizontal: tail at (r, c), head at (r, c+1)
        # Vertical: tail at (r, c), head at (r+1, c)
        
        visited = set()
        queue = deque([(0, 0, True, 0)])  # (r, c, is_horizontal, moves)
        visited.add((0, 0, True))
        
        while queue:
            r, c, is_horizontal, moves = queue.popleft()
            
            # Check if reached target
            if is_horizontal and r == n - 1 and c == n - 2:
                return moves
            
            # Move right
            if is_horizontal and c + 2 < n and grid[r][c + 2] == 0:
                if (r, c + 1, True) not in visited:
                    visited.add((r, c + 1, True))
                    queue.append((r, c + 1, True, moves + 1))
            elif not is_horizontal and c + 1 < n and grid[r][c + 1] == 0 and grid[r + 1][c + 1] == 0:
                if (r, c + 1, False) not in visited:
                    visited.add((r, c + 1, False))
                    queue.append((r, c + 1, False, moves + 1))
            
            # Move down
            if is_horizontal and r + 1 < n and grid[r + 1][c] == 0 and grid[r + 1][c + 1] == 0:
                if (r + 1, c, True) not in visited:
                    visited.add((r + 1, c, True))
                    queue.append((r + 1, c, True, moves + 1))
            elif not is_horizontal and r + 2 < n and grid[r + 2][c] == 0:
                if (r + 1, c, False) not in visited:
                    visited.add((r + 1, c, False))
                    queue.append((r + 1, c, False, moves + 1))
            
            # Rotate clockwise (horizontal -> vertical)
            if is_horizontal and r + 1 < n and grid[r + 1][c] == 0 and grid[r + 1][c + 1] == 0:
                if (r, c, False) not in visited:
                    visited.add((r, c, False))
                    queue.append((r, c, False, moves + 1))
            
            # Rotate counterclockwise (vertical -> horizontal)
            if not is_horizontal and c + 1 < n and grid[r][c + 1] == 0 and grid[r + 1][c + 1] == 0:
                if (r, c, True) not in visited:
                    visited.add((r, c, True))
                    queue.append((r, c, True, moves + 1))
        
        return -1