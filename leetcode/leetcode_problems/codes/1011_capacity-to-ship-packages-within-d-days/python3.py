"""
Problem: Capacity To Ship Packages Within D Days
Difficulty: Medium
Tags: array, search

Approach: Binary search on capacity - find minimum capacity that allows shipping in d days
Time Complexity: O(n * log(sum(weights)))
Space Complexity: O(1)
"""

class Solution:
    def shipWithinDays(self, weights: List[int], days: int) -> int:
        def canShip(capacity):
            current = 0
            needed = 1
            for weight in weights:
                if current + weight > capacity:
                    needed += 1
                    current = weight
                else:
                    current += weight
            return needed <= days
        
        left, right = max(weights), sum(weights)
        
        while left < right:
            mid = (left + right) // 2
            if canShip(mid):
                right = mid
            else:
                left = mid + 1
        
        return left