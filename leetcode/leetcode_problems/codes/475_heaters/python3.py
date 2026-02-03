"""
Problem: Heaters
Difficulty: Medium
Tags: array, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:
        houses.sort()
        heaters.sort()
        radius = 0
        i = 0
        
        for house in houses:
            while i < len(heaters) - 1 and abs(heaters[i+1] - house) <= abs(heaters[i] - house):
                i += 1
            radius = max(radius, abs(heaters[i] - house))
        
        return radius