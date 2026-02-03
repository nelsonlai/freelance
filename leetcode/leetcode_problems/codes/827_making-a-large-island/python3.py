class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        n = len(grid)
        index = 2
        area = {}
        
        def dfs(r, c, idx):
            if r < 0 or r >= n or c < 0 or c >= n or grid[r][c] != 1:
                return 0
            grid[r][c] = idx
            return 1 + dfs(r+1, c, idx) + dfs(r-1, c, idx) + dfs(r, c+1, idx) + dfs(r, c-1, idx)
        
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    area[index] = dfs(i, j, index)
                    index += 1
        
        result = max(area.values() or [0])
        
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 0:
                    seen = set()
                    for di, dj in [(0,1), (1,0), (0,-1), (-1,0)]:
                        ni, nj = i + di, j + dj
                        if 0 <= ni < n and 0 <= nj < n and grid[ni][nj] > 1:
                            seen.add(grid[ni][nj])
                    result = max(result, 1 + sum(area[idx] for idx in seen))
        
        return result
