class Solution:
    def countCornerRectangles(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        result = 0
        
        for i in range(m):
            for j in range(i + 1, m):
                count = 0
                for k in range(n):
                    if grid[i][k] == 1 and grid[j][k] == 1:
                        count += 1
                result += count * (count - 1) // 2
        
        return result
