"""
Problem: Tiling a Rectangle with the Fewest Squares
Difficulty: Hard
Tags: general

Approach: DFS with memoization - try all possible square placements
Time Complexity: O(m * n * (m + n)) in worst case
Space Complexity: O(m * n) for memoization
"""

class Solution:
    def tilingRectangle(self, n: int, m: int) -> int:
        if n == m:
            return 1
        if n > m:
            n, m = m, n
        
        memo = {}
        
        def dfs(height):
            if tuple(height) in memo:
                return memo[tuple(height)]
            
            if all(h == n for h in height):
                return 0
            
            min_h = min(height)
            start = height.index(min_h)
            end = start
            while end < m and height[end] == min_h:
                end += 1
            
            result = float('inf')
            max_size = min(end - start, n - min_h)
            
            for size in range(max_size, 0, -1):
                new_height = list(height)
                for i in range(start, start + size):
                    new_height[i] += size
                result = min(result, 1 + dfs(tuple(new_height)))
            
            memo[tuple(height)] = result
            return result
        
        return dfs(tuple([0] * m))