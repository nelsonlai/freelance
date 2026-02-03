"""
Problem: Maximum Profit in Job Scheduling
Difficulty: Hard
Tags: array, dp, sort, search

Approach: Sort by end time, DP with binary search to find last non-overlapping job
Time Complexity: O(n log n) for sorting and binary search
Space Complexity: O(n) for DP array
"""

import bisect

class Solution:
    def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:
        jobs = sorted(zip(endTime, startTime, profit))
        n = len(jobs)
        dp = [0] * (n + 1)
        
        for i in range(n):
            end, start, prof = jobs[i]
            # Binary search for last job that ends before current starts
            idx = bisect.bisect_right(jobs, (start, float('inf'), 0)) - 1
            dp[i + 1] = max(dp[i], dp[idx + 1] + prof)
        
        return dp[n]