class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        def isMagic(i, j):
            seen = set()
            for di in range(3):
                for dj in range(3):
                    val = grid[i+di][j+dj]
                    if val < 1 or val > 9 or val in seen:
                        return False
                    seen.add(val)
            
            s = grid[i][j] + grid[i][j+1] + grid[i][j+2]
            return (grid[i+1][j] + grid[i+1][j+1] + grid[i+1][j+2] == s and
                    grid[i+2][j] + grid[i+2][j+1] + grid[i+2][j+2] == s and
                    grid[i][j] + grid[i+1][j] + grid[i+2][j] == s and
                    grid[i][j+1] + grid[i+1][j+1] + grid[i+2][j+1] == s and
                    grid[i][j+2] + grid[i+1][j+2] + grid[i+2][j+2] == s and
                    grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2] == s and
                    grid[i][j+2] + grid[i+1][j+1] + grid[i+2][j] == s)
        
        result = 0
        for i in range(len(grid) - 2):
            for j in range(len(grid[0]) - 2):
                if isMagic(i, j):
                    result += 1
        return result
