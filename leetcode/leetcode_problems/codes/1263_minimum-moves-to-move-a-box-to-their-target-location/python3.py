"""
Problem: Minimum Moves to Move a Box to Their Target Location
Difficulty: Hard
Tags: array, tree, search, queue, heap

Approach: BFS with state (box_r, box_c, player_r, player_c), use A* or Dijkstra
Time Complexity: O(m * n * m * n) in worst case
Space Complexity: O(m * n * m * n) for visited states
"""

from collections import deque

class Solution:
    def minPushBox(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        # Find initial positions
        box = player = target = None
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 'B':
                    box = (i, j)
                elif grid[i][j] == 'S':
                    player = (i, j)
                elif grid[i][j] == 'T':
                    target = (i, j)
        
        def can_reach(player_pos, target_pos, box_pos):
            queue = deque([player_pos])
            visited = {player_pos}
            
            while queue:
                r, c = queue.popleft()
                if (r, c) == target_pos:
                    return True
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if (0 <= nr < m and 0 <= nc < n and 
                        grid[nr][nc] != '#' and 
                        (nr, nc) != box_pos and 
                        (nr, nc) not in visited):
                        visited.add((nr, nc))
                        queue.append((nr, nc))
            
            return False
        
        # BFS: state is (box_r, box_c, player_r, player_c)
        queue = deque([(box[0], box[1], player[0], player[1], 0)])
        visited = {(box[0], box[1], player[0], player[1])}
        
        while queue:
            br, bc, pr, pc, pushes = queue.popleft()
            
            if (br, bc) == target:
                return pushes
            
            # Try pushing box in each direction
            for dr, dc in directions:
                nbr, nbc = br + dr, bc + dc
                pbr, pbc = br - dr, bc - dc  # Player needs to be here
                
                if (0 <= nbr < m and 0 <= nbc < n and 
                    grid[nbr][nbc] != '#' and
                    0 <= pbr < m and 0 <= pbc < n and
                    grid[pbr][pbc] != '#'):
                    
                    # Check if player can reach the push position
                    if can_reach((pr, pc), (pbr, pbc), (br, bc)):
                        state = (nbr, nbc, br, bc)
                        if state not in visited:
                            visited.add(state)
                            queue.append((nbr, nbc, br, bc, pushes + 1))
        
        return -1