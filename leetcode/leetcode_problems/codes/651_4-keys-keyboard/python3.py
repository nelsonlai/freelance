"""
Problem: 4 Keys Keyboard
Difficulty: Medium
Tags: dp, math

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maxA(self, n: int) -> int:
        dp = [0] * (n + 1)
        
        for i in range(1, n + 1):
            dp[i] = dp[i-1] + 1
            
            for j in range(3, i):
                dp[i] = max(dp[i], dp[i-j] * (j - 1))
        
        return dp[n]