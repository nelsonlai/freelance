class Solution:
    def numDistinctIslands2(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        seen = set()
        
        def dfs(i, j):
            shape = []
            stack = [(i, j)]
            grid[i][j] = 0
            while stack:
                r, c = stack.pop()
                shape.append((r - i, c - j))
                for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == 1:
                        grid[nr][nc] = 0
                        stack.append((nr, nc))
            return shape
        
        def normalize(shape):
            rotations = [
                [(x, y) for x, y in shape],
                [(-x, y) for x, y in shape],
                [(x, -y) for x, y in shape],
                [(-x, -y) for x, y in shape],
                [(y, x) for x, y in shape],
                [(-y, x) for x, y in shape],
                [(y, -x) for x, y in shape],
                [(-y, -x) for x, y in shape],
            ]
            normalized = []
            for rot in rotations:
                rot.sort()
                if rot:
                    minX, minY = rot[0]
                    normalized.append(tuple((x - minX, y - minY) for x, y in rot))
            normalized.sort()
            return tuple(normalized[0])
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    shape = dfs(i, j)
                    seen.add(normalize(shape))
        
        return len(seen)
