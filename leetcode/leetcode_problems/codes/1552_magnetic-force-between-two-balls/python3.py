"""
Problem: Magnetic Force Between Two Balls
Difficulty: Medium
Tags: array, sort, search

Approach: Binary search on minimum distance, check if we can place m balls with that distance
Time Complexity: O(n log(max_distance)) where n is length of position
Space Complexity: O(1)
"""

class Solution:
    def maxDistance(self, position: List[int], m: int) -> int:
        position.sort()
        n = len(position)
        
        def canPlace(distance):
            count = 1
            last = position[0]
            for i in range(1, n):
                if position[i] - last >= distance:
                    count += 1
                    last = position[i]
                    if count >= m:
                        return True
            return False
        
        left, right = 1, position[-1] - position[0]
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if canPlace(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result