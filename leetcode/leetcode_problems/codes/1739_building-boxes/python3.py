"""
Problem: Building Boxes
Difficulty: Hard
Tags: greedy, math, binary search

Approach: Build pyramid layer by layer, use binary search to find minimum boxes
Time Complexity: O(log n)
Space Complexity: O(1)
"""

class Solution:
    def minimumBoxes(self, n: int) -> int:
        # Find largest complete pyramid
        level = 0
        total = 0
        while total + (level + 1) * (level + 2) // 2 <= n:
            level += 1
            total += level * (level + 1) // 2
        
        # Remaining boxes
        remaining = n - total
        
        # Find minimum boxes on floor to support remaining
        floor = 0
        while floor * (floor + 1) // 2 < remaining:
            floor += 1
        
        # Base boxes = complete pyramid base + floor boxes
        base_boxes = level * (level + 1) // 2 + floor
        
        return base_boxes