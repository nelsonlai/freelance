"""
Problem: Guess Number Higher or Lower II
Difficulty: Medium
Tags: graph, dp, math

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def getMoneyAmount(self, n: int) -> int:
        dp = [[0] * (n + 1) for _ in range(n + 1)]
        
        for length in range(2, n + 1):
            for start in range(1, n - length + 2):
                end = start + length - 1
                dp[start][end] = float('inf')
                
                for guess in range(start, end + 1):
                    cost = guess
                    if guess > start:
                        cost += dp[start][guess - 1]
                    if guess < end:
                        cost += dp[guess + 1][end]
                    dp[start][end] = min(dp[start][end], cost)
        
        return dp[1][n]