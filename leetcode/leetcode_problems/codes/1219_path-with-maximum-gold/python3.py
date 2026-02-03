"""
Problem: Path with Maximum Gold
Difficulty: Medium
Tags: array

Approach: DFS from each cell with gold, backtrack to find maximum path
Time Complexity: O(m * n * 4^k) where k is average path length
Space Complexity: O(m * n) for recursion stack
"""

class Solution:
    def getMaximumGold(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        max_gold = 0
        
        def dfs(r, c, visited):
            if r < 0 or r >= m or c < 0 or c >= n or grid[r][c] == 0 or (r, c) in visited:
                return 0
            
            visited.add((r, c))
            current_gold = grid[r][c]
            max_path = 0
            
            for dr, dc in directions:
                max_path = max(max_path, dfs(r + dr, c + dc, visited))
            
            visited.remove((r, c))
            return current_gold + max_path
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] > 0:
                    max_gold = max(max_gold, dfs(i, j, set()))
        
        return max_gold