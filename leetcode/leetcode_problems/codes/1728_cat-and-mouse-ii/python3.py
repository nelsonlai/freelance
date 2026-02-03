"""
Problem: Cat and Mouse II
Difficulty: Hard
Tags: array, graph, dp, game theory

Approach: Minimax with memoization - mouse tries to win, cat tries to prevent
Time Complexity: O(m * n * (m * n)^2) worst case
Space Complexity: O(m * n * m * n) for memoization
"""

from functools import lru_cache

class Solution:
    def canMouseWin(self, grid: List[str], catJump: int, mouseJump: int) -> bool:
        m, n = len(grid), len(grid[0])
        
        # Find positions
        mouse_pos = cat_pos = food_pos = None
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 'M':
                    mouse_pos = (i, j)
                elif grid[i][j] == 'C':
                    cat_pos = (i, j)
                elif grid[i][j] == 'F':
                    food_pos = (i, j)
        
        @lru_cache(maxsize=None)
        def dfs(mx, my, cx, cy, turn):
            if (mx, my) == food_pos:
                return True
            if (cx, cy) == (mx, my) or (cx, cy) == food_pos:
                return False
            if turn > 100:  # Prevent infinite loops
                return False
            
            if turn % 2 == 0:  # Mouse's turn
                for dx, dy in [(0,1), (0,-1), (1,0), (-1,0)]:
                    for step in range(1, mouseJump + 1):
                        nmx, nmy = mx + dx * step, my + dy * step
                        if 0 <= nmx < m and 0 <= nmy < n and grid[nmx][nmy] != '#':
                            if dfs(nmx, nmy, cx, cy, turn + 1):
                                return True
                        else:
                            break
                return False
            else:  # Cat's turn
                for dx, dy in [(0,1), (0,-1), (1,0), (-1,0)]:
                    for step in range(1, catJump + 1):
                        ncx, ncy = cx + dx * step, cy + dy * step
                        if 0 <= ncx < m and 0 <= ncy < n and grid[ncx][ncy] != '#':
                            if not dfs(mx, my, ncx, ncy, turn + 1):
                                return False
                        else:
                            break
                return True
        
        return dfs(mouse_pos[0], mouse_pos[1], cat_pos[0], cat_pos[1], 0)