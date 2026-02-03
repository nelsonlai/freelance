"""
Problem: Count Sub Islands
Difficulty: Medium
Tags: array, graph, search, DFS

Approach: DFS on grid2, check if all cells are also in grid1
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n) for recursion stack
"""

class Solution:
    def countSubIslands(self, grid1: List[List[int]], grid2: List[List[int]]) -> int:
        m, n = len(grid1), len(grid1[0])
        
        def dfs(i, j):
            if i < 0 or i >= m or j < 0 or j >= n or grid2[i][j] == 0:
                return True
            
            grid2[i][j] = 0
            isSubIsland = grid1[i][j] == 1
            
            isSubIsland = dfs(i + 1, j) and isSubIsland
            isSubIsland = dfs(i - 1, j) and isSubIsland
            isSubIsland = dfs(i, j + 1) and isSubIsland
            isSubIsland = dfs(i, j - 1) and isSubIsland
            
            return isSubIsland
        
        count = 0
        for i in range(m):
            for j in range(n):
                if grid2[i][j] == 1:
                    if dfs(i, j):
                        count += 1
        
        return count