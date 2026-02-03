"""
Problem: Best Position for a Service Centre
Difficulty: Hard
Tags: array, math

Approach: Use gradient descent or geometric median - start from centroid, iteratively improve
Time Complexity: O(n * iterations) where iterations is convergence steps
Space Complexity: O(1)
"""

class Solution:
    def getMinDistSum(self, positions: List[List[int]]) -> float:
        def dist(x, y):
            return sum(((x - px)**2 + (y - py)**2)**0.5 for px, py in positions)
        
        # Start from centroid
        n = len(positions)
        x = sum(px for px, _ in positions) / n
        y = sum(py for _, py in positions) / n
        
        step = 100.0
        min_dist = dist(x, y)
        
        while step > 1e-6:
            improved = False
            for dx, dy in [(0, step), (0, -step), (step, 0), (-step, 0)]:
                new_x, new_y = x + dx, y + dy
                new_dist = dist(new_x, new_y)
                if new_dist < min_dist:
                    min_dist = new_dist
                    x, y = new_x, new_y
                    improved = True
                    break
            
            if not improved:
                step /= 2
        
        return min_dist