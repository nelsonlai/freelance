"""
Problem: Maximize Grid Happiness
Difficulty: Hard
Tags: dp, bitmask, state compression

Approach: DP with state compression - track last n cells, use bitmask for introvert/extrovert
Time Complexity: O(m * n * 3^n * introvertsCount * extrovertsCount)
Space Complexity: O(m * 3^n * introvertsCount * extrovertsCount)
"""

from functools import lru_cache

class Solution:
    def getMaxGridHappiness(self, m: int, n: int, introvertsCount: int, extrovertsCount: int) -> int:
        @lru_cache(maxsize=None)
        def dp(pos, intro, extro, prev_state):
            if pos == m * n or (intro == 0 and extro == 0):
                return 0
            
            row, col = pos // n, pos % n
            res = dp(pos + 1, intro, extro, prev_state // 3)  # Empty cell
            
            neighbors = 0
            if row > 0:
                neighbors += (prev_state // (3 ** (n - 1))) % 3
            if col > 0:
                neighbors += (prev_state % 3)
            
            if intro > 0:
                happiness = 120
                if neighbors == 1:  # Introvert neighbor
                    happiness -= 60
                elif neighbors == 2:  # Extrovert neighbor
                    happiness -= 10
                res = max(res, happiness + dp(pos + 1, intro - 1, extro, (prev_state * 3 + 1) % (3 ** n)))
            
            if extro > 0:
                happiness = 40
                if neighbors == 1:  # Introvert neighbor
                    happiness -= 10
                elif neighbors == 2:  # Extrovert neighbor
                    happiness += 40
                res = max(res, happiness + dp(pos + 1, intro, extro - 1, (prev_state * 3 + 2) % (3 ** n)))
            
            return res
        
        return dp(0, introvertsCount, extrovertsCount, 0)