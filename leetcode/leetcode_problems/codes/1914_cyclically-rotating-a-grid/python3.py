"""
Problem: Cyclically Rotating a Grid
Difficulty: Medium
Tags: array, simulation

Approach: Extract each layer, rotate, put back
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n)
"""

class Solution:
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        result = [[0] * n for _ in range(m)]
        
        layers = min(m, n) // 2
        
        for layer in range(layers):
            elements = []
            # Extract layer
            for j in range(layer, n - layer):
                elements.append(grid[layer][j])
            for i in range(layer + 1, m - layer):
                elements.append(grid[i][n - 1 - layer])
            for j in range(n - 2 - layer, layer - 1, -1):
                elements.append(grid[m - 1 - layer][j])
            for i in range(m - 2 - layer, layer, -1):
                elements.append(grid[i][layer])
            
            # Rotate
            rot = k % len(elements)
            elements = elements[-rot:] + elements[:-rot]
            
            # Put back
            idx = 0
            for j in range(layer, n - layer):
                result[layer][j] = elements[idx]
                idx += 1
            for i in range(layer + 1, m - layer):
                result[i][n - 1 - layer] = elements[idx]
                idx += 1
            for j in range(n - 2 - layer, layer - 1, -1):
                result[m - 1 - layer][j] = elements[idx]
                idx += 1
            for i in range(m - 2 - layer, layer, -1):
                result[i][layer] = elements[idx]
                idx += 1
        
        return result