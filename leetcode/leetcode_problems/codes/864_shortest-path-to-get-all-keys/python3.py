from collections import deque

class Solution:
    def shortestPathAllKeys(self, grid: List[str]) -> int:
        m, n = len(grid), len(grid[0])
        start = None
        keys = 0
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '@':
                    start = (i, j)
                elif grid[i][j].islower():
                    keys |= 1 << (ord(grid[i][j]) - ord('a'))
        
        queue = deque([(*start, 0, 0)])
        visited = {(*start, 0)}
        
        while queue:
            r, c, collected, steps = queue.popleft()
            
            if collected == keys:
                return steps
            
            for dr, dc in [(0,1), (1,0), (0,-1), (-1,0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] != '#':
                    cell = grid[nr][nc]
                    newCollected = collected
                    
                    if cell.islower():
                        newCollected |= 1 << (ord(cell) - ord('a'))
                    elif cell.isupper():
                        if not (collected & (1 << (ord(cell) - ord('A')))):
                            continue
                    
                    state = (nr, nc, newCollected)
                    if state not in visited:
                        visited.add(state)
                        queue.append((nr, nc, newCollected, steps + 1))
        
        return -1
