"""
Problem: Cut Off Trees for Golf Event
Difficulty: Hard
Tags: array, tree, search, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import deque

class Solution:
    def cutOffTree(self, forest: List[List[int]]) -> int:
        trees = sorted([(forest[i][j], i, j) for i in range(len(forest)) 
                       for j in range(len(forest[0])) if forest[i][j] > 1])
        
        def bfs(start, end):
            sx, sy = start
            ex, ey = end
            queue = deque([(sx, sy, 0)])
            seen = {(sx, sy)}
            
            while queue:
                x, y, steps = queue.popleft()
                if (x, y) == (ex, ey):
                    return steps
                
                for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                    nx, ny = x + dx, y + dy
                    if (0 <= nx < len(forest) and 0 <= ny < len(forest[0]) and
                        forest[nx][ny] != 0 and (nx, ny) not in seen):
                        seen.add((nx, ny))
                        queue.append((nx, ny, steps + 1))
            
            return -1
        
        result = 0
        start = (0, 0)
        
        for _, x, y in trees:
            steps = bfs(start, (x, y))
            if steps == -1:
                return -1
            result += steps
            start = (x, y)
        
        return result