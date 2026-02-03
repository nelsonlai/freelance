class Solution:
    def containVirus(self, isInfected: List[List[int]]) -> int:
        m, n = len(isInfected), len(isInfected[0])
        result = 0
        
        while True:
            regions = []
            visited = set()
            
            for i in range(m):
                for j in range(n):
                    if isInfected[i][j] == 1 and (i, j) not in visited:
                        region = []
                        frontiers = set()
                        self.dfs(isInfected, i, j, visited, region, frontiers)
                        if frontiers:
                            regions.append((len(frontiers), region, frontiers))
            
            if not regions:
                break
            
            regions.sort(reverse=True)
            target = regions[0]
            
            for i, j in target[1]:
                isInfected[i][j] = 2
            
            result += len(target[2])
            
            for _, region, _ in regions[1:]:
                for i, j in region:
                    for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                        ni, nj = i + di, j + dj
                        if 0 <= ni < m and 0 <= nj < n and isInfected[ni][nj] == 0:
                            isInfected[ni][nj] = 1
        
        return result
    
    def dfs(self, grid, i, j, visited, region, frontiers):
        if (i, j) in visited:
            return
        visited.add((i, j))
        region.append((i, j))
        m, n = len(grid), len(grid[0])
        for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            ni, nj = i + di, j + dj
            if 0 <= ni < m and 0 <= nj < n:
                if grid[ni][nj] == 0:
                    frontiers.add((ni, nj))
                elif grid[ni][nj] == 1:
                    self.dfs(grid, ni, nj, visited, region, frontiers)
