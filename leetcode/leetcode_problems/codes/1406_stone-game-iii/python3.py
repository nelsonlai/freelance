"""
Problem: Stone Game III
Difficulty: Hard
Tags: array, dp, math

Approach: DP - dp[i] = max score difference from position i, Alice wins if dp[0] > 0
Time Complexity: O(n) where n is length of stoneValue
Space Complexity: O(n) for DP table
"""

class Solution:
    def stoneGameIII(self, stoneValue: List[int]) -> str:
        n = len(stoneValue)
        dp = [float('-inf')] * (n + 1)
        dp[n] = 0
        
        for i in range(n - 1, -1, -1):
            total = 0
            for j in range(i, min(i + 3, n)):
                total += stoneValue[j]
                dp[i] = max(dp[i], total - dp[j + 1])
        
        if dp[0] > 0:
            return "Alice"
        elif dp[0] < 0:
            return "Bob"
        else:
            return "Tie"