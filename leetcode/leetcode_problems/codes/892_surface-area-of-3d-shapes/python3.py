class Solution:
    def surfaceArea(self, grid: List[List[int]]) -> int:
        n = len(grid)
        result = 0
        
        for i in range(n):
            for j in range(n):
                if grid[i][j]:
                    result += 2
                    for di, dj in [(0,1), (1,0)]:
                        ni, nj = i + di, j + dj
                        if ni < n and nj < n:
                            result += abs(grid[i][j] - grid[ni][nj])
                        else:
                            result += grid[i][j]
                    if i == 0:
                        result += grid[i][j]
                    if j == 0:
                        result += grid[i][j]
                    if i == n - 1:
                        result += grid[i][j]
                    if j == n - 1:
                        result += grid[i][j]
        
        return result
