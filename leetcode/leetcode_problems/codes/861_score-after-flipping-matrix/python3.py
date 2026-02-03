class Solution:
    def matrixScore(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        for i in range(m):
            if grid[i][0] == 0:
                for j in range(n):
                    grid[i][j] = 1 - grid[i][j]
        
        result = m * (1 << (n - 1))
        
        for j in range(1, n):
            count = sum(grid[i][j] for i in range(m))
            result += max(count, m - count) * (1 << (n - 1 - j))
        
        return result
