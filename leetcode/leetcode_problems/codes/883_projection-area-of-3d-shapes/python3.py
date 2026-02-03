class Solution:
    def projectionArea(self, grid: List[List[int]]) -> int:
        n = len(grid)
        result = 0
        
        for i in range(n):
            maxRow = maxCol = 0
            for j in range(n):
                if grid[i][j] > 0:
                    result += 1
                maxRow = max(maxRow, grid[i][j])
                maxCol = max(maxCol, grid[j][i])
            result += maxRow + maxCol
        
        return result
