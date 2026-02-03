"""
Problem: Maximum Vacation Days
Difficulty: Hard
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maxVacationDays(self, flights: List[List[int]], days: List[List[int]]) -> int:
        n = len(flights)
        k = len(days[0])
        
        dp = [[-1] * n for _ in range(k)]
        
        for city in range(n):
            if city == 0 or flights[0][city]:
                dp[0][city] = days[city][0]
        
        for week in range(1, k):
            for city in range(n):
                for prev_city in range(n):
                    if dp[week-1][prev_city] != -1:
                        if prev_city == city or flights[prev_city][city]:
                            dp[week][city] = max(dp[week][city], 
                                                dp[week-1][prev_city] + days[city][week])
        
        return max(dp[k-1])