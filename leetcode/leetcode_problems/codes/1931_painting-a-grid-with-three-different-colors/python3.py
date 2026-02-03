"""
Problem: Painting a Grid With Three Different Colors
Difficulty: Hard
Tags: dp, bitmask

Approach: DP with bitmask - track valid colorings for each column
Time Complexity: O(n * 3^m * m) where n is columns, m is rows
Space Complexity: O(3^m)
"""

from functools import lru_cache

class Solution:
    def colorTheGrid(self, m: int, n: int) -> int:
        MOD = 10**9 + 7
        
        @lru_cache(None)
        def get_valid_colors(prev_col):
            colors = []
            for mask in range(3 ** m):
                valid = True
                temp = mask
                prev = prev_col
                for i in range(m):
                    curr = temp % 3
                    prev_digit = prev % 3
                    if curr == prev_digit:
                        valid = False
                        break
                    if i > 0:
                        prev_temp = (temp // 3) % 3
                        if curr == prev_temp:
                            valid = False
                            break
                    temp //= 3
                    prev //= 3
                if valid:
                    colors.append(mask)
            return colors
        
        @lru_cache(None)
        def dp(col, prev_col):
            if col == n:
                return 1
            
            valid_colors = get_valid_colors(prev_col)
            result = 0
            for color in valid_colors:
                result = (result + dp(col + 1, color)) % MOD
            return result
        
        return dp(0, -1)