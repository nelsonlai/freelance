"""
Problem: Minimum Time For K Virus Variants to Spread
Difficulty: Hard
Tags: array, math, search, binary search, geometry

Approach: Binary search on time, check if k points can be covered by circles
Time Complexity: O(n^2 * log(max_time))
Space Complexity: O(1)
"""

class Solution:
    def minDayskVariants(self, points: List[List[int]], k: int) -> int:
        def can_cover(t):
            # Check if k points can be covered within time t
            n = len(points)
            for i in range(n):
                for j in range(n):
                    # Try circle centered at midpoint of points[i] and points[j]
                    cx = (points[i][0] + points[j][0]) / 2
                    cy = (points[i][1] + points[j][1]) / 2
                    count = 0
                    for px, py in points:
                        dist = ((px - cx) ** 2 + (py - cy) ** 2) ** 0.5
                        if dist <= t:
                            count += 1
                    if count >= k:
                        return True
            return False
        
        left, right = 0, 10**9
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if can_cover(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result