"""
Problem: Add Minimum Number of Rungs
Difficulty: Medium
Tags: array, greedy

Approach: Calculate gaps between rungs, add rungs if gap > dist
Time Complexity: O(n) where n is rungs
Space Complexity: O(1)
"""

class Solution:
    def addRungs(self, rungs: List[int], dist: int) -> int:
        count = 0
        prev = 0
        
        for rung in rungs:
            gap = rung - prev
            if gap > dist:
                count += (gap - 1) // dist
            prev = rung
        
        return count