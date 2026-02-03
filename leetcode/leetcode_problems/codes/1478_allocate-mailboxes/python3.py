"""
Problem: Allocate Mailboxes
Difficulty: Hard
Tags: array, tree, dp, math, sort

Approach: DP - dp[i][j] = min distance using j mailboxes for first i houses
Time Complexity: O(n^2 * k) where n is number of houses
Space Complexity: O(n * k) for DP table
"""

class Solution:
    def minDistance(self, houses: List[int], k: int) -> int:
        houses.sort()
        n = len(houses)
        
        # cost[i][j] = min distance if one mailbox serves houses[i:j+1]
        cost = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(i, n):
                median = houses[(i + j) // 2]
                cost[i][j] = sum(abs(houses[m] - median) for m in range(i, j + 1))
        
        # dp[i][j] = min distance using j mailboxes for first i houses
        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, min(i, k) + 1):
                for p in range(j - 1, i):
                    dp[i][j] = min(dp[i][j], dp[p][j-1] + cost[p][i-1])
        
        return dp[n][k]