class Solution:
    def hitBricks(self, grid: List[List[int]], hits: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])
        
        def dfs(i, j):
            if not (0 <= i < m and 0 <= j < n) or grid[i][j] != 1:
                return 0
            grid[i][j] = 2
            return 1 + sum(dfs(i+di, j+dj) for di, dj in [(0,1), (1,0), (0,-1), (-1,0)])
        
        for i, j in hits:
            if grid[i][j] == 1:
                grid[i][j] = 0
        
        for j in range(n):
            dfs(0, j)
        
        result = []
        for i, j in reversed(hits):
            grid[i][j] = 1
            if i == 0 or any(0 <= i+di < m and 0 <= j+dj < n and grid[i+di][j+dj] == 2 
                            for di, dj in [(0,1), (1,0), (0,-1), (-1,0)]):
                count = dfs(i, j) - 1
                result.append(count)
            else:
                result.append(0)
        
        return result[::-1]
