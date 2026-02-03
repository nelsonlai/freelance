"""
Problem: Minimum Knight Moves
Difficulty: Medium
Tags: search

Approach: BFS from origin to target, use symmetry to reduce search space
Time Complexity: O(|x| * |y|) in worst case
Space Complexity: O(|x| * |y|) for visited set
"""

class Solution:
    def minKnightMoves(self, x: int, y: int) -> int:
        from collections import deque
        
        # Use absolute values due to symmetry
        x, y = abs(x), abs(y)
        
        moves = [(2, 1), (2, -1), (-2, 1), (-2, -1),
                 (1, 2), (1, -2), (-1, 2), (-1, -2)]
        
        queue = deque([(0, 0, 0)])
        visited = {(0, 0)}
        
        while queue:
            curr_x, curr_y, steps = queue.popleft()
            
            if curr_x == x and curr_y == y:
                return steps
            
            for dx, dy in moves:
                nx, ny = curr_x + dx, curr_y + dy
                # Constrain to first quadrant and some buffer
                if (nx, ny) not in visited and nx >= -2 and ny >= -2:
                    visited.add((nx, ny))
                    queue.append((nx, ny, steps + 1))
        
        return -1