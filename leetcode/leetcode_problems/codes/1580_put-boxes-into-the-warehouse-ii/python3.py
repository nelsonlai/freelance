"""
Problem: Put Boxes Into the Warehouse II
Difficulty: Medium
Tags: array, greedy, sort, stack

Approach: Sort boxes, use two pointers from both ends of warehouse, greedy placement
Time Complexity: O(n log n + m) where n is boxes, m is warehouse
Space Complexity: O(1)
"""

class Solution:
    def maxBoxesInWarehouse(self, boxes: List[int], warehouse: List[int]) -> int:
        boxes.sort(reverse=True)
        m = len(warehouse)
        left, right = 0, m - 1
        count = 0
        box_idx = 0
        
        while left <= right and box_idx < len(boxes):
            if boxes[box_idx] <= warehouse[left]:
                count += 1
                left += 1
                box_idx += 1
            elif boxes[box_idx] <= warehouse[right]:
                count += 1
                right -= 1
                box_idx += 1
            else:
                box_idx += 1
        
        return count