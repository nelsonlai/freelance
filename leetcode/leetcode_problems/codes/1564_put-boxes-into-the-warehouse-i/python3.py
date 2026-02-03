"""
Problem: Put Boxes Into the Warehouse I
Difficulty: Medium
Tags: array, greedy, sort, stack

Approach: Sort boxes, use greedy - try to place largest boxes first, track warehouse heights
Time Complexity: O(n log n + m) where n is boxes, m is warehouse
Space Complexity: O(m) for effective heights
"""

class Solution:
    def maxBoxesInWarehouse(self, boxes: List[int], warehouse: List[int]) -> int:
        boxes.sort(reverse=True)
        m = len(warehouse)
        effective_heights = [warehouse[0]]
        
        for i in range(1, m):
            effective_heights.append(min(effective_heights[-1], warehouse[i]))
        
        count = 0
        box_idx = 0
        
        for i in range(m - 1, -1, -1):
            if box_idx < len(boxes) and boxes[box_idx] <= effective_heights[i]:
                count += 1
                box_idx += 1
        
        return count