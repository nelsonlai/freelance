"""
Problem: Maximum Units on a Truck
Difficulty: Easy
Tags: array, greedy, sort

Approach: Sort by units per box descending, greedily take boxes with most units
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def maximumUnits(self, boxTypes: List[List[int]], truckSize: int) -> int:
        boxTypes.sort(key=lambda x: x[1], reverse=True)
        result = 0
        
        for boxes, units in boxTypes:
            take = min(boxes, truckSize)
            result += take * units
            truckSize -= take
            if truckSize == 0:
                break
        
        return result