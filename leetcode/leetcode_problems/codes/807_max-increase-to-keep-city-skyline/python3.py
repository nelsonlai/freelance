class Solution:
    def maxIncreaseKeepingSkyline(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        rowMax = [max(row) for row in grid]
        colMax = [max(grid[i][j] for i in range(m)) for j in range(n)]
        
        result = 0
        for i in range(m):
            for j in range(n):
                result += min(rowMax[i], colMax[j]) - grid[i][j]
        return result
