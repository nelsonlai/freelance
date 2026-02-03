"""
Problem: Find the Longest Valid Obstacle Course at Each Position
Difficulty: Hard
Tags: array, tree, search, binary search, LIS

Approach: Longest Increasing Subsequence (LIS) with binary search
Time Complexity: O(n log n) where n is obstacles
Space Complexity: O(n)
"""

import bisect

class Solution:
    def longestObstacleCourseAtEachPosition(self, obstacles: List[int]) -> List[int]:
        result = []
        dp = []  # dp[i] = smallest ending value for LIS of length i+1
        
        for obstacle in obstacles:
            idx = bisect.bisect_right(dp, obstacle)
            if idx == len(dp):
                dp.append(obstacle)
            else:
                dp[idx] = obstacle
            result.append(idx + 1)
        
        return result