"""
Problem: Rotating the Box
Difficulty: Medium
Tags: array, simulation

Approach: First apply gravity (stones fall), then rotate 90 degrees
Time Complexity: O(n * m) where n, m are dimensions
Space Complexity: O(n * m)
"""

class Solution:
    def rotateTheBox(self, boxGrid: List[List[str]]) -> List[List[str]]:
        m, n = len(boxGrid), len(boxGrid[0])
        
        # Apply gravity: stones fall down
        for j in range(n):
            # Process column from bottom to top
            write_pos = m - 1
            for i in range(m - 1, -1, -1):
                if boxGrid[i][j] == '*':
                    # Obstacle: reset write position
                    write_pos = i - 1
                elif boxGrid[i][j] == '#':
                    # Stone: move to write position
                    if write_pos != i:
                        boxGrid[write_pos][j] = '#'
                        boxGrid[i][j] = '.'
                    write_pos -= 1
        
        # Rotate 90 degrees clockwise
        result = [[''] * m for _ in range(n)]
        for i in range(m):
            for j in range(n):
                result[j][m - 1 - i] = boxGrid[i][j]
        
        return result