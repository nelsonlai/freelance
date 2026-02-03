"""
Problem: Maximum Earnings From Taxi
Difficulty: Medium
Tags: array, dp, hash, sort, search

Approach: DP - sort rides by end time, use binary search to find previous compatible ride
Time Complexity: O(n log n) where n is number of rides
Space Complexity: O(n)
"""

class Solution:
    def maxTaxiEarnings(self, n: int, rides: List[List[int]]) -> int:
        rides.sort(key=lambda x: x[1])  # Sort by end time
        m = len(rides)
        dp = [0] * (m + 1)
        
        for i in range(m):
            start, end, tip = rides[i]
            earnings = end - start + tip
            
            # Binary search for last ride that ends before current start
            left, right = 0, i
            while left < right:
                mid = (left + right + 1) // 2
                if rides[mid][1] <= start:
                    left = mid
                else:
                    right = mid - 1
            
            # Take current ride or skip it
            if rides[left][1] <= start:
                dp[i + 1] = max(dp[i], dp[left + 1] + earnings)
            else:
                dp[i + 1] = max(dp[i], earnings)
        
        return dp[m]