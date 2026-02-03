"""
Problem: Stone Game IV
Difficulty: Hard
Tags: dp, math

Approach: DP - dp[i] = True if current player can win with i stones
Time Complexity: O(n * sqrt(n))
Space Complexity: O(n) for DP table
"""

class Solution:
    def winnerSquareGame(self, n: int) -> bool:
        dp = [False] * (n + 1)
        
        for i in range(1, n + 1):
            j = 1
            while j * j <= i:
                if not dp[i - j * j]:
                    dp[i] = True
                    break
                j += 1
        
        return dp[n]