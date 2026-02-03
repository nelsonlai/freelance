"""
Problem: Minimum Speed to Arrive on Time
Difficulty: Medium
Tags: array, search, binary search

Approach: Binary search on speed, check if can arrive on time
Time Complexity: O(n log(max_speed)) where max_speed is max distance * 100
Space Complexity: O(1)
"""

import math

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        def canArrive(speed):
            total_time = 0
            for i, d in enumerate(dist):
                if i < len(dist) - 1:
                    total_time += math.ceil(d / speed)
                else:
                    total_time += d / speed
            return total_time <= hour
        
        left, right = 1, 10**7
        result = -1
        
        while left <= right:
            mid = (left + right) // 2
            if canArrive(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result