"""
Problem: Path Crossing
Difficulty: Easy
Tags: string, hash

Approach: Track visited positions, check if current position was visited
Time Complexity: O(n) where n is length of path
Space Complexity: O(n) for visited set
"""

class Solution:
    def isPathCrossing(self, path: str) -> bool:
        visited = {(0, 0)}
        x, y = 0, 0
        
        directions = {'N': (0, 1), 'S': (0, -1), 'E': (1, 0), 'W': (-1, 0)}
        
        for direction in path:
            dx, dy = directions[direction]
            x += dx
            y += dy
            
            if (x, y) in visited:
                return True
            visited.add((x, y))
        
        return False