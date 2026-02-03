"""
Problem: Where Will the Ball Fall
Difficulty: Medium
Tags: array, simulation

Approach: Simulate ball falling - 1 goes right, -1 goes left, check for V shape
Time Complexity: O(m * n) where m is rows, n is columns
Space Complexity: O(n) for result
"""

class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])
        result = []
        
        for col in range(n):
            current_col = col
            for row in range(m):
                if grid[row][current_col] == 1:
                    # Ball goes right
                    if current_col + 1 >= n or grid[row][current_col + 1] == -1:
                        current_col = -1
                        break
                    current_col += 1
                else:
                    # Ball goes left
                    if current_col - 1 < 0 or grid[row][current_col - 1] == 1:
                        current_col = -1
                        break
                    current_col -= 1
            
            result.append(current_col)
        
        return result