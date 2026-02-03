"""
Problem: Eliminate Maximum Number of Monsters
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort by arrival time, eliminate one per minute
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

class Solution:
    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:
        arrival_times = [d / s for d, s in zip(dist, speed)]
        arrival_times.sort()
        
        for i, time in enumerate(arrival_times):
            if time <= i:
                return i
        
        return len(dist)