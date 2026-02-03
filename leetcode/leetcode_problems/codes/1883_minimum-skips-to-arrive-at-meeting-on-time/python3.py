"""
Problem: Minimum Skips to Arrive at Meeting On Time
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j] = min time to reach i with j skips
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2)
"""

class Solution:
    def minSkips(self, dist: List[int], speed: int, hoursBefore: int) -> int:
        n = len(dist)
        # dp[i][j] = min time to reach i with j skips
        dp = [[float('inf')] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(i + 1):
                # Skip rest at position i-1
                if j > 0:
                    dp[i][j] = min(dp[i][j], dp[i-1][j-1] + dist[i-1] / speed)
                
                # Don't skip: round up to nearest integer
                if j < i:
                    dp[i][j] = min(dp[i][j], (dp[i-1][j] + dist[i-1] / speed + 1e-9) // 1 * 1)
        
        for j in range(n + 1):
            if dp[n][j] <= hoursBefore:
                return j
        
        return -1